#include "n_audio_partial.h"

/* Complete US 0x1C910:0x1C9E0; N-audio update using Conker voice offsets. */
void n_alSynSetVol(ConkerNAudioVoice *v, s16 volume, ALMicroTime time)
{
    ConkerNAudioParam *update;

    if (v->pvoice) {
        update = __n_allocParam();
        if (update == 0) {
            return;
        }
        update->delta = n_syn->paramSamples + v->pvoice->offset;
        update->type = 11;
        update->data.i = volume;
        update->moredata.i = _n_timeToSamples(time);
        update->next = 0;
        n_alEnvmixerParam(v->pvoice, 3, update);
    }
}
