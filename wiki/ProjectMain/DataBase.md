# The BOINC database

BOINC stores information in a MySQL database. The main tables are:

| Table | Description |
| --- | --- |
| platform | Compilation targets of the core client and/or applications |
| app | Applications. The core client is treated as an application; its name is 'core_client' |
| app_version |	Versions of applications. Each record includes a URL for downloading the executable, and the MD5 checksum of the executable |
| user | Describes users, including their email address, name, web password, and authenticator |
| host | Describes hosts |
| workunit | Describes workunits. The input file descriptions are stored in an XML document in a blob field. Includes counts of the number of results linked to this workunit, and the numbers that have been sent, that have succeeded, and that have failed |
| result | Describes results. Includes a 'state' (whether the result has been dispatched). Stores a number of items relevant only after the result has been returned: CPU time, exit status, and validation status |

The database is created by the [make_project](MakeProject) script. Normally you don't have to directly examine or manipulate the database. If you need to, you can use the MySQL command-line interpreter or BOINC's [administrative web interface](HtmlOps).