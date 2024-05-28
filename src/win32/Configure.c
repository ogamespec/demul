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

#include <stdio.h>
#include "configure.h"
#include "resource.h"
#include "inifile.h"
#include "Backends.h"
#include "crc32.h"
#include "debug.h"
#include "demul.h"

typedef struct {
	char description[MAX_DESCRIPTION];
	u32 crc32;
	u32 size;
} DatInfo;

CFG cfg;
CFG tuneCfg;

DatInfo dats[] = {
	{ "Sega Dreamcast BIOS v1.004 (1998)(Sega)(Jp)", 0x5454841f, 2097152 },
	{ "Sega Dreamcast BIOS v1.01d (1998)(Sega)(Eu)", 0xa2564fad, 2097152 },
	{ "Sega Dreamcast BIOS v1.01d (1998)(Sega)(US)", 0x89f2b1a1, 2097152 },
	{ "Dreamcast Flash Rom (Eu-Pal)", 0xb7e5aeeb, 131072 },
	{ "Dreamcast Flash Rom (Eu-Pal)[a]", 0x00a8638b, 131072 },
	{ "Dreamcast Flash Rom (Jp-Ntsc)", 0x5f92bf76, 131072 },
	{ "Dreamcast Flash Rom (Jp-Ntsc)[a2]", 0x8af98e26, 131072 },
	{ "Dreamcast Flash Rom (Jp-Ntsc)[a]", 0x307a7035, 131072 },
	{ "Dreamcast Flash Rom (US-Ntsc)", 0xc611b498, 131072 }
};

u8 *biosFileBuf = NULL;

bool LoadConfig() {
	IniFile iniFile;

	memset(&cfg, 0, sizeof(CFG));
	if (!IniFile_open(&iniFile, DEMUL_NAME)) return false;

	if (!IniFile_exist(&iniFile)) {
		MessageBox(GetActiveWindow(), "System Firmware not configured", "Demul", MB_ICONINFORMATION);
		return SetConfig();
	}

	cfg.sh4mode = IniFile_getLong(&iniFile, "main", "sh4mode");

#ifdef DEMUL_DEBUG
	memQuietMode(cfg.sh4mode);
#endif

	IniFile_getString(&iniFile, "files", "bios", cfg.biosFileName);
	IniFile_getString(&iniFile, "files", "flash", cfg.flashFileName);

	return true;
}

void SaveConfig() {
	IniFile iniFile;
	if (!IniFile_open(&iniFile, DEMUL_NAME)) return;

	IniFile_setLong(&iniFile, "main", "sh4mode", cfg.sh4mode);
	IniFile_setString(&iniFile, "files", "bios", cfg.biosFileName);
	IniFile_setString(&iniFile, "files", "flash", cfg.flashFileName);
}

void UpdateBIOSFilesInfo(HWND hwnd) {
	char *biosDescription;
	char *flashDescription;

	LoadBIOSFiles(&tuneCfg, biosFileBuf, biosFileBuf, &biosDescription, &flashDescription);
	SetDlgItemText(hwnd, IDC_BIOS_DIALOG_BIOS, tuneCfg.biosFileName);
	SetDlgItemText(hwnd, IDC_BIOS_DIALOG_FLASH, tuneCfg.flashFileName);
	SetDlgItemText(hwnd, IDC_BIOS_DIALOG_BIOS_DESCRIPTION, biosDescription);
	SetDlgItemText(hwnd, IDC_BIOS_DIALOG_FLASH_DESCRIPTION, flashDescription);
}

BOOL CALLBACK Configure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	OPENFILENAME openFileName;
	char openFileBuf[MAX_PATH];

	switch (msg) {
	case WM_INITDIALOG:
	{
		UpdateBIOSFilesInfo(hwnd);
		return TRUE;
	}


	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BIOS_DIALOG_FLASH_SELECT:
		case IDC_BIOS_DIALOG_BIOS_SELECT:
			ZeroMemory(&openFileName, sizeof(openFileName));
			openFileName.lStructSize = sizeof(openFileName);
			openFileName.hwndOwner = hwnd;
			openFileName.lpstrFile = openFileBuf;
			openFileName.lpstrFile[0] = '\0';
			openFileName.nMaxFile = sizeof(openFileBuf);
			openFileName.lpstrFilter = "All (*.*)\0*.*\0Bios file\0dc_bios.bin\0Flash file\0dc_flash.bin\0";
			if (LOWORD(wParam) == IDC_BIOS_DIALOG_BIOS_SELECT)
				openFileName.nFilterIndex = 2;
			if (LOWORD(wParam) == IDC_BIOS_DIALOG_FLASH_SELECT)
				openFileName.nFilterIndex = 3;
			openFileName.lpstrFileTitle = NULL;
			openFileName.nMaxFileTitle = 0;
			openFileName.lpstrInitialDir = NULL;
			openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			if (GetOpenFileName(&openFileName) == TRUE) {
				if (LOWORD(wParam) == IDC_BIOS_DIALOG_BIOS_SELECT)
					strcpy(tuneCfg.biosFileName, openFileBuf);
				if (LOWORD(wParam) == IDC_BIOS_DIALOG_FLASH_SELECT)
					strcpy(tuneCfg.flashFileName, openFileBuf);

				UpdateBIOSFilesInfo(hwnd);
			}
			break;
		case IDOK:
			EndDialog(hwnd, 1);
			return TRUE;

		case IDCANCEL:
			EndDialog(hwnd, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}

HMODULE SafeLoadLibrary(char *name) {
	HMODULE result;
	UINT oldMode;
	oldMode = SetErrorMode(SEM_FAILCRITICALERRORS);

	result = LoadLibraryEx(name, 0, 0);

	SetErrorMode(oldMode);
	return result;
}

bool SetConfig() {
	tuneCfg = cfg;
	biosFileBuf = (u8*)malloc(BIOS_SIZE);
	if (DialogBox(demulInfo.hMainInstance, MAKEINTRESOURCE(IDD_BIOS_AND_PLUGINS), GetActiveWindow(), (DLGPROC)Configure) == IDOK) {
		free(biosFileBuf);
		cfg = tuneCfg;
		SaveConfig();
		return true;
	}
	free(biosFileBuf);
	return false;
}

bool LoadBIOSFiles(CFG* aCfg, u8*biosBuf, u8*flashBuf, char** biosDescription, char** flashDescription) {
	static char unableToRead[MAX_DESCRIPTION] = "Unable to read file";
	static char unknownFile[MAX_DESCRIPTION] = "Unknown file";
	static char goodSize[MAX_DESCRIPTION] = "Good size";
	FILE *f;
	u32 i;
	u32 crc32;
	bool goodBios = false;
	bool goodFlash = false;
	*biosDescription = *flashDescription = unableToRead;


	f = fopen(aCfg->biosFileName, "rb");
	if (f != NULL) {
		if (fread(biosBuf, BIOS_SIZE, 1, f) == 1) {
			*biosDescription = unknownFile;
			crc32 = CalcCrc32(biosBuf, BIOS_SIZE);
			for (i = 0; i < ARRAYSIZE(dats); i++)
				if ((dats[i].crc32 == crc32) && (dats[i].size == BIOS_SIZE)) {
					*biosDescription = dats[i].description;
					goodBios = true;;
					break;
				}
		}
		fclose(f);
	}

	f = fopen(aCfg->flashFileName, "rb");
	if (f != NULL) {
		if (fread(flashBuf, FLASH_SIZE, 1, f) == 1) {
			*flashDescription = goodSize;
			goodFlash = true;	//even bad content be good
			crc32 = CalcCrc32(flashBuf, FLASH_SIZE);
			for (i = 0; i < ARRAYSIZE(dats); i++)
				if ((dats[i].crc32 == crc32) && (dats[i].size == FLASH_SIZE)) {
					*flashDescription = dats[i].description;
					break;
				}
		}
		fclose(f);
	}

	return goodFlash && goodBios;
}