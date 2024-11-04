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

#include "Property.h"

Property::Property(const nlohmann::json& json, const InstallerStrings& installerStrings) {
    if (json.contains("Property")) {
        property = json["Property"];
    }
    if (json.contains("Value")) {
        value = installerStrings.get(json["Value"]);
    }
}

MSIHANDLE Property::getRecord() const {
    const auto hRecord = MsiCreateRecord(2);
    MsiRecordSetString(hRecord, 1, property.c_str());
    MsiRecordSetString(hRecord, 2, value.c_str());
    return hRecord;
}
