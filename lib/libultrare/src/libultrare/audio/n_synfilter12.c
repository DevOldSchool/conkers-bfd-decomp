#include "n_audio_partial.h"

/* Complete US 0x1CB40:0x1CBF0; N-audio filter update with Conker offsets. */
void n_alSynFilter12(ConkerNAudioVoice *v, u8 value)
{
    ConkerNAudioParam *update;

    if (v->pvoice) {
        update = __n_allocParam();
        if (update == 0) {
            return;
        }
        update->delta = n_syn->paramSamples + v->pvoice->offset;
        update->type = 18;
        update->data.i = value;
        update->next = 0;
        n_alEnvmixerParam(v->pvoice, 3, update);
    }
}
