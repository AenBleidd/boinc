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

#include "ComponentTable.h"
#include "ValidationTable.h"

ComponentTable::ComponentTable(const std::vector<Directory>& directories) {
    for (const auto& directory : directories) {
        for (const auto& component : directory.getComponents()) {
            components.push_back(component);
        }
    }
}

bool ComponentTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating ComponentTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `Component` (`Component` CHAR(72) NOT NULL, `ComponentId` CHAR(38), `Directory_` CHAR(72) NOT NULL, "
        "`Attributes` SHORT NOT NULL, `Condition` CHAR(255), KeyPath CHAR(72) PRIMARY KEY `Component`)";
    const auto sql_insert = "INSERT INTO `Component` (`Component`, `ComponentId`, `Directory_`, `Attributes`, `Condition`, `KeyPath`) VALUES (?, ?, ?, ?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("Component", "Component", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "Primary key used to identify a particular component record.");
    records.emplace_back("Component", "ComponentId", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Guid", "", "A string GUID unique to this component, version, and language.");
    records.emplace_back("Component", "Directory_", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Directory", "1", "Identifier", "", "Required key of a Directory table record. This is actually a property name whose value contains the actual path, set either by the AppSearch action or with the default setting obtained from the Directory table.");
    records.emplace_back("Component", "Attributes", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "", "", "Remote execution option, one of irsEnum");
    records.emplace_back("Component", "Condition", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Condition", "", "A conditional statement that will disable this component if the specified condition evaluates to the 'True' state. If a component is disabled, it will not be installed, regardless of the 'Action' state associated with the component.");
    records.emplace_back("Component", "KeyPath", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "File;Registry;ODBCDataSource", "1", "Identifier", "", "Either the primary key into the File table, Registry table, or ODBCDataSource table. This extract path is stored when the component is installed, and is used to detect the presence of the component and to return the path to it.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, components);
}
