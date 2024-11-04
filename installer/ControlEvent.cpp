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

#include "ControlEvent.h"
#include "MsiHelper.h"

ControlEvent::ControlEvent(const nlohmann::json& json, const std::string& dialog, const std::string& control) : dialog(dialog), control(control) {
    if (json.contains("Event")) {
        event = json["Event"];
    }
    if (json.contains("Argument")) {
        argument = json["Argument"];
    }
    if (json.contains("Condition")) {
        condition = json["Condition"];
    }
    if (json.contains("Ordering") && !json["Ordering"].is_null()) {
        ordering = json["Ordering"];
    }
}

MSIHANDLE ControlEvent::getRecord() const {
    return MsiHelper::MsiRecordSet({ dialog, control, event, argument, condition, ordering });
}
