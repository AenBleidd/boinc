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
    !endif
  
    !insertmacro MUI_DEFAULT BOINC_${MUI_PAGE_UNINSTALLER_PREFIX}BOINCCONFIGURATIONPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\win.bmp"
    !if "${BOINC_${MUI_PAGE_UNINSTALLER_PREFIX}BOINCCONFIGURATIONPAGE_BITMAP}" == ""
        !error "Invalid BOINC_${MUI_PAGE_UNINSTALLER_PREFIX}BOINCCONFIGURATIONPAGE_BITMAP"
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
        !insertmacro MUI_PAGE_FUNCTION_CUSTOM PRE

        nsDialogs::Create 1044
        nsDialogs::SetRTL $(^RTL)

        Call ${MUI_PAGE_UNINSTALLER_FUNCPREFIX}muiPageLoadFullWindow
        !insertmacro MUI_PAGE_FUNCTION_CUSTOM SHOW
        nsDialogs::Show
        !insertmacro MUI_PAGE_FUNCTION_CUSTOM DESTROYED
        Call ${MUI_PAGE_UNINSTALLER_FUNCPREFIX}muiPageUnloadFullWindow    

    FunctionEnd

    Function "${LEAVE}"
        !insertmacro MUI_PAGE_FUNCTION_CUSTOM LEAVE
    FunctionEnd
!macroend
