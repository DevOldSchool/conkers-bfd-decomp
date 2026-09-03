#include "n_audio_partial.h"

/* Complete US 0x18D50:0x18DA0; Conker posts this event with flags 2. */
void n_alCSPStop(ConkerNAudioCSPlayer *seqp)
{
    ALEvent event;

    event.type = AL_SEQP_STOP_EVT;
    n_alEvtqPostEvent(&seqp->evtq, &event, 0, 2);
}
