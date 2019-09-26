# Setting up a BOINC server

You can set up a BOINC server in a commercial cloud, such as [Amazon](CloudServer) or Google. The hardware and most of the software issues are taken care of for you. You'll have to pay, but it may be cheaper than using your own hardware.

If you choose to use your own hardware, there are several software options:

* Use [a set of Docker containers](https://github.com/marius311/boinc-server-docker) developed by Marius Millea.

* Use a [BOINC server VM](VmServer) that we've created, with all the necessary software already installed. You can run this virtual machine using [VirtualBox](https://www.virtualbox.org/) on any Intel-based computer (Windows, Linux, or Mac OS X).

* Debian and Ubuntu offer a "boinc-server-maker" package to create BOINC projects more easily on local or remote machines. This ongoing effort is described [here](http://wiki.debian.org/BOINC/ServerGuide).

* Build BOINC from source on your own system. You can use any Unix system as a BOINC server; we recommend using a recent Linux release. Disable SELinux. General instructions are given below, followed by a [cookbook for setting up a BOINC server on a Debian system](#cookbook-for-debian).

## Hardware
For experimentation and debugging, you can use almost any computer as a BOINC server. Before deploying a project more widely, make sure that your server has adequate performance, availability, and security. Some factors:

* Your server must have a static IP address.
* Your Internet connection should have adequate performance and reliability.
* Your server should have 64-bit processors, at least 8 GB of RAM, and at least 40 GB of free disk space.
* Do whatever you can to make it highly reliable (UPS power supply, RAID disk configuration, hot-swappable spares, temperature-controlled machine room, etc.).
* Put it behind a firewall; allow access via port 80 (HTTP) and optionally 443 (HTTPS).
* Make it secure; turn off any unneeded network services, especially those that use plaintext passwords (like FTP or Telnet).

Info on increasing capacity and reliability is [here](MultiHost).

## Installing the BOINC server on Unix
### Groups and permissions
BOINC server programs run as two different users:

* The scheduler, file upload handler, and web software run under the web server account (on Fedora this is user '`apache`'; on Debian it's '`www-data`').

* Other programs run under a normal user account, called the `'project owner'`.

The project owner may be your existing account, or you can create a new account for this purpose with `useradd`. In the following we'll assume that the project owner is `boincadm`, with primary group `boincadm`.

**Do not use root as the project owner**.

By default, the directories created by the apache web server user (on Fedora this is user '`apache`'; on Ubuntu or Debian it's '`www-data`') are not world-writable. This causes problems: for example, when the file upload handler creates a directory in the [upload hierarchy](DirHierarchy), on Fedora it's owned by (`apache`, `apache`), and the [file deleter](FileDeleter) (which runs as `boincadm`) won't be able to delete the files there.

To solve this problem on Fedora, add `apache` to the to group `boincadm` using

```bash
$ usermod -a -G boincadm apache
```
To solve this problem on Debian or Ubuntu, add `www-data` to the to group `boincadm` using

```bash
$ usermod -a -G boincadm www-data
```
or edit `/etc/group` and change the line

```
boincadm:x:566:
```
to

```
boincadm:x:566:apache
```
(the "566" is the group ID; it may be different on your system).

Apache will need to be restarted for this to take effect.

Both `boincadm` and `apache` or `www-data` (depending on your linux flavour) should have [umasks](http://en.wikipedia.org/wiki/Umask) that allow group read and write. The place to set this depends on what distribution is used. Normally you can use a umask of 0002 or 0007.

When you create a BOINC project using [make_project](MakeProject), the critical directories are owned by `boincadm` and have the set-GID bit set; this means that any directories or files created by `apache` or  `www-data` in those directories will have group `boincadm` (not group `apache` or `www-data`). The BOINC software makes all directories group read/write. Thus, both `boincadm` and `apache`  or `www-data`  will have read/write access to all directories and files, but other users will have no access.

To fix permissions on an existing project, do:

```bash
chmod 02770 upload
chmod 02770 html/cache
chmod 02770 html/inc
chmod 02770 html/languages
chmod 02770 html/languages/compiled
chmod 02770 html/user_profile
```
You may also need to change the ownership of these directories and all their subdirectories to `boincadm/boinc`. If you're running several projects on the same server and want to isolate them from each other, you can create a different user and group for each project, and add `apache` or `www-data` to all of the groups.

When serving your project files from Apache, note that all directories up to and including the `html` directory must have execute permissions. For example, if you use `make_project` to create the project template in your home directory, your home directory must have 711 permissions as opposed to the default of 700. If this is not corrected, you will receive a `403 Forbidden` error when attempted to browse to your project page. See [more information on dealing with Apache permissions problems](http://httpd.apache.org/docs/1.3/misc/FAQ.html#forbidden).

### Installing BOINC software
* Download and install the needed [software prerequisites](SoftwarePrereqsUnix).
* [Download](SourceCodeGit) the BOINC software.
* [Configure and build](BuildSystem) the BOINC software.

### Make Project
After installation the BOINC software, you should run the [make_project](MakeProject) script to create the project.

After creating a project, a check_project script is available to check your installation. The script will try to check the permissions of various directories as well as the installation of specific PHP modules which are needed for project operations.

### Operating system configuration
Some parts of the BOINC server (the feeder and scheduling server) use shared memory. Hosts where these run must have shared memory enabled, with a maximum segment size of at least 32 MB. How to do this depends on the operating system; see e.g. [here](https://www.msi.umn.edu/~cpsosa/ChemApps/QuaChem/gaussian_tech/support/download/Linux_shared_mem_seg.html) for more information.

### MySQL notes
Instructions for setting up MySQL are [here](https://dev.mysql.com/doc/refman/5.6/en/linux-installation-yum-repo.html) and [here](http://www.if-not-true-then-false.com/2010/install-mysql-on-fedora-centos-red-hat-rhel/)

After setting up MySQL, create a MySQL account for the project owner. We'll use the name `boincadm`, same as the Unix account. All MySQL accounts should be password protected; we'll use "foobar" (use something different).

```bash
mysql -u root -p
CREATE USER 'boincadm'@'localhost' IDENTIFIED BY 'foobar';
GRANT ALL ON *.* TO 'boincadm'@'localhost';
```
This gives boincadm access to all MySQL databases on the host; if you use MySQL for other purposes on the host, set permissions more restrictively.

Other notes:

* Set boincadm's `PATH` environment variable to include MySQL programs (typically `/usr/local/mysql` and `/usr/local/mysql/bin`).
* You'll want to back up your database periodically. Generally this requires stopping the project, making a copy or snapshot, and restarting. An example is [here](https://boinc.berkeley.edu/mysql_backup.txt).
* BOINC gets MySQL compiler and linker flags from a program called `mysql_config` which comes with your MySQL distribution. This sometimes references libraries that are not part of your base system installation, such as `-lnsl` or `-lnss_files`. You may need to install additional packages (often you can use something called `mysql-dev` or `mysql-devel`) or fiddle with Makefiles.
* MySQL can be the bottleneck in a BOINC server. To optimize its performance, read about [configuring MySQL for BOINC](MysqlConfig).
* [Notes on running MySQL on a cluster](https://boinc.berkeley.edu/mysql_cluster.txt).

### MySQLclient notes
* Configure mysql with the `--enable-thread-safe-client` switch.
* Set your `LD_LIBRARY_PATH` to refer to the correct library.

### Apache notes
In `httpd.conf` or `apache2.conf` on Ubuntu, set the default MIME type as follows (otherwise you'll get file upload signature verification errors):

```
DefaultType application/octet-stream
```
To limit denial-of-service attacks, we recommend turning off directory indexing by adding `-Indexes` to the [Options](http://httpd.apache.org/docs/2.0/mod/core.html#options) directive.

Make sure that the filename extensions used by your application or data files aren't handled in undesired way by Apache. For example, if some of your files have a '.map' extension, remove the line

```
AddHandler imap-file map
```
from httpd.conf

Apache has a default request size limit of 1 MB. If your project is likely to exceed this (large output files, large scheduler request messages) increase this, e.g. to 128 MB:

```
LimitXMLRequestBody 134217728
LimitRequestBody 134217728
```
On Debian and Ubuntu Apache's cgi module is not enabled by default. Use the following command to enable it:

```
sudo a2enmod cgi
```

### PHP configuration
You may need to add the GD and XML libraries to your PHP; You can do this with a command like

```bash
yum install php-gd php-xml
```
then restart Apache.

For more information: [manual](http://www.php.net/manual/en/image.installation.php)

If you build PHP from source, use the following:

```bash
configure --with-jpeg-dir --with-png-dir --with-mysqli --with-curl --with-gd --with-zlib
```

### PHPMailer
By default, BOINC uses PHP's `mail` function to send email to participants. This uses sendmail. If this doesn't work, you can use [PHPMailer](https://github.com/PHPMailer/PHPMailer), is a very flexible mail-sending mechanism, instead. To do this:

* Download `PHPMailer` and put it under `PROJECT/html/inc/PHPMailer` (i.e. the files `src/PHPMailer.php` and `src/SMTP.php` should be in that directory).
* Edit your `html/project/project.inc` to add a function like
```php
function make_php_mailer() {
    $mail = new PHPMailer();
    $mail->IsSMTP();
    $mail->SMTPAuth = true;
    $mail->SMTPSecure = "tls";
    $mail->Host = "smtp.gmail.com";
    $mail->Port = 587;
    $mail->Username = "john.doe@gmail.com";
    $mail->Password = "xxx";
    $mail->SetFrom('admin@boincproject.com', 'John Doe');
    $mail->AddReplyTo("admin@boincproject.com", "John Doe");
    return $mail;
}
```
(substitute the values appropriate to your SMTP server).

### Common problems

After adding a new user, you have to check if the home directory was created. Sometimes you have to manually create it.

```bash
$ mkdir /home/{username}
$ chown {username}:{username} /home/{username}
```

The link `/usr/bin/gcc` that points to the currently used compiler could be missing. This could lead to errors when running the make command. Especially when trying to compile the graphical part of the API you need the `/usr/bin/g++` link (make gives a warning that it couldn't find GL/GLU/GLUT although it is installed). So you have to create the symbolic links, depending on your gcc and g++ version, first.

```bash
$ ln -s /usr/bin/gcc-4.11 /usr/bin/gcc
$ ln -s /usr/bin/g++-4.11 /usr/bin/g++
```

At newer linux distributions you can’t login as user root. Instead there is a user notroot with whom you can login, but you won’t have root privileges. If an application or script needs root privileges, you are forced to enter the password you entered during the installation. In the console window you can get root privileges with the su (Debian) or sudo (Ubuntu, Fedora) command also. Note the single quotes around the command when using `su -c` !

```bash
$ su -c {'command'}
$ sudo {command}
```

If you have problems executing the sudo command, you have to add the user to the `/etc/sudoers` file. To edit this file just use this command:

```bash
$ sudo visudo
```

In this file you have to add another line after the line for `notroot`. You can use this:

```
{username} ALL=(ALL) ALL
```

## Cookbook for Debian

Please follow these recipes only for your basic orientation. The Debian landscape has changed a lot over since Debian 4.0. You can inspect the build and runtime dependencies of the `boinc-server-maker` package [here](http://anonscm.debian.org/gitweb/?p=pkg-boinc/boinc.git;a=blob_plain;f=debian/control;hb=HEAD) and the latter more graphically also [here](http://packages.debian.org/unstable/net/boinc-server-maker).

### Install software prerequisites

Common packages for building BOINC (based on [Software prerequisites (Unix/Linux)](SoftwarePrereqsUnix)):

```
m4
make
dh-autoreconf
pkg-config
git
vim
```

packages needed for BOINC server:

* Installed via apt

```
libapache2-mod-php
default-mysql-server
default-libmysqlclient-dev
php-mysql
php-cli
php-gd
phpmyadmin
python2.7
python3
python3-pip
python3-dev
python-mysqldb (or MySQL-python)
libssl-dev
libcurl4-openssl-dev
```

* Installed via pip

```
mysqlclient
```

packages needed for BOINC libraries (including graphics):

```
freeglut3-dev
libxmu-dev
libxi-dev
libjpeg62-turbo-dev
```

packages needed for BOINC client and manager (in addition to libraries):

```
libssl-dev
libcurl4-openssl-dev
libxss-dev
libnotify-dev
libxcb-atom1-dev
libsqlite3-dev
```

optional packages for a graphical desktop manager

```
kdebase
kde-guidance
synaptic
iceweasel
xserver-org
```

This list contains all necessary packages for the BOINC server and the client components. At first startup, these packages should be installed with aptitude. The graphical desktop manager is optional, but makes the configuration of the server a bit easier. The list contains no security packages to secure your server! Please ask your system administrator or read a good Linux book on how to secure your server against attacks.

Hint: You can search packages within aptitude by pressing the '/' key.

### Create a new BOINC user account
The best way to create the boinc user is during installation when you are asked for name and password of the main user. Enter `boincadm`, or a name of your choice, as login name. In this cookbook I will refer to this useraccount as `boincadm`.

When installation is finished please login as the user created during installation. If you have installed a graphical desktop manager please open a text console (Konsole or xterm).

Next step is to add the `www-data` user (apache webserver) to the group of the newly created user:

```bash
$ usermod -a -G boincadm www-data
```

### Configuration of the MySQL server

Create a new MySQL database user account.

```bash
$ mysql -h localhost -u root -p
> GRANT ALL ON *.* TO 'boincadm'@'localhost';
> SET PASSWORD FOR 'boincadm'@'localhost'=''; 
```

The permissions can be limited to project database only, later; Defining an empty password simplifies the installation, can be changed later.

You can also set this using the phpmyadmin interface available through ```!http://{server-IP}/phpmyadmin```

### Download the BOINC source code

The latest development version can be obtained with:

```bash
$ cd ~
$ git clone https://github.com/BOINC/boinc.git boinc-src
```

To update the source code just go into the main directory and enter:

```bash
$ cd ~/boinc-src
$ git pull
```

A stable `client` version can be obtained from [BOINC website](https://boinc.berkeley.edu/download_all.php). Hint: Normally you won't need a self-compiled client,

NOTE: Tags are only for client software, always checkout the latest version for the server!

### Compiling BOINC source code

Enter the following commands into the console window:

```bash
$ cd ~/boinc-src
$ ./_autosetup
$ ./configure --disable-client --disable-manager
$ make
```