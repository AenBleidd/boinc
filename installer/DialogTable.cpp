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
#include "ControlTable.h"
#include "Generator.h"
#include "ValidationTable.h"

DialogTable::DialogTable(const nlohmann::json& json, const InstallerStrings& installerStrings) {
    std::cout << "Loading DialogTable..." << std::endl;

    for (const auto& dialog : json) {
        dialogs.emplace_back(dialog, installerStrings);
    }
}

bool DialogTable::generate(MSIHANDLE hDatabase) {
    if (!ControlTable(dialogs).generate(hDatabase)) {
        std::cerr << "Failed to generate ControlTable" << std::endl;
        return false;
    }

    std::cout << "Generating DialogsTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `Dialog` (`Dialog` CHAR(72) NOT NULL, `HCentering` SHORT NOT NULL, `VCentering` SHORT NOT NULL, "
        "`Width` SHORT NOT NULL, `Height` SHORT NOT NULL, `Attributes` LONG, `Title` LONGCHAR LOCALIZABLE, `Control_First` CHAR(50) NOT NULL, "
        "`Control_Default` CHAR(50), `Control_Cancel` CHAR(50) PRIMARY KEY `Dialog`)";
    const auto sql_insert = "INSERT INTO `Dialog` (`Dialog`, `HCentering`, `VCentering`, `Width`, `Height`, `Attributes`, `Title`, `Control_First`, "
        "`Control_Default`, `Control_Cancel`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("Dialog", "Dialog", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Identifier", "", "Name of the dialog.");
    records.emplace_back("Dialog", "HCentering", "N", 0, 100, "", "", "", "", "Horizontal position of the dialog on a 0-100 scale. 0 means left end, 100 means right end of the screen, 50 center.");
    records.emplace_back("Dialog", "VCentering", "N", 0, 100, "", "", "", "", "Vertical position of the dialog on a 0-100 scale. 0 means top end, 100 means bottom end of the screen, 50 center.");
    records.emplace_back("Dialog", "Width", "N", 0, 32767, "", "", "", "", "Width of the bounding rectangle of the dialog.");
    records.emplace_back("Dialog", "Height", "N", 0, 32767, "", "", "", "", "Height of the bounding rectangle of the dialog.");
    records.emplace_back("Dialog", "Attributes", "Y", 0, 2147483647, "", "", "", "", "A 32-bit word that specifies the attribute flags to be applied to this dialog.");
    records.emplace_back("Dialog", "Title", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Formatted", "", "A text string specifying the title to be displayed in the title bar of the dialog's window.");
    records.emplace_back("Dialog", "Control_First", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Control", "2", "Identifier", "", "Defines the control that has the focus when the dialog is created.");
    records.emplace_back("Dialog", "Control_Default", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Control", "2", "Identifier", "", "Defines the default control. Hitting return is equivalent to pushing this button.");
    records.emplace_back("Dialog", "Control_Cancel", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Control", "2", "Identifier", "", "Defines the cancel control. Hitting escape or clicking on the close icon on the dialog is equivalent to pushing this button.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, dialogs);
}


