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

#include "AdminUISequenceTable.h"
#include "ValidationTable.h"

AdminUISequenceTable::AdminUISequenceTable(const nlohmann::json& json) {
    std::cout << "Loading AdminUISequenceTable..." << std::endl;
    for (const auto& value : json) {
        actions.emplace_back(value);
    }
}

bool AdminUISequenceTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating AdminUISequenceTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `AdminUISequence` (`Action` CHAR(72) NOT NULL, `Condition` CHAR(255), `Sequence` SHORT PRIMARY KEY `Action`)";
    const auto sql_insert = "INSERT INTO `AdminUISequence` (`Action`, `Condition`, `Sequence`) VALUES (?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("AdminUISequence", "Action", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "Name of action to invoke, either in the engine or the handler DLL.");
    records.emplace_back("AdminUISequence", "Condition", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Condition", "", "Optional expression which skips the action if evaluates to expFalse. If the expression syntax is invalid, the engine will terminate, returning iesBadActionData.");
    records.emplace_back("AdminUISequence", "Sequence", "Y", -4, 32767, "", "", "", "", "Number that determines the sort order in which the actions are to be executed. Leave blank to suppress action.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, actions);
}
