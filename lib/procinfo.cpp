// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2011 University of California
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

// platform-independent process-enumeration functions

#if   defined(_WIN32) && !defined(__STDWX_H__)
#include "boinc_win.h"
#include "win_util.h"
#elif defined(_WIN32) && defined(__STDWX_H__)
#include "stdwx.h"
#else
#include "config.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#endif

#include "util.h"

#include "procinfo.h"

using std::vector;

// Scan the process table adding in CPU time and mem usage.
//
void add_child_totals(PROCINFO& procinfo, PROC_MAP& pm, PROC_MAP::iterator i) {
    PROCINFO parent = i->second;
    for (unsigned int j=0; j<parent.children.size(); j++) {
        int child_pid = parent.children[j];
        PROC_MAP::iterator i2 = pm.find(child_pid);
        if (i2 == pm.end()) continue;
        PROCINFO& p = i2->second;
        if (p.scanned) {
            return;     // cycle in graph - shouldn't happen
        }
        procinfo.kernel_time += p.kernel_time;
        procinfo.user_time += p.user_time;
        p.scanned = true;

        // only count process with most swap and memory
        if (p.swap_size > procinfo.swap_size) {
            procinfo.swap_size = p.swap_size;
        }
        if (p.working_set_size > procinfo.working_set_size) {
            procinfo.working_set_size = p.working_set_size;
        }

        p.is_boinc_app = true;
        add_child_totals(procinfo, pm, i2); // recursion - woo hoo!
    }
}

// Fill in the given PROCINFO (initially zero except for id)
// with totals from that process and all its descendants.
// Set PROCINFO.is_boinc_app for all of them.
//
void procinfo_app(
    PROCINFO& procinfo, vector<int>* other_pids, PROC_MAP& pm, char* graphics_exec_file
) {
    PROC_MAP::iterator i;
    for (i=pm.begin(); i!=pm.end(); ++i) {
        PROCINFO& p = i->second;
        if (p.id == procinfo.id
            || (other_pids && in_vector(p.id, *other_pids))
        ) {
            procinfo.kernel_time += p.kernel_time;
            procinfo.user_time += p.user_time;
            procinfo.swap_size += p.swap_size;
            procinfo.working_set_size += p.working_set_size;
            p.is_boinc_app = true;
            p.scanned = true;

            // look for child processes
            //
            add_child_totals(procinfo, pm, i);
        }
        if (graphics_exec_file && !strcmp(p.command, graphics_exec_file)) {
            p.is_boinc_app = true;
        }
    }
}

void find_children(PROC_MAP& pm) {
    PROC_MAP::iterator i;
    for (i=pm.begin(); i!=pm.end(); ++i) {
        int parentid = i->second.parentid;
        PROC_MAP::iterator j = pm.find(parentid);
        if (j == pm.end()) continue;    // should never happen
        j->second.children.push_back(i->first);
    }
}

// get resource usage of non-BOINC apps
//
void procinfo_non_boinc(PROCINFO& procinfo, PROC_MAP& pm) {
    procinfo.clear();
    PROC_MAP::iterator i;
    for (i=pm.begin(); i!=pm.end(); ++i) {
        PROCINFO& p = i->second;
#ifdef _WIN32
        if (p.id == 0) continue;    // idle process
#endif
        if (p.is_boinc_app) continue;
        if (p.is_low_priority) continue;

        // count VirtualBox process as BOINC;
        // on some systems they use nontrivial CPU time
        // TODO: do this only if we're running a vbox app
        //
        if (strstr(p.command, "VBoxSVC")) continue;
        if (strstr(p.command, "VBoxXPCOMIPCD")) continue;

#if 0
        if (p.user_time > .1) {
            fprintf(stderr, "non-boinc: %s (%d) %f %f\n", p.command, p.id, p.user_time, p.kernel_time);
        }
#endif
        procinfo.kernel_time += p.kernel_time;
        procinfo.user_time += p.user_time;
        procinfo.swap_size += p.swap_size;
        procinfo.working_set_size += p.working_set_size;
    }
#if 0
    fprintf(stderr, "total non-boinc: %f %f\n", procinfo.user_time, procinfo.kernel_time);
#endif
}

double process_tree_cpu_time(int pid) {
    PROC_MAP pm;
    PROCINFO procinfo;
    int retval;

    retval = procinfo_setup(pm);
    if (retval) return 0;

    procinfo.clear();
    procinfo.id = pid;
    procinfo_app(procinfo, NULL, pm, NULL);
    return procinfo.user_time + procinfo.kernel_time;
}
