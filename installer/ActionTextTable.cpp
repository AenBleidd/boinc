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

#include "ActionTextTable.h"

ActionTextTable::ActionTextTable(const InstallerStrings& installerStrings) noexcept : installerStrings(installerStrings) {};
std::string ActionTextTable::generate() const {
    std::vector<ActionText> values;

    values.emplace_back("Advertise", installerStrings.get("IDS_ACTIONTEXT_Advertising"));
    values.emplace_back("AllocateRegistrySpace", installerStrings.get("IDS_ACTIONTEXT_AllocatingRegistry"), installerStrings.get("IDS_ACTIONTEXT_FreeSpace"));
    values.emplace_back("AppSearch", installerStrings.get("IDS_ACTIONTEXT_SearchInstalled"), installerStrings.get("IDS_ACTIONTEXT_PropertySignature"));
    values.emplace_back("BindImage", installerStrings.get("IDS_ACTIONTEXT_BindingExes"), installerStrings.get("IDS_ACTIONTEXT_File"));
    values.emplace_back("CCPSearch", installerStrings.get("IDS_ACTIONTEXT_UnregisterModules"));
    values.emplace_back("CostFinalize", installerStrings.get("IDS_ACTIONTEXT_ComputingSpace3"));
    values.emplace_back("CostInitialize", installerStrings.get("IDS_ACTIONTEXT_ComputingSpace"));
    values.emplace_back("CreateFolders", installerStrings.get("IDS_ACTIONTEXT_CreatingFolders"), installerStrings.get("IDS_ACTIONTEXT_Folder"));
    values.emplace_back("CreateShortcuts", installerStrings.get("IDS_ACTIONTEXT_CreatingShortcuts"), installerStrings.get("IDS_ACTIONTEXT_Shortcut"));
    values.emplace_back("DeleteServices", installerStrings.get("IDS_ACTIONTEXT_DeletingServices"), installerStrings.get("IDS_ACTIONTEXT_Service"));
    values.emplace_back("DuplicateFiles", installerStrings.get("IDS_ACTIONTEXT_CreatingDuplicate"), installerStrings.get("IDS_ACTIONTEXT_FileDirectorySize"));
    values.emplace_back("FileCost", installerStrings.get("IDS_ACTIONTEXT_ComputingSpace2"));
    values.emplace_back("FindRelatedProducts", installerStrings.get("IDS_ACTIONTEXT_SearchForRelated"), installerStrings.get("IDS_ACTIONTEXT_FoundApp"));
    values.emplace_back("GenerateScript", installerStrings.get("IDS_ACTIONTEXT_GeneratingScript"), installerStrings.get("IDS_ACTIONTEXT_1"));
    values.emplace_back("InstallAdminPackage", installerStrings.get("IDS_ACTIONTEXT_CopyingNetworkFiles"), installerStrings.get("IDS_ACTIONTEXT_FileDirSize"));
    values.emplace_back("InstallFiles", installerStrings.get("IDS_ACTIONTEXT_CopyingNewFiles"), installerStrings.get("IDS_ACTIONTEXT_FileDirSize2"));
    values.emplace_back("InstallODBC", installerStrings.get("IDS_ACTIONTEXT_InstallODBC"));
    values.emplace_back("InstallSFPCatalogFile", installerStrings.get("IDS_ACTIONTEXT_InstallingSystemCatalog"), installerStrings.get("IDS_ACTIONTEXT_FileDependencies"));
    values.emplace_back("InstallServices", installerStrings.get("IDS_ACTIONTEXT_InstallServices"), installerStrings.get("IDS_ACTIONTEXT_Service2"));
    values.emplace_back("InstallValidate", installerStrings.get("IDS_ACTIONTEXT_Validating"));
    values.emplace_back("LaunchConditions", installerStrings.get("IDS_ACTIONTEXT_EvaluateLaunchConditions"));
    values.emplace_back("MigrateFeatureStates", installerStrings.get("IDS_ACTIONTEXT_MigratingFeatureStates"), installerStrings.get("IDS_ACTIONTEXT_Application"));
    values.emplace_back("MoveFiles", installerStrings.get("IDS_ACTIONTEXT_MovingFiles"), installerStrings.get("IDS_ACTIONTEXT_FileDirSize3"));
    values.emplace_back("PatchFiles", installerStrings.get("IDS_ACTIONTEXT_PatchingFiles"), installerStrings.get("IDS_ACTIONTEXT_FileDirSize4"));
    values.emplace_back("ProcessComponents", installerStrings.get("IDS_ACTIONTEXT_UpdateComponentRegistration"));
    values.emplace_back("PublishComponents", installerStrings.get("IDS_ACTIONTEXT_PublishingQualifiedComponents"), installerStrings.get("IDS_ACTIONTEXT_ComponentIDQualifier"));
    values.emplace_back("PublishFeatures", installerStrings.get("IDS_ACTIONTEXT_PublishProductFeatures"), installerStrings.get("IDS_ACTIONTEXT_FeatureColon"));
    values.emplace_back("PublishProduct", installerStrings.get("IDS_ACTIONTEXT_PublishProductInfo"));
    values.emplace_back("RMCCPSearch", installerStrings.get("IDS_ACTIONTEXT_SearchingQualifyingProducts"));
    values.emplace_back("RegisterClassInfo", installerStrings.get("IDS_ACTIONTEXT_RegisterClassServer"), installerStrings.get("IDS_ACTIONTEXT_ClassId"));
    values.emplace_back("RegisterComPlus", installerStrings.get("IDS_ACTIONTEXT_RegisteringComPlus"), installerStrings.get("IDS_ACTIONTEXT_AppIdAppTypeRSN"));
    values.emplace_back("RegisterExtensionInfo", installerStrings.get("IDS_ACTIONTEXT_RegisterExtensionServers"), installerStrings.get("IDS_ACTIONTEXT_Extension2"));
    values.emplace_back("RegisterFonts", installerStrings.get("IDS_ACTIONTEXT_RegisterFonts"), installerStrings.get("IDS_ACTIONTEXT_Font"));
    values.emplace_back("RegisterMIMEInfo", installerStrings.get("IDS_ACTIONTEXT_RegisterMimeInfo"), installerStrings.get("IDS_ACTIONTEXT_ContentTypeExtension"));
    values.emplace_back("RegisterProduct", installerStrings.get("IDS_ACTIONTEXT_RegisteringProduct"), installerStrings.get("IDS_ACTIONTEXT_1b"));
    values.emplace_back("RegisterProgIdInfo", installerStrings.get("IDS_ACTIONTEXT_RegisteringProgIdentifiers"), installerStrings.get("IDS_ACTIONTEXT_ProgID2"));
    values.emplace_back("RegisterTypeLibraries", installerStrings.get("IDS_ACTIONTEXT_RegisterTypeLibs"), installerStrings.get("IDS_ACTIONTEXT_LibId"));
    values.emplace_back("RegisterUser", installerStrings.get("IDS_ACTIONTEXT_RegUser"), installerStrings.get("IDS_ACTIONTEXT_1c"));
    values.emplace_back("RemoveDuplicateFiles", installerStrings.get("IDS_ACTIONTEXT_RemovingDuplicates"), installerStrings.get("IDS_ACTIONTEXT_FileDir"));
    values.emplace_back("RemoveEnvironmentStrings", installerStrings.get("IDS_ACTIONTEXT_UpdateEnvironmentStrings"), installerStrings.get("IDS_ACTIONTEXT_NameValueAction2"));
    values.emplace_back("RemoveExistingProducts", installerStrings.get("IDS_ACTIONTEXT_RemoveApps"), installerStrings.get("IDS_ACTIONTEXT_AppCommandLine"));
    values.emplace_back("RemoveFiles", installerStrings.get("IDS_ACTIONTEXT_RemovingFiles"), installerStrings.get("IDS_ACTIONTEXT_FileDir2"));
    values.emplace_back("RemoveFolders", installerStrings.get("IDS_ACTIONTEXT_RemovingFolders"), installerStrings.get("IDS_ACTIONTEXT_Folder1"));
    values.emplace_back("RemoveIniValues", installerStrings.get("IDS_ACTIONTEXT_RemovingIni"), installerStrings.get("IDS_ACTIONTEXT_FileSectionKeyValue"));
    values.emplace_back("RemoveODBC", installerStrings.get("IDS_ACTIONTEXT_RemovingODBC"));
    values.emplace_back("RemoveRegistryValues", installerStrings.get("IDS_ACTIONTEXT_RemovingRegistry"), installerStrings.get("IDS_ACTIONTEXT_KeyName"));
    values.emplace_back("RemoveShortcuts", installerStrings.get("IDS_ACTIONTEXT_RemovingShortcuts"), installerStrings.get("IDS_ACTIONTEXT_Shortcut1"));
    values.emplace_back("Rollback", installerStrings.get("IDS_ACTIONTEXT_RollingBack"), installerStrings.get("IDS_ACTIONTEXT_1d"));
    values.emplace_back("RollbackCleanup", installerStrings.get("IDS_ACTIONTEXT_RemovingBackup"), installerStrings.get("IDS_ACTIONTEXT_File2"));
    values.emplace_back("SelfRegModules", installerStrings.get("IDS_ACTIONTEXT_RegisteringModules"), installerStrings.get("IDS_ACTIONTEXT_FileFolder"));
    values.emplace_back("SelfUnregModules", installerStrings.get("IDS_ACTIONTEXT_UnregisterModules"), installerStrings.get("IDS_ACTIONTEXT_FileFolder2"));
    values.emplace_back("SetODBCFolders", installerStrings.get("IDS_ACTIONTEXT_InitializeODBCDirs"));
    values.emplace_back("ShutdownBOINCManager", installerStrings.get("ID_STRING4"));
    values.emplace_back("StartServices", installerStrings.get("IDS_ACTIONTEXT_StartingServices"), installerStrings.get("IDS_ACTIONTEXT_Service3"));
    values.emplace_back("StopServices", installerStrings.get("IDS_ACTIONTEXT_StoppingServices"), installerStrings.get("IDS_ACTIONTEXT_Service4"));
    values.emplace_back("UnmoveFiles", installerStrings.get("IDS_ACTIONTEXT_RemovingMoved"), installerStrings.get("IDS_ACTIONTEXT_FileDir3"));
    values.emplace_back("UnpublishComponents", installerStrings.get("IDS_ACTIONTEXT_UnpublishQualified"), installerStrings.get("IDS_ACTIONTEXT_ComponentIdQualifier2"));
    values.emplace_back("UnpublishFeatures", installerStrings.get("IDS_ACTIONTEXT_UnpublishProductFeatures"), installerStrings.get("IDS_ACTIONTEXT_Feature"));
    values.emplace_back("UnpublishProduct", installerStrings.get("IDS_ACTIONTEXT_UnpublishingProductInfo"));
    values.emplace_back("UnregisterClassInfo", installerStrings.get("IDS_ACTIONTEXT_UnregisterClassServers"), installerStrings.get("IDS_ACTIONTEXT_ClsID"));
    values.emplace_back("UnregisterComPlus", installerStrings.get("IDS_ACTIONTEXT_UnregisteringComPlus"), installerStrings.get("IDS_ACTIONTEXT_AppId"));
    values.emplace_back("UnregisterExtensionInfo", installerStrings.get("IDS_ACTIONTEXT_UnregisterExtensionServers"), installerStrings.get("IDS_ACTIONTEXT_Extension"));
    values.emplace_back("UnregisterFonts", installerStrings.get("IDS_ACTIONTEXT_UnregisteringFonts"), installerStrings.get("IDS_ACTIONTEXT_Font2"));
    values.emplace_back("UnregisterMIMEInfo", installerStrings.get("IDS_ACTIONTEXT_UnregisteringMimeInfo"), installerStrings.get("IDS_ACTIONTEXT_ContentTypeExtension2"));
    values.emplace_back("UnregisterProgIdInfo", installerStrings.get("IDS_ACTIONTEXT_UnregisteringProgramIds"), installerStrings.get("IDS_ACTIONTEXT_ProgID"));
    values.emplace_back("UnregisterTypeLibraries", installerStrings.get("IDS_ACTIONTEXT_UnregTypeLibs"), installerStrings.get("IDS_ACTIONTEXT_Libid2"));
    values.emplace_back("WriteEnvironmentStrings", installerStrings.get("IDS_ACTIONTEXT_EnvironmentStrings"), installerStrings.get("IDS_ACTIONTEXT_NameValueAction"));
    values.emplace_back("WriteIniValues", installerStrings.get("IDS_ACTIONTEXT_WritingINI"), installerStrings.get("IDS_ACTIONTEXT_FileSectionKeyValue2"));
    values.emplace_back("WriteRegistryValues", installerStrings.get("IDS_ACTIONTEXT_WritingRegistry"), installerStrings.get("IDS_ACTIONTEXT_KeyNameValue"));
    values.emplace_back("caCreateVRoots", installerStrings.get("IDS_ACTIONTEXT_CreatingIISRoots"));
    values.emplace_back("caRemoveVRoots", installerStrings.get("IDS_ACTIONTEXT_RemovingIISRoots"));

    return Generator::generate({ { "Action", "s72" }, { "Description", "L0" }, { "Template", "L0" } }, { "ActionText", "Action" }, values);
}
