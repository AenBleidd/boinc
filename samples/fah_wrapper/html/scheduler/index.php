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

require_once("../inc/xml.inc");
require_once("../inc/fah.inc");

xml_header();

echo "
<scheduler_reply>
    <master_url>$wrapper_server_url</master_url>
    <request_delay>300</request_delay>
    <message priority='low'>Project is temporarily shut down for maintenance</message>
    <project_name>$project_name</project_name>
    <project_is_down/>
</scheduler_reply>
";

?>