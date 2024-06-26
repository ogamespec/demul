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
#include <process.h>
#include <wincon.h>

#include "resource.h"
#include "console.h"
#include "demul.h"
#include "Backends.h"
#include "configure.h"

DEmulInfo demulInfo;
static HBITMAP hBitmap;

void UpdateGUIMenuState() {
	HMENU hmenu = GetMenu(demulInfo.hMainWnd);

	CheckMenuItem(hmenu, ID_MODE_INTERPRETER, MF_BYCOMMAND | (!cfg.sh4mode) ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hmenu, ID_MODE_DYNAREC, MF_BYCOMMAND | (cfg.sh4mode) ? MF_CHECKED : MF_UNCHECKED);
	#ifdef DEMUL_DEBUG
	if (!cfg.sh4mode)
		openDebug();
	else
		closeDebug();
	memQuietMode(cfg.sh4mode);
	#endif
}


static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CREATE:
		hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
		break;
	case WM_QUIT:
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		if (demulInfo.hEmu != INVALID_HANDLE_VALUE) SuspendThread(demulInfo.hEmu);
		CloseEmu();
		if (demulInfo.hEmu != INVALID_HANDLE_VALUE) TerminateThread(demulInfo.hEmu, 1);
		if (demulInfo.hEmu != INVALID_HANDLE_VALUE) CloseHandle(demulInfo.hEmu);
		exit(1);
		return TRUE;
	case WM_PAINT: {
		HDC hdcInst, hdcBitmap;
		PAINTSTRUCT ps;
		BITMAP bp;

		GetObject(hBitmap, sizeof(bp), &bp);

		hdcInst = BeginPaint(hWnd, &ps);

		// Create a memory device compatible with the above DC variable

		hdcBitmap = CreateCompatibleDC(hdcInst);

		// Select the new bitmap

		SelectObject(hdcBitmap, hBitmap);

		// Get client coordinates for the StretchBlt() function

		RECT r;
		GetClientRect(hWnd, &r);

		// troublesome part, in my oppinion
		StretchBlt(hdcInst, 0, 0, r.right - r.left, r.bottom - r.top, hdcBitmap, 0, 0, bp.bmWidth, bp.bmHeight, MERGECOPY);

		// Cleanup

		DeleteDC(hdcBitmap);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_FILE_RUN:
			if (demulInfo.hEmu == INVALID_HANDLE_VALUE)
				demulInfo.hEmu = (HANDLE)_beginthread(RunEmu, 0, NULL);
			return TRUE;
		case ID_FILE_EXIT:
			exit(0);
			return TRUE;
		case ID_CONFIG_GDR:
			gdrConfigure();
			return TRUE;
		case ID_CONFIG_GPU:
			gpuConfigure();
			return TRUE;
		case ID_CONFIG_SPU:
			spuConfigure();
			return TRUE;
		case ID_CONFIG_PAD:
			padConfigure();
			return TRUE;
		case ID_CONFIG_BIOS_AND_PLUGINS:
			SetConfig();
			return TRUE;
		case ID_MODE_INTERPRETER:
			cfg.sh4mode = MODE_INTERPRETER;
			SaveConfig();
			UpdateGUIMenuState();
			return TRUE;
		case ID_MODE_DYNAREC:
			cfg.sh4mode = MODE_DYNAREC;
			SaveConfig();
			UpdateGUIMenuState();
			return TRUE;
		case ID_HELP_ABOUT:
			MessageBoxA(hWnd, "Unofficial experimental old Demul, revision " DEMUL_REVISION_STR, "About", MB_OK | MB_ICONINFORMATION);
			break;

		default:
			return TRUE;
		}

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	WNDCLASS wc;
	MSG msg;
	demulInfo.hEmu = INVALID_HANDLE_VALUE;
	demulInfo.hMainInstance = hInstance;

	if (OpenEmu() == 0) return 0;

	wc.lpszClassName = "window";
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = "MENU";
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	RegisterClass(&wc);

	demulInfo.hMainWnd = CreateWindow(
		"window",
		"Demul",
		WS_OVERLAPPED | WS_SYSMENU |
		WS_MINIMIZEBOX | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		910 + GetSystemMetrics(SM_CXFIXEDFRAME) * 2,
		460 + GetSystemMetrics(SM_CXFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYMENU) + GetSystemMetrics(SM_CYCAPTION),
		NULL,
		NULL,
		hInstance,
		NULL
		);


	UnregisterClass("window", hInstance);
	ShowWindow(demulInfo.hMainWnd, SW_SHOWNORMAL);
	UpdateWindow(demulInfo.hMainWnd);

	UpdateGUIMenuState();
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}