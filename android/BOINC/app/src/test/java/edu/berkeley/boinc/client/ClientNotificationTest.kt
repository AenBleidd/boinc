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
package edu.berkeley.boinc.client

import android.app.Notification
import android.app.PendingIntent
import android.content.Context
import android.content.Intent
import androidx.test.core.app.ApplicationProvider
import edu.berkeley.boinc.R
import edu.berkeley.boinc.rpc.*
import edu.berkeley.boinc.utils.PROCESS_ABORTED
import edu.berkeley.boinc.utils.PROCESS_EXECUTING
import edu.berkeley.boinc.utils.PROCESS_SUSPENDED
import io.mockk.justRun
import io.mockk.mockkClass
import org.junit.jupiter.api.Assertions
//import org.junit.Assert
//import org.junit.Before
import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test
import org.junit.jupiter.api.assertDoesNotThrow
import org.junit.runner.RunWith
import org.powermock.modules.junit4.PowerMockRunner
import org.robolectric.RobolectricTestRunner

//@RunWith(RobolectricTestRunner::class)
@RunWith(PowerMockRunner::class)
class ClientNotificationTest {
    private lateinit var clientNotification: ClientNotification

    @BeforeEach
    fun setUp() {
        clientNotification = ClientNotification(ApplicationProvider.getApplicationContext())
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_NEVER then expect corresponding Notification title and text`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assertions.assertEquals(clientStatus.currentStatusTitle, notification.extras.get(Notification.EXTRA_TITLE))
        Assertions.assertEquals(clientStatus.currentStatusDescription, notification.extras.get(Notification.EXTRA_TEXT))
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_IDLE then expect corresponding Notification title and text`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_IDLE

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assertions.assertEquals(clientStatus.currentStatusTitle, notification.extras.get(Notification.EXTRA_TITLE))
        Assertions.assertEquals(clientStatus.currentStatusDescription, notification.extras.get(Notification.EXTRA_TEXT))
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_SUSPENDED then expect corresponding Notification title and text`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_SUSPENDED

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assertions.assertEquals(clientStatus.currentStatusTitle, notification.extras.get(Notification.EXTRA_TITLE))
        Assertions.assertEquals(clientStatus.currentStatusDescription, notification.extras.get(Notification.EXTRA_TEXT))
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_COMPUTING and activeTasks is null then expect corresponding Notification title and text`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_COMPUTING

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assertions.assertEquals(clientStatus.currentStatusTitle, notification.extras.get(Notification.EXTRA_TITLE))
        Assertions.assertEquals(clientStatus.currentStatusDescription, notification.extras.get(Notification.EXTRA_TEXT))
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_COMPUTING and activeTasks is empty then expect corresponding Notification title and text`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_COMPUTING

        val notification = clientNotification.buildNotification(clientStatus, true, listOf())
        Assertions.assertEquals(clientStatus.currentStatusTitle, notification.extras.get(Notification.EXTRA_TITLE))
        Assertions.assertEquals(clientStatus.currentStatusDescription, notification.extras.get(Notification.EXTRA_TEXT))
    }


    @Test
    fun `When ClientStatus is COMPUTING_STATUS_COMPUTING and activeTasks contains records then expect corresponding Notification title and text`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_COMPUTING

        val activeTasks = listOf(
            Result(project = Project(projectName = "Project 1"), app = App(name = "App Name 1")),
            Result(project = Project(projectName = "Project 2"), app = App(name = "App Name 2")),
        )

        val notification = clientNotification.buildNotification(clientStatus, true, activeTasks)
        Assertions.assertEquals(clientStatus.currentStatusTitle, notification.extras.get(Notification.EXTRA_TITLE))
        Assertions.assertEquals(clientStatus.currentStatusDescription, notification.extras.get(Notification.EXTRA_SUB_TEXT))
        Assertions.assertEquals(activeTasks.size, notification.number)
        val lines = notification.extras.getCharSequenceArray(Notification.EXTRA_TEXT_LINES)
        Assertions.assertNotNull(lines)
        Assertions.assertEquals(activeTasks.size, lines?.size)
        Assertions.assertEquals("Project 1: App Name 1", lines?.get(0)?.toString())
        Assertions.assertEquals("Project 2: App Name 2", lines?.get(1)?.toString())
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_COMPUTING and activeTasks contains records with Project equal null or App equal null then expect no exception thrown`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_COMPUTING

        val activeTasks = listOf(
            Result(app = App(name = "App Name 1")),
            Result(project = Project(projectName = "Project 2")),
            Result()
        )

        val notification = clientNotification.buildNotification(clientStatus, true, activeTasks)
        Assertions.assertEquals(activeTasks.size, notification.number)
        val lines = notification.extras.getCharSequenceArray(Notification.EXTRA_TEXT_LINES)
        Assertions.assertNotNull(lines)
        Assertions.assertEquals(activeTasks.size, lines?.size)
        Assertions.assertEquals(": App Name 1", lines?.get(0)?.toString())
        Assertions.assertEquals("Project 2: ", lines?.get(1)?.toString())
        Assertions.assertEquals(": ", lines?.get(2)?.toString())
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_NEVER then expect only one Notification Action with menu_run_mode_enable title`() {
        val context = ApplicationProvider.getApplicationContext<Context>()
        val clientStatus = ClientStatus(context, null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assertions.assertEquals(1, notification.actions.size)
        Assertions.assertEquals(context.getString(R.string.menu_run_mode_enable), notification.actions[0].title)
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_IDLE then expect only one Notification Action with menu_run_mode_disable title`() {
        val context = ApplicationProvider.getApplicationContext<Context>()
        val clientStatus = ClientStatus(context, null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_IDLE

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assertions.assertEquals(1, notification.actions.size)
        Assertions.assertEquals(context.getString(R.string.menu_run_mode_disable), notification.actions[0].title)
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_SUSPENDED then expect only one Notification Action with menu_run_mode_disable title`() {
        val context = ApplicationProvider.getApplicationContext<Context>()
        val clientStatus = ClientStatus(context, null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_SUSPENDED

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assertions.assertEquals(1, notification.actions.size)
        Assertions.assertEquals(context.getString(R.string.menu_run_mode_disable), notification.actions[0].title)
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_COMPUTING then expect only one Notification Action with menu_run_mode_disable title`() {
        val context = ApplicationProvider.getApplicationContext<Context>()
        val clientStatus = ClientStatus(context, null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_COMPUTING

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assertions.assertEquals(1, notification.actions.size)
        Assertions.assertEquals(context.getString(R.string.menu_run_mode_disable), notification.actions[0].title)
    }

    @Test
    fun `When active is true then expect Notification priority to be high`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        @Suppress("DEPRECATION")
        Assertions.assertEquals(Notification.PRIORITY_HIGH, notification.priority)
    }

    @Test
    fun `When active is false then expect Notification priority to be low`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        val notification = clientNotification.buildNotification(clientStatus, false, null)
        @Suppress("DEPRECATION")
        Assertions.assertEquals(Notification.PRIORITY_LOW, notification.priority)
    }

    @Test
    fun `When foreground is false then expect it to be true after setForeground call`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }

        clientNotification.setForegroundState(monitor)
        Assertions.assertTrue(clientNotification.foreground)
    }

    @Test
    fun `When updateStatus is null then expect no exception thrown`() {
        val monitor = mockkClass(Monitor::class)
        assertDoesNotThrow { clientNotification.update(null, monitor, true) }
    }

    @Test
    fun `When service is null then expect no exception thrown`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER
        assertDoesNotThrow { clientNotification.update(clientStatus, null, true) }
    }

    @Test
    fun `When updateStatus is null and service is null then expect no exception thrown`() {
        assertDoesNotThrow { clientNotification.update(null, null, true) }
    }

    @Test
    fun `When active is true then expect foreground to be true`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.foreground)
    }

    @Test
    fun `When active is false then expect foreground to be false`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        clientNotification.update(clientStatus, monitor, false)

        Assertions.assertFalse(clientNotification.foreground)
    }

    @Test
    fun `When active is false and foreground is true then expect foreground to be true`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        clientNotification.foreground = true
        clientNotification.update(clientStatus, monitor, false)

        Assertions.assertTrue(clientNotification.foreground)
    }

    @Test
    fun `When updatedStatus is COMPUTING_STATUS_NEVER then expect status updated`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.notificationShown)
        Assertions.assertTrue(clientNotification.mOldActiveTasks.isEmpty())
        Assertions.assertEquals(clientStatus.computingStatus, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(clientStatus.computingSuspendReason, clientNotification.mOldSuspendReason)
    }

    @Test
    fun `When updatedStatus is COMPUTING_STATUS_IDLE then expect status updated`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_IDLE

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.notificationShown)
        Assertions.assertTrue(clientNotification.mOldActiveTasks.isEmpty())
        Assertions.assertEquals(clientStatus.computingStatus, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(clientStatus.computingSuspendReason, clientNotification.mOldSuspendReason)
    }

    @Test
    fun `When updatedStatus is COMPUTING_STATUS_SUSPENDED then expect status updated`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_SUSPENDED

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.notificationShown)
        Assertions.assertTrue(clientNotification.mOldActiveTasks.isEmpty())
        Assertions.assertEquals(clientStatus.computingStatus, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(clientStatus.computingSuspendReason, clientNotification.mOldSuspendReason)
    }

    @Test
    fun `When updatedStatus is COMPUTING_STATUS_COMPUTING and executingTasks is empty then expect status updated`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_COMPUTING

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.notificationShown)
        Assertions.assertTrue(clientNotification.mOldActiveTasks.isEmpty())
        Assertions.assertEquals(clientStatus.computingStatus, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(clientStatus.computingSuspendReason, clientNotification.mOldSuspendReason)
    }

    @Test
    fun `When updatedStatus is COMPUTING_STATUS_IDLE then expect status updated and oldActiveTasks to be empty`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_IDLE

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.notificationShown)
        Assertions.assertTrue(clientNotification.mOldActiveTasks.isEmpty())
        Assertions.assertEquals(clientStatus.computingStatus, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(clientStatus.computingSuspendReason, clientNotification.mOldSuspendReason)
    }

    @Test
    fun `When updatedStatus is COMPUTING_STATUS_SUSPENDED then expect status updated and oldActiveTasks to be empty`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_SUSPENDED

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.notificationShown)
        Assertions.assertTrue(clientNotification.mOldActiveTasks.isEmpty())
        Assertions.assertEquals(clientStatus.computingStatus, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(clientStatus.computingSuspendReason, clientNotification.mOldSuspendReason)
    }

    @Test
    fun `When updatedStatus is COMPUTING_STATUS_NEVER then expect status updated and oldActiveTasks to be empty`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.notificationShown)
        Assertions.assertTrue(clientNotification.mOldActiveTasks.isEmpty())
        Assertions.assertEquals(clientStatus.computingStatus, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(clientStatus.computingSuspendReason, clientNotification.mOldSuspendReason)
    }

    @Test
    fun `When updatedStatus is COMPUTING_STATUS_COMPUTING and executingTasks is not empty then expect status updated and oldActiveTasks to be equal to executingTasks`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_COMPUTING
        clientStatus.setClientStatus(
            CcStatus(),
            listOf(
                Result(name = "Result 1", isActiveTask = true, activeTaskState = PROCESS_EXECUTING)
            ),
            listOf(Project()),
            listOf(Transfer()),
            HostInfo(),
            AcctMgrInfo(),
            listOf(Notice())
        )

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.notificationShown)
        Assertions.assertEquals(1, clientNotification.mOldActiveTasks.size)
        Assertions.assertEquals("Result 1", clientNotification.mOldActiveTasks[0].name)
        Assertions.assertEquals(clientStatus.computingStatus, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(clientStatus.computingSuspendReason, clientNotification.mOldSuspendReason)
    }

    @Test
    fun `When updatedStatus is COMPUTING_STATUS_COMPUTING and executingTasks contains both running and not running tasks then expect status updated and oldActiveTasks to be equal to executingTasks`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_COMPUTING
        clientStatus.setClientStatus(
            CcStatus(),
            listOf(
                Result(name = "Result 1", isActiveTask = true, activeTaskState = PROCESS_EXECUTING),
                Result(name = "Result 2", isActiveTask = false, activeTaskState = PROCESS_SUSPENDED),
                Result(name = "Result 3", isActiveTask = false, activeTaskState = PROCESS_EXECUTING),
                Result(name = "Result 4", isActiveTask = true, activeTaskState = PROCESS_ABORTED),
            ),
            listOf(Project()),
            listOf(Transfer()),
            HostInfo(),
            AcctMgrInfo(),
            listOf(Notice())
        )

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.notificationShown)
        Assertions.assertEquals(1, clientNotification.mOldActiveTasks.size)
        Assertions.assertEquals("Result 1", clientNotification.mOldActiveTasks[0].name)
        Assertions.assertEquals(clientStatus.computingStatus, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(clientStatus.computingSuspendReason, clientNotification.mOldSuspendReason)
    }

    @Test
    fun `When updatedStatus is COMPUTING_STATUS_COMPUTING and executingTasks contains not running tasks then expect status updated and oldActiveTasks to be empty`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_COMPUTING
        clientStatus.setClientStatus(
            CcStatus(),
            listOf(
                Result(name = "Result 1")
            ),
            listOf(Project()),
            listOf(Transfer()),
            HostInfo(),
            AcctMgrInfo(),
            listOf(Notice())
        )

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.notificationShown)
        Assertions.assertTrue(clientNotification.mOldActiveTasks.isEmpty())
        Assertions.assertEquals(clientStatus.computingStatus, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(clientStatus.computingSuspendReason, clientNotification.mOldSuspendReason)
    }

    @Test
    fun `When updatedStatus is COMPUTING_STATUS_COMPUTING, and executingTasks and oldActiveTasks are not empty then expect status updated and oldActiveTasks to be equal to executingTasks`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_COMPUTING
        clientStatus.setClientStatus(
            CcStatus(),
            listOf(
                Result(name = "Result 1", isActiveTask = true, activeTaskState = PROCESS_EXECUTING)
            ),
            listOf(Project()),
            listOf(Transfer()),
            HostInfo(),
            AcctMgrInfo(),
            listOf(Notice())
        )
        clientNotification.mOldActiveTasks.add(Result(name = "Result 2"))

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.notificationShown)
        Assertions.assertEquals(1, clientNotification.mOldActiveTasks.size)
        Assertions.assertEquals("Result 1", clientNotification.mOldActiveTasks[0].name)
        Assertions.assertEquals(clientStatus.computingStatus, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(clientStatus.computingSuspendReason, clientNotification.mOldSuspendReason)
    }

    @Test
    fun `When updatedStatus is COMPUTING_STATUS_COMPUTING, and executingTasks and oldActiveTasks are not empty and contain different number of records then expect status updated and oldActiveTasks to be equal to executingTasks`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_COMPUTING
        clientStatus.setClientStatus(
            CcStatus(),
            listOf(
                Result(name = "Result 1", isActiveTask = true, activeTaskState = PROCESS_EXECUTING)
            ),
            listOf(Project()),
            listOf(Transfer()),
            HostInfo(),
            AcctMgrInfo(),
            listOf(Notice())
        )
        clientNotification.mOldActiveTasks.add(Result(name = "Result 2"))
        clientNotification.mOldActiveTasks.add(Result(name = "Result 1"))

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.notificationShown)
        Assertions.assertEquals(1, clientNotification.mOldActiveTasks.size)
        Assertions.assertEquals("Result 1", clientNotification.mOldActiveTasks[0].name)
        Assertions.assertEquals(clientStatus.computingStatus, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(clientStatus.computingSuspendReason, clientNotification.mOldSuspendReason)
    }

    @Test
    fun `When updatedStatus is COMPUTING_STATUS_IDLE and oldActiveTasks is not empty then expect status updated and oldActiveTasks to be empty`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_IDLE
        clientNotification.mOldActiveTasks.add(Result())

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.notificationShown)
        Assertions.assertTrue(clientNotification.mOldActiveTasks.isEmpty())
        Assertions.assertEquals(clientStatus.computingStatus, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(clientStatus.computingSuspendReason, clientNotification.mOldSuspendReason)
    }

    @Test
    fun `When updatedStatus is COMPUTING_STATUS_SUSPENDED and oldActiveTasks is not empty then expect status updated and oldActiveTasks to be empty`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_SUSPENDED
        clientNotification.mOldActiveTasks.add(Result())

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.notificationShown)
        Assertions.assertTrue(clientNotification.mOldActiveTasks.isEmpty())
        Assertions.assertEquals(clientStatus.computingStatus, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(clientStatus.computingSuspendReason, clientNotification.mOldSuspendReason)
    }

    @Test
    fun `When updatedStatus is COMPUTING_STATUS_NEVER and oldActiveTasks is not empty then expect status updated and oldActiveTasks to be empty`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER
        clientNotification.mOldActiveTasks.add(Result())

        clientNotification.update(clientStatus, monitor, true)

        Assertions.assertTrue(clientNotification.notificationShown)
        Assertions.assertTrue(clientNotification.mOldActiveTasks.isEmpty())
        Assertions.assertEquals(clientStatus.computingStatus, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(clientStatus.computingSuspendReason, clientNotification.mOldSuspendReason)
    }

    @Test
    fun `When ClientNotification is created then expect default values to be set`() {
        Assertions.assertEquals(-1, clientNotification.mOldComputingStatus)
        Assertions.assertEquals(-1, clientNotification.mOldSuspendReason)
        Assertions.assertTrue(clientNotification.mOldActiveTasks.isEmpty())
        Assertions.assertFalse(clientNotification.notificationShown)
        Assertions.assertFalse(clientNotification.foreground)
    }

    @Test
    fun `Check equality of Intent constants`() {
        Assertions.assertEquals(Intent.FLAG_ACTIVITY_CLEAR_TOP, PendingIntent.FLAG_IMMUTABLE)
        Assertions.assertEquals(Intent.FLAG_ACTIVITY_NEW_TASK, PendingIntent.FLAG_CANCEL_CURRENT)
    }
}
