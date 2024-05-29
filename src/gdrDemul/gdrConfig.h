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

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "types.h"

#define MAX_SECTOR 16

#define GDR_METHOD_SCSI 0
#define GDR_METHOD_GDI_IMAGE 1				// https://dreamcast.wiki/GDI_format

typedef struct {
	char drive[8];
	char image_path[MAX_PATH];			// Path to GDI image
	int method;			// See GDR_METHOD definitions
} GDR_CFG;

extern GDR_CFG gdrcfg;

bool gdrLoadConfig();
bool gdrSetConfig();
void gdrSaveConfig();

#endif