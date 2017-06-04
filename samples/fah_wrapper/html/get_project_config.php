<?php
// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2017 University of California
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

require_once("inc/xml.inc");
require_once("inc/fah.inc");

xml_header();

echo "<project_config>
    <name>Folding@home</name>
    <master_url>$wrapper_server_url</master_url>
    <web_stopped>0</web_stopped>
    <account_creation_disabled/>
    <sched_stopped>0</sched_stopped>
    <uses_username/>
";

echo "</project_config>";

?>