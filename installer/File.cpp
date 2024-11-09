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

#include "File.h"
#include "MsiHelper.h"

File::File(const nlohmann::json& json, const std::string& component) : component(component) {
//    const std::string configuration_template = "%%CONFIGURATION%%";
//    const std::string configuration =
//#ifdef _DEBUG
//        "Debug";
//#else
//        "Release";
//#endif
//    const std::string platform_template = "%%PLATFORM%%";
//    const std::string platform =
//#ifdef _ARM64_
//        "ARM64";
//#else
//        "x64";
//#endif

    if (json.contains("File") && !json["File"].is_null()) {
        file = json["File"];
    }
    if (json.contains("FileName") && !json["FileName"].is_null()) {
        filename = json["FileName"];
    }
    if (json.contains("FilePath") && !json["FilePath"].is_null()) {
        //auto p = std::string(json["FilePath"]);
        //auto index = p.find(configuration_template);
        //if (index != std::string::npos) {
        //    p.replace(index, configuration_template.size(), configuration);
        //}
        //index = p.find(platform_template);
        //if (index != std::string::npos) {
        //    p.replace(index, platform_template.size(), platform);
        //}
        //filepath = root_path / p;
        filepath = std::string(json["FilePath"]);
    }

    // temporary
    filesize = 0;
    sequence = 0;
}

MSIHANDLE File::getRecord() const {
    return MsiHelper::MsiRecordSet({ file, component, filename, filesize, version, language, attributes, sequence });
}

std::filesystem::path File::getFilePath() const {
    return filepath;
}

std::string File::getFileId() const {
    return file;
}

void File::setFilesize(int size) {
    filesize = size;
}

void File::setVersion(const std::string& v) {
    version = v;
}

void File::setLanguage(const std::string& l) {
    language = l;
}

void File::setAttributes(int a) {
    attributes = a;
}

void File::setSequence(int s) {
    sequence = s;
}
