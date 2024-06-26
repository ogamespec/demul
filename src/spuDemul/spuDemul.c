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
#include <stdio.h>
#include "spuRegs.h"
#include "spudevice.h"
#include "Backends.h"

int spuOpen(void *pspu) {
	ARAM = pspu;
	if (!spuOpenDevice()) {
		spuCloseDevice();
		return 0;
	}
	return 1;
}

void spuClose() {
	spuCloseDevice();
	ARAM = NULL;
}

void spuReset() {
}

void spuConfigure() {
}

void spuSync(u32 samples) {
	//spuDeviceSync(samples);
}