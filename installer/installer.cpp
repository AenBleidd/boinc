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

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

#include <windows.h>
#include <objbase.h>

#include <nlohmann/json.hpp>

class GuidHelper {
public:
    GuidHelper() = default;
    ~GuidHelper() = default;
    static std::string generate_guid() {
        GUID guid;
        if (CoCreateGuid(&guid) != S_OK) {
            throw std::runtime_error("Failed to create GUID");
        }

        std::ostringstream oss;
        oss << std::uppercase << std::hex << std::setfill('0')
            << '{'
            << std::setw(8) << guid.Data1 << '-'
            << std::setw(4) << guid.Data2 << '-'
            << std::setw(4) << guid.Data3 << '-'
            << std::setw(2) << static_cast<int>(guid.Data4[0])
            << std::setw(2) << static_cast<int>(guid.Data4[1]) << '-'
            << std::setw(2) << static_cast<int>(guid.Data4[2])
            << std::setw(2) << static_cast<int>(guid.Data4[3])
            << std::setw(2) << static_cast<int>(guid.Data4[4])
            << std::setw(2) << static_cast<int>(guid.Data4[5])
            << std::setw(2) << static_cast<int>(guid.Data4[6])
            << std::setw(2) << static_cast<int>(guid.Data4[7])
            << '}';

        return oss.str();
    }
};

class Record {
public:
    Record() = default;
    virtual ~Record() = default;
    virtual std::string get() const = 0;
};

template <typename K, typename V>
class KeyValue : public Record {
public:
    explicit KeyValue(const K& key, const V& value) : key(key), value(value) {};
    ~KeyValue() = default;
    std::string get() const override {
        std::ostringstream oss;
        oss << key << "\t" << value << "\n";
        return oss.str();
    }
private:
    K key;
    V value;
};

template <typename R>
class Generator {
public:
    Generator() = default;
    virtual ~Generator() = default;
    virtual std::string generate(const std::vector<std::string>& columns, const std::vector<std::string>& types, const std::vector<std::string>& keys, const std::vector<R>& values) const {
        std::string result;
        for (const auto& column : columns) {
            result += column + "\t";
        }
        result += "\n";
        for (const auto& type : types) {
            result += type + "\t";
        }
        result += "\n";
        for (const auto& key : keys) {
            result += key + "\t";
        }
        result += "\n";
        for (const auto& value : values) {
            result += value.get();
        }
        return result;
    }
    virtual std::string generate() const = 0;
};

class InstallerStrings {
public:
    InstallerStrings() noexcept = default;
    ~InstallerStrings() = default;

    std::string get(const std::string& key) {
        return strings.at(key);
    };
    bool load() {
        const auto filename = std::string("../installer/locale/en.json");
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Could not open file " << filename << std::endl;
            return false;
        }
        nlohmann::json j;
        file >> j;
        return load_from_json(j);
    }
private:
    std::map<std::string, std::string> strings;

    bool load_from_json(const nlohmann::json& json) {
        for (const auto& item : json) {
            const auto& id = item.at("Id");
            const auto& value = item.at("Value");
            if (!id.is_null() && !value.is_null()) {
                strings.insert(std::make_pair(id.get<std::string>(), value.get<std::string>()));
            }
            else if (id.is_null()) {
                std::cerr << "WARNING: Skipped record with no Id specified." << std::endl;
                return false;
            }
            else if (value.is_null()) {
                std::cerr << "WARNING: Skipped [" << id.get<std::string>() << "] record with no Value specified" << std::endl;
                return false;
            }
        }
        return true;
    }
};

class SummaryInformation : public Generator<KeyValue<int, std::string>> {
public:
    SummaryInformation(InstallerStrings& is) noexcept : installerStrings(is) {};
    ~SummaryInformation() = default;
    std::string generate() const override {
        const auto now = std::chrono::system_clock::now();
        const auto now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm;
        localtime_s(&now_tm, &now_time_t);
        std::ostringstream oss;
        oss << std::put_time(&now_tm, "%Y/%m/%d %H:%M:%S");

        constexpr auto codepage = 1252;
        constexpr auto pagecount = 200;
        constexpr auto wordcount = 0;
        constexpr auto security = 1;
        constexpr auto charcount = 0;
        const auto title = installerStrings.get("COMPANY_PRODUCT");
        const auto subject = installerStrings.get("COMPANY_PRODUCT_SUBJECT");
        const auto author = installerStrings.get("COMPANY_NAME");
        const auto keywords = std::string("BOINC");
        const auto comments = installerStrings.get("IDS_FEATURE_BOINC_DESCRIPTION");
        const auto arch = std::string("AMD64;1033");
        const auto lastauthor = std::string("BOINC");
        const auto revision = GuidHelper::generate_guid();
        const auto lastprinted = oss.str();
        const auto createdtm = oss.str();
        const auto lastsavedtm = oss.str();
        const auto appname = std::string("BOINC");

        std::vector<KeyValue<int, std::string>> properties;
        properties.emplace_back(1, std::to_string(codepage));
        properties.emplace_back(2, title);
        properties.emplace_back(3, subject);
        properties.emplace_back(4, author);
        properties.emplace_back(5, keywords);
        properties.emplace_back(6, comments);
        properties.emplace_back(7, arch);
        properties.emplace_back(8, lastauthor);
        properties.emplace_back(9, revision);
        properties.emplace_back(11, lastprinted);
        properties.emplace_back(12, createdtm);
        properties.emplace_back(13, lastsavedtm);
        properties.emplace_back(14, std::to_string(pagecount));
        properties.emplace_back(15, std::to_string(wordcount));
        properties.emplace_back(16, std::to_string(charcount));
        properties.emplace_back(18, appname);
        properties.emplace_back(19, std::to_string(security));

        std::vector<std::string> columns = { "PropertyId", "Value" };
        std::vector<std::string> types = { "i2", "l255" };
        std::vector<std::string> keys = { "_SummaryInformation", "PropertyId" };

        return Generator::generate(columns, types, keys, properties);
    }
private:
    InstallerStrings& installerStrings;
};

class Installer {
public:
    Installer() = default;
    ~Installer() = default;
    void load() {
        installerStrings.load();
    }
    void generate() {
        SummaryInformation si(installerStrings);
        std::cout << si.generate() << std::endl;
    }
private:
    InstallerStrings installerStrings;
};

int main(int argc, char** argv) {
    Installer installer;
    installer.load();
    installer.generate();
    return 0;
}
