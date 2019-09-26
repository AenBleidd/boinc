# The `make_project` script

The `make_project` script creates the server components of a BOINC project.
To use it, [set up a BOINC server](ServerIntro.md).
Then, for example, type:
```bash
cd BOINC_SOURCE/tools
./make_project --db_passwd xxx --test_app cplan
```
where 'xxx' is the MySQL password of boincadm.
This creates a project with [master URL](ServerComponents.md) `http://HOSTNAME/cplan/`
whose directory structure is rooted at `$HOME/projects/cplan`.

More specifically, `make_project` does the following:

* Create the [project directory and its subdirectories](ServerDirs.md).
* Create the project's encryption keys if necessary. NOTE: before making the project visible to the public, you must move the code-signing private key to a highly secure (preferably non-networked) host, and delete it from the server host.
* Create and initialize the [MySQL database](DataBase.md).
* Copy source and executable files.
* Generate the project's [configuration file](ProjectConfigFile.md).

With the `--test_app` option,
the project will have a [test application](ExampleApps.md) (uppercase)
and daemons to generate and handle work for this application.
This lets you quickly check that the project is working;
you can remove the test application later by marking it deprecated in your [administrative web interface](HtmlOps.md).

The following steps complete the project setup:

* Insert `cplan.httpd.conf` into `/etc/apache/httpd.conf` (path varies), or [Include](http://httpd.apache.org/docs/2.0/mod/core.html#include) it from that file, or symlink it into `/etc/apache2/sites-enabled` (on Debian) via 
```bash
sudo ln -s /home/boincadm/projects/cplan/cplan.httpd.conf /etc/apache2/sites-enabled
```

* Generate a username/password file for your [administrative web interface](HtmlOps.md) using:
```bash
htpasswd -cb ~/projects/cplan/html/ops/.htpasswd username password
```
* Run `crontab -e`, and add an entry to run the project's cron script:
```
 0,5,10,15,20,25,30,35,40,45,50,55 * * * * /home/boincadm/cplan/bin/start --cron
```
* **or** type this command to include the line above to your crontab automaticaly:
```bash
 $ crontab ~/projects/cplan/cplan.cronjob
```
(if cron cannot run 'start', try using a helper script to set the `PATH` and `PYTHONPATH` environment variables)
* Run [bin/xadd](XaddTool.md) and [UpdateVersions bin/update_versions] in the project's home directory.
* Run [bin/start](StartTool.md).

The script prints instructions for these steps.

The command-line syntax is as follows:
```bash
make_project [options] project_name [ 'Project Long Name' ]
```
Options are as follows (normally you don't need to include any of them):

## Directory options

| Option | Description |
| --- | --- |
| --srcdir | The BOINC source directory. Default: . or .. |
| --project_root | Project root directory path. Default: `$HOME/projects/PROJECT_NAME` |
| --key_dir | Where keys are stored. Default: `PROJECT_ROOT/keys` |
| --no_query | Accept all directories without yes/no query |
| --delete_prev_inst | Delete project-root first (from prev installation) |

## URL options

| Option | Description |
| --- | --- |
| --url_base | Used to build the URL defaults, see below. Default: `http://HOSTNAME/` |
| --html_user_url | Master URL (where clients attach, and the main website is). Default: `URL_BASE/PROJECT_NAME/` |
| --html_ops_url | Admin URL. Default: `URL_BASE/PROJECT_NAME_ops/` |
| --cgi_url | CGI URL. Default: `URL_BASE/PROJECT_cgi/` |

## Database options

| Option | Description |
| --- | --- |
| --db_host | Database host. Default: localhost |
| --db_name | Database name. Default: `PROJECT_NAME` |
| --db_user | Database user. Default: `USER_NAME` |
| --db_passwd | Database password. Default: None |
| --drop_db_first | Drop database first (from prev installation) |

## Miscellaneous options

| Option | Description |
| --- | --- |
| --test_app | install test application |
| --web_only | Install only web features (for [BossaIntro Bossa], [BoltIntro Bolt]) |
| --user_name | Install project as this user (used as DB_USER). Default: current user |
| -h or --help | Show options |

## Check project

After making a project. a check_project script is available to help check certain aspects of the system. Specifically it checks for three things.

1. Checks the permissions for the apache web server user on certain project directories, to make sure they are writable.
1. Checks to see if specific PHP modules are installed.
1. Checks to see if certain command line program/tools are installed and executable.

Running this script after making a project may help in identifying some of the common problems that may occur. 

## options

| Option | Descrption |
| --- | --- |
| -p or --project_dir | project installation directory |
| -a or --apache_user | (optional) the apache user name, script will attempt to auto-detect this if this option is left blank. |
| -h or --help | Show options |

## Deleting a project

To delete a project, in this example named 'cplan', delete its directory and its database:
```bash
cd ~/projects
/bin/rm -rf cplan

mysql
> drop database cplan;
```
