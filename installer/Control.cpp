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

Control::Control(const std::string& control, const std::string& type, const int x, const int y, const int width, const int height, const int attributes, const std::shared_ptr<Property> property, const std::string& text, const std::string& help)
    : control(control), type(type), x(x), y(y), width(width), height(height), attributes(attributes), property(property), text(text), help(help) {};
std::string Control::get() const {
    std::ostringstream oss;
    oss << control << "\t" << type << "\t" << x << "\t" << y << "\t" << width << "\t" << height << "\t" << attributes << "\t" << property->get_name() << "\t" << text << "\t" << (next.lock() ? next.lock()->get_name() : "\t") << "\t" << help << "\n";
    return oss.str();
}
const std::string& Control::get_name() const {
    return control;
}
void Control::set_next(std::shared_ptr<Control> n) noexcept {
    next = n;
}
