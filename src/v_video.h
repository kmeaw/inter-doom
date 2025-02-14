//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005-2014 Simon Howard
// Copyright(C) 2016-2022 Julian Nechaevsky
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	Gamma correction LUT.
//	Functions to draw patches (by post) directly to screen.
//	Functions to blit a block to the screen.
//


#pragma once

#include "doomtype.h"

// Needed because we are refering to patches.
#include "v_patch.h"


//
// VIDEO
//

#define CENTERY			(SCREENHEIGHT/2)


extern int dirtybox[4];

extern byte *tinttable;
extern byte *extratinttable;
extern byte *transtable90;
extern byte *transtable80;
extern byte *transtable70;
extern byte *transtable60;
extern byte *transtable50;
extern byte *transtable40;
extern byte *transtable30;
extern byte *transtable20;
extern byte *transtable10;

extern byte *dp_translation;

// haleyjd 08/28/10: implemented for Strife support
// haleyjd 08/28/10: Patch clipping callback, implemented to support Choco
// Strife.
typedef boolean (*vpatchclipfunc_t)(patch_t *, int, int);
void V_SetPatchClipCallback(vpatchclipfunc_t func);


// Allocates buffer screens, call before R_Init.
void V_Init (void);

// Draw a block from the specified source screen to the screen.

void V_CopyRect(int srcx, int srcy, byte *source,
                int width, int height,
                int destx, int desty);

void V_DrawPatch(int x, int y, patch_t *patch, byte *table);
void V_DrawPatchFullScreen(patch_t *patch, boolean flipped);
void V_DrawPatchFlipped(int x, int y, patch_t *patch);
void V_DrawTLPatch(int x, int y, patch_t *patch);
void V_DrawAltTLPatch(int x, int y, patch_t * patch);
void V_DrawFadePatch(int x, int y, patch_t * patch, byte *table);
void V_DrawShadowedPatch(int x, int y, patch_t *patch);
void V_DrawShadowedPatchDoom(int x, int y, patch_t *patch);
void V_DrawShadowedPatchRaven(int x, int y, patch_t *patch);
void V_DrawShadowedPatchStrife(int x, int y, patch_t *patch);
void V_DrawXlaPatch(int x, int y, patch_t * patch);     // villsa [STRIFE]
void V_DrawPatchUnscaled(int x, int y, patch_t *patch, byte *table);
void V_DrawPatchFinale(int x, int y, patch_t *patch);
void V_FillFlat (char *lump);

// Draw a linear block of pixels into the view buffer.

void V_DrawBlock(int x, int y, int width, int height, byte *src);
void V_DrawScaledBlock(int x, int y, int width, int height, byte *src);

void V_MarkRect(int x, int y, int width, int height);

void V_DrawFilledBox(int x, int y, int w, int h, int c);
void V_DrawHorizLine(int x, int y, int w, int c);
void V_DrawVertLine(int x, int y, int h, int c);
void V_DrawBox(int x, int y, int w, int h, int c);
void V_CopyScaledBuffer(byte *dest, byte *src, size_t size);

// Draw a raw screen lump

void V_DrawRawScreen(byte *raw);

// Temporarily switch to using a different buffer to draw graphics, etc.

void V_UseBuffer(byte *buffer);

// Return to using the normal screen buffer to draw graphics.

void V_RestoreBuffer(void);

// Save a screenshot of the current screen to a file, named in the 
// format described in the string passed to the function, eg.
// "DOOM%02i.pcx"

void V_ScreenShot(char *format);

// [JN] Load the lookup table for shadowed text from the TINTMAP lump.

void V_LoadTintMap(void);

// Load the lookup table for translucency calculations from the TINTTAB
// lump.

void V_LoadTintTable(void);

// villsa [STRIFE]
// Load the lookup table for translucency calculations from the XLATAB
// lump.

void V_LoadXlaTable(void);

void V_DrawMouseSpeedBox(int speed);
