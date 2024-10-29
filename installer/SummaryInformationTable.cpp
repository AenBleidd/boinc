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

//#include "Windows.h"
//#include "Msi.h"
//#include "MsiQuery.h"

#include "SummaryInformationTable.h"
#include "GuidHelper.h"

std::string SummaryInformationTable::generate() const {
    return {};
    /*return Generator::generate({ {"PropertyId", "i2"}, {"Value", "l255"} }, { "_SummaryInformation", "PropertyId" }, summary);*/
}

bool SummaryInformationTable::load(const nlohmann::json& json, const InstallerStrings& installerStrings)
{
    //const auto now_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    //std::tm now_tm;
    //localtime_s(&now_tm, &now_time_t);
    //std::ostringstream oss;
    //oss << std::put_time(&now_tm, "%Y/%m/%d %H:%M:%S");
    //const auto time_str = oss.str();

    // Get the current system time as FILETIME
    SYSTEMTIME systemTime;
    GetSystemTime(&systemTime); // Gets UTC time
    FILETIME fileTime;
    SystemTimeToFileTime(&systemTime, &fileTime);

    try {
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
    catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return false;
    }
    return true;
}

bool SummaryInformationTable::generate(MSIHANDLE hDatabase) {
    MSIHANDLE hSummaryInfo;
    const auto updateCount = summary.size();

    auto result = MsiGetSummaryInformation(hDatabase, nullptr, updateCount, &hSummaryInfo);
    if (result != ERROR_SUCCESS) {
        std::cerr << "MsiGetSummaryInformation failed: " << result << std::endl;
        return false;
    }

    for (auto& [id, value] : summary) {
        try {
            if (std::holds_alternative<int>(value)) {
                std::cout << "Setting property " << id << " to " << std::get<int>(value) << std::endl;
                result = MsiSummaryInfoSetProperty(hSummaryInfo, id, VT_I4, std::get<int>(value), nullptr, nullptr);
            }
            else if (std::holds_alternative<FILETIME>(value)) {
                std::cout << "Setting property " << id << " to FILETIME" << std::endl;
                result = MsiSummaryInfoSetProperty(hSummaryInfo, id, VT_FILETIME, 0, std::get_if<FILETIME>(&value), nullptr);
            }
            else {
                std::cout << "Setting property " << id << " to " << std::get<std::string>(value) << std::endl;
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

    if (MsiSummaryInfoPersist(hSummaryInfo) != ERROR_SUCCESS) {
        std::cerr << "MsiSummaryInfoPersist failed" << std::endl;
        return false;
    }

    if (MsiCloseHandle(hSummaryInfo) != ERROR_SUCCESS) {
        std::cerr << "MsiCloseHandle failed" << std::endl;
        return false;
    }

    return true;
}
