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
import android.content.Context
import androidx.test.core.app.ApplicationProvider
import edu.berkeley.boinc.R
import edu.berkeley.boinc.rpc.App
import edu.berkeley.boinc.rpc.Project
import edu.berkeley.boinc.rpc.Result
import io.mockk.justRun
import io.mockk.mockkClass
import org.junit.Assert
import org.junit.Before
import org.junit.Test
import org.junit.jupiter.api.assertDoesNotThrow
import org.junit.runner.RunWith
import org.robolectric.RobolectricTestRunner

@RunWith(RobolectricTestRunner::class)
class ClientNotificationTest {
    private lateinit var clientNotification: ClientNotification

    @Before
    fun setUp() {
        clientNotification = ClientNotification(ApplicationProvider.getApplicationContext())
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_NEVER then expect corresponding Notification title and text`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assert.assertEquals(clientStatus.currentStatusTitle, notification.extras.get(Notification.EXTRA_TITLE))
        Assert.assertEquals(clientStatus.currentStatusDescription, notification.extras.get(Notification.EXTRA_TEXT))
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_IDLE then expect corresponding Notification title and text`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_IDLE

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assert.assertEquals(clientStatus.currentStatusTitle, notification.extras.get(Notification.EXTRA_TITLE))
        Assert.assertEquals(clientStatus.currentStatusDescription, notification.extras.get(Notification.EXTRA_TEXT))
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_SUSPENDED then expect corresponding Notification title and text`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_SUSPENDED

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assert.assertEquals(clientStatus.currentStatusTitle, notification.extras.get(Notification.EXTRA_TITLE))
        Assert.assertEquals(clientStatus.currentStatusDescription, notification.extras.get(Notification.EXTRA_TEXT))
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_COMPUTING and activeTasks is null then expect corresponding Notification title and text`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_COMPUTING

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assert.assertEquals(clientStatus.currentStatusTitle, notification.extras.get(Notification.EXTRA_TITLE))
        Assert.assertEquals(clientStatus.currentStatusDescription, notification.extras.get(Notification.EXTRA_TEXT))
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_COMPUTING and activeTasks is empty then expect corresponding Notification title and text`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_COMPUTING

        val notification = clientNotification.buildNotification(clientStatus, true, listOf())
        Assert.assertEquals(clientStatus.currentStatusTitle, notification.extras.get(Notification.EXTRA_TITLE))
        Assert.assertEquals(clientStatus.currentStatusDescription, notification.extras.get(Notification.EXTRA_TEXT))
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
        Assert.assertEquals(clientStatus.currentStatusTitle, notification.extras.get(Notification.EXTRA_TITLE))
        Assert.assertEquals(clientStatus.currentStatusDescription, notification.extras.get(Notification.EXTRA_SUB_TEXT))
        Assert.assertEquals(activeTasks.size, notification.number)
        val lines = notification.extras.getCharSequenceArray(Notification.EXTRA_TEXT_LINES)
        Assert.assertNotNull(lines)
        Assert.assertEquals(activeTasks.size, lines?.size)
        Assert.assertEquals("Project 1: App Name 1", lines?.get(0)?.toString())
        Assert.assertEquals("Project 2: App Name 2", lines?.get(1)?.toString())
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
        Assert.assertEquals(activeTasks.size, notification.number)
        val lines = notification.extras.getCharSequenceArray(Notification.EXTRA_TEXT_LINES)
        Assert.assertNotNull(lines)
        Assert.assertEquals(activeTasks.size, lines?.size)
        Assert.assertEquals(": App Name 1", lines?.get(0)?.toString())
        Assert.assertEquals("Project 2: ", lines?.get(1)?.toString())
        Assert.assertEquals(": ", lines?.get(2)?.toString())
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_NEVER then expect only one Notification Action with menu_run_mode_enable title`() {
        val context = ApplicationProvider.getApplicationContext<Context>()
        val clientStatus = ClientStatus(context, null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assert.assertEquals(1, notification.actions.size)
        Assert.assertEquals(context.getString(R.string.menu_run_mode_enable), notification.actions[0].title)
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_IDLE then expect only one Notification Action with menu_run_mode_disable title`() {
        val context = ApplicationProvider.getApplicationContext<Context>()
        val clientStatus = ClientStatus(context, null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_IDLE

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assert.assertEquals(1, notification.actions.size)
        Assert.assertEquals(context.getString(R.string.menu_run_mode_disable), notification.actions[0].title)
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_SUSPENDED then expect only one Notification Action with menu_run_mode_disable title`() {
        val context = ApplicationProvider.getApplicationContext<Context>()
        val clientStatus = ClientStatus(context, null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_SUSPENDED

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assert.assertEquals(1, notification.actions.size)
        Assert.assertEquals(context.getString(R.string.menu_run_mode_disable), notification.actions[0].title)
    }

    @Test
    fun `When ClientStatus is COMPUTING_STATUS_COMPUTING then expect only one Notification Action with menu_run_mode_disable title`() {
        val context = ApplicationProvider.getApplicationContext<Context>()
        val clientStatus = ClientStatus(context, null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_COMPUTING

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assert.assertEquals(1, notification.actions.size)
        Assert.assertEquals(context.getString(R.string.menu_run_mode_disable), notification.actions[0].title)
    }

    @Test
    fun `When active is true then expect Notification priority to be high`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assert.assertEquals(Notification.PRIORITY_HIGH, notification.priority)
    }

    @Test
    fun `When active is false then expect Notification priority to be low`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        val notification = clientNotification.buildNotification(clientStatus, false, null)
        Assert.assertEquals(Notification.PRIORITY_LOW, notification.priority)
    }

    @Test
    fun `When foreground is false expect it to be true after setForeground call`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }

        clientNotification.setForegroundState(monitor)
        Assert.assertTrue(clientNotification.foreground)
    }

    @Test
    fun `When updateStatus is null expect no exception thrown`() {
        val monitor = mockkClass(Monitor::class)
        assertDoesNotThrow { clientNotification.update(null, monitor, true) }
    }

    @Test
    fun `When service is null expect no exception thrown`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER
        assertDoesNotThrow { clientNotification.update(clientStatus, null, true) }
    }

    @Test
    fun `When updateStatus is null and service is null expect no exception thrown`() {
        assertDoesNotThrow { clientNotification.update(null, null, true) }
    }

    @Test
    fun `When active is true expect foreground to be true`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        clientNotification.update(clientStatus, monitor, true)

        Assert.assertTrue(clientNotification.foreground)
    }

    @Test
    fun `When active is false expect foreground to be false`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        clientNotification.update(clientStatus, monitor, false)

        Assert.assertFalse(clientNotification.foreground)
    }

    @Test
    fun `When active is false and foreground is true expect foreground to be true`() {
        val monitor = mockkClass(Monitor::class)
        justRun { monitor.startForeground(any(), any()) }
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        clientNotification.foreground = true
        clientNotification.update(clientStatus, monitor, false)

        Assert.assertTrue(clientNotification.foreground)
    }
}
