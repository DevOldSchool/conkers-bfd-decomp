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

#include <PR/gu.h>


/* Conker US game rotation copy, 0x48190:0x48360.
 * Its matrix helpers belong to the game engine, distinct from the SDK tail.
 * Evidence: docs/evidence/game_sdk_rotation_variant.md.
 */
extern float __conker_game_sinf(float);
extern float __conker_game_cosf(float);
extern void __conker_game_guMtxIdentF(float mf[4][4]);
extern void __conker_game_guMtxF2L(float mf[4][4], Mtx *m);

typedef float Matrix[4][4];

void guRotateF(float mf[4][4], float a, float x, float y, float z)
{
	static float	dtor = 3.1415926 / 180.0;
	float	sine;
	float	cosine;
	float	ab, bc, ca, t;

	guNormalize(&x, &y, &z);
	a *= dtor;
	sine = __conker_game_sinf(a);
	cosine = __conker_game_cosf(a);
	t = (1-cosine);
	ab = x*y*t;
	bc = y*z*t;
	ca = z*x*t;

	__conker_game_guMtxIdentF(mf);

    #define xxsine (x * sine)
    #define yxsine (y * sine)
    #define zxsine (z * sine)


	t = x*x;
	mf[0][0] = t+cosine*(1-t);
	mf[2][1] = bc-xxsine;
	mf[1][2] = bc+xxsine;

	t = y*y;
	mf[1][1] = t+cosine*(1-t);
	mf[2][0] = ca+yxsine;
	mf[0][2] = ca-yxsine;

	t = z*z;
	mf[2][2] = t+cosine*(1-t);
	mf[1][0] = ab-zxsine;
	mf[0][1] = ab+zxsine;
}

void guRotate(Mtx *m, float a, float x, float y, float z)
{
	Matrix	mf;

	guRotateF(mf, a, x, y, z);

	__conker_game_guMtxF2L(mf, m);
}
