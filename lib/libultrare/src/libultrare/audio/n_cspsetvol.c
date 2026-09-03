#include "n_audio_partial.h"

/* Complete US 0x18D00:0x18D50; Conker posts this event with flags 2. */
void n_alCSPSetVol(ConkerNAudioCSPlayer *seqp, s16 vol)
{
    ALEvent event;

    event.type = AL_SEQP_VOL_EVT;
    event.msg.spvol.vol = vol;
    n_alEvtqPostEvent(&seqp->evtq, &event, 0, 2);
}
