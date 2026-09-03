#include "n_audio_seq.h"

/* Conker US 0x19B50:0x1AAE0: compact-sequence channel control handlers.
 * The MP3 trigger retains a neutral name until its callee is reviewed.
 */
extern s16 __n_vsVol(ConkerNAudioVoiceState *, ConkerNAudioCSPlayer *);
extern ALMicroTime __n_vsDelta(ConkerNAudioVoiceState *, ALMicroTime);
extern ALPan __n_vsPan(ConkerNAudioVoiceState *, ConkerNAudioCSPlayer *);
extern void __n_seqpReleaseVoice(ConkerNAudioCSPlayer *, ConkerNAudioVoice *, ALMicroTime);
extern void n_alSynSetPan(ConkerNAudioVoice *, ALPan);
extern void n_alSynSetFXMix(ConkerNAudioVoice *, u8);
extern void n_alSynFilter11(ConkerNAudioVoice *, u8);
extern void n_alSynFilter12(ConkerNAudioVoice *, u8);
extern void n_alSynFilter13(ConkerNAudioVoice *, f32);
extern f32 alSemitones2Ratio(s32);
extern f32 fabsf(f32);
#pragma intrinsic(fabsf)
extern void __conker_audio_1263C(s32, s32, s32);
void __n_cspFadeUpdate(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);

void __n_cspVolume(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    ConkerNAudioVoiceState *vs;
    s16 vol;
    seqp->chanState[chan].vol = value;
    for (vs = seqp->vAllocHead; vs; vs = vs->next) {
        if (vs->channel == chan && vs->envPhase != 3) {
            vol = __n_vsVol(vs, seqp);
            n_alSynSetVol(&vs->voice, vol, __n_vsDelta(vs, seqp->curTime));
        }
    }
}

void __n_cspPan(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    ConkerNAudioVoiceState *vs;
    ALPan pan;
    seqp->chanState[chan].pan = value;
    for (vs = seqp->vAllocHead; vs; vs = vs->next) {
        if (vs->channel == chan) {
            pan = __n_vsPan(vs, seqp);
            n_alSynSetPan(&vs->voice, pan);
        }
    }
}

void __n_cspPriority(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    seqp->chanState[chan].priority = value;
}

void __n_cspNotify(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    if (seqp->field84) {
        osSendMesg((OSMesgQueue *)seqp->field84,
                   (OSMesg)((value & 7) | 0x10 | ((seqp->node.samplesLeft << 5) & 0xffffff00)), 0);
    }
}

void __n_cspInstrumentMajor(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    seqp->chanState[chan].instmajor = value;
}

void __n_cspRefreshFilter(ConkerNAudioCSPlayer *seqp, u8 chan)
{
    ConkerNAudioVoiceState *vs;
    s16 enabled;
    s8 pitchOffset = (s8)seqp->chanState[chan].field15 - 64;
    f32 bend = seqp->chanState[chan].pitchBend;
    for (vs = seqp->vAllocHead; vs; vs = vs->next) {
        if (vs->channel == chan) {
            enabled = seqp->chanState[chan].field14;
            n_alSynFilter12(&vs->voice, enabled);
            if (enabled) {
                n_alSynFilter13(&vs->voice,
                    alSemitones2Ratio(vs->key - vs->sound->keyMap->keyBase + pitchOffset) * 440 * bend);
            }
        }
    }
}

void __n_cspFilterEnable(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    seqp->chanState[chan].field14 = value;
    __n_cspRefreshFilter(seqp, chan);
}

void __n_cspFilterPitch(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    seqp->chanState[chan].field15 = value;
    __n_cspRefreshFilter(seqp, chan);
}

void __n_cspFilter11(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    ConkerNAudioVoiceState *vs;
    seqp->chanState[chan].field16 = value;
    for (vs = seqp->vAllocHead; vs; vs = vs->next) {
        if (vs->channel == chan) {
            n_alSynFilter11(&vs->voice, value);
        }
    }
}

void __n_cspSustain(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    ConkerNAudioVoiceState *vs;
    seqp->chanState[chan].sustain = value;
    for (vs = seqp->vAllocHead; vs; vs = vs->next) {
        if (vs->channel == chan && vs->phase != 3) {
            if (value >= 64) {
                if (vs->phase == 0) vs->phase = 2;
            } else {
                if (vs->phase == 2) vs->phase = 0;
                else if (vs->phase == 4) {
                    vs->phase = 3;
                    if (seqp->chanState[chan].usechanparams) {
                        __n_seqpReleaseVoice(seqp, &vs->voice,
                            seqp->chanState[chan].releaseTime < 16000 ? 16000 : seqp->chanState[chan].releaseTime);
                    } else {
                        __n_seqpReleaseVoice(seqp, &vs->voice,
                            vs->sound->envelope->releaseTime < 16000 ? 16000 : vs->sound->envelope->releaseTime);
                    }
                }
            }
        }
    }
}

void __n_cspSurround(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    ConkerNAudioVoiceState *vs;
    seqp->chanState[chan].fxmix = (seqp->chanState[chan].fxmix & 0x7f) | (value << 7);
    for (vs = seqp->vAllocHead; vs; vs = vs->next) {
        if (vs->channel == chan && vs->envPhase != 3) {
            n_alSynSetFXMix(&vs->voice, seqp->chanState[chan].fxmix);
        }
    }
}

void __n_cspFXMix(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    value &= 0x7f;
    seqp->chanState[chan].fxmix = (seqp->chanState[chan].fxmix & 0x80) | value;
    __n_cspSurround(seqp, event, chan, seqp->chanState[chan].fxmix >> 7);
}

void __n_cspFXBus(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    if (value < n_syn->maxAuxBusses) seqp->chanState[chan].fxbus = value;
}

void __n_cspMP3Major(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    seqp->field36 = value;
}

void __n_cspMP3Trigger(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    __conker_audio_1263C(seqp->field36 * 100 + value, 0x7fff, 0x40);
}

void __n_cspRefreshVolume(ConkerNAudioCSPlayer *seqp, u8 chan)
{
    ConkerNAudioVoiceState *vs;
    s16 vol;
    for (vs = seqp->vAllocHead; vs; vs = vs->next) {
        if (vs->channel == chan && vs->envPhase != 3) {
            vol = __n_vsVol(vs, seqp);
            n_alSynSetVol(&vs->voice, vol, __n_vsDelta(vs, seqp->curTime));
        }
    }
}

void __n_cspFadeStart(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    f32 delta;
    if (seqp->chanState[chan].fadevolinc == 0) seqp->chanState[chan].fadevolinc = 0x88;
    if (value != seqp->chanState[chan].fadevoltarget) {
        delta = (s32)value - seqp->chanState[chan].fadevolcurrent;
        seqp->chanState[chan].fadeStep = delta / (seqp->chanState[chan].fadevolinc & 0x7f);
        seqp->chanState[chan].fadeStep = fabsf(seqp->chanState[chan].fadeStep);
        if (seqp->chanState[chan].fadevoltarget == seqp->chanState[chan].fadevolcurrent) {
            seqp->chanState[chan].fadevoltarget = value;
        } else {
            seqp->chanState[chan].fadevoltarget = value;
            return;
        }
    } else return;
    event->msg.midi.byte1 = 0xfe;
    __n_cspFadeUpdate(seqp, event, chan, value);
}

void __n_cspFadeUpdate(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    u8 current = seqp->chanState[chan].fadevolcurrent;
    u8 target = seqp->chanState[chan].fadevoltarget;
    s32 delta;
    s32 step;
    f32 amount = seqp->chanState[chan].fadeStep;
    f32 scale;
    delta = target - current;
    if (delta > 0) {
        if (seqp->chanState[chan].fadevolinc & 0x80) amount *= 2.0f;
        step = amount;
        if (step == 0) { step = 1; scale = 1.0f / amount; }
        else scale = (f32)step / amount;
        if (delta > step) delta = step;
    } else {
        step = amount;
        if (step == 0) { step = 1; scale = amount; }
        else scale = (f32)step / amount;
        step = -step;
        if (delta < step) delta = step;
    }
    current += delta;
    seqp->chanState[chan].fadevolcurrent = current;
    if (current != target) {
        n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)event, (seqp->uspt * 100) * scale, 2);
    }
    if (current) seqp->chanMask |= 1 << chan;
    else seqp->chanMask &= ~(1 << chan);
    __n_cspRefreshVolume(seqp, chan);
}

void __n_cspFadeRate(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    seqp->chanState[chan].fadevolinc = value;
}

void __n_cspFadeVolume(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event, u32 chan, u32 value)
{
    seqp->chanState[chan].fadevolcurrent = value;
    seqp->chanState[chan].fadevoltarget = value;
    if (!value) seqp->chanMask &= (1 << chan) ^ 0xffff;
    else seqp->chanMask |= 1 << chan;
    __n_cspRefreshVolume(seqp, chan);
}
