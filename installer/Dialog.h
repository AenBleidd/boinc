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

#include <vector>

#include "Record.h"
#include "Control.h"

enum ATTRIBUTE {
    VISIBLE = 1,
    MODAL = 2,
    MINIMIZE = 4,
    SYSMODAL = 8,
    KEEP_MODELESS = 16,
    TRACK_DISK_SPACE = 32,
    USE_CUSTOM_PALETTE = 64,
    RTLRO = 128,
    RIGHT_ALIGNED = 256,
    LEFT_SCROLL = 512,
    BIDI = RTLRO | RIGHT_ALIGNED | LEFT_SCROLL,
    ATTRIBUTE_ERROR = 65536
};

class Dialog : public Record {
public:
    explicit Dialog(const std::string& dialog, int hcentering, int vcentering, int width, int height, int attributes, const std::string& title,
        const std::string& first, const std::string& default, const std::string& cancel, const std::vector<Control>& controls);
    ~Dialog() = default;
    std::string get() const override;
    std::vector<Control> get_controls() const;
private:
    std::string dialog;
    int hcentering;
    int vcentering;
    int width;
    int height;
    int attributes;
    std::string title;
    std::string first;
    std::string default;
    std::string cancel;
    std::vector<Control> controls;
};
