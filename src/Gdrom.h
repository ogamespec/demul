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

#ifndef __GDROM_H__
#define __GDROM_H__

#include "types.h"

typedef struct {
	u8 busy;
	u8 ftrs;
	u8 irsn;
	u8 stat;
	u8 cntlo;
	u8 cnthi;
	u32 count;
} GDROM;

GDROM gdrom;

u32 bufsize;
u32 position;
u8 buffer[0x01000000];

u32 index;
u32 count;

u8   ReadGdrom8(u32 mem);
u16  ReadGdrom16(u32 mem);

void WriteGdrom8(u32 mem, u8 value);
void WriteGdrom16(u32 mem, u16 value);

static u8 rom[] =
{
	0x96, 0x0B, 0x45, 0xF0, 0x7E, 0xFF, 0x3D, 0x06,
	0x4D, 0x7D, 0x10, 0xBF, 0x07, 0x00, 0x73, 0xCF,
	0x9C, 0x00, 0xBC, 0x0C, 0x1C, 0xAF, 0x1C, 0x30,
	0xE7, 0xA7, 0x03, 0xA8, 0x98, 0x00, 0xBD, 0x0F,
	0xBD, 0x5B, 0xAA, 0x50, 0x23, 0x39, 0x31, 0x10,
	0x0E, 0x69, 0x13, 0xE5, 0x00, 0xD2, 0x0D, 0x66,
	0x54, 0xBF, 0x5F, 0xFD, 0x37, 0x74, 0xF4, 0x5B,
	0x22, 0x00, 0xC6, 0x09, 0x0F, 0xCA, 0x93, 0xE8,
	0xA4, 0xAB, 0x00, 0x61, 0x0E, 0x2E, 0xE1, 0x4B,
	0x76, 0x8B, 0x6A, 0xA5, 0x9C, 0xE6, 0x23, 0xC4,
	0x00, 0x4B, 0x06, 0x1B, 0x91, 0x01, 0x00, 0xE2,
	0x0D, 0xCF, 0xCA, 0x38, 0x3A, 0xB9, 0xE7, 0x91,
	0xE5, 0xEF, 0x4B, 0x00, 0xD6, 0x09, 0xD3, 0x68,
	0x3E, 0xC4, 0xAF, 0x2D, 0x00, 0x2A, 0x0D, 0xF9,
	0xFC, 0x78, 0xED, 0xAE, 0x99, 0xB3, 0x32, 0x5A,
	0xE7, 0x00, 0x4C, 0x0A, 0x22, 0x97, 0x5B, 0x82,
	0x06, 0x7A, 0x4C, 0x00, 0x42, 0x0E, 0x57, 0x78,
	0x46, 0xF5, 0x20, 0xFC, 0x6B, 0xCB, 0x01, 0x5B,
	0x86, 0x00, 0xE4, 0x0E, 0xB2, 0x26, 0xCD, 0x71,
	0xE3, 0xA5, 0x33, 0x06, 0x8E, 0x9A, 0x50, 0x00,
	0x07, 0x07, 0xF5, 0x34, 0xEF, 0xE6, 0x00, 0x32,
	0x0F, 0x13, 0x41, 0x59, 0x56, 0x0F, 0x02, 0x38,
	0x2A, 0x64, 0x2A, 0x07, 0x3E, 0x00, 0x52, 0x11,
	0x2A, 0x1D, 0x5F, 0x76, 0x66, 0xA0, 0xB2, 0x2F,
	0x97, 0xC7, 0x5E, 0x6E, 0x52, 0xE2, 0x00, 0x58,
	0x09, 0xCA, 0x89, 0xA5, 0xDF, 0x0A, 0xDE, 0x00,
	0x50, 0x06, 0x49, 0xB8, 0xB4, 0x00, 0x77, 0x05,
	0x24, 0xE8, 0x00, 0xBB, 0x0C, 0x91, 0x89, 0xA2,
	0x8B, 0x62, 0xDE, 0x6A, 0xC6, 0x60, 0x00, 0xE7,
	0x0F, 0x0F, 0x11, 0x96, 0x55, 0xD2, 0xBF, 0xE6,
	0x48, 0x0B, 0x5C, 0xAB, 0xDC, 0x00, 0xBA, 0x0A,
	0x30, 0xD7, 0x48, 0x0E, 0x78, 0x63, 0x0C, 0x00,
	0xD2, 0x0D, 0xFB, 0x8A, 0xA3, 0xFE, 0xF8, 0x3A,
	0xDD, 0x88, 0xA9, 0x4B, 0x00, 0xA2, 0x0A, 0x75,
	0x5D, 0x0D, 0x37, 0x24, 0xC5, 0x9D, 0x00, 0xF7,
	0x0B, 0x25, 0xEF, 0xDB, 0x41, 0xE0, 0x52, 0x3E,
	0x4E, 0x00, 0xB7, 0x03, 0x00, 0xE5, 0x11, 0xB9,
	0xDE, 0x5A, 0x57, 0xCF, 0xB9, 0x1A, 0xFC, 0x7F,
	0x26, 0xEE, 0x7B, 0xCD, 0x2B, 0x00, 0x4B, 0x08,
	0xB8, 0x09, 0x70, 0x6A, 0x9F, 0x00, 0x4B, 0x11,
	0x8C, 0x15, 0x87, 0xA3, 0x05, 0x4F, 0x37, 0x8E,
	0x63, 0xDE, 0xEF, 0x39, 0xFC, 0x4B, 0x00, 0xAB,
	0x10, 0x0B, 0x91, 0xAA, 0x0F, 0xE1, 0xE9, 0xAE,
	0x69, 0x3A, 0xF8, 0x03, 0x69, 0xD2, 0x00, 0xE2,
	0x07, 0xC1, 0x5C, 0x3D, 0x82, 0x00, 0xA9, 0x08,
	0x68, 0xC4, 0xAD, 0x2E, 0xD1, 0x00, 0xF7, 0x0E,
	0xC6, 0x47, 0xC8, 0xCD, 0x8E, 0x7C, 0x00, 0x5C,
	0x95, 0xB9, 0xF4, 0x00, 0xE3, 0x04, 0x5B, 0x00,
	0x74, 0x07, 0x65, 0xC7, 0x84, 0x8E, 0x00, 0xC6,
	0x07, 0x61, 0x80, 0x44, 0x3F, 0x00, 0xC8, 0x0E,
	0x72, 0x78, 0x47, 0xD3, 0xC2, 0x4D, 0xAF, 0xC0,
	0x54, 0x13, 0x31, 0x00, 0xF7, 0x0D, 0x48, 0xD8,
	0xE2, 0x92, 0x9F, 0x7F, 0x2F, 0x44, 0x68, 0x33,
	0x00, 0x0D, 0x10, 0xAB, 0xFE, 0xEA, 0x8E, 0x19,
	0x81, 0xF8, 0x6F, 0x7C, 0xDE, 0xE1, 0xB3, 0x06,
	0x00, 0x4D, 0x11, 0x66, 0xAE, 0x4C, 0xF9, 0xB7,
	0x2F, 0xEE, 0xB0, 0x8E, 0x7E, 0xE1, 0x8D, 0x95,
	0x6F, 0x00, 0xF4, 0x0D, 0x88, 0x9D, 0xCA, 0xE3,
	0xC4, 0xB2, 0x47, 0xBB, 0xA0, 0x69, 0x00, 0xF3,
	0x0B, 0x48, 0x17, 0x41, 0x64, 0xA0, 0x0E, 0x71,
	0x82, 0x00, 0x34, 0x1E, 0x18, 0x4D, 0x85, 0x80,
	0x4C, 0xA9, 0x0B, 0x66, 0x9B, 0x75, 0x13, 0x61,
	0x70, 0x27, 0x81, 0x7A, 0x02, 0xCD, 0x57, 0xAB,
	0xDF, 0x02, 0x93, 0x52, 0x83, 0xDF, 0x48, 0xA8,
	0xA6, 0x9E, 0x74, 0x6F, 0x89, 0x03, 0x28, 0x25,
	0x52, 0x96, 0xFF, 0x67, 0x7A, 0xD8, 0x3C, 0xB1,
	0x2C, 0x46, 0x84, 0xEF, 0xE1, 0xC1, 0xC6, 0xC9,
	0xDC, 0x96, 0xAA, 0xA9, 0xC4, 0x82, 0x58, 0x27,
	0x57, 0x75, 0x67, 0x34, 0xFB, 0x3B, 0x25, 0xBF,
	0xFB, 0x3B, 0xF6, 0x13, 0xEC, 0x96, 0xE5, 0x16,
	0x26, 0xFD, 0xA8, 0xDA, 0x1B, 0xC6, 0x50, 0x7F,
	0x47, 0xFF, 0x08, 0x55, 0x08, 0xED, 0x00, 0x93,
	0x9B, 0xC4, 0x71, 0x67, 0xEC, 0xA6, 0xCC, 0x16,
	0x20, 0x87, 0x47, 0x07, 0xA6, 0x00, 0x79, 0x5D,
	0x4F, 0xAB, 0xA1, 0x6F, 0x7A, 0x6B, 0x27, 0xC4,
	0xDA, 0xA3, 0xC3, 0x94, 0x4F, 0x7F, 0xF3, 0xE5,
	0x1B, 0x6F, 0xCC, 0xE5, 0xF0, 0xE5, 0x9D, 0xC9,
	0xAE, 0xFD, 0x39, 0xAC, 0x4C, 0xE5, 0x58, 0x83,
	0x25, 0x65, 0x92, 0x74, 0x9E, 0x81, 0xA0, 0xB6,
	0xA9, 0x02, 0x9B, 0x07, 0xB6, 0xE7, 0x79, 0x57,
	0xD9, 0x4A, 0xCE, 0xFA, 0xB4, 0x94, 0x05, 0xCC,
	0x86, 0x3C, 0xDD, 0x06, 0xCD, 0xA6, 0x24, 0x24,
	0xFA, 0xC1, 0xF9, 0x48, 0xC9, 0x0C, 0x6C, 0xC4,
	0x96, 0x82, 0x17, 0xF6, 0x31, 0x09, 0xC4, 0xE2,
	0x77, 0xFD, 0xCF, 0x46, 0x18, 0xB2, 0x5F, 0x01,
	0x6B, 0xD1, 0x7B, 0x56, 0xB8, 0x94, 0x4A, 0xE5,
	0x6C, 0x19, 0xF0, 0xC0, 0xB6, 0x70, 0x93, 0xF7,
	0xD3, 0xD1, 0x2B, 0x6E, 0x7C, 0x53, 0x6D, 0x85,
	0xD1, 0x0C, 0x8B, 0x77, 0xEE, 0x90, 0xDA, 0x15,
	0x55, 0xE0, 0x58, 0x09, 0x56, 0xFC, 0x31, 0x9F,
	0xAF, 0x46, 0xCB, 0xC3, 0x8D, 0x71, 0x75, 0xF2,
	0x2C, 0xC3, 0xBB, 0xA1, 0xC4, 0xCF, 0x27, 0x56,
	0x7C, 0x9B, 0xFE, 0xAF, 0x3E, 0x4E, 0xB4, 0xCD,
	0x6A, 0xAA, 0xF5, 0xF3, 0xE3, 0x22, 0x82, 0xE1,
	0xA5, 0x68, 0xB3, 0xDB, 0x8F, 0x9E, 0x5E, 0x7B,
	0x90, 0xF0, 0x79, 0x3F, 0x52, 0x8C, 0x61, 0x88,
	0x76, 0xAE, 0x14, 0x63, 0x19, 0x0F, 0x1D, 0xCE,
	0xA1, 0x63, 0x10, 0xB2, 0xE2, 0xD7, 0x94, 0xB1,
	0x33, 0xCB, 0x28, 0x85, 0x7D, 0x9B, 0xF5, 0xF4,
	0x25, 0x50, 0x9B, 0xDB, 0x35, 0xA5, 0xB0, 0x9C,
	0x09, 0x92, 0xE3, 0x31, 0x40, 0xAB, 0x4D, 0xF4,
	0x35, 0xE8, 0xB3, 0x0A, 0x21, 0xC3, 0x86, 0x9C,
	0xCB, 0x29, 0xA4, 0x77, 0x57, 0xBC, 0xD8, 0xDA,
	0xA5, 0x82, 0x80, 0xE8, 0xCF, 0x72, 0x81, 0xAD,
	0x2E, 0x28, 0xFF, 0xD8, 0xB6, 0xD1, 0x2B, 0x97,
	0x00, 0xFF, 0xE1, 0x06, 0x44, 0x39, 0x1C, 0x4B,
	0xAB, 0x19, 0x5B, 0x4D, 0xD6, 0x3E, 0x1B, 0x5C,
	0x64, 0xBB, 0x32, 0x68, 0xF5, 0x7C, 0xC9, 0x9E,
	0xE8, 0xB4, 0x29, 0x1B, 0x7F, 0x4D, 0x80, 0x80,
	0x7E, 0x8B, 0x1C, 0x0A, 0xE6, 0x9A, 0xBF, 0x49,
	0x1E, 0xC5, 0xB6, 0x67, 0x7D, 0x05, 0xE4, 0x90,
	0x40, 0x4B, 0xAF, 0x9B, 0x52, 0xDE, 0x17, 0x80,
	0x81, 0x56, 0xEA, 0x3A, 0x53, 0x82, 0x8C, 0x62,
	0xFB, 0x96, 0x97, 0x6F, 0xC1, 0x16, 0x78, 0xD4,
	0x7B, 0xE7, 0xB9, 0x5A, 0x2A, 0xEB, 0x87, 0x68,
	0x33, 0xD3, 0x31, 0x45, 0xFA, 0xFE, 0xF4, 0x1C,
	0x90, 0x86, 0x73, 0x77, 0xD9, 0xA9, 0xD1, 0x4A,
	0x4A, 0xCF, 0xAE, 0x23, 0xDB, 0xF9, 0x09, 0xD8,
	0x18, 0xDC, 0x6A, 0x0D, 0xE4, 0x19, 0x8C, 0x65,
	0xC6, 0x64, 0xC7, 0xDC, 0xA9, 0xE3, 0x91, 0xB1,
	0x4C, 0xC8, 0xC1, 0x9E, 0x3B, 0x7F, 0xCB, 0xA3,
	0xCF, 0xDD, 0xF0, 0x1D, 0x07, 0x6E, 0xDC, 0xCE,
	0x0D, 0xCD, 0x7E, 0x1E, 0x55, 0x11, 0x8B, 0xDF,
	0x3A, 0xAB, 0xB6, 0x3B, 0x6E, 0x52, 0x7F, 0xA7,
	0x00, 0xD1, 0x33, 0xBE, 0xF2, 0x9B, 0xFC, 0x4A,
	0xCF, 0x9D, 0x8F, 0xC6, 0xC4, 0x7B, 0xDA, 0xE7,
	0x2A, 0x1C, 0x26, 0x6E, 0x00, 0x00, 0x00, 0x00,
	0x42, 0x07, 0xF0, 0x47, 0x07, 0x1B, 0x10, 0xED,
	0x05, 0xBC, 0xC0, 0x00, 0xA7, 0x08, 0x94, 0x78,
	0x6D, 0x0A, 0x4B, 0x00, 0xA5, 0x0E, 0xDD, 0xC4,
	0x49, 0x38, 0x82, 0x0D, 0xFC, 0xD5, 0x5E, 0x2A,
	0xB7, 0x00, 0x9A, 0x0B, 0xEC, 0x1D, 0xBB, 0x85,
	0x5C, 0x81, 0xF4, 0x82, 0x00, 0x69, 0x0A, 0x9E,
	0x34, 0xE7, 0x3D, 0x73, 0x22, 0x83, 0x00, 0x68,
	0x0F, 0x3F, 0x3E, 0x26, 0x83, 0x55, 0xBF, 0x6D,
	0xB3, 0xEB, 0x0F, 0x07, 0xC4, 0x00, 0xE1, 0x07,
	0xD8, 0xFE, 0x35, 0xFC, 0x00, 0x00, 0x0E, 0x79,
	0x47, 0x65, 0xDE, 0x52, 0xE3, 0xEF, 0xD4, 0x97,
	0x77, 0xB0, 0x00, 0x9B, 0x04, 0x67, 0x00, 0xBE,
	0x03, 0x00, 0xDE, 0x05, 0x36, 0x7B, 0x00, 0x0C,
	0x0C, 0x3D, 0x8B, 0x0C, 0x6F, 0xB1, 0x79, 0x00,
	0x13, 0xCE, 0x00, 0xEC, 0x07, 0x12, 0x3D, 0xF2,
	0x6B, 0x00, 0x4F, 0x04, 0xD4, 0x00, 0xE1, 0x11,
	0x03, 0x89, 0x78, 0x76, 0x39, 0x1E, 0x8A, 0xAC,
	0xCF, 0xEF, 0xFA, 0xBA, 0x03, 0xC5, 0x00, 0x8E,
	0x07, 0x0B, 0x50, 0xAA, 0xEE, 0x00, 0x99, 0x0B,
	0x9E, 0x52, 0x66, 0x4B, 0x6E, 0xEE, 0xCE, 0x2B,
	0x00, 0xFC, 0x0C, 0x67, 0x60, 0x71, 0xA9, 0x32,
	0xE3, 0x9F, 0x88, 0xBC, 0x00, 0xE0, 0x0E, 0x7B,
	0x8A, 0xA3, 0x48, 0x0C, 0xDA, 0xEB, 0xC4, 0x53,
	0x2D, 0x78, 0x00, 0x65, 0x0C, 0xDA, 0x21, 0xD6,
	0x9F, 0x4C, 0xA9, 0xA6, 0xEE, 0x91, 0x00, 0xDD,
	0x08, 0x75, 0xC8, 0x14, 0x0E, 0x20, 0x00, 0x60,
	0x10, 0x69, 0x30, 0x2C, 0x7F, 0xC8, 0x6D, 0x28,
	0xFA, 0x40, 0x8A, 0x88, 0x89, 0xEC, 0x00, 0xDD,
	0x0D, 0x85, 0x01, 0x5D, 0x85, 0x80, 0xAD, 0x9E,
	0xAA, 0x2E, 0x24, 0x00, 0xA3, 0x10, 0x84, 0x60,
	0xAF, 0x09, 0xD2, 0x26, 0xC5, 0x47, 0x50, 0x0D,
	0x1B, 0xB6, 0xC5, 0x00, 0x9C, 0x03, 0x00, 0x26,
	0x0D, 0x5E, 0x88, 0xC2, 0xE4, 0xFE, 0x63, 0xD8,
	0x97, 0xF1, 0xCA, 0x00, 0x2F, 0x0F, 0xA7, 0x4A,
	0xCE, 0x2E, 0x67, 0x23, 0x7C, 0x50, 0xD8, 0x95,
	0xE1, 0x28, 0x00, 0xF8, 0x09, 0x15, 0x75, 0xBE,
	0xB5, 0xAD, 0x11, 0x00, 0x45, 0x11, 0xB1, 0x43,
	0x11, 0x2D, 0xB3, 0x12, 0x87, 0x59, 0x55, 0x98,
	0x61, 0x31, 0x01, 0x0B, 0x00, 0xCE, 0x0E, 0x1A,
	0xA4, 0xFC, 0xCE, 0x34, 0x2F, 0xB4, 0x78, 0xCF,
	0x19, 0xE4, 0x00, 0xA7, 0x0F, 0x1A, 0xE7, 0xB5,
	0x47, 0x57, 0x41, 0x4C, 0x30, 0x2E, 0xBF, 0xB3,
	0x2C, 0x00, 0x42, 0x07, 0x67, 0xEC, 0xEB, 0x68,
	0x00, 0x90, 0x09, 0x9B, 0xC5, 0x35, 0x52, 0xEF,
	0x15, 0x00, 0xF5, 0x08, 0xDE, 0x61, 0x4A, 0xA4,
	0x2D, 0x00, 0x53, 0x08, 0x37, 0xAF, 0x76, 0x26,
	0x83, 0x00, 0x7B, 0x09, 0x52, 0x54, 0xC7, 0x36,
	0x8F, 0xE3, 0x00, 0xA3, 0x0C, 0x08, 0x81, 0xBB,
	0xB5, 0x86, 0xA6, 0x24, 0xD2, 0xBC, 0x00, 0x45,
	0x0F, 0x49, 0xBF, 0xDB, 0xF5, 0x32, 0x43, 0xCE,
	0x2C, 0x4A, 0x8C, 0xA3, 0x98, 0x00, 0xD7, 0x0D,
	0x6A, 0x89, 0xE6, 0x1A, 0x63, 0xBC, 0x68, 0x35,
	0xA3, 0xE2, 0x00, 0x7B, 0x10, 0x52, 0xEC, 0x59,
	0x85, 0x48, 0x0A, 0xC9, 0xBC, 0x4D, 0xB0, 0x97,
	0x9E, 0x0E, 0x00, 0xD0, 0x09, 0x4C, 0x95, 0x80,
	0x79, 0x94, 0x2E, 0x00, 0x0A, 0x0D, 0x17, 0x5E,
	0x86, 0xEC, 0xBD, 0x2C, 0xC7, 0x96, 0xEB, 0x90,
	0x00, 0x2C, 0x42, 0x48, 0x12, 0x5B, 0x2B, 0xE4,
	0x58, 0xBF, 0x36, 0x2C, 0xBE, 0x8B, 0x78, 0x31,
	0xAC, 0x43, 0xD0, 0x90, 0x84, 0xD0, 0x08, 0x23,
	0x40, 0x05, 0xA3, 0xA1, 0xA5, 0x90, 0xDE, 0x68,
	0x3D, 0xC1, 0x43, 0x68, 0x70, 0x7F, 0xBF, 0xEF,
	0x7F, 0x97, 0x56, 0x9E, 0x4A, 0x3D, 0x0F, 0x3B,
	0x46, 0xE7, 0x1A, 0x8B, 0x22, 0x06, 0x0D, 0x28,
	0xEF, 0x81, 0x05, 0xAA, 0xEB, 0xAC, 0x25, 0x69,
	0x40, 0x9F, 0xD6, 0x20, 0x41, 0x3B, 0x22, 0x71,
	0xFD, 0xE9, 0x76, 0xF9, 0xAE, 0x02, 0x16, 0x18,
	0x16, 0x22, 0x9C, 0xFB, 0xA5, 0x32, 0x43, 0xD4,
	0x81, 0xA4, 0x92, 0x50, 0x3E, 0x84, 0xCD, 0x0E,
	0x9A, 0x6D, 0x28, 0x51, 0x8F, 0x0D, 0x25, 0x2E,
	0xD1, 0xF8, 0xEF, 0x27, 0x61, 0xDB, 0xE5, 0x1B,
	0x00, 0x61, 0x18, 0x9B, 0x6E, 0xA1, 0x9C, 0x32,
	0x05, 0x69, 0xF8, 0xF0, 0xAC, 0x15, 0x4C, 0xCF,
	0x18, 0x7E, 0x0A, 0x87, 0xA1, 0x3B, 0x33, 0xFB,
	0x22, 0x3B, 0xE3, 0x0A, 0xC4, 0xA2, 0x38, 0x4F,
	0x9F, 0x29, 0x58, 0x4E, 0xD8, 0xB8, 0xC2, 0xCB,
	0x55, 0xAA, 0x47, 0x08, 0x6C, 0xEA, 0xFB, 0xD6,
	0xD6, 0xB4, 0x44, 0x57, 0x17, 0x43, 0xE3, 0xB1,
	0xC2, 0xEF, 0x43, 0x20, 0xC9, 0xE4, 0x70, 0x3A,
	0x14, 0x4E, 0xA9, 0xA4, 0xA9, 0x62, 0xD4, 0x42,
	0xA8, 0x56, 0x43, 0x4A, 0x24, 0xF0, 0x18, 0x71,
	0x79, 0xF4, 0xC7, 0xA4, 0xD9, 0x54, 0xDF, 0x65,
	0x15, 0x0A, 0xA5, 0x34, 0x0F, 0x60, 0xF7, 0x13,
	0x02, 0xF1, 0xC5, 0x22, 0xC6, 0x0B, 0xBE, 0x65,
	0x3B, 0x50, 0x90, 0x73, 0x6A, 0x8F, 0xD2, 0x5D,
	0xDA, 0x39, 0x7B, 0x95, 0xD5, 0x10, 0x43, 0x01,
	0x4C, 0xB8, 0xDF, 0x87, 0x9C, 0xC9, 0x84, 0x43,
	0x1B, 0xF3, 0xBA, 0xB1, 0x86, 0x89, 0x9F, 0x1C,
	0x1A, 0x8E, 0x29, 0x44, 0x7F, 0xCF, 0x22, 0x14,
	0xBE, 0xED, 0x55, 0x88, 0xC4, 0x2E, 0x8F, 0xBF,
	0xD6, 0xD2, 0x68, 0x15, 0x85, 0x35, 0xC6, 0x1F,
	0x36, 0x02, 0x4A, 0x26, 0x10, 0x03, 0x3B, 0xC6,
	0x7B, 0x8E, 0x40, 0x4D, 0x4C, 0x15, 0x72, 0x8D,
	0xE2, 0x0D, 0x1F, 0x87, 0x44, 0x4F, 0x7D, 0xFC,
	0xBD, 0xB8, 0x67, 0x60, 0x79, 0x9C, 0xE1, 0x54,
	0x13, 0x9B, 0x04, 0x32, 0x83, 0x0D, 0xA2, 0x31,
	0x0B, 0x48, 0x69, 0x3D, 0xEA, 0x40, 0x42, 0xDA,
	0x15, 0xB0, 0xAE, 0x25, 0xBC, 0x2A, 0x3E, 0xE2,
	0xEF, 0xAF, 0x22, 0xDE, 0x80, 0x2E, 0x24, 0x4A,
	0x83, 0xF8, 0xE4, 0x0F, 0x2B, 0x32, 0x4B, 0x08,
	0xF8, 0x6F, 0xD9, 0x1F, 0x93, 0x53, 0xBE, 0xDB,
	0xC9, 0xB8, 0x3E, 0x9B, 0x1C, 0xB3, 0x30, 0xC9,
	0x18, 0x0C, 0x4E, 0x74, 0xE2, 0x70, 0xE6, 0x03,
	0x50, 0xFA, 0x64, 0xCB, 0xAD, 0xEF, 0x1C, 0x3A,
	0xE7, 0xF6, 0xE7, 0x21, 0x0E, 0x8B, 0xB2, 0x26,
	0x97, 0x16, 0x90, 0x0C, 0x4C, 0xB4, 0x64, 0x80,
	0xA8, 0xEA, 0xAB, 0x60, 0x85, 0x5C, 0xEC, 0xBE,
	0x88, 0xE3, 0x38, 0x72, 0x45, 0x33, 0x29, 0xA3,
	0x21, 0x28, 0x0B, 0x10, 0x67, 0x7C, 0x65, 0x98,
	0x64, 0x64, 0xC9, 0x82, 0xEB, 0x8A, 0x17, 0x92,
	0x72, 0x81, 0x93, 0x3B, 0xAA, 0xE9, 0x11, 0x44,
	0xD5, 0xBF, 0x16, 0xFE, 0x24, 0x36, 0xC1, 0xFF,
	0xB2, 0x2C, 0x43, 0xCA, 0xC9, 0xDA, 0x69, 0x16,
	0x78, 0x2A, 0xCD, 0x4A, 0xB2, 0x03, 0xAD, 0x44,
	0x0E, 0x79, 0x5C, 0x47, 0x0F, 0xF3, 0xE2, 0x22,
	0x76, 0xDF, 0xCD, 0x9D, 0xB3, 0x8B, 0x2F, 0x4E,
	0xEC, 0x9F, 0xB5, 0xA1, 0xD8, 0x14, 0xE5, 0x2E,
	0x73, 0x1A, 0xDF, 0x63, 0xDA, 0x1E, 0x62, 0xB3,
	0x49, 0x37, 0x31, 0x87, 0x83, 0x36, 0xD0, 0x64,
	0x40, 0xA4, 0x15, 0x28, 0x02, 0x55, 0x31, 0x4A,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xB4, 0x19, 0x00,
	0x00, 0x08, 0x53, 0x45, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x52, 0x65, 0x76, 0x20, 0x36, 0x2E,
	0x34, 0x32, 0x39, 0x39, 0x30, 0x33, 0x31, 0x36,
	0x00, 0xB4, 0x19, 0x00, 0x00, 0x08, 0x53, 0x45,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x52, 0x65,
	0x00, 0x15, 0x00, 0x64, 0x00, 0x40, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x40,
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x40, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00,
	0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x40,
	0x40, 0x40, 0x40, 0x00, 0x00, 0x15, 0x00, 0x0E,
	0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x96, 0x00, 0x00, 0x00, 0x15, 0x00, 0x18,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30,
	0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
	0x30, 0x30, 0x00, 0x00, 0x00, 0x15, 0x00, 0x18,
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
	0x30, 0x00, 0x00, 0x00, 0x01, 0x20, 0x01, 0x01,
	0x01, 0x00, 0x00, 0x96, 0x00, 0x00, 0x01, 0x00,
	0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F,
	0x00, 0x00, 0x80, 0x3F, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0xBF,
	0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
	0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x09, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00,
	0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
	0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
	0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
	0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#endif