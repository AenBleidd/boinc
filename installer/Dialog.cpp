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

#include <sstream>

#include "Dialog.h"
#include "Control.h"

Dialog::Dialog(const std::string& dialog, const int hcentering, const int vcentering, const int width, const int height, const int attributes, const std::string& title, const std::string& first, const std::string& default, const std::string& cancel)
    : dialog(dialog), hcentering(hcentering), vcentering(vcentering), width(width), height(height), attributes(attributes), title(title), first(first), default(default), cancel(cancel) {};
std::string Dialog::get() const {
    std::ostringstream oss;
    oss << dialog << "\t" << hcentering << "\t" << vcentering << "\t" << width << "\t" << height << "\t" << attributes << "\t" << title << "\t" << first << "\t" << default << "\t" << cancel << "\n";
    return oss.str();
}
std::vector<Control>& Dialog::get_controls() noexcept {
    return controls;
}
void Dialog::add(Control control) {
    controls.emplace_back(control);
}
