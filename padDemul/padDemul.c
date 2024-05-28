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
	if (!padOpenDevice()) {
		padCloseDevice();
		return 0;
	}
	if (!LoadConfig(true)) {
		padCloseDevice();
		return 0;
	}
	return 1;
}

void padClose() {
	padCloseDevice();
}

void padReset() {
}

void padConfigure() {
	bool wasOpened = IsOpened();
	if (!wasOpened) {
		if (!padOpenDevice()) {
			padCloseDevice();
			return;
		}
		if (!LoadConfig(false)) {
			padCloseDevice();
			return;
		}
	}

	SetConfig();

	if (!wasOpened)
		padCloseDevice();
}

void padAbout() {
}

u32 padJoyCaps(u32 port) {
	return /*0xfe060f00*/ JoyCaps[port];
}

void padReadJoy(u8 *keymask, u32 port) {
	GetControllerDevice((CONTROLLER*)keymask, port);
}