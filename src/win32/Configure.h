/*
 * Demul
 * Copyright (C) 2006 Demul Team
 *
 * Demul is not free software: you can't redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Demul isn't distributed in the hope that it will be useful,
 * and WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__

#include <windows.h>
#include "types.h"
#include "Backends.h"

#define DEMUL_NAME "demul"
#define DEMUL_REVISION_STR "Babaika"		// Just a catchy revision name for the development build/iteration
#define MAX_DESCRIPTION 300

//TO Wind - move to Memory unit ?
#define BIOS_SIZE 0x00200000
#define FLASH_SIZE 0x00020000

#define MODE_INTERPRETER 0
#define MODE_DYNAREC     1

typedef struct {
	int sh4mode;

	char biosFileName[MAX_PATH];
	char flashFileName[MAX_PATH];

} CFG;

extern CFG cfg;
extern DEmulInfo demulInfo;

bool LoadConfig();
void SaveConfig();
bool SetConfig();
bool LoadBIOSFiles(CFG* aCfg, u8*biosBuf, u8*flashBuf, char** biosDescription, char** flashDescription);

#endif