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

#include "Directory.h"
#include "MsiHelper.h"

Directory::Directory(const nlohmann::json& json, const std::string& parent) : parent(parent) {
    if (json.contains("Directory")) {
        directory = json["Directory"];
    }
    if (json.contains("DefaultDir")) {
        default = json["DefaultDir"];
    }
    if (json.contains("Directories")) {
        for (const auto& dir : json["Directories"]) {
            directories.emplace_back(dir, directory);
        }
    }
}

MSIHANDLE Directory::getRecord() const {
    return MsiHelper::MsiRecordSet({ directory, parent, default });
}

std::vector<Directory> Directory::getDirectories() const {
    std::vector<Directory> all;
    for (const auto& dir : directories) {
        all.push_back(dir);
        auto subdirs = dir.getDirectories();
        all.insert(all.end(), subdirs.begin(), subdirs.end());
    }
    return all;
}
