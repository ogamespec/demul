/*
 * Demul
 * Copyright (C) 2006 Org, Demul Team
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

#ifndef __DISASM_H__
#define __DISASM_H__

char*   Disasm(u32 pc, u16 op);
u16 disMaskOpcode(u16 code);

#endif