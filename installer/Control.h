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

#pragma once

#include <sstream>
#include <vector>
#include <nlohmann/json.hpp>


#include "Property.h"
#include "ControlCondition.h"
#include "InstallerStrings.h"

class Control : public Record {
public:
    explicit Control(const nlohmann::json& json, const InstallerStrings& installerStrings, const std::string& dialog);
    ~Control() = default;
    std::string get() const override;
    const std::vector<ControlCondition>& get_conditions() const noexcept;
private:
    std::string dialog;
    std::string control;
    std::string type;
    int x;
    int y;
    int width;
    int height;
    int attributes;
    std::string property;
    std::string text;
    std::string next;
    std::string help;
    std::vector<ControlCondition> conditions;
};
