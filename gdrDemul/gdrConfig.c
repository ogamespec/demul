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
#include "resource.h"
#include "gdrConfig.h"
#include "device.h"
#include "inifile.h"
#include "plugins.h"

GDR_CFG gdrcfg;
extern DEmulInfo* gdrDemulInfo;

static BOOL CALLBACK Configure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
	{
		char i;
		int idx, selectedIdx;
		selectedIdx = -1;

		for (i = 'a'; i < 'z'; i++) {
			char name[256];
			sprintf(name, "%c:", i);
			if ((GetDriveType(name) != DRIVE_CDROM))
				continue;
			idx = SendDlgItemMessage(hWnd, IDC_COMBO, CB_ADDSTRING, 0, (LPARAM)name);
			if (toupper(i) == toupper(gdrcfg.drive[0]))
				selectedIdx = idx;
		}
		SendDlgItemMessage(hWnd, IDC_COMBO, CB_SETCURSEL, selectedIdx, 0);

		return TRUE;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
		{
			char drive[8];

			SendDlgItemMessage(hWnd, IDC_COMBO, WM_GETTEXT, 5, (LPARAM)drive);
			strcpy(gdrcfg.drive, drive);
			EndDialog(hWnd, 1);
			break;
		}

		case WM_CLOSE:
		case IDCANCEL:
			EndDialog(hWnd, 0);
			break;
		}
		break;
	}

	return FALSE;
}


bool gdrSetConfig() {
	if ((DialogBox(gdrDemulInfo->hMainInstance, MAKEINTRESOURCE(IDD_DIALOG), GetActiveWindow(), (DLGPROC)Configure)) == IDOK) {
		gdrSaveConfig();
		return true;
	}
	return false;
}

bool gdrLoadConfig(bool autoSetConfig) {
	IniFile iniFile;

	memset(&gdrcfg, 0, sizeof(gdrcfg));
	if (!IniFile_open(&iniFile, GDR_MODULE_NAME)) return false;

	if (!IniFile_exist(&iniFile)) {
		if (!autoSetConfig)
			return true;
		MessageBox(GetActiveWindow(), "gdrDemul not configured", GDR_MODULE_NAME, MB_ICONINFORMATION);
		return gdrSetConfig();
	}

	IniFile_getString(&iniFile, "drive", "name", gdrcfg.drive);
	return true;
}

void gdrSaveConfig() {
	IniFile iniFile;
	if (!IniFile_open(&iniFile, GDR_MODULE_NAME)) return;

	IniFile_setString(&iniFile, "drive", "name", gdrcfg.drive);
}