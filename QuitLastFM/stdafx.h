// (C) 2013, Dominik Martin Drzic

#pragma once

// Winamp SDK is missing those (unicode versions)
#define IPC_GETINIFILEW 1334
#define IPC_GETINIDIRECTORYW 1335
#define IPC_GETPLUGINDIRECTORYW 1336
#define IPC_GETVISDIRECTORYW 339
#define IPC_GETSKINDIRECTORYW 340
#define IPC_GETDSPDIRECTORYW 341

// Windows and STL
#include <windows.h>
#include <atlbase.h>
#include <tlhelp32.h>

// Winamp
#include "winamp\wa_dlg.h"
#include "winamp\wa_ipc.h"

// Own
#include "Resource.h"

