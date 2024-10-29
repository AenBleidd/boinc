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

#include <string>
#include <vector>

#include "Windows.h"
#include "Msi.h"
#include "MsiQuery.h"

template <typename V>
class Generator {
public:
    Generator() = default;
    virtual ~Generator() = default;
    virtual std::string generate(const std::vector<std::pair<std::string, std::string>>& columns, const std::vector<std::string>& keys, const std::vector<V>& values) const {
        std::string result;
        std::string cols;
        std::string types;
        for (const auto& column : columns) {
            cols += column.first + "\t";
            types += column.second + "\t";
        }
        result += cols + "\n" + types + "\n";
        for (const auto& key : keys) {
            result += key + "\t";
        }
        result += "\n";
        for (const auto& value : values) {
            result += value.get();
        }
        return result;
    }
    virtual bool generate(MSIHANDLE hDatabase) { return false; };
};
