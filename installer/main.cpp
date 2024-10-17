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

#include <iostream>
#include <fstream>

#include "GuidHelper.h"
#include "KeyValue.h"
#include "ActionText.h"
#include "Action.h"
#include "Dialog.h"
#include "Generator.h"
#include "InstallerStrings.h"

#include "SummaryInformationTable.h"
#include "ActionTextTable.h"
#include "AdminExecuteSequenceTable.h"
#include "AdminUISequenceTable.h"
#include "AdvtExecuteSequenceTable.h"
#include "InstallExecuteSequenceTable.h"
#include "InstallUISequenceTable.h"

class Installer {
public:
    Installer() = default;
    ~Installer() = default;
    void load() {
        installerStrings.load();
    }
    void generate() {
        SummaryInformationTable si(installerStrings);
        std::cout << "==== SummaryInformation ====" << std::endl;
        std::cout << si.generate() << std::endl;
        ActionTextTable at(installerStrings);
        std::cout << "==== ActionText Table ====" << std::endl;
        std::cout << at.generate() << std::endl;
        AdminExecuteSequenceTable aes;
        std::cout << "==== AdminExecuteSequence Table ====" << std::endl;
        std::cout << aes.generate() << std::endl;
        AdminUISequenceTable aus;
        std::cout << "==== AdminUISequence Table ====" << std::endl;
        std::cout << aus.generate() << std::endl;
        AdvtExecuteSequenceTable aes2;
        std::cout << "==== AdvtExecuteSequence Table ====" << std::endl;
        std::cout << aes2.generate() << std::endl;

        InstallExecuteSequenceTable ies;
        std::cout << "==== InstallExecuteSequence Table ====" << std::endl;
        std::cout << ies.generate() << std::endl;
        InstallUISequenceTable ius;
        std::cout << "==== InstallUISequence Table ====" << std::endl;
        std::cout << ius.generate() << std::endl;
    }
private:
    InstallerStrings installerStrings;
};

int main(int argc, char** argv) {
    Installer installer;
    installer.load();
    installer.generate();
    return 0;
}
