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


// display the contents of a thread.

require_once('../inc/util.inc');
require_once('../inc/forum.inc');
require_once('../inc/news.inc');

$threadid = get_int('id');
$sort_style = get_int('sort', true);
$temp_sort_style = get_int('temp_sort_style', true);
$start = get_int('start', true);
$postid = get_int('postid', true);
$filter = get_str('filter', true);

if ($filter != "false"){
    $filter = true;
} else {
    $filter = false;
}

$logged_in_user = get_logged_in_user(false);

$tokens = "";
if ($logged_in_user) {
    BoincForumPrefs::lookup($logged_in_user);
    $tokens = url_tokens($logged_in_user->authenticator);
}

if (DISABLE_FORUMS && !is_admin($logged_in_user)) {
    error_page("Forums are disabled");
}

if ($threadid < 1) {
    error_page("Invalid thread ID!");
}

$thread = BoincThread::lookup_id($threadid);

if (!$thread) {
    error_page("Bad thread ID");
}
$forum = BoincForum::lookup_id($thread->forum);

if (!is_forum_visible_to_user($forum, $logged_in_user)) {
    if ($logged_in_user) {
        remove_subscriptions_forum($logged_in_user->id, $forum->id);
    }
    error_page(tra("This forum is not visible to you."));
}

if ($thread->hidden) {
    if (!is_moderator($logged_in_user, $forum)) {
        if ($logged_in_user) {
            remove_subscriptions_forum($logged_in_user->id, $thread->id);
        }
        error_page(tra("This thread has been hidden by moderators."));
    }
}

$title = cleanup_title($thread->title);
if ($temp_sort_style) {
    $sort_style = $temp_sort_style;
} else if ($sort_style) {
    $forum_style = 0;   // this is deprecated
    if ($logged_in_user){
        $logged_in_user->prefs->thread_sorting = $sort_style;
        $logged_in_user->prefs->update("thread_sorting=$sort_style");
    } else {
        list($forum_style, $old_style) = parse_forum_cookie();
    }
    send_cookie('sorting',
        implode("|", array($forum_style, $sort_style)),
        true
    );
} else {
    // get the sorting style from the user or a cookie
    if ($logged_in_user){
        $sort_style = $logged_in_user->prefs->thread_sorting;
    } else {
        list($forum_style, $sort_style) = parse_forum_cookie();
    }
}

page_head("Thread '$title'", 'onload="jumpToUnread();"');

$is_subscribed = $logged_in_user && BoincSubscription::lookup($logged_in_user->id, $thread->id);

echo "<p>";
switch ($forum->parent_type) {
case 0:
    $category = BoincCategory::lookup_id($forum->category);
    echo forum_title($category, $forum, $thread);
    break;
case 1:
    echo team_forum_title($forum, $thread);
    break;
}
echo "<br><small><a href=moderation.php>".tra("Message board moderation")."</a></small>
";

if (false) {
if ($forum->parent_type == 0) {
    if ($category->is_helpdesk && !$thread->status){
        if ($logged_in_user){
            if ($thread->owner == $logged_in_user->id){
                if ($thread->replies !=0) {
                    // Show a "this question has been answered" to the author
                    echo "<p>";
                    show_button(
                        "forum_thread_status.php?id=$thread->id&action=set",
                        tra("My question was answered"),
                        tra("Click here if your question has been adequately answered")
                    );
                }
            } else {
                // and a "I also got this question" to everyone else
                echo "<p>";
                show_button(
                    "forum_thread_vote.php?id=$thread->id",
                    tra("I've also got this question")
                );
            }
        }
    }
}
}

echo '
    <p>
    <form class="form-inline" action="forum_thread.php">
    <table width="100%" cellspacing=0 cellpadding=0>
    <tr>
    <td>
';

$reply_url = "";
if (!$logged_in_user) {
    echo "To post messages, you must <a href=login_form.php>log in</a>.";
} else {
    if (can_reply($thread, $forum, $logged_in_user)) {
        $reply_url = "forum_reply.php?thread=".$thread->id."#input";
        show_button_small(
            $reply_url,
            tra("Post to thread"),
            tra("Add a new message to this thread")
        );
    }

    if ($is_subscribed) {
        BoincNotify::delete_aux(sprintf(
            'userid=%d and type=%d and opaque=%d',
            $logged_in_user->id,
            NOTIFY_SUBSCRIBED_THREAD,
            $thread->id
        ));
        $url = "forum_subscribe.php?action=unsubscribe&amp;thread=".$thread->id."$tokens";
        show_button_small(
            $url,
            tra("Unsubscribe"),
            tra("You are subscribed to this thread.  Click here to unsubscribe.")
        );
    } else {
        $url = "forum_subscribe.php?action=subscribe&amp;thread=".$thread->id."$tokens";
        show_button_small(
            $url,
            tra("Subscribe"),
            tra("Click to get notified when there are new posts in this thread")
        );
    }

    // If logged in user is moderator, enable some extra features
    //
    if (is_moderator($logged_in_user, $forum)) {
        if ($thread->hidden){
            show_button_small(
                "forum_moderate_thread_action.php?action=unhide&amp;thread=".$thread->id."$tokens",
                tra("Unhide"),
                tra("Unhide this thread")
            );
        } else {
            show_button_small(
                "forum_moderate_thread.php?action=hide&amp;thread=".$thread->id,
                tra("Hide"),
                tra("Hide this thread")
            );
        }
        if ($thread->sticky){
            show_button_small(
                "forum_moderate_thread_action.php?action=desticky&amp;thread=".$thread->id."$tokens",
                tra("Make unsticky"),
                tra("Make this thread not sticky")
            );
        } else {
            show_button_small(
                "forum_moderate_thread_action.php?action=sticky&amp;thread=".$thread->id."$tokens",
                tra("Make sticky"),
                tra("Make this thread always appear at top of forum")
            );
        }
        if ($thread->locked) {
            show_button_small(
                "forum_moderate_thread_action.php?action=unlock&amp;thread=".$thread->id."$tokens",
                tra("Unlock"),
                tra("Allow new posts in this thread")
            );
        } else {
            show_button_small(
                "forum_moderate_thread.php?action=lock&amp;thread=".$thread->id."$tokens",
                tra("Lock"),
                tra("Don't allow new posts in this thread")
            );
        }
        if ($forum->parent_type == 0) {
            show_button_small(
                "forum_moderate_thread.php?action=move&amp;thread=".$thread->id."$tokens",
                tra("Move"),
                tra("Move this thread to a different forum")
            );
        }
        show_button_small(
            "forum_moderate_thread.php?action=title&amp;thread=".$thread->id."$tokens",
            tra("Edit title"),
            tra("Edit thread title")
        );
    }

    if (is_admin($logged_in_user)) {
        show_button_small(
            "forum_moderate_thread.php?action=delete&amp;thread=".$thread->id."$tokens",
            tra("Delete"),
            tra("Delete thread permanently")
        );
    }

    // let admins decide whether a news item should be exported as notice
    //
    if (is_news_forum($forum) && $logged_in_user && ($logged_in_user->id == $thread->owner)) {
        if ($thread->status) {
            show_button_small(
                "forum_thread_status.php?action=clear&amp;id=$thread->id",
                tra("Export as Notice"),
                "Show this message to all volunteers in the desktop GUI.  Use this only for messages of interest or importance to all volunteers."
            );
        } else {
            show_button_small(
                "forum_thread_status.php?action=set&amp;id=$thread->id",
                tra("Don't export"),
                tra("Don't export this news item as a Notice")
            );
        }
    }
}

// Display a box that allows the user to select sorting of the posts
//
echo '</td><td align="right">
    <input type="hidden" name="id" value="', $thread->id, '">
    <div class="form-group">
';
echo select_from_array("sort", $thread_sort_styles, $sort_style);
echo ' <input class="btn btn-default btn-sm" type="submit" value="'.tra('Sort').'">
    </div>
    </td></tr></table>
    </form><p>
';

// if it's news, show original post first
//
if (is_news_forum($forum) && !is_moderator($logged_in_user, null)) {
    $sort_style = CREATE_TIME_OLD;
}

show_posts(
    $thread, $forum, $start, $postid, $sort_style, $filter, $logged_in_user
);

if ($reply_url) {
    //echo "<br>";
    show_button(
        $reply_url,
        tra("Post to thread"),
        tra("Add a new message to this thread")
    );
}

echo "<p></p>";
switch ($forum->parent_type) {
case 0:
    echo forum_title($category, $forum, $thread);
    break;
case 1:
    echo team_forum_title($forum, $thread);
    break;
}

$thread->update("views=views+1");

page_tail();
?>
