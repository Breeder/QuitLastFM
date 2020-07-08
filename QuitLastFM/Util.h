// (C) 2013, Dominik Martin Drzic

#pragma once

// Functions for refreshing notification area
DWORD GetProcID (WCHAR* name);
bool KillProcess (DWORD ID, int exitCode);
void RefreshTaskbarNotificationArea ();