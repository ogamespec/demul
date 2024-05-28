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

#include "demul.h"
#include "interpreter.h"
#include "x86-32/dynarec.h"
#include "arm.h"
#include "gpu.h"
#include "Backends.h"
#include "win32/configure.h"

bool EmuRunning = false;
static bool EmuOpened = false;

int OpenEmu() {
	if (EmuOpened) return 1;

	if (!LoadConfig())
		return false;

	while (memOpen() == 0) {
		if (!SetConfig())
			return false;
	}

	if (intpOpen() == 0) return 0;
	if (armOpen() == 0) return 0;
	if (recOpen() == 0) return 0;

	EmuOpened = true;
	return 1;
}

void RunEmu(void *p) {
	EmuRunning = true;

	if (!openPlugins())
		return;

	for (;; ) {
		if (cfg.sh4mode == MODE_INTERPRETER) intpExecute();
		else recExecute();
	}
}

void CloseEmu() {
	if (EmuRunning)
		closePlugins();

	#ifdef DEMUL_DEBUG
	closeDebug();
	#endif

	memClose();

	armClose();
	intpClose();
	recClose();

	EmuRunning = false;
	EmuOpened = false;
}
