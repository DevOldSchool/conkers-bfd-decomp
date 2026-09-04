#include <ultra64.h>

/* Conker US 0x12D80:0x13320: pooled tremolo/vibrato oscillators.
 * Callback pointers use the main runtime mapping, while JAL uses link aliases.
 */
#define OSCTYPE_TREM 1
#define OSCTYPE_VIB 128
extern f32 __conker_osc_sinf(f32);
extern ALMicroTime __conker_runtime_osc_init(void **, f32 *, u8, u8, u8, u8);
extern ALMicroTime __conker_runtime_osc_update(void *, f32 *);
extern void __conker_runtime_osc_stop(void *);

struct typetrem {
	u8 unk28;
	u8 unk29;
};

struct typevib {
	f32 unk28;
};

typedef struct oscData_s {
	struct oscData_s *next;
	u8 type;
	u8 stateFlags;
	u16 maxCount;
	s32 curCount;
	f32 unk0c;
	f32 unk10;
	u16 unk14;
	u16 unk16;
	f32 unk18;
	f32 unk1c;
	u16 unk20;
	u16 unk22;
	u16 unk24;
	u16 unk26;
	union {
		struct typetrem trem;
		struct typevib vib;
	} data;
} oscData;

oscData *freeOscStateList;
oscData *oscStates;

f32 _depth2Cents(u8 depth)
{
	f32 x = 1.0309929847717f;
	f32 cents = 1.0f;

	while (depth) {
		if (depth & 1) {
			cents *= x;
		}

		x *= x;
		depth >>= 1;
	}

	return cents;
}

ALMicroTime osc_init(void **oscState, f32 *initVal, u8 oscType, u8 oscRate, u8 oscDepth, u8 oscDelay)
{
	oscData *state;
	ALMicroTime result = 0;

	if (oscDelay == 0) {
		return 0;
	}

	if (freeOscStateList != NULL) {
		state = freeOscStateList;
		freeOscStateList = freeOscStateList->next;
		state->type = oscType;
		*oscState = state;
		result = oscDelay << 14;

		switch (oscType) {
		case OSCTYPE_TREM:
			state->unk24 = 0;
			state->unk22 = 259 - oscRate;
			state->data.trem.unk28 = oscDepth >> 1;
			state->data.trem.unk29 = 127 - state->data.trem.unk28;
			*initVal = state->data.trem.unk29;
			break;
		case OSCTYPE_VIB:
			state->data.vib.unk28 = _depth2Cents(oscDepth);
			state->unk24 = 0;
			state->unk22 = 259 - oscRate;
			*initVal = 1.0f;
			break;
		default:
			break;
		}
	}

	return result;
}

ALMicroTime osc_update(void *oscState, f32 *updateVal)
{
	f32 sp2c;
	oscData *state = oscState;
	ALMicroTime result = AL_USEC_PER_FRAME;

	switch (state->type) {
	case OSCTYPE_TREM:
		state->unk24++;

		if (state->unk24 >= state->unk22) {
			state->unk24 = 0;
		}

		sp2c = (f32)state->unk24 / (f32)state->unk22;
		sp2c = __conker_osc_sinf(sp2c * 6.28318530717958647692f);
		sp2c = sp2c * state->data.trem.unk28;
		*updateVal = state->data.trem.unk29 + sp2c;
		break;
	case OSCTYPE_VIB:
		state->unk24++;

		if (state->unk24 >= state->unk22) {
			state->unk24 = 0;
		}

		sp2c = (f32)state->unk24 / (f32)state->unk22;
		sp2c = __conker_osc_sinf(sp2c * 6.28318530717958647692f) * state->data.vib.unk28;
		*updateVal = alCents2Ratio(sp2c);
		break;
	default:
		break;
	}

	return result;
}

void osc_stop(void *oscState)
{
    ((oscData *)oscState)->next = freeOscStateList;
    freeOscStateList = (oscData *)oscState;
}

void osc_configure(ALSeqpConfig *config, s32 count)
{
    oscData *item;
    s32 i;
    oscStates = alHeapAlloc(config->heap, count, sizeof(oscData));
    freeOscStateList = oscStates;
    freeOscStateList = &oscStates[0];
    item = &oscStates[0];
    for (i = 0; i < count - 1; i++) {
        item->next = &oscStates[i + 1];
        item = item->next;
    }
    item->next = NULL;
    config->initOsc = __conker_runtime_osc_init;
    config->updateOsc = __conker_runtime_osc_update;
    config->stopOsc = __conker_runtime_osc_stop;
}
