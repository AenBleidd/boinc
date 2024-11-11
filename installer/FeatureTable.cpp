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

#include "FeatureTable.h"
#include "ValidationTable.h"

FeatureTable::FeatureTable(const nlohmann::json& json, const InstallerStrings& installerStrings) {
    std::cout << "Loading FeatureTable..." << std::endl;
    for (const auto& feature : json) {
        features.emplace_back(feature, "", installerStrings);
    }
}

bool FeatureTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating FeatureTable..." << std::endl;

    std::vector<Feature> all;
    for (const auto& feature : features) {
        all.push_back(feature);
        for (const auto& component : feature.getFeatures()) {
            all.push_back(component);
        }
    }

    const auto sql_create = "CREATE TABLE `Feature` (`Feature` CHAR(38) NOT NULL, `Feature_Parent` CHAR(38), `Title` CHAR(64) LOCALIZABLE, "
        "`Description` CHAR(255) LOCALIZABLE, `Display` SHORT, `Level` SHORT NOT NULL, `Directory_` CHAR(72), `Attributes` SHORT NOT NULL PRIMARY KEY `Feature`)";
    const auto sql_insert = "INSERT INTO `Feature` (`Feature`, `Feature_Parent`, `Title`, `Description`, `Display`, `Level`, `Directory_`, `Attributes`) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("Feature", "Feature", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "Primary key used to identify a particular feature record.");
    records.emplace_back("Feature", "Feature_Parent", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Feature", "1", "Identifier", "", "Optional key of a parent record in the same table. If the parent is not selected, then the record will not be installed. Null indicates a root item.");
    records.emplace_back("Feature", "Title", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Text", "", "Short text identifying a visible feature item.");
    records.emplace_back("Feature", "Description", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Text", "", "Longer descriptive text describing a visible feature item.");
    records.emplace_back("Feature", "Display", "Y", 0, 32767, "", "", "", "", "Numeric sort order, used to force a specific display ordering.");
    records.emplace_back("Feature", "Level", "N", 0, 32767, "", "", "", "", "The install level at which record will be initially selected. An install level of 0 will disable an item and prevent its display.");
    records.emplace_back("Feature", "Directory_", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Directory", "1", "UpperCase", "", "The name of the Directory that can be configured by the UI. A non-null value will enable the browse button.");
    records.emplace_back("Feature", "Attributes", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "", "0;1;2;4;5;6;8;9;10;16;17;18;20;21;22;24;25;26;32;33;34;36;37;38;48;49;50;52;53;54", "Feature attributes.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, all);
}
