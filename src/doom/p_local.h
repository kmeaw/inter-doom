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
//	Play functions, animation, global header.
//


#pragma once

#include <SDL.h>
#include "r_local.h"


#define TOCENTER        -8
#define FLOATSPEED		(FRACUNIT*4)


#define MAXHEALTH		100
#define VIEWHEIGHT		(41*FRACUNIT)

// mapblocks are used to check movement
// against lines and things
#define MAPBLOCKUNITS	128
#define MAPBLOCKSIZE	(MAPBLOCKUNITS*FRACUNIT)
#define MAPBLOCKSHIFT	(FRACBITS+7)
#define MAPBMASK		(MAPBLOCKSIZE-1)
#define MAPBTOFRAC		(MAPBLOCKSHIFT-FRACBITS)


// player radius for movement checking
#define PLAYERRADIUS	16*FRACUNIT

// MAXRADIUS is for precalculated sector block boxes
// the spider demon is larger,
// but we do not have any moving sectors nearby
#define MAXRADIUS		32*FRACUNIT

#define GRAVITY		FRACUNIT
#define MAXMOVE		(30*FRACUNIT)

#define USERANGE		(64*FRACUNIT)
#define MELEERANGE		(64*FRACUNIT)
#define MISSILERANGE	(32*64*FRACUNIT)

// follow a player exlusively for 3 seconds
#define	BASETHRESHOLD	 	100



//
// P_TICK
//

// Both the head and tail of the thinker list.
extern thinker_t thinkercap;	

void P_Ticker (void);
void P_InitThinkers (void);
void P_AddThinker (thinker_t* thinker);
void P_RemoveThinker (thinker_t* thinker);


//
// P_PSPR
//
void P_SetupPsprites (player_t* player);
void P_MovePsprites (player_t* player);
void P_DropWeapon (player_t* player);


//
// P_USER
//
#define MLOOKUNIT	8
void	P_CalcHeight (player_t *player, boolean safe);
void	P_PlayerThink (player_t* player);


//
// P_MOBJ
//
#define ONFLOORZ		INT_MIN
#define ONCEILINGZ		INT_MAX

// Time interval for item respawning.
#define ITEMQUESIZE		128

extern mapthing_t	itemrespawnque[ITEMQUESIZE];
extern int		itemrespawntime[ITEMQUESIZE];
extern int		iquehead;
extern int		iquetail;


void P_RespawnSpecials (void);

mobj_t*
P_SpawnMobj
( fixed_t	x,
  fixed_t	y,
  fixed_t	z,
  mobjtype_t	type );

void 	P_RemoveMobj (mobj_t* th);
mobj_t* P_SubstNullMobj (mobj_t* th);
boolean	P_SetMobjState (mobj_t* mobj, statenum_t state);
void 	P_MobjThinker (mobj_t* mobj);

void	P_SpawnPuff (fixed_t x, fixed_t y, fixed_t z);

void 	P_SpawnColoredBlood (fixed_t x, fixed_t y, fixed_t z, int damage, mobj_t* target);
void 	P_SpawnBlood (fixed_t x, fixed_t y, fixed_t z, int damage, mobj_t* target);
mobj_t* P_SpawnMissile (mobj_t* source, mobj_t* dest, mobjtype_t type);
void	P_SpawnPlayerMissile (mobj_t* source, mobjtype_t type);

void	P_SpawnPuffSafe (fixed_t x, fixed_t y, fixed_t z, boolean safe); 

//
// P_ENEMY
//
void P_NoiseAlert (mobj_t* target, mobj_t* emmiter);


//
// P_MAPUTL
//
typedef struct
{
    fixed_t	x;
    fixed_t	y;
    fixed_t	dx;
    fixed_t	dy;
    
} divline_t;

typedef struct
{
    fixed_t	frac;		// along trace line
    boolean	isaline;
    union {
	mobj_t*	thing;
	line_t*	line;
    }			d;
} intercept_t;

// Extended MAXINTERCEPTS, to allow for intercepts overrun emulation.

#define MAXINTERCEPTS_ORIGINAL 128*16 // [JN] Лимит шестнадцатикратно умножен
#define MAXINTERCEPTS          (MAXINTERCEPTS_ORIGINAL + 61)

extern intercept_t	intercepts[MAXINTERCEPTS];
extern intercept_t*	intercept_p;

typedef boolean (*traverser_t) (intercept_t *in);

fixed_t P_AproxDistance (fixed_t dx, fixed_t dy);
fixed_t P_ApproxDistanceZ(fixed_t dx, fixed_t dy, fixed_t dz);
int 	P_PointOnLineSide (fixed_t x, fixed_t y, const line_t *line);
int 	P_PointOnDivlineSide (fixed_t x, fixed_t y, const divline_t *line);
void 	P_MakeDivline (line_t* li, divline_t* dl);
fixed_t P_InterceptVector (divline_t* v2, divline_t* v1);
int 	P_BoxOnLineSide (const fixed_t *tmbox, const line_t *ld);

extern fixed_t		opentop;
extern fixed_t 		openbottom;
extern fixed_t		openrange;
extern fixed_t		lowfloor;

void 	P_LineOpening (line_t* linedef);

boolean P_BlockLinesIterator (int x, int y, boolean(*func)(line_t*) );
boolean P_BlockThingsIterator (int x, int y, boolean(*func)(mobj_t*));
boolean PIT_RadiusAttack (mobj_t* thing);
boolean PIT_ChangeSector (mobj_t* thing);

#define PT_ADDLINES		1
#define PT_ADDTHINGS	2

extern divline_t	trace;

boolean
P_PathTraverse
( fixed_t	x1,
  fixed_t	y1,
  int64_t	x2,
  int64_t	y2,
  int		flags,
  boolean	(*trav) (intercept_t *));

void P_UnsetThingPosition (mobj_t* thing);
void P_SetThingPosition (mobj_t* thing);


//
// P_MAP
//

// If "floatok" true, move would be ok
// if within "tmfloorz - tmceilingz".
extern boolean		floatok;
extern fixed_t		tmfloorz;
extern fixed_t		tmceilingz;
extern mobj_t		*BlockingMobj;


extern	line_t*		ceilingline;

// fraggle: I have increased the size of this buffer.  In the original Doom,
// overrunning past this limit caused other bits of memory to be overwritten,
// affecting demo playback.  However, in doing so, the limit was still
// exceeded.  So we have to support more than 8 specials.
//
// We keep the original limit, to detect what variables in memory were
// overwritten (see SpechitOverrun())

#define MAXSPECIALCROSS 		20
#define MAXSPECIALCROSS_ORIGINAL	8

extern	line_t*	spechit[MAXSPECIALCROSS];
extern	int	numspechit;

boolean P_CheckPosition (mobj_t *thing, fixed_t x, fixed_t y);
boolean P_TryMove (mobj_t* thing, fixed_t x, fixed_t y);
boolean P_CheckLineSide(mobj_t *actor, fixed_t x, fixed_t y);
boolean P_TeleportMove (mobj_t* thing, fixed_t x, fixed_t y);
void	P_SlideMove (mobj_t* mo);
boolean P_CheckSight (mobj_t* t1, mobj_t* t2);
boolean PTR_NoWayAudible (line_t *line);
void 	P_UseLines (player_t* player);

boolean P_ChangeSector (sector_t* sector, boolean crunch);

extern mobj_t*	linetarget;	// who got hit (or NULL)

fixed_t
P_AimLineAttack
( mobj_t*	t1,
  angle_t	angle,
  fixed_t	distance );

void
P_LineAttack
( mobj_t*	t1,
  angle_t	angle,
  int64_t	distance,
  fixed_t	slope,
  int		damage );

void
P_RadiusAttack
( mobj_t*	spot,
  mobj_t*	source,
  int		damage );

void P_ApplyTorque(mobj_t *mo);     // killough 9/12/98


//
// P_SETUP
//
extern byte*		rejectmatrix;	// for fast sight rejection
extern int32_t*		blockmaplump;	// offsets in blockmap are from here // [crispy] BLOCKMAP limit
extern int32_t*		blockmap; // [crispy] BLOCKMAP limit
extern int		bmapwidth;
extern int		bmapheight;	// in mapblocks
extern fixed_t		bmaporgx;
extern fixed_t		bmaporgy;	// origin of block map
extern mobj_t**		blocklinks;	// for thing chains

// NOT called by W_Ticker. Fixme.
void P_SetupLevel (int episode, int map, int playermask, skill_t skill);

// Called by startup code.
void P_Init (void);


// [crispy] blinking key or skull in the status bar
#define KEYBLINKMASK 0x8
#define KEYBLINKTICS (7*KEYBLINKMASK)
extern int st_keyorskull[3];


//
// P_INTER
//

void P_SetMessage (player_t *player, char *message, MessageType_t messageType, boolean ultmsg);
extern boolean ultimatemsg;

extern int		maxammo[NUMAMMO];
extern int		clipammo[NUMAMMO];

boolean P_GivePower (player_t *player, int power);

void
P_TouchSpecialThing
( mobj_t*	special,
  mobj_t*	toucher );

void
P_DamageMobj
( mobj_t*	target,
  mobj_t*	inflictor,
  mobj_t*	source,
  int		damage );


//
// P_SPEC
//
#include "p_spec.h"
