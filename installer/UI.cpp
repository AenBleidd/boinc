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
    //		<row><td>AdminChangeFolder</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Tail</td><td>OK</td><td>Cancel</td><td>Install Point Browse</td><td/><td>0</td><td/></row>
    Dialog dialog("AdminChangeFolder", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_AdminNetworkLocation_dialog() {
    //		<row><td>AdminNetworkLocation</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>InstallNow</td><td>InstallNow</td><td>Cancel</td><td>Network Location</td><td/><td>0</td><td/></row>
    Dialog dialog("AdminNetworkLocation", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_AdminWelcome_dialog() {
    //		<row><td>AdminWelcome</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Next</td><td>Next</td><td>Cancel</td><td>Administration Welcome</td><td/><td>0</td><td/></row>
    Dialog dialog("AdminWelcome", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_CancelSetup_dialog() {
    //		<row><td>CancelSetup</td><td>50</td><td>50</td><td>260</td><td>85</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>No</td><td>No</td><td>No</td><td>Cancel</td><td/><td>0</td><td/></row>
    Dialog dialog("CancelSetup", 50, 50, 260, 85, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_ChangeFolderData_dialog() {
    //		<row><td>ChangeFolderData</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Tail</td><td>OK</td><td>Cancel</td><td>Browse</td><td/><td>0</td><td/></row>
    Dialog dialog("ChangeFolderData", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_ChangeFolderInstall_dialog() {
    //		<row><td>ChangeFolderInstall</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Tail</td><td>OK</td><td>Cancel</td><td>Browse</td><td/><td>0</td><td/></row>
    Dialog dialog("ChangeFolderInstall", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_DiskSpaceRequirements_dialog() {
    //		<row><td>DiskSpaceRequirements</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>OK</td><td>OK</td><td>OK</td><td>Feature Details</td><td/><td>0</td><td/></row>
    Dialog dialog("DiskSpaceRequirements", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_FeatureNotSupported_dialog() {
    //		<row><td>FeatureNotSupported</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Back</td><td>Back</td><td>Cancel</td><td>Interior</td><td/><td>0</td><td/></row>
    Dialog dialog("FeatureNotSupported", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_FilesInUse_dialog() {
    //		<row><td>FilesInUse</td><td>50</td><td>50</td><td>374</td><td>266</td><td>19</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Retry</td><td>Retry</td><td>Exit</td><td>Files in Use</td><td/><td>0</td><td/></row>
    Dialog dialog("FilesInUse", 50, 50, 374, 266, 19, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_InstallWelcome_dialog() {
    //		<row><td>InstallWelcome</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Next</td><td>Next</td><td>Cancel</td><td>Welcome Panel</td><td/><td>0</td><td/></row>
    Dialog dialog("InstallWelcome", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_LicenseAgreement_dialog() {
    //		<row><td>LicenseAgreement</td><td>50</td><td>50</td><td>374</td><td>266</td><td>2</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Agree</td><td>Next</td><td>Cancel</td><td>License Agreement</td><td/><td>0</td><td/></row>
    Dialog dialog("LicenseAgreement", 50, 50, 374, 266, 2, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_MaintenanceType_dialog() {
    //		<row><td>MaintenanceType</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>RadioGroup</td><td>Next</td><td>Cancel</td><td>Change, Reinstall, Remove</td><td/><td>0</td><td/></row>
    Dialog dialog("MaintenanceType", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_MaintenanceWelcome_dialog() {
    //		<row><td>MaintenanceWelcome</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Next</td><td>Next</td><td>Cancel</td><td>Maintenance Welcome</td><td/><td>0</td><td/></row>
    Dialog dialog("MaintenanceWelcome", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_MsiRMFilesInUse_dialog() {
    //		<row><td>MsiRMFilesInUse</td><td>50</td><td>50</td><td>374</td><td>266</td><td>19</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>OK</td><td>OK</td><td>Cancel</td><td>RestartManager Files in Use</td><td/><td>0</td><td/></row>
    Dialog dialog("MsiRMFilesInUse", 50, 50, 374, 266, 19, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_OutOfSpace_dialog() {
    //		<row><td>OutOfSpace</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Resume</td><td>Resume</td><td>Resume</td><td>Out Of Disk Space</td><td/><td>0</td><td/></row>
    Dialog dialog("OutOfSpace", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_PatchWelcome_dialog() {
    //		<row><td>PatchWelcome</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>##IDS__IsPatchDlg_PatchWizard##</td><td>Next</td><td>Next</td><td>Cancel</td><td>Patch Panel</td><td/><td>0</td><td/></row>
    Dialog dialog("PatchWelcome", 50, 50, 374, 266, 3, installerStrings.get("IDS__IsPatchDlg_PatchWizard"));
    dialogs.emplace_back(dialog);
}

void UI::create_ReadyToInstall_dialog() {
    //		<row><td>ReadyToInstall</td><td>50</td><td>50</td><td>374</td><td>266</td><td>35</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>InstallNow</td><td>InstallNow</td><td>Cancel</td><td>Ready to Install</td><td/><td>0</td><td/></row>
    Dialog dialog("ReadyToInstall", 50, 50, 374, 266, 35, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_ReadyToRemove_dialog() {
    //		<row><td>ReadyToRemove</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>RemoveNow</td><td>RemoveNow</td><td>Cancel</td><td>Verify Remove</td><td/><td>0</td><td/></row>
    Dialog dialog("ReadyToRemove", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_SetupCompleteError_dialog() {
    //		<row><td>SetupCompleteError</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Finish</td><td>Finish</td><td>Finish</td><td>Fatal Error</td><td/><td>0</td><td/></row>
    Dialog dialog("SetupCompleteError", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_SetupCompleteSuccess_dialog() {
    //		<row><td>SetupCompleteSuccess</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>OK</td><td>LaunchProgramCheck</td><td>OK</td><td>Exit</td><td/><td>0</td><td/></row>
    Dialog dialog("SetupCompleteSuccess", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_SetupConfig_dialog() {
    //		<row><td>SetupConfig</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>##ID_STRING18##</td><td>Advanced</td><td>CheckBox4</td><td>Cancel</td><td>Interior</td><td/><td>0</td><td/></row>
    Dialog dialog("SetupConfig", 50, 50, 374, 266, 3, installerStrings.get("ID_STRING18"));
    dialogs.emplace_back(dialog);
}

void UI::create_SetupConfigAdvanced_dialog() {
    //		<row><td>SetupConfigAdvanced</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>##ID_STRING26##</td><td>Next</td><td>CheckBox4</td><td>Cancel</td><td>Interior</td><td/><td>0</td><td/></row>
    Dialog dialog("SetupConfigAdvanced", 50, 50, 374, 266, 3, installerStrings.get("ID_STRING26"));
    dialogs.emplace_back(dialog);
}

void UI::create_SetupError_dialog() {
    //		<row><td>SetupError</td><td>50</td><td>10</td><td>270</td><td>110</td><td>65543</td><td>##IDS__IsErrorDlg_InstallerInfo##</td><td>ErrorText</td><td>O</td><td>C</td><td>Error</td><td/><td>0</td><td/></row>
    Dialog dialog("SetupError", 50, 10, 270, 110, 65543, installerStrings.get("IDS__IsErrorDlg_InstallerInfo"));
    dialogs.emplace_back(dialog);
}

void UI::create_SetupInitialization_dialog() {
    //		<row><td>SetupInitialization</td><td>50</td><td>50</td><td>374</td><td>266</td><td>5</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Cancel</td><td>Cancel</td><td>Cancel</td><td>Setup Initialization</td><td/><td>0</td><td/></row>
    Dialog dialog("SetupInitialization", 50, 50, 374, 266, 5, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_SetupInterrupted_dialog() {
    //		<row><td>SetupInterrupted</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Finish</td><td>Finish</td><td>Finish</td><td>User Exit</td><td/><td>0</td><td/></row>
    Dialog dialog("SetupInterrupted", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_SetupProgress_dialog() {
    //		<row><td>SetupProgress</td><td>50</td><td>50</td><td>374</td><td>266</td><td>5</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Cancel</td><td>Cancel</td><td>Cancel</td><td>Progress</td><td/><td>0</td><td/></row>
    Dialog dialog("SetupProgress", 50, 50, 374, 266, 5, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_SetupResume_dialog() {
    //		<row><td>SetupResume</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Next</td><td>Next</td><td>Cancel</td><td>Resume</td><td/><td>0</td><td/></row>
    Dialog dialog("SetupResume", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

void UI::create_SplashBitmap_dialog() {
    //		<row><td>SplashBitmap</td><td>50</td><td>50</td><td>374</td><td>266</td><td>3</td><td>installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD")</td><td>Next</td><td>Next</td><td>Cancel</td><td>Welcome Bitmap</td><td/><td>0</td><td/></row>
    Dialog dialog("SplashBitmap", 50, 50, 374, 266, 3, installerStrings.get("IDS_PRODUCTNAME_INSTALLSHIELD"));
    dialogs.emplace_back(dialog);
}

const std::vector<Dialog>& UI::get_dialogs() const noexcept {
    return dialogs;
}