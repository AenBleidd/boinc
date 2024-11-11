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
#include "ValidationTable.h"

ActionTextTable::ActionTextTable(const nlohmann::json& json, const InstallerStrings& installerStrings) {
    std::cout << "Loading ActionTextTable..." << std::endl;
    for (const auto& item : json) {
        values.emplace_back(item, installerStrings);
    }
}

bool ActionTextTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating ActionTextTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `ActionText` (`Action` CHAR(72) NOT NULL, `Description` LONGCHAR LOCALIZABLE, `Template` LONGCHAR LOCALIZABLE PRIMARY KEY `Action`)";
    const auto sql_insert = "INSERT INTO `ActionText` (`Action`, `Description`, `Template`) VALUES (?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("ActionText", "Action", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "Name of action to be described.");
    records.emplace_back("ActionText", "Description", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Text", "", "Localized description displayed in progress dialog and log when action is executing.");
    records.emplace_back("ActionText", "Template", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Template", "", "Optional localized format template used to format action data records for display during action execution.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, values);
}
