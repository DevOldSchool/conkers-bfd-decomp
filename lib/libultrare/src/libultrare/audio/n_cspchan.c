#include "n_audio_partial.h"

/* Conker US 0x17AF0:0x17D80: channel control family. The two unnamed
 * setters retain neutral field names pending semantic identification.
 */
void __conker_csp_set_field84(ConkerNAudioCSPlayer *seqp, void *value)
{
    seqp->field84 = value;
}

void __conker_csp_set_channel_field17(ConkerNAudioCSPlayer *seqp, s32 chan, u8 value)
{
    seqp->chanState[chan].field17 = value;
}

void n_alCSPAllChanOn(ConkerNAudioCSPlayer *seqp)
{
    s32 i;
    seqp->chanMask = 0xffff;
    for (i = 0; i < seqp->maxChannels; i++) {
        seqp->chanState[i].fadevoltarget = 255;
        seqp->chanState[i].fadevolcurrent = 255;
    }
}

void n_alCSPChanOff(ConkerNAudioCSPlayer *seqp, s32 chan)
{
    n_alCSPSendMidi(seqp, 0, AL_MIDI_ControlChange | chan, 0xfc, 0);
}

void n_alCSPChanOn(ConkerNAudioCSPlayer *seqp, s32 chan)
{
    seqp->chanMask |= 1 << chan;
    n_alCSPSendMidi(seqp, 0, AL_MIDI_ControlChange | chan, 0xfc, 255);
}

void n_alCSPChanFade(ConkerNAudioCSPlayer *seqp, s32 chan, u8 targetvol, u8 incvol)
{
    n_alCSPSendMidi(seqp, 0, AL_MIDI_ControlChange | chan, 0xfd, incvol);
    n_alCSPSendMidi(seqp, 0, AL_MIDI_ControlChange | chan, 0xff, targetvol);
}

void n_alCSPChanSurround(ConkerNAudioCSPlayer *seqp, s32 chan, u8 value)
{
    n_alCSPSendMidi(seqp, 0, AL_MIDI_ControlChange | chan, 0x41, value);
}

void n_alCSPChanFadeForce(ConkerNAudioCSPlayer *seqp, s32 chan, u8 vol)
{
    n_alCSPSendMidi(seqp, 0, AL_MIDI_ControlChange | chan, 0xfc, vol);
}
