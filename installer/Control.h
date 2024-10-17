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

#include "Dialog.h"
#include "Property.h"

class CONTROL_TYPE {
    static auto Billboard() noexcept { return "Billboard"; }
    static auto Bitmap() noexcept { return "Bitmap"; }
    static auto CheckBox() noexcept { return "CheckBox"; }
    static auto ComboBox() noexcept { return "ComboBox"; }
    static auto DirectoryCombo() noexcept { return "DirectoryCombo"; }
    static auto DirectoryList() noexcept { return "DirectoryList"; }
    static auto Edit() noexcept { return "Edit"; }
    static auto GroupBox() noexcept { return "GroupBox"; }
    static auto Hyperlink() noexcept { return "Hyperlink"; }
    static auto Icon() noexcept { return "Icon"; }
    static auto Line() noexcept { return "Line"; }
    static auto ListBox() noexcept { return "ListBox"; }
    static auto ListView() noexcept { return "ListView"; }
    static auto MaskedEdit() noexcept { return "MaskedEdit"; }
    static auto PathEdit() noexcept { return "PathEdit"; }
    static auto ProgressBar() noexcept { return "ProgressBar"; }
    static auto PushButton() noexcept { return "PushButton"; }
    static auto RadioButtonGroup() noexcept { return "RadioButtonGroup"; }
    static auto ScrollableText() noexcept { return "ScrollableText"; }
    static auto SelectionTree() noexcept { return "SelectionTree"; }
    static auto Text() noexcept { return "Text"; }
    static auto VolumeCostList() noexcept { return "VolumeCostList"; }
    static auto VolumeSelectCombo() noexcept { return "VolumeSelectCombo"; }
};

class Control : public Record {
public:
    explicit Control(const std::weak_ptr<Dialog> dialog, const std::string& control, const std::string& type, const int x, const int y, const int width, const int height, const int attributes, const std::shared_ptr<Property> property, const std::string& text, const std::string& help);
    ~Control() = default;
    std::string get() const override;
    const std::string& get_name() const;
    void set_next(std::shared_ptr<Control> n) noexcept;
private:
    std::weak_ptr<Dialog> dialog;
    std::string control;
    std::string type;
    int x;
    int y;
    int width;
    int height;
    int attributes;
    std::shared_ptr<Property> property;
    std::string text;
    std::weak_ptr<Control> next;
    std::string help;
};
