#include "n_audio_partial.h"

/* Complete US 0x18CB0:0x18D00; Conker posts this event with flags 2. */
void n_alCSPSetSeq(ConkerNAudioCSPlayer *seqp, ALCSeq *seq)
{
    ALEvent event;

    event.type = AL_SEQP_SEQ_EVT;
    event.msg.spseq.seq = seq;
    n_alEvtqPostEvent(&seqp->evtq, &event, 0, 2);
}
