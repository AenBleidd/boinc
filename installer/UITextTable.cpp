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

#include "UITextTable.h"
#include "ValidationTable.h"

UITextTable::UITextTable(const nlohmann::json& json, const InstallerStrings& installerStrings) {
    std::cout << "Loading UITextTable.." << std::endl;
    for (const auto& item : json) {
        uiTexts.emplace_back(item, installerStrings);
    }
}

bool UITextTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating UITextTable.." << std::endl;

    const auto sql_create = "CREATE TABLE `UIText` (`Key` CHAR(72) NOT NULL, `Text` CHAR(255) LOCALIZABLE PRIMARY KEY `Key`)";
    const auto sql_insert = "INSERT INTO `UIText` (`Key`, `Text`) VALUES (?, ?)";

    std::vector<Validation> records;
    records.emplace_back("UIText", "Key", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "A unique key that identifies the particular string.");
    records.emplace_back("UIText", "Text", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Text", "", "The localized version of the string.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, uiTexts);
}