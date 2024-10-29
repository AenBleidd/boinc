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

#include "ActionTextTable.h"
#include "Generator.h"

std::string ActionTextTable::generate() const {
    return Generator<ActionText>().generate({ { "Action", "s72" }, { "Description", "L0" }, { "Template", "L0" } }, { "ActionText", "Action" }, values);
}

bool ActionTextTable::load(const nlohmann::json& json, const InstallerStrings& installerStrings)
{
    try {
        for (const auto& item : json) {
            values.emplace_back(item, installerStrings);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading ActionTextTable: " << e.what() << std::endl;
        return false;
    }
    return true;
}
