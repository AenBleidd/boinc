// This file is part of BOINC.
// https://boinc.berkeley.edu
// Copyright (C) 2024 University of California
//
// BOINC is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC.  If not, see <http://www.gnu.org/licenses/>.

#include "UI.h"

UI::UI(const InstallerStrings& is) : installerStrings(is) {
    create_dialogs();
}

void UI::create_dialogs() {
    create_AdminChangeFolder_dialog();
    create_AdminNetworkLocation_dialog();
    create_AdminWelcome_dialog();
    create_CancelSetup_dialog();
    create_ChangeFolderData_dialog();
    create_ChangeFolderInstall_dialog();
    create_DiskSpaceRequirements_dialog();
    create_FeatureNotSupported_dialog();
    create_FilesInUse_dialog();
    create_InstallWelcome_dialog();
    create_LicenseAgreement_dialog();
    create_MaintenanceType_dialog();
    create_MaintenanceWelcome_dialog();
    create_MsiRMFilesInUse_dialog();
    create_OutOfSpace_dialog();
    create_PatchWelcome_dialog();
    create_ReadyToInstall_dialog();
    create_ReadyToRemove_dialog();
    create_SetupCompleteError_dialog();
    create_SetupCompleteSuccess_dialog();
    create_SetupConfig_dialog();
    create_SetupConfigAdvanced_dialog();
    create_SetupError_dialog();
    create_SetupInitialization_dialog();
    create_SetupInterrupted_dialog();
    create_SetupProgress_dialog();
    create_SetupResume_dialog();
    create_SplashBitmap_dialog();
}

void UI::create_AdminChangeFolder_dialog() {
    
    Dialog dialog("AdminChangeFolder", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Tail", "OK", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_AdminNetworkLocation_dialog() {
    Dialog dialog("AdminNetworkLocation", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "InstallNow", "InstallNow", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_AdminWelcome_dialog() {
    Dialog dialog("AdminWelcome", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_CancelSetup_dialog() {
    Dialog dialog("CancelSetup", 50, 50, 260, 85, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "No", "No", "No");
    dialogs.emplace_back(dialog);
}

void UI::create_ChangeFolderData_dialog() {
    Dialog dialog("ChangeFolderData", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Tail", "OK", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_ChangeFolderInstall_dialog() {
    Dialog dialog("ChangeFolderInstall", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Tail", "OK", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_DiskSpaceRequirements_dialog() {
    Dialog dialog("DiskSpaceRequirements", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "OK", "OK", "OK");
    dialogs.emplace_back(dialog);
}

void UI::create_FeatureNotSupported_dialog() {
    Dialog dialog("FeatureNotSupported", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Back", "Back", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_FilesInUse_dialog() {
    Dialog dialog("FilesInUse", 50, 50, 374, 266, 19, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Retry", "Retry", "Exit");
    dialogs.emplace_back(dialog);
}

void UI::create_InstallWelcome_dialog() {
    Dialog dialog("InstallWelcome", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_LicenseAgreement_dialog() {
    Dialog dialog("LicenseAgreement", 50, 50, 374, 266, 2, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Agree", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_MaintenanceType_dialog() {
    Dialog dialog("MaintenanceType", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "RadioGroup", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_MaintenanceWelcome_dialog() {
    Dialog dialog("MaintenanceWelcome", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_MsiRMFilesInUse_dialog() {
    Dialog dialog("MsiRMFilesInUse", 50, 50, 374, 266, 19, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "OK", "OK", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_OutOfSpace_dialog() {
    Dialog dialog("OutOfSpace", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Resume", "Resume", "Resume");
    dialogs.emplace_back(dialog);
}

void UI::create_PatchWelcome_dialog() {
    Dialog dialog("PatchWelcome", 50, 50, 374, 266, 3, installerStrings.get("IDS__IsPatchDlg_PatchWizard"), "Next", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_ReadyToInstall_dialog() {
    Dialog dialog("ReadyToInstall", 50, 50, 374, 266, 35, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "InstallNow", "InstallNow", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_ReadyToRemove_dialog() {
    Dialog dialog("ReadyToRemove", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "RemoveNow", "RemoveNow", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupCompleteError_dialog() {
    Dialog dialog("SetupCompleteError", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Finish", "Finish", "Finish");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupCompleteSuccess_dialog() {
    Dialog dialog("SetupCompleteSuccess", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "OK", "LaunchProgramCheck", "OK");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupConfig_dialog() {
    Dialog dialog("SetupConfig", 50, 50, 374, 266, 3, installerStrings.get("ID_STRING18"), "Advanced", "CheckBox4", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupConfigAdvanced_dialog() {
    Dialog dialog("SetupConfigAdvanced", 50, 50, 374, 266, 3, installerStrings.get("ID_STRING26"), "Next", "CheckBox4", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupError_dialog() {
    Dialog dialog("SetupError", 50, 10, 270, 110, 65543, installerStrings.get("IDS__IsErrorDlg_InstallerInfo"), "ErrorText", "O", "C");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupInitialization_dialog() {
    Dialog dialog("SetupInitialization", 50, 50, 374, 266, 5, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Cancel", "Cancel", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupInterrupted_dialog() {
    Dialog dialog("SetupInterrupted", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Finish", "Finish", "Finish");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupProgress_dialog() {
    Dialog dialog("SetupProgress", 50, 50, 374, 266, 5, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Cancel", "Cancel", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupResume_dialog() {
    Dialog dialog("SetupResume", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_SplashBitmap_dialog() {
    Dialog dialog("SplashBitmap", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

const std::vector<Dialog>& UI::get_dialogs() const noexcept {
    return dialogs;
}