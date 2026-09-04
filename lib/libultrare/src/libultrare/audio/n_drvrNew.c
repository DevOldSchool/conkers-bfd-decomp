#include "n_audio_driver.h"

/* Conker US 0x1CBF0:0x1D900. Driver-family reconstruction from the pinned
 * Rare source lineage, using the retail float ABI and physical-voice layout.
 * Default effect parameters remain external until their full extent is proven.
 */
#define SCALE 16384.0f
extern f32 __conker_game_atan2f(f32, f32);
extern s32 __conker_default_fx_params[];

#define M_PI    3.141592741f

void __conker_audio_coefficients(f32 outputrate, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4)
{
	f32 sp24;
	f32 sp20;
	f32 sp1c;

	if (arg1 >= outputrate - 200) {
		arg1 = outputrate - 200;
	}

	sp24 = __conker_game_atan2f(arg1 * M_PI, outputrate);
	sp20 = sp24 * sp24;
	sp1c = (sp24 * 1.4142136573792f) / arg2;

	arg3[0] = sp20 / (1 + sp20 + sp1c);
	arg3[1] = arg3[0] * 2;
	arg3[2] = arg3[0];

	arg4[1] = ((sp20 - 1) * 2) / (1 + sp20 + sp1c);
	arg4[2] = ((1 + sp20) - sp1c) / (1 + sp20 + sp1c);
}

void n_alFxInitlpfilter(ConkerNAudioLowPass *lp)
{
	s32 i, temp;
	s16 fc;
	f32 ffc, fcoef;
	f32 scale;

	temp = lp->fc * SCALE;
	fc = temp >> 15;
	lp->fgain = SCALE - fc;

	lp->first = 0;

	for (i = 0; i < 8; i++) {
		lp->fcvec.fccoef[i] = 0;
	}

	lp->fcvec.fccoef[i++] = fc;
	scale = SCALE;
	fcoef = ffc = fc / scale;

	for (; i < 16; i++) {
		fcoef *= ffc;
		lp->fcvec.fccoef[i] = (s16)(fcoef * scale);
	}
}

f32 alSemitones2Ratio(s32 arg0)
{
	f32 mult;
	f32 value;

	value = 1.0f;

	if (arg0 >= 0) {
		mult = 1.0594631433487f;
	} else {
		mult = 0.94387429952621f;
		arg0 = -arg0;
	}

	while (arg0) {
		if (arg0 & 1) {
			value *= mult;
		}

		mult *= mult;
		arg0 >>= 1;
	}

	return value;
}

void n_alFxInitlpfilter_mono(ConkerNAudioOutputLP *fx, f32 outputrate)
{
	s32 i;
	f32 sp30[3];
	f32 sp24[3];

	if (fx->amount == 0) {
		return;
	}

	if (fx->amount < 10) {
		fx->amount = 10;
	}

	__conker_audio_coefficients(outputrate, fx->frequency + 10.0f, fx->amount / 10.0f, sp30, sp24);

	for (i = 3; i < 8; i++) {
		fx->coefficients[i] = 0;
	}

	fx->coefficients[0] = sp30[0] * (26768 - fx->amount * 128.0f);
	fx->coefficients[1] = sp30[1] * (26768 - fx->amount * 128.0f);
	fx->coefficients[2] = 0;
	fx->coefficients[8] = sp24[1] * -16384;
	fx->coefficients[9] = sp24[2] * -16384;

	for (i = 10; i < 16; i++) {
		fx->coefficients[i] = 0;
	}
}

void n_alFxNew(ALFxRef *fx_ar, ConkerNAudioConfig *c, s16 bus, ALHeap *hp)
{
	u16 i, j, k;
	s32 *param = 0;
	ConkerNAudioDelay	*d;
	ConkerNAudioFx *r;

	*fx_ar = r = (ConkerNAudioFx *)alHeapAlloc(hp, 1, sizeof(ConkerNAudioFx));

	switch (c->fxTypes[bus]) {
	case AL_FX_CUSTOM:
		param = c->params[bus];
		break;
	default:
		param = __conker_default_fx_params;
		break;
	}

	j = 0;

	r->section_count = param[j++];
	r->length = param[j++];

	r->delay = alHeapAlloc(hp, r->section_count, sizeof(ConkerNAudioDelay));
	r->base[0] = alHeapAlloc(hp, r->length, sizeof(s16));
	r->input[0] = r->base[0];
	r->base[1] = alHeapAlloc(hp, r->length, sizeof(s16));
	r->input[1] = r->base[1];

	for (k = 0; k < r->length; k++) {
		r->base[0][k] = r->base[1][k] = 0;
	}

	for (i = 0; i < r->section_count; i++) {
		d = &r->delay[i];
		d->input  = param[j++];
		d->output = param[j++];
		d->fbcoef = param[j++];
		d->ffcoef = param[j++];
		d->gain   = param[j++];

		if (param[j]) {
#define RANGE 2.0f
			/*	    d->rsinc     = ((f32) param[j++])/0xffffff; */
			d->rsinc = ((((f32)param[j++])/1000) * RANGE)/c->outputRate;

			/*
			 * the following constant is derived from:
			 *
			 *		ratio = 2^(cents/1200)
			 *
			 * and therefore for hundredths of a cent
			 *			           x
			 *		ln(ratio) = ---------------
			 *			    (120,000)/ln(2)
			 * where
			 *		120,000/ln(2) = 173123.40...
			 */
#define CONVERT 173123.404906676f
#define LENGTH	(d->output - d->input)
			d->rsgain 	 = (((f32) param[j++])/CONVERT) * LENGTH;
			d->rsval	 = 1.0f;
			d->rsdelta	 = 0.0f;
			d->rs 	 = alHeapAlloc(hp, 1, sizeof(ConkerNAudioResampler));
			d->rs->state[0] = alHeapAlloc(hp, 1, sizeof(RESAMPLE_STATE));
			d->rs->state[1] = alHeapAlloc(hp, 1, sizeof(RESAMPLE_STATE));
			d->rs->delta = 0.0f;
			d->rs->first = 1;
		} else {
			d->rs = 0;
			j++;
			j++;
		}

		if (param[j]) {
			d->lp = alHeapAlloc(hp, 1, sizeof(ConkerNAudioLowPass));
			d->lp->fstate[0] = alHeapAlloc(hp, 1, sizeof(POLEF_STATE));
			d->lp->fstate[1] = alHeapAlloc(hp, 1, sizeof(POLEF_STATE));
			d->lp->fc = param[j++];
			n_alFxInitlpfilter(d->lp);
		} else {
			d->lp = 0;
			j++;
		}
	}
}

void alN_PVoiceNew(ConkerNAudioPVoice *mv, ALDMANew dmaNew, ALHeap *hp)
{
	mv->dc_state = alHeapAlloc(hp, 1, sizeof(ADPCM_STATE));
	mv->dc_lstate = alHeapAlloc(hp, 1, sizeof(ADPCM_STATE));
	mv->dc_dma = dmaNew(&mv->dc_dmaState);
	mv->dc_lastsam = 0;
	mv->dc_first = 1;
	mv->dc_memin = 0;

	mv->rs_state = alHeapAlloc(hp, 1, sizeof(RESAMPLE_STATE));
	mv->rs_delta  = 0.0f;
	mv->rs_first  = 1;
	mv->rs_ratio = 1.0f;
	mv->rs_upitch = 0;

	mv->em_state = alHeapAlloc(hp, 1, sizeof(ENVMIX_STATE));
	mv->em_first = 1;
	mv->em_motion = AL_STOPPED;
	mv->em_volume = 1;
	mv->em_ltgt = 1;
	mv->em_rtgt = 1;
	mv->em_cvolL = 1;
	mv->em_cvolR = 1;
	mv->em_dryamt = 0;
	mv->em_wetamt = 0;
	mv->em_lratm = 1;
	mv->em_lratl = 0;
	mv->em_lratm = 1;
	mv->em_lratl = 0;
	mv->em_delta = 0;
	mv->em_segEnd = 0;
	mv->em_pan = 0;
	mv->em_ctrlList = 0;
	mv->em_ctrlTail = 0;
	mv->flags99 = 0;
	mv->fx.amount = 0;
	mv->fx.frequency = 0;
	mv->filterBuffer = alHeapAlloc(hp, 1, 8);
	mv->filterState = 0;
}
