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

#include <sstream>

#include "Dialog.h"
#include "Control.h"
#include "MsiHelper.h"

Dialog::Dialog(const nlohmann::json& json, const InstallerStrings& installerStrings) {
    if (json.contains("Dialog") && !json["Dialog"].is_null()) {
        dialog = json["Dialog"];
    }
    if (json.contains("HCentering") && !json["HCentering"].is_null()) {
        hcentering = json["HCentering"];
    }
    if (json.contains("VCentering") && !json["VCentering"].is_null()) {
        vcentering = json["VCentering"];
    }
    if (json.contains("Width") && !json["Width"].is_null()) {
        width = json["Width"];
    }
    if (json.contains("Height") && !json["Height"].is_null()) {
        height = json["Height"];
    }
    if (json.contains("Attributes") && !json["Attributes"].is_null()) {
        attributes = json["Attributes"];
    }
    if (json.contains("Title") && !json["Title"].is_null()) {
        title = installerStrings.get(json["Title"]);
    }
    if (json.contains("Control_First") && !json["Control_First"].is_null()) {
        first = json["Control_First"];
    }
    if (json.contains("Control_Default") && !json["Control_Default"].is_null()) {
        default = json["Control_Default"];
    }
    if (json.contains("Control_Cancel") && !json["Control_Cancel"].is_null()) {
        cancel = json["Control_Cancel"];
    }
    if (json.contains("Controls") && !json["Controls"].is_null()) {
        for (const auto& control : json["Controls"]) {
            controls.emplace_back(control, installerStrings, dialog);
        }
    }
}

std::vector<Control> Dialog::get_controls() const {
    return controls;
}

MSIHANDLE Dialog::getRecord() const {
    return MsiHelper::MsiRecordSet({ dialog, hcentering, vcentering, width, height, attributes, title, first, default, cancel });
}
