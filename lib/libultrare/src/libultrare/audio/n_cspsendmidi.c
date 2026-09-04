#include "n_audio_partial.h"

/* Complete US 0x1E400:0x1E480. Conker takes the event delay directly rather
 * than multiplying ticks by the sequence tempo, and uses posting flags 2.
 */
void n_alCSPSendMidi(ConkerNAudioCSPlayer *seqp, s32 delay, u8 status,
                    u8 byte1, u8 byte2)
{
    ALEvent event;
    ALMicroTime deltaTime;

    event.type = AL_SEQP_MIDI_EVT;
    event.msg.midi.ticks = 0;
    event.msg.midi.status = status;
    event.msg.midi.byte1 = byte1;
    event.msg.midi.byte2 = byte2;
    event.msg.midi.duration = 0;
    deltaTime = delay;
    n_alEvtqPostEvent(&seqp->evtq, &event, deltaTime, 2);
}
