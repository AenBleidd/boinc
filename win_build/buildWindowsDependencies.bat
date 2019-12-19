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

if not exist %dependencies_root%/wxWidgets.7z (
    curl -L https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.0/wxWidgets-3.0.0.7z --output %dependencies_root%/wxWidgets.7z
)

if exist %dependencies_root%/wxWidgets.7z (
    7z x %dependencies_root%/wxWidgets.7z -o%dependencies_root%/wxWidgets -aoa
)

cp patches/wxWidgets.patch %dependencies_root%
cd %dependencies_root%/wxWidgets
git --work-tree=. --git-dir=.git apply ../wxWidgets.patch


msbuild build/msw/wx_vc10.sln /p:Configuration=%configuration% /p:Platform=%platform%

if not exist mswin/%platform%/%configuration%/lib (
    mkdir mswin\%platform%\%configuration%\lib
)

mv lib/vc_lib mswin/%platform%/%configuration%/lib/
del /q *
mv docs/licence.txt ./
mv docs/readme.txt ./
rmdir /s /q art
rmdir /s /q build
rmdir /s /q demos
rmdir /s /q distrib
rmdir /s /q docs
rmdir /s /q interface
rmdir /s /q lib
rmdir /s /q locale
rmdir /s /q misc
rmdir /s /q samples
rmdir /s /q src
rmdir /s /q tests
rmdir /s /q utils

cd %win_build_path%
