#include "n_audio_partial.h"

/* Conker US 0x17870:0x17A80: output mode and per-bus surround routing.
 * Source-family BSS groups the output flags, routing and saved bus modes.
 */
void alSurround_ReverbSetup(s32 index, s32 mode);

typedef struct { u8 surround, mono, headphone, pad03; } ConkerAudioOutput;
ConkerAudioOutput __conker_audio_output;
u8 __conker_bus_route[2];
u8 __conker_bus_invert[2];
u8 __conker_bus_modes[4];

void alSurround_OutputType(u8 mode)
{
	s32 i;

	__conker_audio_output.surround = 0;
	__conker_audio_output.mono = 0;
	__conker_audio_output.headphone = 0;

	switch (mode) {
	case 1:
		__conker_audio_output.mono = 1;
		break;
	case 3:
		__conker_audio_output.headphone = 1;
		break;
	case 4:
		__conker_audio_output.surround = 1;
		break;
	}

	for (i = 0; i < 2; i++) {
		alSurround_ReverbSetup(i, 0);
	}
}

void alSurround_ReverbSetup(s32 index, s32 arg1)
{
	if (arg1 == 0) {
		arg1 = __conker_bus_modes[index];
	}

	__conker_bus_route[index] = 0;
	__conker_bus_invert[index] = 0;

	switch (arg1) {
	case 2:
		if (__conker_audio_output.surround) {
			__conker_bus_invert[index] = 1;
		}
		break;
	case 3:
		if (__conker_audio_output.surround) {
			__conker_bus_route[index] = 1;
		}
		break;
	case 4:
		if (!__conker_audio_output.mono) {
			__conker_bus_route[index] = 1;
		}
		break;
	case 5:
		if (!__conker_audio_output.mono) {
			__conker_bus_route[index] = 1;
			__conker_bus_invert[index] = 1;
		}
		break;
	}

	__conker_bus_modes[index] = arg1;
}
