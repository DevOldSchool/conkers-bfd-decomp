#include "n_audio_partial.h"

/* Complete US 0x1D900:0x1DBA0: five effects-control functions compiled as one
 * unit. This reconstruction name does not assert the original filename.
 */
extern Acmd *__conker_audio_fx_pull(s32, Acmd *, s32);
extern s32 n_alFxParamHdl(ALFxRef fx, s32 paramID, void *param);
extern void n_alFxInitlpfilter_mono(ConkerNAudioOutputLP *fx, f32 outputRate);

void n_alSynSetFXMix(ConkerNAudioVoice *v, u8 fxmix)
{
    ConkerNAudioParam *update;

    if (v->pvoice) {
        update = __n_allocParam();
        if (update == 0) {
            return;
        }
        update->delta = n_syn->paramSamples + v->pvoice->offset;
        update->type = 16;
        update->data.i = fxmix;
        update->next = 0;
        n_alEnvmixerParam(v->pvoice, 3, update);
    }
}

ALFxRef n_alSynGetFXRef(s16 bus)
{
    ConkerNAudioMainBus *mainbus = n_syn->mainBus;

    if (mainbus->handler == __conker_audio_fx_pull) {
        return n_syn->auxBus[bus].primaryFx;
    } else {
        return 0;
    }
}

ALFxRef n_alSynGetOutputLPRef(s16 bus)
{
    ConkerNAudioMainBus *mainbus = n_syn->mainBus;

    if (mainbus->handler == __conker_audio_fx_pull) {
        return n_syn->auxBus[bus].outputLP;
    } else {
        return 0;
    }
}

void n_alSynSetFXParam(ALFxRef fx, s16 paramID, void *param)
{
    ALFxRef f = fx;

    n_alFxParamHdl(f, (s32)paramID, param);
}

void n_alSynSetOutputLPParam(ConkerNAudioOutputLP *fx, s16 paramID, void *param)
{
    if (paramID == 8) {
        fx->amount = *(s32 *)param * 0.1f;
    } else if (paramID == 9) {
        fx->frequency = *(s32 *)param;
    }
    n_alFxInitlpfilter_mono(fx, n_syn->outputRate);
}
