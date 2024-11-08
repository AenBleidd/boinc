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

#include "Feature.h"
#include "MsiHelper.h"

Feature::Feature(const nlohmann::json& json, const std::string& parent, const InstallerStrings& installerStrings) : feature_parent(parent) {
    if (json.contains("Feature") && !json["Feature"].is_null()) {
        feature = json["Feature"];
    }
    if (json.contains("Title") && !json["Title"].is_null()) {
        title = installerStrings.get(json["Title"]);
    }
    if (json.contains("Description") && !json["Description"].is_null()) {
        description = installerStrings.get(json["Description"]);
    }
    if (json.contains("Display") && !json["Display"].is_null()) {
        display = json["Display"];
    }
    if (json.contains("Level") && !json["Level"].is_null()) {
        level = json["Level"];
    }
    if (json.contains("Directory_") && !json["Directory_"].is_null()) {
        directory = json["Directory_"];
    }
    if (json.contains("Attributes") && !json["Attributes"].is_null()) {
        attributes = json["Attributes"];
    }
    if (json.contains("Features") && !json["Features"].is_null()) {
        for (const auto& f : json["Features"]) {
            features.emplace_back(f, feature, installerStrings);
        }
    }
}

MSIHANDLE Feature::getRecord() const {
    return MsiHelper::MsiRecordSet({ feature, feature_parent, title, description, display, level, directory, attributes });
}

std::vector<Feature> Feature::getFeatures() const {
    std::vector<Feature> result;
    for (const auto& f : features) {
        result.push_back(f);
        auto subFeatures = f.getFeatures();
        result.insert(result.end(), subFeatures.begin(), subFeatures.end());
    }
    return result;
}
