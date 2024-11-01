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
#include <tuple>

#include "SummaryInformationTable.h"
#include "ActionTextTable.h"
#include "AdminExecuteSequenceTable.h"
#include "AdminUISequencetable.h"
#include "AdvtExecuteSequenceTable.h"
#include "ControlTable.h"
#include "DialogTable.h"
#include "InstallExecuteSequenceTable.h"
#include "InstallUISequenceTable.h"

#include "Installer.h"

Installer::Installer() noexcept{
}

bool Installer::load() {
    if (!installer_strings.load()) {
        return false;
    }

    const auto filename = std::string("../installer/boinc.json");
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file " << filename << std::endl;
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

    return load_from_json(j);
}

bool Installer::load_from_json(const nlohmann::json& json)
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
        if (json.contains("Dialog") && !json["Dialog"].is_null()) {
            tables["Dialog"] = std::make_shared<DialogTable>(json["Dialog"], installer_strings);
        }
        if (json.contains("InstallExecuteSequence") && !json["InstallExecuteSequence"].is_null()) {
            tables["InstallExecuteSequence"] = std::make_shared<InstallExecuteSequenceTable>(json["InstallExecuteSequence"]);
        }
        if (json.contains("InstallUISequence") && !json["InstallUISequence"].is_null()) {
            tables["InstallUISequence"] = std::make_shared<InstallUISequenceTable>(json["InstallUISequence"]);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
    return true;
}

bool Installer::create_msi() {
    MSIHANDLE hDatabase;

    try {
        auto result = MsiOpenDatabase("boinc.msi", MSIDBOPEN_CREATE, &hDatabase);
        if (result != ERROR_SUCCESS) {
            std::cerr << "MsiOpenDatabase failed with error " << result << std::endl;
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
