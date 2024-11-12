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

#include "LaunchConditionTable.h"
#include "ValidationTable.h"

LaunchConditionTable::LaunchConditionTable(const nlohmann::json& json, const InstallerStrings& installerStrings) {
    std::cout << "Loading LaunchConditionTable..." << std::endl;

    for (const auto& launchCondition : json) {
        launchConditions.emplace_back(launchCondition, installerStrings);
    }
}

bool LaunchConditionTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating LaunchConditionTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `LaunchCondition` (`Condition` CHAR(255) NOT NULL, `Description` CHAR(255) NOT NULL LOCALIZABLE PRIMARY KEY `Condition`)";
    const auto sql_insert = "INSERT INTO `LaunchCondition` (`Condition`, `Description`) VALUES (?, ?)";

    std::vector<Validation> records;
    records.emplace_back("LaunchCondition", "Condition", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Condition", "", "Expression which must evaluate to TRUE in order for install to commence.");
    records.emplace_back("LaunchCondition", "Description", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Formatted", "", "Localizable text to display when condition fails and install must abort.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, launchConditions);
}
