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

require_once("inc/fah.inc");

?>
<html>
<head>
    <title>$project_name</title>
    
<?php

echo "
<!--
<scheduler>$wrapper_server_url/scheduler</scheduler>
<link rel='boinc_scheduler' href='$wrapper_server_url/scheduler'>
-->
";

?>

</head>
<body>
    <h1>It works!</h1>
</body>

</html>
