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

#include "DialogTable.h"

DialogTable::DialogTable(const UI& ui) : ui(ui) {
}

std::string DialogTable::generate() const {
    return Generator::generate({ { "Dialog", "s72" }, { "HCentering", "i2" }, { "VCentering", "i2" }, { "Width", "i2" }, { "Height", "i2" }, { "Attributes", "I4" },
        { "Title", "L128" }, { "Control_First", "s50" }, { "Control_Default", "S50" }, { "Control_Cancel", "S50" } }, { "Dialog", "Dialog" }, ui.get_dialogs());
}


