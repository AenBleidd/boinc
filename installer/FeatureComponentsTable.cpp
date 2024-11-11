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

#include "FeatureComponentsTable.h"
#include "ValidationTable.h"

FeatureComponentsTable::FeatureComponentsTable(const std::vector<Directory>& directories) {
    for (const auto& directory : directories) {
        for (const auto& component : directory.getComponents()) {
            featureComponents.emplace_back(component.getFeatureComponent());
        }
    }
}

bool FeatureComponentsTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating FeatureComponentsTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `FeatureComponents` (`Feature_` CHAR(38) NOT NULL, `Component_` CHAR(72) NOT NULL PRIMARY KEY `Feature_`, `Component_`)";
    const auto sql_insert = "INSERT INTO `FeatureComponents` (`Feature_`, `Component_`) VALUES (?, ?)";

    std::vector<Validation> records;
    records.emplace_back("FeatureComponents", "Feature_", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Feature", "1", "Identifier", "", "Foreign key into Feature table.");
    records.emplace_back("FeatureComponents", "Component_", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Component", "1", "Identifier", "", "Foreign key into Component table.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, featureComponents);
}
