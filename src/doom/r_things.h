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
//	Rendering of moving objects, sprites.
//


#pragma once


// Constant arrays used for psprite clipping and initializing clipping.
extern int *negonearray;       // [JN] killough 2/8/98: // dropoff overflow
extern int *screenheightarray; //      change to MAX_*  // dropoff overflow

// vars for R_DrawMaskedColumn
extern int     *mfloorclip;
extern int     *mceilingclip;
extern fixed_t  spryscale;
extern int64_t  sprtopscreen; // [crispy] WiggleFix

extern fixed_t  pspritescale;
extern fixed_t  pspriteiscale;


void R_InitSpritesRes (void);
void R_DrawMaskedColumn (const column_t *column);
void R_AddSprites (const sector_t *sec);
void R_AddPSprites (void);
void R_DrawSprites (void);
void R_InitSprites (char** namelist);
void R_ClearSprites (void);
void R_DrawMasked (void);
void R_ClipVisSprite (vissprite_t *vis, int xl, int xh);
