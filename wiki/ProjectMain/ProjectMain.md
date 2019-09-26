# Technical documentation

These documents describe how to create and operate a BOINC project.
Don't be scared by the amount of information;
most of it is for advanced features that you probably won't need.

## Quick start

* [Create a BOINC project in 1 hour or less](https://github.com/marius311/boinc-server-docker/blob/master/docs/cookbook.md)

## BOINC concepts and features

* Computing model
  * [Basic concepts](BasicConcepts.md)
  * [Platforms](BoincPlatforms.md)
  * [Applications and versions](AppVersion.md)
  * [Jobs](JobIn.md)
  * [Jobs and data](DataFlow.md)
  * [Redundancy and errors](JobReplication.md)
  * [Work distribution](WorkDistribution.md)
  * [Locality scheduling](LocalityScheduling.md)
  * [Trickle messages](TrickleMessages.md)
* Data management
  * [Files and file references](BoincFiles.md)
  * [File compression](FileCompression.md)
  * [Explicit client file management](PhysicalFileManagement.md)

## Developing BOINC applications

* [Overview](AppIntro.md)
  * [The BOINC wrapper](WrapperApp.md)
  * [Apps that run in VirtualBox virtual machines](VboxApps.md)
  * [Apps that run in Docker containers](BoincDocker.md)
  * [Example applications](ExampleApps.md)
* Basic APIs
  * [API for native apps](BasicApi.md)
  * [Cross-platform utility functions](AppDev.md)
* Special types of applications
  * [Multicore applications](AppMultiThread.md)
    * [OpenCL CPU applications](OpenclCpu.md)
  * [Applications that use GPUs](AppCoprocessor.md)
    * [CUDA applications](CudaApps.md)
    * [OpenCL applications](OpenclApps.md)
  * [Non-CPU-intensive applications](NonCpuIntensive.md)
  * [MPI applications](MpiApps.md)
* Specialized APIs
  * [Startup and status data](StatusApi.md)
  * [Diagnostics](DiagnosticsApi.md)
  * [Trickle messages](TrickleApi.md)
  * [Intermediate upload](IntermediateUpload.md)
  * [Apps that do network communication](NetworkApps.md)
  * [API for wrappers](OptionsApi.md)
* Adding graphics
  * [Adding graphics to the manager's simple view](ProjectSkin.md)
  * [Graphics apps](GraphicsApps.md)
  * [Using OpenGL](GraphicsApi.md)
  * [Using HTML](GraphicsHtml.md)
* Customized scheduling
  * [Plan classes](AppPlan.md)
    * [Specifying plan classes in XML](AppPlanSpec.md)
    * [Specifying plan classes in C++](PlanClassFunc.md)
  * [Job-level scheduler customization](JobSched.md)
* Languages other than C/C++
  * [FORTRAN](FortranApps.md)
  * [Java](JavaApps.md)
  * [Python](PythonApps.md)
  * [PyMW: Python master/worker system](PyMw.md)
* [Dynamic library naming issues](AppLibraries.md)
* [Building applications](CompileApp.md)
  * [Windows](CompileAppWin.md)
  * [Mac OS X](BuildMacApp.md)
  * [Linux](CompileAppLinux.md)
  * [Android](CompileAppLinux.md)
  * [CUDA and OpenCL](GPUApp.md)
* [Debugging applications](AppDebug.md)
  * [Windows](AppDebugWin.md)
  * [Android](AppDebugAndroid.md)
* [Testing applications](BetaTest.md)

## Creating a BOINC project

* [What is a project?](ServerComponents.md)
  * [The project URL](MasterUrl.md)
  * [Directory structure](ServerDirs.md)
* [Setting up a BOINC server](ServerIntro.md)
  * [The make_project script](MakeProject.md)
* [The project configuration file](ProjectConfigFile.md)
  * [Project options](ProjectOptions.md)
  * [Daemons](ProjectDaemons.md)
  * [Periodic tasks](ProjectTasks.md)
* [Adding applications/platforms](XaddTool.md)
* [Adding application versions](AppVersionNew.md)
* [Administrative web interface](HtmlOps.md)
* [Project control](StartTool.md)
* [Security issues](SecurityIssues.md)
  * [Server security](ProjectSecurity.md)
  * [Encryption utility program](KeySetup.md)
  * [Code signing](CodeSigning.md)
* [Launching your project](ProjectLaunch.md)
* [Using Secure Socket Layer (SSL)](SecureHttp.md)
* Internals
  * [The BOINC database](DataBase.md)
  * [Other job-processing daemons](BackendPrograms.md)
  * [Server-side file deletion](FileDeleter.md)
  * [Database purging utility](DbPurge.md)

## Submitting and handling jobs

* [Introduction](JobIntro.md)
* [Input and output templates](JobTemplates.md)
* Local job submission
  * [Staging input files](JobStage.md)
  * [Submitting jobs locally](JobSubmission.md)
  * [Work generators](WorkGeneration.md)
* [Local web-based job submission](WebSubmit.md)
  * [Per-user file sandbox](FileSandbox.md)
  * [Example: LAMMPS](LammpsRemote.md)
* [Remote job submission](RemoteOverview.md)
  * [Job-based input file management](RemoteInputFiles.md)
  * [Remote access to output files](RemoteOutputFiles.md)
  * [Job submission, monitoring, and control](RemoteJobs.md)
  * [Logging of remote job submission](RemoteLogs.md)
* [Job keywords](JobKeywords.md)
* Managing multiple job submitters
  * [Access control and quotas](MultiUser.md)
  * [Prioritizing jobs](MultiUserPriority.md)
* [Validation](ValidationSummary.md)
  * [Standard validators](ValidationIntro.md)
  * [Custom validators](ValidationSimple.md)
  * [Homogeneous redundancy](HomogeneousRedundancy.md)
  * [Homogeneous App Version](HomogeneousAppVersion.md)
  * [Adaptive replication](AdaptiveReplication.md)
* [Handling completed jobs](AssimilateIntro.md)
* [Canceling jobs](CancelJobs.md)
* [APIs for job-processing programs](BackendUtilities.md)
* [Broadcast and targeted jobs](AssignedWork.md)
* [The status of completed jobs](JobStatus.md)
* [Single job submission](SingleJob.md)
* [Multi-size applications](MultiSize.md)
* [Condor/BOINC integration](CondorBoinc.md)
* [Pinning jobs to app version numbers](JobPinning.md)
* [Assigning credit to jobs](CreditOptions.md)

## Maintaining a BOINC project

* [Trouble-shooting server components](ServerDebug.md)
* [Upgrading a project's server software](ToolUpgrade.md)
  * [Server software change log](ServerUpdates.md)
* [Increasing server capacity](MultiHost.md)
* [Log rotation](LogRotate.md)
* [Watchdogs](WatchDog.md)
* [Stripcharts](StripChart.md)

## Project web site

* [Customize web site content](WebConfig.md)
* [Customize web site appearance with CSS](StyleSheets.md)
* [Project-specific preferences](ProjectSpecificPrefs.md)
* [Dealing with spam](ProtectionFromSpam.md)
* [Creating and managing message boards](WebForum.md)
* [Project news](ProjectNews.md)
* [Web site translation](TranslateProject.md)
* [Badges](BadgeDoc.md)
* [Server status page](ServerStatus.md)
* [Profile screening](ProfileScreen.md)
* [Proof of account ownership: Lets users proof they are the account owner to external sites](ProofOfOwnership.md)
* [Caching](WebCache.md)
* [Adding a wiki](MediaWiki.md)
* [Integration with WordPress](WordPressInt.md)
* [Integration with Drupal](DrupalIntegration.md)

## Communicating with volunteers

* [Recruiting and retaining volunteers](VolunteerRecruit.md)
* [GUI URLs](GuiUrls.md)
* [Notices](ProjectNotices.md)
* [Requiring that volunteers accept Terms of Use](TermsOfUse.md)

## Miscellaneous

* [Accepting donations through PayPal](PayPalDonations.md)
* [Blacklisting hosts](BlackList.md)
* [Campus-level BOINC projects](VirtualCampusSupercomputerCenter.md)
* [Code signing using X509 certificates](CertSig.md)
* [Combining BOINC with Grids and clusters](GridIntegration.md)
* [Configuring MySQL for BOINC](MysqlConfig.md)
* [Controlling account creation](AccountControl.md)
* [Export credit data as XML](DbDump.md)
* [Importing BOINC-wide teams](TeamImport.md)
* [Including opaque data in scheduler request messages](ClientOpaque.md)
* [LDAP authentication](LdapSupport.md)
* [Per-app credit](PerAppCredit.md)
* [User app selection](AppFiltering.md)
* [Volunteer storage](VolunteerStorage.md)
* [Volunteer data archival](VolunteerDataArchival.md)
* [What to do when you run out of database IDs](DbIds.md)
* [How to be compliant with GDPR](GdprCompliance.md)
* [Simplified registration/download](SimpleAttach.md)

## Unsupported software
* [RBoinc remote job submission](RemoteJob.md)
