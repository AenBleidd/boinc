# Increasing server capacity

The BOINC server software is designed so that a project with tens of thousands of volunteers can run on a single server computer. However, the capacity of this computer may eventually be exceeded. Symptoms of server overload include:
* dropped connections
* slow web site access
* daemons fall behind
* database queries take minutes or hours to complete

If you experience these problems, try the following (in order).

## Use Fast CGI
[Fast CGI](http://fastcgi.coremail.cn/) uses long-lived processes that handle lots of requests, instead of creating a new process
for each request.
This eliminates the overhead of creating processes and connecting to the database.
To use Fast CGI:
* Build (or yum or apt-get) an Apache server with mod_fcgid (or mod_fastcgi - an older compatible version of mod_fcgid)
* compile the Fast CGI version of the scheduler (`fcgi`) and file upload handler (`fcgi_file_upload_handler`). To do that run `./configure` with `--enable-fcgi` parameter.
* Copy these to your project's cgi-bin directory, with the names `cgi`' and `file_upload_handler`.
* Edit the following line in your `fcgid.conf` (usually in `/etc/httpd/conf.d/fcgid.conf`):

```
AddHandler fcgid-script fcg fcgi fpl
```

 change to:

```
AddHandler fcgid-script fcg fcgi fpl cgi
```

* Add the following directive to your httpd.conf (usually in /etc/httpd/conf):

```
<Location /cgi-bin>
 SetHandler fcgid-script
 Options ExecCGI
 allow from all
</Location>
```

..except change `cgi-bin` to the name of the URL path to your actual cgi directory according to any alias you may have used in apache. For example a project might have the scheduler URL ```http://boinc.project.edu/boinc_cgi/cgi``` which is scriptalias'ed in `httpd.conf`:

```
ScriptAlias /boinc_cgi /home/boinc/projects/cgi-bin
```

So make the Location line: `<Location /boinc_cgi> `

* restart Apache.

## Upgrade your hardware

Use a host with good CPU capacity (dual Xeon or Opteron), at least 2 GB of RAM, and at least 40 GB of free disk space. Do whatever you can to make it highly reliable (UPS power supply, RAID disk configuration, hot-swappable spares, temperature-controlled machine room, etc.). For a high-traffic project, use a machine with 8 GB of RAM or more, and 64-bit processors.

## Run MySQL on a separate host
When you initially create a BOINC project using [make_project](MakeProject.md), everything runs on a single host: MySQL database server, web server, scheduling server, daemons, tasks, and file upload handler.  Of these tasks, the MySQL server does the most work (typically as much as all the others combined). So, if you need to increase the capacity of your server the first step is to move the MySQL server to a separate host (preferably a fast computer with lots of memory). Specify this host in the [project configuration file](ProjectOptions.md).

## Create a read-only DB replica

You can use MySQL's replication mechanism to create a read-only replica.
If you [ProjectOptions#db add this to your configuration file],
some high-traffic web pages and the db_dump program will use the replica,
reducing the load on your main DB server.

## Run server daemons and tasks on multiple hosts

If you need more server capacity, you can move some of the server [daemons](ProjectDaemons.md) and [tasks](ProjectTasks.md) to separate hosts. (Start by moving the one that's doing the most work).

When you move daemons and tasks to other hosts, those hosts must satisfy the following rules:

* The [project admin account](ServerIntro.md#groups-and-permissions) must exist on all hosts, and a user must be able to use `ssh` to run commands on any other host without typing a password.
 * The hosts must share a common network file system, and path to the project directory relative to the project admin's home directory (typically `~/projects/PROJECT_NAME`) must be the same on all hosts.
 * One host is designated as the project's `main host` in config.xml. **The 'start', 'stop', and 'status' scripts should normally be run on the main host** (if you run them on a different host X, they'll affect only daemons and tasks on host X).
 * The project admin account on all hosts must be able to access the project's MySQL database. (Exception: data servers and file upload handlers don't need DB access).

Host locations are specified as follows:
* Scheduling servers are listed in the project's [master page](ServerComponents.md).
* The hosts on which tasks and daemons are run are specified in the [config.xml](ProjectConfigFile.md) file.
* Data servers are listed in [template files](WorkGeneration.md).
* File upload handlers are listed in [result template files](WorkGeneration.md).
* Your web server runs on the host to which your project URL is mapped.

## Parallelize schedulers and daemons

If you need even more server capacity, you can parallelize most of the BOINC daemons so that multiple instances run on a single (multiprocessor) host, or on different hosts. For example, the following [config.xml](ProjectDaemons.md) entries run two instances of the transitioner on the host 'kosh'. Because these instances are on the same host, you must specify different output and PID files.

```xml
<daemon>
  <host>kosh</host>
  <cmd>transitioner -d 1 -mod 2 0</cmd>
  <output>transitioner0.log</output>
  <pid_file>transitioner0.pid</pid_file>
</daemon>
<daemon>
  <host>kosh</host>
  <cmd>transitioner -d 1 -mod 2 1</cmd>
  <output>transitioner1.log</output>
  <pid_file>transitioner1.pid</pid_file>
</daemon>
```

You can run scheduling servers on multiple hosts by running an instance of the feeder on each host, and including the URLs in your master file.

Example of projects using multiple hosts are [Leiden Classical](http://boinc.gorlaeus.net/ServerHardware.php) and [SIMAP](http://boinc.bio.wzw.tum.de/boincsimap/server_hardware.php).

## Increasing network performance

For projects using "fast" links, or even for internal networks, there
can be some performance gains from tuning system TCP settings.

A few links:

http://dsd.lbl.gov/TCP-tuning/background.html

http://dsd.lbl.gov/TCP-tuning/linux.html

http://proj.sunet.se/E2E/tcptune.html

http://www.onlamp.com/pub/a/onlamp/2005/11/17/tcp_tuning.html?page=1

http://www.psc.edu/networking/projects/tcptune/

http://www.acc.umu.se/~maswan/linux-netperf.txt

http://datatag.web.cern.ch/datatag/howto/tcp.html

http://www.aarnet.edu.au/engineering/networkdesign/mtu/local.html

http://www.hep.ucl.ac.uk/~ytl/tcpip/linux/txqueuelen/

And for bonding multiple links/interfaces:

http://www.linux-corner.info/bonding.html

http://www.devco.net/archives/2004/11/26/linux_ethernet_bonding.php

You can greatly improve your data transfer rate
over long Internet links by increasing the system TCP tx and rx
window/buffer values. Note also the comments in
http://www.onlamp.com/pub/a/onlamp/2005/11/17/tcp_tuning.html?page=1
about software set buffer sizes.

For internal networks fully under your control, you can greatly increase
transfer rates and reduce CPU overheads by using "Jumbo packets" with an
MTU of 9000. (Most new switches should support that. Check further
before trying to go any larger.)

Other comments are in this example `/etc/sysctl.conf` (for Linux 2.6.xx):

```bash
# Run "sysctl -p" to effect any changes made here
#
# TCP tuning
# See:
# http://www.onlamp.com/pub/a/onlamp/2005/11/17/tcp_tuning.html?page=1
#
# optimal TCP buffer size for a given network link is double the value for delay times bandwidth:
# buffer size = 2 * delay * bandwidth
# For example, assume a 100Mbits/s link between California and the United Kingdom, an RTT of 150ms. The optimal TCP buffer size for this link is 1.9MBytes
#
# increase TCP maximum buffer size
# Example for 16 MBytes
#net.core.rmem_max = 16777216
#net.core.wmem_max = 16777216

# For a 10Mbits/s link and worst case is Australia at 350ms RTT, so 1MByte is more than enough
# Linux 2.6.17 (later?) defaults to 4194304 max, so match that instead...
net.core.rmem_max = 4194304
net.core.wmem_max = 4194304

# increase Linux autotuning TCP buffer limits
# min, default, and maximum number of bytes to use
# Example for 16 MBytes
#net.ipv4.tcp_rmem = 4096 87380 16777216
#net.ipv4.tcp_wmem = 4096 65536 16777216

# Scaled for 4MByte:
net.ipv4.tcp_rmem = 4096 87380 4194304
net.ipv4.tcp_wmem = 4096 49152 4194304

# Notes:
#
# Defaults:
# net.ipv4.tcp_rmem = 4096        87380   174760
# net.ipv4.tcp_wmem = 4096        16384   131072
# net.ipv4.tcp_mem = 49152        65536   98304
#
# Do not adjust tcp_mem unless you know exactly what you are doing.
# This array (in units of pages) determines how the system balances the
# total network buffer space against all other LOWMEM memory usage. The
# three elements are initialized at boot time to appropriate fractions
# of the available system memory and do not need to be changed.
#
# You do not need to adjust rmem_default or wmem_default (at least not
# for TCP tuning). These are the default buffer sizes for non-TCP sockets
# (e.g. unix domain and UDP sockets).
#
#
# Also use for example:
# /sbin/ifconfig eth2 txqueuelen 2000
#
# The default of 1000 is inadequate for long distance, high throughput pipes.
# For example, a rtt of 120ms at Gig rates, a txqueuelen of at least 10000 is recommended.
#
# txqueuelen should not be set too large for slow links to avoid excessive latency,
#
# If you are seeing "TCP: drop open request" for real load (not a DDoS),
# you need to increase tcp_max_syn_backlog (8192 worked much better than
# 1024 on heavy webserver load).
#
# If you see stuff like "swapper: page allocation failure. order:0, mode:0x20"
# you definitely need to increase min_free_kbytes for the virtual memory.
#
#
# All tcp settings listed by
# sysctl -a | fgrep tcp
#
# Run "sysctl -p" to effect any changes made here
```
