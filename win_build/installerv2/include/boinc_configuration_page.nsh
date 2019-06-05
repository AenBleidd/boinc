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

!include nsDialogs.nsh
!include LogicLib.nsh

!macro BOINC_CONFIGURATIONPAGE_INTERFACE
    !ifndef BOINC_CONFIGURATIONPAGE_INTERFACE
        !define BOINC_CONFIGURATIONPAGE_INTERFACE

        !insertmacro MUI_DEFAULT MUI_LICENSEPAGE_BGCOLOR "/windows"    
        LicenseBkColor "${MUI_LICENSEPAGE_BGCOLOR}"

        Var configuration_page
        Var use_screensaver_checkbox
        Var service_install
        Var all_users
    !endif
!macroend

!macro BOINC_CONFIGURATIONPAGE_GUIINIT
!macroend

!macro BOINC_PAGEDECLARATION_CONFIGURATION
    !insertmacro MUI_SET BOINC_${MUI_PAGE_UNINSTALLER_PREFIX}CONFIGURATION ""
    !insertmacro BOINC_CONFIGURATIONPAGE_INTERFACE

    !insertmacro BOINC_CONFIGURATIONPAGE_GUIINIT

    !insertmacro MUI_PAGE_FUNCTION_FULLWINDOW

    PageEx ${MUI_PAGE_UNINSTALLER_FUNCPREFIX}custom
        PageCallbacks ${MUI_PAGE_UNINSTALLER_FUNCPREFIX}boinc.ConfigurationPre_${MUI_UNIQUEID} ${MUI_PAGE_UNINSTALLER_FUNCPREFIX}boinc.ConfigurationLeave_${MUI_UNIQUEID}
        Caption " "
    PageExEnd
    !insertmacro BOINC_FUNCTION_CONFIGURATIONPAGE ${MUI_PAGE_UNINSTALLER_FUNCPREFIX}boinc.ConfigurationPre_${MUI_UNIQUEID} ${MUI_PAGE_UNINSTALLER_FUNCPREFIX}boinc.ConfigurationLeave_${MUI_UNIQUEID}
!macroend

!macro BOINC_PAGE_CONFIGURATION
    !verbose push
    !verbose ${MUI_VERBOSE}

    !insertmacro MUI_PAGE_INIT
    !insertmacro BOINC_PAGEDECLARATION_CONFIGURATION

    !verbose pop
!macroend

!macro BOINC_FUNCTION_CONFIGURATIONPAGE PRE LEAVE
    Function "${PRE}"
        Var /GLOBAL folder_image_handle
        !insertmacro MUI_HEADER_TEXT "${product_name} Configuration" "These are the current installation options"

        InitPluginsDir
        File /oname=$PLUGINSDIR\folder.ico ${folder_icon}

        nsDialogs::Create 1018
        Pop $configuration_page
        nsDialogs::SetRTL $(^RTL)

        ${NSD_CreateIcon} 0 0 32 32 ""
        Pop $0
        ${NSD_SetIcon} $0 $PLUGINSDIR\folder.ico $folder_image_handle
        ${NSD_CreateLabel} 50 0 100% 11u "Program directory:"
        ${NSD_CreateLabel} 50 11u 100% 11u "[INSTALLDIR]"

        ${NSD_CreateIcon} 0 26u 32 32 ""
        Pop $0
        ${NSD_SetIcon} $0 $PLUGINSDIR\folder.ico $folder_image_handle
        ${NSD_CreateLabel} 50 26u 100% 11u "Data directory:"
        ${NSD_CreateLabel} 50 37u 100% 11u "[DATADIR]"

        ${NSD_CreateCheckBox} 0 60u 100% 11u "Use BOINC Screensaver"
        Pop $use_screensaver_checkbox
        ${NSD_Check} $use_screensaver_checkbox
        EnableWindow $use_screensaver_checkbox 0

        ${NSD_CreateCheckBox} 0 73u 100% 11u "Service Install"
        Pop $service_install
        ${NSD_Uncheck} $service_install
        EnableWindow $service_install 0
        ${NSD_CreateLabel} 11u 84u 100% 11u "This option is now disabled by defaut."
        Pop $0
        EnableWindow $0 0
        ${NSD_CreateLabel} 11u 92u 100% 11u "A reboot may be required."
        Pop $0
        EnableWindow $0 0

        ${NSD_CreateCheckBox} 0 105u 100% 11u "Allow all users on this computer to control BOINC"
        Pop $all_users
        ${NSD_Check} $all_users
        EnableWindow $all_users 0

        ${NSD_CreateLabel} 0 122u 50% 11u "Click Next to use these options."
        ${NSD_CreateLabel} 0 131u 50% 11u "Click Advanced to customize options."

        ${NSD_CreateButton} 82% 125u 18% 15u "Advanced"
        Pop $0
        ${NSD_OnClick} $0 OnAdvanced

        nsDialogs::Show

        ${NSD_FreeImage} $folder_image_handle
        Delete $PLUGINSDIR\folder.ico
    FunctionEnd

    Function "${LEAVE}"
        !insertmacro MUI_PAGE_FUNCTION_CUSTOM LEAVE
    FunctionEnd
!macroend

Function OnAdvanced
FunctionEnd
