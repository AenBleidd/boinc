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

if not exist %dependencies_root%/openssl.tar.gz (
    curl -L https://www.openssl.org/source/old/1.0.2/openssl-1.0.2a.tar.gz --output %dependencies_root%/openssl.tar.gz
)

if exist %dependencies_root%/openssl.tar.gz (
    tar xzvf %dependencies_root%/openssl.tar.gz -C %dependencies_root%
    mv %dependencies_root%/openssl-1.0.2a %dependencies_root%/openssl
)

if %platform%==Win32 (
    cp patches/OpenSSL_debug.patch %dependencies_root%
    if %configuration%==Debug (
        cp patches/OpenSSL_nmake_debug.patch %dependencies_root%
    )
    if %configuration%==Release (
        cp patches/OpenSSL_nmake_release.patch %dependencies_root%
    )

    cd %dependencies_root%/openssl

    if %configuration%==Debug (
        git --work-tree=. --git-dir=.git apply ../OpenSSL_debug.patch
    )

    perl Configure VC-WIN32
    call ms/do_nasm

    REM https://devblogs.microsoft.com/cppblog/windows-xp-targeting-with-c-in-visual-studio-2012/
    if %configuration%==Debug (
        git --work-tree=. --git-dir=.git apply ../OpenSSL_nmake_debug.patch
    )

    if %configuration%==Release (
        git --work-tree=. --git-dir=.git apply ../OpenSSL_nmake_release.patch
    )

    nmake -f ms/ntdll.mak

    mv out32dll.dbg out32dll
    rmdir /s /q tmp32dll.dbg

)

if not exist mswin/%platform%/%configuration%/lib (
    mkdir mswin\%platform%\%configuration%\lib
)

if not exist mswin/%platform%/%configuration%/bin (
    mkdir mswin\%platform%\%configuration%\bin
)

cp out32dll/libeay32.dll mswin/%platform%/%configuration%/bin/
cp out32dll/libeay32.pdb mswin/%platform%/%configuration%/bin/
cp out32dll/ssleay32.dll mswin/%platform%/%configuration%/bin/
cp out32dll/ssleay32.pdb mswin/%platform%/%configuration%/bin/

cp out32dll/libeay32.exp mswin/%platform%/%configuration%/lib/
cp out32dll/libeay32.lib mswin/%platform%/%configuration%/lib/
cp out32dll/ssleay32.exp mswin/%platform%/%configuration%/lib/
cp out32dll/ssleay32.lib mswin/%platform%/%configuration%/lib/
cp ms/libeay32.def mswin/%platform%/%configuration%/lib/
cp ms/ssleay32.def mswin/%platform%/%configuration%/lib/

cp README mswin/

rename \\.\%CD%\nul. deletefile.txt

del /q *
rmdir /s /q apps
rmdir /s /q bugs
rmdir /s /q certs
rmdir /s /q crypto
rmdir /s /q demos
rmdir /s /q doc
rmdir /s /q engines
rmdir /s /q inc32
rmdir /s /q MacOS
rmdir /s /q ms
rmdir /s /q Netware
rmdir /s /q os2
rmdir /s /q out32dll
rmdir /s /q perl
rmdir /s /q shlib
rmdir /s /q ssl
rmdir /s /q test
rmdir /s /q times
rmdir /s /q tools
rmdir /s /q util
rmdir /s /q VMS

mv mswin/README ./

cd ../
del openssl.tar.gz
del OpenSSL_debug.patch
del OpenSSL_nmake_debug.patch

cd %win_build_path%
