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

#include "RadioButton.h"
#include "MsiHelper.h"

RadioButton::RadioButton(const nlohmann::json& json, const InstallerStrings& installerStrings) {
    if (json.contains("Property")) {
        property = json["Property"];
    }
    if (json.contains("Order")) {
        order = json["Order"];
    }
    if (json.contains("Value")) {
        value = json["Value"];
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
    if (json.contains("Text")) {
        text = installerStrings.get(json["Text"]);
    }
    if (json.contains("Help")) {
        help = installerStrings.get(json["Help"]);
    }
}

MSIHANDLE RadioButton::getRecord() const {
    return MsiHelper::MsiRecordSet({ property, order, value, x, y, width, height, text, help });
}
