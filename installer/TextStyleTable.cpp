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

#include "TextStyleTable.h"
#include "ValidationTable.h"

TextStyleTable::TextStyleTable(const nlohmann::json& json) {
    std::cout << "Loading TextStyleTable..." << std::endl;

    for (const auto& textStyle : json) {
        textStyles.emplace_back(textStyle);
    }
}

bool TextStyleTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating TextStyleTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `TextStyle` (`TextStyle` CHAR(72) NOT NULL, `FaceName` CHAR(32) NOT NULL, `Size` SHORT NOT NULL, `Color` LONG, `StyleBits` SHORT PRIMARY KEY `TextStyle`)";
    const auto sql_insert = "INSERT INTO `TextStyle` (`TextStyle`, `FaceName`, `Size`, `Color`, `StyleBits`) VALUES (?, ?, ?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("TextStyle", "TextStyle", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "Name of the style. The primary key of this table. This name is embedded in the texts to indicate a style change.");
    records.emplace_back("TextStyle", "FaceName", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Text", "", "A string indicating the name of the font used. Required. The string must be at most 31 characters long.");
    records.emplace_back("TextStyle", "Size", "N", 0, 32767, "", "", "", "", "The size of the font used. This size is given in our units (1/12 of the system font height). Assuming that the system font is set to 12 point size, this is equivalent to the point size.");
    records.emplace_back("TextStyle", "Color", "Y", 0, 16777215, "", "", "", "", "A long integer indicating the color of the string in the RGB format (Red, Green, Blue each 0-255, RGB = R + 256*G + 256^2*B).");
    records.emplace_back("TextStyle", "StyleBits", "Y", 0, 15, "", "", "", "", "A combination of style bits.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, textStyles);
}
