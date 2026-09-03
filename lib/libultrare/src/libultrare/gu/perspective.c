
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

/* Conker's two-angle perspective variant; the second angle replaces aspect.
 * Calls retain the game-engine matrix and trigonometric helper bindings.
 */
extern float __conker_game_sinf(float);
extern float __conker_game_cosf(float);
extern void __conker_game_guMtxIdentF(float mf[4][4]);
extern void __conker_game_guMtxF2L(float mf[4][4], Mtx *m);
typedef float Matrix[4][4];

void guPerspectiveF(float mf[4][4], u16 *perspNorm, float fovy, float fovx, float near, float far, float scale)
{
	float	cot;
	int	i, j;

	__conker_game_guMtxIdentF(mf);

	fovx *= 3.1415926f / 360.0f;
	mf[0][0] = __conker_game_cosf(fovx) / __conker_game_sinf(fovx);
	fovy *= 3.1415926f / 360.0f;
	mf[1][1] = __conker_game_cosf(fovy) / __conker_game_sinf(fovy);
	mf[2][2] = (near + far) / (near - far);
	mf[2][3] = -1;
	mf[3][2] = (2.0f * near * far) / (near - far);
	mf[3][3] = 0;

	for (i=0; i<4; i++)
	    for (j=0; j<4; j++)
		mf[i][j] *= scale;

	if (perspNorm != (u16 *) NULL) {
	    if (near+far<=2.0f) {
		*perspNorm = (u16) 0xFFFF;
	    } else  {
		*perspNorm = (u16) ((2.0f*65536.0f)/(near+far));
		if (*perspNorm<=0)
		    *perspNorm = (u16) 0x0001;
	    }
	}
}

void guPerspective(Mtx *m, u16 *perspNorm, float fovy, float fovx, float near, float far, float scale)
{
	Matrix	mf;

	guPerspectiveF(mf, perspNorm, fovy, fovx, near, far, scale);

	__conker_game_guMtxF2L(mf, m);
}


