

#if !defined(_MMShellHook_DLL_)
#define _MMShellHook_DLL_

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////
// Define the import/export tags

#define DllImport __declspec(dllimport)
#define DllExport __declspec(dllexport)

/////////////////////////////////////////////////////////////////////////////
//
// Functions used by WinVNC

extern "C"
{
	// DLL functions:
	DllExport BOOL SetMMShellHook(HWND hWnd	);		// Set the hook
	DllExport BOOL UnSetMMShellHook(HWND hWnd);			// Remove it


}

#endif // !defined(_VNCHOOKS_DLL_)
