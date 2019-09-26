# What is a project?

A BOINC project consists of the following components:

 * A [MySQL database](DataBase.md)
 * A [directory structure](ServerDirs.md)
 * A [configuration file](ProjectConfigFile.md), which specifies [options](ProjectOptions.md),
   [daemons](ProjectDaemons.md), and [periodic tasks](ProjectTasks.md).

Multiple BOINC projects can exist on the same host.
This can be handy for creating separate projects for testing and debugging.

The easiest way to create a project is with the [make_project](MakeProject.md) script,
which creates all the above components.
