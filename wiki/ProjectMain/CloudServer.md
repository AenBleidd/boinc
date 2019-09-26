# Deploying a BOINC server in the Amazon Elastic Computing Cloud

```This is a contributed tutorial on how to get a BOINC server going using Amazon Web Services. This is just a snapshot and not always up to date (you need to update on your own!). See it as a tutorial on how to start. Please don't copy and paste commands you don't understand!```

## Why use a Cloud?

Hosting a BOINC server on a cloud has two advantages:
* It's cheaper for small projects to rent time on a cloud versus paying for hardware, bandwidth, and electric power.
* It's easier and faster to use an existing OS image with the BOINC server already installed than to compile and configure it.

For an in-depth cost-benefit analysis, please read:
[Cost-Benefit Analysis of Cloud Computing versus Desktop Grids](http://mescal.imag.fr/membres/derrick.kondo/pubs/kondo_hcw09.pdf).  Derrick Kondo, Bahman Javadi, Paul Malecot, Franck Cappello and David Anderson.  8th International Heterogeneity in Computing Workshop, May 25 2009, Rome. 

You can set up a free BOINC server in a few minutes using a preconfigured server for Amazon's Elastic Compute Cloud.

## Deploying the BOINC Server Image

* Navigate to to aws.amazon.com and create an account if needed (requires a credit card, but it will not be charged for 12 months).
* Click “EC2: Virtual Servers in the Cloud” and “Launch Instance”.
* Click “Community AMIs” (left sidebar), search for “BOINCServerTemplate”, and click on the blue Launch Button.
* Choose type “t2.micro: Free tier eligible” and “Review and Launch”.
* Click “Edit security groups”, “Add Rule” and select type “HTTP”.
* Click “Review and Launch” and then “Launch”.
* If you do not have a key pair, choose “Create a new key pair” and give it a name like BOINCKeypair, click on “Download Key Pair”, and save BOINCKeypair.pem in a safe place.
* Click on “Launch instance” and  “View Instances”.
* Wait until your instance changes from Instance State “Pending” to “running” with a green circle.

Paste the Public IP nnn.nnn.nnn.nnn (once it appears) into a web browser, and it should say “Apache2 Ubuntu Default Page”. You can assign a static IP address by choosing Elastic IP in the left side bar, allocate IP, and associate the IP with your instance. You can then buy a domain name and point to that static IP.

Then, connect to Public IP nnn.nnn.nnn.nnn by ssh. For instance, download PuTTY, use PuTTYgen to import the .pem file and save a .ppk file, and choose public ip address nnn.nnn.nnn.nnn, port 22, connection type SSH, choose Connection, SSH, Auth, and browse to find the .ppk file, click Open, click Yes at the “PuTTY Security Alert”. At the "login:" prompt, enter "ubuntu".

```bash
$su boincadm
password: boincadm
$cd /home/boincadm/boinc/tools
$hostname
ip-nnn-nnn-nnn-nnn  (note: this is the internal IP address, with dashes, different from the public IP)
$./make_project --url_base http://nnn.nnn.nnn.nnn/ --project_host ip-nnn-nnn-nnn-nnn --test_app uppercase
...

[Y/n] (hit enter)

$cd /home/boincadm/projects/uppercase/

$sudo -- sh -c 'cat /home/boincadm/projects/uppercase/uppercase.httpd.conf >> /etc/apache2/httpd.conf'

```
Check in a web browser that the page `http://nnn.nnn.nnn.nnn/uppercase` works and has the title `REPLACE WITH PROJECT NAME`

```bash
$bin/xadd
$bin/update_versions
```

Choose "y" repeatedly

```
$bin/start
```

In a web browser, using the Public IP, navigate to `http://nnn.nnn.nnn.nnn/uppercase/server_status.php`. Status should be "Running" green now for all Programs on the left.

 Using a BOINC client, add the project `nnn.nnn.nnn.nnn/uppercase` and the client should start downloading and doing work. Congratulations you have a working BOINC project!

To protect your administrator page:

```bash
$cd /home/boincadm/projects/uppercase/html/ops
$htpasswd -c .htpasswd boincadm
password: boincadm (choose your own password)
```

In the web browser, navigate to your project administrator web interface at `http://nnn.nnn.nnn.nnn/uppercase_ops`. Click on `Summary` to see work already done.

## Creating Your Own Application

To create your application, you need a work generator, a client program in Windows/unix, and an assimilator to combine the work that comes back. To modify the work generator and sample assimilator:

```bash
$cd /home/boincadm/boinc/sched/
$emacs sample_work_generator.cpp
$emacs sample_assimilator.cpp
$make
$cp sample_work_generator /home/boinc/projects/uppercase/bin
$cp sample_assimilator /home/boinc/projects/uppercase/bin
$cd /home/boincadm/projects/uppercase
$bin/stop
$bin/start
```

To modify the Unix client program in Unix,

```bash
$emacs /home/boincadm/boinc/samples/example_app/uc2.cpp
$make
$cd /home/boincadm/apps/example_app
$cp -r 22489 30000 (to create the directories for the new versions)
$cd 30000/x86_64-pc-linux-gnu
$cp /home/boinc/boinc/samples/example_app/uc2 /home/boinc/projects/apps/example_app/30000/x86_64-pc-linux-gnu/example_app_30000_x86_64-pc-linux-gnu
```

and delete the other files in that directory. To create updated client program for Windows, download Microsoft C++ Express Version 10, download the boinc source, Build All, in project `example_app` of the `boinc` solution, edit `uc2.cpp`, Build All, run the compiled program `win_build\Build\Win32\Release` with input file `in`, and review the output file `out` and the `stderr.txt`. When the program is ready, use `FileZilla` to transfer the file `example_app.exe` to `http://nnn.nnn.nnn.nnn/`, SFTP, username `ubuntu`, select the private .ppk key under Settings, SFTP, and click on the `example_app.exe` file in the left hand tree. Connect to your server, and look for the file in `/home/ubuntu`. Then

```bash
$cp /home/ubuntu/example_app.exe /home/boincadm/projects/uppercase/apps/example_app/30000/windows_intelx86/example_app_30000_windows_intelx86.exe
```

and delete the older versions in that directory. Delete other architectures for which you do not have clients in the 30000 directory. Navigate in the browser to `http://nnn.nnn.nnn.nnn/uppercase_ops/`, choose `Manage application versions` and deprecated the old versions.

To fix the appearance of the page `http://nnn.nnn.nnn.nnn/uppercase`, edit `/home/boincadm/projects/uppercase/html/project.in` especially to enter the project name in place of `REPLACE WITH PROJECT NAME` the `COPYRIGHT_HOLDER`, the `SYS_ADMIN_EMAIL`, and the smtp settings. To limit SPAM users, add akismet and recaptcha keys to `config.xml`.

## Notes

Change the following default passwords: for the Unix user `boincadm` password `boincadm`, and for the mysql `root` user password `boincadm`. The mysql user `boincadm` has not password; add one and update `config.xml`. Edit `/etc/apache2/apache2.config` and `/etc/apache2/httpd.config` to use the `Require` directory in both places.

## Questions?

Email: daniel-monroe :: verizon net.
