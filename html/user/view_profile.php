<?php
// This file is part of BOINC.
// http://boinc.berkeley.edu
// Copyright (C) 2008 University of California
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

require_once("../inc/profile.inc");

if (DISABLE_PROFILES) error_page("Profiles are disabled");

check_get_args(array("userid"));

$userid = get_int('userid');
$user = BoincUser::lookup_id($userid);
if (!$user) {
    error_page(tra("No such user"));
}
if (!$user->has_profile) {
    // check whether user.has_profile is out of synch w/ profile table
    //
    $profile = BoincProfile::lookup("userid=$user->id");
    if ($profile) {
        $user->update("has_profile=1");
        $user->has_profile = 1;
    } else {
        error_page(tra("This user has no profile"));
    }
}

$logged_in_user = get_logged_in_user(false);
check_whether_to_show_profile($user, $logged_in_user);

$cache_args = "userid=$userid";
$cacheddata = get_cached_data(USER_PROFILE_TTL, $cache_args);
if ($cacheddata){
    // Already got a cached version of the information
    $community_links_object = unserialize($cacheddata);
} else {
    // Need to generate a new bunch of data
    $community_links_object = get_community_links_object($user);
    set_cached_data(USER_PROFILE_TTL, serialize($community_links_object), $cache_args);
}

page_head(tra("Profile: %1", $user->name));

start_table();
echo "<tr><td valign=\"top\">";
start_table();
show_profile($user, $logged_in_user);
end_table();
echo "</td><td valign=\"top\">";
start_table("table-striped");
row2(tra("User info"),
    sprintf(
        '<a href="%s?userid=%d">%s</a>',
        SHOW_USER_PAGE, $userid, tra("View")
    )
);

community_links($community_links_object, $logged_in_user);
end_table();
echo "</td></tr>";
end_table();

page_tail();
?>
