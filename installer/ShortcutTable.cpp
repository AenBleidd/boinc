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

#include "ShortcutTable.h"
#include "ValidationTable.h"

ShortcutTable::ShortcutTable(const std::vector<Directory>& directories) {
    for (const auto& directory : directories) {
        for (const auto& component : directory.getComponents()) {
            for (const auto& shortcut : component.getShortcuts()) {
                values.push_back(shortcut);
            }
        }
    }
}

bool ShortcutTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating ShortcutTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `Shortcut` (`Shortcut` CHAR(72) NOT NULL, `Directory_` CHAR(72) NOT NULL, `Name` CHAR(128) NOT NULL LOCALIZABLE, "
        "`Component_` CHAR(72) NOT NULL, `Target` CHAR(255) NOT NULL, `Arguments` CHAR(255), `Description` CHAR(255) LOCALIZABLE, `Hotkey` SHORT, "
        "`Icon_` CHAR(72), `IconIndex` SHORT, `ShowCmd` SHORT, `WkDir` CHAR(72) NOT NULL, `DisplayResourceDll` CHAR(255), `DisplayResourceId` SHORT, "
        "`DescriptionResourceDll` CHAR(255), `DescriptionResourceId` SHORT PRIMARY KEY `Shortcut`)";

    const auto sql_insert = "INSERT INTO `Shortcut` (`Shortcut`, `Directory_`, `Name`, `Component_`, `Target`, `Arguments`, `Description`, `Hotkey`, `Icon_`, "
        "`IconIndex`, `ShowCmd`, `WkDir`, `DisplayResourceDll`, `DisplayResourceId`, `DescriptionResourceDll`, `DescriptionResourceId`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    std::vector<Validation> records;

    records.emplace_back("Shortcut", "Shortcut", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "0", "Identifier", "", "Primary key, non-localized token.");
    records.emplace_back("Shortcut", "Directory_", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Directory", "1", "Identifier", "", "Foreign key into the Directory table denoting the directory where the shortcut file is created.");
    records.emplace_back("Shortcut", "Name", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "0", "Text", "", "The name of the shortcut to be created.");
    records.emplace_back("Shortcut", "Component_", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Component", "1", "Identifier", "", "Foreign key into the Component table denoting the component whose selection gates the the shortcut creation/deletion.");
    records.emplace_back("Shortcut", "Target", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "0", "Shortcut", "", "The shortcut target. This is usually a property that is expanded to a file or a folder that the shortcut points to.");
    records.emplace_back("Shortcut", "Arguments", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "0", "Formatted", "", "The command-line arguments for the shortcut.");
    records.emplace_back("Shortcut", "Description", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "0", "Text", "", "The description for the shortcut.");
    records.emplace_back("Shortcut", "Hotkey", "Y", 0, 32767, "", "0", "", "", "The hotkey for the shortcut. It has the virtual-key code for the key in the low-order byte, and the modifier flags in the high-order byte. ");
    records.emplace_back("Shortcut", "Icon_", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "Icon", "1", "Identifier", "", "Foreign key into the File table denoting the external icon file for the shortcut.");
    records.emplace_back("Shortcut", "IconIndex", "Y", -32767, 32767, "", "0", "", "", "The icon index for the shortcut.");
    records.emplace_back("Shortcut", "ShowCmd", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "0", "", "1;3;7", "The show command for the application window.The following values may be used.");
    records.emplace_back("Shortcut", "WkDir", "N", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "0", "Identifier", "", "Name of property defining location of working directory.");
    records.emplace_back("Shortcut", "DisplayResourceDll", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "0", "Formatted", "", "This field contains a Formatted string value for the full path to the language neutral file that contains the MUI manifest.");
    records.emplace_back("Shortcut", "DisplayResourceId", "Y", 0, 32767, "", "0", "", "", "The display name index for the shortcut.");
    records.emplace_back("Shortcut", "DescriptionResourceDll", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "0", "Formatted", "", "This field contains a Formatted string value for the full path to the language neutral file that contains the MUI manifest.");
    records.emplace_back("Shortcut", "DescriptionResourceId", "Y", 0, 32767, "", "0", "", "", "The description name index for the shortcut.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, values);
}
