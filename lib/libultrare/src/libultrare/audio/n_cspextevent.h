#ifndef CONKER_N_AUDIO_EXT_EVENT_H
#define CONKER_N_AUDIO_EXT_EVENT_H
#include "n_audio_partial.h"

/* Conker's extended queue messages retain the 16-byte ALEvent storage. */
typedef union {
    ALEvent base;
    struct { s16 type; f32 major; f32 mega; } mix;
    struct { s16 type; s16 pad; u8 bus; u8 param; u8 section; s32 value; } fx;
} ConkerNAudioExtendedEvent;
#endif
