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
//  Refresh module, data I/O, caching, retrieval of graphics
//  by name.
//


#pragma once

#include "r_defs.h"
#include "r_state.h"


#define LOOKDIRMIN	110 // [crispy] -110, actually
#define LOOKDIRMAX	90
#define LOOKDIRS	(LOOKDIRMIN+1+LOOKDIRMAX) // [crispy] lookdir range: -110..0..90


// Retrieve column data for span blitting.
const byte *R_GetColumn (const int tex, int col);

// [crispy] wrapping column getter function for composited
// translucent mid-textures on 1S walls
const byte *R_GetColumnMod (const int tex, int col);

// I/O, setting up the stuff.
void R_InitData (void);
void R_PrecacheLevel (void);

// Retrieval.
// Floor/ceiling opaque texture tiles, lookup by name. For animation?
int R_FlatNumForName (char *name);

// Called by P_Ticker for switches and animations,
// returns the texture number for the texture name.
int R_TextureNumForName (char *name);
int R_CheckTextureNumForName (char *name);
