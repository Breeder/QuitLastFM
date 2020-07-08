// (C) 2013, Dominik Martin Drzic

#include "stdafx.h"
#include "GlobalVars.h"
#include "EntryPoint.h"

// Holds plugin info
winampGeneralPurposePlugin plugin =
{
  GPPHDR_VER,  // version of the plugin, defined in "EntryPoint.h"
  PLUGIN_NAME, // name/title of the plugin, defined in "EntryPoint.h"
  init,        // function name which will be executed on init event
  config,      // function name which will be executed on config event
  quit,        // function name which will be executed on quit event
  0,           // handle to Winamp main window, loaded by winamp when this dll is loaded
  0            // hinstance to this dll, loaded by winamp when this dll is loaded
};

wchar_t* iniFile = NULL;    // holds .ini file path
bool enable = true;			// settings flag - plugin enabled