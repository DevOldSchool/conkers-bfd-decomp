#include "n_audio_partial.h"
#include "n_audio_list.h"

/* Conker's synthesizer family at US 0x18E60:0x19AB0. Allocation sizes,
 * callback slots, linked bus membership and command emission are ROM-derived.
 */
extern ALFxRef n_alSynAllocFX(s16, ConkerNAudioConfig *, ALHeap *);
extern Acmd *__conker_audio_fx_pull(s32, Acmd *, s32);
extern void alN_PVoiceNew(ConkerNAudioPVoice *, ALDMANew, ALHeap *);
extern Acmd *n_alMainBusPull(s32, Acmd *);
void _n_collectPVoices(void);
s32 __n_nextSampleTime(ALPlayer **);
s32 _n_timeToSamplesNoRound(s32);

void n_alSynNew(ConkerNAudioConfig *c)
{
    s32 i;
    s32 j;
    ConkerNAudioPVoice *pv;
    ConkerNAudioPVoice *pvoices;
    ALHeap *hp = c->heap;
    ConkerNAudioParam *params;
    ConkerNAudioParam *paramPtr;

    n_syn->head = 0;
    n_syn->numPVoices = c->maxPVoices;
    n_syn->curSamples = 0;
    n_syn->paramSamples = 0;
    n_syn->outputRate = c->outputRate;
    n_syn->maxOutSamples = 184;
    n_syn->dma = c->dmaproc;
    n_syn->callback28 = c->callback14;
    n_syn->release = c->release;
    n_syn->callback30 = c->callback1C;
    n_syn->callback34 = c->callback20;
    n_syn->callback38 = c->callback24;
    if (c->maxFXbusses > 2) {
        n_syn->maxAuxBusses = 2;
    } else if (c->maxFXbusses < 1) {
        n_syn->maxAuxBusses = 1;
    } else {
        n_syn->maxAuxBusses = c->maxFXbusses;
    }
    n_syn->auxBus = alHeapAlloc(hp, n_syn->maxAuxBusses, sizeof(ConkerNAudioAuxBus));
    for (i = 0; i < n_syn->maxAuxBusses; i++) {
        n_syn->auxBus[i].sources.next = 0;
        n_syn->auxBus[i].sources.prev = 0;
        if (c->fxTypes[i]) {
            n_syn->auxBus[i].primaryFx = n_alSynAllocFX(i, c, hp);
        } else {
            n_syn->auxBus[i].primaryFx = 0;
        }
        n_syn->auxBus[i].outputLP = alHeapAlloc(hp, 1, sizeof(ConkerNAudioOutputLP));
        n_syn->auxBus[i].outputLP->amount = 0;
        n_syn->auxBus[i].outputLP->stateLeft = alHeapAlloc(hp, 1, sizeof(POLEF_STATE));
        n_syn->auxBus[i].outputLP->stateRight = alHeapAlloc(hp, 1, sizeof(POLEF_STATE));
    }
    n_syn->mainBus = alHeapAlloc(hp, 1, sizeof(ConkerNAudioMainBus));
    n_syn->mainBus->handler = __conker_audio_fx_pull;
    n_syn->pFreeList.next = 0;
    n_syn->pFreeList.prev = 0;
    n_syn->pLameList.next = 0;
    n_syn->pLameList.prev = 0;
    n_syn->pAllocList.next = 0;
    n_syn->pAllocList.prev = 0;
    pvoices = alHeapAlloc(hp, c->maxPVoices, sizeof(ConkerNAudioPVoice));
    for (i = 0; i < c->maxPVoices; i++) {
        pv = &pvoices[i];
        CONKER_AUDIO_LINK((ALLink *)pv, &n_syn->pFreeList);
        pv->vvoice = 0;
        alN_PVoiceNew(pv, n_syn->dma, hp);
    }
    for (j = 0; j < n_syn->maxAuxBusses; j++) {
        n_syn->auxBus[j].sources.next = 0;
        n_syn->auxBus[j].sources.prev = 0;
    }
    params = alHeapAlloc(hp, c->maxUpdates, sizeof(ConkerNAudioParam));
    n_syn->paramList = 0;
    for (i = 0; i < c->maxUpdates; i++) {
        paramPtr = &params[i];
        paramPtr->next = n_syn->paramList;
        n_syn->paramList = paramPtr;
    }
    n_syn->heap = hp;
}

Acmd *n_alAudioFrame(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen)
{
    ALPlayer *client;
    Acmd *cmdlEnd = cmdList;
    s32 nOut;
    s16 *lOutBuf = outBuf;

    if (n_syn->head == 0) {
        *cmdLen = 0;
        return cmdList;
    }
    for (n_syn->paramSamples = __n_nextSampleTime(&client);
         n_syn->paramSamples - n_syn->curSamples < outLen;
         n_syn->paramSamples = __n_nextSampleTime(&client)) {
        n_syn->paramSamples &= ~0xf;
        client->samplesLeft += _n_timeToSamplesNoRound((*client->handler)(client));
    }
    n_syn->paramSamples &= ~0xf;
    while (outLen > 0) {
        nOut = n_syn->maxOutSamples < outLen ? n_syn->maxOutSamples : outLen;
        cmdlEnd = n_alMainBusPull(n_syn->curSamples, cmdlEnd);
        {
            Acmd *cmd = cmdlEnd++;
            cmd->words.w0 = 0x0D000000; /* Interleave fixed stereo buffers. */
        }
        {
            Acmd *cmd = cmdlEnd++;
            cmd->words.w0 = 0x062E0000; /* Save 184 stereo samples. */
            cmd->words.w1 = (u32)lOutBuf;
        }
        outLen -= nOut;
        lOutBuf += nOut << 1;
        n_syn->curSamples += nOut;
    }
    *cmdLen = (s32)(cmdlEnd - cmdList);
    _n_collectPVoices();
    return cmdlEnd;
}

ConkerNAudioParam *__n_allocParam(void)
{
    ConkerNAudioParam *update = 0;
    if (n_syn->paramList) {
        update = n_syn->paramList;
        n_syn->paramList = n_syn->paramList->next;
        update->next = 0;
    }
    return update;
}

void _n_freeParam(ConkerNAudioParam *param)
{
    param->next = n_syn->paramList;
    n_syn->paramList = param;
}

void _n_collectPVoices(void)
{
    ALLink *dl;
    while ((dl = n_syn->pLameList.next) != 0) {
        CONKER_AUDIO_UNLINK(dl);
        CONKER_AUDIO_LINK(dl, &n_syn->pFreeList);
        CONKER_AUDIO_UNLINK(&((ConkerNAudioPVoice *)dl)->auxNode);
        ((ConkerNAudioPVoice *)dl)->auxNode.next = 0;
        ((ConkerNAudioPVoice *)dl)->auxNode.prev = 0;
    }
}

void _n_freePVoice(ConkerNAudioPVoice *pvoice)
{
    CONKER_AUDIO_UNLINK((ALLink *)pvoice);
    CONKER_AUDIO_LINK((ALLink *)pvoice, &n_syn->pLameList);
}

s32 _n_timeToSamplesNoRound(s32 micros)
{
    f32 tmp = ((f32)micros) * n_syn->outputRate / 1000000.0f + 0.5f;
    return (s32)tmp;
}

s32 _n_timeToSamples(s32 micros)
{
    return _n_timeToSamplesNoRound(micros) & ~0xf;
}

s32 __n_nextSampleTime(ALPlayer **client)
{
    ALMicroTime delta = 0x7fffffff;
    ALPlayer *cl;
    *client = 0;
    for (cl = n_syn->head; cl != 0; cl = cl->next) {
        if ((cl->samplesLeft - n_syn->curSamples) < delta) {
            *client = cl;
            delta = cl->samplesLeft - n_syn->curSamples;
        }
    }
    return (*client)->samplesLeft;
}
