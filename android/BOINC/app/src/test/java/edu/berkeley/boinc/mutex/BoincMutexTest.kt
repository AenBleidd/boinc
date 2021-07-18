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
package edu.berkeley.boinc.mutex

import android.net.LocalSocket
import android.util.Log
import edu.berkeley.boinc.utils.Logging.setLogLevel
import io.mockk.*
import io.mockk.impl.annotations.MockK
import org.junit.jupiter.api.Assertions
import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test
//import org.junit.Assert
//import org.junit.Before
//import org.junit.Test
//import org.junit.runner.RunWith
//import org.mockito.ArgumentMatchers
//import org.mockito.Mock
//import org.mockito.Mockito
//import org.mockito.MockitoAnnotations
//import org.powermock.api.mockito.PowerMockito
//import org.powermock.core.classloader.annotations.PrepareForTest
//import org.powermock.modules.junit4.PowerMockRunner

import java.io.IOException

//@RunWith(PowerMockRunner::class)
//@PrepareForTest(Log::class)
class BoincMutexTest {
    @MockK
    private val localSocket: LocalSocket? = null
    private var boincMutex: BoincMutex? = null
    @BeforeEach
    fun setUp() {
        MockKAnnotations.init(this)
//        MockitoAnnotations.initMocks(this)
        boincMutex = BoincMutex(localSocket!!)
    }

    @Test
    fun `Acquire() Expect True when socket is already bound`() {
        every { localSocket!!.isBound } returns true
//        Mockito.`when`(localSocket!!.isBound).thenReturn(true)
        Assertions.assertTrue(boincMutex!!.acquire())
    }

    @Test
    fun `Acquire() Expect False when isBound() returns false`() {
        every { localSocket!!.isBound } returns false
//        Mockito.`when`(localSocket!!.isBound).thenReturn(false)
        Assertions.assertFalse(boincMutex!!.acquire())
    }

    @Test
    @Throws(IOException::class)
    fun `Acquire() Expect IOException thrown by bind to be logged when LoggingLevel is Error`() {
        mockkStatic(Log::class)
//        PowerMockito.mockStatic(Log::class.java)
        every { localSocket?.bind(any()) } throws IOException()
//        Mockito.doThrow(IOException()).`when`(localSocket)?.bind(ArgumentMatchers.any())
        setLogLevel(1)
        boincMutex!!.acquire()
//        PowerMockito.verifyStatic(Log::class.java)
        verify(exactly = 1) { Log.e(any(), "BoincMutex.acquire error: ", any()) }
//        Log.e(ArgumentMatchers.anyString(), ArgumentMatchers.eq("BoincMutex.acquire error: "), ArgumentMatchers.any())
        confirmVerified()
    }

    @Test
    fun `Release() Expect isAcquired to be False`() {
        every { localSocket!!.isBound } returns true
//        Mockito.`when`(localSocket!!.isBound).thenReturn(true)
        boincMutex!!.release()
        Assertions.assertFalse(boincMutex!!.isAcquired)
    }

    @Test
    @Throws(IOException::class)
    fun `Release() Expect IOException thrown by Close to be logged when bound and LoggingLevel is Error`() {
        mockkStatic(Log::class)
//        PowerMockito.mockStatic(Log::class.java)
        every { localSocket!!.isBound } returns true
//        Mockito.`when`(localSocket!!.isBound).thenReturn(true)
        every { localSocket?.close() } throws IOException()
//        Mockito.doThrow(IOException()).`when`(localSocket).close()
        setLogLevel(1)
        boincMutex!!.release()
//        PowerMockito.verifyStatic(Log::class.java)
        verify(exactly = 1) { Log.e(any(), "BoincMutex.release error: ", any()) }
//        Log.e(ArgumentMatchers.anyString(), ArgumentMatchers.eq("BoincMutex.release error: "), ArgumentMatchers.any())
        confirmVerified()
    }
}
