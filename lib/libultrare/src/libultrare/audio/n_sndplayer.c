#include "n_audio_partial.h"
#include "n_audio_list.h"

/* Conker US 0x155A0:0x17870: Rare sound player with asynchronous bank
 * acquisition, reserved playback states, and chained event dispatch.
 * Static player storage remains external until its source ownership is proven.
 */
#undef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#undef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#define KEYMAP_FLAGS(m) ((m)->keyMax & 0xf0)
#define KEYMAP_FXMIX(m) (((m)->keyMax & 0xf) * 8)
#define KEYMAP_PITCHCENTS_EXACT(m) ((m)->keyBase * 100 + (m)->detune - 6000)
#define KEYMAP_PITCHCENTS_ROUGH(m) ((m)->keyBase * 100 - 6000)
#define KEYMAP_VOLINDEX(m) ((m)->keyMin & 0x1f)
#define AL_STATE4 4
#define AL_STATE5 5
#define SNDSTATEFLAG_LEAF 1
#define SNDSTATEFLAG_NO_DECAY 2
#define SNDSTATEFLAG_HAS_VOICE 4
#define SNDSTATEFLAG_PARENT_OF_LEAF 16
#define SNDSTATEFLAG_HAS_DETUNE_PITCH 32
#define AL_SNDP_PLAY_EVT 1
#define AL_SNDP_STOP_EVT 2
#define AL_SNDP_PAN_EVT 4
#define AL_SNDP_VOL_EVT 8
#define AL_SNDP_PITCH_EVT 16
#define AL_SNDP_API_EVT 32
#define AL_SNDP_DECAY_EVT 64
#define AL_SNDP_END_EVT 128
#define AL_SNDP_FX_EVT 256
#define AL_SNDP_PLAYNEXT_EVT 512
#define AL_SNDP_STOPALL_EVT 1024
#define AL_SNDP_VOLTBL_EVT 2048
#define AL_SNDP_STOP2_EVT 4096
#define AL_SNDP_FXBUS_EVT 8192
#define AL_SNDP_INIT_EVT 16384
#define AL_SNDP_FILTER11_EVT 32768

typedef struct { u8 pad00[0x10]; void *entries[1]; } ConkerSoundCache;
typedef struct { u8 pad00[0xc]; ConkerSoundCache *cache; } ConkerSoundBank;
struct sndstate {
    ALLink node;
    u8 pad08[4];
    ALSound *sound;
    ConkerNAudioVoice voice;
    f32 basepitch, pitch;
    struct sndstate **handleptr;
    ConkerSoundBank *bank;
    s32 attempts;
    s16 vol, envvol;
    ALMicroTime endtime;
    s16 soundIndex;
    u8 priority;
    ALPan pan;
    u8 fxmix, fxbus, filter11, flags, state;
    u8 pad55[3];
};
typedef struct {
    s16 type;
    union { struct { struct sndstate *sndstate; s32 data; ConkerSoundBank *data2; } generic; } msg;
} ConkerSoundMessage;
typedef union {
    ConkerSoundMessage msg;
    struct { u16 type; struct sndstate *state; u32 unk08; } common;
    struct { s16 type; struct sndstate *state; f32 pitch; } pitch;
} ConkerSoundEvent;
typedef struct { ALLink node; ALMicroTime delta; ConkerSoundMessage evt; } ConkerSoundEventItem;
typedef struct {
    ALPlayer node;
    ALEventQueue evtq;
    ConkerSoundMessage nextEvent;
    ConkerNAudioSynth *drvr;
    struct sndstate *target;
    void *sndState;
    s32 maxSounds;
    ALMicroTime frameTime, nextDelta, curTime;
    void *waveBase;
} ConkerSoundPlayer;
typedef struct { s32 maxStates, maxEvents, maxSounds; ALHeap *heap; void *waveBase; u16 maxVolumes; } ConkerSoundConfig;
extern ConkerSoundPlayer __conker_sound_player_storage;
extern s16 *g_SndpVolumeTable;
struct sndstate *g_SndpAllocStatesHead = NULL;
struct sndstate *g_SndpAllocStatesTail = NULL;
struct sndstate *g_SndpFreeStatesHead = NULL;
ConkerSoundPlayer *g_SndPlayer = &__conker_sound_player_storage;
s16 g_SndpNumPlaying = 0;

void sndp_free_state(struct sndstate *);
void sndp_free_state2(struct sndstate *);
void sndp_apply_detune_pitch(struct sndstate *);
void _removeEvents(ALEventQueue *, struct sndstate *, u16);
void _n_handleEvent(ConkerSoundEvent *);
ALMicroTime _n_sndpVoiceHandler(void *);
extern ALMicroTime __conker_runtime_sndpVoiceHandler(void *);
struct sndstate *sndp_play_sound(ConkerSoundBank *, s16, u16, ALPan, f32, u8, u8, struct sndstate **);
void n_alEvtqNew(ALEventQueue *, void *, s32);
void n_alEvtqPostEvent(ALEventQueue *, ALEvent *, ALMicroTime, s32);
ALMicroTime n_alEvtqNextEvent(ALEventQueue *, ALEvent *);
void __conker_audio_add_player_1(ALPlayer *);
s32 n_alSynAllocVoice(ConkerNAudioVoice *, ConkerNAudioVoiceConfig *);
void n_alSynStartVoiceParams(ConkerNAudioVoice *, ALWaveTable *, f32, s16, ALPan, u8, u8, f32, u8, ALMicroTime);
void n_alSynStopVoice(ConkerNAudioVoice *);
void n_alSynFreeVoice(ConkerNAudioVoice *);
void n_alSynSetVol(ConkerNAudioVoice *, s16, ALMicroTime);
void n_alSynSetPitch(ConkerNAudioVoice *, f32);
void n_alSynSetPan(ConkerNAudioVoice *, ALPan);
void n_alSynSetFXMix(ConkerNAudioVoice *, u8);
void n_alSynFilter11(ConkerNAudioVoice *, u8);
void *__conker_bank_acquire(ConkerNAudioSynth *, ALInstrument **, s32);
void __conker_bank_release(ConkerNAudioSynth *, ALInstrument *, s32);
void __conker_bank_patch_sound(ALSound *, ALInstrument *, void *);

void n_alSndpNew(ConkerSoundConfig *config)
{
	u32 i;
	void *ptr;
	ConkerSoundMessage evt;


	g_SndPlayer->maxSounds = config->maxSounds;
	g_SndPlayer->target = NULL;
    g_SndPlayer->drvr = n_syn;
	g_SndPlayer->frameTime = AL_USEC_PER_FRAME;

	ptr = alHeapAlloc(config->heap, config->maxStates, sizeof(struct sndstate));
	g_SndPlayer->sndState = ptr;
    g_SndPlayer->waveBase = config->waveBase;


	ptr = alHeapAlloc(config->heap, config->maxEvents, sizeof(ConkerSoundEventItem));
	n_alEvtqNew(&g_SndPlayer->evtq, ptr, config->maxEvents);

	g_SndpFreeStatesHead = g_SndPlayer->sndState;

	for (i = 1; i < config->maxStates; i++) {
		struct sndstate *sndstate = g_SndPlayer->sndState;
		CONKER_AUDIO_LINK(&sndstate[i].node, &sndstate[i - 1].node);
	}


	g_SndpVolumeTable = alHeapAlloc(config->heap, sizeof(s16), config->maxVolumes);

	for (i = 0; i < config->maxVolumes; i++) {
		g_SndpVolumeTable[i] = 32767;
	}


	g_SndPlayer->node.next = NULL;
	g_SndPlayer->node.handler = (ALVoiceHandler) __conker_runtime_sndpVoiceHandler;
	g_SndPlayer->node.clientData = g_SndPlayer;

	__conker_audio_add_player_1(&g_SndPlayer->node);


	evt.type = AL_SNDP_API_EVT;

	n_alEvtqPostEvent(&g_SndPlayer->evtq, (ALEvent *)&evt, g_SndPlayer->frameTime, 3);

	g_SndPlayer->nextDelta = n_alEvtqNextEvent(&g_SndPlayer->evtq, (ALEvent *)&g_SndPlayer->nextEvent);
}

ALMicroTime _n_sndpVoiceHandler(void *node)
{
	ConkerSoundPlayer *sndp = (ConkerSoundPlayer *) node;
	ConkerSoundEvent evt;

	do {
		switch (sndp->nextEvent.type) {
		case (AL_SNDP_API_EVT):
			evt.common.type = AL_SNDP_API_EVT;
			n_alEvtqPostEvent(&sndp->evtq, (ALEvent *)(ConkerSoundMessage *)&evt, sndp->frameTime, 3);
			break;

		default:
			_n_handleEvent((ConkerSoundEvent *)&sndp->nextEvent);
			break;
		}

		sndp->nextDelta = n_alEvtqNextEvent(&sndp->evtq, (ALEvent *)&sndp->nextEvent);
	} while (sndp->nextDelta == 0);

	sndp->curTime += sndp->nextDelta;

	return sndp->nextDelta;
}

void _n_handleEvent(ConkerSoundEvent *event)
{
	ConkerNAudioVoiceConfig config;
	ALSound *sound;
	ALKeyMap *keymap;
	ALPan pan;
	ConkerSoundEvent sp94;
	ConkerSoundEvent sp84;
	ALMicroTime delta;
	s32 fxmix;
	s32 vol;
	s32 tmppan;
	s32 isfull;
	s32 isspecial;
	s32 done = 1;
	s32 hasvoice = 0;
	struct sndstate *state = NULL;
	struct sndstate *nextstate = NULL;
	do {
		if (nextstate != NULL) {
			sp84.common.state = (struct sndstate *)state;
			sp84.common.type = event->common.type;
			sp84.common.unk08 = event->common.unk08;
			event = &sp84;
		}

		state = (struct sndstate *)event->common.state;

		if (state == NULL) {

		}

		sound = state->sound;

        nextstate = (struct sndstate *)state->node.next;
        if (sound == NULL && event->common.type != AL_SNDP_INIT_EVT) {
            if (state->attempts > 0) {
                if (event->common.type != AL_SNDP_PAN_EVT && event->common.type != AL_SNDP_VOL_EVT
                    && event->common.type != AL_SNDP_FX_EVT && event->common.type != AL_SNDP_PITCH_EVT
                    && event->common.type != AL_SNDP_VOLTBL_EVT && event->common.type != AL_SNDP_FXBUS_EVT) {
                    state->attempts--;
                }
                n_alEvtqPostEvent(&g_SndPlayer->evtq, (ALEvent *)&event->msg, 33333, 2);
            } else {
                sndp_free_state(state);
            }
            goto afterswitch;
        }

		switch (event->common.type) {
		case AL_SNDP_INIT_EVT:
            {
                s32 noDecay;
                if (!sound) {
                    sound = (ALSound *)__conker_bank_acquire(g_SndPlayer->drvr, (ALInstrument **)&state->bank->cache, state->soundIndex);
                    state->sound = sound;
                    if (!sound) {
                        event->common.type = AL_SNDP_INIT_EVT;
                        state->state = AL_STATE5;
                        state->attempts--;
                        n_alEvtqPostEvent(&g_SndPlayer->evtq, (ALEvent *)&event->msg, 33333, 2);
                        break;
                    }
                }
                if (sound) {
                    if ((u32)sound->envelope < 0x01000000) {
                        __conker_bank_patch_sound(sound, (ALInstrument *)sound, g_SndPlayer->waveBase);
                    }
                    if (((u32)sound->envelope & 0xff000003) != 0x80000000) break;
                    keymap = sound->keyMap;
                    state->sound = sound;
                    noDecay = sound->envelope->decayTime + 1 == 0;
                    state->priority = noDecay + 64;
                    state->flags = KEYMAP_FLAGS(keymap) | 1;
                    if (state->flags & SNDSTATEFLAG_HAS_DETUNE_PITCH) {
                        state->basepitch = alCents2Ratio(KEYMAP_PITCHCENTS_ROUGH(keymap));
                    } else {
                        state->basepitch = alCents2Ratio(KEYMAP_PITCHCENTS_EXACT(keymap));
                    }
                    if (noDecay) state->flags |= SNDSTATEFLAG_NO_DECAY;
                }
                event->common.type = AL_SNDP_PLAY_EVT;
            }
        case AL_SNDP_PLAY_EVT:
			if (state->state != AL_STATE5 && state->state != AL_STATE4) {
				return;
			}

			keymap = sound->keyMap;
            config.standard.fxBus = state->fxbus;
			config.standard.priority = state->priority;
			config.standard.unityPitch = 0;
            config.releaseData = state->bank->cache->entries[state->soundIndex];
			isfull = g_SndpNumPlaying >= g_SndPlayer->maxSounds;

			if (!isfull || (state->flags & SNDSTATEFLAG_PARENT_OF_LEAF)) {
				hasvoice = n_alSynAllocVoice(&state->voice, &config);
			}

			if (!hasvoice) {
				if (state->flags & (SNDSTATEFLAG_NO_DECAY | SNDSTATEFLAG_PARENT_OF_LEAF) || state->attempts > 0) {
					state->state = AL_STATE4;
					state->attempts--;
					n_alEvtqPostEvent(&g_SndPlayer->evtq, (ALEvent *)&event->msg, 33333, 2);
				} else {
                    sndp_free_state(state);
                }
				return;
			}


			state->flags |= SNDSTATEFLAG_HAS_VOICE;
			state->envvol = sound->envelope->attackVolume;
			state->fxbus = config.standard.fxBus;
			delta = sound->envelope->attackTime / state->pitch / state->basepitch;
			state->endtime = g_SndPlayer->curTime + delta;

			vol = MAX(0, (g_SndpVolumeTable[KEYMAP_VOLINDEX(keymap)] * (state->envvol * state->vol * sound->sampleVolume / 0x3f01)) / 32767 - 1);
			tmppan = state->pan + sound->samplePan - AL_PAN_CENTER;
			pan = MIN(MAX(tmppan, 0), 127);

			fxmix = (state->fxmix & 0x7f) + KEYMAP_FXMIX(keymap);
			fxmix = MIN(127, MAX(0, fxmix));
			fxmix |= state->fxmix & 0x80;

			__conker_bank_release(g_SndPlayer->drvr, (ALInstrument *)state->bank->cache, state->soundIndex);
            n_alSynStartVoiceParams(&state->voice, sound->wavetable, state->pitch * state->basepitch, vol, pan, fxmix, 0, 0, 0, delta);
			state->state = AL_PLAYING;
			g_SndpNumPlaying++;

			if ((state->flags & SNDSTATEFLAG_NO_DECAY) == 0) {
				if (delta == 0) {
					state->envvol =  sound->envelope->decayVolume;

					vol = MAX(0, (g_SndpVolumeTable[KEYMAP_VOLINDEX(keymap)] * (state->envvol * state->vol * sound->sampleVolume / 0x3f01)) / 32767 - 1);

					delta = sound->envelope->decayTime / state->basepitch / state->pitch;


					state->endtime = g_SndPlayer->curTime + delta;

					n_alSynSetVol(&state->voice, vol, delta);

					sp94.common.type = AL_SNDP_STOP_EVT;
					sp94.common.state = (struct sndstate *)state;

					n_alEvtqPostEvent(&g_SndPlayer->evtq, (ALEvent *)&sp94.msg, delta, 2);

					if (state->flags & SNDSTATEFLAG_HAS_DETUNE_PITCH) {
						sndp_apply_detune_pitch(state);
					}
				} else {
					sp94.common.type = AL_SNDP_DECAY_EVT;
					sp94.common.state = (struct sndstate *)state;
					delta = sound->envelope->attackTime / state->pitch / state->basepitch;


					n_alEvtqPostEvent(&g_SndPlayer->evtq, (ALEvent *)&sp94.msg, delta, 2);
				}
			}
			break;


		case AL_SNDP_STOP_EVT:
		case AL_SNDP_STOP2_EVT:
		case AL_SNDP_STOPALL_EVT:
			if (event->common.type != AL_SNDP_STOP2_EVT || (state->flags & SNDSTATEFLAG_NO_DECAY)) {
				switch (state->state) {
				case AL_PLAYING:
					_removeEvents(&g_SndPlayer->evtq, (struct sndstate *)state, AL_SNDP_DECAY_EVT);
                    if (0) {
                        osSyncPrintf("snd %d has been freed too early - %d\n\n\n\n\n", state->state, state->state);
                        osSyncPrintf("-2 sound has been freed too early - %d\n\n\n\n\n", state->state);
                    }
					delta = sound->envelope->releaseTime / state->basepitch / state->pitch;


					n_alSynSetVol(&state->voice, 0, delta);

					if (delta) {
						sp94.common.type = AL_SNDP_END_EVT;
						sp94.common.state = (struct sndstate *)state;
						n_alEvtqPostEvent(&g_SndPlayer->evtq, (ALEvent *)&sp94.msg, delta, 2);
						state->state = AL_STOPPING;
					} else {
						sndp_free_state(state);
					}
					break;
				case AL_STATE4:
				case AL_STATE5:
					sndp_free_state(state);
					break;
				default:
					break;
				}

				if (event->common.type == AL_SNDP_STOP_EVT) {
					event->common.type = AL_SNDP_STOP2_EVT;
				}
			}
			break;

		case AL_SNDP_PAN_EVT:
			state->pan = event->common.unk08;

			if (state->state == AL_PLAYING) {
				tmppan = state->pan + sound->samplePan - AL_PAN_CENTER;
				pan = MIN(MAX(tmppan, AL_PAN_LEFT), AL_PAN_RIGHT);

				n_alSynSetPan(&state->voice, pan);
			}
			break;
		case AL_SNDP_PITCH_EVT:
			state->pitch = event->pitch.pitch;

			if (state->state == AL_PLAYING) {
				n_alSynSetPitch(&state->voice, state->pitch * state->basepitch);

				if (state->flags & SNDSTATEFLAG_HAS_DETUNE_PITCH) {
					sndp_apply_detune_pitch(state);
				}
			}
			break;
		case AL_SNDP_FX_EVT:
            keymap = sound->keyMap;
			state->fxmix = event->common.unk08;

			if (state->state == AL_PLAYING) {
				fxmix = (state->fxmix & 0x7f) + KEYMAP_FXMIX(keymap);
				fxmix = MIN(127, MAX(0, fxmix));
				fxmix |= state->fxmix & 0x80;

				n_alSynSetFXMix(&state->voice, fxmix);
			}
			break;
		case AL_SNDP_FXBUS_EVT:
			state->fxbus = event->common.unk08;

			if (state->fxbus >= n_syn->maxAuxBusses) {
				state->fxbus = 0;
			}

			if (state->state == AL_PLAYING) {
				state->voice.fxBus = state->fxbus;
			}
			break;
		case AL_SNDP_VOL_EVT:
            keymap = sound->keyMap;
			state->vol = event->common.unk08;

			if (state->state == AL_PLAYING) {
				vol = MAX(0, (g_SndpVolumeTable[KEYMAP_VOLINDEX(keymap)] * (state->envvol * state->vol * sound->sampleVolume / 0x3f01)) / 32767 - 1);

				n_alSynSetVol(&state->voice, vol, MAX(1000, state->endtime - g_SndPlayer->curTime));
			}
			break;
		case AL_SNDP_VOLTBL_EVT:
            keymap = sound->keyMap;
			if (state->state == AL_PLAYING) {
				delta = sound->envelope->releaseTime / state->basepitch / state->pitch;


				vol = MAX(0, g_SndpVolumeTable[KEYMAP_VOLINDEX(keymap)] * (state->envvol * state->vol * sound->sampleVolume / 0x3f01) / 32767 - 1);

				n_alSynSetVol(&state->voice, vol, delta);
			}
			break;
		case AL_SNDP_DECAY_EVT:
			if ((state->flags & SNDSTATEFLAG_NO_DECAY) == 0) {
				keymap = sound->keyMap;
                state->envvol = sound->envelope->decayVolume;
				vol = MAX(0, g_SndpVolumeTable[KEYMAP_VOLINDEX(keymap)] * (state->envvol * state->vol * sound->sampleVolume / 0x3f01) / 32767 - 1);
				delta = sound->envelope->decayTime / state->basepitch / state->pitch;


				state->endtime = g_SndPlayer->curTime + delta;

				n_alSynSetVol(&state->voice, vol, delta);

				sp94.common.type = AL_SNDP_STOP_EVT;
				sp94.common.state = (struct sndstate *)state;

				n_alEvtqPostEvent(&g_SndPlayer->evtq, (ALEvent *)&sp94.msg, delta, 2);

				if (state->flags & SNDSTATEFLAG_HAS_DETUNE_PITCH) {
					sndp_apply_detune_pitch(state);
				}
			}
			break;
		case AL_SNDP_END_EVT:
			sndp_free_state(state);
			break;
		case AL_SNDP_PLAYNEXT_EVT:
			if (state->flags & SNDSTATEFLAG_PARENT_OF_LEAF) {
				sndp_play_sound(event->msg.msg.generic.data2, event->msg.msg.generic.data, state->vol, state->pan,
						state->pitch, state->fxmix, state->fxbus, state->handleptr);
			}
			break;
        case AL_SNDP_FILTER11_EVT:
            state->filter11 = event->common.unk08;
            if (state->state == AL_PLAYING) n_alSynFilter11(&state->voice, state->filter11);
            break;
		default:
			break;
		}

afterswitch:
		isspecial = event->common.type
			& (AL_SNDP_PLAY_EVT | AL_SNDP_PITCH_EVT | AL_SNDP_DECAY_EVT | AL_SNDP_END_EVT | AL_SNDP_PLAYNEXT_EVT | AL_SNDP_INIT_EVT);

		if ((state = nextstate) && !isspecial) {
			done = state->flags & SNDSTATEFLAG_LEAF;
		}
	} while (!done && state && !isspecial);
}

void sndp_free_state(struct sndstate *state)
{
	if (state->flags & SNDSTATEFLAG_HAS_VOICE) {
		n_alSynStopVoice(&state->voice);
		n_alSynFreeVoice(&state->voice);
	}

	sndp_free_state2(state);


	_removeEvents(&g_SndPlayer->evtq, (struct sndstate *)state, 0xffff);
}

void sndp_apply_detune_pitch(struct sndstate *state)
{
	ConkerSoundEvent evt;
	f32 pitch = alCents2Ratio(state->sound->keyMap->detune) * state->pitch;

	evt.common.type = AL_SNDP_PITCH_EVT;
	evt.common.state = (struct sndstate *)state;
	evt.common.unk08 = *(u32 *)&pitch;

	n_alEvtqPostEvent(&g_SndPlayer->evtq, (ALEvent *)&evt.msg, 33333, 2);
}

void _removeEvents(ALEventQueue *evtq, struct sndstate *state, u16 typemask)
{
	ALLink            *thisNode;
	ALLink            *nextNode;
	ConkerSoundEventItem *thisItem;
	ConkerSoundEventItem *nextItem;
	ConkerSoundEvent     *thisEvent;
	OSIntMask         mask;

	mask = osSetIntMask(OS_IM_NONE);

	thisNode = evtq->allocList.next;

	while (thisNode != 0) {
		nextNode = thisNode->next;
		thisItem = (ConkerSoundEventItem *)thisNode;
		nextItem = (ConkerSoundEventItem *)nextNode;
		thisEvent = (ConkerSoundEvent *) &thisItem->evt;

		if (thisEvent->common.state == state && thisEvent->common.type & typemask) {
			if (nextItem) {
				nextItem->delta += thisItem->delta;
			}

			CONKER_AUDIO_UNLINK(thisNode);
			CONKER_AUDIO_LINK(thisNode, &evtq->freeList);
		}

		thisNode = nextNode;
	}

	osSetIntMask(mask);
}

struct sndstate *sndp_alloc_state(ConkerSoundBank *bank, s16 soundIndex)
{
	struct sndstate *state;
	OSIntMask mask;

	mask = osSetIntMask(1);
	state = g_SndpFreeStatesHead;

	if (state != NULL) {
		g_SndpFreeStatesHead = (struct sndstate *)state->node.next;

		CONKER_AUDIO_UNLINK(&state->node);

		if (g_SndpAllocStatesHead) {
			state->node.next = &g_SndpAllocStatesHead->node;
			state->node.prev = NULL;
			g_SndpAllocStatesHead->node.prev = &state->node;
			g_SndpAllocStatesHead = state;
		} else {
			state->node.next = state->node.prev = NULL;
			g_SndpAllocStatesHead = state;
			g_SndpAllocStatesTail = state;
		}

		osSetIntMask(mask);

        state->sound = NULL;
        state->soundIndex = soundIndex;
        state->bank = bank;
        state->priority = 64;
        state->state = AL_STATE5;
        state->attempts = 2;
        state->flags = 0;
        state->handleptr = NULL;
        state->basepitch = 1.0f;

	} else {
		osSetIntMask(mask);
	}

	return state;
}

void sndp_free_state2(struct sndstate *state)
{

	if (g_SndpAllocStatesHead == state) {
		g_SndpAllocStatesHead = (struct sndstate *)state->node.next;
	}

	if (g_SndpAllocStatesTail == state) {
		g_SndpAllocStatesTail = (struct sndstate *)state->node.prev;
	}

	CONKER_AUDIO_UNLINK(&state->node);

	if (g_SndpFreeStatesHead) {
		state->node.next = &g_SndpFreeStatesHead->node;
		state->node.prev = NULL;
		g_SndpFreeStatesHead->node.prev = &state->node;
		g_SndpFreeStatesHead = state;
	} else {
		state->node.next = state->node.prev = NULL;
		g_SndpFreeStatesHead = state;
	}

	if (state->flags & SNDSTATEFLAG_HAS_VOICE) {
		g_SndpNumPlaying--;
	}

	state->state = AL_STOPPED;

	if (state->handleptr) {
		if (*state->handleptr == state) {
			*state->handleptr = 0;
		}

		state->handleptr = NULL;
	}

}

s32 sndp_get_state(struct sndstate **handle)
{
    s32 result = 0;
    u32 mask;
    if (*handle) {
        mask = __osDisableInt();
        if (*handle) result = (*handle)->state;
        __osRestoreInt(mask);
    }
    return result;
}

struct sndstate *sndp_play_sound(ConkerSoundBank *bank, s16 soundnum, u16 vol, ALPan pan, f32 pitch, u8 fxmix, u8 fxbus, struct sndstate **handleptr)
{
    struct sndstate *state;
    struct sndstate *leafstate = NULL;
    s16 prevsoundnum = 0;
    s32 thisdelay;
    ConkerSoundMessage evt;
    if (soundnum != 0) {
        do {
            state = sndp_alloc_state(bank, soundnum - 1);
            if (state != NULL) {
                g_SndPlayer->target = state;
                evt.type = AL_SNDP_INIT_EVT;
                evt.msg.generic.sndstate = state;
                state->pan = pan;
                state->vol = vol;
                state->pitch = pitch;
                state->fxmix = fxmix;
                state->fxbus = fxbus;
                thisdelay = 0;
                n_alEvtqPostEvent(&g_SndPlayer->evtq, (ALEvent *)&evt, thisdelay + 1, 2);
                leafstate = state;
            }
            soundnum = 0;
        } while (soundnum && state);
        if (leafstate != NULL) {
            leafstate->flags |= SNDSTATEFLAG_LEAF;
            leafstate->handleptr = handleptr;
            if (prevsoundnum != 0) { }
        }
    }
    if (handleptr != NULL) *handleptr = leafstate;
    return leafstate;
}

void sndp_stop_sound(struct sndstate *state)
{
	ConkerSoundMessage evt;

	if (state != NULL) {
        evt.type = AL_SNDP_STOPALL_EVT;
        evt.msg.generic.sndstate = state;
		evt.msg.generic.sndstate->flags &= ~SNDSTATEFLAG_PARENT_OF_LEAF;

		n_alEvtqPostEvent(&g_SndPlayer->evtq, (ALEvent *)&evt, 0, 2);
	}
}

void sndp_post_stopall_event_bulk(u8 flags)
{
	OSIntMask mask = osSetIntMask(1);
	ConkerSoundMessage evt;
	struct sndstate *state = g_SndpAllocStatesHead;

	while (state) {
		evt.type = AL_SNDP_STOPALL_EVT;
		evt.msg.generic.sndstate = state;

		if ((state->flags & flags) == flags) {
			evt.msg.generic.sndstate->flags &= ~SNDSTATEFLAG_PARENT_OF_LEAF;
			n_alEvtqPostEvent(&g_SndPlayer->evtq, (ALEvent *)&evt, 0, 2);
		}

		state = (struct sndstate *)state->node.next;
	}

	osSetIntMask(mask);
}

void sndp_stop_all(void)
{
	sndp_post_stopall_event_bulk(SNDSTATEFLAG_LEAF);
}

void sndp_stop_nodecays(void)
{
	sndp_post_stopall_event_bulk(SNDSTATEFLAG_LEAF | SNDSTATEFLAG_NO_DECAY);
}

void sndp_post_event(struct sndstate *state, s16 type, s32 data)
{
	ConkerSoundMessage evt;

	if (state) {
    evt.type = type;
	evt.msg.generic.sndstate = state;
	evt.msg.generic.data = data;

		n_alEvtqPostEvent(&g_SndPlayer->evtq, (ALEvent *)&evt, 0, 2);
	}
}

void sndp_set_volume_entry(u8 index, u16 volume)
{
		OSIntMask mask = osSetIntMask(1);
		struct sndstate *state = g_SndpAllocStatesHead;
		s32 i;
		ConkerSoundMessage evt;

		g_SndpVolumeTable[index] = volume;

		for (i = 0; state != NULL; i++, state = (struct sndstate *)state->node.next) {
			if (state->sound && KEYMAP_VOLINDEX(state->sound->keyMap) == index) {
				evt.type = AL_SNDP_VOLTBL_EVT;
				evt.msg.generic.sndstate = state;
				n_alEvtqPostEvent(&g_SndPlayer->evtq, (ALEvent *)&evt, 0, 2);
			}
		}

		osSetIntMask(mask);
}
