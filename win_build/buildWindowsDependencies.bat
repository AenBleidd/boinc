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
    curl -L https://www.openssl.org/source/old/0.9.x/openssl-0.9.8e.tar.gz --output %dependencies_root%/openssl.tar.gz
)

if exist %dependencies_root%/openssl.tar.gz (
    tar xzvf %dependencies_root%/openssl.tar.gz -C %dependencies_root%
    mv %dependencies_root%/openssl-0.9.8e %dependencies_root%/openssl
)
