#include "n_audio_partial.h"

/* Complete US 0x1E4A0:0x1E530; Conker's auxiliary buses have stride 0x44. */
ALFxRef n_alSynAllocFX(s16 bus, ConkerNAudioConfig *config, ALHeap *heap)
{
    n_alFxNew(&n_syn->auxBus[bus].fx, config, bus, heap);
    return n_syn->auxBus[bus].fx;
}
