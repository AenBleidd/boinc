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
#include "Control.h"
#include "ControlConditionTable.h"
#include "ControlEventTable.h"
#include "EventMappingTable.h"
#include "ValidationTable.h"
#include "ControlTable.h"

ControlTable::ControlTable(const std::vector<Dialog>& dialogs) noexcept : dialogs(dialogs) {}

bool ControlTable::generate(MSIHANDLE hDatabase)
{
    std::vector<Control> controls;
    for (const auto& dialog : dialogs) {
        for (const auto& control : dialog.get_controls()) {
            controls.emplace_back(control);
        }
    }

    if (!ControlConditionTable(controls).generate(hDatabase)) {
        std::cerr << "Failed to generate ControlConditionTable" << std::endl;
        return false;
    }
    if (!ControlEventTable(controls).generate(hDatabase)) {
        std::cerr << "Failed to generate ControlEventTable" << std::endl;
        return false;
    }
    if (!EventMappingTable(controls).generate(hDatabase)) {
        std::cerr << "Failed to generate EventMappingTable" << std::endl;
        return false;
    }

    std::cout << "Generating ControlTable..." << std::endl;

    const auto create_sql = "CREATE TABLE `Control` (`Dialog_` CHAR(72) NOT NULL, `Control` CHAR(50) NOT NULL, `Type` CHAR(20) NOT NULL, `X` SHORT NOT NULL, "
        "`Y` SHORT NOT NULL, `Width` SHORT NOT NULL, `Height` SHORT NOT NULL, `Attributes` LONG, `Property` CHAR(50), `Text` LONGCHAR LOCALIZABLE, "
        "`Control_Next` CHAR(50), `Help` CHAR(50) LOCALIZABLE PRIMARY KEY `Dialog_`, `Control`)";
    const auto insert_sql = "INSERT INTO `Control` (`Dialog_`, `Control`, `Type`, `X`, `Y`, `Width`, `Height`, `Attributes`, `Property`, `Text`, `Control_Next`, `Help`) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("Control", "Dialog_", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Dialog", "1", "Identifier", "", "External key to the Dialog table, name of the dialog.");
    records.emplace_back("Control", "Control", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "Name of the control. This name must be unique within a dialog, but can repeat on different dialogs. ");
    records.emplace_back("Control", "Type", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "The type of the control.");
    records.emplace_back("Control", "X", "N", 0, 32767, "", "", "", "", "Horizontal coordinate of the upper left corner of the bounding rectangle of the control.");
    records.emplace_back("Control", "Y", "N", 0, 32767, "", "", "", "", "Vertical coordinate of the upper left corner of the bounding rectangle of the control.");
    records.emplace_back("Control", "Width", "N", 0, 32767, "", "", "", "", "Width of the bounding rectangle of the control.");
    records.emplace_back("Control", "Height", "N", 0, 32767, "", "", "", "", "Height of the bounding rectangle of the control.");
    records.emplace_back("Control", "Attributes", "Y", 0, 2147483647, "", "", "", "", "A 32-bit word that specifies the attribute flags to be applied to this control.");
    records.emplace_back("Control", "Property", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "The name of a defined property to be linked to this control. ");
    records.emplace_back("Control", "Text", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Formatted", "", "A string used to set the initial text contained within a control (if appropriate).");
    records.emplace_back("Control", "Control_Next", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Control", "2", "Identifier", "", "The name of an other control on the same dialog. This link defines the tab order of the controls. The links have to form one or more cycles!");
    records.emplace_back("Control", "Help", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Text", "", "The help strings used with the button. The text is optional.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, create_sql, insert_sql, controls);
}
