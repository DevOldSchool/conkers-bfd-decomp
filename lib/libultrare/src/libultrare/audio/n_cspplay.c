#include "n_audio_partial.h"

/* Complete US 0x17AA0:0x17AF0; Conker posts this event with flags 2. */
void n_alCSPPlay(ConkerNAudioCSPlayer *seqp)
{
    ALEvent event;

    event.type = AL_SEQP_PLAY_EVT;
    n_alEvtqPostEvent(&seqp->evtq, &event, 0, 2);
}
