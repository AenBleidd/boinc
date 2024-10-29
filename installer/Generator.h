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
#include <iostream>

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

    bool generate(MSIHANDLE hDatabase, const std::string& sql_create, const std::string& sql_insert, const std::vector<V>& records) {
        MSIHANDLE hView;
        if (MsiDatabaseOpenView(hDatabase, sql_create.c_str(), &hView) != ERROR_SUCCESS) {
            std::cerr << "Error creating view for ActionTextTable" << std::endl;
            return false;
        }
        if (MsiViewExecute(hView, 0) != ERROR_SUCCESS) {
            std::cerr << "Error executing view for ActionTextTable" << std::endl;
            return false;
        }
        if (MsiViewClose(hView) != ERROR_SUCCESS) {
            std::cerr << "Error closing view for ActionTextTable" << std::endl;
            return false;
        }
        if (MsiDatabaseOpenView(hDatabase, sql_insert.c_str(), &hView) != ERROR_SUCCESS) {
            std::cerr << "Error creating view for ActionTextTable" << std::endl;
            return false;
        }
        for (const auto& record : records) {
            const auto hRecord = record.getRecord();
            if (MsiViewExecute(hView, hRecord) != ERROR_SUCCESS) {
                std::cerr << "Error inserting record for ActionTextTable" << std::endl;
                return false;
            }
            if (MsiCloseHandle(hRecord) != ERROR_SUCCESS) {
                std::cerr << "Error closing record for ActionTextTable" << std::endl;
                return false;
            }
        }
        if (MsiViewClose(hView) != ERROR_SUCCESS) {
            std::cerr << "Error closing view for ActionTextTable" << std::endl;
            return false;
        }
        return true;
    }

    virtual bool generate(MSIHANDLE hDatabase) { return false; };

};
