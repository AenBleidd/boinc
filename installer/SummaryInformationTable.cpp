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

#include <chrono>
#include <iomanip>
#include <iostream>

#include "SummaryInformationTable.h"
#include "GuidHelper.h"

SummaryInformationTable::SummaryInformationTable(const nlohmann::json& json, const InstallerStrings& installerStrings)
{
    std::cout << "Loading SummaryInformationTable..." << std::endl;

    SYSTEMTIME systemTime;
    GetSystemTime(&systemTime);
    FILETIME fileTime;
    SystemTimeToFileTime(&systemTime, &fileTime);

    summary[1] = json.at("codepage").get<int>();
    summary[2] = installerStrings.get(json.at("title").get<std::string>());
    summary[3] = installerStrings.get(json.at("subject").get<std::string>());
    summary[4] = installerStrings.get(json.at("author").get<std::string>());
    summary[5] = json.at("keywords").get<std::string>();
    summary[6] = installerStrings.get(json.at("comments").get<std::string>());
    summary[7] = json.at("template").get<std::string>();
    summary[8] = json.at("lastauthor").get<std::string>();
    summary[9] = GuidHelper::generate_guid();
    summary[11] = fileTime;
    summary[12] = fileTime;
    summary[13] = fileTime;
    summary[14] = json.at("pagecount").get<int>();
    summary[15] = json.at("wordcount").get<int>();
    summary[16] = json.at("charcount").get<int>();
    summary[18] = json.at("appname").get<std::string>();
    summary[19] = json.at("security").get<int>();
}

bool SummaryInformationTable::generate(MSIHANDLE hDatabase) {
    std::cout << "Generating SummaryInformationTable" << std::endl;

    MSIHANDLE hSummaryInfo;
    const auto updateCount = summary.size();

    auto result = MsiGetSummaryInformation(hDatabase, nullptr, updateCount, &hSummaryInfo);
    if (result != ERROR_SUCCESS) {
        std::cerr << "MsiGetSummaryInformation failed: " << result << std::endl;
        return false;
    }

    for (auto& [id, value] : summary) {
        try {
            std::cout << "Setting property " << id << std::endl;
            if (std::holds_alternative<int>(value)) {
                result = MsiSummaryInfoSetProperty(hSummaryInfo, id, VT_I4, std::get<int>(value), nullptr, nullptr);
            }
            else if (std::holds_alternative<FILETIME>(value)) {
                result = MsiSummaryInfoSetProperty(hSummaryInfo, id, VT_FILETIME, 0, std::get_if<FILETIME>(&value), nullptr);
            }
            else {
                result = MsiSummaryInfoSetProperty(hSummaryInfo, id, VT_LPSTR, 0, nullptr, std::get<std::string>(value).c_str());
            }
        }
        catch (const std::bad_variant_access& e) {
            std::cerr << "bad_variant_access: " << e.what() << std::endl;
            return false;
        }
        if (result != ERROR_SUCCESS) {
            std::cerr << "MsiSummaryInfoSetProperty failed: " << result << std::endl;
            return false;
        }
    }

    result = MsiSummaryInfoPersist(hSummaryInfo);
    if (result != ERROR_SUCCESS) {
        std::cerr << "MsiSummaryInfoPersist failed:" << result << std::endl;
        return false;
    }

    result = MsiCloseHandle(hSummaryInfo);
    if (result != ERROR_SUCCESS) {
        std::cerr << "MsiCloseHandle failed:" << result << std::endl;
        return false;
    }

    return true;
}
