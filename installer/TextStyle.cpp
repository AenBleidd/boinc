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

#include "TextStyle.h"

TextStyle::TextStyle(const nlohmann::json& json) {
    if (json.contains("TextStyle")) {
        textstyle = json["TextStyle"];
    }
    if (json.contains("FaceName")) {
        facename = json["FaceName"];
    }
    if (json.contains("Size")) {
        size = json["Size"];
    }
    if (json.contains("Color")) {
        color = json["Color"];
    }
    if (json.contains("StyleBits")) {
        stylebits = json["StyleBits"];
    }
}

MSIHANDLE TextStyle::getRecord() const {
    const auto hRecord = MsiCreateRecord(5);
    MsiRecordSetString(hRecord, 1, textstyle.c_str());
    MsiRecordSetString(hRecord, 2, facename.c_str());
    MsiRecordSetInteger(hRecord, 3, size);
    MsiRecordSetInteger(hRecord, 4, color);
    MsiRecordSetInteger(hRecord, 5, stylebits);
    return hRecord;
}
