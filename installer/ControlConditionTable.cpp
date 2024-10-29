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

#include "Generator.h"

#include "ControlConditionTable.h"

std::string ControlConditionTable::generate(const std::vector<Dialog>& dialogs) const
{
    std::vector<ControlCondition> conditions;
    for (const auto& dialog : dialogs) {
        for (const auto& control : dialog.get_controls()) {
            for (const auto& condition : control.get_conditions()) {
                conditions.push_back(condition);
            }
        }
    }

    return Generator<ControlCondition>().generate({{"Dialog_", "s72"}, {"Control_", "s50"}, {"Action", "s50"}, {"Condition", "s255"}},
        { "ControlCondition", "Dialog_", "Control_", "Action", "Condition" }, conditions);
}
