#include "n_audio_seq.h"

/* Conker US 0x15550:0x155A0: queue a bank change using Conker's flag 2. */
void n_alCSPSetBank(ConkerNAudioCSPlayer *seqp, ALBank *bank)
{
    ConkerNAudioSeqEvent evt;

    evt.type = AL_SEQP_BANK_EVT;
    evt.msg.spbank.bank = bank;
    n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, 0, 2);
}
