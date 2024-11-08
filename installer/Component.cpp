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

#include "Component.h"
#include "GuidHelper.h"
#include "MsiHelper.h"

Component::Component(const nlohmann::json& json, const std::string& directory, const std::string& parent) : directory(directory) {
    if (json.contains("Component") && !json["Component"].is_null()) {
        component = json["Component"];
    }
    if (json.contains("Attributes") && !json["Attributes"].is_null()) {
        attributes = json["Attributes"];
    }
    if (json.contains("Condition") && !json["Condition"].is_null()) {
        condition = json["Condition"];
    }
    if (json.contains("Feature_") && !json["Feature_"].is_null()) {
        feature = json["Feature_"];
    }
    if (json.contains("CreateFolder") && !json["CreateFolder"].is_null()) {
        create_folder = json["CreateFolder"];
    }
    if (component.empty()) {
        component = parent + "_" + directory;
    }
    componentId = GuidHelper::generate_guid();
    // add keypath
}

MSIHANDLE Component::getRecord() const {
    return MsiHelper::MsiRecordSet({ component, componentId, directory, attributes, condition, keyPath });
}

FeatureComponents Component::getFeatureComponent() const {
    return { feature, component };
}

std::tuple<bool, CreateFolder> Component::getCreateFolder() const {
    if (create_folder) {
        return { true, { directory, component } };
    }
    return { false, {} };
}
