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

#include <windows.h>
#include "device.h"
#include "config.h"
#include "plugins.h"

HINSTANCE hinstance;
DEmulInfo *gDemulInfo = NULL;

int padOpen(DEmulInfo *demulInfo) {
	gDemulInfo = demulInfo;
	if (!OpenDevice()) {
		CloseDevice();
		return 0;
	}
	if (!LoadConfig(true)) {
		CloseDevice();
		return 0;
	}
	return 1;
}

void padClose() {
	CloseDevice();
}

void padReset() {
}

void padConfigure() {
	bool wasOpened = IsOpened();
	if (!wasOpened) {
		if (!OpenDevice()) {
			CloseDevice();
			return;
		}
		if (!LoadConfig(false)) {
			CloseDevice();
			return;
		}
	}

	SetConfig();

	if (!wasOpened)
		CloseDevice();
}

void padAbout() {
}

u32 padJoyCaps(u32 port) {
	return /*0xfe060f00*/ JoyCaps[port];
}

void padReadJoy(u8 *keymask, u32 port) {
	GetControllerDevice((CONTROLLER*)keymask, port);
}