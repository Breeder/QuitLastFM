// (C) 2013, Dominik Martin Drzic

#include "stdafx.h"
#include "SettingsDlg.h"
#include "EntryPoint.h"
#include "GlobalVars.h"


// Dialog proc
INT_PTR SettingsDlgProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_INITDIALOG:
		{
			// Set check button per global var and make sure dialog gets TOPMOST flag (in case it gets created with NULL parent)
			CheckDlgButton(hwnd, IDC_ENABLE, !!enable);
			SetWindowPos(hwnd, HWND_TOPMOST ,0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);
		}
		break;
		
		case WM_COMMAND:
		{
            switch(LOWORD(wParam))
            {
				case IDC_ENABLE:
				{
					// Set global variable per checkbox state
					enable = !!IsDlgButtonChecked (hwnd, IDC_ENABLE);
					
					// Print to char
					wchar_t temp [256];
					_snwprintf_s(temp, sizeof(temp), L"%d", enable);

					// Save
					WritePrivateProfileString (DLL_NAME, S_ENABLE, temp, iniFile);
				}
				break;

				case IDC_ABOUT:
				{
					MessageBox (hwnd, L"© 2013 Dominik Martin Držiæ", L"AutoClose Last.FM", MB_OK);
				}
				break;

				case IDOK:
				{
					EndDialog(hwnd, 0);
				}
				break;

				case IDCANCEL:
				{
					EndDialog(hwnd, 0);
				}
				break;

			}
			break;
		}
		break;
	}
	return 0;

};

// Dialog caller
void ShowSettings ()
{
	HWND prefsHwnd = (HWND)SendMessage (plugin.hwndParent, WM_WA_IPC, 0, IPC_GETPREFSWND);
	DialogBox (plugin.hDllInstance, MAKEINTRESOURCE(IDD_SETTINGS), prefsHwnd, (DLGPROC) SettingsDlgProc);
};