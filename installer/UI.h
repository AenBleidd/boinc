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

#pragma once

#include "Dialog.h"
#include "InstallerStrings.h"

class UI {
public:
    explicit UI(const InstallerStrings& is);
    ~UI() = default;

    const std::vector<Dialog>& get_dialogs() const noexcept;
    std::vector<Control> get_controls() const;
private:
    void create_dialogs();

    void create_AdminChangeFolder_dialog();
    void create_AdminNetworkLocation_dialog();
    void create_AdminWelcome_dialog();
    void create_CancelSetup_dialog();
    void create_ChangeFolderData_dialog();
    void create_ChangeFolderInstall_dialog();
    void create_DiskSpaceRequirements_dialog();
    void create_FeatureNotSupported_dialog();
    void create_FilesInUse_dialog();
    void create_InstallWelcome_dialog();
    void create_LicenseAgreement_dialog();
    void create_MaintenanceType_dialog();
    void create_MaintenanceWelcome_dialog();
    void create_MsiRMFilesInUse_dialog();
    void create_OutOfSpace_dialog();
    void create_PatchWelcome_dialog();
    void create_ReadyToInstall_dialog();
    void create_ReadyToRemove_dialog();
    void create_SetupCompleteError_dialog();
    void create_SetupCompleteSuccess_dialog();
    void create_SetupConfig_dialog();
    void create_SetupConfigAdvanced_dialog();
    void create_SetupError_dialog();
    void create_SetupInitialization_dialog();
    void create_SetupInterrupted_dialog();
    void create_SetupProgress_dialog();
    void create_SetupResume_dialog();
    void create_SplashBitmap_dialog();

    std::vector<Dialog> dialogs;
    const InstallerStrings& installerStrings;
};
