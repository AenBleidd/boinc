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

Dialog::Dialog(const std::string& dialog, const int hcentering, const int vcentering, const int width, const int height, const int attributes, const std::string& title)
    : dialog(dialog), hcentering(hcentering), vcentering(vcentering), width(width), height(height), attributes(attributes), title(title) {};
std::string Dialog::get() const {
    std::ostringstream oss;
    oss << dialog << "\t" << hcentering << "\t" << vcentering << "\t" << width << "\t" << height << "\t" << attributes << "\t" << title << "\t" << first->get_name() << "\t" << default->get_name() << "\t" << cancel->get_name() << "\n";
    return oss.str();
}
std::string Dialog::get_name() const {
    return dialog;
}
std::vector<std::shared_ptr<Control>>& Dialog::get_controls() noexcept {
    return controls;
}
void Dialog::add(std::shared_ptr<Control> control, bool f, bool d, bool c) {
    if (f) {
        first = control;
    }
    if (d) {
        default = control;
    }
    if (c) {
        cancel = control;
    }
    controls.emplace_back(control);
}
