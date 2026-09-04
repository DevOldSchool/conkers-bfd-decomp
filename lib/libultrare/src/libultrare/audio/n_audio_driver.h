#ifndef CONKER_N_AUDIO_DRIVER_H
#define CONKER_N_AUDIO_DRIVER_H
#include "n_audio_partial.h"

/* Driver construction layouts verified from Conker's allocation and accesses. */
typedef struct {
    u8 filter[0x14];
    RESAMPLE_STATE *state[2];
    f32 ratio;
    s32 upitch;
    f32 delta;
    s32 first;
    ConkerNAudioParam *ctrlList;
    ConkerNAudioParam *ctrlTail;
    s32 motion;
} ConkerNAudioResampler;

typedef struct {
    s16 fc;
    s16 fgain;
    union { s16 fccoef[16]; s64 force_aligned; } fcvec;
    s32 first;
    POLEF_STATE *fstate[2];
    s32 field34;
} ConkerNAudioLowPass;

typedef struct {
    u32 input;
    u32 output;
    s16 ffcoef;
    s16 fbcoef;
    s16 gain;
    f32 rsinc;
    f32 rsval;
    s32 rsdelta;
    f32 rsgain;
    ConkerNAudioLowPass *lp;
    ConkerNAudioResampler *rs;
} ConkerNAudioDelay;

typedef struct {
    u32 length;
    ConkerNAudioDelay *delay;
    u8 section_count;
    u8 filter[0x17];
    s16 *base[2];
    s16 *input[2];
} ConkerNAudioFx;
#endif
