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

#include "ErrorTable.h"
#include "ValidationTable.h"

ErrorTable::ErrorTable(const nlohmann::json& json, const InstallerStrings& installerStrings) {
    std::cout << "Loading ErrorTable..." << std::endl;

    for (const auto& error : json) {
        errors.emplace_back(error, installerStrings);
    }
}

bool ErrorTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating ErrorTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `Error` (`Error` SHORT NOT NULL, `Message` LONGCHAR LOCALIZABLE PRIMARY KEY `Error`)";
    const auto sql_insert = "INSERT INTO `Error` (`Error`, `Message`) VALUES (?, ?)";

    std::vector<Validation> records;
    records.emplace_back("Error", "Error", "N", 0, 32767, "", "", "", "", "Integer error number, obtained from header file IError(...) macros.");
    records.emplace_back("Error", "Message", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Template", "", "Error formatting template, obtained from user ed. or localizers.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, errors);    
}