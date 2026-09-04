/**************************************************************************
 *									  *
 *		 Copyright (C) 1994, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

#include <PR/ultratypes.h>

/* Conker's single-precision form of the SDK polynomial approximation.
 * Constants are the exact IEEE-754 values read through the retail relocations.
 */
typedef union { u32 i; f32 f; } fu;
extern f32 __libm_qnan_f;
#define ABS(d) ((d) > 0 ? (d) : -(d))
#define ROUND(d) (int)(((d) >= 0.0f) ? ((d) + 0.5f) : ((d) - 0.5f))

/* ====================================================================
 * ====================================================================
 *
 * Module: fcos.c
 * $Revision: 1.3 $
 * $Date: 1998/10/09 06:10:53 $
 * $Author: has $
 * $Source: /exdisk2/cvs/N64OS/Master/cvsmdev2/PR/libultra/monegi/gu/cosf.c,v $
 *
 * Revision history:
 *  09-Jun-93 - Original Version
 *
 * Description:	source code for fcos function
 *
 * ====================================================================
 * ====================================================================
 */


/* coefficients for polynomial approximation of cos on +/- pi/2 */

static const fu P[] = {
    {0x3f800000}, {0xbe2aaaa6}, {0x3c088769}, {0xb94fb7fd}, {0x362edefa}
};
static fu rpi = {0x3ea2f984};
static fu pihi = {0x40490fdc};
static fu pilo = {0x330885a3};
static fu zero = {0x00000000};



/* ====================================================================
 *
 * FunctionName		fcos
 *
 * Description		computes cosine of arg
 *
 * ====================================================================
 */

float
__conker_game_cosf( float x )
{
float	absx;
float	dx, xsq, poly;
float	dn;
int	n;
float	result;
int	ix, xpt;


	ix = *(int *)&x;
	xpt = (ix >> 22);
	xpt &= 0x1ff;

	/* xpt is exponent(x) + 1 bit of mantissa */


	if ( xpt < 0x136 )
	{
		/* |x| < 2^28 */

		/* use the standard algorithm from Cody and Waite, doing
		   the computations in float precision
		*/

		absx = ABS(x);

		dx = absx;

		dn = dx*rpi.f + 0.5f;
		n = ROUND(dn);
		dn = n;

		dn -= 0.5f;

		dx = dx - dn*pihi.f;
		dx = dx - dn*pilo.f;	/* dx = x - (n - 0.5f)*pi */

		xsq = dx*dx;

		poly = ((P[4].f*xsq + P[3].f)*xsq + P[2].f)*xsq + P[1].f;

		result = dx + (dx*xsq)*poly;

		/* negate result if n is odd */

		if ( (n & 1) == 0 )
			return ( (float)result );

		return ( -(float)result );
	}

	if ( x != x )
	{
		/* x is a NaN; return a quiet NaN */

#ifdef _IP_NAN_SETS_ERRNO

		*__errnoaddr = EDOM;
#endif

		return ( __libm_qnan_f );
	}

	/* just give up and return 0.0 */

	return ( zero.f );
}
