// Method for working with GD-ROM disks using GDI image file format.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_GDI_SESSIONS 100
#define MAX_GDI_TRACKS 100

	/// <summary>
	/// https://dreamcast.wiki/GDI_format
	/// </summary>
	typedef struct _gdi_track
	{
		int track_num;			// 1...
		int start_lba;
		int track_type;				// The track type is always 4 for data tracks, and 0 for audio tracks.
		int sector_size;		// Sector size is 2352 for raw data tracks containing error correction, as well as audio tracks. 2048 is used for tracks with error correction stripped.
		char filename[0x100];
		int filesize;			// in bytes
		char fullpath[MAX_PATH];
		int exists;
		int offset;			// The offset field should always be 0.
	} gdi_track;

	typedef struct _gdi_device_state
	{
		char image_path[MAX_PATH];
		char base_dir[MAX_PATH];
		bool mounted;
		FILE* f;
		u32 sessions[MAX_GDI_SESSIONS];
		gdi_track tracks[MAX_GDI_TRACKS];
		int tracks_count;
		GDR_TOC toc;
	} gdi_device_state;

	int  gdiOpenDevice(char* image_path);
	void gdiReadDevice(u8* buffer, u32 size, u32 sector, u32 count, u32 flags);
	void gdiCloseDevice();
	u32  gdiGetStatusDevice();
	void gdiReadTOCDevice(u8* buffer, u32 size);
	void gdiReadInfoSessionDevice(u8* buffer, u32 session, u32 count);

#ifdef __cplusplus
};
#endif
