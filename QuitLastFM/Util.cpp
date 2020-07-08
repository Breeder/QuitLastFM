// (C) 2013, Dominik Martin Drzic

#include "stdafx.h"
#include "Util.h"
#include <StrSafe.h>

void GetLastError (LPTSTR name) 
{ 
    // Retrieve the system error message for the last-error code
	LPVOID msgBuf;
	LPVOID displayBuf;
    DWORD error = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        error,
        MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &msgBuf,
        0, NULL
	);

    // Display the error message
    displayBuf = (LPVOID)LocalAlloc (LMEM_ZEROINIT, (lstrlen ((LPCTSTR)msgBuf) + lstrlen ((LPCTSTR)name) + 40) * sizeof(TCHAR)); 
    StringCchPrintf ((LPTSTR)displayBuf, LocalSize(displayBuf) / sizeof (TCHAR), TEXT("%s failed with error %d: %s"), name, error, msgBuf); 
    MessageBox (NULL, (LPCTSTR)displayBuf, TEXT("Error"), MB_OK); 

	// Exit process
    LocalFree (msgBuf);
    LocalFree (displayBuf);
    ExitProcess (error); 
};

DWORD GetProcID (WCHAR* name)
{
	// Get snapshot of all the processes in the system and check if valid
	HANDLE snapshot = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE)
		return 0;
	
	// This will hold info on process currently being inspected (setting size as specified in documentation)
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof (PROCESSENTRY32);
	
	// Get first process encountered in the snapshot
	if (Process32First (snapshot, &pe32))
	{
		// Go through processes in the snapshot and compare names
		do
		{
			if (wcscmp (pe32.szExeFile, name) == 0)
			{
				// Close snapshot handle and return process id
				CloseHandle (snapshot);
				return pe32.th32ProcessID;
			}
		}
		while (Process32Next (snapshot, &pe32));
	}

	// No process found - close handle and return 0
	CloseHandle (snapshot);
	return 0;
};

bool KillProcess (DWORD ID, int exitCode)
{
	// Invalid process ID?
	if (!ID)
		return false;

	// Get process handle
	HANDLE process = OpenProcess (PROCESS_TERMINATE, FALSE, ID); // no need to use PROCESS_ALL_ACCESS - it will result in ERROR_ACCESS_DENIED if used on WinXP
	if (process)
	{
		// Kill process with specified exit code
		if (TerminateProcess (process, exitCode))
		{
			CloseHandle (process);
			return true;
		}
		else
			CloseHandle (process);	
	}
	
	return false;
};

HWND GetTaskbarHandle (bool visible)
{
	HWND handle = NULL;
	
	// Search for "visible part"
	if (visible)
	{
		handle = FindWindowEx (handle, NULL, L"Shell_TrayWnd",	NULL);
		if (handle)
			handle = FindWindowEx (handle, NULL, L"TrayNotifyWnd",	NULL);
		if (handle)
			handle = FindWindowEx (handle, NULL, L"SysPager",		NULL);
		if (handle)	
			handle = FindWindowEx (handle, NULL, L"ToolbarWindow32", NULL);	
	}	
	
	// Search for "hidden part"
	else
	{
		handle = FindWindowEx (handle, NULL, L"NotifyIconOverflowWindow", NULL);
		if (handle)
			handle = FindWindowEx (handle, NULL, L"ToolbarWindow32", NULL);
	}

	return handle;
};

void RefreshTaskbarNotificationArea ()
{
	// Refresh visible part of the taskbar
	HWND visible = GetTaskbarHandle (true);
	if (visible)
	{
		// Get taskbar rect
		RECT r;	GetClientRect (visible, &r);

		// Loop through rect in steps of 5 and send mouse move message (should result in removal of unused icons)
		for (LONG x = 0; x < r.right; x += 5)
			for (LONG y = 0; y < r.bottom; y += 5)
				SendMessage (visible, WM_MOUSEMOVE, 0, (y << 16) + x);
	}

	// Refresh hidden part of the taskbar
	HWND hidden = GetTaskbarHandle (false);
	if (hidden)
	{
		// Get taskbar coordinates and "extend" it's height and width in case it hasn't been updated after adding new buttons (happens if user didn't show hidden icons)
		RECT r; GetClientRect (visible, &r);
		r.bottom +=(r.bottom - r.top);
		r.right += (r.right - r.left);
		
		// Loop through rect in steps of 5 and send mouse move message (should result in removal of unused icons)
		for (LONG x = 0; x < r.right; x += 5)
			for (LONG y = 0; y < r.bottom; y += 5)
				SendMessage (hidden, WM_MOUSEMOVE, 0, (y << 16) + x);
	}
};


