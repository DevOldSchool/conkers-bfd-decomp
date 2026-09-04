#include "n_audio_partial.h"

/* Complete US 0x1C770:0x1C810; N-audio update using Conker voice offsets. */
void n_alSynStopVoice(ConkerNAudioVoice *v)
{
    ConkerNAudioParam *update;

    if (v->pvoice) {
        update = __n_allocParam();
        if (update == 0) {
            return;
        }
        update->delta = n_syn->paramSamples + v->pvoice->offset;
        update->type = 15;
        update->next = 0;
        n_alEnvmixerParam(v->pvoice, 3, update);
    }
}
