@echo off
REM Required tools:
REM Visual Studio 2013 with Windows XP (v120_xp)
REM 7-zip
REM curl
REM tar
REM perl
REM nasm

set dependencies_root_name=boinc_depends_win_vs2013
set dependencies_root_location=../../
set dependencies_root=%dependencies_root_location%%dependencies_root_name%
set "win_build_path=%cd%"

if not exist %dependencies_root% (
    cd %dependencies_root_location%
    mkdir %dependencies_root_name%
    cd %win_build_path%
)

set configuration=Debug
set platform=Win32

REM REM wxWidgets

REM if not exist %dependencies_root%/wxWidgets.7z (
REM     curl -L https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.0/wxWidgets-3.0.0.7z --output %dependencies_root%/wxWidgets.7z
REM )

REM if exist %dependencies_root%/wxWidgets.7z (
REM     7z x %dependencies_root%/wxWidgets.7z -o%dependencies_root%/wxWidgets -aoa
REM )

REM cp patches/wxWidgets.patch %dependencies_root%
REM cd %dependencies_root%/wxWidgets
REM git --work-tree=. --git-dir=.git apply ../wxWidgets.patch


REM msbuild build/msw/wx_vc10.sln /p:Configuration=%configuration% /p:Platform=%platform%

REM if not exist mswin/%platform%/%configuration%/lib (
REM     mkdir mswin\%platform%\%configuration%\lib
REM )

REM mv lib/vc_lib mswin/%platform%/%configuration%/lib/
REM del /q *
REM mv docs/licence.txt ./
REM mv docs/readme.txt ./
REM rmdir /s /q art
REM rmdir /s /q build
REM rmdir /s /q demos
REM rmdir /s /q distrib
REM rmdir /s /q docs
REM rmdir /s /q interface
REM rmdir /s /q lib
REM rmdir /s /q locale
REM rmdir /s /q misc
REM rmdir /s /q samples
REM rmdir /s /q src
REM rmdir /s /q tests
REM rmdir /s /q utils
REM cd ../
REM del wxWidgets.7z
REM del wxWidgets.patch

REM cd %win_build_path%

REM OpenSSL

REM if not exist %dependencies_root%/openssl.tar.gz (
REM     curl -L https://www.openssl.org/source/old/1.0.2/openssl-1.0.2a.tar.gz --output %dependencies_root%/openssl.tar.gz
REM )

REM if exist %dependencies_root%/openssl.tar.gz (
REM     tar xzvf %dependencies_root%/openssl.tar.gz -C %dependencies_root%
REM     mv %dependencies_root%/openssl-1.0.2a %dependencies_root%/openssl
REM )

REM if %platform%==Win32 (
REM     cp patches/OpenSSL_debug.patch %dependencies_root%
REM     if %configuration%==Debug (
REM         cp patches/OpenSSL_nmake_debug.patch %dependencies_root%
REM     )
REM     if %configuration%==Release (
REM         cp patches/OpenSSL_nmake_release.patch %dependencies_root%
REM     )

REM     cd %dependencies_root%/openssl

REM     if %configuration%==Debug (
REM         git --work-tree=. --git-dir=.git apply ../OpenSSL_debug.patch
REM     )

REM     perl Configure VC-WIN32
REM     call ms/do_nasm

REM     REM https://devblogs.microsoft.com/cppblog/windows-xp-targeting-with-c-in-visual-studio-2012/
REM     if %configuration%==Debug (
REM         git --work-tree=. --git-dir=.git apply ../OpenSSL_nmake_debug.patch
REM     )

REM     if %configuration%==Release (
REM         git --work-tree=. --git-dir=.git apply ../OpenSSL_nmake_release.patch
REM     )

REM     nmake -f ms/ntdll.mak

REM     mv out32dll.dbg out32dll
REM     rmdir /s /q tmp32dll.dbg

REM )

REM if not exist mswin/%platform%/%configuration%/lib (
REM     mkdir mswin\%platform%\%configuration%\lib
REM )

REM if not exist mswin/%platform%/%configuration%/bin (
REM     mkdir mswin\%platform%\%configuration%\bin
REM )

REM cp out32dll/libeay32.dll mswin/%platform%/%configuration%/bin/
REM cp out32dll/libeay32.pdb mswin/%platform%/%configuration%/bin/
REM cp out32dll/ssleay32.dll mswin/%platform%/%configuration%/bin/
REM cp out32dll/ssleay32.pdb mswin/%platform%/%configuration%/bin/

REM cp out32dll/libeay32.exp mswin/%platform%/%configuration%/lib/
REM cp out32dll/libeay32.lib mswin/%platform%/%configuration%/lib/
REM cp out32dll/ssleay32.exp mswin/%platform%/%configuration%/lib/
REM cp out32dll/ssleay32.lib mswin/%platform%/%configuration%/lib/
REM cp ms/libeay32.def mswin/%platform%/%configuration%/lib/
REM cp ms/ssleay32.def mswin/%platform%/%configuration%/lib/

REM cp README mswin/

REM rename \\.\%CD%\nul. deletefile.txt

REM del /q *
REM rmdir /s /q apps
REM rmdir /s /q bugs
REM rmdir /s /q certs
REM rmdir /s /q crypto
REM rmdir /s /q demos
REM rmdir /s /q doc
REM rmdir /s /q engines
REM rmdir /s /q inc32
REM rmdir /s /q MacOS
REM rmdir /s /q ms
REM rmdir /s /q Netware
REM rmdir /s /q os2
REM rmdir /s /q out32dll
REM rmdir /s /q perl
REM rmdir /s /q shlib
REM rmdir /s /q ssl
REM rmdir /s /q test
REM rmdir /s /q times
REM rmdir /s /q tools
REM rmdir /s /q util
REM rmdir /s /q VMS

REM mv mswin/README ./

REM cd ../
REM del openssl.tar.gz
REM del OpenSSL_debug.patch
REM del OpenSSL_nmake_debug.patch

REM cd %win_build_path%

REM curl

if not exist %dependencies_root%/curl.zip (
    curl -L https://github.com/curl/curl/archive/curl-7_42_1.zip --output %dependencies_root%/curl.zip
)

if exist %dependencies_root%/curl.zip (
    7z x %dependencies_root%/curl.zip -o%dependencies_root%/ -aoa
)

mv %dependencies_root%/curl-curl-7_42_1 %dependencies_root%/curl

cp patches/curl.patch %dependencies_root%

cd %dependencies_root%/curl

cd projects
call generate.bat vc12

cd ../

git --work-tree=. --git-dir=.git apply ../curl.patch

if %configuration%==Debug (
    msbuild /p:Configuration="DLL Debug - DLL OpenSSL" /p:Platform=%platform% "projects/Windows/VC12/lib/libcurl.sln" /p:AdditionalIncludeDirectories=%CD%/../openssl/include/
)
if %configuration%==Release (
    msbuild /p:Configuration="DLL Release - DLL OpenSSL" /p:Platform=%platform% "projects/Windows/VC12/lib/libcurl.sln" /p:AdditionalIncludeDirectories=%CD%/../openssl/include/
)

if not exist mswin/%platform%/%configuration%/lib (
    mkdir mswin\%platform%\%configuration%\lib
)

if not exist mswin/%platform%/%configuration%/bin (
    mkdir mswin\%platform%\%configuration%\bin
)

if %platform%==Win32 (
    if %configuration%==Debug (
        mv "build/Win32/VC12/DLL Debug - DLL OpenSSL/libcurld.dll" mswin/%platform%/%configuration%/bin/
        mv "build/Win32/VC12/DLL Debug - DLL OpenSSL/libcurld.pdb" mswin/%platform%/%configuration%/bin/libcurld_imp.pdb
        mv "build/Win32/VC12/DLL Debug - DLL OpenSSL/libcurld.exp" mswin/%platform%/%configuration%/lib/libcurld_imp.exp
        mv "build/Win32/VC12/DLL Debug - DLL OpenSSL/libcurld.lib" mswin/%platform%/%configuration%/lib/libcurld_imp.lib
    )
    if %configuration%==Release (
        mv "build/Win32/VC12/DLL Release - DLL OpenSSL/libcurl.dll" mswin/%platform%/%configuration%/bin/
        mv "build/Win32/VC12/DLL Release - DLL OpenSSL/libcurl.pdb" mswin/%platform%/%configuration%/bin/libcurl.pdb
        mv "build/Win32/VC12/DLL Release - DLL OpenSSL/libcurl.exp" mswin/%platform%/%configuration%/lib/libcurl_imp.exp
        mv "build/Win32/VC12/DLL Release - DLL OpenSSL/libcurl.lib" mswin/%platform%/%configuration%/lib/libcurl_imp.lib
    )
)
if %platform%==Win64 (
    if %configuration%==Debug (
        mv "build/Win64/VC12/DLL Debug - DLL OpenSSL/libcurld.exp" mswin/%platform%/%configuration%/lib/libcurld_imp.exp
        mv "build/Win64/VC12/DLL Debug - DLL OpenSSL/libcurld.dll" mswin/%platform%/%configuration%/bin/
        mv "build/Win64/VC12/DLL Debug - DLL OpenSSL/libcurld.pdb" mswin/%platform%/%configuration%/bin/libcurld_imp.pdb
        mv "build/Win64/VC12/DLL Debug - DLL OpenSSL/libcurld.lib" mswin/%platform%/%configuration%/lib/libcurld_imp.lib
    )
    if %configuration%==Release (
        mv "build/Win64/VC12/DLL Release - DLL OpenSSL/libcurl.dll" mswin/%platform%/%configuration%/bin/
        mv "build/Win64/VC12/DLL Release - DLL OpenSSL/libcurl.pdb" mswin/%platform%/%configuration%/bin/libcurl.pdb
        mv "build/Win64/VC12/DLL Release - DLL OpenSSL/libcurl.exp" mswin/%platform%/%configuration%/lib/libcurl_imp.exp
        mv "build/Win64/VC12/DLL Release - DLL OpenSSL/libcurl.lib" mswin/%platform%/%configuration%/lib/libcurl_imp.lib
    )
)

mv README mswin/

del /q *
rmdir /s /q build
rmdir /s /q CMake
rmdir /s /q docs
rmdir /s /q lib
rmdir /s /q m4
rmdir /s /q packages
rmdir /s /q perl
rmdir /s /q projects
rmdir /s /q src
rmdir /s /q tests
rmdir /s /q winbuild

mv mswin/README ./

cd ../
del curl.patch
del curl.zip

cd %win_build_path%