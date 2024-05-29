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
#include "device.h"
#include "gdi_device.h"
#include "gdrConfig.h"
#include "Backends.h"

int gdrOpen() {
	if (!gdrLoadConfig(true))
		return 0;

	switch (gdrcfg.method) {
	case GDR_METHOD_GDI_IMAGE:
		return gdiOpenDevice(gdrcfg.image_path);
	case GDR_METHOD_SCSI:
		return gdrOpenDevice(gdrcfg.drive);
	default:
		break;
	}
	
	return 0;
}

void gdrClose() {

	switch (gdrcfg.method) {
	case GDR_METHOD_GDI_IMAGE:
		gdiCloseDevice();
		break;
	case GDR_METHOD_SCSI:
		gdrCloseDevice();
		break;
	default:
		break;
	}
}

void gdrReset() {
}

void gdrConfigure() {
	if (gdrLoadConfig(false))
		gdrSetConfig();
}

u32 gdrGetStatus() {

	switch (gdrcfg.method) {
		case GDR_METHOD_GDI_IMAGE:
			return gdiGetStatusDevice();
		case GDR_METHOD_SCSI:
			return gdrGetStatusDevice();
		default:
			break;
	}

	return 0x22;
}

void gdrReadTOC(u8 *buffer, u32 size) {

	switch (gdrcfg.method) {
	case GDR_METHOD_GDI_IMAGE:
		gdiReadTOCDevice(buffer, size);
		break;
	case GDR_METHOD_SCSI:
		gdrReadTOCDevice(buffer, size);
		break;
	default:
		break;
	}
}

void gdrReadInfoSession(u8 *buffer, u32 session, u32 size) {

	switch (gdrcfg.method) {
	case GDR_METHOD_GDI_IMAGE:
		gdiReadInfoSessionDevice(buffer, session, size);
		break;
	case GDR_METHOD_SCSI:
		gdrReadInfoSessionDevice(buffer, session, size);
		break;
	default:
		break;
	}
}

void gdrReadSectors(u8 *buffer, u32 sector, u32 count, u32 mode) {
	u32 flags;
	u32 sSize;

	if ((mode & 0xe) == 0x8) {
		sSize = 2048;
		flags = 0x10;
	} else {
		sSize = 2056;
		flags = 0x50;
	}

	for (;; ) {
		u32 sCount;
		u32 size;

		if (count > MAX_SECTOR) {
			size = sSize * MAX_SECTOR;
			sCount = MAX_SECTOR;
		} else {
			size = sSize * count;
			sCount = count;
		}

		switch (gdrcfg.method) {
			case GDR_METHOD_GDI_IMAGE:
				gdiReadDevice(buffer, size, sector, sCount, flags);
				break;
			case GDR_METHOD_SCSI:
				gdrReadDevice(buffer, size, sector, sCount, flags);
				break;
		}

		if ((s32)(count -= MAX_SECTOR) <= 0) break;
		sector += MAX_SECTOR;
		buffer += size;
	}
}