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
#include "Backends.h"
#include "memory.h"
#include "gpu.h"
#include "win32/configure.h"

bool openPlugins() {
	int st;

	st = gpuOpen(pgpu);
	if (st == 0) {
		closePlugins();
		return false;
	}
	gpuSetIrqHandler((void*)gpuIrq);

	st = gdrOpen();
	if (st == 0) {
		closePlugins();
		return false;
	}

	st = padOpen();
	if (st == 0) {
		closePlugins();
		return false;
	}

	st = spuOpen(pspu);
	if (st == 0) {
		closePlugins();
		return false;
	}

	return true;
}

void closePlugins() {
	gpuClose();
	gdrClose();
	padClose();
	spuClose();
}
