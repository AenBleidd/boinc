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

#include "DirectoryTable.h"
#include "ComponentTable.h"
#include "FeatureComponentsTable.h"
#include "CreateFolderTable.h"

DirectoryTable::DirectoryTable(const nlohmann::json& json) {
    std::cout << "Loading DirectoryTable..." << std::endl;
    for (const auto& directory : json) {
        directories.emplace_back(directory, "");
    }
}

bool DirectoryTable::generate(MSIHANDLE hDatabase) {
    ComponentTable(directories).generate(hDatabase);
    FeatureComponentsTable(directories).generate(hDatabase);
    CreateFolderTable(directories).generate(hDatabase);

    std::vector<Directory> all;
    for (const auto& directory : directories) {
        all.push_back(directory);
        auto subdirs = directory.getDirectories();
        all.insert(all.end(), subdirs.begin(), subdirs.end());
    }

    std::cout << "Generating DirectoryTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `Directory` (`Directory` CHAR(72) NOT NULL, `Directory_Parent` CHAR(72), `DefaultDir` CHAR(255) NOT NULL LOCALIZABLE PRIMARY KEY `Directory`)";
    const auto sql_insert = "INSERT INTO `Directory` (`Directory`, `Directory_Parent`, `DefaultDir`) VALUES (?, ?, ?)";

    return Generator::generate(hDatabase, sql_create, sql_insert, all);
}
