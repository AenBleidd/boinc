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

<?php

echo "<title>$project_name</title>";

echo "
<!--
<scheduler>$wrapper_server_url/scheduler</scheduler>
<link rel='boinc_scheduler' href='$wrapper_server_url/scheduler'>
-->
";

?>

</head>
<body>

<?php

 echo "
   <p><b>Configuration:</b></p>
   <p><b>Server URL: </b>$wrapper_server_url</p>
   <p><b>Project Name: </b>$project_name</p>
   <p><b>Project Key: </b>$project_key</p>
   ";

?>  

</body>

</html>
