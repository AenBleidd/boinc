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

#include "EventMappingTable.h"
#include "ValidationTable.h"

EventMappingTable::EventMappingTable(const std::vector<Control>& controls) : controls(controls) {
}

bool EventMappingTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating EventMappingTable..." << std::endl;

    std::vector<EventMapping> eventMappings;
    for (const auto& control : controls) {
        for (const auto& eventMapping : control.get_event_mappings()) {
            eventMappings.push_back(eventMapping);
        }
    }

    const auto sql_create = "CREATE TABLE `EventMapping` (`Dialog_` CHAR(72) NOT NULL, `Control_` CHAR(50) NOT NULL, `Event` CHAR(50) NOT NULL, `Attribute` CHAR(50) "
        "PRIMARY KEY Dialog_, Control_, Event)";
    const auto sql_insert = "INSERT INTO `EventMapping` (`Dialog_`, `Control_`, `Event`, `Attribute`) VALUES (?, ?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("EventMapping", "Dialog_", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Dialog", "1", "Identifier", "", "A foreign key to the Dialog table, name of the Dialog.");
    records.emplace_back("EventMapping", "Control_", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Control", "2", "Identifier", "", "A foreign key to the Control table, name of the control.");
    records.emplace_back("EventMapping", "Event", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "An identifier that specifies the type of the event that the control subscribes to.");
    records.emplace_back("EventMapping", "Attribute", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "The name of the control attribute, that is set when this event is received.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, eventMappings);
}