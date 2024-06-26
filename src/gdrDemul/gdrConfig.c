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
#include "win32/resource.h"
#include "gdrConfig.h"
#include "device.h"
#include "inifile.h"
#include "Backends.h"

GDR_CFG gdrcfg;

static BOOL CALLBACK Configure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	OPENFILENAME openFileName;
	char openFileBuf[MAX_PATH];

	switch (msg) {
	case WM_INITDIALOG:
	{
		char i;
		int idx, selectedIdx;
		selectedIdx = -1;

		CheckRadioButton(
			hWnd,
			IDC_RADIO_METHOD_SCSI,
			IDC_RADIO_METHOD_GDI,
			gdrcfg.method == GDR_METHOD_SCSI ? IDC_RADIO_METHOD_SCSI : IDC_RADIO_METHOD_GDI);

		SetDlgItemText(hWnd, IDC_EDIT_GDI_PATH, gdrcfg.image_path);

		for (i = 'a'; i < 'z'; i++) {
			char name[256];
			sprintf(name, "%c:", i);
			if ((GetDriveType(name) != DRIVE_CDROM))
				continue;
			idx = (int)SendDlgItemMessage(hWnd, IDC_GDR_COMBO, CB_ADDSTRING, 0, (LPARAM)name);
			if (toupper(i) == toupper(gdrcfg.drive[0]))
				selectedIdx = idx;
		}
		SendDlgItemMessage(hWnd, IDC_GDR_COMBO, CB_SETCURSEL, selectedIdx, 0);

		return TRUE;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
		{
			SendDlgItemMessage(hWnd, IDC_GDR_COMBO, WM_GETTEXT, 5, (LPARAM)gdrcfg.drive);

			if (IsDlgButtonChecked(hWnd, IDC_RADIO_METHOD_SCSI)) {
				gdrcfg.method = GDR_METHOD_SCSI;
			}
			else if (IsDlgButtonChecked(hWnd, IDC_RADIO_METHOD_GDI)) {
				gdrcfg.method = GDR_METHOD_GDI_IMAGE;
			}

			GetDlgItemText(hWnd, IDC_EDIT_GDI_PATH, gdrcfg.image_path, sizeof(gdrcfg.image_path));

			EndDialog(hWnd, 1);
			break;
		}
		case ID_BUTTON_CHOOSE_GDI:
		{
			ZeroMemory(&openFileName, sizeof(openFileName));
			openFileName.lStructSize = sizeof(openFileName);
			openFileName.hwndOwner = hWnd;
			openFileName.lpstrFile = openFileBuf;
			openFileName.lpstrFile[0] = '\0';
			openFileName.nMaxFile = sizeof(openFileBuf);
			openFileName.lpstrFilter = "GDI files (*.gdi)\0*.gdi\0All files (*.*)\0*.*\0";
			openFileName.nFilterIndex = 1;
			openFileName.lpstrFileTitle = NULL;
			openFileName.nMaxFileTitle = 0;
			openFileName.lpstrInitialDir = NULL;
			openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			if (GetOpenFileName(&openFileName) == TRUE) {
				SetDlgItemText(hWnd, IDC_EDIT_GDI_PATH, openFileBuf);
			}
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
	if ((DialogBox(demulInfo.hMainInstance, MAKEINTRESOURCE(IDD_GDR_DIALOG), GetActiveWindow(), (DLGPROC)Configure)) == IDOK) {
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
	IniFile_getString(&iniFile, "drive", "gdi_path", gdrcfg.image_path);
	gdrcfg.method = IniFile_getLong(&iniFile, "drive", "method");
	return true;
}

void gdrSaveConfig() {
	IniFile iniFile;
	if (!IniFile_open(&iniFile, GDR_MODULE_NAME)) return;

	IniFile_setString(&iniFile, "drive", "name", gdrcfg.drive);
	IniFile_setString(&iniFile, "drive", "gdi_path", gdrcfg.image_path);
	IniFile_setLong(&iniFile, "drive", "method", gdrcfg.method);
}