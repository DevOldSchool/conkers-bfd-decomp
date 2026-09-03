#include "n_audio_partial.h"

/* Complete US 0x1C810:0x1C910; includes Conker's extra release callback. */
void n_alSynFreeVoice(ConkerNAudioVoice *voice)
{
    ConkerNAudioFreeParam *update;

    if (voice->pvoice) {
        if (voice->pvoice->offset) {
            update = (ConkerNAudioFreeParam *)__n_allocParam();
            if (update == 0) {
                return;
            }
            update->delta = n_syn->paramSamples + voice->pvoice->offset;
            update->type = 0;
            update->pvoice = voice->pvoice;
            n_alEnvmixerParam(voice->pvoice, 3, update);
        } else {
            _n_freePVoice(voice->pvoice);
        }
        voice->pvoice = 0;
    }
    if (voice->releaseData) {
        n_syn->release(voice->releaseData);
    }
}
