<?php
// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2014 University of California
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

// Use this file you can vote for a thread.
// It simply votes for the first post in the thread.

require_once('../inc/forum.inc');

if (DISABLE_FORUMS) error_page("Forums are disabled");

check_get_args(array("id"));

$threadid = get_int('id');
$thread = BoincThread::lookup_id($threadid);
if (!$thread) error_page('No such thread');
$logged_in_user = get_logged_in_user();

$posts = get_thread_posts($threadid, 0,true);
header("Location: forum_rate.php?choice=p&post=".$posts[0]->id);
?>
