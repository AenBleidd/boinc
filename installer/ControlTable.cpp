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

#include "ControlTable.h"

ControlTable::ControlTable(const UI& ui) : ui(ui) {}

std::string ControlTable::generate() const
{
    return Generator::generate({ { "Dialog_", "s72" }, { "Control", "s50" }, { "Type", "s20" }, { "X", "i2" }, { "Y", "i2" }, { "Width", "i2" },
        { "Height", "i2" }, { "Attributes", "I4", }, { "Property", "S72" }, { "Text", "L0" }, { "Control_Next", "S50" }, { "Help", "L50"} },
        { "Control", "Dialog_", "Control" }, ui.get_controls());
}
