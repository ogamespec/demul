// Common definitions for the GDR subsystem.

#pragma once

#pragma pack(push, 1)
typedef struct _GDR_TOC {
	u32 entry[99];			// track offset in LBA
	u32 first;			// start LBA
	u32 last;			// last LBA
	u32 leadout;		// offset in LBA of the residue without tracks
} GDR_TOC;
#pragma pack(pop)


#define GDROM_SIZE 1227104256  // bytes
