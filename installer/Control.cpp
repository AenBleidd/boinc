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

#include "Control.h"

Control::Control(const std::string& dialog, const std::string& control, const std::string& type, int x, int y, int width, int height, int attributes,
    const std::string& property, const std::string& text, const std::string& next, const std::string& help, const std::vector<ControlCondition>& conditions)
    : dialog(dialog), control(control), type(type), x(x), y(y), width(width), height(height), attributes(attributes), property(property), text(text),
    next(next), help(help), conditions(conditions) {};
std::string Control::get() const {
    std::ostringstream oss;
    oss << dialog << "\t" << control << "\t" << type << "\t" << x << "\t" << y << "\t" << width << "\t" << height << "\t" << attributes << "\t" << property << "\t" << text << "\t" << next << "\t" << help << "\n";
    return oss.str();
}

const std::vector<ControlCondition>& Control::get_conditions() const noexcept {
    return conditions;
}
