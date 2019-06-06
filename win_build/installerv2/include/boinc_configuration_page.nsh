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

Var configuration_page
Var installdir_change_button
Var datadir_change_button
Var use_screensaver_checkbox
Var service_install
Var service_label_disable_line
Var service_label_description_line
Var service_label_reboot_line
Var all_users
Var advanced_label
Var advanced_button

!macro BOINC_CONFIGURATIONPAGE_INTERFACE
    !ifndef BOINC_CONFIGURATIONPAGE_INTERFACE
        !define BOINC_CONFIGURATIONPAGE_INTERFACE

        !insertmacro MUI_DEFAULT MUI_LICENSEPAGE_BGCOLOR "/windows"    
        LicenseBkColor "${MUI_LICENSEPAGE_BGCOLOR}"
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
        ${NSD_CreateLabel} 50 0 65% 11u "Program directory:"
        ${NSD_CreateLabel} 50 11u 65% 11u "[INSTALLDIR]"

        ${NSD_CreateButton} 82% 7u 18% 15u "Change..."
        Pop $installdir_change_button
        ShowWindow $installdir_change_button ${SW_HIDE}

        ${NSD_CreateIcon} 0 26u 32 32 ""
        Pop $0
        ${NSD_SetIcon} $0 $PLUGINSDIR\folder.ico $folder_image_handle
        ${NSD_CreateLabel} 50 26u 65% 11u "Data directory:"
        ${NSD_CreateLabel} 50 37u 65% 11u "[DATADIR]"

        ${NSD_CreateButton} 82% 33u 18% 15u "Change..."
        Pop $datadir_change_button
        ShowWindow $datadir_change_button ${SW_HIDE}

        ${NSD_CreateCheckBox} 0 50u 100% 11u "Use BOINC Screensaver"
        Pop $use_screensaver_checkbox
        ${NSD_Check} $use_screensaver_checkbox
        EnableWindow $use_screensaver_checkbox 0

        ${NSD_CreateCheckBox} 0 63u 100% 11u "Service Install"
        Pop $service_install
        ${NSD_Uncheck} $service_install
        EnableWindow $service_install 0
        ${NSD_CreateLabel} 11u 74u 100% 11u "This option is disabled by defaut."
        Pop $service_label_disable_line
        EnableWindow $service_label_disable_line 0
        ${NSD_CreateLabel} 11u 82u 100% 24u "Run project applications under an unprivileged account. This provides increased protection from faulty applications, and on Windows, it will prevent the use of applications that use graphics chips (GPUs)"
        Pop $service_label_description_line
        EnableWindow $service_label_description_line 0
        ${NSD_CreateLabel} 11u 106u 100% 11u "A reboot may be required."
        Pop $service_label_reboot_line
        EnableWindow $service_label_reboot_line 0

        ${NSD_CreateCheckBox} 0 117u 75% 11u "Allow all users on this computer to control BOINC"
        Pop $all_users
        ${NSD_Check} $all_users
        EnableWindow $all_users 0

        ; ${NSD_CreateLabel} 0 128u 50% 11u "Click Next to use these options."
        ${NSD_CreateLabel} 0 130u 75% 11u "Click Advanced to customize options."
        Pop $advanced_label

        ${NSD_CreateButton} 82% 125u 18% 15u "Advanced"
        Pop $advanced_button
        ${NSD_OnClick} $advanced_button OnAdvanced

        nsDialogs::Show

        ${NSD_FreeImage} $folder_image_handle
        Delete $PLUGINSDIR\folder.ico
    FunctionEnd

    Function "${LEAVE}"
        !insertmacro MUI_PAGE_FUNCTION_CUSTOM LEAVE
    FunctionEnd
!macroend

Function OnAdvanced
    ShowWindow $installdir_change_button ${SW_SHOW}
    ShowWindow $datadir_change_button ${SW_SHOW}
    EnableWindow $use_screensaver_checkbox 1
    EnableWindow $service_install 1
    EnableWindow $service_label_disable_line 1
    EnableWindow $service_label_description_line 1
    EnableWindow $service_label_reboot_line 1
    EnableWindow $all_users 1
    ShowWindow $advanced_label ${SW_HIDE}
    ShowWindow $advanced_button ${SW_HIDE}
FunctionEnd
