#include "n_audio_partial.h"

/* Complete US 0x1C9E0:0x1CA90; N-audio update using Conker voice offsets. */
void n_alSynSetPitch(ConkerNAudioVoice *v, f32 pitch)
{
    ConkerNAudioParam *update;

    if (v->pvoice) {
        update = __n_allocParam();
        if (update == 0) {
            return;
        }
        update->delta = n_syn->paramSamples + v->pvoice->offset;
        update->type = 7;
        update->data.f = pitch;
        update->next = 0;
        n_alEnvmixerParam(v->pvoice, 3, update);
    }
}
