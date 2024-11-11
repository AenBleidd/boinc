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

#include "ControlEventTable.h"
#include "ValidationTable.h"

ControlEventTable::ControlEventTable(const std::vector<Control>& controls) noexcept : controls(controls) {}

bool ControlEventTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating ControlEventTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `ControlEvent` (`Dialog_` CHAR(72) NOT NULL, `Control_` CHAR(50) NOT NULL, `Event` CHAR(50) NOT NULL, "
        "`Argument` CHAR(255) NOT NULL, `Condition` CHAR(255), `Ordering` SHORT PRIMARY KEY `Dialog_`, `Control_`, `Event`, `Argument`, `Condition`)";
    const auto sql_insert = "INSERT INTO `ControlEvent` (`Dialog_`, `Control_`, `Event`, `Argument`, `Condition`, `Ordering`) VALUES (?, ?, ?, ?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("ControlEvent", "Dialog_", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Dialog", "1", "Identifier", "", "A foreign key to the Dialog table, name of the dialog.");
    records.emplace_back("ControlEvent", "Control_", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Control", "2", "Identifier", "", "A foreign key to the Control table, name of the control.");
    records.emplace_back("ControlEvent", "Event", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Formatted", "", "An identifier that specifies the type of the event that should take place when the user interacts with control specified by the first two entries.");
    records.emplace_back("ControlEvent", "Argument", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Formatted", "", "A value to be used as a modifier when triggering a particular event.");
    records.emplace_back("ControlEvent", "Condition", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Condition", "", "A standard conditional statement that specifies under which conditions an event should be triggered.");
    records.emplace_back("ControlEvent", "Ordering", "Y", 0, 2147483647, "", "", "", "", "An integer used to order several events tied to the same control. Can be left blank.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    std::vector<ControlEvent> controlEvents;
    for (const auto& control : controls) {
        for (const auto& controlEvent : control.get_events()) {
            controlEvents.emplace_back(controlEvent);
        }
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, controlEvents);
}
