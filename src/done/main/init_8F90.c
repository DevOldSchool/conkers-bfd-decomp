#include "types.h"
#include "libultra_os.h"
#include "../lib/ultralib/include/PR/abi.h"

/*
 * Reviewed source unit: src/main/init_8F90.c
 * Boundary evidence: docs/evidence/boundaries/main/main_audio_driver_sequence_boundaries.md
 */

typedef struct AudioBufferState {
    struct AudioBufferState *next;
    struct AudioBufferState *prev;
    s32 savedValue;
    s32 *ownerSlot;
    void *buffer;
    s8 count;
    u8 state;
    u8 field16;
} AudioBufferState;

typedef struct {
    u8 initialized;
    u8 pad1[3];
    AudioBufferState *active;
    void *base;
    AudioBufferState *pending;
    AudioBufferState *freeAnchor;
} AudioBankManager;

extern AudioBankManager D_800406A0;

typedef struct AudioTaskRecord AudioTaskRecord;
typedef s32 (*ALDMAproc)(s32 addr, s32 len, void *state);
typedef void *(*ConkerBankFetch)(void *, s32);
typedef struct {
    s16 type;
    u8 pad2[2];
    AudioTaskRecord *record;
} AudioCompletionMessage;
typedef struct {
    u32 type;
    u32 flags;
    void *boot;
    u32 bootSize;
    void *microcode;
    u32 microcodeSize;
    void *microcodeData;
    u32 microcodeDataSize;
    void *stack;
    u32 stackSize;
    void *output;
    void *outputSize;
    Acmd *commands;
    u32 commandSize;
    void *yieldData;
    u32 yieldSize;
} AudioRspTask;

typedef struct {
    void *next;
    u8 pad4[8];
    u32 flags;
    void *framebuffer;
    u8 pad14[4];
    AudioRspTask task;
    OSMesgQueue *completionQueue;
    void *completionMessage;
} AudioSchedulerTask;

struct AudioTaskRecord {
    u8 *buffer;
    u8 *adjustedBuffer;
    s16 samples;
    u8 padA[6];
    AudioSchedulerTask scheduler;
    AudioCompletionMessage completion;
};

typedef struct AudioDmaNode {
    struct AudioDmaNode *next;
    struct AudioDmaNode *prev;
    u32 address;
    u32 frame;
    u8 *buffer;
} AudioDmaNode;

typedef struct AudioHeap AudioHeap;
typedef struct ThreadState ThreadState;

typedef struct {
    s32 maxVoices;
    s32 maxPhysicalVoices;
    s32 maxUpdates;
    s32 maxFxBuses;
    ALDMAproc (*dma)(void *);
    ConkerBankFetch (*fetch)(void);
    void (*release)(void *);
    void (*retain)(void *);
    void (*releaseNow)(void *);
    void *waveBase;
    AudioHeap *heap;
    s32 outputRate;
    u8 fxTypes[2];
    u8 pad32[2];
    s32 *params[2];
} AudioDriverConfig;

typedef struct {
    u32 frequency;
    u32 frames;
    s32 maxCommands;
} AudioDeviceConfig;

typedef struct {
    s32 values[2][66];
} AudioEffectParameters;

void func_80012588(s32);
void *func_80012844(u8 *, s32, AudioHeap *, s32, s32);
void func_80018DA0(void *, AudioDriverConfig *);
void func_80022A60(ThreadState *);
s32 func_800263D0(u32);
void func_800037F0(ThreadState *, s32, void (*)(void *), void *, void *, s32);
void D_10009400(void *);
ALDMAproc D_10009980(void *);
ConkerBankFetch D_10009FFC(void);
void D_10009B2C(void *);
void D_10009B90(void *);
void D_10009B4C(void *);
extern AudioHeap D_8003E370;
extern void *D_8003E380;
extern AudioEffectParameters D_8002AE54;
extern s32 D_80040F90;
extern s32 D_80040F94;
extern void *D_8003E620[];
extern void *D_8003E5E8[];
extern void *D_800412B0[];
extern void *D_80041708[];
void func_800226F0(void *, s32);
extern u8 D_8002AE40;
extern u8 D_8003E3A0[];
extern AudioTaskRecord *D_8003E390[3];
extern OSMesgQueue D_8003E5D0;
extern OSMesgQueue D_8003E608;
extern u8 D_8003E640[];
extern Acmd *D_8003E388[];
extern u8 D_80040F84;
extern s32 D_80040F88;
extern u32 D_80040F8C;
extern AudioDmaNode D_800406B8[];
extern AudioBufferState D_80040AC8[];
extern OSMesgQueue D_80041298;
extern OSMesgQueue D_800416F0;

#define AUDIO_LINK(ln, to)                      \
    {                                           \
        (ln)->next = (to)->next;                \
        (ln)->prev = (to);                      \
        if ((to)->next != NULL) {               \
            (to)->next->prev = (ln);            \
        }                                       \
        (to)->next = (ln);                      \
    }

typedef struct {
    Acmd *commands[2];
    AudioTaskRecord *tasks[3];
} AudioWorkSlots;

void func_80008F90(AudioDriverConfig *c, s32 pri, AudioDeviceConfig *amc) {
    u32 i;
    f32 fsize;

    func_80012588((s32)&D_8003E370);
    c->dma = D_10009980;
    c->outputRate = func_800263D0(amc->frequency);
    c->fetch = D_10009FFC;
    c->release = D_10009B2C;
    c->retain = D_10009B90;
    c->releaseNow = D_10009B4C;
    fsize = (f32)amc->frames * c->outputRate / 30.0f;
    D_80040F8C = (s32)fsize;
    if (D_80040F8C < fsize) {
        D_80040F8C++;
    }
    D_80040F8C = (D_80040F8C / 184) * 184 + 184;
    D_80040F88 = D_80040F8C - 184;
    D_80040F90 = D_80040F8C + 0x54;
    D_80040F84 = 0;
    {
        AudioEffectParameters effects = D_8002AE54;

        c->params[0] = effects.values[0];
        c->params[1] = effects.values[1];
        func_80018DA0(D_8003E640, c);
    }
    D_8003E380 = D_8003E640;
    D_800406B8[0].prev = NULL;
    D_800406B8[0].next = NULL;
    for (i = 0; i < 51; i++) {
        {
            AudioDmaNode *ln = &D_800406B8[i + 1];
            AudioDmaNode *to = &D_800406B8[i];

            AUDIO_LINK(ln, to);
        }
        D_800406B8[i].buffer = func_80012844(0, 0, c->heap, 1, 0x800);
    }
    D_800406B8[i].buffer = func_80012844(0, 0, c->heap, 1, 0x800);
    func_800226F0(D_80040AC8, 0x4B0);
    D_80040AC8[0].prev = NULL;
    D_80040AC8[0].next = NULL;
    for (i = 0; i < 49; i++) {
        {
            AudioBufferState *ln = &D_80040AC8[i + 1];
            AudioBufferState *to = &D_80040AC8[i];

            AUDIO_LINK(ln, to);
        }
        D_80040AC8[i].buffer = NULL;
    }
    D_80040AC8[i].buffer = NULL;
    for (i = 0; i < 2; i++) {
        ((AudioWorkSlots *)D_8003E388)->commands[i] =
            func_80012844(0, 0, c->heap, 1, amc->maxCommands * sizeof(Acmd));
    }
    D_80040F94 = amc->maxCommands;
    for (i = 0; i < 3; i++) {
        ((AudioWorkSlots *)D_8003E388)->tasks[i] = func_80012844(0, 0, c->heap, 1, 0x90);
        ((AudioWorkSlots *)D_8003E388)->tasks[i]->completion.type = 2;
        ((AudioWorkSlots *)D_8003E388)->tasks[i]->completion.record = ((AudioWorkSlots *)D_8003E388)->tasks[i];
        ((AudioWorkSlots *)D_8003E388)->tasks[i]->buffer = func_80012844(0, 0, c->heap, 1, D_80040F90 * 4);
    }
    func_80023790(&D_8003E608, D_8003E620, 8);
    func_80023790(&D_8003E5D0, D_8003E5E8, 8);
    func_80023790(&D_80041298, D_800412B0, 0x20);
    func_80023790(&D_800416F0, D_80041708, 0x28);
    func_800037F0((ThreadState *)D_8003E3A0, 4, D_10009400, 0, &D_800406A0, pri);
    D_8002AE40 = 1;
    func_80022A60((ThreadState *)D_8003E3A0);
}
void func_80022E00(void *);

void func_800093CC(void) {
    if (D_8002AE40 != 0) {
        func_80022E00(D_8003E3A0);
    }
}

typedef struct AudioSchedulerClient {
    struct AudioSchedulerClient *next;
    OSMesgQueue *queue;
    u32 flags;
} AudioSchedulerClient;


void func_800051C8(AudioSchedulerClient *, OSMesgQueue *);
s32 func_800095A0(AudioTaskRecord *, AudioTaskRecord *);
void func_80018E0C(void *);
extern u8 D_8002AC5C;
extern u32 D_8002AE44;

void func_80009400(s32 arg0) {
    u32 done;
    AudioTaskRecord *previous;
    void *message;
    s32 first;
    AudioSchedulerClient client;
    u32 cadence;
    s16 type;

    done = 0;
    message = 0;
    previous = 0;
    cadence = 0;
    first = 1;
    client.flags = 0;
    func_800051C8(&client, &D_8003E5D0);
    while (done == 0) {
        func_80023440(&D_8003E5D0, &message, 1);
        if (D_8002AC5C != 0) {
            *(s16 *)message = 4;
        }
        type = *(s16 *)message;
        switch (type) {
        case 1:
            if (cadence >= 2) {
                cadence = 0;
            }
            if (cadence == 0 &&
                func_800095A0(D_8003E390[D_8002AE44 % 3U], previous) != 0) {
                if (first == 0) {
                    func_80023440(&D_8003E608, &message, 1);
                    previous = ((AudioCompletionMessage *)message)->record;
                }
                first = 0;
            }
            cadence++;
            break;
        case 4:
            done = 1;
            break;
        case 10:
            done = 1;
            break;
        }
    }
    func_80018E0C(D_8003E640);
    for (;;) {
        func_80023440(&D_8003E5D0, &message, 1);
    }
}
u32 func_800233C0(void *);
s32 func_80002DB0(void *, u32);
void func_800099BC(void);
void func_8000A03C(void);
Acmd *func_80019498(Acmd *, s32 *, s16 *, s32);
void func_80024F10(void);
extern u8 D_100290D0[];
extern u8 D_100291A0[];
extern u8 D_8002C960[];
extern s32 D_8002AE4C;
extern OSMesgQueue D_8003B200;

s32 func_800095A0(AudioTaskRecord *info, AudioTaskRecord *lastInfo) {
    s16 *audioPtr;
    Acmd *cmdp;
    s32 cmdLen;
    s32 samplesLeft;
    AudioSchedulerTask *t;
    u32 end;

    audioPtr = (s16 *)func_800233C0(info->buffer);
    func_800099BC();
    func_8000A03C();
    samplesLeft = *(volatile u32 *)0xA4500004 >> 2;
    if (lastInfo != NULL) {
        func_80002DB0(lastInfo->adjustedBuffer, lastInfo->samples << 2);
    }
    if (samplesLeft >= 0xF9 && D_80040F84 == 0) {
        info->samples = D_80040F88;
        D_80040F84 = 2;
    } else {
        info->samples = D_80040F8C;
        if (D_80040F84 != 0) {
            D_80040F84--;
        }
    }
    end = (u32)audioPtr + (info->samples << 2);
    if ((end & 0x1FFF) == 0) {
        audioPtr += 8;
        info->adjustedBuffer = info->buffer + 0x10;
    } else {
        info->adjustedBuffer = info->buffer;
    }
    cmdp = func_80019498(D_8003E388[D_8002AE4C], &cmdLen, audioPtr, info->samples);
    if (cmdLen == 0) {
        return 0;
    }
    t = &info->scheduler;
    t->next = NULL;
    t->completionQueue = &D_8003E608;
    t->completionMessage = &info->completion;
    t->flags = 2;
    t->framebuffer = NULL;
    t->task.commands = D_8003E388[D_8002AE4C];
    t->task.commandSize = (cmdp - D_8003E388[D_8002AE4C]) * sizeof(Acmd);
    t->task.type = 2;
    t->task.boot = D_100290D0;
    t->task.bootSize = (s32)D_100291A0 - (s32)D_100290D0;
    t->task.flags = 0;
    /* aspMain text begins where the 0xD0-byte rspboot text ends. */
    t->task.microcode = D_100290D0 + 0xD0;
    t->task.microcodeData = D_8002C960;
    t->task.microcodeDataSize = 0x800;
    t->task.yieldData = NULL;
    t->task.yieldSize = 0x400;
    func_80024F10();
    func_80023580(&D_8003B200, t, 1);
    D_8002AE4C ^= 1;
    return 1;
}
/* SDK ALDMAproc contract, using the project scalar aliases. */

typedef struct {
    u8 initialized;
    u8 pad1[3];
    s32 field4;
    void *base;
} AudioDmaManager;

extern AudioDmaManager D_80040F78;
s32 D_100097CC(s32, s32, void *);


extern u32 D_8002AE48;

typedef struct {
    u16 type;
    u8 priority;
    u8 status;
    OSMesgQueue *returnQueue;
    void *dramAddress;
    u32 deviceAddress;
    u32 size;
    void *piHandle;
} TransferIoMessage;

s32 func_80024920(TransferIoMessage *, s32, s32, u32, void *, u32,
                 OSMesgQueue *);
extern TransferIoMessage D_80040F98[];

s32 func_800097CC(s32 addr, s32 len, void *state) {
    u8 *foundBuffer;
    s32 delta;
    s32 addrEnd;
    s32 buffEnd;
    AudioDmaNode *dmaPtr;
    AudioDmaNode *lastDmaPtr;

    lastDmaPtr = 0;
    dmaPtr = (AudioDmaNode *)D_80040F78.field4;
    addrEnd = addr + len;
    while (dmaPtr != 0) {
        buffEnd = dmaPtr->address + 0x800;
        if (dmaPtr->address > addr) {
            break;
        } else if (addrEnd <= buffEnd) {
            dmaPtr->frame = D_8002AE44;
            foundBuffer = dmaPtr->buffer + addr - dmaPtr->address;
            return (s32)func_800233C0(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = dmaPtr->next;
    }
    dmaPtr = D_80040F78.base;
    if (dmaPtr == 0 || D_8002AE48 >= 0x20) {
        return 0;
    }
    D_80040F78.base = dmaPtr->next;
    if (dmaPtr->next != 0) {
        dmaPtr->next->prev = dmaPtr->prev;
    }
    if (dmaPtr->prev != 0) {
        dmaPtr->prev->next = dmaPtr->next;
    }
    if (lastDmaPtr != 0) {
        AudioDmaNode *linkNode = dmaPtr;
        AudioDmaNode *linkAfter = lastDmaPtr;

        linkNode->next = linkAfter->next;
        linkNode->prev = linkAfter;
        if (linkAfter->next != 0) {
            linkAfter->next->prev = linkNode;
        }
        linkAfter->next = linkNode;
    } else if (D_80040F78.field4 != 0) {
        lastDmaPtr = (AudioDmaNode *)D_80040F78.field4;
        D_80040F78.field4 = (s32)dmaPtr;
        dmaPtr->next = lastDmaPtr;
        dmaPtr->prev = 0;
        lastDmaPtr->prev = dmaPtr;
    } else {
        D_80040F78.field4 = (s32)dmaPtr;
        dmaPtr->next = 0;
        dmaPtr->prev = 0;
    }
    foundBuffer = dmaPtr->buffer;
    delta = addr & 1;
    addr -= delta;
    dmaPtr->address = addr;
    dmaPtr->frame = D_8002AE44;
    func_80024920(&D_80040F98[D_8002AE48++], 1, 0, addr, foundBuffer, 0x800,
                  &D_80041298);
    return (s32)(func_800233C0(foundBuffer) + delta);
}

ALDMAproc func_80009980(void *state) {
    if (D_80040F78.initialized == 0) {
        D_80040F78.field4 = 0;
        D_80040F78.base = D_800406B8;
        D_80040F78.initialized = 1;
    }
    *(void **)state = 0;
    return D_100097CC;
}
void func_800099BC(void) {
    u32 i;
    void *message;
    AudioDmaNode *record;
    AudioDmaNode *next;

    message = 0;
    i = 0;
    if (D_8002AE48 != 0) {
        do {
            if (func_80023440(&D_80041298, &message, 0) == -1) {
                func_80023440(&D_80041298, &message, 1);
            }
            i++;
        } while (i < D_8002AE48);
    }
    record = (AudioDmaNode *)D_80040F78.field4;
    if (record != 0) {
        do {
            next = record->next;
            if (record->frame + 1 < D_8002AE44) {
                if (record == (AudioDmaNode *)D_80040F78.field4) {
                    D_80040F78.field4 = (s32)next;
                }
                {
                    AudioDmaNode *element = record;

                    if (element->next != 0) {
                        element->next->prev = element->prev;
                    }
                    if (element->prev != 0) {
                        element->prev->next = element->next;
                    }
                }
                if (D_80040F78.base != 0) {
                    AudioDmaNode *linkNode = record;
                    AudioDmaNode *linkAfter = D_80040F78.base;

                    linkNode->next = linkAfter->next;
                    linkNode->prev = linkAfter;
                    if (linkAfter->next != 0) {
                        linkAfter->next->prev = linkNode;
                    }
                    linkAfter->next = linkNode;
                } else {
                    D_80040F78.base = record;
                    record->next = 0;
                    record->prev = 0;
                }
            }
            record = next;
        } while (next != 0);
    }
    D_8002AE48 = 0;
    D_8002AE44++;
}
void func_80009B2C(void *arg0) {
    if (((u32)arg0 & 1) == 0) {
        ((AudioBufferState *)arg0)->count--;
    }
}
void func_80009BE4(void *);

void func_80009B4C(void *arg0) {
    if (((u32)arg0 & 1) == 0) {
        ((AudioBufferState *)arg0)->count--;
        if (((AudioBufferState *)arg0)->count == 0) {
            func_80009BE4(arg0);
        }
    }
}
void func_80009B90(void *arg0) {
    if (((u32)arg0 & 1) == 0) {
        if (((AudioBufferState *)arg0)->state == 1) {
            if (((AudioBufferState *)arg0)->field16 == 1) {
                ((AudioBufferState *)arg0)->count++;
            }
            ((AudioBufferState *)arg0)->state = 2;
            return;
        }
        ((AudioBufferState *)arg0)->count++;
    }
}
void func_850AD770(void);
extern s32 D_8003C8E0;

void func_80009BE4(void *arg0) {
    AudioBufferState *record = arg0;
    extern AudioBufferState *D_800406A4;
    extern AudioBufferState *D_800406B0;

    if ((u32)arg0 & 1) {
        D_8003C8E0 = 0x0F000004;
        func_850AD770();
        return;
    }
    {
        s32 *ownerSlot = record->ownerSlot;

        *ownerSlot = record->savedValue;
    }
    if (record == D_800406A0.active) {
        D_800406A4 = record->next;
    }
    if (record->next != 0) {
        record->next->prev = record->prev;
    }
    if (record->prev != 0) {
        record->prev->next = record->next;
    }
    if (D_800406A0.freeAnchor != 0) {
        AudioBufferState *linkNode = record;
        AudioBufferState *linkAfter = D_800406A0.freeAnchor;

        linkNode->next = linkAfter->next;
        linkNode->prev = linkAfter;
        if (linkAfter->next != 0) {
            linkAfter->next->prev = linkNode;
        }
        linkAfter->next = linkNode;
    } else {
        D_800406B0 = record;
        record->next = 0;
        record->prev = 0;
    }
}
s32 func_80003C40(s32, s32, s32, s32);
void func_800043B4(void *, s32);
void func_80022D10(void *, s32);
void func_80023D20(void *, s32);
extern u32 D_8002AE50;
extern TransferIoMessage D_80041330[];

void *func_80009CBC(void *arg0, s32 mode) {
    AudioBufferState *record;
    AudioBufferState *reuse;
    s32 size;
    s32 alignedSize;
    AudioBufferState *anchor;
    u32 value;
    s32 *ownerSlot;
    extern AudioBufferState *D_800406A4;

    reuse = 0;
    value = *(u32 *)arg0;
    if (value & 1) {
        if (mode == 0) {
            size = (value & 0xFF) + 1;
        } else {
            size = (value & 0xFF & ~1) << 6;
        }
        record = D_800406A0.base;
        if (record == 0) {
            record = D_800406A0.active;
            while (record != 0) {
                if (record->count == 0 && record->field16 == 0 && record->state == 2) {
                    reuse = record;
                }
                record = record->next;
            }
            record = reuse;
            if (reuse != 0) {
                ownerSlot = reuse->ownerSlot;
                *ownerSlot = reuse->savedValue;
                func_800043B4(reuse->buffer, 4);
                reuse->buffer = 0;
                reuse->ownerSlot = 0;
                if (reuse == D_800406A0.active) {
                    D_800406A4 = reuse->next;
                }
                {
                    AudioBufferState *element = reuse;

                    if (element->next != 0) {
                        element->next->prev = element->prev;
                    }
                    if (element->prev != 0) {
                        element->prev->next = element->next;
                    }
                }
            }
        } else {
            D_800406A0.base = record->next;
            {
                AudioBufferState *element = record;

                if (element->next != 0) {
                    element->next->prev = element->prev;
                }
                if (element->prev != 0) {
                    element->prev->next = element->next;
                }
            }
        }
        if (record != 0) {
            record->next = 0;
            record->prev = 0;
            if (D_800406A0.pending != 0) {
                AudioBufferState *linkNode = record;
                AudioBufferState *linkAfter = D_800406A0.pending;

                linkNode->next = linkAfter->next;
                linkNode->prev = linkAfter;
                if (linkAfter->next != 0) {
                    linkAfter->next->prev = linkNode;
                }
                linkAfter->next = linkNode;
            } else {
                D_800406A0.pending = record;
                record->next = 0;
                record->prev = 0;
            }
            record->savedValue = value;
            record->count = 0;
            record->field16 = mode;
            record->ownerSlot = arg0;
            record->state = 0;
            if (D_8002AE50 < 0x28U) {
                alignedSize = (size + 0xF) & ~0xF;
                record->buffer = (void *)func_80003C40(alignedSize, 0xFF, 2, 0);
                func_800226F0(record->buffer, alignedSize);
            } else {
                record->buffer = 0;
            }
            if (record->buffer != 0) {
                func_80023D20(record->buffer, alignedSize);
                func_80022D10(record->buffer, alignedSize);
                func_80024920(&D_80041330[D_8002AE50++], 1, 0,
                             (value >> 5) & ~7U, record->buffer, alignedSize,
                             &D_800416F0);
                *(u32 *)arg0 = (u32)record;
            }
        }
        return 0;
    }
    *(u32 *)arg0 = value;
    record = (AudioBufferState *)value;
    if (record->state != 0) {
        if (mode == 1) {
            if (record->state == 1) {
                record->state = 2;
            } else {
                record->count++;
            }
        }
        return record->buffer;
    }
    return 0;
}

void *D_10009CBC(void *, s32);

ConkerBankFetch func_80009FFC(void) {
    if (D_800406A0.initialized == 0) {
        D_800406A0.active = 0;
        D_800406A0.base = D_80040AC8;
        D_800406A0.pending = 0;
        D_800406A0.freeAnchor = 0;
        D_800406A0.initialized = 1;
    }
    return D_10009CBC;
}
typedef struct {
    u8 pad0[0xA];
    u8 fieldA;
} AudioWaveState;

typedef struct {
    u8 pad0[8];
    AudioWaveState *wave;
} AudioBankSound;

typedef struct {
    u8 pad0[0xE];
    s16 soundCount;
    AudioBankSound *sounds[1];
} AudioInstrument;

void func_80004074(s32);
void func_8000A348(void);
extern s32 D_8003E384;

void func_8000A03C(void) {
    u32 i;
    u32 sound;
    s32 found;
    s32 received;
    void *message;
    AudioBufferState *record;
    AudioBufferState *next;
    AudioInstrument *instrument;
    AudioWaveState *wave;
    s32 busy;

    received = 0;
    message = 0;
    for (i = 0; i < D_8002AE50; i++) {
        if (func_80023440(&D_800416F0, &message, 0) != -1) {
            record = D_800406A0.pending;
            received++;
            found = 0;
            while (record != 0 && found == 0) {
                if (record->buffer == ((TransferIoMessage *)message)->dramAddress) {
                    if (record == D_800406A0.pending) {
                        D_800406A0.pending = record->next;
                    }
                    {
                        AudioBufferState *element = record;

                        if (element->next != 0) {
                            element->next->prev = element->prev;
                        }
                        if (element->prev != 0) {
                            element->prev->next = element->next;
                        }
                    }
                    record->next = 0;
                    record->prev = 0;
                    if (D_800406A0.active != 0) {
                        AudioBufferState *linkNode = record;
                        AudioBufferState *linkAfter = D_800406A0.active;

                        linkNode->next = linkAfter->next;
                        linkNode->prev = linkAfter;
                        if (linkAfter->next != 0) {
                            linkAfter->next->prev = linkNode;
                        }
                        linkAfter->next = linkNode;
                    } else {
                        D_800406A0.active = record;
                        record->next = 0;
                        record->prev = 0;
                    }
                    if (record->field16 == 1) {
                        instrument = record->buffer;
                        for (sound = 0; sound < (u32)instrument->soundCount; sound++) {
                            instrument->sounds[sound] = (AudioBankSound *)
                                ((u32)instrument->sounds[sound] + (u32)record->buffer);
                        }
                    }
                    record->state = 1;
                    record->count++;
                    found = 1;
                } else {
                    record = record->next;
                }
            }
        }
    }
    D_8002AE50 -= received;
    record = D_800406A0.freeAnchor;
    if (record != 0) {
        do {
            busy = 0;
            next = record->next;
            if (record->field16 == 1) {
                AudioInstrument *cleanupInstrument = record->buffer;
                for (sound = 0; sound < (u32)cleanupInstrument->soundCount; sound++) {
                    wave = cleanupInstrument->sounds[sound]->wave;
                    if (wave->fieldA != 0) {
                        wave->fieldA = 0;
                        busy = 1;
                    }
                }
            }
            if (busy == 0) {
                record->count = 0;
                record->state = 0;
                func_80004074((s32)record->buffer);
                record->ownerSlot = 0;
                if (record == D_800406A0.freeAnchor) {
                    D_800406A0.freeAnchor = next;
                }
                {
                    AudioBufferState *element = record;

                    if (element->next != 0) {
                        element->next->prev = element->prev;
                    }
                    if (element->prev != 0) {
                        element->prev->next = element->next;
                    }
                }
                if (D_800406A0.base != 0) {
                    AudioBufferState *linkNode = record;
                    AudioBufferState *linkAfter = D_800406A0.base;

                    linkNode->next = linkAfter->next;
                    linkNode->prev = linkAfter;
                    if (linkAfter->next != 0) {
                        linkAfter->next->prev = record;
                    }
                    linkAfter->next = record;
                    record = next;
                    continue;
                } else {
                    D_800406A0.base = record;
                    record->next = 0;
                    record->prev = 0;
                }
            }
            record = next;
        } while (next != 0);
    }
    if (D_8003E384 != 0) {
        func_8000A348();
        D_8003E384 = 0;
    }
}
void func_8000A348(void) {
    AudioBufferState *record;
    AudioBufferState *next;
    AudioBufferState *anchor;
    s32 *ownerSlot;

    record = D_800406A0.active;
    if (record != 0) {
        do {
            next = record->next;
            if ((record->count == 0) && (record->field16 == 0)) {
                ownerSlot = record->ownerSlot;
                *ownerSlot = record->savedValue;
                record->ownerSlot = 0;
                if (record == D_800406A0.active) {
                    D_800406A0.active = next;
                }
                if (record->next != 0) {
                    record->next->prev = record->prev;
                }
                if (record->prev != 0) {
                    record->prev->next = record->next;
                }
                anchor = D_800406A0.freeAnchor;
                if (anchor != 0) {
                    {
                        AudioBufferState *linkNode = record;
                        AudioBufferState *linkAfter;

                        linkNode->next = anchor->next;
                        linkNode->prev = anchor;
                        linkAfter = anchor;
                        anchor = linkAfter->next;
                        if (linkAfter->next != 0) {
                            linkAfter->next->prev = linkNode;
                        }
                        linkAfter->next = linkNode;
                    }
                } else {
                    D_800406A0.freeAnchor = record;
                    record->next = 0;
                    record->prev = 0;
                }
            }
            record = next;
        } while (next != 0);
    }
}
