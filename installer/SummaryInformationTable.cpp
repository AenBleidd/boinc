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
#include "Generator.h"

#include "GuidHelper.h"

std::string SummaryInformationTable::generate() const {
    return Generator<KeyValue<int, std::string>>().generate({{"PropertyId", "i2"}, {"Value", "l255"}}, {"_SummaryInformation", "PropertyId"}, summary);
}

bool SummaryInformationTable::load(const nlohmann::json& json, const InstallerStrings& installerStrings)
{
    const auto now_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm now_tm;
    localtime_s(&now_tm, &now_time_t);
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y/%m/%d %H:%M:%S");
    const auto time_str = oss.str();

    try {
        summary.emplace_back(1, std::to_string(json.at("codepage").get<int>()));
        summary.emplace_back(2, installerStrings.get(json.at("title").get<std::string>()));
        summary.emplace_back(3, installerStrings.get(json.at("subject").get<std::string>()));
        summary.emplace_back(4, installerStrings.get(json.at("author").get<std::string>()));
        summary.emplace_back(5, json.at("keywords").get<std::string>());
        summary.emplace_back(6, installerStrings.get(json.at("comments").get<std::string>()));
        summary.emplace_back(7, json.at("template").get<std::string>());
        summary.emplace_back(8, json.at("lastauthor").get<std::string>());
        summary.emplace_back(9, GuidHelper::generate_guid());
        summary.emplace_back(11, time_str);
        summary.emplace_back(12, time_str);
        summary.emplace_back(13, time_str);
        summary.emplace_back(14, std::to_string(json.at("pagecount").get<int>()));
        summary.emplace_back(15, std::to_string(json.at("wordcount").get<int>()));
        summary.emplace_back(16, std::to_string(json.at("charcount").get<int>()));
        summary.emplace_back(18, json.at("appname").get<std::string>());
        summary.emplace_back(19, std::to_string(json.at("security").get<int>()));
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return false;
    }
    return true;
}
