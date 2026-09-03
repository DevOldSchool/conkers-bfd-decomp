#include "n_audio_partial.h"

/* Complete US 0x17D80:0x17DF0; Conker posts this event with flags 2. */
void n_alCSPSetChlPan(ConkerNAudioCSPlayer *seqp, u8 chan, ALPan pan)
{
    ALEvent event;

    event.type = AL_SEQP_MIDI_EVT;
    event.msg.midi.ticks = 0;
    event.msg.midi.status = AL_MIDI_ControlChange | chan;
    event.msg.midi.byte1 = AL_MIDI_PAN_CTRL;
    event.msg.midi.byte2 = pan;
    n_alEvtqPostEvent(&seqp->evtq, &event, 0, 2);
}
