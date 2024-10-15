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

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

#include <windows.h>
#include <objbase.h>

#include <nlohmann/json.hpp>

class GuidHelper {
public:
    GuidHelper() = default;
    ~GuidHelper() = default;
    static std::string generate_guid() {
        GUID guid;
        if (CoCreateGuid(&guid) != S_OK) {
            throw std::runtime_error("Failed to create GUID");
        }

        std::ostringstream oss;
        oss << std::uppercase << std::hex << std::setfill('0')
            << '{'
            << std::setw(8) << guid.Data1 << '-'
            << std::setw(4) << guid.Data2 << '-'
            << std::setw(4) << guid.Data3 << '-'
            << std::setw(2) << static_cast<int>(guid.Data4[0])
            << std::setw(2) << static_cast<int>(guid.Data4[1]) << '-'
            << std::setw(2) << static_cast<int>(guid.Data4[2])
            << std::setw(2) << static_cast<int>(guid.Data4[3])
            << std::setw(2) << static_cast<int>(guid.Data4[4])
            << std::setw(2) << static_cast<int>(guid.Data4[5])
            << std::setw(2) << static_cast<int>(guid.Data4[6])
            << std::setw(2) << static_cast<int>(guid.Data4[7])
            << '}';

        return oss.str();
    }
};

class Record {
public:
    Record() = default;
    virtual ~Record() = default;
    virtual std::string get() const = 0;
};

template <typename K, typename V>
class KeyValue : public Record {
public:
    explicit KeyValue(const K& key, const V& value) : key(key), value(value) {};
    ~KeyValue() = default;
    std::string get() const override {
        std::ostringstream oss;
        oss << key << "\t" << value << "\n";
        return oss.str();
    }
private:
    K key;
    V value;
};

class ActionText : public Record {
public:
    explicit ActionText(const std::string& action, const std::string& description, const std::string& tmplt = "") : action(action), description(description), tmplt(tmplt) {};
    ~ActionText() = default;
    std::string get() const override {
        std::ostringstream oss;
        oss << action << "\t" << description << "\t" << tmplt << "\n";
        return oss.str();
    }
private:
    std::string action;
    std::string description;
    std::string tmplt;
};

class Action : public Record {
public:
    explicit Action(const std::string& action, const std::string& condition, const int sequence) : action(action), condition(condition), sequence(sequence) {};
    explicit Action(const std::string& action, const int sequence) : action(action), condition(""), sequence(sequence) {};
    ~Action() = default;
    std::string get() const override {
        std::ostringstream oss;
        oss << action << "\t" << condition << "\t" << sequence << "\n";
        return oss.str();
    }
private:
    std::string action;
    std::string condition;
    int sequence;
};

template <typename V>
class Generator {
public:
    Generator() = default;
    virtual ~Generator() = default;
    virtual std::string generate(const std::vector<std::string>& columns, const std::vector<std::string>& types, const std::vector<std::string>& keys, const std::vector<V>& values) const {
        std::string result;
        for (const auto& column : columns) {
            result += column + "\t";
        }
        result += "\n";
        for (const auto& type : types) {
            result += type + "\t";
        }
        result += "\n";
        for (const auto& key : keys) {
            result += key + "\t";
        }
        result += "\n";
        for (const auto& value : values) {
            result += value.get();
        }
        return result;
    }
    virtual std::string generate() const = 0;
};

class InstallerStrings {
public:
    InstallerStrings() noexcept = default;
    ~InstallerStrings() = default;

    std::string get(const std::string& key) {
        return strings.at(key);
    };
    bool load() {
        const auto filename = std::string("../installer/locale/en.json");
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Could not open file " << filename << std::endl;
            return false;
        }
        nlohmann::json j;
        file >> j;
        return load_from_json(j);
    }
private:
    std::map<std::string, std::string> strings;

    bool load_from_json(const nlohmann::json& json) {
        for (const auto& item : json) {
            const auto& id = item.at("Id");
            const auto& value = item.at("Value");
            if (!id.is_null() && !value.is_null()) {
                strings.insert(std::make_pair(id.get<std::string>(), value.get<std::string>()));
            }
            else if (id.is_null()) {
                std::cerr << "WARNING: Skipped record with no Id specified." << std::endl;
            }
            else if (value.is_null()) {
                std::cerr << "WARNING: Skipped [" << id.get<std::string>() << "] record with no Value specified" << std::endl;
            }
        }
        return true;
    }
};

class SummaryInformationTable : public Generator<KeyValue<int, std::string>> {
public:
    SummaryInformationTable(InstallerStrings& installerStrings) noexcept : installerStrings(installerStrings) {};
    ~SummaryInformationTable() = default;
    std::string generate() const override {
        const auto now = std::chrono::system_clock::now();
        const auto now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm;
        localtime_s(&now_tm, &now_time_t);
        std::ostringstream oss;
        oss << std::put_time(&now_tm, "%Y/%m/%d %H:%M:%S");

        constexpr auto codepage = 1252;
        constexpr auto pagecount = 200;
        constexpr auto wordcount = 0;
        constexpr auto security = 1;
        constexpr auto charcount = 0;
        const auto title = installerStrings.get("COMPANY_PRODUCT");
        const auto subject = installerStrings.get("COMPANY_PRODUCT_SUBJECT");
        const auto author = installerStrings.get("COMPANY_NAME");
        const auto keywords = std::string("BOINC");
        const auto comments = installerStrings.get("IDS_FEATURE_BOINC_DESCRIPTION");
        const auto arch = std::string("AMD64;1033");
        const auto lastauthor = std::string("BOINC");
        const auto revision = GuidHelper::generate_guid();
        const auto lastprinted = oss.str();
        const auto createdtm = oss.str();
        const auto lastsavedtm = oss.str();
        const auto appname = std::string("BOINC");

        std::vector<KeyValue<int, std::string>> values;
        values.emplace_back(1, std::to_string(codepage));
        values.emplace_back(2, title);
        values.emplace_back(3, subject);
        values.emplace_back(4, author);
        values.emplace_back(5, keywords);
        values.emplace_back(6, comments);
        values.emplace_back(7, arch);
        values.emplace_back(8, lastauthor);
        values.emplace_back(9, revision);
        values.emplace_back(11, lastprinted);
        values.emplace_back(12, createdtm);
        values.emplace_back(13, lastsavedtm);
        values.emplace_back(14, std::to_string(pagecount));
        values.emplace_back(15, std::to_string(wordcount));
        values.emplace_back(16, std::to_string(charcount));
        values.emplace_back(18, appname);
        values.emplace_back(19, std::to_string(security));

        return Generator::generate({ "PropertyId", "Value" }, { "i2", "l255" }, { "_SummaryInformation", "PropertyId" }, values);
    }
private:
    InstallerStrings& installerStrings;
};

class ActionTextTable : public Generator<ActionText> {
public:
    ActionTextTable(InstallerStrings& installerStrings) noexcept : installerStrings(installerStrings) {};
    ~ActionTextTable() = default;
    std::string generate() const override {
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

        return Generator::generate({ "Action", "Description", "Template" }, { "s72", "L0", "L0" }, { "ActionText", "Action" }, values);
    }
private:
    InstallerStrings& installerStrings;
};

class AdminExecuteSequenceTable : public Generator<Action> {
public:
    AdminExecuteSequenceTable() = default;
    ~AdminExecuteSequenceTable() = default;
    std::string generate() const override {
        std::vector<Action> values;

        values.emplace_back("CASetBOINCDataProjects", 1300);
        values.emplace_back("CASetBOINCDataSlots", 1200);
        values.emplace_back("CostFinalize", 1000);
        values.emplace_back("CostInitialize", 800);
        values.emplace_back("FileCost", 900);
        values.emplace_back("InstallAdminPackage", 3900);
        values.emplace_back("InstallFiles", 4000);
        values.emplace_back("InstallFinalize", 6600);
        values.emplace_back("InstallInitialize", 1500);
        values.emplace_back("InstallValidate", 1400);
        values.emplace_back("ScheduleReboot", "ISSCHEDULEREBOOT", 4010);

        return Generator::generate({ "Action", "Condition", "Sequence" }, { "s72", "S255", "I2" }, { "AdminExecuteSequence", "Action" }, values);
    }
};

class AdminUISequenceTable : public Generator<Action> {
public:
    AdminUISequenceTable() = default;
    ~AdminUISequenceTable() = default;
    std::string generate() const override {
        std::vector<Action> values;

        values.emplace_back("AdminWelcome", 1010);
        values.emplace_back("CostFinalize", 1000);
        values.emplace_back("CostInitialize", 800);
        values.emplace_back("ExecuteAction", 1300);
        values.emplace_back("FileCost", 900);
        values.emplace_back("SetupCompleteError", -3);
        values.emplace_back("SetupCompleteSuccess", -1);
        values.emplace_back("SetupInitialization", 50);
        values.emplace_back("SetupInterrupted", -2);
        values.emplace_back("SetupProgress", 1020);

        return Generator::generate({ "Action", "Condition", "Sequence" }, { "s72", "S255", "I2" }, { "AdminUISequence", "Action" }, values);
    }
};

class AdvtExecuteSequenceTable : public Generator<Action> {
public:
    AdvtExecuteSequenceTable() = default;
    ~AdvtExecuteSequenceTable() = default;
    std::string generate() const override {
        std::vector<Action> values;

        values.emplace_back("CostFinalize", 1000);
        values.emplace_back("CostInitialize", 800);
        values.emplace_back("CreateShortcuts", 4500);
        values.emplace_back("InstallFinalize", 6600);
        values.emplace_back("InstallInitialize", 1500);
        values.emplace_back("InstallValidate", 1400);
        values.emplace_back("MsiPublishAssemblies", 6250);
        values.emplace_back("PublishComponents", 6200);
        values.emplace_back("PublishFeatures", 6300);
        values.emplace_back("PublishProduct", 6400);
        values.emplace_back("RegisterClassInfo", 4600);
        values.emplace_back("RegisterExtensionInfo", 4700);
        values.emplace_back("RegisterMIMEInfo", 4900);
        values.emplace_back("RegisterProgIdInfo", 4800);
        values.emplace_back("RegisterTypeLibraries", 4910);
        values.emplace_back("ScheduleReboot", "ISSCHEDULEREBOOT", 6410);

        return Generator::generate({ "Action", "Condition", "Sequence" }, { "s72", "S255", "I2" }, { "AdvtExecuteSequence", "Action" }, values);
    }
};

class InstallExecuteSequenceTable : public Generator<Action> {
public:
    InstallExecuteSequenceTable() = default;
    ~InstallExecuteSequenceTable() = default;
    std::string generate() const override {
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

        return Generator::generate({ "Action", "Condition", "Sequence" }, { "s72", "S255", "I2" }, { "InstallExecuteSequence", "Action" }, values);
    }
};

class InstallUISequenceTable : public Generator<Action> {
public:
    InstallUISequenceTable() = default;
    ~InstallUISequenceTable() = default;
    std::string generate() const override {
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

        return Generator::generate({ "Action", "Condition", "Sequence" }, { "s72", "S255", "I2" }, { "InstallUISequence", "Action" }, values);
    }

};

class Installer {
public:
    Installer() = default;
    ~Installer() = default;
    void load() {
        installerStrings.load();
    }
    void generate() {
        SummaryInformationTable si(installerStrings);
        std::cout << "==== SummaryInformation ====" << std::endl;
        std::cout << si.generate() << std::endl;
        ActionTextTable at(installerStrings);
        std::cout << "==== ActionText Table ====" << std::endl;
        std::cout << at.generate() << std::endl;
        AdminExecuteSequenceTable aes;
        std::cout << "==== AdminExecuteSequence Table ====" << std::endl;
        std::cout << aes.generate() << std::endl;
        AdminUISequenceTable aus;
        std::cout << "==== AdminUISequence Table ====" << std::endl;
        std::cout << aus.generate() << std::endl;
        AdvtExecuteSequenceTable aes2;
        std::cout << "==== AdvtExecuteSequence Table ====" << std::endl;
        std::cout << aes2.generate() << std::endl;

        InstallExecuteSequenceTable ies;
        std::cout << "==== InstallExecuteSequence Table ====" << std::endl;
        std::cout << ies.generate() << std::endl;
        InstallUISequenceTable ius;
        std::cout << "==== InstallUISequence Table ====" << std::endl;
        std::cout << ius.generate() << std::endl;
    }
private:
    InstallerStrings installerStrings;
};

int main(int argc, char** argv) {
    Installer installer;
    installer.load();
    installer.generate();
    return 0;
}
