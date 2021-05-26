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
import androidx.test.core.app.ApplicationProvider
import org.junit.Assert
import org.junit.Before
import org.junit.Test
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
    fun `When ClientStatus is COMPUTING_STATUS_NEVER then expect corresponding Notification`() {
        val clientStatus = ClientStatus(ApplicationProvider.getApplicationContext(), null, null)
        clientStatus.computingStatus = ClientStatus.COMPUTING_STATUS_NEVER

        val notification = clientNotification.buildNotification(clientStatus, true, null)
        Assert.assertEquals(clientStatus.currentStatusTitle, notification.extras.get(Notification.EXTRA_TITLE))
        Assert.assertEquals(1, notification.actions.size)
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
}