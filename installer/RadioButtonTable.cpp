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

#include "RadioButtonTable.h"
#include "ValidationTable.h"

RadioButtonTable::RadioButtonTable(const nlohmann::json& json, const InstallerStrings& installerStrings) {
    std::cout << "Loading RadioButtonTable..." << std::endl;
    for (const auto& item : json) {
        properties.emplace_back(item, installerStrings);
    }
}

bool RadioButtonTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating RadioButtonTable..." << std::endl;
    const auto sql_create = "CREATE TABLE `RadioButton` (`Property` CHAR(72) NOT NULL, `Order` SHORT NOT NULL, `Value` CHAR(64) NOT NULL, `X` SHORT NOT NULL, "
        "`Y` SHORT NOT NULL, `Width` SHORT NOT NULL, `Height` SHORT NOT NULL, `Text` CHAR(64) LOCALIZABLE, `Help` CHAR(50) LOCALIZABLE PRIMARY KEY `Property`, `Order`)";
    const auto sql_insert = "INSERT INTO `RadioButton` (`Property`, `Order`, `Value`, `X`, `Y`, `Width`, `Height`, `Text`, `Help`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("RadioButton", "Property", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "A named property to be tied to this radio button. All the buttons tied to the same property become part of the same group.");
    records.emplace_back("RadioButton", "Order", "N", 1, 32767, "", "", "", "", "A positive integer used to determine the ordering of the items within one list..The integers do not have to be consecutive.");
    records.emplace_back("RadioButton", "Value", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Formatted", "", "The value string associated with this button. Selecting the button will set the associated property to this value.");
    records.emplace_back("RadioButton", "X", "N", 0, 32767, "", "", "", "", "The horizontal coordinate of the upper left corner of the bounding rectangle of the radio button.");
    records.emplace_back("RadioButton", "Y", "N", 0, 32767, "", "", "", "", "The vertical coordinate of the upper left corner of the bounding rectangle of the radio button.");
    records.emplace_back("RadioButton", "Width", "N", 0, 32767, "", "", "", "", "The width of the button.");
    records.emplace_back("RadioButton", "Height", "N", 0, 32767, "", "", "", "", "The height of the button.");
    records.emplace_back("RadioButton", "Text", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Text", "", "The visible title to be assigned to the radio button.");
    records.emplace_back("RadioButton", "Help", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Text", "", "The help strings used with the button. The text is optional.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, properties);
}
