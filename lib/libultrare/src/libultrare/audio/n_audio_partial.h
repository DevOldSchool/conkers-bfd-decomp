#ifndef CONKER_N_AUDIO_PARTIAL_H
#define CONKER_N_AUDIO_PARTIAL_H
#include <PR/os_internal.h>
#include <PR/libaudio.h>
#include <PR/abi.h>

/* Conker field views. Unknown members retain explicit padding; allocation
 * extents used by the synthesizer are independently verified against the ROM.
 */
typedef struct {
    s16 frequency;
    s16 amount;
    s32 state;
    s16 coefficients[16];
    s32 first;
    POLEF_STATE *stateLeft;
    POLEF_STATE *stateRight;
    u8 pad34[4];
} ConkerNAudioOutputLP;

typedef struct {
    u8 pad00[4];
    Acmd *(*handler)(s32, Acmd *, s32);
    u8 pad08[0xC];
} ConkerNAudioMainBus;

typedef struct ConkerNAudioParam ConkerNAudioParam;

typedef struct {
    s32 maxVVoices;
    s32 maxPVoices;
    s32 maxUpdates;
    s32 maxFXbusses;
    ALDMANew dmaproc;
    void *callback14;
    void (*release)(void *);
    void *callback1C;
    void *callback20;
    void *callback24;
    ALHeap *heap;
    s32 outputRate;
    u8 fxTypes[2];
    u8 pad32[2];
    s32 *params[2];
} ConkerNAudioConfig;

typedef struct {
    u8 pad00[0x14];
    ALLink sources;
    ALFxRef primaryFx;
    ALFxRef fx;
    u8 pad24[0x1C];
    ConkerNAudioOutputLP *outputLP;
} ConkerNAudioAuxBus;

typedef struct {
    ALPlayer *head;
    ALLink pFreeList;
    ALLink pAllocList;
    ALLink pLameList;
    s32 paramSamples;
    u32 curSamples;
    ALDMANew dma;
    void *callback28;
    void (*release)(void *);
    void *callback30;
    void *callback34;
    void *callback38;
    ALHeap *heap;
    ConkerNAudioParam *paramList;
    ConkerNAudioMainBus *mainBus;
    ConkerNAudioAuxBus *auxBus;
    s32 numPVoices;
    s32 maxAuxBusses;
    s32 outputRate;
    s32 maxOutSamples;
} ConkerNAudioSynth;
extern ConkerNAudioSynth *n_syn;

typedef struct ConkerNAudioVoice ConkerNAudioVoice;

typedef struct {
    s16 frequency;
    s16 amount;
    s32 state;
    s16 coefficients[16];
} ConkerNAudioCoefficients;

typedef struct {
    ALLink node;
    ALLink auxNode;
    ConkerNAudioVoice *vvoice;
    ADPCM_STATE *dc_state;
    ADPCM_STATE *dc_lstate;
    ALRawLoop dc_loop;
    ALWaveTable *dc_table;
    s32 dc_bookSize;
    ALDMAproc dc_dma;
    void *dc_dmaState;
    s32 dc_sample;
    s32 dc_lastsam;
    s32 dc_first;
    u32 dc_memin;
    RESAMPLE_STATE *rs_state;
    f32 rs_ratio;
    s32 rs_upitch;
    f32 rs_delta;
    s32 rs_first;
    ENVMIX_STATE *em_state;
    s16 em_pan;
    s16 em_volume;
    s16 em_cvolL;
    s16 em_cvolR;
    s16 em_dryamt;
    s16 em_wetamt;
    u16 em_lratl;
    s16 em_lratm;
    s16 em_ltgt;
    u16 em_rratl;
    s16 em_rratm;
    s16 em_rtgt;
    s32 em_delta;
    s32 em_segEnd;
    s32 em_first;
    ConkerNAudioParam *em_ctrlList;
    ConkerNAudioParam *em_ctrlTail;
    s32 em_motion;
    s32 offset;
    u8 pad94[5];
    u8 flags99;
    u8 pad9A[6];
    ConkerNAudioCoefficients fx;
    s32 filterState;
    void *filterBuffer;
} ConkerNAudioPVoice;

struct ConkerNAudioVoice {
    u8 pad00[8];
    ConkerNAudioPVoice *pvoice;
    ALWaveTable *table;
    void *clientPrivate;
    void *releaseData;
    s16 state;
    s16 priority;
    s16 fxBus;
    s16 unityPitch;
};

typedef struct {
    ALVoiceConfig standard;
    void *releaseData;
} ConkerNAudioVoiceConfig;

struct ConkerNAudioParam {
    struct ConkerNAudioParam *next;
    s32 delta;
    s16 type;
    union { f32 f; s32 i; } data;
    union { f32 f; s32 i; } moredata;
    u8 pad14[0x10];
};

typedef struct {
    ConkerNAudioParam *next;
    s32 delta;
    s16 type;
    ConkerNAudioPVoice *pvoice;
} ConkerNAudioFreeParam;

typedef struct {
    ALInstrument *instrument;
    s16 bendRange;
    ALPan pan;
    u8 priority;
    u8 instmajor;
    u8 vol;
    u8 fxmix;
    u8 fxbus;
    u8 sustain;
    u8 fadevolcurrent;
    u8 fadevoltarget;
    u8 fadevolinc;
    f32 fadeStep;
    u8 field14;
    u8 field15;
    u8 field16;
    u8 field17;
    f32 pitchBend;
    ALMicroTime attackTime;
    ALMicroTime decayTime;
    ALMicroTime releaseTime;
    u8 usechanparams;
    u8 attackVolume;
    u8 decayVolume;
    s8 pitch;
    u8 tremType, tremRate, tremDepth, tremDelay;
    u8 vibType, vibRate, vibDepth, vibDelay;
    u8 field34;
    u8 timeindex;
    u8 loadFailed;
    u8 pad37;
    s16 instrumentIndex;
    u8 pad3A[2];
} ConkerNAudioChannel;

typedef struct ConkerNAudioVoiceState ConkerNAudioVoiceState;
struct ConkerNAudioVoiceState {
    ConkerNAudioVoiceState *next;
    ConkerNAudioVoice voice;
    ALSound *sound;
    ALMicroTime envEndTime;
    f32 pitch;
    f32 vibrato;
    u8 envGain, channel, key, velocity;
    u8 envPhase, phase, tremelo, flags;
    void *oscState;
    void *oscState2;
};

typedef struct {
    s16 type;
    union {
        ALMIDIEvent midi;
        ALTempoEvent tempo;
        ALSeqpLoopEvent loop;
        ALSeqpVolEvent spvol;
        ALSeqpPriorityEvent sppriority;
        ALSeqpSeqEvent spseq;
        ALSeqpBankEvent spbank;
        struct { f32 major, mega; } mix;
        struct { u8 bus, param, section; s32 value; } fx;
        struct { ConkerNAudioVoice *voice; } note;
        struct { ConkerNAudioVoice *voice; ALMicroTime delta; u8 vol; } vol;
        struct { ConkerNAudioVoiceState *vs; void *oscState; u8 chan; } osc;
    } msg;
} ConkerNAudioSeqEvent;

typedef struct {
    u16 type;
    union {
        ALMIDIEvent midi;
        ALTempoEvent tempo;
        ALSeqpLoopEvent loop;
        ALSeqpVolEvent spvol;
        ALSeqpPriorityEvent sppriority;
        ALSeqpSeqEvent spseq;
        ALSeqpBankEvent spbank;
        struct { f32 major, mega; } mix;
        struct { u8 bus, param, section; s32 value; } fx;
        struct { ConkerNAudioVoice *voice; } note;
        struct { ConkerNAudioVoice *voice; ALMicroTime delta; u8 vol; } vol;
        struct { ConkerNAudioVoiceState *vs; void *oscState; u8 chan; } osc;
    } msg;
} ConkerNAudioNextSeqEvent;
typedef struct {
    ALPlayer node;
    ConkerNAudioSynth *drvr;
    ALCSeq *target;
    ALMicroTime curTime;
    ALBank *bank;
    s32 uspt;
    s32 nextDelta;
    s32 state;
    u16 chanMask;
    s16 vol;
    u8 maxChannels;
    u8 debugFlags;
    u8 field36;
    u8 pad37;
    ConkerNAudioNextSeqEvent nextEvent;
    ALEventQueue evtq;
    s32 frameTime;
    ConkerNAudioChannel *chanState;
    ConkerNAudioVoiceState *vAllocHead;
    ConkerNAudioVoiceState *vAllocTail;
    ConkerNAudioVoiceState *vFreeList;
    ALOscInit initOsc;
    ALOscUpdate updateOsc;
    ALOscStop stopOsc;
    f32 fxmixmajor;
    f32 fxmixmega;
    void *field84;
    ALMicroTime pausedDelta;
    u8 voicelimit;
    u8 voicecount;
} ConkerNAudioCSPlayer;

typedef struct {
    ConkerNAudioParam *next;
    s32 delta;
    s16 type;
    s16 unity;
    f32 pitch;
    s16 volume;
    ALPan pan;
    u8 fxMix;
    u8 filter11;
    u8 filter12;
    f32 filter13;
    s32 samples;
    ALWaveTable *wave;
} ConkerNAudioStartParam;

extern void n_alCSPSendMidi(ConkerNAudioCSPlayer *, s32, u8, u8, u8);
extern ConkerNAudioParam *__n_allocParam(void);
extern s32 _n_timeToSamples(ALMicroTime time);
extern s32 n_alEnvmixerParam(ConkerNAudioPVoice *voice, s32 param, void *value);
extern void _n_freePVoice(ConkerNAudioPVoice *voice);
extern void n_alEvtqPostEvent(ALEventQueue *queue, ALEvent *event,
                            ALMicroTime delta, s32 flags);
extern void n_alFxNew(ALFxRef *fx, ConkerNAudioConfig *config, s16 bus, ALHeap *heap);
#endif
