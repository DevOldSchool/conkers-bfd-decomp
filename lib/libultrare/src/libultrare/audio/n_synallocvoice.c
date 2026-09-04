#include "n_audio_partial.h"
#include "n_audio_list.h"

/* Complete US 0x1DC80:0x1E170. Conker adds per-voice release data and
 * auxiliary-bus list membership to the N-audio allocation algorithm.
 */
s32 _allocatePVoice(ConkerNAudioPVoice **pvoice, s16 priority);

s32 n_alSynAllocVoice(ConkerNAudioVoice *voice, ConkerNAudioVoiceConfig *vc)
{
	ConkerNAudioPVoice *pvoice = 0;
	ConkerNAudioParam *update;
	s32 stolen;

	voice->priority   = vc->standard.priority;
	voice->unityPitch = vc->standard.unityPitch;
	voice->table      = 0;
	voice->fxBus      = vc->standard.fxBus;
	voice->state      = AL_STOPPED;
	voice->pvoice     = 0;
	voice->releaseData = vc->releaseData;

	stolen = _allocatePVoice( &pvoice, vc->standard.priority);

	if (pvoice) {    /* if we were able to allocate a voice */
		if (stolen) {
			pvoice->offset = 552;
			pvoice->vvoice->pvoice = 0; /* zero stolen voice */
			pvoice->vvoice = voice;
			voice->pvoice = pvoice;

			/*
			 * ramp down stolen voice
			 */
			update = __n_allocParam();

			if (update) {
				update->delta      = n_syn->paramSamples;
				update->type       = 11;
				update->data.i     = 0;
				update->moredata.i = 368; /* pvoice->offset - 184 */

				n_alEnvmixerParam(voice->pvoice, 3, update);
			} else {
				// empty
			}

			/*
			 * stop stolen voice
			 */
			update = __n_allocParam();

			if (update) {
				update->delta = n_syn->paramSamples + pvoice->offset;
				update->type = 15;
				update->next = 0;
				n_alEnvmixerParam(voice->pvoice, 3, update);
			} else {
				// empty
			}
		} else {
			pvoice->offset = 0;
			pvoice->vvoice = voice;
			voice->pvoice = pvoice;
			CONKER_AUDIO_UNLINK(&pvoice->auxNode);
			CONKER_AUDIO_LINK(&pvoice->auxNode, &n_syn->auxBus[vc->standard.fxBus].sources);
			pvoice->dc_table = 0;
		}
	}

	return (pvoice != 0);
}

s32 _allocatePVoice(ConkerNAudioPVoice **pvoice, s16 priority)
{
	ALLink *dl;
	ConkerNAudioPVoice *pv;
	s32 stolen = 0;

	if ((dl = n_syn->pLameList.next) != 0) { /* check the lame list first */
		*pvoice = (ConkerNAudioPVoice *)dl;
		CONKER_AUDIO_UNLINK(dl);
		CONKER_AUDIO_LINK(dl, &n_syn->pAllocList);
	} else if ((dl = n_syn->pFreeList.next) != 0) { /* from the free list */
		*pvoice = (ConkerNAudioPVoice *) dl;
		CONKER_AUDIO_UNLINK(dl);
		CONKER_AUDIO_LINK(dl, &n_syn->pAllocList);
	} else { /* steal one */
		for (dl = n_syn->pAllocList.next; dl != 0; dl = dl->next) {
			pv = (ConkerNAudioPVoice *)dl;

			/*
			 * if it is lower priority and not already stolen, keep it
			 * as a candidate for stealing
			 */
			if ((pv->vvoice->priority <= priority) && (pv->offset == 0)) {
				*pvoice = pv;
				priority = pv->vvoice->priority;
				stolen = 1;
			}
		}
	}

	return stolen;
}
