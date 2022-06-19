// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// DESCRIPTION:
//	Fixed point arithemtics, implementation.
//
//-----------------------------------------------------------------------------


#ifndef __M_FIXED__
#define __M_FIXED__


#ifdef __GNUG__
#pragma interface
#endif


//
// Fixed point, 32bit as 16.16.
//
#define FRACBITS		16
#define FRACUNIT		(1<<FRACBITS)

typedef int fixed_t;


//extern fixed_t _finesine(fixed_t a);
//extern fixed_t _finecosine(fixed_t a);

//fixed_t FixedMul	(fixed_t a, fixed_t b);
//fixed_t FixedMul	(fixed_t a, fixed_t b);
//fixed_t FixedDiv	(fixed_t a, fixed_t b);
//fixed_t FixedDiv2	(fixed_t a, fixed_t b);
#define FixedMul(a,b) (fixed_t)((float)(a) * (float)(b) * 0.0000152587890625f)
#define FixedDiv(a,b) (fixed_t)((float)(a) / (float)(b) * FRACUNIT)
#define FixedDiv2(a,b) FixedDiv(a,b)



#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
