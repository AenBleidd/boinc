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
    const auto dialog_name = "AdminChangeFolder";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Tail", "OK", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "NewBinary1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "ComboText"));
            controls.emplace_back(Control(dialog_name, "Combo", CONTROL_TYPE::DirectoryCombo(), 21, 64, 277, 80, 458755, "TARGETDIR", installerStrings.get("IDS__IsAdminInstallBrowse_4"), "Up"));
            controls.emplace_back(Control(dialog_name, "ComboText", CONTROL_TYPE::Text(), 21, 50, 99, 14, 3, "", installerStrings.get("IDS__IsAdminInstallBrowse_LookIn"), "Combo"));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65539, "", installerStrings.get("IDS__IsAdminInstallBrowse_BrowseDestination")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65539, "", installerStrings.get("IDS__IsAdminInstallBrowse_ChangeDestination")));
            controls.emplace_back(Control(dialog_name, "List", CONTROL_TYPE::DirectoryList(), 21, 90, 332, 97, 7, "TARGETDIR", installerStrings.get("IDS__IsAdminInstallBrowse_8"), "TailText"));
            controls.emplace_back(Control(dialog_name, "NewFolder", CONTROL_TYPE::PushButton(), 335, 66, 19, 19, 3670019, "", "NewBinary2", "List", installerStrings.get("IDS__IsAdminInstallBrowse_CreateFolder")));
            controls.emplace_back(Control(dialog_name, "OK", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS_OK"), "Cancel"));
            controls.emplace_back(Control(dialog_name, "Tail", CONTROL_TYPE::PathEdit(), 21, 207, 332, 17, 3, "TARGETDIR", installerStrings.get("IDS__IsAdminInstallBrowse_11"), "OK"));
            controls.emplace_back(Control(dialog_name, "TailText", CONTROL_TYPE::Text(), 21, 193, 99, 13, 3, "", installerStrings.get("IDS__IsAdminInstallBrowse_FolderName"), "Tail"));
            controls.emplace_back(Control(dialog_name, "Up", CONTROL_TYPE::PushButton(), 310, 66, 19, 19, 3670019, "", "NewBinary3", "NewFolder", installerStrings.get("IDS__IsAdminInstallBrowse_UpOneLevel")));
            return controls;
        }()));
}

void UI::create_AdminNetworkLocation_dialog() {
    const auto dialog_name = "AdminNetworkLocation";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "InstallNow", "InstallNow", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 3, "", installerStrings.get("IDS_BACK"), "InstallNow"));
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "NewBinary1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1, ""));
            controls.emplace_back(Control(dialog_name, "Browse", CONTROL_TYPE::PushButton(), 286, 124, 66, 17, 3, "", installerStrings.get("IDS__IsAdminInstallPoint_Change"), "Back"));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "SetupPathEdit"));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65539, "", installerStrings.get("IDS__IsAdminInstallPoint_SpecifyNetworkLocation")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1, ""));
            controls.emplace_back(Control(dialog_name, "DlgText", CONTROL_TYPE::Text(), 21, 51, 326, 40, 3, "", installerStrings.get("IDS__IsAdminInstallPoint_EnterNetworkLocation")));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65539, "", installerStrings.get("IDS__IsAdminInstallPoint_NetworkLocationFormatted")));
            controls.emplace_back(Control(dialog_name, "InstallNow", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS__IsAdminInstallPoint_Install"), "Cancel"));
            controls.emplace_back(Control(dialog_name, "LBBrowse", CONTROL_TYPE::Text(), 21, 90, 100, 10, 3, "", installerStrings.get("IDS__IsAdminInstallPoint_NetworkLocation")));
            controls.emplace_back(Control(dialog_name, "SetupPathEdit", CONTROL_TYPE::PathEdit(), 21, 102, 330, 17, 3, "TARGETDIR", "", "Browse"));
            return controls;
        }()));
}

void UI::create_AdminWelcome_dialog() {
    const auto dialog_name = "AdminWelcome";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 1, "", installerStrings.get("IDS_BACK"), "Next"));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "Back"));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 0, 234, 326, 0, 1));
            controls.emplace_back(Control(dialog_name, "Image", CONTROL_TYPE::Bitmap(), 0, 0, 374, 234, 1, "", "NewBinary5"));
            controls.emplace_back(Control(dialog_name, "Next", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS_NEXT"), "Cancel"));
            controls.emplace_back(Control(dialog_name, "TextLine1", CONTROL_TYPE::Text(), 135, 8, 225, 45, 65539, "", installerStrings.get("IDS__IsAdminInstallPointWelcome_Wizard")));
            controls.emplace_back(Control(dialog_name, "TextLine2", CONTROL_TYPE::Text(), 135, 55, 228, 45, 65539, "", installerStrings.get("IDS__IsAdminInstallPointWelcome_ServerImage")));
            return controls;
        }()));
}

void UI::create_CancelSetup_dialog() {
    const auto dialog_name = "CancelSetup";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 260, 85, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "No", "No", "No",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Icon", CONTROL_TYPE::Icon(), 15, 15, 24, 24, 5242881, "", "NewBinary4"));
            controls.emplace_back(Control(dialog_name, "No", CONTROL_TYPE::PushButton(), 135, 57, 66, 17, 3, "", installerStrings.get("IDS__IsCancelDlg_No"), "Yes"));
            controls.emplace_back(Control(dialog_name, "Text", CONTROL_TYPE::Text(), 48, 15, 194, 30, 3, "", installerStrings.get("IDS__IsCancelDlg_ConfirmCancel")));
            controls.emplace_back(Control(dialog_name, "Yes", CONTROL_TYPE::PushButton(), 62, 57, 66, 17, 3, "", installerStrings.get("IDS__IsCancelDlg_Yes"), "No"));
            return controls;
        }()));
}

void UI::create_ChangeFolderData_dialog() {
    dialogs.emplace_back(Dialog("ChangeFolderData", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Tail", "OK", "Cancel", {}));
}

void UI::create_ChangeFolderInstall_dialog() {
    dialogs.emplace_back(Dialog("ChangeFolderInstall", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Tail", "OK", "Cancel", {}));
}

void UI::create_DiskSpaceRequirements_dialog() {
    dialogs.emplace_back(Dialog("DiskSpaceRequirements", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "OK", "OK", "OK", {}));
}

void UI::create_FeatureNotSupported_dialog() {
    dialogs.emplace_back(Dialog("FeatureNotSupported", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Back", "Back", "Cancel", {}));
}

void UI::create_FilesInUse_dialog() {
    dialogs.emplace_back(Dialog("FilesInUse", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL | ATTRIBUTE::KEEP_MODELESS, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Retry", "Retry", "Exit", {}));
}

void UI::create_InstallWelcome_dialog() {
    dialogs.emplace_back(Dialog("InstallWelcome", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel", {}));
}

void UI::create_LicenseAgreement_dialog() {
    dialogs.emplace_back(Dialog("LicenseAgreement", 50, 50, 374, 266, ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Agree", "Next", "Cancel", {}));
}

void UI::create_MaintenanceType_dialog() {
    dialogs.emplace_back(Dialog("MaintenanceType", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "RadioGroup", "Next", "Cancel", {}));
}

void UI::create_MaintenanceWelcome_dialog() {
    dialogs.emplace_back(Dialog("MaintenanceWelcome", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel", {}));
}

void UI::create_MsiRMFilesInUse_dialog() {
    dialogs.emplace_back(Dialog("MsiRMFilesInUse", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL | ATTRIBUTE::KEEP_MODELESS, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "OK", "OK", "Cancel", {}));
}

void UI::create_OutOfSpace_dialog() {
    dialogs.emplace_back(Dialog("OutOfSpace", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Resume", "Resume", "Resume", {}));
}

void UI::create_PatchWelcome_dialog() {
    dialogs.emplace_back(Dialog("PatchWelcome", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS__IsPatchDlg_PatchWizard"), "Next", "Next", "Cancel", {}));
}

void UI::create_ReadyToInstall_dialog() {
    dialogs.emplace_back(Dialog("ReadyToInstall", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL | ATTRIBUTE::TRACK_DISK_SPACE, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "InstallNow", "InstallNow", "Cancel", {}));
}

void UI::create_ReadyToRemove_dialog() {
    dialogs.emplace_back(Dialog("ReadyToRemove", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "RemoveNow", "RemoveNow", "Cancel", {}));
}

void UI::create_SetupCompleteError_dialog() {
    dialogs.emplace_back(Dialog("SetupCompleteError", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Finish", "Finish", "Finish", {}));
}

void UI::create_SetupCompleteSuccess_dialog() {
    dialogs.emplace_back(Dialog("SetupCompleteSuccess", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "OK", "LaunchProgramCheck", "OK", {}));
}

void UI::create_SetupConfig_dialog() {
    dialogs.emplace_back(Dialog("SetupConfig", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("ID_STRING18"), "Advanced", "CheckBox4", "Cancel", {}));
}

void UI::create_SetupConfigAdvanced_dialog() {
    dialogs.emplace_back(Dialog("SetupConfigAdvanced", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("ID_STRING26"), "Next", "CheckBox4", "Cancel", {}));
}

void UI::create_SetupError_dialog() {
    dialogs.emplace_back(Dialog("SetupError", 50, 10, 270, 110, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL | ATTRIBUTE::MINIMIZE | ATTRIBUTE::ATTRIBUTE_ERROR, installerStrings.get("IDS__IsErrorDlg_InstallerInfo"), "ErrorText", "O", "C", {}));
}

void UI::create_SetupInitialization_dialog() {
    dialogs.emplace_back(Dialog("SetupInitialization", 50, 50, 374, 266, ATTRIBUTE::MINIMIZE | ATTRIBUTE::VISIBLE, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Cancel", "Cancel", "Cancel", {}));
}

void UI::create_SetupInterrupted_dialog() {
    dialogs.emplace_back(Dialog("SetupInterrupted", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Finish", "Finish", "Finish", {}));
}

void UI::create_SetupProgress_dialog() {
    dialogs.emplace_back(Dialog("SetupProgress", 50, 50, 374, 266, ATTRIBUTE::MINIMIZE | ATTRIBUTE::VISIBLE, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Cancel", "Cancel", "Cancel", {}));
}

void UI::create_SetupResume_dialog() {
    dialogs.emplace_back(Dialog("SetupResume", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel", {}));
}

void UI::create_SplashBitmap_dialog() {
    dialogs.emplace_back(Dialog("SplashBitmap", 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel", {}));
}

const std::vector<Dialog>& UI::get_dialogs() const noexcept {
    return dialogs;
}

std::vector<Control> UI::get_controls() const
{
    std::vector<Control> controls;
    for (const auto& dialog : dialogs) {
        for (const auto& control : dialog.get_controls()) {
            controls.emplace_back(control);
        }
    }
    return controls;
}
