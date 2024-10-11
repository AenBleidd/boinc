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
#include <nlohmann/json.hpp>

class InstallerStrings {
public:
    std::string get(const std::string& key) {
        return strings.at(key);
    };
    void load_from_json(const nlohmann::json &json) {
        for (auto& item : json) {
            auto &id = item.at("Id");
            auto &value = item.at("Value");
            if (!id.is_null() && !value.is_null()) {
                strings.insert(std::make_pair(id.get<std::string>(), value.get<std::string>()));
            }
        }
    }                    
private:
    std::map<std::string, std::string> strings;
};

class Installer {

};

int main(int argc, char** argv) {
    std::ifstream file("../installer/locale/en.json");
    if (!file.is_open()) {
        std::cerr << "Could not open file" << std::endl;
        return 1;
    }
    nlohmann::json j;
    file >> j;
    InstallerStrings installerStrings;
    installerStrings.load_from_json(j);
    return 0;
}
