#include "n_audio_seq.h"
#include "n_audio_list.h"

/* Conker US 0x1AAE0:0x1C060: voice/channel helpers and callback-based
 * instrument acquisition. Unknown callback details retain neutral names.
 */
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
enum { CONKER_TREM_OSC_EVT = 23, CONKER_VIB_OSC_EVT = 24 };

void __n_unmapVoice(ConkerNAudioCSPlayer *seqp, ConkerNAudioVoice *voice)
{
	ConkerNAudioVoiceState *prev = 0;
	ConkerNAudioVoiceState *vs;

	/*
	 * we could use doubly linked lists here and save some code and
	 * execution time, but time spent here in negligible, so it won't
	 * make much difference.
	 */
	for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
		if (&vs->voice == voice) {
			if (prev) {
				prev->next = vs->next;
			} else {
				seqp->vAllocHead = vs->next;
			}

			if (vs == seqp->vAllocTail) {
				seqp->vAllocTail = prev;
			}

			vs->next = seqp->vFreeList;
			seqp->vFreeList = vs;
			seqp->voicecount--;
			return;
		}

		prev = vs;
	}
}

void __n_seqpReleaseVoice(ConkerNAudioCSPlayer *seqp, ConkerNAudioVoice *voice, ALMicroTime deltaTime)
{
	ConkerNAudioSeqEvent evt;
	ConkerNAudioVoiceState *vs = (ConkerNAudioVoiceState *)voice->clientPrivate;

	/*
	 * if in attack phase, remove all pending volume
	 * events for this voice from the queue
	 */

	if (vs->envPhase == AL_PHASE_ATTACK) {
		ALLink *thisNode;
		ALLink *nextNode;
		ConkerNAudioSeqEventItem *thisItem, *nextItem;

		thisNode = seqp->evtq.allocList.next;

		while (thisNode != 0) {
			nextNode = thisNode->next;
			thisItem = (ConkerNAudioSeqEventItem *)thisNode;
			nextItem = (ConkerNAudioSeqEventItem *)nextNode;

			if (thisItem->evt.type == AL_SEQP_ENV_EVT) {
				if (thisItem->evt.msg.vol.voice == voice) {
					if (nextItem) {
						nextItem->delta += thisItem->delta;
					}

					CONKER_AUDIO_UNLINK(thisNode);
					CONKER_AUDIO_LINK(thisNode, &seqp->evtq.freeList);
				}
			}

			thisNode = nextNode;
		}
	}

	vs->velocity = 0;
	vs->envPhase = AL_PHASE_RELEASE;
	vs->envGain  = 0;
	vs->envEndTime = seqp->curTime + deltaTime;

	n_alSynSetPriority(voice, 0); /* make candidate for stealing */
	n_alSynSetVol(voice, 0, deltaTime);

	evt.type = AL_NOTE_END_EVT;
	evt.msg.note.voice = voice;

	deltaTime += AL_USEC_PER_FRAME * 2;

	n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, deltaTime, 0);
}

char __n_voiceNeedsNoteKill(ConkerNAudioCSPlayer *seqp, ConkerNAudioVoice *voice, ALMicroTime killTime)
{
	ALLink *thisNode;
	ALLink *nextNode;
	ConkerNAudioSeqEventItem *thisItem;
	ALMicroTime itemTime = 0;
	char needsNoteKill = TRUE;

	thisNode = seqp->evtq.allocList.next;

	while (thisNode != 0) {
		nextNode = thisNode->next;
		thisItem = (ConkerNAudioSeqEventItem *)thisNode;
		itemTime += thisItem->delta;

		if (thisItem->evt.type == AL_NOTE_END_EVT) {
			if (thisItem->evt.msg.note.voice == voice) {
				if (itemTime > killTime) {
					if ((ConkerNAudioSeqEventItem *)nextNode) {
						((ConkerNAudioSeqEventItem *)nextNode)->delta += thisItem->delta;
					}

					CONKER_AUDIO_UNLINK(thisNode);
					CONKER_AUDIO_LINK(thisNode, &seqp->evtq.freeList);
				} else {
					needsNoteKill = FALSE;
				}

				break;
			}
		}

		thisNode = nextNode;
	}

	return needsNoteKill;
}

ConkerNAudioVoiceState *__n_mapVoice(ConkerNAudioCSPlayer *seqp, u8 key, u8 vel, u8 channel)
{
	ConkerNAudioVoiceState *vs = seqp->vFreeList;

	if (seqp->voicecount > seqp->voicelimit) {
		return 0;
	}

	if (vs) {
		seqp->vFreeList = vs->next;
		vs->next = 0;

		if (!seqp->vAllocHead) {
			seqp->vAllocHead = vs;
		} else {
			seqp->vAllocTail->next = vs;
		}

		seqp->vAllocTail = vs;

		vs->channel = channel;
		vs->key = key;
		vs->velocity = vel;
		vs->voice.clientPrivate = vs;

		seqp->voicecount++;
	}

	return vs;
}

ConkerNAudioVoiceState *__n_lookupVoice(ConkerNAudioCSPlayer *seqp, u8 key, u8 channel)
{
	ConkerNAudioVoiceState *vs = seqp->vAllocHead;

	while (vs != 0) {
		if (vs->key == key
				&& vs->channel == channel
				&& vs->phase != AL_PHASE_RELEASE
				&& vs->phase != AL_PHASE_SUSTREL) {
			return vs;
		}

		vs = vs->next;
	}

	return 0;
}

ALSound *__n_lookupSoundQuick(ConkerNAudioCSPlayer *seqp, u8 key, u8 vel, u8 chan)
{
	ALInstrument *inst = seqp->chanState[chan].instrument;
	s32 l = 1;
	s32 r;
	s32 i;
	ALKeyMap *keymap;

	if (!inst) return 0;
	r = inst->soundCount;

	while (r >= l) {
		i = (l + r) / 2;

		keymap = inst->soundArray[i - 1]->keyMap;

		if (key >= keymap->keyMin && key <= keymap->keyMax
				&& vel >= keymap->velocityMin && vel <= keymap->velocityMax) {
			return inst->soundArray[i - 1];
		} else if (key < keymap->keyMin || (vel < keymap->velocityMin && key <= keymap->keyMax)) {
			r = i - 1;
		} else {
			l = i + 1;
		}
	}

	return 0;
}

/**
 * __n_vsVol calculates the target volume for the voice based on the
 * note on velocity, envelope, sampleVolume and controller.
 */
s16 __n_vsVol(ConkerNAudioVoiceState *vs, ConkerNAudioCSPlayer *seqp)
{
	u32 t1 = (vs->tremelo * vs->velocity * vs->envGain) >> 6;
	u32 t2 = (vs->sound->sampleVolume * seqp->vol * seqp->chanState[vs->channel].vol) >> 14;

	if (seqp->chanState[vs->channel].fadevolcurrent != 0xff) {
		t2 = (seqp->chanState[vs->channel].fadevolcurrent * t2 + 1) >> 8;
	}

	t1 *= t2;
	t1 >>= 15;

	return t1;
}

u8 __n_vsMix(ConkerNAudioVoiceState *vs, ConkerNAudioCSPlayer *seqp)
{
	s32 sign = seqp->chanState[vs->channel].fxmix & 0x80;
	s32 fxmix = ((seqp->chanState[vs->channel].fxmix & 0x7f) + (s32)(seqp->fxmixmajor * 127)) * seqp->fxmixmega;

	return MAX(0, MIN(127, fxmix)) | sign;
}

ALMicroTime __n_vsDelta(ConkerNAudioVoiceState *vs, ALMicroTime t)
{
	/*
	 * If we are interrupting a previously set envelope segment, we
	 * need to recalculate the segment end time given the current
	 * time. Note: this routine assumes that the voice is currently
	 * playing.
	 */

	s32 delta = vs->envEndTime - t;

	if (delta >= 0) {
		return delta;
	} else {
		return AL_GAIN_CHANGE_TIME;
	}
}

ALPan __n_vsPan(ConkerNAudioVoiceState *vs, ConkerNAudioCSPlayer *seqp)
{
	s32 tmp;

	tmp = seqp->chanState[vs->channel].pan - AL_PAN_CENTER + vs->sound->samplePan;
	tmp = MAX(tmp, AL_PAN_LEFT);
	tmp = MIN(tmp, AL_PAN_RIGHT);

	return (ALPan) tmp;
}

void __n_initFromBank(ConkerNAudioCSPlayer *seqp, ALBank *b)
{
	/*
	 * init the chanState with the default instrument
	 */
	s32 i;
	ALInstrument *inst = 0;

	/* set to the first available instrument. */
	for (i = 1; !inst; i++) {
		inst = b->instArray[i];
	}

	/* sct 11/6/95 - Setup the channel state for the given instrument. */
	/* There is some wasted effort here since both calls the same state vars */
	/* but it's safer. */
	for (i = 0; i < seqp->maxChannels; i++) {
		__n_resetPerfChanState(seqp, i);
	}

	if (b->percussion) {
		__n_resetPerfChanState(seqp, i);
	}
}

void __n_initChanState(ConkerNAudioCSPlayer *seqp)
{
	int i;

	for (i = 0; i < seqp->maxChannels; i++) {
		seqp->chanState[i].instrument = 0;
		__n_resetPerfChanState (seqp, i);
	}
}

void __n_resetPerfChanState(ConkerNAudioCSPlayer *seqp, s32 chan)
{
	seqp->chanState[chan].fxmix = AL_DEFAULT_FXMIX;
	seqp->chanState[chan].pan = AL_PAN_CENTER;
	seqp->chanState[chan].vol = 127;
	seqp->chanState[chan].priority = AL_DEFAULT_PRIORITY;
	seqp->chanState[chan].sustain = 0;
	seqp->chanState[chan].bendRange = 200;
	seqp->chanState[chan].pitchBend = 1;
	seqp->chanState[chan].field17 = 0;
	seqp->chanState[chan].fadevolcurrent = 255;
	seqp->chanState[chan].fadevoltarget = 255;
	seqp->chanState[chan].fadevolinc = 0;
	seqp->chanState[chan].fxbus = 0;
	seqp->chanState[chan].field16 = 0;
	seqp->chanState[chan].field15 = 0;
	seqp->chanState[chan].field14 = 0;
	seqp->chanState[chan].instmajor = 0;
}

typedef void *(*ConkerBankFetch)(void *, s32);
typedef ConkerBankFetch (*ConkerBankFetchNew)(void);
extern void __conker_bank_patch_sound(ALSound *, ALInstrument *, void *);

s32 __n_setInstChanState(ConkerNAudioCSPlayer *seqp, s32 instrument, s32 chan)
{
    ALSound *sound;
    ALInstrument *inst;
    s32 i;

    inst = __conker_bank_acquire(seqp->drvr, &seqp->bank->instArray[instrument], -1);
    if (seqp->chanState[chan].instrument) {
        ((void (*)(void *))seqp->drvr->callback34)(seqp->bank->instArray[seqp->chanState[chan].instrumentIndex]);
        seqp->chanState[chan].instrument = 0;
    }
    if (inst) {
        for (i = 0; i < inst->soundCount; i++) {
            sound = inst->soundArray[i];
            if ((u32)sound->envelope < 0x100000) {
                __conker_bank_patch_sound(sound, inst, seqp->drvr->callback38);
            }
        }
        sound = inst->soundArray[0];
    }
    if (inst) {
        if (inst->soundCount == 0) return 0;
        if (sound) {
            seqp->chanState[chan].attackTime = sound->envelope->attackTime;
            seqp->chanState[chan].decayTime = sound->envelope->decayTime;
            seqp->chanState[chan].releaseTime = sound->envelope->releaseTime;
            seqp->chanState[chan].attackVolume = sound->envelope->attackVolume;
            seqp->chanState[chan].decayVolume = sound->envelope->decayVolume;
        }
        seqp->chanState[chan].pan = inst->pan;
        seqp->chanState[chan].vol = inst->volume;
        seqp->chanState[chan].priority = inst->priority;
        seqp->chanState[chan].bendRange = inst->bendRange;
        seqp->chanState[chan].tremType = inst->tremType;
        seqp->chanState[chan].tremRate = inst->tremRate;
        seqp->chanState[chan].tremDepth = inst->tremDepth;
        seqp->chanState[chan].tremDelay = inst->tremDelay;
        seqp->chanState[chan].vibType = inst->vibType;
        seqp->chanState[chan].vibRate = inst->vibRate;
        seqp->chanState[chan].vibDepth = inst->vibDepth;
        seqp->chanState[chan].vibDelay = inst->vibDelay;
        seqp->chanState[chan].loadFailed = 0;
        seqp->chanState[chan].instrument = inst;
    } else {
        seqp->chanState[chan].loadFailed = 1;
    }
    seqp->chanState[chan].pitch = 0;
    seqp->chanState[chan].usechanparams = 0;
    seqp->chanState[chan].timeindex = 0;
    seqp->chanState[chan].instrumentIndex = instrument;
    if (!inst) return 1;
    return 0;
}

void *__conker_bank_acquire(ConkerNAudioSynth *synth, ALInstrument **slot, s32 index)
{
    ConkerBankFetch fetch;
    void *result = 0;
    fetch = ((ConkerBankFetchNew)synth->callback28)();
    if (fetch) {
        if (index == -1) result = fetch(slot, 1);
        else result = fetch(&(*slot)->soundArray[index], 0);
        if (result && ((u32)result & 0xff000003) != 0x80000000) return 0;
    } else {
        return 0;
    }
    return result;
}

void __conker_bank_release(ConkerNAudioSynth *synth, ALInstrument *inst, s32 index)
{
    if (index == -1) ((void (*)(void *))synth->callback30)(inst);
    else ((void (*)(void *))synth->callback30)(inst->soundArray[index]);
}

void __n_seqpStopOsc(ConkerNAudioCSPlayer *seqp, ConkerNAudioVoiceState *vs)
{
	ConkerNAudioSeqEventItem *thisNode,*nextNode;
	s16 evtType;

	thisNode = (ConkerNAudioSeqEventItem*)seqp->evtq.allocList.next;

	while (thisNode) {
		nextNode = (ConkerNAudioSeqEventItem*)thisNode->node.next;
		evtType = thisNode->evt.type;

		if (evtType == CONKER_TREM_OSC_EVT || evtType == CONKER_VIB_OSC_EVT) {
			if (thisNode->evt.msg.osc.vs == vs) {
				(*seqp->stopOsc)(thisNode->evt.msg.osc.oscState);
				CONKER_AUDIO_UNLINK((ALLink*)thisNode);

				if (nextNode) {
					nextNode->delta += thisNode->delta;
				}

				CONKER_AUDIO_LINK((ALLink*)thisNode, &seqp->evtq.freeList);

				if (evtType == CONKER_TREM_OSC_EVT) {
					vs->flags &= 0xfe;
				} else { /* must be a CONKER_VIB_OSC_EVT */
					vs->flags &= 0xfd;
				}

				if (!vs->flags) {
					return;  /* there should be no more events */
				}
			}
		}

		thisNode = nextNode;
	}
}
