#include <PR/ultratypes.h>

/* Conker US Rare math library; independently identified in the MP3 source
 * family. Complete object text and constants are compared with the ROM.
 */

f32 fabsf(f32 value);

#ifdef __sgi
#pragma intrinsic (fabsf)
#else
#define fabsf(f) __builtin_fabsf((f32)(f))
#endif

f32 __conker_game_expf(f32 arg0)
{
	f32 sp1c;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 sp0c;
	s32 sp08;
	s32 sp04;

	sp0c = fabsf(arg0);

	if (sp0c < 0.00000011920929f) {
		return 1;
	}

	sp04 = (s32) (sp0c / 0.6931471824646f);

	if (sp04 > 1024) {
		if (arg0 >= 0) {
			return 3.4028234663852886e+38f;
		} else {
			return 0;
		}
	}

	sp10 = sp0c - sp04 * 0.6931471824646f;
	sp08 = 1;
	sp1c = 1;
	sp18 = 1;

	do {
		sp14 = sp1c;
		sp18 *= sp10 / sp08;
		sp1c += sp18;
		sp08++;
	} while (sp1c != sp14);

	while (sp04) {
		sp1c += sp1c;
		sp04--;
	}

	if (arg0 >= 0) {
		return sp1c;
	} else {
		return 1 / sp1c;
	}
}
