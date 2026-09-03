#include "n_audio_partial.h"

/* Complete US 0x1E2A0:0x1E350; N-audio filter update with Conker offsets. */
void n_alSynSetPan(ConkerNAudioVoice *v, ALPan pan)
{
    ConkerNAudioParam *update;

    if (v->pvoice) {
        update = __n_allocParam();
        if (update == 0) {
            return;
        }
        update->delta = n_syn->paramSamples + v->pvoice->offset;
        update->type = 12;
        update->data.i = pan;
        update->next = 0;
        n_alEnvmixerParam(v->pvoice, 3, update);
    }
}
