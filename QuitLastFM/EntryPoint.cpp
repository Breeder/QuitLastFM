// (C) 2013, Dominik Martin Drzic

#include "stdafx.h"
#include "EntryPoint.h"
#include "GlobalVars.h"
#include "SettingsDlg.h"
#include "Util.h"

// Entry point functions
int init ()
{
	iniFile = (wchar_t*)SendMessage (plugin.hwndParent, WM_WA_IPC, 0, IPC_GETINIFILEW);
	enable = !!GetPrivateProfileInt (DLL_NAME, S_ENABLE, 1, iniFile);
	return 0;
};
 
void config ()
{  
	ShowSettings ();
};
 
void quit () 
{
	if (enable)
	{
		// Kill process (new version)
		KillProcess (GetProcID (L"Last.fm Scrobbler.exe"), 0);
		
		// Kill process (old version)
		KillProcess (GetProcID (L"LastFM.exe"), 0);
		
		// Clear notification icon
		RefreshTaskbarNotificationArea();
	}
};

// Entry point
// This is an export function called by winamp which returns this plugin info.
// We wrap the code in 'extern "C"' to ensure the export isn't mangled if used in a CPP file.
extern "C" __declspec(dllexport) winampGeneralPurposePlugin * winampGetGeneralPurposePlugin ()
{
	return &plugin;
};