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

#include "AdminExecuteSequenceTable.h"

std::string AdminExecuteSequenceTable::generate() const {
    std::vector<Action> values;

    values.emplace_back("CASetBOINCDataProjects", 1300);
    values.emplace_back("CASetBOINCDataSlots", 1200);
    values.emplace_back("CostFinalize", 1000);
    values.emplace_back("CostInitialize", 800);
    values.emplace_back("FileCost", 900);
    values.emplace_back("InstallAdminPackage", 3900);
    values.emplace_back("InstallFiles", 4000);
    values.emplace_back("InstallFinalize", 6600);
    values.emplace_back("InstallInitialize", 1500);
    values.emplace_back("InstallValidate", 1400);
    values.emplace_back("ScheduleReboot", "ISSCHEDULEREBOOT", 4010);

    return Generator::generate({ "Action", "Condition", "Sequence" }, { "s72", "S255", "I2" }, { "AdminExecuteSequence", "Action" }, values);
}
