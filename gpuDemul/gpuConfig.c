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
#include "gpuConfig.h"
#include "gpuDemul.h"
#include "inifile.h"

GPU_CFG gpucfg;

WPARAM GetCBState(long state) {
	return state != 0 ? BST_CHECKED : BST_UNCHECKED;
}

void UpdateCfg(HWND hwnd) {
	gpucfg.fullScreen = SendDlgItemMessage(hwnd, IDC_GPU_FULL_SCREEN, BM_GETCHECK, 0, 0) != BST_UNCHECKED;
	gpucfg.ListSorting = SendDlgItemMessage(hwnd, IDC_GPU_CHECK2, BM_GETCHECK, 0, 0) != BST_UNCHECKED;
	gpucfg.AlphasubSort = SendDlgItemMessage(hwnd, IDC_GPU_CHECK3, BM_GETCHECK, 0, 0) != BST_UNCHECKED;
	gpucfg.PunchsubSort = SendDlgItemMessage(hwnd, IDC_GPU_CHECK5, BM_GETCHECK, 0, 0) != BST_UNCHECKED;
	gpucfg.AlphaZWriteDisable = SendDlgItemMessage(hwnd, IDC_GPU_CHECK4, BM_GETCHECK, 0, 0) != BST_UNCHECKED;
	gpucfg.Wireframe = SendDlgItemMessage(hwnd, IDC_GPU_CHECK6, BM_GETCHECK, 0, 0) != BST_UNCHECKED;
	gpucfg.check7 = SendDlgItemMessage(hwnd, IDC_GPU_CHECK7, BM_GETCHECK, 0, 0) != BST_UNCHECKED;
	gpucfg.check8 = SendDlgItemMessage(hwnd, IDC_GPU_CHECK8, BM_GETCHECK, 0, 0) != BST_UNCHECKED;
}

static BOOL CALLBACK Configure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hwnd, IDC_GPU_FULL_SCREEN, BM_SETCHECK, GetCBState(gpucfg.fullScreen), 0);
		SendDlgItemMessage(hwnd, IDC_GPU_CHECK2, BM_SETCHECK, GetCBState(gpucfg.ListSorting), 0);
		SendDlgItemMessage(hwnd, IDC_GPU_CHECK3, BM_SETCHECK, GetCBState(gpucfg.AlphasubSort), 0);
		SendDlgItemMessage(hwnd, IDC_GPU_CHECK4, BM_SETCHECK, GetCBState(gpucfg.AlphaZWriteDisable), 0);
		SendDlgItemMessage(hwnd, IDC_GPU_CHECK5, BM_SETCHECK, GetCBState(gpucfg.PunchsubSort), 0);
		SendDlgItemMessage(hwnd, IDC_GPU_CHECK6, BM_SETCHECK, GetCBState(gpucfg.Wireframe), 0);
		SendDlgItemMessage(hwnd, IDC_GPU_CHECK7, BM_SETCHECK, GetCBState(gpucfg.check7), 0);
		SendDlgItemMessage(hwnd, IDC_GPU_CHECK8, BM_SETCHECK, GetCBState(gpucfg.check8), 0);

		return TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			UpdateCfg(hwnd);
			EndDialog(hwnd, 1);
			return TRUE;

		case IDCANCEL:
			EndDialog(hwnd, 0);
			return TRUE;

		case IDC_GPU_CHECK2:
		case IDC_GPU_CHECK3:
		case IDC_GPU_CHECK4:
		case IDC_GPU_CHECK5:
		case IDC_GPU_CHECK6:
		case IDC_GPU_CHECK7:
		case IDC_GPU_CHECK8:
			UpdateCfg(hwnd);
			break;
		}
		break;
	}

	return FALSE;
}


bool gpuSetConfig() {
	GPU_CFG backUp;
	backUp = gpucfg;
	if (DialogBox(demulInfo.hMainInstance, MAKEINTRESOURCE(IDD_GPU_DIALOG), GetActiveWindow(), (DLGPROC)Configure) == IDOK) {
		gpuSaveConfig();
		return true;
	}
	gpucfg = backUp;
	return false;
}


bool gpuLoadConfig(bool autoSetConfig) {
	IniFile iniFile;

	memset(&gpucfg, 0, sizeof(gpucfg));
	if (!IniFile_open(&iniFile, GPU_MODULE_NAME)) return false;

	if (!IniFile_exist(&iniFile)) {
		if (!autoSetConfig)
			return true;
		MessageBox(GetActiveWindow(), "gpuDemul not configured", GPU_MODULE_NAME, MB_ICONINFORMATION);
		return gpuSetConfig();
	}
	gpucfg.fullScreen = IniFile_getLong(&iniFile, "main", "FullScreen");
	gpucfg.ListSorting = IniFile_getLong(&iniFile, "main", "ListSorting");
	gpucfg.AlphasubSort = IniFile_getLong(&iniFile, "main", "AlphasubSort");
	gpucfg.AlphaZWriteDisable = IniFile_getLong(&iniFile, "main", "AlphaZWriteDisable");
	gpucfg.PunchsubSort = IniFile_getLong(&iniFile, "main", "PunchsubSort");
	gpucfg.Wireframe = IniFile_getLong(&iniFile, "main", "Wireframe");
	gpucfg.check7 = IniFile_getLong(&iniFile, "main", "check7");
	gpucfg.check8 = IniFile_getLong(&iniFile, "main", "check8");
	return true;
}

void gpuSaveConfig() {
	IniFile iniFile;
	if (!IniFile_open(&iniFile, GPU_MODULE_NAME)) return;

	IniFile_setLong(&iniFile, "main", "FullScreen", gpucfg.fullScreen);
	IniFile_setLong(&iniFile, "main", "ListSorting", gpucfg.ListSorting);
	IniFile_setLong(&iniFile, "main", "AlphasubSort", gpucfg.AlphasubSort);
	IniFile_setLong(&iniFile, "main", "AlphaZWriteDisable", gpucfg.AlphaZWriteDisable);
	IniFile_setLong(&iniFile, "main", "PunchsubSort", gpucfg.PunchsubSort);
	IniFile_setLong(&iniFile, "main", "Wireframe", gpucfg.Wireframe);
	IniFile_setLong(&iniFile, "main", "check7", gpucfg.check7);
	IniFile_setLong(&iniFile, "main", "check8", gpucfg.check8);
}
