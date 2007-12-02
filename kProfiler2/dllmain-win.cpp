/* $Id$ */
/** @file
 * kProfiler Mark 2 - The Windows DllMain for the profiler DLL.
 */

/*
 * Copyright (c) 2006-2007 knut st. osmundsen <bird-src-spam@anduin.net>
 *
 * This file is part of kProfile.
 *
 * kProfile is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * kProfile is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with kProfile; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


/*******************************************************************************
*   Header Files                                                               *
*******************************************************************************/
#include <Windows.h>
#include "kProfileR3.h"


/**
 * The DLL Main for the kPrf DLL.
 *
 * This is required because we need to initialize the profiler at some point
 * and because we need to know when threads terminate. (We don't care about
 * when threads get created, we simply pick them up when we see them the
 * first time.)
 *
 * @returns Success indicator.
 * @param   hInstDll        The instance handle of the DLL. (i.e. the module handle)
 * @param   fdwReason       The reason why we're here. This is a 'flag' for reasons of
 *                          tradition, it's really a kind of enum.
 * @param   pReserved       Reserved / undocumented something.
 */
BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD fdwReason, PVOID pReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            if (kPrfInitialize())
                return FALSE;
            break;

        case DLL_PROCESS_DETACH:
            kPrfTerminate();
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            kPrfTerminateThread();
            break;
    }

    return TRUE;
}
