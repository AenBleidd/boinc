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

Var boinc_configuration_page_data_dir_label
Var boinc_configuration_page_service_install_checkbox
Var boinc_configuration_page_all_users_checkbox
Var boinc_configuration_page_data_dir
Var boinc_configuration_page_service_install
Var boinc_configuration_page_all_users

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
        !insertmacro MUI_HEADER_TEXT "${product_name} Configuration" "Customize how BOINC is installed on your computer"

        InitPluginsDir
        File /oname=$PLUGINSDIR\folder.ico ${folder_icon}

        nsDialogs::Create 1018
        nsDialogs::SetRTL $(^RTL)

        ${NSD_CreateIcon} 0 0 32 32 ""
        Pop $0
        ${NSD_SetIcon} $0 $PLUGINSDIR\folder.ico $folder_image_handle
        ${NSD_CreateLabel} 50 0 65% 11u "Data directory:"
        ${NSD_CreateLabel} 50 11u 65% 11u $boinc_configuration_page_data_dir
        Pop $boinc_configuration_page_data_dir_label

        ${NSD_CreateButton} 82% 7u 18% 15u "Change..."
        Pop $0
        ${NSD_OnClick} $0 OnDataDirChange

        ${NSD_CreateCheckBox} 0 26u 100% 11u "Service Install"
        Pop $boinc_configuration_page_service_install_checkbox
        ${NSD_CreateLabel} 11u 37u 100% 24u "Run project applications under an unprivileged account. This provides increased protection from faulty applications, and on Windows, it will prevent the use of applications that use graphics chips (GPUs)"
        ${NSD_CreateLabel} 11u 69u 100% 11u "A reboot may be required."

        ${NSD_CreateCheckBox} 0 93u 75% 11u "Allow all users on this computer to control BOINC"
        Pop $boinc_configuration_page_all_users_checkbox
        ${NSD_Check} $boinc_configuration_page_all_users_checkbox

        nsDialogs::Show

        ${NSD_FreeImage} $folder_image_handle
        Delete $PLUGINSDIR\folder.ico
    FunctionEnd

    Function "${LEAVE}"
        !insertmacro MUI_PAGE_FUNCTION_CUSTOM LEAVE

        ${NSD_GetText} $boinc_configuration_page_data_dir_label $boinc_configuration_page_data_dir
        ${NSD_GetState} $boinc_configuration_page_service_install_checkbox $boinc_configuration_page_service_install
        ${NSD_GetState} $boinc_configuration_page_all_users_checkbox $boinc_configuration_page_all_users
    FunctionEnd
!macroend

Function OnDataDirChange
FunctionEnd
