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

#include "Binary.h"

Binary::Binary(const nlohmann::json& json, const std::filesystem::path& root_path) {
    const std::string configuration_template = "%%CONFIGURATION%%";
    const std::string configuration = 
#ifdef _DEBUG
        "Debug";
#else
        "Release";
#endif
    const std::string platform_template = "%%PLATFORM%%";
    const std::string platform =
#ifdef _ARM64_
        "ARM64";
#else
        "x64";
#endif

    if (json.contains("Name")) {
        name = json["Name"];
    }
    if (json.contains("Path")) {
        auto p = std::string(json["Path"]);
        auto index = p.find(configuration_template);
        if (index != std::string::npos) {
            p.replace(index, configuration_template.size(), configuration);
        }
        index = p.find(platform_template);
        if (index != std::string::npos) {
            p.replace(index, platform_template.size(), platform);
        }
        path = root_path / p;
    }
}

MSIHANDLE Binary::getRecord() const {
    if (!std::filesystem::exists(path)) {
        throw std::filesystem::filesystem_error("File does not exist", path.string(), std::make_error_code(std::errc::no_such_file_or_directory));
    }
    const auto hRecord = MsiCreateRecord(2);
    MsiRecordSetString(hRecord, 1, name.c_str());
    MsiRecordSetStream(hRecord, 2, path.string().c_str());
    return hRecord;
}
