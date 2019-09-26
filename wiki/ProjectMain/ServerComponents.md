# What is a project?

A BOINC project consists of the following components:

 * A [MySQL database](DataBase)
 * A [directory structure](ServerDirs)
 * A [configuration file](ProjectConfigFile), which specifies [options](ProjectOptions),
   [daemons](ProjectDaemons), and [periodic tasks](ProjectTasks).

Multiple BOINC projects can exist on the same host.
This can be handy for creating separate projects for testing and debugging.

The easiest way to create a project is with the [make_project](MakeProject) script,
which creates all the above components.
