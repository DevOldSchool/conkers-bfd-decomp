#include "n_audio_partial.h"
#include "n_audio_commands.h"

/* Conker US 0x22040:0x22460: per-voice scaling and low-pass filtering.
 * The coefficient prefix has the same layout as the output-bus filter.
 */
extern f32 sqrtf(f32);
extern Acmd *n_alResamplePull(ConkerNAudioPVoice *, s16 *, Acmd *);
extern s32 n_alLoadParam(ConkerNAudioPVoice *, s32, void *);
extern void n_alFxInitlpfilter_mono(ConkerNAudioOutputLP *, f32);

Acmd *n_alLPFilterPull(ConkerNAudioPVoice *e, s16 *outp, s32 outCount, Acmd *p)
{
	Acmd *ptr = p;
	f32 sp28;

	ptr = n_alResamplePull(e, outp, p);

	if (e->flags99 != 0 && e->flags99 < 64) {
		if (e->flags99 >= 6) {
			sp28 = 26755 / sqrtf(e->flags99 + 1.0f);
		} else {
			sp28 = 65536 / (e->flags99 + 1.0f);
		}

		if (sp28 < 7723) {
			sp28 = 7723;
		}

		CONKER_AUDIO_SCALE(ptr++, *outp, sp28, e->flags99 + 1);
	}

	if (e->fx.amount > 0) {
		if (e->filterState != 0) {
			n_alFxInitlpfilter_mono((ConkerNAudioOutputLP *)&e->fx, 22050);
		}

		aLoadADPCM(ptr++, 32, osVirtualToPhysical(e->fx.coefficients));

		if (e->filterState == 2) {
			e->filterState = 0;
		}

		CONKER_AUDIO_POLE_FILTER(ptr++, e->filterState, *outp, 0, osVirtualToPhysical(e->filterBuffer) & 0xffffff);

		e->filterState = 0;
	}

	return ptr;
}

s32 n_alLPFilterParam(ConkerNAudioPVoice *filter, s32 paramID, void *param)
{
	f32 *f = (f32 *) &param;

	switch (paramID) {
	case (4):
		filter->fx.amount = 0;
		n_alLoadParam(filter, 4, param);
		break;
	case (18):
		filter->fx.amount = (s32) param;
		filter->filterState |= 2;
		break;
	case (19):
		filter->fx.frequency = *f;
		filter->filterState |= 2;
		break;
	case (17):
		filter->flags99 = (u8)param;
		break;
	default:
		n_alLoadParam(filter, paramID, param);
		break;
	}

	return 0;
}
