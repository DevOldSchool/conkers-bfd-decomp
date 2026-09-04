#ifndef CONKER_N_AUDIO_SEQ_H
#define CONKER_N_AUDIO_SEQ_H
#include "n_audio_partial.h"

/* Sequence queue messages preserve the established 16-byte event layout. */
typedef struct {
    ALLink node;
    ALMicroTime delta;
    ConkerNAudioSeqEvent evt;
} ConkerNAudioSeqEventItem;

void __n_resetPerfChanState(ConkerNAudioCSPlayer *, s32);
s32 __n_setInstChanState(ConkerNAudioCSPlayer *, s32, s32);
void * __conker_bank_acquire(ConkerNAudioSynth *, ALInstrument **, s32);
void __conker_bank_release(ConkerNAudioSynth *, ALInstrument *, s32);
void n_alSynSetVol(ConkerNAudioVoice *, s16, ALMicroTime);
void n_alSynSetPriority(ConkerNAudioVoice *, s16);
#endif
