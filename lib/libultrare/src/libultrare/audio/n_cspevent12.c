#include "n_audio_partial.h"

/* Conker US 0x18C60:0x18CB0: posts event 0x12 with flags 2. */
void __conker_csp_post_event12(ConkerNAudioCSPlayer *seqp)
{
    ALEvent event;
    event.type = 0x12;
    n_alEvtqPostEvent(&seqp->evtq, &event, 0, 2);
}
