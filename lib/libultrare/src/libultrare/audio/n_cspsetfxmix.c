#include "n_cspextevent.h"

/* Conker US 0x17DF0:0x17EC0: global effect mix and channel control 0x5C. */
void __conker_csp_set_fx_mix(ConkerNAudioCSPlayer *seqp, f32 major, f32 mega)
{
    ConkerNAudioExtendedEvent event;
    event.mix.type = 0x19;
    event.mix.major = major;
    event.mix.mega = mega;
    n_alEvtqPostEvent(&seqp->evtq, &event.base, 0, 2);
}

void __conker_csp_control5c(ConkerNAudioCSPlayer *seqp, u8 chan, u8 value)
{
    ALEvent event;
    event.type = AL_SEQP_MIDI_EVT;
    event.msg.midi.ticks = 0;
    event.msg.midi.status = AL_MIDI_ControlChange | chan;
    event.msg.midi.byte1 = 0x5c;
    event.msg.midi.byte2 = value;
    n_alEvtqPostEvent(&seqp->evtq, &event, 0, 2);
}
