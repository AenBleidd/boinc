; This file is part of BOINC.
; http://boinc.berkeley.edu
; Copyright (C) 2019 University of California
;
; BOINC is free software; you can redistribute it and/or modify it
; under the terms of the GNU Lesser General Public License
; as published by the Free Software Foundation,
; either version 3 of the License, or (at your option) any later version.
;
; BOINC is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
; See the GNU Lesser General Public License for more details.
;
; You should have received a copy of the GNU Lesser General Public License
; along with BOINC.  If not, see <http://www.gnu.org/licenses/>.

Unicode true
XPStyle on

SetCompressor /SOLID lzma

!include "MUI2.nsh"

!include "include\boinc_configuration_page.nsh"


!define license_file "redist\0409\eula.rtf"
!define setup_icon "redist\setup.ico"
!define setup_splash "redist\setup.bmp"
!define folder_icon "redist\folder.ico"
!define out_file "boinc_${product_version}_${product_arch}.exe"
!if ${product_arch} == "intelx86"
    !define arch_path "Win32"
!else
    !define arch_path "x64"
!endif
!define boinc_src_path "..\.."
!define boinc_release_path "${boinc_src_path}\win_build\Build\${arch_path}\Release"
!define boinc_dependencies_path "${boinc_src_path}\..\boinc_depends_win_vs2013"
!define boinc_dependencies_curl_path "${boinc_dependencies_path}\curl\mswin\${arch_path}\Release\bin"
!define boinc_dependencies_openssl_path "${boinc_dependencies_path}\openssl\mswin\${arch_path}\Release\bin"
!define boinc_dependencies_sqlite3_path "${boinc_dependencies_path}\sqlite3\mswin\${arch_path}\Release\bin"
!define boinc_dependencies_zlib_path "${boinc_dependencies_path}\zlib\mswin\${arch_path}\Release\bin"
!define boinc_msvc_path "${boinc_src_path}\win_build\Build\${arch_path}\Release"
!define boinc_skin_path "${boinc_src_path}\clientgui\skins\${boinc_skin_name}"

!define MUI_ABORTWARNING

!define MUI_ICON "${setup_icon}"
!define MUI_UNICON "${setup_icon}"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "${license_file}"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro BOINC_PAGE_CONFIGURATION
!insertmacro MUI_PAGE_INSTFILES

!define MUI_LANGDLL_ALLLANGUAGES

;--------------------------------
;Language Selection Dialog Settings

  ;Remember the installer language
;   !define MUI_LANGDLL_REGISTRY_ROOT "HKCU" 
;   !define MUI_LANGDLL_REGISTRY_KEY "Software\Modern UI Test" 
;   !define MUI_LANGDLL_REGISTRY_VALUENAME "Installer Language"

!insertmacro MUI_LANGUAGE "English"

!include "include\l10n\English.nsh"

!insertmacro MUI_RESERVEFILE_LANGDLL

Name "${product_name}"
Caption "${product_name}"
OutFile "${out_file}"

!define MUI_COMPONENTSPAGE_NODESC

Section "-Common"
    SetOutPath "$INSTDIR"
    File "${boinc_src_path}\COPYING"
    File "${boinc_src_path}\COPYING.LESSER"
    File "${boinc_src_path}\COPYRIGHT"
    File "${boinc_msvc_path}\msvcp100.dll"
    File "${boinc_msvc_path}\msvcr100.dll"
SectionEnd

Section "BOINC Client" sec_boinc_client
    SetOutPath "$INSTDIR"
    File "${boinc_release_path}\boinc.exe"
    File "${boinc_release_path}\boinccmd.exe"
    File "${boinc_release_path}\boinctray.exe"
    File "${boinc_dependencies_curl_path}\libcurl.dll"
    File "${boinc_dependencies_openssl_path}\libeay32.dll"
    File "${boinc_dependencies_openssl_path}\ssleay32.dll"
    File "${boinc_dependencies_zlib_path}\zlib1.dll"
    File "${boinc_src_path}\curl\ca-bundle.crt"
    ${If} $boinc_configuration_page_service_install == "1"
        File "${boinc_release_path}\boincsvcctrl.exe"
    ${EndIf}

    SetOutPath "$boinc_configuration_page_data_dir\BOINC"
    File "${boinc_src_path}\win_build\installerv2\redist\all_projects_list.xml"

    CreateDirectory "$boinc_configuration_page_data_dir\BOINC\projects"
    CreateDirectory "$boinc_configuration_page_data_dir\BOINC\slots"

    SetOutPath "$INSTDIR\locale"
    File /r "${boinc_src_path}\locale\BOINC-Client.mo"

SectionEnd

Section "BOINC Manager"
    SetOutPath "$INSTDIR"
    File "${boinc_release_path}\boincmgr.exe"
    File "${boinc_dependencies_sqlite3_path}\sqlite3.dll"

    SetOutPath "$INSTDIR\Skins\${boinc_skin_name}"
    File "${boinc_skin_path}\*"

    SetOutPath "$INSTDIR\locale"
    File /r "${boinc_src_path}\locale\BOINC-Manager.mo"
SectionEnd

Section "BOINC Screensaver"
    SetOutPath "$INSTDIR"
    File "${boinc_src_path}\clientscr\res\boinc_logo_black.jpg"
    File "${boinc_release_path}\boincscr.exe"
    File "${boinc_src_path}\api\ttf\liberation-fonts-ttf-2.00.0\LiberationSans-Regular.ttf"

    SetOutPath "$SYSDIR"
    File "${boinc_release_path}\boinc.scr"
SectionEnd

Function .onInit
    InitPluginsDir
    File /oname=$PLUGINSDIR\splash.bmp "${setup_splash}"
    advsplash::show 1000 600 400 -1 $PLUGINSDIR\splash
    Pop $0
    Delete $PLUGINSDIR\splash.bmp

    !insertmacro MUI_LANGDLL_DISPLAY

    !if ${product_arch} == "intelx86"
        StrCpy $INSTDIR $PROGRAMFILES\${product_name}
    !else
        StrCpy $INSTDIR $PROGRAMFILES64\${product_name}
    !endif
    SetShellVarContext all
    StrCpy $boinc_configuration_page_data_dir $APPDATA

    StrCpy $sec_boinc_client_name ${sec_boinc_client}
FunctionEnd

;--------------------------------
;Uninstaller Functions

; Function un.onInit

;   !insertmacro MUI_UNGETLANGUAGE
  
; FunctionEnd
