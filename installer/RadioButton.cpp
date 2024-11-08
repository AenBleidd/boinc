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
    if (json.contains("Property") && !json["Property"].is_null()) {
        property = json["Property"];
    }
    if (json.contains("Order") && !json["Order"].is_null()) {
        order = json["Order"];
    }
    if (json.contains("Value") && !json["Value"].is_null()) {
        value = json["Value"];
    }
    if (json.contains("X") && !json["X"].is_null()) {
        x = json["X"];
    }
    if (json.contains("Y") && !json["Y"].is_null()) {
        y = json["Y"];
    }
    if (json.contains("Width") && !json["Width"].is_null()) {
        width = json["Width"];
    }
    if (json.contains("Height") && !json["Height"].is_null()) {
        height = json["Height"];
    }
    if (json.contains("Text") && !json["Text"].is_null()) {
        text = installerStrings.get(json["Text"]);
    }
    if (json.contains("Help") && !json["Help"].is_null()) {
        help = installerStrings.get(json["Help"]);
    }
}

MSIHANDLE RadioButton::getRecord() const {
    return MsiHelper::MsiRecordSet({ property, order, value, x, y, width, height, text, help });
}
