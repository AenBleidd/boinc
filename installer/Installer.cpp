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

#include "Installer.h"

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

bool Installer::generate() const
{
    try {
        std::cout << "==== SummaryInformation ====" << std::endl;
        std::cout << summary_information_table.generate() << std::endl;
        std::cout << "==== ActionText ====" << std::endl;
        std::cout << action_text_table.generate() << std::endl;
        std::cout << "==== AdminExecuteSequence ====" << std::endl;
        std::cout << admin_execute_sequence_table.generate() << std::endl;
        std::cout << "==== AdminUISequence ====" << std::endl;
        std::cout << admin_ui_sequence_table.generate() << std::endl;
        std::cout << "==== AdvtExecuteSequence ====" << std::endl;
        std::cout << advt_execute_sequence_table.generate() << std::endl;
        std::cout << "==== Control ====" << std::endl;
        std::cout << control_table.generate(dialog_table.get()) << std::endl;
        std::cout << "==== ControlCondition ====" << std::endl;
        std::cout << control_condition_table.generate(dialog_table.get()) << std::endl;
        std::cout << "==== Dialog ====" << std::endl;
        std::cout << dialog_table.generate() << std::endl;
        std::cout << "==== InstallExecuteSequence ====" << std::endl;
        std::cout << install_execute_sequence_table.generate() << std::endl;
        std::cout << "==== InstallUISequence ====" << std::endl;
        std::cout << install_ui_sequence_table.generate() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
    return true;
}

bool Installer::load_from_json(const nlohmann::json& json)
{
    auto load_table_with_strings = [&](const std::string& name, auto& table, const InstallerStrings& installer_strings) -> auto {
        if (json.find(name) == json.end()) {
            std::cerr << "Could not find " << name << " in json" << std::endl;
            return false;
        };
        if (!table.load(json.at(name), installer_strings)) {
            std::cerr << "Could not load " << name << " table" << std::endl;
            return false;
        }
        return true;
        };

    auto load_table = [&](const std::string& name, auto& table) -> auto {
        if (json.find(name) == json.end()) {
            std::cerr << "Could not find " << name << " in json" << std::endl;
            return false;
        };
        if (!table.load(json.at(name))) {
            std::cerr << "Could not load " << name << " table" << std::endl;
            return false;
        }
        return true;
        };

    try {
        if (!load_table_with_strings("Summary", summary_information_table, installer_strings)) {
            return false;
        }
        if (!load_table_with_strings("ActionText", action_text_table, installer_strings)) {
            return false;
        }
        if (!load_table("AdminExecuteSequence", admin_execute_sequence_table)) {
            return false;
        }
        if (!load_table("AdminUISequence", admin_ui_sequence_table)) {
            return false;
        }
        if (!load_table("AdvtExecuteSequence", advt_execute_sequence_table)) {
            return false;
        }

        if (!load_table_with_strings("Dialog", dialog_table, installer_strings)) {
            return false;
        }

        if (!load_table("InstallExecuteSequence", install_execute_sequence_table)) {
            return false;
        }
        if (!load_table("InstallUISequence", install_ui_sequence_table)) {
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
    return true;
}
