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

#include "LaunchCondition.h"
#include "MsiHelper.h"

LaunchCondition::LaunchCondition(const nlohmann::json& json, const InstallerStrings& installerStrings) {
    if (json.contains("Condition") && !json["Condition"].is_null()) {
        condition = json["Condition"];
    }
    if (json.contains("Description") && !json["Description"].is_null()) {
        description = installerStrings.get(json["Description"]);
    }
}

MSIHANDLE LaunchCondition::getRecord() const {
    return MsiHelper::MsiRecordSet({ condition, description });
}
