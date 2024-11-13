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
#include "FileTable.h"
#include "ValidationTable.h"
#include "FontTable.h"
#include "RegistryTable.h"

DirectoryTable::DirectoryTable(const nlohmann::json& json, const std::filesystem::path& root_path) : root_path (root_path) {
    std::cout << "Loading DirectoryTable..." << std::endl;
    for (const auto& directory : json) {
        directories.emplace_back(directory, "");
    }
}

bool DirectoryTable::generate(MSIHANDLE hDatabase) {
    if (!ComponentTable(directories).generate(hDatabase)) {
        std::cerr << "Failed to generate ComponentTable" << std::endl;
        return false;
    }
    if (!FeatureComponentsTable(directories).generate(hDatabase)) {
        std::cerr << "Failed to generate FeatureComponentsTable" << std::endl;
        return false;
    }
    if (!CreateFolderTable(directories).generate(hDatabase)) {
        std::cerr << "Failed to generate CreateFolderTable" << std::endl;
        return false;
    }
    if (!FileTable(directories, root_path).generate(hDatabase)) {
        std::cerr << "Failed to generate FileTable" << std::endl;
        return false;
    }
    if (!FontTable(directories).generate(hDatabase)) {
        std::cerr << "Failed to generate FontTable" << std::endl;
        return false;
    }
    if (!RegistryTable(directories).generate(hDatabase)) {
        std::cerr << "Failed to generate RegistryTable" << std::endl;
        return false;
    }

    std::vector<Directory> all;
    for (const auto& directory : directories) {
        all.push_back(directory);
        auto subdirs = directory.getDirectories();
        all.insert(all.end(), subdirs.begin(), subdirs.end());
    }

    std::cout << "Generating DirectoryTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `Directory` (`Directory` CHAR(72) NOT NULL, `Directory_Parent` CHAR(72), `DefaultDir` CHAR(255) NOT NULL LOCALIZABLE PRIMARY KEY `Directory`)";
    const auto sql_insert = "INSERT INTO `Directory` (`Directory`, `Directory_Parent`, `DefaultDir`) VALUES (?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("Directory", "Directory", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "Unique identifier for directory entry, primary key. If a property by this name is defined, it contains the full path to the directory.");
    records.emplace_back("Directory", "Directory_Parent", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Directory", "1", "Identifier", "", "Reference to the entry in this table specifying the default parent directory. A record parented to itself or with a Null parent represents a root of the install tree.");
    records.emplace_back("Directory", "DefaultDir", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "DefaultDir", "", "The default sub-path under parent's path.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, all);
}
