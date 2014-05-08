
// MMShellHook.cpp : Defines the implementation of the DLL.
//

#include "MMShellHook.h"
#include <tchar.h>
#include <windows.h>
#include <winuser.h>

#include <crtdbg.h>
/////////////////////////////////////////////////////////////////////////////
// Storage for the global data in the DLL

#pragma data_seg(".shared")
HWND hNotifyWnd = NULL;
HHOOK hShellHook = NULL;							// Handle to the Shell hook
#pragma data_seg( )
/////////////////////////////////////////////////////////////////////////////
// Per-instance DLL variables


HINSTANCE hInstance = NULL;							// This instance of the DLL


LRESULT CALLBACK ShellProc (int nCode, WPARAM wParam, LPARAM lParam);



// The DLL's main procedure
BOOL WINAPI DllMain (HANDLE hInst, ULONG ul_reason_for_call, LPVOID lpReserved)
{
	// Find out why we're being called
	switch (ul_reason_for_call)
	{

	case DLL_PROCESS_ATTACH:
#ifndef _WIN32_WCE
#ifdef _MSC_VER
		_RPT0(_CRT_WARN, "MMShellHook : Hook DLL loaded\n");
#endif
#endif
		// Save the instance handle
		hInstance = (HINSTANCE)hInst;
		// ALWAYS return TRUE to avoid breaking unhookable applications!!!
		return TRUE;

	case DLL_PROCESS_DETACH:
#ifndef _WIN32_WCE
#ifdef _MSC_VER
		_RPT0(_CRT_WARN, "MMShellHook : Hook DLL unloaded\n");
#endif
#endif		

		return TRUE;

	default:
		return TRUE;
	}
}

// Add the new hook

#include <stdio.h>
DllExport BOOL SetMMShellHook(HWND hWnd)
{

	// Don't add the hook if the window ID is NULL
	printf("1\n");
	if (hWnd == NULL)
		return FALSE;
	
	// Don't add a hook if there is already one added
	printf("2\n");
	if (hNotifyWnd != NULL)
		return FALSE;

	// Add the ShellProc hook
	printf("3\n");
	hShellHook = SetWindowsHookEx(
					WH_SHELL,					// Hook in before msg reaches app
					(HOOKPROC) ShellProc,			// Hook procedure
					hInstance,						// This DLL instance
					0L								// Hook in to all apps
					);


	// Check that it worked
	if (hShellHook != NULL)
	{
printf("4\n");
		hNotifyWnd = hWnd;						// Save the WinRFB window handle

#ifdef _MSC_VER
		_RPT1(_CRT_WARN, "Notify Window is: %d\n", hWnd);
#endif
		return TRUE;
	}
	printf("5\n");
	// The hook failed, so return an error code
	return FALSE;
}


// Remove the hook from the system
DllExport BOOL UnSetMMShellHook(HWND hWnd)
{

	BOOL unHooked = TRUE;
	
	// Is the window handle valid?
	if (hWnd == NULL)
		MessageBox(NULL, _T("Window pointer is null"), _T("Message"), MB_OK);

	// Is the correct application calling UnSetHook?
	if (hWnd != hNotifyWnd)
		return FALSE;
	// Unhook the procs
	if (hNotifyWnd != NULL)
	{
		unHooked = UnhookWindowsHookEx(hShellHook);
		hShellHook = NULL;
	}
	// If we managed to unhook then reset
	if (unHooked)
	{
		hNotifyWnd = NULL;
	}

	return unHooked;

}



// Hook procedure for Shell hook

LRESULT CALLBACK ShellProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	// Do we have to handle this message?
	if (nCode == HSHELL_APPCOMMAND)
	{
		// Process the hook if the hNotifyWnd window handle is valid
		if (hNotifyWnd != NULL)
		{
			short AppCommand = GET_APPCOMMAND_LPARAM(lParam);
			switch (AppCommand)
			{
			case APPCOMMAND_MEDIA_NEXTTRACK:
			case APPCOMMAND_MEDIA_PLAY_PAUSE:
			case APPCOMMAND_MEDIA_PREVIOUSTRACK:
			case APPCOMMAND_MEDIA_STOP:
				::PostMessage(hNotifyWnd,WM_APPCOMMAND,wParam,lParam);
				return 1; // dont call CallNextHookEx, instead return non-zero, because we have handled the message (see MSDN doc)

			}
		}
	}

	// Call the next handler in the chain
    return CallNextHookEx (hShellHook, nCode, wParam, lParam);
}
