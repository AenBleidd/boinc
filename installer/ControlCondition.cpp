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

#include "ControlCondition.h"

ControlCondition::ControlCondition(const nlohmann::json& json, const std::string& dialog, const std::string& control)
    : dialog(dialog), control(control) {
    if (json.contains("Action")) {
        action = json["Action"];
    }
    if (json.contains("Condition")) {
        condition = json["Condition"];
    }
}

MSIHANDLE ControlCondition::getRecord() const {
    const auto hRecord = MsiCreateRecord(4);
    MsiRecordSetString(hRecord, 1, dialog.c_str());
    MsiRecordSetString(hRecord, 2, control.c_str());
    MsiRecordSetString(hRecord, 3, action.c_str());
    MsiRecordSetString(hRecord, 4, condition.c_str());
    return hRecord;
}
