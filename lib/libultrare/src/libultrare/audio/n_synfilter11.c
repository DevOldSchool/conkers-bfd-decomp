#include "n_audio_partial.h"

/* Complete US 0x1E350:0x1E400; N-audio filter update with Conker offsets. */
void n_alSynFilter11(ConkerNAudioVoice *v, u8 channel)
{
    ConkerNAudioParam *update;

    if (v->pvoice) {
        update = __n_allocParam();
        if (update == 0) {
            return;
        }
        update->delta = n_syn->paramSamples + v->pvoice->offset;
        update->type = 17;
        update->data.i = channel;
        update->next = 0;
        n_alEnvmixerParam(v->pvoice, 3, update);
    }
}
