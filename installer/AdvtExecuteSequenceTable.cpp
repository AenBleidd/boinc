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

#include "AdvtExecuteSequenceTable.h"

std::string AdvtExecuteSequenceTable::generate() const {
    std::vector<Action> values;

    values.emplace_back("CostFinalize", 1000);
    values.emplace_back("CostInitialize", 800);
    values.emplace_back("CreateShortcuts", 4500);
    values.emplace_back("InstallFinalize", 6600);
    values.emplace_back("InstallInitialize", 1500);
    values.emplace_back("InstallValidate", 1400);
    values.emplace_back("MsiPublishAssemblies", 6250);
    values.emplace_back("PublishComponents", 6200);
    values.emplace_back("PublishFeatures", 6300);
    values.emplace_back("PublishProduct", 6400);
    values.emplace_back("RegisterClassInfo", 4600);
    values.emplace_back("RegisterExtensionInfo", 4700);
    values.emplace_back("RegisterMIMEInfo", 4900);
    values.emplace_back("RegisterProgIdInfo", 4800);
    values.emplace_back("RegisterTypeLibraries", 4910);
    values.emplace_back("ScheduleReboot", "ISSCHEDULEREBOOT", 6410);

    return Generator::generate({ "Action", "Condition", "Sequence" }, { "s72", "S255", "I2" }, { "AdvtExecuteSequence", "Action" }, values);
}
