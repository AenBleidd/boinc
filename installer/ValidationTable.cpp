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

#include "ValidationTable.h"

bool ValidationTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating ValidationTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `_Validation` (`Table` CHAR(32) NOT NULL, `Column` CHAR(32) NOT NULL, `Nullable` CHAR(4) NOT NULL, `MinValue` LONG, `MaxValue` LONG, `KeyTable` CHAR(255), `KeyColumn` SHORT, `Category` CHAR(32), `Set` CHAR(255), `Description` CHAR(255) PRIMARY KEY `Table`, `Column`)";
    const auto sql_insert = "INSERT INTO `_Validation` (`Table`, `Column`, `Nullable`, `MinValue`, `MaxValue`, `KeyTable`, `KeyColumn`, `Category`, `Set`, `Description`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("_Validation", "Table", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "Name of table");
    records.emplace_back("_Validation", "Column", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "Name of column");
    records.emplace_back("_Validation", "Nullable", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "", "Y;N;@", "Whether the column is nullable");
    records.emplace_back("_Validation", "MinValue", "Y", -2147483647, 2147483647, "", "", "", "", "Minimum value allowed");
    records.emplace_back("_Validation", "MaxValue", "Y", -2147483647, 2147483647, "", "", "", "", "Maximum value allowed");
    records.emplace_back("_Validation", "KeyTable", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "For foreign key, Name of table to which data must link");
    records.emplace_back("_Validation", "KeyColumn", "Y", 1, 32, "", "", "", "", "Column to which foreign key connects");
    records.emplace_back("_Validation", "Category", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "", "Text;Formatted;Template;Condition;Guid;Path;Version;Language;Identifier;Binary;UpperCase;LowerCase;Filename;Paths;AnyPath;WildCardFilename;RegPath;KeyFormatted;CustomSource;Property;Cabinet;Shortcut;URL", "String category");
    records.emplace_back("_Validation", "Set", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Text", "", "Set of values that are permitted");
    records.emplace_back("_Validation", "Description", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Text", "", "Description of column");

    return Generator::generate(hDatabase, sql_create, sql_insert, records);
}

bool ValidationTable::insert(MSIHANDLE hDatabase, const std::vector<Validation>& records) {
    std::cout << "Adding validation data..." << std::endl;
    const auto sql_insert = "INSERT INTO `_Validation` (`Table`, `Column`, `Nullable`, `MinValue`, `MaxValue`, `KeyTable`, `KeyColumn`, `Category`, `Set`, `Description`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    return Generator::generate(hDatabase, {}, sql_insert, records);
}
