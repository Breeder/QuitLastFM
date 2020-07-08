// (C) 2013, Dominik Martin Drzic

#pragma once

// Entry point struct
#ifndef gen_myplugin_h
	#include <windows.h>
	#define gen_myplugin_h
	#define GPPHDR_VER 0x10								// plugin version (don't touch this)
	#define PLUGIN_NAME "AutoClose Last.FM Scrobbler"	// plugin name/title
	
	typedef struct										// main structure with plugin information, version, name...
	{
	  int version;                   // version of the plugin structure
	  char *description;             // name/title of the plugin 
	  int (*init)();                 // function which will be executed on init event
	  void (*config)();              // function which will be executed on config event
	  void (*quit)();                // function which will be executed on quit event
	  HWND hwndParent;               // hwnd of the Winamp client main window (stored by Winamp when dll is loaded)
	  HINSTANCE hDllInstance;        // hinstance of this plugin DLL. (stored by Winamp when dll is loaded) 
	} winampGeneralPurposePlugin;

#endif

// Globals
extern winampGeneralPurposePlugin plugin;
extern wchar_t* iniFile;
extern bool enable;

// Defines used for preference storing
#define DLL_NAME L"gen_autoCloseLastFM"
#define S_ENABLE L"enable"