/*
 * This file is part of BOINC.
 * http://boinc.berkeley.edu
 * Copyright (C) 2021 University of California
 *
 * BOINC is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * BOINC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with BOINC.  If not, see <http://www.gnu.org/licenses/>.
 */
package edu.berkeley.boinc.client;

import android.annotation.SuppressLint;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.util.Log;

import androidx.annotation.VisibleForTesting;
import androidx.core.app.NotificationCompat;
import androidx.core.content.ContextCompat;

import java.util.ArrayList;
import java.util.List;

import javax.inject.Inject;
import javax.inject.Singleton;

import edu.berkeley.boinc.BOINCActivity;
import edu.berkeley.boinc.R;
import edu.berkeley.boinc.rpc.Result;
import edu.berkeley.boinc.utils.BOINCUtils;
import edu.berkeley.boinc.utils.Logging;

@Singleton
public class ClientNotification {
    private Context context;
    private NotificationManager nm;
    private Integer notificationId;
    private PendingIntent contentIntent;
    private Notification n;

    private int mOldComputingStatus = -1;
    private int mOldSuspendReason = -1;
    private List<Result> mOldActiveTasks = new ArrayList<>();
    private boolean notificationShown = false;
    // debug foreground state by running
    // adb shell: dumpsys activity services edu.berkeley.boinc
    @VisibleForTesting()
    protected boolean foreground = false;

    @Inject
    public ClientNotification(Context context) {
        this.context = context;
        this.nm = ContextCompat.getSystemService(context, NotificationManager.class);
        notificationId = context.getResources().getInteger(R.integer.autostart_notification_id);
        Intent intent = new Intent(context, BOINCActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        intent.putExtra("targetFragment", R.string.tab_tasks);
        contentIntent = PendingIntent.getActivity(context, 0, intent, Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_NEW_TASK);
    }

    /**
     * Updates notification with client's current status. Notifies if not present. Checking
     * notification-related preferences.
     *
     * @param updatedStatus client status data
     * @param service       reference to service, sets to foreground if active
     * @param active        indicator whether BOINC should stay in foreground (during computing and
     *                      idle, i.e. not suspended)
     */
    public void update(ClientStatus updatedStatus, Monitor service, boolean active) {
        // nop if data is not present
        if(service == null || updatedStatus == null) {
            return;
        }

        //check if active tasks have changed to force update
        boolean activeTasksChanged = false;
        if(active && updatedStatus.computingStatus == ClientStatus.COMPUTING_STATUS_COMPUTING) {
            List<Result> activeTasks = updatedStatus.getExecutingTasks();
            if(activeTasks.size() != mOldActiveTasks.size()) {
                activeTasksChanged = true;
            }
            else {
                for(int x = 0; x < activeTasks.size(); x++) {
                    if(!activeTasks.get(x).getName().equals(mOldActiveTasks.get(x).getName())) {
                        activeTasksChanged = true;

                        Log.d(Logging.TAG, "Active task: " + activeTasks.get(x).getName() +
                                ", old active task: " +
                                mOldActiveTasks.get(x).getName());
                        break;
                    }
                }
            }
            if(activeTasksChanged) {
                mOldActiveTasks = activeTasks;
            }
        }
        else if (!mOldActiveTasks.isEmpty()) {
            mOldActiveTasks.clear();
            activeTasksChanged = true;
        }

        // update notification, only if it hasn't been shown before, or after change in status
        Log.d(Logging.TAG,
                "ClientNotification: notification needs update? "
                + (mOldComputingStatus == -1)
                + activeTasksChanged
                + !notificationShown
                + (updatedStatus.computingStatus != mOldComputingStatus)
                + (updatedStatus.computingStatus == ClientStatus.COMPUTING_STATUS_SUSPENDED
                    && updatedStatus.computingSuspendReason != mOldSuspendReason));

        if(mOldComputingStatus == -1
           || activeTasksChanged
           || !notificationShown
           || updatedStatus.computingStatus != mOldComputingStatus
           || (updatedStatus.computingStatus == ClientStatus.COMPUTING_STATUS_SUSPENDED
               && updatedStatus.computingSuspendReason != mOldSuspendReason)) {

            // update, build and notify
            nm.notify(notificationId, buildNotification(updatedStatus, active, mOldActiveTasks));

            Log.d(Logging.TAG, "ClientNotification: update");

            notificationShown = true;

            // save status for comparison next time
            mOldComputingStatus = updatedStatus.computingStatus;
            mOldSuspendReason = updatedStatus.computingSuspendReason;
        }

        // start foreground service, if requested
        // notification instance exists now, but might be out-dated (if screen is off)
        if(active && !foreground) {
            setForegroundState(service);
        }
    }

    // Notification must be built, before setting service to foreground!
    @VisibleForTesting()
    protected void setForegroundState(Monitor service) {
        service.startForeground(notificationId, n);

        Log.d(Logging.TAG, "ClientNotification.setForeground() start service as foreground.");

        foreground = true;
    }

    @SuppressLint("InlinedApi")
    @VisibleForTesting()
    protected Notification buildNotification(ClientStatus status, Boolean active, List<Result> activeTasks) {
        // get current client computing status
        Integer computingStatus = status.computingStatus;
        // get status strings from ClientStatus
        String statusDesc = status.getCurrentStatusDescription();
        String statusTitle = status.getCurrentStatusTitle();

        // build notification
        NotificationCompat.Builder nb = new NotificationCompat.Builder(context, "main-channel");
        nb.setContentTitle(statusTitle)
          .setSmallIcon(getIcon(computingStatus, true))
          .setLargeIcon(BOINCUtils.getBitmapFromVectorDrawable(context, getIcon(computingStatus, false)))
          .setContentIntent(contentIntent);

        // adapt priority based on computing status
        // computing: IDLE and COMPUTING (see wakelock handling)
        if(active) {
            nb.setPriority(Notification.PRIORITY_HIGH);
        }
        else {
            nb.setPriority(Notification.PRIORITY_LOW);
        }

        // set action based on computing status
        if(computingStatus == ClientStatus.COMPUTING_STATUS_NEVER) {
            // add resume button
            // 0 - only text. Unify all versions of android with text button.
            nb.addAction(0,
                         context.getString(R.string.menu_run_mode_enable), getActionIntent(2));
        }
        else {
            // add suspend button
            // 0 - only text. Unify all versions of android with text button.
            nb.addAction(0,
                         context.getString(R.string.menu_run_mode_disable), getActionIntent(1));
        }

        // set tasks if computing
        if(computingStatus == ClientStatus.COMPUTING_STATUS_COMPUTING && activeTasks != null && activeTasks.size() > 0) {
            // set summary text
            nb.setSubText(statusDesc);
            // set number as content info
            nb.setNumber(activeTasks.size());
            // set names in list
            NotificationCompat.InboxStyle inboxStyle = new NotificationCompat.InboxStyle();
            for(Result task : activeTasks) {
                String line = task.getProject() == null ? "" : task.getProject().getName();
                line += ": ";
                line += task.getApp() == null ? "" : task.getApp().getDisplayName();
                inboxStyle.addLine(line);
            }
            nb.setStyle(inboxStyle);
        }
        else {
            nb.setContentText(statusDesc);
        }

        n = nb.build();

        return n;
    }

    // creates pending intent to service with specified action code
    private PendingIntent getActionIntent(int actionCode) {
        Intent si = new Intent(context, Monitor.class);
        si.putExtra("action", actionCode);
        return PendingIntent.getService(context, 0, si, PendingIntent.FLAG_CANCEL_CURRENT);
    }

    // returns resource id of icon
    @VisibleForTesting()
    protected int getIcon(int status, boolean isSmall) {
        int icon;
        switch(status) {
            case ClientStatus.COMPUTING_STATUS_NEVER:
            case ClientStatus.COMPUTING_STATUS_SUSPENDED:
            case ClientStatus.COMPUTING_STATUS_IDLE:
                if (Build.VERSION.SDK_INT < Build.VERSION_CODES.LOLLIPOP && isSmall) {
                    icon = R.mipmap.ic_boinc_paused_white;
                }
                else {
                    icon = R.drawable.ic_boinc_paused;
                }
                break;
            default:
                if (Build.VERSION.SDK_INT < Build.VERSION_CODES.LOLLIPOP && isSmall) {
                    icon = R.mipmap.ic_boinc_white;
                } else {
                    icon = R.drawable.ic_boinc;
                }
        }
        return icon;
    }
}
