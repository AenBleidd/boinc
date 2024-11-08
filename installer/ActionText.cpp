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

#include "ActionText.h"
#include "MsiHelper.h"

ActionText::ActionText(const nlohmann::json& json, const InstallerStrings& installerStrings) {
    if (json.contains("Action") && !json["Action"].is_null()) {
        action = json["Action"];
    }
    if (json.contains("Description") && !json["Description"].is_null()) {
        description = installerStrings.get(json["Description"]);
    }
    if (json.contains("Template") && !json["Template"].is_null()) {
        tmplt = installerStrings.get(json["Template"]);
    }
}

MSIHANDLE ActionText::getRecord() const {
    return MsiHelper::MsiRecordSet({ action, description, tmplt });
}
