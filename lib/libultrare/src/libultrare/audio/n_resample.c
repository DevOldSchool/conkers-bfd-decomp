#include "n_audio_partial.h"
#include "n_audio_commands.h"

/* Conker US 0x22460:0x226B0: resampler pull. The following 64 zero
 * bytes remain outside this compiled object. */
extern Acmd *n_alAdpcmPull(ConkerNAudioPVoice *, s16 *, s32, Acmd *);

Acmd *n_alResamplePull(ConkerNAudioPVoice *e, s16 *outp, Acmd *p)
{
	Acmd *ptr = p;
	s16 inp;
	s32 inCount;
	s32	incr;
	f32 finCount;

	inp = 368;

	/*
	 * check if resampler is required
	 */
	if (e->rs_upitch) {
		ptr = n_alAdpcmPull(e, &inp, 184, p);
		aDMEMMove(ptr++, inp, *outp , 184 << 1);
	} else {
		/*
		 * clip to maximum allowable pitch
		 * FIXME: should we check for some minimum as well?
		 */
		if (e->rs_ratio > MAX_RATIO) {
			e->rs_ratio = MAX_RATIO;
		}

		/*
		 * quantize the pitch
		 */
		e->rs_ratio = (s32)(e->rs_ratio * UNITY_PITCH);
		e->rs_ratio = e->rs_ratio / UNITY_PITCH;

		/*
		 * determine how many samples to generate
		 */
		finCount = e->rs_delta + (e->rs_ratio * (f32)184);
		inCount = (s32) finCount;
		e->rs_delta = finCount - (f32)inCount;

		/*
		 * ask all filters upstream from us to build their command
		 * lists.
		 */
		ptr = n_alAdpcmPull(e, &inp, inCount, p);

		/*
		 * construct our portion of the command list
		 */
		incr = (s32)(e->rs_ratio * UNITY_PITCH);
		CONKER_AUDIO_RESAMPLE(ptr++, osVirtualToPhysical(e->rs_state), e->rs_first, incr, inp, 0);
		e->rs_first = 0;
	}

	return ptr;
}

