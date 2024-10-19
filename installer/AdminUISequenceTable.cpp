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

#include "AdminUISequenceTable.h"

std::string AdminUISequenceTable::generate() const {
    std::vector<Action> values;

    values.emplace_back("AdminWelcome", 1010);
    values.emplace_back("CostFinalize", 1000);
    values.emplace_back("CostInitialize", 800);
    values.emplace_back("ExecuteAction", 1300);
    values.emplace_back("FileCost", 900);
    values.emplace_back("SetupCompleteError", -3);
    values.emplace_back("SetupCompleteSuccess", -1);
    values.emplace_back("SetupInitialization", 50);
    values.emplace_back("SetupInterrupted", -2);
    values.emplace_back("SetupProgress", 1020);

    return Generator::generate({ { "Action", "s72" }, { "Condition", "S255" }, { "Sequence", "I2" } }, { "AdminUISequence", "Action" }, values);
}
