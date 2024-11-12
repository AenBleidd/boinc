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

#include <fstream>
#include <iostream>

#include "SummaryInformationTable.h"
#include "ActionTextTable.h"
#include "AdminExecuteSequenceTable.h"
#include "AdminUISequencetable.h"
#include "AdvtExecuteSequenceTable.h"
#include "BinaryTable.h"
#include "CheckboxTable.h"
#include "ControlTable.h"
#include "CustomActionTable.h"
#include "DialogTable.h"
#include "DirectoryTable.h"
#include "ErrorTable.h"
#include "FeatureTable.h"
#include "InstallExecuteSequenceTable.h"
#include "InstallUISequenceTable.h"
#include "LaunchConditionTable.h"
#include "PropertyTable.h"
#include "RadioButtonTable.h"
#include "TextStyleTable.h"
#include "UITextTable.h"
#include "ValidationTable.h"

#include "Installer.h"

bool Installer::load(const std::filesystem::path& json) {
    if (!installer_strings.load(json.parent_path())) {
        return false;
    }

    std::ifstream file(json);
    if (!file.is_open()) {
        std::cerr << "Could not open file " << json << std::endl;
        return false;
    }

    nlohmann::json j;
    try {
        file >> j;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    return load_from_json(j, json.parent_path());
}

bool Installer::load_from_json(const nlohmann::json& json, const std::filesystem::path& path)
{
    try {
        if (json.contains("Summary") && !json["Summary"].is_null()) {
            tables["Summary"] = std::make_shared<SummaryInformationTable>(json["Summary"], installer_strings);
        }
        if (json.contains("ActionText") && !json["ActionText"].is_null()) {
            tables["ActionText"] = std::make_shared<ActionTextTable>(json["ActionText"], installer_strings);
        }
        if (json.contains("AdminExecuteSequence") && !json["AdminExecuteSequence"].is_null()) {
            tables["AdminExecuteSequence"] = std::make_shared<AdminExecuteSequenceTable>(json["AdminExecuteSequence"]);
        }
        if (json.contains("AdminUISequence") && !json["AdminUISequence"].is_null()) {
            tables["AdminUISequence"] = std::make_shared<AdminUISequenceTable>(json["AdminUISequence"]);
        }
        if (json.contains("AdvtExecuteSequence") && !json["AdvtExecuteSequence"].is_null()) {
            tables["AdvtExecuteSequence"] = std::make_shared<AdvtExecuteSequenceTable>(json["AdvtExecuteSequence"]);
        }
        if (json.contains("Binary") && !json["Binary"].is_null()) {
            tables["Binary"] = std::make_shared<BinaryTable>(json["Binary"], path);
        }
        if (json.contains("Checkbox") && !json["Checkbox"].is_null()) {
            tables["Checkbox"] = std::make_shared<CheckboxTable>(json["Checkbox"]);
        }
        if (json.contains("CustomAction") && !json["CustomAction"].is_null()) {
            tables["CustomAction"] = std::make_shared<CustomActionTable>(json["CustomAction"]);
        }
        if (json.contains("Dialog") && !json["Dialog"].is_null()) {
            tables["Dialog"] = std::make_shared<DialogTable>(json["Dialog"], installer_strings);
        }
        if (json.contains("Directory") && !json["Directory"].is_null()) {
            tables["Directory"] = std::make_shared<DirectoryTable>(json["Directory"], path);
        }
        if (json.contains("Error") && !json["Error"].is_null()) {
            tables["Error"] = std::make_shared<ErrorTable>(json["Error"], installer_strings);
        }
        if (json.contains("Feature") && !json["Feature"].is_null()) {
            tables["Feature"] = std::make_shared<FeatureTable>(json["Feature"], installer_strings);
        }
        if (json.contains("InstallExecuteSequence") && !json["InstallExecuteSequence"].is_null()) {
            tables["InstallExecuteSequence"] = std::make_shared<InstallExecuteSequenceTable>(json["InstallExecuteSequence"]);
        }
        if (json.contains("InstallUISequence") && !json["InstallUISequence"].is_null()) {
            tables["InstallUISequence"] = std::make_shared<InstallUISequenceTable>(json["InstallUISequence"]);
        }
        if (json.contains("LaunchCondition") && !json["LaunchCondition"].is_null()) {
            tables["LaunchCondition"] = std::make_shared<LaunchConditionTable>(json["LaunchCondition"], installer_strings);
        }
        if (json.contains("Property") && !json["Property"].is_null()) {
            tables["Property"] = std::make_shared<PropertyTable>(json["Property"], installer_strings);
        }
        if (json.contains("RadioButton") && !json["RadioButton"].is_null()) {
            tables["RadioButton"] = std::make_shared<RadioButtonTable>(json["RadioButton"], installer_strings);
        }
        if (json.contains("TextStyle") && !json["TextStyle"].is_null()) {
            tables["TextStyle"] = std::make_shared<TextStyleTable>(json["TextStyle"]);
        }
        if (json.contains("UIText") && !json["UIText"].is_null()) {
            tables["UIText"] = std::make_shared<UITextTable>(json["UIText"], installer_strings);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
    return true;
}

bool Installer::create_msi(const std::filesystem::path& msi) {
    MSIHANDLE hDatabase;

    try {
        if (std::filesystem::exists(msi)) {
            if (!std::filesystem::remove(msi)) {
                std::cerr << "Failed to remove existing file " << msi << std::endl;
                return false;
            }
        }
        auto result = MsiOpenDatabase(msi.string().c_str(), MSIDBOPEN_CREATE, &hDatabase);
        if (result != ERROR_SUCCESS) {
            std::cerr << "MsiOpenDatabase failed with error " << result << std::endl;
            return false;
        }

        // _Validation table should always be first
        if (!ValidationTable().generate(hDatabase)) {
            std::cerr << "Failed to write _Validation table" << std::endl;
            return false;
        }

        for (const auto& table : tables) {
            if (!table.second->generate(hDatabase)) {
                std::cerr << "Failed to write table " << table.first << std::endl;
                return false;
            }
        }

        result = MsiDatabaseCommit(hDatabase);
        if (result != ERROR_SUCCESS) {
            std::cerr << "MsiDatabaseCommit failed: " << result << std::endl;
            return false;
        }

        result = MsiCloseHandle(hDatabase);
        if (result != ERROR_SUCCESS) {
            std::cerr << "MsiCloseHandle failed: " << result << std::endl;
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    return true;
}
