// Method for working with GD-ROM disks using GDI image file format.

#include <windows.h>
#include <stdio.h>
#include <string>
#include "types.h"
#include "gdi_device.h"

static gdi_device_state gdi;

extern "C"
int  gdiOpenDevice(char *image_path)
{
	memset(&gdi, 0, sizeof(gdi));
	strcpy(gdi.image_path, image_path);

	// Get base dir
	std::string path(image_path);
	size_t found = path.find_last_of("/\\");
	strcpy(gdi.base_dir, path.substr(0, found).c_str());

	// Parse file
	gdi.f = fopen(gdi.image_path, "rt");
	if (!gdi.f) {
		gdi.mounted = false;
		return 1;
	}

	fscanf(gdi.f, "%d\n", &gdi.tracks_count);
	for (int i = 0; i < gdi.tracks_count; i++) {
		fscanf(gdi.f, "%d %d %d %d %s %d\n",
			&gdi.tracks[i].track_num,
			&gdi.tracks[i].start_lba,
			&gdi.tracks[i].track_type,
			&gdi.tracks[i].sector_size,
			&gdi.tracks[i].filename,
			&gdi.tracks[i].offset);

		sprintf(gdi.tracks[i].fullpath, "%s/%s", gdi.base_dir, gdi.tracks[i].filename);

		FILE* f;
		f = fopen(gdi.tracks[i].fullpath, "rb");
		if (f) {

			fseek(f, 0, SEEK_END);
			gdi.tracks[i].filesize = ftell(f);
			fseek(f, 0, SEEK_SET);

			fclose(f);

			gdi.tracks[i].exists = 1;
		}
		else {
			gdi.tracks[i].filesize = 0;
			gdi.tracks[i].exists = 0;
		}
	}

	fclose(gdi.f);
	gdi.f = nullptr;

	gdi.mounted = true;
	return 1;
}

extern "C"
void gdiCloseDevice()
{
	if (gdi.f) {
		fclose(gdi.f);
	}
	memset(&gdi, 0, sizeof(gdi));
}

static void gdiReadSector(size_t sector_num, size_t sector_size, u8* buf)
{
	for (int n = 0; n < gdi.tracks_count; n++) {

		if (!gdi.tracks[n].exists) {
			continue;
		}

		size_t lba_offset = gdi.tracks[n].start_lba;
		size_t track_size_lba = gdi.tracks[n].filesize / gdi.tracks[n].sector_size;
		if (lba_offset >= sector_num && sector_num < (lba_offset + track_size_lba)) {

			gdi.f = fopen(gdi.tracks[n].fullpath, "rb");
			if (gdi.f) {

				fseek(gdi.f, (sector_num - lba_offset) * sector_size, SEEK_SET);
				fread(buf, 1, sector_size, gdi.f);
				fclose(gdi.f);
				gdi.f = nullptr;
			}
			else {
				memset(buf, 0, sector_size);
			}

			break;
		}
	}
}

extern "C"
void gdiReadDevice(u8 *buffer, u32 size, u32 sector, u32 count, u32 flags)
{
	size_t sector_size;

	if (!gdi.mounted) {
		memset(buffer, 0, size);
		return;
	}

	switch (flags) {
		case 0x10:
			sector_size = 2048;
			break;
		case 0x50:
			sector_size = 2056;
			break;
		default:
			return;
	}

	while (count-- != 0) {

		if (size < sector_size)
			break;

		gdiReadSector(sector, sector_size, buffer);

		size -= sector_size;
		buffer += sector_size;
		sector++;
	}
}

extern "C"
u32  gdiGetStatusDevice()
{
	// TODO: wtf these magic numbers
	if (gdi.mounted) return 0x6;
	return 0x22;
}

extern "C"
void gdiReadTOCDevice(u8* buffer, u32 size)
{
	memset(buffer, 0, size);
}

extern "C"
void gdiReadInfoSessionDevice(u8* buffer, u32 session, u32 count)
{
	buffer[0] = 1;
	buffer[1] = 0;
	*(u32*)&buffer[2] = gdi.sessions[session];
}
