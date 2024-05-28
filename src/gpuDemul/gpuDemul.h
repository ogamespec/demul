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

#ifndef __DEMUL_H__
#define __DEMUL_H__

#include "Backends.h"

#define GPU_MODULE_NAME "gpuDemul"

void DEMUL_printf(char *format, ...);
void ProfileStart(int n);
void ProfileFinish(int n);

#endif
