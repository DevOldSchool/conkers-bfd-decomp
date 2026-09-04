#include "types.h"

/* Unmatched Conker US Rare power-helper candidate, overlay 0x4A400:0x4A5E0.
 * The canonical range remains raw ASM. Bounded source and compiler-mode
 * trials did not reproduce its register allocation; see the Rare math note.
 */
#if 0
/* Conker US Rare math library; independently identified in the MP3 source
 * family. Complete object text and constants are compared with the ROM.
 */
f32 __conker_game_expf(f32);
f32 __conker_game_logf(f32);

f32 __conker_game_powf(f32 arg0, f32 arg1)
{
	s32 arg1int = arg1;
	f32 sp30;
	register s32 s0;

	if (arg0 != 0 && arg1 == 0) {
		return 1.0f;
	}

	if (arg0 == 0) {
		return 0.0f;
	}

	if ((arg0 == 0 && arg1 == 0) || (arg0 < 0 && arg1int != arg1)) {
		return 0.0f;
	}

	if (arg1int != arg1) {
		arg0 = __conker_game_expf(__conker_game_logf(arg0) * arg1);
	} else if (arg1 > 0) {
		arg1--;
		sp30 = arg0;

		for (s0 = (arg1-- != 0); s0; s0 = (arg1-- != 0)) {
			arg0 *= sp30;
		}
	} else {
		sp30 = 1;

		for (s0 = (arg1++ != 0); s0; s0 = (arg1++ != 0)) {
			sp30 /= arg0;
		}

		arg0 = sp30;
	}

	return arg0;
}

#endif
