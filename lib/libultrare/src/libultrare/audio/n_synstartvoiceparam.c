#include "n_audio_partial.h"

/* Complete US 0x1E170:0x1E2A0; Conker retains the three extra N-audio filter
 * parameters and reads unityPitch at virtual-voice offset +0x1E.
 */
void n_alSynStartVoiceParams(ConkerNAudioVoice *v, ALWaveTable *wave,
                            f32 pitch, s16 volume, ALPan pan, u8 fxmix,
                            u8 filter12, f32 filter13, u8 filter11, ALMicroTime time)
{
    ConkerNAudioStartParam *update;

    if (v->pvoice) {
        update = (ConkerNAudioStartParam *)__n_allocParam();
        if (update == 0) {
            return;
        }
        update->delta = n_syn->paramSamples + v->pvoice->offset;
        update->next = 0;
        update->type = 13;
        update->unity = v->unityPitch;
        update->pan = pan;
        update->volume = volume;
        update->fxMix = fxmix;
        update->pitch = pitch;
        update->filter11 = filter11;
        update->filter12 = filter12;
        update->filter13 = filter13;
        update->samples = _n_timeToSamples(time);
        update->wave = wave;
        n_alEnvmixerParam(v->pvoice, 3, update);
    }
}
