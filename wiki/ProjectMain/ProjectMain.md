# Technical documentation

These documents describe how to create and operate a BOINC project.
Don't be scared by the amount of information;
most of it is for advanced features that you probably won't need.

## Quick start

* [Create a BOINC project in 1 hour or less](https://github.com/marius311/boinc-server-docker/blob/master/docs/cookbook.md)

## BOINC concepts and features

* Computing model
  * [Basic concepts](BasicConcepts)
  * [Platforms](BoincPlatforms)
  * [Applications and versions](AppVersion)
  * [Jobs](JobIn)
  * [Jobs and data](DataFlow)
  * [Redundancy and errors](JobReplication)
  * [Work distribution](WorkDistribution)
  * [Locality scheduling](LocalityScheduling)
  * [Trickle messages](TrickleMessages)
* Data management
  * [Files and file references](BoincFiles)
  * [File compression](FileCompression)
  * [Explicit client file management](PhysicalFileManagement)

## Developing BOINC applications

* [Overview](AppIntro)
  * [The BOINC wrapper](WrapperApp)
  * [Apps that run in VirtualBox virtual machines](VboxApps)
  * [Apps that run in Docker containers](BoincDocker)
  * [Example applications](ExampleApps)
* Basic APIs
  * [API for native apps](BasicApi)
  * [Cross-platform utility functions](AppDev)
* Special types of applications
  * [Multicore applications](AppMultiThread)
    * [OpenCL CPU applications](OpenclCpu)
  * [Applications that use GPUs](AppCoprocessor)
    * [CUDA applications](CudaApps)
    * [OpenCL applications](OpenclApps)
  * [Non-CPU-intensive applications](NonCpuIntensive)
  * [MPI applications](MpiApps)
* Specialized APIs
  * [Startup and status data](StatusApi)
  * [Diagnostics](DiagnosticsApi)
  * [Trickle messages](TrickleApi)
  * [Intermediate upload](IntermediateUpload)
  * [Apps that do network communication](NetworkApps)
  * [API for wrappers](OptionsApi)
* Adding graphics
  * [Adding graphics to the manager's simple view](ProjectSkin)
  * [Graphics apps](GraphicsApps)
  * [Using OpenGL](GraphicsApi)
  * [Using HTML](GraphicsHtml)
* Customized scheduling
  * [Plan classes](AppPlan)
    * [Specifying plan classes in XML](AppPlanSpec)
    * [Specifying plan classes in C++](PlanClassFunc)
  * [Job-level scheduler customization](JobSched)
* Languages other than C/C++
  * [FORTRAN](FortranApps)
  * [Java](JavaApps)
  * [Python](PythonApps)
  * [PyMW: Python master/worker system](PyMw)
* [Dynamic library naming issues](AppLibraries)
* [Building applications](CompileApp)
  * [Windows](CompileAppWin)
  * [Mac OS X](BuildMacApp)
  * [Linux](CompileAppLinux)
  * [Android](CompileAppLinux)
  * [CUDA and OpenCL](GPUApp)
* [Debugging applications](AppDebug)
  * [Windows](AppDebugWin)
  * [Android](AppDebugAndroid)
* [Testing applications](BetaTest)

## Creating a BOINC project

* [What is a project?](ServerComponents)
  * [The project URL](MasterUrl)
  * [Directory structure](ServerDirs)
* [Setting up a BOINC server](ServerIntro)
  * [The make_project script](MakeProject)
* [The project configuration file](ProjectConfigFile)
  * [Project options](ProjectOptions)
  * [Daemons](ProjectDaemons)
  * [Periodic tasks](ProjectTasks)
* [Adding applications/platforms](XaddTool)
* [Adding application versions](AppVersionNew)
* [Administrative web interface](HtmlOps)
* [Project control](StartTool)
* [Security issues](SecurityIssues)
  * [Server security](ProjectSecurity)
  * [Encryption utility program](KeySetup)
  * [Code signing](CodeSigning)
* [Launching your project](ProjectLaunch)
* [Using Secure Socket Layer (SSL)](SecureHttp)
* Internals
  * [The BOINC database](DataBase)
  * [Other job-processing daemons](BackendPrograms)
  * [Server-side file deletion](FileDeleter)
  * [Database purging utility](DbPurge)

## Submitting and handling jobs

* [Introduction](JobIntro)
* [Input and output templates](JobTemplates)
* Local job submission
  * [Staging input files](JobStage)
  * [Submitting jobs locally](JobSubmission)
  * [Work generators](WorkGeneration)
* [Local web-based job submission](WebSubmit)
  * [Per-user file sandbox](FileSandbox)
  * [Example: LAMMPS](LammpsRemote)
* [Remote job submission](RemoteOverview)
  * [Job-based input file management](RemoteInputFiles)
  * [Remote access to output files](RemoteOutputFiles)
  * [Job submission, monitoring, and control](RemoteJobs)
  * [Logging of remote job submission](RemoteLogs)
* [Job keywords](JobKeywords)
* Managing multiple job submitters
  * [Access control and quotas](MultiUser)
  * [Prioritizing jobs](MultiUserPriority)
* [Validation](ValidationSummary)
  * [Standard validators](ValidationIntro)
  * [Custom validators](ValidationSimple)
  * [Homogeneous redundancy](HomogeneousRedundancy)
  * [Homogeneous App Version](HomogeneousAppVersion)
  * [Adaptive replication](AdaptiveReplication)
* [Handling completed jobs](AssimilateIntro)
* [Canceling jobs](CancelJobs)
* [APIs for job-processing programs](BackendUtilities)
* [Broadcast and targeted jobs](AssignedWork)
* [The status of completed jobs](JobStatus)
* [Single job submission](SingleJob)
* [Multi-size applications](MultiSize)
* [Condor/BOINC integration](CondorBoinc)
* [Pinning jobs to app version numbers](JobPinning)
* [Assigning credit to jobs](CreditOptions)

## Maintaining a BOINC project

* [Trouble-shooting server components](ServerDebug)
* [Upgrading a project's server software](ToolUpgrade)
  * [Server software change log](ServerUpdates)
* [Increasing server capacity](MultiHost)
* [Log rotation](LogRotate)
* [Watchdogs](WatchDog)
* [Stripcharts](StripChart)

## Project web site

* [Customize web site content](WebConfig)
* [Customize web site appearance with CSS](StyleSheets)
* [Project-specific preferences](ProjectSpecificPrefs)
* [Dealing with spam](ProtectionFromSpam)
* [Creating and managing message boards](WebForum)
* [Project news](ProjectNews)
* [Web site translation](TranslateProject)
* [Badges](BadgeDoc)
* [Server status page](ServerStatus)
* [Profile screening](ProfileScreen)
* [Proof of account ownership: Lets users proof they are the account owner to external sites](ProofOfOwnership)
* [Caching](WebCache)
* [Adding a wiki](MediaWiki)
* [Integration with WordPress](WordPressInt)
* [Integration with Drupal](DrupalIntegration)

## Communicating with volunteers

* [Recruiting and retaining volunteers](VolunteerRecruit)
* [GUI URLs](GuiUrls)
* [Notices](ProjectNotices)
* [Requiring that volunteers accept Terms of Use](TermsOfUse)

## Miscellaneous

* [Accepting donations through PayPal](PayPalDonations)
* [Blacklisting hosts](BlackList)
* [Campus-level BOINC projects](VirtualCampusSupercomputerCenter)
* [Code signing using X509 certificates](CertSig)
* [Combining BOINC with Grids and clusters](GridIntegration)
* [Configuring MySQL for BOINC](MysqlConfig)
* [Controlling account creation](AccountControl)
* [Export credit data as XML](DbDump)
* [Importing BOINC-wide teams](TeamImport)
* [Including opaque data in scheduler request messages](ClientOpaque)
* [LDAP authentication](LdapSupport)
* [Per-app credit](PerAppCredit)
* [User app selection](AppFiltering)
* [Volunteer storage](VolunteerStorage)
* [Volunteer data archival](VolunteerDataArchival)
* [What to do when you run out of database IDs](DbIds)
* [How to be compliant with GDPR](GdprCompliance)
* [Simplified registration/download](SimpleAttach)

## Unsupported software
* [RBoinc remote job submission](RemoteJob)
