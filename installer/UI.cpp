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
    
    Dialog dialog("AdminChangeFolder", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Tail", "OK", "Cancel");

    dialog.add(Control("AdminChangeFolder", "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "NewBinary1"));
    dialog.add(Control("AdminChangeFolder", "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
    dialog.add(Control("AdminChangeFolder", "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "ComboText"));
    dialog.add(Control("AdminChangeFolder", "Combo", CONTROL_TYPE::DirectoryCombo(), 21, 64, 277, 80, 458755, "TARGETDIR", installerStrings.get("IDS__IsAdminInstallBrowse_4"), "Up"));
    dialog.add(Control("AdminChangeFolder", "ComboText", CONTROL_TYPE::Text(), 21, 50, 99, 14, 3, "", installerStrings.get("IDS__IsAdminInstallBrowse_LookIn"), "Combo"));
    dialog.add(Control("AdminChangeFolder", "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65539, "", installerStrings.get("IDS__IsAdminInstallBrowse_BrowseDestination")));
    dialog.add(Control("AdminChangeFolder", "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1));
    dialog.add(Control("AdminChangeFolder", "DlgTitle", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65539, "", installerStrings.get("IDS__IsAdminInstallBrowse_ChangeDestination")));
    dialog.add(Control("AdminChangeFolder", "List", CONTROL_TYPE::DirectoryList(), 21, 90, 332, 97, 7, "TARGETDIR", installerStrings.get("IDS__IsAdminInstallBrowse_8"), "TailText"));
    dialog.add(Control("AdminChangeFolder", "NewFolder", CONTROL_TYPE::PushButton(), 335, 66, 19, 19, 3670019, "", "NewBinary2", "List", installerStrings.get("IDS__IsAdminInstallBrowse_CreateFolder")));
    dialog.add(Control("AdminChangeFolder", "OK", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS_OK"), "Cancel"));
    dialog.add(Control("AdminChangeFolder", "Tail", CONTROL_TYPE::PathEdit(), 21, 207, 332, 17, 3, "TARGETDIR", installerStrings.get("IDS__IsAdminInstallBrowse_11"), "OK"));
    dialog.add(Control("AdminChangeFolder", "TailText", CONTROL_TYPE::Text(), 21, 193, 99, 13, 3, "", installerStrings.get("IDS__IsAdminInstallBrowse_FolderName"), "Tail"));
    dialog.add(Control("AdminChangeFolder", "Up", CONTROL_TYPE::PushButton(), 310, 66, 19, 19, 3670019, "", "NewBinary3", "NewFolder", installerStrings.get("IDS__IsAdminInstallBrowse_UpOneLevel")));

    dialogs.emplace_back(dialog);
}

void UI::create_AdminNetworkLocation_dialog() {
    Dialog dialog("AdminNetworkLocation", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "InstallNow", "InstallNow", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_AdminWelcome_dialog() {
    Dialog dialog("AdminWelcome", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_CancelSetup_dialog() {
    Dialog dialog("CancelSetup", 50, 50, 260, 85, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "No", "No", "No");
    dialogs.emplace_back(dialog);
}

void UI::create_ChangeFolderData_dialog() {
    Dialog dialog("ChangeFolderData", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Tail", "OK", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_ChangeFolderInstall_dialog() {
    Dialog dialog("ChangeFolderInstall", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Tail", "OK", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_DiskSpaceRequirements_dialog() {
    Dialog dialog("DiskSpaceRequirements", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "OK", "OK", "OK");
    dialogs.emplace_back(dialog);
}

void UI::create_FeatureNotSupported_dialog() {
    Dialog dialog("FeatureNotSupported", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Back", "Back", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_FilesInUse_dialog() {
    Dialog dialog("FilesInUse", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL | ATTRIBUTE::KEEP_MODELESS, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Retry", "Retry", "Exit");
    dialogs.emplace_back(dialog);
}

void UI::create_InstallWelcome_dialog() {
    Dialog dialog("InstallWelcome", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_LicenseAgreement_dialog() {
    Dialog dialog("LicenseAgreement", 50, 50, 374, 266, ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Agree", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_MaintenanceType_dialog() {
    Dialog dialog("MaintenanceType", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "RadioGroup", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_MaintenanceWelcome_dialog() {
    Dialog dialog("MaintenanceWelcome", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_MsiRMFilesInUse_dialog() {
    Dialog dialog("MsiRMFilesInUse", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL | ATTRIBUTE::KEEP_MODELESS, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "OK", "OK", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_OutOfSpace_dialog() {
    Dialog dialog("OutOfSpace", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Resume", "Resume", "Resume");
    dialogs.emplace_back(dialog);
}

void UI::create_PatchWelcome_dialog() {
    Dialog dialog("PatchWelcome", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS__IsPatchDlg_PatchWizard"), "Next", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_ReadyToInstall_dialog() {
    Dialog dialog("ReadyToInstall", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL | ATTRIBUTE::TRACK_DISK_SPACE, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "InstallNow", "InstallNow", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_ReadyToRemove_dialog() {
    Dialog dialog("ReadyToRemove", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "RemoveNow", "RemoveNow", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupCompleteError_dialog() {
    Dialog dialog("SetupCompleteError", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Finish", "Finish", "Finish");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupCompleteSuccess_dialog() {
    Dialog dialog("SetupCompleteSuccess", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "OK", "LaunchProgramCheck", "OK");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupConfig_dialog() {
    Dialog dialog("SetupConfig", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("ID_STRING18"), "Advanced", "CheckBox4", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupConfigAdvanced_dialog() {
    Dialog dialog("SetupConfigAdvanced", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("ID_STRING26"), "Next", "CheckBox4", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupError_dialog() {
    Dialog dialog("SetupError", 50, 10, 270, 110, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL | ATTRIBUTE::MINIMIZE | ATTRIBUTE::ATTRIBUTE_ERROR, installerStrings.get("IDS__IsErrorDlg_InstallerInfo"), "ErrorText", "O", "C");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupInitialization_dialog() {
    Dialog dialog("SetupInitialization", 50, 50, 374, 266, ATTRIBUTE::MINIMIZE | ATTRIBUTE::VISIBLE, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Cancel", "Cancel", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupInterrupted_dialog() {
    Dialog dialog("SetupInterrupted", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Finish", "Finish", "Finish");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupProgress_dialog() {
    Dialog dialog("SetupProgress", 50, 50, 374, 266, ATTRIBUTE::MINIMIZE | ATTRIBUTE::VISIBLE, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Cancel", "Cancel", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_SetupResume_dialog() {
    Dialog dialog("SetupResume", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

void UI::create_SplashBitmap_dialog() {
    Dialog dialog("SplashBitmap", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel");
    dialogs.emplace_back(dialog);
}

const std::vector<Dialog>& UI::get_dialogs() const noexcept {
    return dialogs;
}

std::vector<Control> UI::get_controls() const noexcept
{
    std::vector<Control> controls;
    for (const auto& dialog : dialogs) {
        for (const auto& control : dialog.get_controls()) {
            controls.emplace_back(control);
        }
    }
    return controls;
}
