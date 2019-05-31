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

!macro BOINC_CONFIGURATIONPAGE_INTERFACE
    !ifndef BOINC_CONFIGURATIONPAGE_INTERFACE
        !define BOINC_CONFIGURATIONPAGE_INTERFACE

        !insertmacro MUI_DEFAULT MUI_LICENSEPAGE_BGCOLOR "/windows"    
        LicenseBkColor "${MUI_LICENSEPAGE_BGCOLOR}"

        Var boinc.configuration_page

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
        !insertmacro MUI_HEADER_TEXT "${product_name} Configuration" "These are the current installation options"

        nsDialogs::Create 1018
        Pop $boinc.configuration_page
        nsDialogs::SetRTL $(^RTL)



        nsDialogs::Show

    FunctionEnd

    Function "${LEAVE}"
        !insertmacro MUI_PAGE_FUNCTION_CUSTOM LEAVE
    FunctionEnd
!macroend
