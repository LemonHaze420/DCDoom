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
// $Log:$
//
// DESCRIPTION:
//	Fixed point implementation.
//
//-----------------------------------------------------------------------------


static const char
rcsid[] = "$Id: m_bbox.c,v 1.1 1997/02/03 22:45:10 b1 Exp $";

#include "stdlib.h"

#include "doomtype.h"
#include "i_system.h"

#ifdef __GNUG__
#pragma implementation "m_fixed.h"
#endif
#include "m_fixed.h"

/*
__inline fixed_t  _finesine(a)
{
    float   s, c;
    __fsca(&s, &c, a<<3);
    return (fixed_t)(s * 65336.f);
}

__inline fixed_t  _finecosine(a)
{
    float   s, c;
    __fsca(&s, &c, a<<3);
    return (fixed_t)(c * 65336.f);
}
*/
//__USE_C_FIXED__ or something.
/*
fixed_t FixedMul( fixed_t a, fixed_t b )
   {
    return (((__int64) a * (__int64) b) >> FRACBITS);
   }
*/


//
// FixedDiv, C version.
//
#if 0
fixed_t
FixedDiv
( /*fixed_t*/float	a,
  /*fixed_t*/float	b )
{
    if ( (abs(a)>>14) >= abs(b))
	return (a^b)<0 ? MININT : MAXINT;
    return FixedDiv2 (a,b);
}



fixed_t
FixedDiv2
( /*fixed_t*/float	a,
  /*fixed_t*/float	b )
{
#if 0
    long long c;
    c = ((long long)a<<16) / ((long long)b);
    return (fixed_t) c;
#endif

    float c;

    c = ((float)a) / ((float)b) * FRACUNIT;

    if (c >= 2147483648.0f ) c = 2147483648.0f; else if( c < -2147483648.0) c = -2147483648.0;
	//I_Error("FixedDiv: divide by zero");
    return (fixed_t) c;
}
#endif
