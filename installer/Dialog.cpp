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

Dialog::Dialog(const nlohmann::json& json, const InstallerStrings& installerStrings) {
    if (json.contains("Dialog")) {
        dialog = json.at("Dialog").get<std::string>();
    }
    if (json.contains("HCentering")) {
        hcentering = json.at("HCentering").get<int>();
    }
    if (json.contains("VCentering")) {
        vcentering = json.at("VCentering").get<int>();
    }
    if (json.contains("Width")) {
        width = json.at("Width").get<int>();
    }
    if (json.contains("Height")) {
        height = json.at("Height").get<int>();
    }
    if (json.contains("Attributes")) {
        attributes = json.at("Attributes").get<int>();
    }
    if (json.contains("Title")) {
        title = installerStrings.get(json.at("Title").get<std::string>());
    }
    if (json.contains("Control_First")) {
        first = json.at("Control_First").get<std::string>();
    }
    if (json.contains("Control_Default")) {
        default = json.at("Control_Default").get<std::string>();
    }
    if (json.contains("Control_Cancel")) {
        cancel = json.at("Control_Cancel").get<std::string>();
    }
    if (json.contains("Controls")) {
        for (const auto& control : json.at("Controls")) {
            controls.emplace_back(control, installerStrings, dialog);
        }
    }
}

std::vector<Control> Dialog::get_controls() const {
    return controls;
}

MSIHANDLE Dialog::getRecord() const {
    const auto hRecord = MsiCreateRecord(10);
    MsiRecordSetString(hRecord, 1, dialog.c_str());
    MsiRecordSetInteger(hRecord, 2, hcentering);
    MsiRecordSetInteger(hRecord, 3, vcentering);
    MsiRecordSetInteger(hRecord, 4, width);
    MsiRecordSetInteger(hRecord, 5, height);
    MsiRecordSetInteger(hRecord, 6, attributes);
    MsiRecordSetString(hRecord, 7, title.c_str());
    MsiRecordSetString(hRecord, 8, first.c_str());
    MsiRecordSetString(hRecord, 9, default.c_str());
    MsiRecordSetString(hRecord, 10, cancel.c_str());
    return hRecord;
}
