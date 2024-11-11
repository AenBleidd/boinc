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

#include "CustomActionTable.h"
#include "ValidationTable.h"

CustomActionTable::CustomActionTable(const nlohmann::json& json) {
    std::cout << "Loading CustomActionTable..." << std::endl;
    for (const auto& customAction : json) {
        customActions.emplace_back(customAction);
    }
}

bool CustomActionTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating CustomActionTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `CustomAction` (`Action` CHAR(72) NOT NULL, `Type` SHORT NOT NULL, `Source` CHAR(64), `Target` CHAR(255), `ExtendedType` LONG PRIMARY KEY `Action`)";
    const auto sql_insert = "INSERT INTO `CustomAction` (`Action`, `Type`, `Source`, `Target`, `ExtendedType`) VALUES (?, ?, ?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("CustomAction", "Action", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "Primary key, name of action, normally appears in sequence table unless private use.");
    records.emplace_back("CustomAction", "Type", "N", 1, 32767, "", "", "", "", "The numeric custom action type, consisting of source location, code type, entry, option flags.");
    records.emplace_back("CustomAction", "Source", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "CustomSource", "", "The table reference of the source of the code.");
    records.emplace_back("CustomAction", "Target", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Formatted", "", "Excecution parameter, depends on the type of custom action");
    records.emplace_back("CustomAction", "ExtendedType", "Y", 0, 2147483647, "", "", "", "", "The numeric custom action type info flags.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, customActions);
}
