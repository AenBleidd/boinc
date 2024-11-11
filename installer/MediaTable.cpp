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

#include "MediaTable.h"
#include "ValidationTable.h"

MediaTable::MediaTable(const std::vector<Media>& media) : media(media) {
}

bool MediaTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating MediaTable..." << std::endl;

    const auto sql_create = "CREATE TABLE `Media` (`DiskId` SHORT NOT NULL, `LastSequence` SHORT NOT NULL, `DiskPrompt` CHAR(64) LOCALIZABLE, `Cabinet` CHAR(255), `VolumeLabel` CHAR(32), `Source` CHAR(72) PRIMARY KEY `DiskId`)";
    const auto sql_insert = "INSERT INTO `Media` (`DiskId`, `LastSequence`, `DiskPrompt`, `Cabinet`, `VolumeLabel`, `Source`) VALUES (?, ?, ?, ?, ?, ?)";

    std::vector<Validation> records;
    records.emplace_back("Media", "DiskId", "N", 1, 32767, "", "", "", "", "Primary key, integer to determine sort order for table.");
    records.emplace_back("Media", "LastSequence", "N", 0, 32767, "", "", "", "", "File sequence number for the last file for this media.");
    records.emplace_back("Media", "DiskPrompt", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Text", "", "Disk name: the visible text actually printed on the disk. This will be used to prompt the user when this disk needs to be inserted.");
    records.emplace_back("Media", "Cabinet", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Cabinet", "", "If some or all of the files stored on the media are compressed in a cabinet, the name of that cabinet.");
    records.emplace_back("Media", "VolumeLabel", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Text", "", "The label attributed to the volume.");
    records.emplace_back("Media", "Source", "Y", MSI_NULL_INTEGER, MSI_NULL_INTEGER, "", "", "Property", "", "The property defining the location of the cabinet file.");

    if (!ValidationTable().insert(hDatabase, records)) {
        return false;
    }

    return Generator::generate(hDatabase, sql_create, sql_insert, media);
}
