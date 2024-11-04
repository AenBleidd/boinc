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

#include "Control.h"
#include "MsiHelper.h"

Control::Control(const nlohmann::json& json, const InstallerStrings& installerStrings, const std::string& dialog) : dialog(dialog) {
    if (json.contains("Control")) {
        control = json["Control"];
    }
    if (json.contains("Type")) {
        type = json["Type"];
    }
    if (json.contains("X")) {
        x = json["X"];
    }
    if (json.contains("Y")) {
        y = json["Y"];
    }
    if (json.contains("Width")) {
        width = json["Width"];
    }
    if (json.contains("Height")) {
        height = json["Height"];
    }
    if (json.contains("Attributes")) {
        attributes = json["Attributes"];
    }
    if (json.contains("Property") && !json["Property"].is_null()) {
        property = json["Property"];
    }
    if (json.contains("Text") && !json["Text"].is_null()) {
        text = installerStrings.get(json["Text"]);
    }
    if (json.contains("Control_Next") && !json["Control_Next"].is_null()) {
        next = json["Control_Next"];
    }
    if (json.contains("Help") && !json["Help"].is_null()) {
        help = installerStrings.get(json["Help"]);
    }
    if (json.contains("Binary_") && !json["Binary_"].is_null()) {
        text = json["Binary_"];
    }
    if (json.contains("Conditions") && !json["Conditions"].is_null()) {
        for (const auto& condition : json["Conditions"]) {
            conditions.emplace_back(condition, dialog, control);
        }
    }
    if (json.contains("Events") && !json["Events"].is_null()) {
        for (const auto& event : json["Events"]) {
            events.emplace_back(event, dialog, control);
        }
    }
    //TODO: Make special case for LicenseAgreement -> Memo
}

const std::vector<ControlCondition>& Control::get_conditions() const noexcept {
    return conditions;
}

const std::vector<ControlEvent>& Control::get_events() const noexcept
{
    return events;
}

MSIHANDLE Control::getRecord() const {
    return MsiHelper::MsiRecordSet({ dialog, control, type, x, y, width, height, attributes, property, text, next, help });
}
