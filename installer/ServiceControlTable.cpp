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

#include "ServiceControlTable.h"
#include "ValidationTable.h"

ServiceControlTable::ServiceControlTable(const std::vector<Directory>& directories) {
    for (const auto& directory : directories) {
        for (const auto& component : directory.getComponents()) {
            for (const auto& serviceControl : component.getServiceControls()) {
                values.emplace_back(serviceControl);
            }
        }
    }
}

bool ServiceControlTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating ServiceControlTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `ServiceControl` (`ServiceControl` CHAR(72) NOT NULL, `Name` CHAR(255) NOT NULL LOCALIZABLE, `Event` SHORT NOT NULL, "
        "`Arguments` CHAR(255) LOCALIZABLE, `Wait` SHORT, `Component_` CHAR(72) NOT NULL PRIMARY KEY `ServiceControl`)";
    const auto sql_insert = "INSERT INTO `ServiceControl` (`ServiceControl`, `Name`, `Event`, `Arguments`, `Wait`, `Component_`) VALUES (?, ?, ?, ?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("ServiceControl", "ServiceControl", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "Primary key, non-localized token.");
    records.emplace_back("ServiceControl", "Name", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Formatted", "", "Name of a service. /, \\, comma and space are invalid");
    records.emplace_back("ServiceControl", "Event", "N", 0, 187, "", "", "", "", "Bit field:  Install:  0x1 = Start, 0x2 = Stop, 0x8 = Delete, Uninstall: 0x10 = Start, 0x20 = Stop, 0x80 = Delete");
    records.emplace_back("ServiceControl", "Arguments", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Formatted", "", "Arguments for the service.  Separate by [~].");
    records.emplace_back("ServiceControl", "Wait", "Y", 0, 1, "", "", "", "0;1", "Boolean for whether to wait for the service to fully start");
    records.emplace_back("ServiceControl", "Component_", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Component", "1", "Identifier", "", "Required foreign key into the Component Table that controls the startup of the service");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, values);
}
