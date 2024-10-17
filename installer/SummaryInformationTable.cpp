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

#include "SummaryInformationTable.h"

#include "GuidHelper.h"

SummaryInformationTable::SummaryInformationTable(InstallerStrings& installerStrings) noexcept : installerStrings(installerStrings) {};
std::string SummaryInformationTable::generate() const {
    const auto now = std::chrono::system_clock::now();
    const auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm;
    localtime_s(&now_tm, &now_time_t);
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y/%m/%d %H:%M:%S");
    const auto time_str = oss.str();

    std::vector<KeyValue<int, std::string>> values;
    values.emplace_back(1, "1252");
    values.emplace_back(2, installerStrings.get("COMPANY_PRODUCT"));
    values.emplace_back(3, installerStrings.get("COMPANY_PRODUCT_SUBJECT"));
    values.emplace_back(4, installerStrings.get("COMPANY_NAME"));
    values.emplace_back(5, "BOINC");
    values.emplace_back(6, installerStrings.get("IDS_FEATURE_BOINC_DESCRIPTION"));
    values.emplace_back(7, "AMD64;1033");
    values.emplace_back(8, "BOINC");
    values.emplace_back(9, GuidHelper::generate_guid());
    values.emplace_back(11, time_str);
    values.emplace_back(12, time_str);
    values.emplace_back(13, time_str);
    values.emplace_back(14, "200");
    values.emplace_back(15, "0");
    values.emplace_back(16, "0");
    values.emplace_back(18, std::string("BOINC"));
    values.emplace_back(19, "1");

    return Generator::generate({ "PropertyId", "Value" }, { "i2", "l255" }, { "_SummaryInformation", "PropertyId" }, values);
}
