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

#include "InstallUISequenceTable.h"

std::string InstallUISequenceTable::generate() const {
    std::vector<Action> values;

    values.emplace_back("AppSearch", 400);
    values.emplace_back("CARestoreExecutionState", 1352);
    values.emplace_back("CARestoreSetupState", 6);
    values.emplace_back("CCPSearch", "CCP_TEST", 500);
    values.emplace_back("CostFinalize", 1000);
    values.emplace_back("CostInitialize", 800);
    values.emplace_back("ExecuteAction", 1300);
    values.emplace_back("FileCost", 900);
    values.emplace_back("FindRelatedProducts", 430);
    values.emplace_back("ISPreventDowngrade", "ISFOUNDNEWERPRODUCTVERSION", 450);
    values.emplace_back("ISSetAllUsers", "Not Installed", 10);
    values.emplace_back("ISSetupFilesCleanup", 1302);
    values.emplace_back("ISSetupFilesExtract", 3);
    values.emplace_back("InstallWelcome", "Not Installed And(Not PATCH Or IS_MAJOR_UPGRADE)", 1210);
    values.emplace_back("IsolateComponents", 950);
    values.emplace_back("LaunchConditions", "Not Installed", 410);
    values.emplace_back("MaintenanceWelcome", "Installed And Not RESUME And Not Preselected And Not PATCH", 1230);
    values.emplace_back("MigrateFeatureStates", 1200);
    values.emplace_back("PatchWelcome", "PATCH And Not IS_MAJOR_UPGRADE", 1205);
    values.emplace_back("RMCCPSearch", "Not CCP_SUCCESS And CCP_TEST", 600);
    values.emplace_back("ResolveSource", "Not Installed And Not PATCH", 990);
    values.emplace_back("SetARPReadme", 1002);
    values.emplace_back("SetAllUsersProfileNT", "VersionNT = 400", 970);
    values.emplace_back("SetupCompleteError", -3);
    values.emplace_back("SetupCompleteSuccess", -1);
    values.emplace_back("SetupInitialization", 420);
    values.emplace_back("SetupInterrupted", -2);
    values.emplace_back("SetupProgress", 1240);
    values.emplace_back("SetupResume", "Installed And(RESUME Or Preselected) And Not PATCH", 1220);
    values.emplace_back("ValidateProductID", 700);
    values.emplace_back("setAllUsersProfile2K", "VersionNT >= 500", 980);
    values.emplace_back("setUserProfileNT", "VersionNT", 960);

    return Generator::generate({ { "Action", "s72" }, { "Condition", "S255" }, { "Sequence", "I2" } }, { "InstallUISequence", "Action" }, values);
}
