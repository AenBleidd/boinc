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

#include "InstallExecuteSequenceTable.h"

std::string InstallExecuteSequenceTable::generate() const {
    std::vector<Action> values;

    values.emplace_back("AllocateRegistrySpace", "NOT Installed", 1562);
    values.emplace_back("AppSearch", 400);
    values.emplace_back("BindImage", 4300);
    values.emplace_back("CAAnnounceUpgrade", "VersionNT And REMOVE <> \"ALL\"", 1001);
    values.emplace_back("CACleanupOldBinaries", "REMOVE <> \"ALL\"", 796);
    values.emplace_back("CACreateAcctMgrLoginFile", "NOT Installed", 6605);
    values.emplace_back("CACreateBOINCAccounts", "VersionNT And REMOVE <> \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1546);
    values.emplace_back("CACreateBOINCGroups", "VersionNT And REMOVE <> \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1552);
    values.emplace_back("CACreateClientAuthFile", "VersionNT And NOT Installed", 6604);
    values.emplace_back("CACreateProjectInitFile", "NOT Installed", 6606);
    values.emplace_back("CADeleteBOINCAccounts", "VersionNT And REMOVE = \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1551);
    values.emplace_back("CADeleteBOINCGroups", "VersionNT And REMOVE = \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1561);
    values.emplace_back("CAGetAdministratorsGroupName", "VersionNT And REMOVE <> \"ALL\"", 1537);
    values.emplace_back("CAGetUsersGroupName", "VersionNT And REMOVE <> \"ALL\"", 1543);
    values.emplace_back("CAGrantBOINCAdminsRights", "VersionNT And REMOVE <> \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1553);
    values.emplace_back("CAGrantBOINCAdminsVirtualBoxRights", "VersionNT And REMOVE <> \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1555);
    values.emplace_back("CAGrantBOINCMasterRights", "VersionNT And REMOVE <> \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1547);
    values.emplace_back("CAGrantBOINCProjectRights", "VersionNT And REMOVE <> \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1549);
    values.emplace_back("CAGrantBOINCProjectsRights", "VersionNT And REMOVE <> \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1558);
    values.emplace_back("CAGrantBOINCProjectsVirtualBoxRights", "VersionNT And REMOVE <> \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1560);
    values.emplace_back("CAGrantBOINCUsersRights", "VersionNT And REMOVE <> \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1556);
    values.emplace_back("CARestorePermissionBOINCData", "VersionNT And REMOVE = \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 6612);
    values.emplace_back("CARestoreSetupState", "VersionNT And REMOVE = \"ALL\"", 1002);
    values.emplace_back("CARevokeBOINCAdminsRights", "VersionNT And REMOVE = \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1554);
    values.emplace_back("CARevokeBOINCMasterRights", "VersionNT And REMOVE = \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1548);
    values.emplace_back("CARevokeBOINCProjectRights", "VersionNT And REMOVE = \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1550);
    values.emplace_back("CARevokeBOINCProjectsRights", "VersionNT And REMOVE = \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1559);
    values.emplace_back("CARevokeBOINCUsersRights", "VersionNT And REMOVE = \"ALL\" AND ENABLEPROTECTEDAPPLICATIONEXECUTION3 = 1", 1557);
    values.emplace_back("CASaveExecutionState", 6614);
    values.emplace_back("CASaveSetupState", 6613);
    values.emplace_back("CASetBOINCDataProjects", 1004);
    values.emplace_back("CASetBOINCDataSlots", 1003);
    values.emplace_back("CASetPermissionBOINC", "VersionNT And REMOVE <> \"ALL\"", 6607);
    values.emplace_back("CASetPermissionBOINCData", "VersionNT And REMOVE <> \"ALL\"", 6609);
    values.emplace_back("CASetPermissionBOINCDataProjects", "VersionNT And REMOVE <> \"ALL\"", 6610);
    values.emplace_back("CASetPermissionBOINCDataSlots", "VersionNT And REMOVE <> \"ALL\"", 6611);
    values.emplace_back("CAShutdownBOINC", "VersionNT", 403);
    values.emplace_back("CAShutdownBOINCManager", "VersionNT", 404);
    values.emplace_back("CAShutdownBOINCScreensaver", "VersionNT", 408);
    values.emplace_back("CAValidateInstall", "REMOVE <> \"ALL\"", 6602);
    values.emplace_back("CAValidateRebootRequest", "REMOVE <> \"ALL\" AND RETURN_REBOOTREQUESTED = \"1\"", 6603);
    values.emplace_back("CAValidateSetupType", 737);
    values.emplace_back("CCPSearch", "CCP_TEST", 500);
    values.emplace_back("CostFinalize", 1000);
    values.emplace_back("CostInitialize", 800);
    values.emplace_back("CreateFolders", 3700);
    values.emplace_back("CreateShortcuts", 4500);
    values.emplace_back("DeleteServices", "VersionNT", 2000);
    values.emplace_back("DuplicateFiles", 4210);
    values.emplace_back("FileCost", 900);
    values.emplace_back("FindRelatedProducts", "NOT ISSETUPDRIVEN", 420);
    values.emplace_back("ISPreventDowngrade", "ISFOUNDNEWERPRODUCTVERSION", 450);
    values.emplace_back("ISSetAllUsers", "Not Installed", 10);
    values.emplace_back("ISSetupFilesCleanup", 6615);
    values.emplace_back("ISSetupFilesExtract", 3);
    values.emplace_back("InstallFiles", 4000);
    values.emplace_back("InstallFinalize", 6601);
    values.emplace_back("InstallInitialize", 1501);
    values.emplace_back("InstallODBC", 5400);
    values.emplace_back("InstallServices", "VersionNT", 5800);
    values.emplace_back("InstallValidate", 1400);
    values.emplace_back("IsolateComponents", 950);
    values.emplace_back("LaunchConditions", "Not Installed", 410);
    values.emplace_back("MigrateFeatureStates", 1200);
    values.emplace_back("MoveFiles", 3800);
    values.emplace_back("MsiConfigureServices", "VersionMsi >= \"5.00\"", 5801);
    values.emplace_back("MsiPublishAssemblies", 6250);
    values.emplace_back("MsiUnpublishAssemblies", 1750);
    values.emplace_back("PatchFiles", 4090);
    values.emplace_back("ProcessComponents", 1600);
    values.emplace_back("PublishComponents", 6200);
    values.emplace_back("PublishFeatures", 6300);
    values.emplace_back("PublishProduct", 6400);
    values.emplace_back("RMCCPSearch", "Not CCP_SUCCESS And CCP_TEST", 600);
    values.emplace_back("RegisterClassInfo", 4600);
    values.emplace_back("RegisterComPlus", 5700);
    values.emplace_back("RegisterExtensionInfo", 4700);
    values.emplace_back("RegisterFonts", 5300);
    values.emplace_back("RegisterMIMEInfo", 4900);
    values.emplace_back("RegisterProduct", 6100);
    values.emplace_back("RegisterProgIdInfo", 4800);
    values.emplace_back("RegisterTypeLibraries", 5500);
    values.emplace_back("RegisterUser", 6000);
    values.emplace_back("RemoveDuplicateFiles", 3400);
    values.emplace_back("RemoveEnvironmentStrings", 3300);
    values.emplace_back("RemoveExistingProducts", 1410);
    values.emplace_back("RemoveFiles", 3500);
    values.emplace_back("RemoveFolders", 3600);
    values.emplace_back("RemoveIniValues", 3100);
    values.emplace_back("RemoveODBC", 2400);
    values.emplace_back("RemoveRegistryValues", 2600);
    values.emplace_back("RemoveShortcuts", 3200);
    values.emplace_back("ResolveSource", "_IsMaintenance <> \"Remove\"", 850);
    values.emplace_back("ScheduleReboot", "ISSCHEDULEREBOOT", 6410);
    values.emplace_back("SelfRegModules", 5600);
    values.emplace_back("SelfUnregModules", 2200);
    values.emplace_back("SetARPINSTALLLOCATION", "Not Installed", 1010);
    values.emplace_back("SetARPReadme", 1005);
    values.emplace_back("SetODBCFolders", 1100);
    values.emplace_back("StartServices", "VersionNT", 5900);
    values.emplace_back("StopServices", "VersionNT", 1900);
    values.emplace_back("UnpublishComponents", 1700);
    values.emplace_back("UnpublishFeatures", 1800);
    values.emplace_back("UnregisterClassInfo", 2700);
    values.emplace_back("UnregisterComPlus", 2100);
    values.emplace_back("UnregisterExtensionInfo", 2800);
    values.emplace_back("UnregisterFonts", 2500);
    values.emplace_back("UnregisterMIMEInfo", 3000);
    values.emplace_back("UnregisterProgIdInfo", 2900);
    values.emplace_back("UnregisterTypeLibraries", 2300);
    values.emplace_back("ValidateProductID", 700);
    values.emplace_back("WriteEnvironmentStrings", 5200);
    values.emplace_back("WriteIniValues", 5100);
    values.emplace_back("WriteRegistryValues", 5000);

    return Generator::generate({ {"Action", "s72" }, { "Condition", "S255" }, { "Sequence", "I2" } }, { "InstallExecuteSequence", "Action" }, values);
}
