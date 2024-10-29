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

#include <nlohmann/json.hpp>
#include "SummaryInformationTable.h"
#include "InstallerStrings.h"
#include "ActionTextTable.h"
#include "AdminExecuteSequenceTable.h"
#include "AdminUISequencetable.h"
#include "AdvtExecuteSequenceTable.h"
#include "ControlTable.h"
#include "ControlConditionTable.h"
#include "DialogTable.h"
#include "InstallExecuteSequenceTable.h"
#include "InstallUISequenceTable.h"

class Installer {
public:
    explicit Installer() noexcept = default;
    ~Installer() = default;
    bool load();
    bool generate() const;
    bool create_msi();
private:
    bool load_from_json(const nlohmann::json& json);

    
    InstallerStrings installer_strings;
    SummaryInformationTable summary_information_table;
    ActionTextTable action_text_table;
    AdminExecuteSequenceTable admin_execute_sequence_table;
    AdminUISequenceTable admin_ui_sequence_table;
    AdvtExecuteSequenceTable advt_execute_sequence_table;
    ControlTable control_table;
    ControlConditionTable control_condition_table;
    DialogTable dialog_table;
    InstallExecuteSequenceTable install_execute_sequence_table;
    InstallUISequenceTable install_ui_sequence_table;
};
