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

#ifndef __PLUGINS_H__
#define __PLUGINS_H__

#include "types.h"
#include <windows.h>

// global - main module variables
typedef struct DEmulInfo {
	HANDLE hEmu;
	HWND hMainWnd;
	HINSTANCE hMainInstance;
	HWND hGpuWnd;
} DEmulInfo;

bool  openPlugins();
void closePlugins();

int gpuOpen(DEmulInfo *demulInfo, void* pgpu);
void gpuClose();
void gpuReset();
void gpuConfigure();
void gpuAbout();
void gpuSync();
u32 gpuRead32(u32 mem);
void gpuWrite32(u32 mem, u32 value);
void gpuSetIrqHandler(void (*Handler));
void gpuTaTransfer(u32 *mem, u32 size);
void gpuYuvTransfer(u8 *src, u8 *dst);

int gdrOpen(DEmulInfo *demulInfo);
void gdrClose();
void gdrReset();
void gdrConfigure();
void gdrAbout();
void gdrReadTOC(u8 *buffer, u32 size);
void gdrReadInfoSession(u8 *buffer, u32 session, u32 size);
u32 gdrGetStatus();
void gdrReadSectors(u8 *buffer, u32 sector, u32 count, u32 mode);

int padOpen(DEmulInfo *demulInfo);
void padClose();
void padReset();
void padConfigure();
void padAbout();
u32 padJoyCaps(u32 port);
void padReadJoy(u8 *keymask, u32 port);

int spuOpen(DEmulInfo *demulInfo, void *pspu);
void spuClose();
void spuReset();
void spuConfigure();
void spuAbout();
void spuSync(u32 samples);
u8 spuRead8(u32 mem);
u16 spuRead16(u32 mem);
u32 spuRead32(u32 mem);
void spuWrite8(u32 mem, u8 value);
void spuWrite16(u32 mem, u16 value);
void spuWrite32(u32 mem, u32 value);

#endif
