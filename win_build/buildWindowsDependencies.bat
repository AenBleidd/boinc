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

REM wxWidgets

REM if not exist %dependencies_root%/wxWidgets.7z (
REM     curl -L https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.2/wxWidgets-3.0.2.7z --output %dependencies_root%/wxWidgets.7z
REM )

REM if exist %dependencies_root%/wxWidgets.7z (
REM     7z x %dependencies_root%/wxWidgets.7z -o%dependencies_root%/wxWidgets -aoa
REM )

REM copy "patches\wxWidgets.patch" "%dependencies_root%"
REM cd %dependencies_root%/wxWidgets
REM git --work-tree=. --git-dir=.git apply ../wxWidgets.patch


REM msbuild build/msw/wx_vc10.sln /p:Configuration=%configuration% /p:Platform=%platform%

REM if not exist mswin/%platform%/%configuration%/lib (
REM     mkdir mswin\%platform%\%configuration%\lib
REM )

REM move lib/vc_lib mswin/%platform%/%configuration%/lib/
REM del /q *
REM move docs\licence.txt ./
REM move docs\readme.txt ./
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

REM if not exist %dependencies_root%/openssl.zip (
REM     curl -L https://github.com/openssl/openssl/archive/OpenSSL_1_0_2a.zip --output %dependencies_root%/openssl.zip
REM )

REM if exist %dependencies_root%/openssl.zip (
REM     7z x %dependencies_root%/openssl.zip -o%dependencies_root%/ -aoa
REM     move %dependencies_root%/openssl-OpenSSL_1_0_2a %dependencies_root%/openssl
REM )

REM if %platform%==Win32 (
REM     copy "patches\OpenSSL_debug.patch" "%dependencies_root%"
REM     if %configuration%==Debug (
REM         copy "patches\OpenSSL_nmake_debug.patch" "%dependencies_root%"
REM     )
REM     if %configuration%==Release (
REM         copy "patches\OpenSSL_nmake_release.patch" "%dependencies_root%"
REM     )

REM     cd %dependencies_root%/openssl

REM     if %configuration%==Debug (
REM         git --work-tree=. --git-dir=.git apply ../OpenSSL_debug.patch
REM     )

REM     perl Configure VC-WIN32
REM     call ms/do_nasm

REM     https://devblogs.microsoft.com/cppblog/windows-xp-targeting-with-c-in-visual-studio-2012/
REM     if %configuration%==Debug (
REM         git --work-tree=. --git-dir=.git apply ../OpenSSL_nmake_debug.patch
REM     )

REM     if %configuration%==Release (
REM         git --work-tree=. --git-dir=.git apply ../OpenSSL_nmake_release.patch
REM     )

REM     nmake -f ms/ntdll.mak

REM     move out32dll.dbg out32dll
REM     rmdir /s /q tmp32dll.dbg

REM     cd %win_build_path%
REM )

REM cd %dependencies_root%/openssl
REM mkdir include\openssl
REM copy "crypto\aes\aes.h" "include\openssl\"
REM copy "crypto\asn1\asn1.h" "include\openssl\"
REM copy "crypto\asn1\asn1t.h" "include\openssl\"
REM copy "crypto\asn1\asn1_mac.h" "include\openssl\"
REM copy "crypto\bf\blowfish.h" "include\openssl\"
REM copy "crypto\bio\bio.h" "include\openssl\"
REM copy "crypto\bn\bn.h" "include\openssl\"
REM copy "crypto\buffer\buffer.h" "include\openssl\"
REM copy "crypto\camellia\camellia.h" "include\openssl\"
REM copy "crypto\cast\cast.h" "include\openssl\"
REM copy "crypto\cmac\cmac.h" "include\openssl\"
REM copy "crypto\cms\cms.h" "include\openssl\"
REM copy "crypto\comp\comp.h" "include\openssl\"
REM copy "crypto\conf\conf.h" "include\openssl\"
REM copy "crypto\conf\conf_api.h" "include\openssl\"
REM copy "crypto\crypto.h" "include\openssl\"
REM copy "crypto\des\des.h" "include\openssl\"
REM copy "crypto\des\des_old.h" "include\openssl\"
REM copy "crypto\dh\dh.h" "include\openssl\"
REM copy "crypto\dsa\dsa.h" "include\openssl\"
REM copy "crypto\dso\dso.h" "include\openssl\"
REM copy "crypto\ebcdic.h" "include\openssl\"
REM copy "crypto\ec\ec.h" "include\openssl\"
REM copy "crypto\ecdh\ecdh.h" "include\openssl\"
REM copy "crypto\ecdsa\ecdsa.h" "include\openssl\"
REM copy "crypto\engine\engine.h" "include\openssl\"
REM copy "crypto\err\err.h" "include\openssl\"
REM copy "crypto\evp\evp.h" "include\openssl\"
REM copy "crypto\hmac\hmac.h" "include\openssl\"
REM copy "crypto\idea\idea.h" "include\openssl\"
REM copy "crypto\krb5\krb5_asn.h" "include\openssl\"
REM copy "crypto\lhash\lhash.h" "include\openssl\"
REM copy "crypto\md4\md4.h" "include\openssl\"
REM copy "crypto\md5\md5.h" "include\openssl\"
REM copy "crypto\mdc2\mdc2.h" "include\openssl\"
REM copy "crypto\modes\modes.h" "include\openssl\"
REM copy "crypto\objects\objects.h" "include\openssl\"
REM copy "crypto\objects\obj_mac.h" "include\openssl\"
REM copy "crypto\ocsp\ocsp.h" "include\openssl\"
REM copy "crypto\opensslconf.h" "include\openssl\"
REM copy "crypto\opensslv.h" "include\openssl\"
REM copy "crypto\ossl_typ.h" "include\openssl\"
REM copy "crypto\pem\pem.h" "include\openssl\"
REM copy "crypto\pem\pem2.h" "include\openssl\"
REM copy "crypto\pkcs12\pkcs12.h" "include\openssl\"
REM copy "crypto\pkcs7\pkcs7.h" "include\openssl\"
REM copy "crypto\pqueue\pqueue.h" "include\openssl\"
REM copy "crypto\rand\rand.h" "include\openssl\"
REM copy "crypto\rc2\rc2.h" "include\openssl\"
REM copy "crypto\rc4\rc4.h" "include\openssl\"
REM copy "crypto\ripemd\ripemd.h" "include\openssl\"
REM copy "crypto\rsa\rsa.h" "include\openssl\"
REM copy "crypto\seed\seed.h" "include\openssl\"
REM copy "crypto\sha\sha.h" "include\openssl\"
REM copy "crypto\srp\srp.h" "include\openssl\"
REM copy "crypto\stack\safestack.h" "include\openssl\"
REM copy "crypto\stack\stack.h" "include\openssl\"
REM copy "crypto\symhacks.h" "include\openssl\"
REM copy "crypto\ts\ts.h" "include\openssl\"
REM copy "crypto\txt_db\txt_db.h" "include\openssl\"
REM copy "crypto\ui\ui.h" "include\openssl\"
REM copy "crypto\ui\ui_compat.h" "include\openssl\"
REM copy "crypto\whrlpool\whrlpool.h" "include\openssl\"
REM copy "crypto\x509\x509.h" "include\openssl\"
REM copy "crypto\x509\x509_vfy.h" "include\openssl\"
REM copy "crypto\x509v3\x509v3.h" "include\openssl\"
REM copy "e_os2.h" "include\openssl\"
REM copy "ssl\dtls1.h" "include\openssl\"
REM copy "ssl\kssl.h" "include\openssl\"
REM copy "ssl\srtp.h" "include\openssl\"
REM copy "ssl\ssl.h" "include\openssl\"
REM copy "ssl\ssl2.h" "include\openssl\"
REM copy "ssl\ssl23.h" "include\openssl\"
REM copy "ssl\ssl3.h" "include\openssl\"
REM copy "ssl\tls1.h" "include\openssl\"

REM if not exist mswin/%platform%/%configuration%/lib (
REM     mkdir mswin\%platform%\%configuration%\lib
REM )

REM if not exist mswin/%platform%/%configuration%/bin (
REM     mkdir mswin\%platform%\%configuration%\bin
REM )

REM copy "out32dll\libeay32.dll" "mswin/%platform%/%configuration%/bin/"
REM copy "out32dll\libeay32.pdb" "mswin/%platform%/%configuration%/bin/"
REM copy "out32dll\ssleay32.dll" "mswin/%platform%/%configuration%/bin/"
REM copy "out32dll\ssleay32.pdb" "mswin/%platform%/%configuration%/bin/"

REM copy "out32dll\libeay32.exp" "mswin/%platform%/%configuration%/lib/"
REM copy "out32dll\libeay32.lib" "mswin/%platform%/%configuration%/lib/"
REM copy "out32dll\ssleay32.exp" "mswin/%platform%/%configuration%/lib/"
REM copy "out32dll\ssleay32.lib" "mswin/%platform%/%configuration%/lib/"
REM copy "ms\libeay32.def" "mswin/%platform%/%configuration%/lib/"
REM copy "ms\ssleay32.def" "mswin/%platform%/%configuration%/lib/"

REM copy "README" "mswin/"

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

REM move mswin\README ./

REM cd ../
REM del openssl.zip
REM del OpenSSL_debug.patch
REM del OpenSSL_nmake_debug.patch

REM cd %win_build_path%

REM curl

REM if not exist %dependencies_root%/curl.zip (
REM     curl -L https://github.com/curl/curl/archive/curl-7_42_1.zip --output %dependencies_root%/curl.zip
REM )

REM if exist %dependencies_root%/curl.zip (
REM     7z x %dependencies_root%/curl.zip -o%dependencies_root%/ -aoa
REM )

REM move %dependencies_root%\curl-curl-7_42_1 %dependencies_root%\curl

REM copy "patches\curl.patch" "%dependencies_root%"

REM cd %dependencies_root%/curl

REM cd projects
REM call generate.bat vc12

REM cd ../

REM git --work-tree=. --git-dir=.git apply ../curl.patch

REM if %configuration%==Debug (
REM     msbuild /p:Configuration="DLL Debug - DLL OpenSSL" /p:Platform=%platform% "projects/Windows/VC12/lib/libcurl.sln" /p:AdditionalIncludeDirectories=%CD%/../openssl/include/
REM )
REM if %configuration%==Release (
REM     msbuild /p:Configuration="DLL Release - DLL OpenSSL" /p:Platform=%platform% "projects/Windows/VC12/lib/libcurl.sln" /p:AdditionalIncludeDirectories=%CD%/../openssl/include/
REM )

REM if not exist mswin/%platform%/%configuration%/lib (
REM     mkdir mswin\%platform%\%configuration%\lib
REM )

REM if not exist mswin/%platform%/%configuration%/bin (
REM     mkdir mswin\%platform%\%configuration%\bin
REM )

REM if %platform%==Win32 (
REM     if %configuration%==Debug (
REM         move "build\Win32\VC12\DLL Debug - DLL OpenSSL\libcurld.dll" mswin\%platform%\%configuration%\bin\
REM         move "build\Win32\VC12\DLL Debug - DLL OpenSSL\libcurld.pdb" mswin\%platform%\%configuration%\bin\libcurld_imp.pdb
REM         move "build\Win32\VC12\DLL Debug - DLL OpenSSL\libcurld.exp" mswin\%platform%\%configuration%\lib\libcurld_imp.exp
REM         move "build\Win32\VC12\DLL Debug - DLL OpenSSL\libcurld.lib" mswin\%platform%\%configuration%\lib\libcurld_imp.lib
REM     )
REM     if %configuration%==Release (
REM         move "build\Win32\VC12\DLL Release - DLL OpenSSL\libcurl.dll" mswin\%platform%\%configuration%\bin\
REM         move "build\Win32\VC12\DLL Release - DLL OpenSSL\libcurl.pdb" mswin\%platform%\%configuration%\bin\libcurl.pdb
REM         move "build\Win32\VC12\DLL Release - DLL OpenSSL\libcurl.exp" mswin\%platform%\%configuration%\lib\libcurl_imp.exp
REM         move "build\Win32\VC12\DLL Release - DLL OpenSSL\libcurl.lib" mswin\%platform%\%configuration%\lib\libcurl_imp.lib
REM     )
REM )
REM if %platform%==Win64 (
REM     if %configuration%==Debug (
REM         move "build\Win64\VC12\DLL Debug - DLL OpenSSL\libcurld.exp" mswin\%platform%\%configuration%\lib\libcurld_imp.exp
REM         move "build\Win64\VC12\DLL Debug - DLL OpenSSL\libcurld.dll" mswin\%platform%\%configuration%\bin\
REM         move "build\Win64\VC12\DLL Debug - DLL OpenSSL\libcurld.pdb" mswin\%platform%\%configuration%\bin\libcurld_imp.pdb
REM         move "build\Win64\VC12\DLL Debug - DLL OpenSSL\libcurld.lib" mswin\%platform%\%configuration%\lib\libcurld_imp.lib
REM     )
REM     if %configuration%==Release (
REM         move "build\Win64\VC12\DLL Release - DLL OpenSSL\libcurl.dll" mswin\%platform%\%configuration%\bin\
REM         move "build\Win64\VC12\DLL Release - DLL OpenSSL\libcurl.pdb" mswin\%platform%\%configuration%\bin\libcurl.pdb
REM         move "build\Win64\VC12\DLL Release - DLL OpenSSL\libcurl.exp" mswin\%platform%\%configuration%\lib\libcurl_imp.exp
REM         move "build\Win64\VC12\DLL Release - DLL OpenSSL\libcurl.lib" mswin\%platform%\%configuration%\lib\libcurl_imp.lib
REM     )
REM )

REM move README mswin/

REM del /q *
REM rmdir /s /q build
REM rmdir /s /q CMake
REM rmdir /s /q docs
REM rmdir /s /q lib
REM rmdir /s /q m4
REM rmdir /s /q packages
REM rmdir /s /q perl
REM rmdir /s /q projects
REM rmdir /s /q src
REM rmdir /s /q tests
REM rmdir /s /q winbuild

REM move mswin\README ./

REM cd ../
REM del curl.patch
REM del curl.zip

REM cd %win_build_path%

REM zlib

REM if not exist %dependencies_root%/zlib.zip (
REM     curl -L https://github.com/madler/zlib/archive/v1.2.8.zip --output %dependencies_root%/zlib.zip
REM )

REM if exist %dependencies_root%/zlib.zip (
REM     7z x %dependencies_root%/zlib.zip -o%dependencies_root%/ -aoa
REM )

REM move %dependencies_root%/zlib-1.2.8 %dependencies_root%/zlib

REM copy "patches\zlib.patch" "%dependencies_root%"

REM cd %dependencies_root%/zlib

REM git --work-tree=. --git-dir=.git apply ../zlib.patch

REM msbuild contrib/vstudio/vc11/zlibvc.vcxproj /p:Configuration=%configuration% /p:Platform=%platform%

REM if not exist mswin/%platform%/%configuration%/lib (
REM     mkdir mswin\%platform%\%configuration%\lib
REM )

REM if not exist mswin/%platform%/%configuration%/bin (
REM     mkdir mswin\%platform%\%configuration%\bin
REM )

REM move README mswin/

REM if not exist include (
REM     mkdir include
REM )

REM move zconf.h include\
REM move zlib.h include\

REM if %platform%==Win32 (
REM     if %configuration%==Debug (
REM         move contrib\vstudio\vc11\x86\ZlibDll%configuration%\zlibwapi.dll mswin\Win32\%configuration%\bin\zlib1d.dll
REM         move contrib\vstudio\vc11\x86\ZlibDll%configuration%\zlibwapi.pdb mswin\Win32\%configuration%\bin\zlib1d.pdb
REM         move contrib\vstudio\vc11\x86\ZlibDll%configuration%\zlibwapi.exp mswin\Win32\%configuration%\lib\zlib1d.exp
REM         move contrib\vstudio\vc11\x86\ZlibDll%configuration%\zlibwapi.lib mswin\Win32\%configuration%\lib\zlib1d.lib
REM         move contrib\vstudio\vc11\zlibvc.def mswin\Win32\%configuration%\lib\zlib.def
REM     )
REM     if %configuration%==Release (
REM         move contrib\vstudio\vc11\x86\ZlibDll%configuration%\zlibwapi.dll mswin\Win32\%configuration%\bin\zlib1.dll
REM         move contrib\vstudio\vc11\x86\ZlibDll%configuration%\zlibwapi.pdb mswin\Win32\%configuration%\bin\zlib1.pdb
REM         move contrib\vstudio\vc11\x86\ZlibDll%configuration%\zlibwapi.exp mswin\Win32\%configuration%\lib\zlib1.exp
REM         move contrib\vstudio\vc11\x86\ZlibDll%configuration%\zlibwapi.lib mswin\Win32\%configuration%\lib\zlib1.lib
REM         move contrib\vstudio\vc11\zlibvc.def mswin\Win32\%configuration%\lib\zlib.def
REM     )
REM )

REM if %platform%==x64 (
REM     if %configuration%==Debug (
REM         move contrib\vstudio\vc11\x64\ZlibDll%configuration%\zlibwapi.dll mswin\x64\%configuration%\bin\zlib1d.dll
REM         move contrib\vstudio\vc11\x64\ZlibDll%configuration%\zlibwapi.pdb mswin\x64\%configuration%\bin\zlib1d.pdb
REM         move contrib\vstudio\vc11\x64\ZlibDll%configuration%\zlibwapi.exp mswin\x64\%configuration%\lib\zlib1d.exp
REM         move contrib\vstudio\vc11\x64\ZlibDll%configuration%\zlibwapi.lib mswin\x64\%configuration%\lib\zlib1d.lib
REM         move contrib\vstudio\vc11\zlibvc.def mswin\Win32\%configuration%\lib\zlib.def
REM     )
REM     if %configuration%==Release (
REM         move contrib\vstudio\vc11\x64\ZlibDll%configuration%\zlibwapi.dll mswin\x64\%configuration%\bin\zlib1.dll
REM         move contrib\vstudio\vc11\x64\ZlibDll%configuration%\zlibwapi.pdb mswin\x64\%configuration%\bin\zlib1.pdb
REM         move contrib\vstudio\vc11\x64\ZlibDll%configuration%\zlibwapi.exp mswin\x64\%configuration%\lib\zlib1.exp
REM         move contrib\vstudio\vc11\x64\ZlibDll%configuration%\zlibwapi.lib mswin\x64\%configuration%\lib\zlib1.lib
REM         move contrib\vstudio\vc11\zlibvc.def mswin\Win32\%configuration%\lib\zlib.def
REM     )
REM )

REM del /q *
REM rmdir /s /q amiga
REM rmdir /s /q as400
REM rmdir /s /q contrib
REM rmdir /s /q doc
REM rmdir /s /q examples
REM rmdir /s /q msdos
REM rmdir /s /q nintendods
REM rmdir /s /q old
REM rmdir /s /q qnx
REM rmdir /s /q test
REM rmdir /s /q watcom
REM rmdir /s /q win32

REM move mswin\README README.txt

REM cd ../
REM del zlib.patch
REM del zlib.zip

REM cd %win_build_path%

REM FreeType

REM if not exist %dependencies_root%/freetype.zip (
REM     curl -L http://download.savannah.gnu.org/releases/freetype/ft2410.zip --output %dependencies_root%/freetype.zip
REM )

REM if exist %dependencies_root%/freetype.zip (
REM     7z x %dependencies_root%/freetype.zip -o%dependencies_root%/ -aoa
REM )

REM move %dependencies_root%/freetype-2.4.10 %dependencies_root%/freetype

REM copy "patches\freetype.patch" "%dependencies_root%"

REM cd %dependencies_root%/freetype

REM git --work-tree=. --git-dir=.git apply ../freetype.patch

REM msbuild builds/win32/vc2010/freetype.sln /p:Configuration=%configuration% /p:Platform=%platform%

REM if not exist mswin/%platform%/%configuration%/lib (
REM     mkdir mswin\%platform%\%configuration%\lib
REM )

REM move objs\win32\vc2010\* mswin\%platform%\%configuration%\lib\
REM move objs\%configuration%\vc120.pdb mswin\%platform%\%configuration%\lib\

REM move README mswin

REM del /q *
REM rmdir /s /q builds
REM rmdir /s /q devel
REM rmdir /s /q docs
REM rmdir /s /q objs
REM rmdir /s /q src

REM move mswin\README ./

REM cd ../
REM del freetype.patch
REM del freetype.zip

REM cd %win_build_path%

REM FTGL

if not exist %dependencies_root%/ftgl.tar.gz (
    curl -L0 https://sourceforge.net/projects/ftgl/files/latest/download --output %dependencies_root%/ftgl.tar.gz
)

if exist %dependencies_root%/ftgl.tar.gz (
    tar xzf %dependencies_root%/ftgl.tar.gz -C %dependencies_root%/
)

move %dependencies_root%/ftgl-2.1.3~rc5 %dependencies_root%/ftgl

copy "patches\ftgl_static.vcxproj" "%dependencies_root%\ftgl\msvc\vc8\"

cd %dependencies_root%/ftgl

msbuild msvc/vc8/ftgl_static.vcxproj /p:Configuration=%configuration% /p:Platform=%platform%

if not exist mswin/%platform%/%configuration%/lib (
    mkdir mswin\%platform%\%configuration%\lib
)

move msvc\build\* mswin\%platform%\%configuration%\lib
move msvc\vc8\%configuration%\vc120.pdb mswin\%platform%\%configuration%\lib

mkdir include\FTGL
move src\FTGL\*.* include\FTGL

move README mswin\README

del /q *
rmdir /s /q demo
rmdir /s /q docs
rmdir /s /q m4
rmdir /s /q msvc
rmdir /s /q src
rmdir /s /q test

move mswin\README ./

cd ../
del ftgl.tar.gz

cd %win_build_path%
