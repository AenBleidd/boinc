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
    const auto dialog_name = "ChangeFolderData";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Tail", "OK", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "NewBinary1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "ComboText"));
            controls.emplace_back(Control(dialog_name, "Combo", CONTROL_TYPE::DirectoryCombo(), 21, 64, 277, 80, 4128779, "_BrowseDataProperty", installerStrings.get("IDS__IsBrowseFolderDlg_4"), "Up"));
            controls.emplace_back(Control(dialog_name, "ComboText", CONTROL_TYPE::Text(), 21, 50, 99, 14, 3, "", installerStrings.get("IDS__IsBrowseFolderDlg_LookIn"), "Combo"));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65539, "", installerStrings.get("IDS__IsBrowseFolderDlg_BrowseDestFolder")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65539, "", installerStrings.get("IDS__IsBrowseFolderDlg_ChangeCurrentFolder")));
            controls.emplace_back(Control(dialog_name, "List", CONTROL_TYPE::DirectoryList(), 21, 90, 332, 97, 15, "_BrowseDataProperty", installerStrings.get("IDS__IsBrowseFolderDlg_8"), "TailText"));
            controls.emplace_back(Control(dialog_name, "NewFolder", CONTROL_TYPE::PushButton(), 335, 66, 19, 19, 3670019, "", "NewBinary2", "List", installerStrings.get("IDS__IsBrowseFolderDlg_CreateFolder")));
            controls.emplace_back(Control(dialog_name, "OK", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS__IsBrowseFolderDlg_OK"), "Cancel"));
            controls.emplace_back(Control(dialog_name, "Tail", CONTROL_TYPE::PathEdit(), 21, 207, 332, 17, 15, "_BrowseDataProperty", installerStrings.get("IDS__IsBrowseFolderDlg_11"), "OK"));
            controls.emplace_back(Control(dialog_name, "TailText", CONTROL_TYPE::Text(), 21, 193, 99, 13, 3, "", installerStrings.get("IDS__IsBrowseFolderDlg_FolderName"), "Tail"));
            controls.emplace_back(Control(dialog_name, "Up", CONTROL_TYPE::PushButton(), 310, 66, 19, 19, 3670019, "", "NewBinary3", "NewFolder", installerStrings.get("IDS__IsBrowseFolderDlg_UpOneLevel")));
            return controls;
        }()));
}

void UI::create_ChangeFolderInstall_dialog() {
    const auto dialog_name = "ChangeFolderInstall";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Tail", "OK", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "NewBinary1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "ComboText"));
            controls.emplace_back(Control(dialog_name, "Combo", CONTROL_TYPE::DirectoryCombo(), 21, 64, 277, 80, 4128779, "_BrowseInstallProperty", installerStrings.get("IDS__IsBrowseFolderDlg_4"), "Up"));
            controls.emplace_back(Control(dialog_name, "ComboText", CONTROL_TYPE::Text(), 21, 50, 99, 14, 3, "", installerStrings.get("IDS__IsBrowseFolderDlg_LookIn"), "Combo"));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65539, "", installerStrings.get("IDS__IsBrowseFolderDlg_BrowseDestFolder")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65539, "", installerStrings.get("IDS__IsBrowseFolderDlg_ChangeCurrentFolder")));
            controls.emplace_back(Control(dialog_name, "List", CONTROL_TYPE::DirectoryList(), 21, 90, 332, 97, 15, "_BrowseInstallProperty", installerStrings.get("IDS__IsBrowseFolderDlg_8"), "TailText"));
            controls.emplace_back(Control(dialog_name, "NewFolder", CONTROL_TYPE::PushButton(), 335, 66, 19, 19, 3670019, "", "NewBinary2", "List", installerStrings.get("IDS__IsBrowseFolderDlg_CreateFolder")));
            controls.emplace_back(Control(dialog_name, "OK", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS__IsBrowseFolderDlg_OK"), "Cancel"));
            controls.emplace_back(Control(dialog_name, "Tail", CONTROL_TYPE::PathEdit(), 21, 207, 332, 17, 15, "_BrowseInstallProperty", installerStrings.get("IDS__IsBrowseFolderDlg_11"), "OK"));
            controls.emplace_back(Control(dialog_name, "TailText", CONTROL_TYPE::Text(), 21, 193, 99, 13, 3, "", installerStrings.get("IDS__IsBrowseFolderDlg_FolderName"), "Tail"));
            controls.emplace_back(Control(dialog_name, "Up", CONTROL_TYPE::PushButton(), 310, 66, 19, 19, 3670019, "", "NewBinary3", "NewFolder", installerStrings.get("IDS__IsBrowseFolderDlg_UpOneLevel")));
            return controls;
        }()));
}

void UI::create_DiskSpaceRequirements_dialog() {
    const auto dialog_name = "DiskSpaceRequirements";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "OK", "OK", "OK",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "NewBinary1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 17, 23, 292, 25, 65539, "", installerStrings.get("IDS__IsFeatureDetailsDlg_SpaceRequired")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgText", CONTROL_TYPE::Text(), 10, 185, 358, 41, 3, "", installerStrings.get("IDS__IsFeatureDetailsDlg_VolumesTooSmall")));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 9, 6, 292, 25, 65539, "", installerStrings.get("IDS__IsFeatureDetailsDlg_DiskSpaceRequirements")));
            controls.emplace_back(Control(dialog_name, "List", CONTROL_TYPE::VolumeCostList(), 8, 55, 358, 125, 393223, "", installerStrings.get("IDS__IsFeatureDetailsDlg_Numbers")));
            controls.emplace_back(Control(dialog_name, "OK", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS__IsFeatureDetailsDlg_OK")));
            return controls;
        }()));
}

void UI::create_FeatureNotSupported_dialog() {
    const auto dialog_name = "FeatureNotSupported";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Back", "Back", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 3, "", installerStrings.get("IDS_BACK")));
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "InteriorBin1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL")));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65539, "", installerStrings.get("IDS__FeatueNotSupportedDlg_DialogDescription")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65539, "", installerStrings.get("IDS__FeatueNotSupportedDlg_DialogTitle")));
            controls.emplace_back(Control(dialog_name, "Next", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 1, "", installerStrings.get("IDS_NEXT")));
            return controls;
        }()));
}

void UI::create_FilesInUse_dialog() {
    const auto dialog_name = "FilesInUse";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL | ATTRIBUTE::KEEP_MODELESS, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Retry", "Retry", "Exit",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "NewBinary1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65539, "", installerStrings.get("IDS__IsFilesInUse_FilesInUseMessage")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgText", CONTROL_TYPE::Text(), 21, 51, 348, 29, 3, "", installerStrings.get("IDS__IsFilesInUse_ApplicationsUsingFiles")));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65539, "", installerStrings.get("IDS__IsFilesInUse_FilesInUse")));
            controls.emplace_back(Control(dialog_name, "Exit", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS__IsFilesInUse_Exit"), "List"));
            controls.emplace_back(Control(dialog_name, "Ignore", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS__IsFilesInUse_Ignore"), "Exit"));
            controls.emplace_back(Control(dialog_name, "List", CONTROL_TYPE::ListBox(), 21, 87, 331, 135, 7, "FileInUseProcess", "", "Retry"));
            controls.emplace_back(Control(dialog_name, "Retry", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 3, "", installerStrings.get("IDS__IsFilesInUse_Retry"), "Ignore"));
            return controls;
        }()));
}

void UI::create_InstallWelcome_dialog() {
    const auto dialog_name = "InstallWelcome";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 1, "", installerStrings.get("IDS_BACK"), "Copyright"));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "Back"));
            controls.emplace_back(Control(dialog_name, "Copyright", CONTROL_TYPE::Text(), 135, 144, 228, 73, 65539, "", installerStrings.get("IDS__IsWelcomeDlg_WarningCopyright"), "Next"));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 0, 234, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Image", CONTROL_TYPE::Bitmap(), 0, 0, 374, 234, 1, "", "NewBinary5"));
            controls.emplace_back(Control(dialog_name, "Next", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS_NEXT"), "Cancel"));
            controls.emplace_back(Control(dialog_name, "TextLine1", CONTROL_TYPE::Text(), 135, 8, 225, 45, 65539, "", installerStrings.get("IDS__IsWelcomeDlg_WelcomeProductName")));
            controls.emplace_back(Control(dialog_name, "TextLine2", CONTROL_TYPE::Text(), 135, 55, 228, 45, 65539, "", installerStrings.get("IDS__IsWelcomeDlg_InstallProductName")));
            return controls;
        }()));
}

void UI::create_LicenseAgreement_dialog() {
    const auto dialog_name = "LicenseAgreement";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Agree", "Next", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Agree", CONTROL_TYPE::RadioButtonGroup(), 8, 190, 291, 40, 3, "AgreeToLicense", "", "Back"));
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 3, "", installerStrings.get("IDS_BACK"), "Next"));
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "NewBinary1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "ISPrintButton"));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65539, "", installerStrings.get("IDS__IsLicenseDlg_ReadLicenseAgreement")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65539, "", installerStrings.get("IDS__IsLicenseDlg_LicenseAgreement")));
            controls.emplace_back(Control(dialog_name, "ISPrintButton", CONTROL_TYPE::PushButton(), 301, 188, 65, 17, 3, "", installerStrings.get("IDS_PRINT_BUTTON"), "Agree"));
            controls.emplace_back(Control(dialog_name, "Memo", CONTROL_TYPE::ScrollableText(), 8, 55, 358, 130, 7, "", "&lt;ISProjectFolder&gt;\\redist\\0409\\eula.rtf"));
            controls.emplace_back(Control(dialog_name, "Next", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS_NEXT"), "Cancel"));
            return controls;
        }()));
}

void UI::create_MaintenanceType_dialog() {
    const auto dialog_name = "MaintenanceType";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "RadioGroup", "Next", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 3, "", installerStrings.get("IDS_BACK"), "Next"));
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "NewBinary1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "RadioGroup"));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65539, "", installerStrings.get("IDS__IsMaintenanceDlg_MaitenanceOptions")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65539, "", installerStrings.get("IDS__IsMaintenanceDlg_ProgramMaintenance")));
            controls.emplace_back(Control(dialog_name, "Ico2", CONTROL_TYPE::Icon(), 35, 75, 24, 24, 5767169, "", "NewBinary7"));
            controls.emplace_back(Control(dialog_name, "Ico3", CONTROL_TYPE::Icon(), 35, 135, 24, 24, 5767169, "", "NewBinary8"));
            controls.emplace_back(Control(dialog_name, "Next", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS_NEXT"), "Cancel"));
            controls.emplace_back(Control(dialog_name, "RadioGroup", CONTROL_TYPE::RadioButtonGroup(), 21, 55, 290, 170, 3, "_IsMaintenance", installerStrings.get("IDS__IsMaintenanceDlg_11"), "Back"));
            controls.emplace_back(Control(dialog_name, "Text2", CONTROL_TYPE::Text(), 80, 75, 260, 35, 3, "", installerStrings.get("IDS__IsMaintenanceDlg_RepairMessage")));
            controls.emplace_back(Control(dialog_name, "Text3", CONTROL_TYPE::Text(), 80, 135, 260, 35, 3, "", installerStrings.get("IDS__IsMaintenanceDlg_RemoveProductName")));
            return controls;
        }()));
}

void UI::create_MaintenanceWelcome_dialog() {
    const auto dialog_name = "MaintenanceWelcome";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 1, "", installerStrings.get("IDS_BACK"), "Next"));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "Back"));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 0, 234, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Image", CONTROL_TYPE::Bitmap(), 0, 0, 374, 234, 1, "", "NewBinary5"));
            controls.emplace_back(Control(dialog_name, "Next", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS_NEXT"), "Cancel"));
            controls.emplace_back(Control(dialog_name, "TextLine1", CONTROL_TYPE::Text(), 135, 8, 225, 45, 65539, "", installerStrings.get("IDS__IsMaintenanceWelcome_WizardWelcome")));
            controls.emplace_back(Control(dialog_name, "TextLine2", CONTROL_TYPE::Text(), 135, 55, 228, 50, 65539, "", installerStrings.get("IDS__IsMaintenanceWelcome_MaintenanceOptionsDescription")));
            return controls;
        }()));
}

void UI::create_MsiRMFilesInUse_dialog() {
    const auto dialog_name = "MsiRMFilesInUse";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL | ATTRIBUTE::KEEP_MODELESS, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "OK", "OK", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "NewBinary1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "Restart"));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65539, "", installerStrings.get("IDS__IsFilesInUse_FilesInUseMessage")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgText", CONTROL_TYPE::Text(), 21, 51, 348, 14, 3, "", installerStrings.get("IDS__IsMsiRMFilesInUse_ApplicationsUsingFiles")));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65539, "", installerStrings.get("IDS__IsFilesInUse_FilesInUse")));
            controls.emplace_back(Control(dialog_name, "List", CONTROL_TYPE::ListBox(), 21, 66, 331, 130, 3, "FileInUseProcess", "", "OK"));
            controls.emplace_back(Control(dialog_name, "OK", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS_OK"), "Cancel"));
            controls.emplace_back(Control(dialog_name, "Restart", CONTROL_TYPE::RadioButtonGroup(), 19, 187, 343, 40, 3, "RestartManagerOption", "", "List"));
            return controls;
        }()));
}

void UI::create_OutOfSpace_dialog() {
    const auto dialog_name = "OutOfSpace";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Resume", "Resume", "Resume",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "NewBinary1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65539, "", installerStrings.get("IDS__IsDiskSpaceDlg_DiskSpace")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgText", CONTROL_TYPE::Text(), 21, 51, 326, 43, 3, "", installerStrings.get("IDS__IsDiskSpaceDlg_HighlightedVolumes")));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65539, "", installerStrings.get("IDS__IsDiskSpaceDlg_OutOfDiskSpace")));
            controls.emplace_back(Control(dialog_name, "List", CONTROL_TYPE::VolumeCostList(), 21, 95, 332, 120, 393223, "", installerStrings.get("IDS__IsDiskSpaceDlg_Numbers")));
            controls.emplace_back(Control(dialog_name, "Resume", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS__IsDiskSpaceDlg_OK")));
            return controls;
        }()));
}

void UI::create_PatchWelcome_dialog() {
    const auto dialog_name = "PatchWelcome";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS__IsPatchDlg_PatchWizard"), "Next", "Next", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 1, "", installerStrings.get("IDS_BACK"), "Next"));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "Back"));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 0, 234, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Image", CONTROL_TYPE::Bitmap(), 0, 0, 374, 234, 1, "", "NewBinary5"));
            controls.emplace_back(Control(dialog_name, "Next", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS__IsPatchDlg_Update"), "Cancel"));
            controls.emplace_back(Control(dialog_name, "TextLine1", CONTROL_TYPE::Text(), 135, 8, 225, 45, 65539, "", installerStrings.get("IDS__IsPatchDlg_WelcomePatchWizard")));
            controls.emplace_back(Control(dialog_name, "TextLine2", CONTROL_TYPE::Text(), 135, 54, 228, 45, 65539, "", installerStrings.get("IDS__IsPatchDlg_PatchClickUpdate")));
            return controls;
        }()));
}

void UI::create_ReadyToInstall_dialog() {
    const auto dialog_name = "ReadyToInstall";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL | ATTRIBUTE::TRACK_DISK_SPACE, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "InstallNow", "InstallNow", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 3, "", installerStrings.get("IDS_BACK"), "InstallNow"));
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "NewBinary1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "Back"));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65539, "", installerStrings.get("IDS__IsVerifyReadyDlg_WizardReady")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgText", CONTROL_TYPE::Text(), 21, 51, 326, 20, 3, "", installerStrings.get("IDS__IsVerifyReadyDlg_ClickInstall")));
            controls.emplace_back(Control(dialog_name, "DlgText1", CONTROL_TYPE::Text(), 21, 70, 330, 24, 3, "", installerStrings.get("IDS__IsVerifyReadyDlg_BackOrCancel")));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65538, "", installerStrings.get("IDS__IsVerifyReadyDlg_ModifyReady")));
            controls.emplace_back(Control(dialog_name, "DlgTitle2", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65538, "", installerStrings.get("IDS__IsVerifyReadyDlg_ReadyRepair")));
            controls.emplace_back(Control(dialog_name, "DlgTitle3", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65538, "", installerStrings.get("IDS__IsVerifyReadyDlg_ReadyInstall")));
            controls.emplace_back(Control(dialog_name, "InstallNow", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS__IsVerifyReadyDlg_Install"), "Cancel"));
            return controls;
        }()));
}

void UI::create_ReadyToRemove_dialog() {
    const auto dialog_name = "ReadyToRemove";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "RemoveNow", "RemoveNow", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 3, "", installerStrings.get("IDS_BACK"), "RemoveNow"));
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "NewBinary1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "Back"));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65539, "", installerStrings.get("IDS__IsVerifyRemoveAllDlg_ChoseRemoveProgram")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgText", CONTROL_TYPE::Text(), 21, 51, 326, 24, 3, "", installerStrings.get("IDS__IsVerifyRemoveAllDlg_ClickRemove")));
            controls.emplace_back(Control(dialog_name, "DlgText1", CONTROL_TYPE::Text(), 21, 79, 330, 23, 3, "", installerStrings.get("IDS__IsVerifyRemoveAllDlg_ClickBack")));
            controls.emplace_back(Control(dialog_name, "DlgText2", CONTROL_TYPE::Text(), 21, 102, 330, 24, 3));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65539, "", installerStrings.get("IDS__IsVerifyRemoveAllDlg_RemoveProgram")));
            controls.emplace_back(Control(dialog_name, "RemoveNow", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS__IsVerifyRemoveAllDlg_Remove"), "Cancel"));
            return controls;
        }()));
}

void UI::create_SetupCompleteError_dialog() {
    const auto dialog_name = "SetupCompleteError";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Finish", "Finish", "Finish",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 1, "", installerStrings.get("IDS_BACK"), "Finish"));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 1, "", installerStrings.get("IDS_CANCEL"), "Back"));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 0, 234, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Finish", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS__IsFatalError_Finish"), "Cancel"));
            controls.emplace_back(Control(dialog_name, "FinishText1", CONTROL_TYPE::Text(), 135, 80, 228, 50, 65539, "", installerStrings.get("IDS__IsFatalError_NotModified")));
            controls.emplace_back(Control(dialog_name, "FinishText2", CONTROL_TYPE::Text(), 135, 135, 228, 25, 65539, "", installerStrings.get("IDS__IsFatalError_ClickFinish")));
            controls.emplace_back(Control(dialog_name, "Image", CONTROL_TYPE::Bitmap(), 0, 0, 374, 234, 1, "", "NewBinary5"));
            controls.emplace_back(Control(dialog_name, "RestContText1", CONTROL_TYPE::Text(), 135, 80, 228, 50, 65539, "", installerStrings.get("IDS__IsFatalError_KeepOrRestore")));
            controls.emplace_back(Control(dialog_name, "RestContText2", CONTROL_TYPE::Text(), 135, 135, 228, 25, 65539, "", installerStrings.get("IDS__IsFatalError_RestoreOrContinueLater")));
            controls.emplace_back(Control(dialog_name, "TextLine1", CONTROL_TYPE::Text(), 135, 8, 225, 45, 65539, "", installerStrings.get("IDS__IsFatalError_WizardCompleted")));
            controls.emplace_back(Control(dialog_name, "TextLine2", CONTROL_TYPE::Text(), 135, 55, 228, 25, 65539, "", installerStrings.get("IDS__IsFatalError_WizardInterrupted")));
            return controls;
        }()));
}

void UI::create_SetupCompleteSuccess_dialog() {
    const auto dialog_name = "SetupCompleteSuccess";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "OK", "LaunchProgramCheck", "OK",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 1, "", installerStrings.get("IDS_BACK"), "LaunchProgramCheck"));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 1, "", installerStrings.get("IDS_CANCEL"), "Image"));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 0, 234, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Image", CONTROL_TYPE::Bitmap(), 0, 0, 374, 234, 1, "", "NewBinary5", "Back"));
            controls.emplace_back(Control(dialog_name, "LaunchProgramCheck", CONTROL_TYPE::CheckBox(), 151, 114, 10, 9, 2, "LAUNCHPROGRAM", "", "LaunchProgramText"));
            controls.emplace_back(Control(dialog_name, "LaunchProgramText", CONTROL_TYPE::Text(), 165, 114, 198, 15, 65538, "NewProperty1", installerStrings.get("NEW_STRING2"), "OK"));
            controls.emplace_back(Control(dialog_name, "OK", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS__IsExitDialog_Finish"), "Cancel"));
            controls.emplace_back(Control(dialog_name, "RebootText", CONTROL_TYPE::Text(), 135, 140, 225, 35, 65538, "", installerStrings.get("NEW_STRING28")));
            controls.emplace_back(Control(dialog_name, "RepairText", CONTROL_TYPE::Text(), 135, 178, 225, 52, 65538, "", installerStrings.get("NEW_STRING29")));
            controls.emplace_back(Control(dialog_name, "TextLine1", CONTROL_TYPE::Text(), 135, 8, 225, 45, 65539, "", installerStrings.get("IDS__IsExitDialog_WizardCompleted")));
            controls.emplace_back(Control(dialog_name, "TextLine2", CONTROL_TYPE::Text(), 135, 55, 228, 45, 65538, "", installerStrings.get("IDS__IsExitDialog_InstallSuccess")));
            controls.emplace_back(Control(dialog_name, "TextLine3", CONTROL_TYPE::Text(), 135, 55, 228, 45, 65538, "", installerStrings.get("IDS__IsExitDialog_UninstallSuccess")));
            controls.emplace_back(Control(dialog_name, "UpdateTextLine1", CONTROL_TYPE::Text(), 134, 30, 228, 45, 65538, "", installerStrings.get("IDS__IsExitDialog_Update_SetupFinished")));
            return controls;
        }()));
}

void UI::create_SetupConfig_dialog() {
    const auto dialog_name = "SetupConfig";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("ID_STRING18"), "Advanced", "CheckBox4", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Advanced", CONTROL_TYPE::PushButton(), 301, 209, 66, 17, 3, "", installerStrings.get("NEW_STRING1"), "Back"));
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 3, "", installerStrings.get("ID_STRING14"), "CheckBox4"));
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "InteriorBin1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Branding1", CONTROL_TYPE::Text(), 4, 229, 50, 13, 3, "", installerStrings.get("ID_STRING19")));
            controls.emplace_back(Control(dialog_name, "Branding2", CONTROL_TYPE::Text(), 3, 228, 50, 13, 65537, "", installerStrings.get("ID_STRING20")));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("ID_STRING15")));
            controls.emplace_back(Control(dialog_name, "CheckBox2", CONTROL_TYPE::CheckBox(), 21, 127, 331, 13, 1, "ENABLESCREENSAVER", installerStrings.get("NEW_STRING22"), "CheckBox3"));
            controls.emplace_back(Control(dialog_name, "CheckBox3", CONTROL_TYPE::CheckBox(), 21, 143, 331, 13, 1, "ENABLEPROTECTEDAPPLICATIONEXECUTION3", installerStrings.get("NEW_STRING24"), "Advanced"));
            controls.emplace_back(Control(dialog_name, "CheckBox4", CONTROL_TYPE::CheckBox(), 21, 185, 331, 13, 1, "ENABLEUSEBYALLUSERS", installerStrings.get("NEW_STRING25"), "CheckBox2"));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65539, "", installerStrings.get("ID_STRING17")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 12, 5, 292, 25, 65539, "", installerStrings.get("ID_STRING16")));
            controls.emplace_back(Control(dialog_name, "Icon1", CONTROL_TYPE::Icon(), 21, 52, 24, 24, 5767169, "", "NewBinary12"));
            controls.emplace_back(Control(dialog_name, "Icon2", CONTROL_TYPE::Icon(), 21, 87, 24, 24, 5767169, "", "NewBinary12"));
            controls.emplace_back(Control(dialog_name, "Next", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("ID_STRING13")));
            controls.emplace_back(Control(dialog_name, "Text1", CONTROL_TYPE::Text(), 57, 65, 240, 13, 3, "_BrowseInstallProperty", installerStrings.get("NEW_STRING16")));
            controls.emplace_back(Control(dialog_name, "Text2", CONTROL_TYPE::Text(), 57, 52, 290, 12, 3, "NewProperty1", installerStrings.get("NEW_STRING17")));
            controls.emplace_back(Control(dialog_name, "Text3", CONTROL_TYPE::Text(), 57, 100, 240, 13, 3, "_BrowseDataProperty1", installerStrings.get("NEW_STRING18")));
            controls.emplace_back(Control(dialog_name, "Text4", CONTROL_TYPE::Text(), 21, 202, 267, 22, 3, "NewProperty211", installerStrings.get("NEW_STRING27")));
            controls.emplace_back(Control(dialog_name, "Text5", CONTROL_TYPE::Text(), 57, 87, 290, 11, 3, "NewProperty21", installerStrings.get("NEW_STRING21")));
            controls.emplace_back(Control(dialog_name, "Text6", CONTROL_TYPE::Text(), 34, 159, 328, 25, 1, "", installerStrings.get("NEW_STRING30")));
            return controls;
        }()));
}

void UI::create_SetupConfigAdvanced_dialog() {
    const auto dialog_name = "SetupConfigAdvanced";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("ID_STRING26"), "Next", "CheckBox4", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 3, "", installerStrings.get("ID_STRING22"), "ChangeInstall"));
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "InteriorBin1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Branding1", CONTROL_TYPE::Text(), 4, 229, 50, 13, 3, "", installerStrings.get("ID_STRING27")));
            controls.emplace_back(Control(dialog_name, "Branding2", CONTROL_TYPE::Text(), 3, 228, 50, 13, 65537, "", installerStrings.get("ID_STRING28")));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("ID_STRING23"), "ChangeData"));
            controls.emplace_back(Control(dialog_name, "ChangeData", CONTROL_TYPE::PushButton(), 301, 100, 66, 17, 3, "", installerStrings.get("NEW_STRING8"), "Back"));
            controls.emplace_back(Control(dialog_name, "ChangeInstall", CONTROL_TYPE::PushButton(), 301, 65, 66, 17, 3, "", installerStrings.get("NEW_STRING5"), "CheckBox4"));
            controls.emplace_back(Control(dialog_name, "CheckBox2", CONTROL_TYPE::CheckBox(), 21, 127, 331, 13, 3, "ENABLESCREENSAVER", installerStrings.get("NEW_STRING12"), "CheckBox3"));
            controls.emplace_back(Control(dialog_name, "CheckBox3", CONTROL_TYPE::CheckBox(), 21, 143, 331, 13, 3, "ENABLEPROTECTEDAPPLICATIONEXECUTION3", installerStrings.get("NEW_STRING13"), "Next"));
            controls.emplace_back(Control(dialog_name, "CheckBox4", CONTROL_TYPE::CheckBox(), 21, 210, 331, 13, 3, "ENABLEUSEBYALLUSERS", installerStrings.get("NEW_STRING15"), "CheckBox2"));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65539, "", installerStrings.get("ID_STRING25")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65539, "", installerStrings.get("ID_STRING24")));
            controls.emplace_back(Control(dialog_name, "Icon1", CONTROL_TYPE::Icon(), 21, 52, 24, 24, 5767169, "", "NewBinary12"));
            controls.emplace_back(Control(dialog_name, "Icon2", CONTROL_TYPE::Icon(), 21, 87, 24, 24, 5767169, "", "NewBinary12"));
            controls.emplace_back(Control(dialog_name, "Next", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("ID_STRING21"), "Cancel"));
            controls.emplace_back(Control(dialog_name, "Text1", CONTROL_TYPE::Text(), 57, 65, 240, 13, 3, "_BrowseInstallProperty", installerStrings.get("NEW_STRING6")));
            controls.emplace_back(Control(dialog_name, "Text2", CONTROL_TYPE::Text(), 57, 52, 290, 11, 3, "NewProperty1", installerStrings.get("NEW_STRING7")));
            controls.emplace_back(Control(dialog_name, "Text3", CONTROL_TYPE::Text(), 57, 100, 240, 13, 3, "_BrowseDataProperty", installerStrings.get("NEW_STRING9")));
            controls.emplace_back(Control(dialog_name, "Text4", CONTROL_TYPE::Text(), 57, 87, 290, 11, 3, "NewProperty2", installerStrings.get("NEW_STRING10")));
            controls.emplace_back(Control(dialog_name, "Text5", CONTROL_TYPE::Text(), 34, 158, 328, 44, 3, "", "***IS_STRING_NOT_DEFINED***"));
            controls.emplace_back(Control(dialog_name, "Text6", CONTROL_TYPE::Text(), 34, 158, 328, 44, 3, "NewProperty1", installerStrings.get("NEW_STRING31")));
            return controls;
        }()));
}

void UI::create_SetupError_dialog() {
    const auto dialog_name = "SetupError";
    dialogs.emplace_back(Dialog(dialog_name, 50, 10, 270, 110, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL | ATTRIBUTE::MINIMIZE | ATTRIBUTE::ATTRIBUTE_ERROR, installerStrings.get("IDS__IsErrorDlg_InstallerInfo"), "ErrorText", "O", "C",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "A", CONTROL_TYPE::PushButton(), 192, 80, 66, 17, 3, "", installerStrings.get("IDS__IsErrorDlg_Abort")));
            controls.emplace_back(Control(dialog_name, "C", CONTROL_TYPE::PushButton(), 192, 80, 66, 17, 3, "", installerStrings.get("IDS_CANCEL2")));
            controls.emplace_back(Control(dialog_name, "ErrorText", CONTROL_TYPE::Text(), 50, 15, 200, 50, 3, "", installerStrings.get("IDS__IsErrorDlg_ErrorText")));
            controls.emplace_back(Control(dialog_name, "I", CONTROL_TYPE::PushButton(), 192, 80, 66, 17, 3, "", installerStrings.get("IDS__IsErrorDlg_Ignore")));
            controls.emplace_back(Control(dialog_name, "N", CONTROL_TYPE::PushButton(), 192, 80, 66, 17, 3, "", installerStrings.get("IDS__IsErrorDlg_NO")));
            controls.emplace_back(Control(dialog_name, "O", CONTROL_TYPE::PushButton(), 192, 80, 66, 17, 3, "", installerStrings.get("IDS__IsErrorDlg_OK")));
            controls.emplace_back(Control(dialog_name, "R", CONTROL_TYPE::PushButton(), 192, 80, 66, 17, 3, "", installerStrings.get("IDS__IsErrorDlg_Retry")));
            controls.emplace_back(Control(dialog_name, "WarningIcon", CONTROL_TYPE::Icon(), 15, 15, 24, 24, 5242881, "", "NewBinary4"));
            controls.emplace_back(Control(dialog_name, "Y", CONTROL_TYPE::PushButton(), 192, 80, 66, 17, 3, "", installerStrings.get("IDS__IsErrorDlg_Yes")));
            return controls;
        }()));
}

void UI::create_SetupInitialization_dialog() {
    const auto dialog_name = "SetupInitialization";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::MINIMIZE | ATTRIBUTE::VISIBLE, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Cancel", "Cancel", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "ActionData", CONTROL_TYPE::Text(), 135, 125, 228, 12, 65539, "", installerStrings.get("IDS__IsInitDlg_1")));
            controls.emplace_back(Control(dialog_name, "ActionText", CONTROL_TYPE::Text(), 135, 109, 220, 36, 65539, "", installerStrings.get("IDS__IsInitDlg_2")));
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 1, "", installerStrings.get("IDS_BACK")));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 0, 234, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Image", CONTROL_TYPE::Bitmap(), 0, 0, 374, 234, 1, "", "NewBinary5"));
            controls.emplace_back(Control(dialog_name, "Next", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 1, "", installerStrings.get("IDS_NEXT")));
            controls.emplace_back(Control(dialog_name, "TextLine1", CONTROL_TYPE::Text(), 135, 8, 225, 45, 65539, "", installerStrings.get("IDS__IsInitDlg_WelcomeWizard")));
            controls.emplace_back(Control(dialog_name, "TextLine2", CONTROL_TYPE::Text(), 135, 55, 228, 30, 65539, "", installerStrings.get("IDS__IsInitDlg_PreparingWizard")));
            return controls;
        }()));
}

void UI::create_SetupInterrupted_dialog() {
    const auto dialog_name = "SetupInterrupted";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Finish", "Finish", "Finish",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 1, "", installerStrings.get("IDS_BACK")));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 1, "", installerStrings.get("IDS_CANCEL")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 0, 234, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Finish", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS__IsUserExit_Finish")));
            controls.emplace_back(Control(dialog_name, "FinishText1", CONTROL_TYPE::Text(), 135, 80, 228, 50, 65539, "", installerStrings.get("IDS__IsUserExit_NotModified")));
            controls.emplace_back(Control(dialog_name, "FinishText2", CONTROL_TYPE::Text(), 135, 135, 228, 25, 65539, "", installerStrings.get("IDS__IsUserExit_ClickFinish")));
            controls.emplace_back(Control(dialog_name, "Image", CONTROL_TYPE::Bitmap(), 0, 0, 374, 234, 1, "", "NewBinary5"));
            controls.emplace_back(Control(dialog_name, "RestContText1", CONTROL_TYPE::Text(), 135, 80, 228, 50, 65539, "", installerStrings.get("IDS__IsUserExit_KeepOrRestore")));
            controls.emplace_back(Control(dialog_name, "RestContText2", CONTROL_TYPE::Text(), 135, 135, 228, 25, 65539, "", installerStrings.get("IDS__IsUserExit_RestoreOrContinue")));
            controls.emplace_back(Control(dialog_name, "TextLine1", CONTROL_TYPE::Text(), 135, 8, 225, 45, 65539, "", installerStrings.get("IDS__IsUserExit_WizardCompleted")));
            controls.emplace_back(Control(dialog_name, "TextLine2", CONTROL_TYPE::Text(), 135, 55, 228, 25, 65539, "", installerStrings.get("IDS__IsUserExit_WizardInterrupted")));
            return controls;
        }()));
}

void UI::create_SetupProgress_dialog() {
    const auto dialog_name = "SetupProgress";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::MINIMIZE | ATTRIBUTE::VISIBLE, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Cancel", "Cancel", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "ActionProgress95", CONTROL_TYPE::ProgressBar(), 59, 113, 275, 12, 65537, "", installerStrings.get("IDS__IsProgressDlg_ProgressDone")));
            controls.emplace_back(Control(dialog_name, "ActionText", CONTROL_TYPE::Text(), 59, 100, 275, 12, 3, "", installerStrings.get("IDS__IsProgressDlg_2")));
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 1, "", installerStrings.get("IDS_BACK"), "Next"));
            controls.emplace_back(Control(dialog_name, "Banner", CONTROL_TYPE::Bitmap(), 0, 0, 374, 44, 1, "", "NewBinary1"));
            controls.emplace_back(Control(dialog_name, "BannerLine", CONTROL_TYPE::Line(), 0, 44, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "Back"));
            controls.emplace_back(Control(dialog_name, "DlgDesc", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65538, "", installerStrings.get("IDS__IsProgressDlg_UninstallingFeatures2")));
            controls.emplace_back(Control(dialog_name, "DlgDesc2", CONTROL_TYPE::Text(), 21, 23, 292, 25, 65538, "", installerStrings.get("IDS__IsProgressDlg_UninstallingFeatures")));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 326, 0, 1));
            controls.emplace_back(Control(dialog_name, "DlgText", CONTROL_TYPE::Text(), 59, 51, 275, 30, 65538, "", installerStrings.get("IDS__IsProgressDlg_WaitUninstall2")));
            controls.emplace_back(Control(dialog_name, "DlgText2", CONTROL_TYPE::Text(), 59, 51, 275, 30, 65538, "", installerStrings.get("IDS__IsProgressDlg_WaitUninstall")));
            controls.emplace_back(Control(dialog_name, "DlgTitle", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65538, "", installerStrings.get("IDS__IsProgressDlg_InstallingProductName")));
            controls.emplace_back(Control(dialog_name, "DlgTitle2", CONTROL_TYPE::Text(), 13, 6, 292, 25, 65538, "", installerStrings.get("IDS__IsProgressDlg_Uninstalling")));
            controls.emplace_back(Control(dialog_name, "LbSec", CONTROL_TYPE::Text(), 172, 139, 32, 12, 2, "", installerStrings.get("IDS__IsProgressDlg_SecHidden")));
            controls.emplace_back(Control(dialog_name, "LbStatus", CONTROL_TYPE::Text(), 59, 85, 70, 12, 3, "", installerStrings.get("IDS__IsProgressDlg_Status")));
            controls.emplace_back(Control(dialog_name, "Next", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 1, "", installerStrings.get("IDS_NEXT"), "Cancel"));
            controls.emplace_back(Control(dialog_name, "SetupIcon", CONTROL_TYPE::Icon(), 21, 51, 24, 24, 5242881, "", "NewBinary9"));
            controls.emplace_back(Control(dialog_name, "ShowTime", CONTROL_TYPE::Text(), 155, 139, 17, 12, 2, "", installerStrings.get("IDS__IsProgressDlg_Hidden")));
            controls.emplace_back(Control(dialog_name, "TextTime", CONTROL_TYPE::Text(), 59, 139, 96, 12, 2, "", installerStrings.get("IDS__IsProgressDlg_HiddenTimeRemaining")));
            return controls;
        }()));
}

void UI::create_SetupResume_dialog() {
    const auto dialog_name = "SetupResume";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 1, "", installerStrings.get("IDS_BACK"), "Next"));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "Back"));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 0, 234, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Image", CONTROL_TYPE::Bitmap(), 0, 0, 374, 234, 1, "", "NewBinary5"));
            controls.emplace_back(Control(dialog_name, "Next", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS_NEXT"), "Cancel"));
            controls.emplace_back(Control(dialog_name, "PreselectedText", CONTROL_TYPE::Text(), 135, 55, 228, 45, 65539, "", installerStrings.get("IDS__IsResumeDlg_WizardResume")));
            controls.emplace_back(Control(dialog_name, "ResumeText", CONTROL_TYPE::Text(), 135, 46, 228, 45, 65539, "", installerStrings.get("IDS__IsResumeDlg_ResumeSuspended")));
            controls.emplace_back(Control(dialog_name, "TextLine1", CONTROL_TYPE::Text(), 135, 8, 225, 45, 65539, "", installerStrings.get("IDS__IsResumeDlg_Resuming")));
            return controls;
        }()));
}

void UI::create_SplashBitmap_dialog() {
    const auto dialog_name = "SplashBitmap";
    dialogs.emplace_back(Dialog(dialog_name, 50, 50, 374, 266, ATTRIBUTE::VISIBLE | ATTRIBUTE::MODAL, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"), "Next", "Next", "Cancel",
        [&]() -> auto {
            std::vector<Control> controls;
            controls.emplace_back(Control(dialog_name, "Back", CONTROL_TYPE::PushButton(), 164, 243, 66, 17, 1, "", installerStrings.get("IDS_BACK"), "Next"));
            controls.emplace_back(Control(dialog_name, "Cancel", CONTROL_TYPE::PushButton(), 301, 243, 66, 17, 3, "", installerStrings.get("IDS_CANCEL"), "Back"));
            controls.emplace_back(Control(dialog_name, "DlgLine", CONTROL_TYPE::Line(), 48, 234, 374, 0, 1));
            controls.emplace_back(Control(dialog_name, "Image", CONTROL_TYPE::Bitmap(), 13, 12, 349, 211, 1, "", "NewBinary19"));
            controls.emplace_back(Control(dialog_name, "Next", CONTROL_TYPE::PushButton(), 230, 243, 66, 17, 3, "", installerStrings.get("IDS_NEXT"), "Cancel"));
            return controls;
        }()));
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
