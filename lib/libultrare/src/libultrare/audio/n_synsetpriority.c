#include "n_audio_partial.h"

/* Conker's N-audio priority field is at +0x1A, unlike the stock voice. */
void n_alSynSetPriority(ConkerNAudioVoice *voice, s16 priority)
{
    voice->priority = priority;
}
