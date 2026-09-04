#include "n_audio_seq.h"
#include "n_audio_list.h"

/* Conker US 0x13320:0x15550: compact-sequence engine, with pause/resume,
 * instrument-load retries and the ROM's separate channel-control dispatch.
 */
enum { CONKER_PAUSE_EVT = 16, CONKER_STOP_EVT, CONKER_STOPPING_EVT,
    CONKER_TRACK_END, CONKER_LOOPSTART, CONKER_LOOPEND, CONKER_NOTEOFF_EVT,
    CONKER_TREM_EVT, CONKER_VIB_EVT, CONKER_FXMIX_EVT, CONKER_FXPARAM_EVT };
#define KILL_TIME 50000

typedef void (*ConkerControlHandler)(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
typedef ALMicroTime (*ConkerOscInit)(void **, f32 *, u8, u8, u8, u8, u8);
extern ALMicroTime __conker_runtime_CSPVoiceHandler(void *);
void n_alCSPAllChanOn(ConkerNAudioCSPlayer *);
void __n_initChanState(ConkerNAudioCSPlayer *);
void __n_initFromBank(ConkerNAudioCSPlayer *, ALBank *);
void n_alEvtqNew(ALEventQueue *, ALEventListItem *, s32);
ALMicroTime n_alEvtqNextEvent(ALEventQueue *, ALEvent *);
ALMicroTime n_alEvtqFlushType(ALEventQueue *, s16);
void n_alSynAddSeqPlayer(ALPlayer *);
void n_alSynStopVoice(ConkerNAudioVoice *);
void n_alSynFreeVoice(ConkerNAudioVoice *);
void n_alSynSetPitch(ConkerNAudioVoice *, f32);
void n_alSynSetFXMix(ConkerNAudioVoice *, u8);
ALFxRef n_alSynGetFXRef(s16);
ALFxRef n_alSynGetOutputLPRef(s16);
void n_alSynSetFXParam(ALFxRef, s16, void *);
void n_alSynSetOutputLPParam(ConkerNAudioOutputLP *, s16, void *);
void n_alSynFilter13(ConkerNAudioVoice *, f32);
f32 alSemitones2Ratio(s32);
s32 n_alSynAllocVoice(ConkerNAudioVoice *, ConkerNAudioVoiceConfig *);
void n_alSynStartVoiceParams(ConkerNAudioVoice *, ALWaveTable *, f32, s16, ALPan, u8, u8, f32, u8, ALMicroTime);
void n_alCSeqNextEvent(ALCSeq *, ALEvent *, s32);
s32 __alCSeqNextDelta(ALCSeq *, s32 *);
void __n_seqpStopOsc(ConkerNAudioCSPlayer *, ConkerNAudioVoiceState *);
void __n_unmapVoice(ConkerNAudioCSPlayer *, ConkerNAudioVoice *);
void __n_seqpReleaseVoice(ConkerNAudioCSPlayer *, ConkerNAudioVoice *, ALMicroTime);
char __n_voiceNeedsNoteKill(ConkerNAudioCSPlayer *, ConkerNAudioVoice *, ALMicroTime);
ConkerNAudioVoiceState *__n_mapVoice(ConkerNAudioCSPlayer *, u8, u8, u8);
ConkerNAudioVoiceState *__n_lookupVoice(ConkerNAudioCSPlayer *, u8, u8);
ALSound *__n_lookupSoundQuick(ConkerNAudioCSPlayer *, u8, u8, u8);
s16 __n_vsVol(ConkerNAudioVoiceState *, ConkerNAudioCSPlayer *);
u8 __n_vsMix(ConkerNAudioVoiceState *, ConkerNAudioCSPlayer *);
ALPan __n_vsPan(ConkerNAudioVoiceState *, ConkerNAudioCSPlayer *);
ALMicroTime __n_vsDelta(ConkerNAudioVoiceState *, ALMicroTime);
void __n_CSPHandleNextSeqEvent(ConkerNAudioCSPlayer *);
void __n_CSPHandleMIDIMsg(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *);
void __n_CSPHandleMetaMsg(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *);
void __n_CSPPostNextSeqEvent(ConkerNAudioCSPlayer *);
void __n_CSPRepostEvent(ALEventQueue *, ConkerNAudioSeqEventItem *);
void __n_setUsptFromTempo(ConkerNAudioCSPlayer *, f32);

extern void __conker_runtime_cspVolume(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspPan(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspPriority(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspMP3Trigger(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspMP3Major(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspNotify(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspInstrumentMajor(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspFilterEnable(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspFilterPitch(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspFilter11(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspSustain(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspSurround(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspFXMix(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspFXBus(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspFadeStart(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspFadeUpdate(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspFadeRate(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);
extern void __conker_runtime_cspFadeVolume(ConkerNAudioCSPlayer *, ConkerNAudioSeqEvent *, u32, u32);

u32 __n_cspNoteDuration[16];

ConkerControlHandler __n_cspControls[93] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    __conker_runtime_cspVolume,
    NULL,
    NULL,
    __conker_runtime_cspPan,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    __conker_runtime_cspPriority,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    __conker_runtime_cspMP3Trigger,
    __conker_runtime_cspMP3Major,
    NULL,
    NULL,
    __conker_runtime_cspNotify,
    NULL,
    __conker_runtime_cspInstrumentMajor,
    __conker_runtime_cspFilterEnable,
    __conker_runtime_cspFilterPitch,
    __conker_runtime_cspFilter11,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    __conker_runtime_cspSustain,
    __conker_runtime_cspSurround,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    __conker_runtime_cspFXMix,
    __conker_runtime_cspFXBus,
};
ConkerControlHandler __n_cspHighControls[4] = {
    __conker_runtime_cspFadeStart,
    __conker_runtime_cspFadeUpdate,
    __conker_runtime_cspFadeRate,
    __conker_runtime_cspFadeVolume,
};

void n_alCSPNew(ConkerNAudioCSPlayer *seqp, ALSeqpConfig *c)
{
	s32                 i;
	ConkerNAudioSeqEventItem     *items;
	ConkerNAudioVoiceState        *vs;
	ConkerNAudioVoiceState        *voices;

	ALHeap *hp = c->heap;

	/*
	 * initialize member variables
	 */
	seqp->bank          = 0;
	seqp->target        = NULL;
	seqp->drvr          = n_syn;
	seqp->chanMask      = 0xffff;

	n_alCSPAllChanOn(seqp);

	seqp->uspt          = 488;
	seqp->nextDelta     = 0;
	seqp->state         = AL_STOPPED;
	seqp->vol           = 0x7fff;
	seqp->debugFlags    = c->debugFlags;
	seqp->frameTime     = AL_USEC_PER_FRAME; /* should get this from driver */
	seqp->curTime       = 0;
	seqp->initOsc       = c->initOsc;
	seqp->updateOsc     = c->updateOsc;
	seqp->stopOsc       = c->stopOsc;

	seqp->fxmixmajor = 0;
	seqp->fxmixmega = 1;
	seqp->field84 = 0;
	seqp->voicecount = 0;
	seqp->voicelimit = c->maxVoices;

	seqp->nextEvent.type = AL_SEQP_API_EVT;	/* this will start the voice handler "spinning" */

	/*
	 * init the channel state
	 */
	seqp->maxChannels = c->maxChannels;
	seqp->chanState = alHeapAlloc(hp, c->maxChannels, sizeof(ConkerNAudioChannel) );
	__n_initChanState((ConkerNAudioCSPlayer*)seqp);

	/*
	 * init the voice state array
	 */
	voices = alHeapAlloc(hp, c->maxVoices, sizeof(ConkerNAudioVoiceState));
	seqp->vFreeList = 0;
	for (i = 0; i < c->maxVoices; i++) {
		vs = &voices[i];
		vs->next = seqp->vFreeList;
		seqp->vFreeList = vs;
	}

	seqp->vAllocHead = 0;
	seqp->vAllocTail = 0;

	/*
	 * init the event queue
	 */
	items = alHeapAlloc(hp, c->maxEvents, sizeof(ConkerNAudioSeqEventItem));
	n_alEvtqNew(&seqp->evtq, (ALEventListItem *)items, c->maxEvents);


	/*
	 * add ourselves to the driver
	 */
	seqp->node.next       = NULL;
	seqp->node.handler    = __conker_runtime_CSPVoiceHandler;
	seqp->node.clientData = seqp;

	n_alSynAddSeqPlayer(&seqp->node);
}

ALMicroTime __n_CSPVoiceHandler(void *node)
{
	ConkerNAudioCSPlayer    *seqp = (ConkerNAudioCSPlayer *) node;
	ConkerNAudioSeqEvent        evt;
	ConkerNAudioVoice       *voice;
	ALMicroTime      delta;
	ConkerNAudioVoiceState  *vs;
	void            *oscState;
	f32              oscValue;
	u8               chan;

	do {
		switch (seqp->nextEvent.type) {
		case (AL_SEQ_REF_EVT):
			__n_CSPHandleNextSeqEvent(seqp);
			break;

		case (AL_SEQP_API_EVT):
			evt.type = AL_SEQP_API_EVT;
			n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, seqp->frameTime, 1);
			break;

		case (AL_NOTE_END_EVT):
			voice = seqp->nextEvent.msg.note.voice;

			n_alSynStopVoice(voice);
			n_alSynFreeVoice(voice);
			vs = (ConkerNAudioVoiceState *)voice->clientPrivate;

			if (vs->flags) {
				__n_seqpStopOsc((ConkerNAudioCSPlayer*)seqp,vs);
			}

			__n_unmapVoice((ConkerNAudioCSPlayer*)seqp, voice);
			break;

		case (AL_SEQP_ENV_EVT):
			voice = seqp->nextEvent.msg.vol.voice;
			vs = (ConkerNAudioVoiceState *)voice->clientPrivate;

			if (vs->envPhase == AL_PHASE_ATTACK) {
				vs->envPhase = AL_PHASE_DECAY;
			}

			delta = seqp->nextEvent.msg.vol.delta;
			vs->envEndTime = seqp->curTime + delta;
			vs->envGain = seqp->nextEvent.msg.vol.vol;
			n_alSynSetVol(voice, __n_vsVol(vs, (ConkerNAudioCSPlayer*)seqp), delta);
			break;

		case (CONKER_TREM_EVT):
			vs = seqp->nextEvent.msg.osc.vs;
			oscState = seqp->nextEvent.msg.osc.oscState;
			delta = (*seqp->updateOsc)(oscState,&oscValue);
			vs->tremelo = (u8)oscValue;
			n_alSynSetVol(&vs->voice, __n_vsVol(vs,(ConkerNAudioCSPlayer*)seqp), __n_vsDelta(vs,seqp->curTime));
			evt.type = CONKER_TREM_EVT;
			evt.msg.osc.vs = vs;
			evt.msg.osc.oscState = oscState;
			n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, delta, 0);
			break;

		case (CONKER_VIB_EVT):
			vs = seqp->nextEvent.msg.osc.vs;
			oscState = seqp->nextEvent.msg.osc.oscState;
			chan = seqp->nextEvent.msg.osc.chan;
			delta = (*seqp->updateOsc)(oscState,&oscValue);
			vs->vibrato = oscValue;
			n_alSynSetPitch( &vs->voice, vs->pitch * vs->vibrato * seqp->chanState[chan].pitchBend);

			if (seqp->chanState[chan].field14) {
				n_alSynFilter13(&vs->voice,
						440
						* alSemitones2Ratio(seqp->chanState[chan].field15 + (vs->key - vs->sound->keyMap->keyBase) - 64)
						* seqp->chanState[chan].pitchBend
						* vs->vibrato);
			}

			evt.type = CONKER_VIB_EVT;
			evt.msg.osc.vs = vs;
			evt.msg.osc.oscState = oscState;
			evt.msg.osc.chan = chan;
			n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, delta, 0);
			break;

		case (AL_SEQP_MIDI_EVT):
		case (CONKER_NOTEOFF_EVT):	/* nextEvent is a note off midi message */
			__n_CSPHandleMIDIMsg(seqp, (ConkerNAudioSeqEvent *)&seqp->nextEvent);
			break;

		case (AL_SEQP_META_EVT):
			__n_CSPHandleMetaMsg(seqp, (ConkerNAudioSeqEvent *)&seqp->nextEvent);
			break;

		case (AL_SEQP_VOL_EVT):
			seqp->vol =  seqp->nextEvent.msg.spvol.vol;

			for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
				n_alSynSetVol(&vs->voice,
						__n_vsVol(vs, (ConkerNAudioCSPlayer*)seqp),
						__n_vsDelta(vs, seqp->curTime));
			}
			break;

		case (CONKER_FXMIX_EVT):
			seqp->fxmixmajor = seqp->nextEvent.msg.mix.major;
			seqp->fxmixmega = seqp->nextEvent.msg.mix.mega;

			for (vs = seqp->vAllocHead; vs != 0;) {
				if (vs->envPhase != AL_PHASE_RELEASE) {
                    n_alSynSetFXMix(&vs->voice, __n_vsMix(vs, seqp));
                }
                vs = vs->next;
			}
			break;

		case (CONKER_FXPARAM_EVT):
			if (seqp->nextEvent.msg.fx.param < 8) {
				ALFxRef fx = n_alSynGetFXRef(seqp->nextEvent.msg.fx.bus);

				if (fx) {
					n_alSynSetFXParam(fx,
							(seqp->nextEvent.msg.fx.section << 3) | (seqp->nextEvent.msg.fx.param & 7),
							&seqp->nextEvent.msg.fx.value);
				}
			} else {
				ALFxRef fx = n_alSynGetOutputLPRef(seqp->nextEvent.msg.fx.bus);

				if (fx) {
					n_alSynSetOutputLPParam(fx, seqp->nextEvent.msg.fx.param, &seqp->nextEvent.msg.fx.value);
				}
			}
			break;

        case AL_SEQP_PLAY_EVT:
            if (seqp->state != AL_PLAYING) {
                s32 previousState = seqp->state;
                ConkerNAudioSeqEvent playEvent;
                s32 deltaTicks;
                if (seqp->target) {
                    seqp->state = AL_PLAYING;
                    if (__alCSeqNextDelta(seqp->target, &deltaTicks)) {
                        playEvent.type = AL_SEQ_REF_EVT;
                        if (previousState == 3) deltaTicks = seqp->pausedDelta;
                        n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&playEvent, deltaTicks, 0);
                    }
                }
            }
            break;
        case CONKER_PAUSE_EVT:
            if (seqp->state == AL_PLAYING) {
                seqp->state = 3;
                seqp->pausedDelta = n_alEvtqFlushType(&seqp->evtq, AL_SEQ_REF_EVT);
            }
            break;

		case (CONKER_STOP_EVT):
			if (seqp->state == AL_STOPPING ) {
				for (vs = seqp->vAllocHead; vs != 0; vs = seqp->vAllocHead) {
					n_alSynStopVoice(&vs->voice);
					n_alSynFreeVoice(&vs->voice);

					if (vs->flags) {
						__n_seqpStopOsc((ConkerNAudioCSPlayer*)seqp,vs);
					}

					__n_unmapVoice((ConkerNAudioCSPlayer*)seqp, &vs->voice);
				}

				seqp->state = AL_STOPPED;
                for (chan = 0; chan < 16; chan++) {
                    if (seqp->chanState[chan].loadFailed) { }
                    if (seqp->chanState[chan].instrument) {
                        ((void (*)(ALInstrument *))seqp->drvr->callback34)(
                            seqp->bank->instArray[seqp->chanState[chan].instrumentIndex]);
                        seqp->chanState[chan].instrument = NULL;
                    }
                }

				/* alEvtqFlush(&seqp->evtq); - Don't flush event queue
				   anymore. */
				/* sct 1/3/96 - Don't overwrite nextEvent with
				   AL_SEQP_API_EVT or set nextDelta to
				   AL_USEC_PER_FRAME since we're not stopping event
				   processing. */
				/* sct 1/3/96 - Don't return here since we keep
				   processing events as usual. */
			}
			break;

		case (CONKER_STOPPING_EVT):
			if (seqp->state == AL_PLAYING || seqp->state == 3) {
				/* sct 12/29/95 - Remove events associated with the
				 * stopping sequence.  For compact sequence player,
				 * also remove all queued note off events since they
				 * are not contained in a compact sequence but are
				 * generated in response to note ons.  Note that
				 * flushing AL_SEQP_MIDI_EVTs may flush events that
				 * were posted after the call to alSeqpStop, so the
				 * application must queue these events either when
				 * the player is fully stopped, or when it is
				 * playing. */
				n_alEvtqFlushType(&seqp->evtq, AL_SEQ_REF_EVT);
				n_alEvtqFlushType(&seqp->evtq, CONKER_NOTEOFF_EVT);
				n_alEvtqFlushType(&seqp->evtq, AL_SEQP_MIDI_EVT);

				/* sct 1/3/96 - Check to see which voices need to be
				   killed and release them. */
				/* Unkilled voices should have note end events
				   occurring prior to KILL_TIME. */
				for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
					if (__n_voiceNeedsNoteKill ((ConkerNAudioCSPlayer*)seqp, &vs->voice, KILL_TIME)) {
						__n_seqpReleaseVoice((ConkerNAudioCSPlayer*)seqp, &vs->voice, KILL_TIME);
					}
				}

				for (chan = 0; chan < 16; chan++) {
					seqp->chanState[chan].fadevolcurrent = seqp->chanState[chan].fadevoltarget;

					if (seqp->chanState[chan].fadevolcurrent == 0) {
						seqp->chanMask &= (1 << chan) ^ 0xffff;
					} else {
						seqp->chanMask |= 1 << chan;
					}
				}

				seqp->state = AL_STOPPING;
				evt.type = CONKER_STOP_EVT;
				n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, AL_EVTQ_END, 0);
			}
			break;

		case (AL_SEQP_PRIORITY_EVT):
			chan = seqp->nextEvent.msg.sppriority.chan;
			seqp->chanState[chan].priority = seqp->nextEvent.msg.sppriority.priority;
			break;

		case (AL_SEQP_SEQ_EVT):
			/* Must be done playing to change sequences. */

			seqp->target = seqp->nextEvent.msg.spseq.seq;
			seqp->chanMask = 0xffff;

			if (seqp->bank) {
				__n_initFromBank((ConkerNAudioCSPlayer *)seqp, seqp->bank);
			}
			break;

		case (AL_SEQP_BANK_EVT):
			/* Must be fully stopped to change banks. */

			seqp->bank = seqp->nextEvent.msg.spbank.bank;
			__n_initFromBank((ConkerNAudioCSPlayer *)seqp, seqp->bank);
			break;

			/* sct 11/6/95 - these events should
			   now be handled by __n_CSPHandleNextSeqEvent */

		case (AL_SEQ_END_EVT):
		case (AL_TEMPO_EVT):
		case (AL_SEQ_MIDI_EVT):
			break;
		}

		seqp->nextDelta = n_alEvtqNextEvent(&seqp->evtq, (ALEvent *)&seqp->nextEvent);
	} while (seqp->nextDelta == 0);

	/*
	 * assume that next callback won't be more than half an
	 * hour away
	 */
	seqp->curTime += seqp->nextDelta;		/* sct 11/7/95 */
	return seqp->nextDelta;
}

void __n_CSPHandleNextSeqEvent(ConkerNAudioCSPlayer *seqp)
{
	ConkerNAudioSeqEvent evt;

	/* sct 1/5/96 - Do nothing if we don't have a target sequence. */
	if (seqp->target == NULL || seqp->state == 3) {
		return;
	}

	n_alCSeqNextEvent(seqp->target, (ALEvent *)&evt, 1);

	switch (evt.type) {
	case AL_SEQ_MIDI_EVT:
		__n_CSPHandleMIDIMsg(seqp, &evt);
		__n_CSPPostNextSeqEvent(seqp);
		break;

	case AL_TEMPO_EVT:
		__n_CSPHandleMetaMsg(seqp, &evt);
		__n_CSPPostNextSeqEvent(seqp);
		break;

	case AL_SEQ_END_EVT:
        seqp->state = AL_STOPPING;
        evt.type = CONKER_STOP_EVT;
        n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, AL_EVTQ_END, 0);
		break;

	case CONKER_TRACK_END:
	case CONKER_LOOPSTART:
	case CONKER_LOOPEND:
		__n_CSPPostNextSeqEvent(seqp);
		break;

	default:
		break;
	}
}

void __n_CSPHandleMIDIMsg(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event)
{
    ConkerNAudioVoice *voice;
    s32 status;
    u8 chan, key, byte1, byte2;
    ALMIDIEvent *midi = &event->msg.midi;
    ConkerNAudioSeqEvent evt;
    ALMicroTime deltaTime;
    ConkerNAudioVoiceState *vstate;
    ConkerNAudioChannel *chanstate;
    s32 oscillatorType;
    ConkerNAudioVoiceConfig config;
    ALSound *sound;
    s16 cents;
    f32 pitch, oscValue;
    u8 fxmix, filterEnable;
    ALPan pan;
    s16 vol;
    f32 filterPitch;
    void *oscState;
    ALInstrument *inst;

	status = midi->status & AL_MIDI_StatusMask;
	chan = midi->status & AL_MIDI_ChannelMask;
	byte1 = key  = midi->byte1;
	byte2 = midi->byte2;

    if (seqp->chanState[chan].loadFailed && status != AL_MIDI_ProgramChange) {
        evt.type = AL_SEQP_MIDI_EVT;
        evt.msg.midi = *midi;
        n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, 33333, 0);
        return;
    }

	switch (status) {
	case (AL_MIDI_NoteOn):

		if (byte2 != 0) /* a real note on */ {
			oscState = 0;

			/* If we're not playing, don't process note ons. */
			if (seqp->state != AL_PLAYING || (seqp->chanMask & (1 << chan)) == 0) {
				if (midi->duration) {
					evt.type = AL_SEQP_MIDI_EVT;
					evt.msg.midi.status = chan | 0x80;
					evt.msg.midi.byte1 = key;
					evt.msg.midi.byte2 = 0;

					deltaTime = seqp->uspt * midi->duration;
					__n_cspNoteDuration[chan] = deltaTime;

					n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, deltaTime, 0);
				}

				break;
			}

			chanstate = &seqp->chanState[chan];

			sound = __n_lookupSoundQuick((ConkerNAudioCSPlayer*)seqp, key, byte2, chan);
            if (!sound) break;
            if (!sound) return;

			config.standard.priority = chanstate->priority;
			config.standard.fxBus = chanstate->fxbus;
			config.standard.unityPitch = 0;
            config.releaseData = NULL;

			vstate = __n_mapVoice((ConkerNAudioCSPlayer*)seqp, key, byte2, chan);
			if (!vstate) return;

			voice = &vstate->voice;

			n_alSynAllocVoice(voice, &config);

			/*
			 * set up the voice state structure
			 */
			vstate->sound = sound;
			vstate->envPhase = AL_PHASE_ATTACK;

			if (chanstate->sustain >= 64) {
				vstate->phase = AL_PHASE_SUSTAIN;
			} else {
				vstate->phase = AL_PHASE_NOTEON;
			}

			cents = (key - sound->keyMap->keyBase) * 100 + sound->keyMap->detune;

			if (chanstate->usechanparams) {
				cents += chanstate->pitch;
			}

			vstate->pitch = alCents2Ratio(cents);

			if (chanstate->usechanparams) {
				vstate->envGain = chanstate->attackVolume;
				vstate->envEndTime = seqp->curTime + chanstate->attackTime;
			} else {
				vstate->envGain = sound->envelope->attackVolume;
				vstate->envEndTime = seqp->curTime + sound->envelope->attackTime;
			}

			/*
			 * setup tremelo and vibrato if active
			 */
			vstate->flags = 0;

			if (chanstate->usechanparams) {
				oscillatorType = chanstate->tremType;
			} else {
				inst = seqp->chanState[chan].instrument;
				oscillatorType = inst->tremType;
			}

			oscValue = 127.0f; /* set this as a default */

			if (oscillatorType) {
				if (seqp->initOsc) {
					if (chanstate->usechanparams) {
						deltaTime = ((ConkerOscInit)seqp->initOsc)(&oscState, &oscValue, chanstate->tremType,
								chanstate->tremRate, chanstate->tremDepth, chanstate->tremDelay, chanstate->timeindex);
					} else {
						deltaTime = ((ConkerOscInit)seqp->initOsc)(&oscState, &oscValue, inst->tremType,
								inst->tremRate, inst->tremDepth, inst->tremDelay, chanstate->timeindex);
					}

					if (deltaTime) /* a deltaTime of zero means don't run osc */ {
						evt.type = CONKER_TREM_EVT;
						evt.msg.osc.vs = vstate;
						evt.msg.osc.oscState = oscState;
						n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, deltaTime, 0);
						vstate->flags |= 0x01; /* set tremelo flag bit */
						vstate->oscState = oscState;
					}
				}
			}

			vstate->tremelo = (u8)oscValue;

			/* will default if not changed by initOsc */

			oscValue = 1.0f; /* set this as a default */

			if (chanstate->usechanparams) {
				oscillatorType = chanstate->vibType;
			} else {
				oscillatorType = inst->vibType;
			}

			if (oscillatorType) {
				if (seqp->initOsc) {
					if (chanstate->usechanparams) {
						deltaTime = ((ConkerOscInit)seqp->initOsc)(&oscState, &oscValue, chanstate->vibType,
								chanstate->vibRate, chanstate->vibDepth, chanstate->vibDelay, chanstate->timeindex);
					} else {
						deltaTime = ((ConkerOscInit)seqp->initOsc)(&oscState, &oscValue, inst->vibType,
								inst->vibRate, inst->vibDepth, inst->vibDelay, chanstate->timeindex);
					}

					if (deltaTime)  /* a deltaTime of zero means don't run osc. */ {
						evt.type = CONKER_VIB_EVT;
						evt.msg.osc.vs = vstate;
						evt.msg.osc.oscState = oscState;
						evt.msg.osc.chan = chan;
						n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, deltaTime, 0);
						vstate->flags |= 0x02; /* set the vibrato flag bit */
						vstate->oscState2 = oscState;
					}
				}
			}

			vstate->vibrato = oscValue; /* will default if not changed by initOsc */

			/*
			 * calculate the note on parameters
			 */
			pitch = vstate->pitch * chanstate->pitchBend * vstate->vibrato;

			fxmix = __n_vsMix(vstate, seqp);

			filterEnable = chanstate->field14;

			if (filterEnable) {
				filterPitch = 440 * alSemitones2Ratio(cents / 100 + chanstate->field15 - 64) * chanstate->pitchBend;
			} else {
				filterPitch = 127.0f;
			}

			pan = __n_vsPan(vstate, (ConkerNAudioCSPlayer*)seqp);
			vol = __n_vsVol(vstate, (ConkerNAudioCSPlayer*)seqp);

			if (chanstate->usechanparams) {
				deltaTime = chanstate->attackTime;
			} else {
				deltaTime = sound->envelope->attackTime;
			}

			n_alSynStartVoiceParams(voice, sound->wavetable,
					pitch, vol, pan, fxmix, filterEnable, filterPitch, chanstate->field16, deltaTime);

			/*
			 * set up callbacks for envelope
			 */
			evt.type = AL_SEQP_ENV_EVT;
			evt.msg.vol.voice = voice;

			if (chanstate->usechanparams) {
				evt.msg.vol.vol = chanstate->decayVolume;
				evt.msg.vol.delta = chanstate->decayTime;
			} else {
				evt.msg.vol.vol = sound->envelope->decayVolume;
				evt.msg.vol.delta = sound->envelope->decayTime;
			}

			n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, deltaTime, 0);

			if (midi->duration) {
				/*
				 * set up note off evt. if no duration don't do this
				 */
				evt.type            = CONKER_NOTEOFF_EVT;
				evt.msg.midi.status = chan | AL_MIDI_NoteOff;
				evt.msg.midi.byte1  = key;
				evt.msg.midi.byte2  = 0;   /* not needed ? */
				deltaTime = seqp->uspt * midi->duration;
				__n_cspNoteDuration[chan] = deltaTime;

				/* max time would be about one hour ten minutes */
				n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, deltaTime, 0);
			}

			if ((chanstate->field17 & 1) && seqp->field84) {
				osSendMesg(seqp->field84, (OSMesg)((__n_cspNoteDuration[chan] & 0xffffff00) | (chanstate->field17 >> 2)), OS_MESG_NOBLOCK);
			}

			break;
		}

		/*
		 * NOTE: intentional fall-through for note on with zero
		 * velocity (Should never happen with compact midi sequence,
		 * but could happen with real time midi.)
		 */

	case (AL_MIDI_NoteOff):
		vstate = __n_lookupVoice((ConkerNAudioCSPlayer*)seqp, key, chan);
		if (!vstate) return;

		chanstate = &seqp->chanState[chan];

		if (vstate->phase == AL_PHASE_SUSTAIN) {
			vstate->phase = AL_PHASE_SUSTREL;
		} else {
			vstate->phase = AL_PHASE_RELEASE;

			if (chanstate->usechanparams) {
				__n_seqpReleaseVoice((ConkerNAudioCSPlayer*)seqp, &vstate->voice, chanstate->releaseTime);
			} else {
				__n_seqpReleaseVoice((ConkerNAudioCSPlayer*)seqp, &vstate->voice, vstate->sound->envelope->releaseTime);
			}
		}

		if ((chanstate->field17 & 2) && seqp->field84) {
			osSendMesg(seqp->field84, (OSMesg)(key << 16 | 8 | chanstate->field17 >> 2), OS_MESG_NOBLOCK);
		}

		break;

	case (AL_MIDI_PolyKeyPressure):
		/*
		 * Aftertouch per key (hardwired to volume). Note that
		 * aftertouch affects only notes that are already
		 * sounding.
		 */
		vstate = __n_lookupVoice((ConkerNAudioCSPlayer*)seqp, key, chan);
		if (!vstate) return;

		vstate->velocity = byte2;
		n_alSynSetVol(&vstate->voice,
				__n_vsVol(vstate, (ConkerNAudioCSPlayer*)seqp),
				__n_vsDelta(vstate, seqp->curTime));
		break;

	case (AL_MIDI_ChannelPressure):
        { ConkerNAudioVoiceState *vs;
		/*
		 * Aftertouch per channel (hardwired to volume). Note that
		 * aftertouch affects only notes that are already
		 * sounding.
		 */
		for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
			if (vs->channel == chan) {
				vs->velocity = byte1;
				n_alSynSetVol(&vs->voice,
						__n_vsVol(vs, (ConkerNAudioCSPlayer*)seqp),
						__n_vsDelta(vs, seqp->curTime));
			}
		}
        }
		break;

    case AL_MIDI_ControlChange:
        {
            ConkerControlHandler handler;
            if (byte1 < 93) handler = __n_cspControls[byte1];
            else if (byte1 >= 252) handler = __n_cspHighControls[255 - byte1];
            else handler = NULL;
            if (handler) {
                /* Retained empty debug branches in the original control dispatch. */
                if (1) { } else if (chan == 2) { }
                handler(seqp, event, chan, byte2);
            }
        }
        break;
	case (AL_MIDI_ProgramChange):
		/* sct 1/16/96 - We must have a valid bank in order to process the program change. */
		oscillatorType = (seqp->chanState[chan].instmajor << 7) + key;

		if (oscillatorType < seqp->bank->instCount) {
            if (__n_setInstChanState(seqp, oscillatorType, chan)) {
                evt.type = AL_SEQP_MIDI_EVT;
                evt.msg.midi.ticks = 0;
                evt.msg.midi.status = chan | AL_MIDI_ProgramChange;
                evt.msg.midi.byte1 = key;
                evt.msg.midi.byte2 = 0;
                n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, 33333, 0);
            }
		} else {
			// empty
		}
		break;
	case (AL_MIDI_PitchBendChange):
		{
			s32 bendVal;
			f32 bendRatio;
			s32 cents;
            ConkerNAudioVoiceState *vs;

			/* get 14-bit unsigned midi value */
			bendVal = ((byte2 << 7) + byte1) - 8192;

			/* calculate pitch bend in cents */
			cents = seqp->chanState[chan].bendRange * bendVal / 8192;

			/* calculate the corresponding ratio  */
			bendRatio = alCents2Ratio(cents);
			seqp->chanState[chan].pitchBend = bendRatio;

			for (vs = seqp->vAllocHead; vs != 0; vs = vs->next) {
				if (vs->channel == chan) {
					n_alSynSetPitch(&vs->voice, vs->pitch * bendRatio * vs->vibrato);

					if (seqp->chanState[chan].field14) {
						n_alSynFilter13(&vs->voice, 440 * alSemitones2Ratio(vs->key - vs->sound->keyMap->keyBase + seqp->chanState[chan].field15 - 64) * bendRatio * vs->vibrato);
					}
				}
			}

		}
		break;

	default:
		break;
	}
}

void __n_CSPHandleMetaMsg(ConkerNAudioCSPlayer *seqp, ConkerNAudioSeqEvent *event)
{
	ALTempoEvent *tevt = &event->msg.tempo;
	s32 tempo;
	s32 oldUspt;
	u32 ticks;
	ALMicroTime tempDelta, curDelta = 0;
	ConkerNAudioSeqEventItem *thisNode, *nextNode, *firstTemp = 0;

	if (event->msg.tempo.status == AL_MIDI_Meta) {
		if (event->msg.tempo.type == AL_MIDI_META_TEMPO) {
			oldUspt = seqp->uspt;
			tempo = (tevt->byte1 << 16) | (tevt->byte2 <<  8) | (tevt->byte3 <<  0);
			__n_setUsptFromTempo(seqp, (f32)tempo);

			thisNode = (ConkerNAudioSeqEventItem*)seqp->evtq.allocList.next;

			while (thisNode) {
				curDelta += thisNode->delta;
				nextNode = (ConkerNAudioSeqEventItem*)thisNode->node.next;

				if (thisNode->evt.type == CONKER_NOTEOFF_EVT) {
					CONKER_AUDIO_UNLINK((ALLink*)thisNode);

					if (firstTemp) {
						CONKER_AUDIO_LINK((ALLink*)thisNode,(ALLink*)firstTemp);
					} else {
						thisNode->node.next = 0;
						thisNode->node.prev = 0;
						firstTemp = thisNode;
					}

					tempDelta = curDelta;         /* record the current delta */

					if (nextNode) {/* don't do this if no nextNode */
						curDelta -= thisNode->delta;  /* subtract out this delta */
						nextNode->delta += thisNode->delta; /* add it to next event */
					}

					thisNode->delta = tempDelta; /* set this event delta from current */
				}

				thisNode = nextNode;
			}

			thisNode = firstTemp;

			while (thisNode) {
				nextNode = (ConkerNAudioSeqEventItem*)thisNode->node.next;
				ticks = thisNode->delta/oldUspt;
				thisNode->delta = ticks * seqp->uspt;
				__n_CSPRepostEvent(&seqp->evtq,thisNode);
				thisNode = nextNode;
			}
		}
	}
}

void __n_CSPRepostEvent(ALEventQueue *evtq, ConkerNAudioSeqEventItem *item)
{
	ALLink *node;
	ConkerNAudioSeqEventItem *nextItem;


	for (node = &evtq->allocList; node != 0; node = node->next) {
		if (!node->next) {
			CONKER_AUDIO_LINK((ALLink *)item, node);
			break;
		} else {
			nextItem = (ConkerNAudioSeqEventItem *)node->next;

			if (item->delta < nextItem->delta) {
				nextItem->delta -= item->delta;
				CONKER_AUDIO_LINK((ALLink *)item, node);
				break;
			}

			item->delta -= nextItem->delta;
		}
	}

}

void __n_setUsptFromTempo(ConkerNAudioCSPlayer *seqp, f32 tempo)
{
	if (seqp->target) {
		seqp->uspt = (s32)((f32)tempo * seqp->target->qnpt);
	} else {
		seqp->uspt = 488;
	}
}

void __n_CSPPostNextSeqEvent(ConkerNAudioCSPlayer *seqp)
{
	ConkerNAudioSeqEvent evt;
	s32 deltaTicks;

	if (seqp->state != AL_PLAYING || seqp->target == NULL) {
		return;
	}

	/* Get the next event time in ticks. */
	/* If false is returned, then there is no next delta (ie. end of sequence reached). */
	if (!__alCSeqNextDelta(seqp->target, &deltaTicks)) {
		return;
	}

	evt.type = AL_SEQ_REF_EVT;
	n_alEvtqPostEvent(&seqp->evtq, (ALEvent *)&evt, deltaTicks * seqp->uspt, 0);
}
