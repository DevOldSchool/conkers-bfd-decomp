#include "types.h"
#include "libultra_os.h"
#include "../lib/ultralib/include/PR/abi.h"

/*
 * Reviewed source unit: src/main/init_8F90.c
 * Boundary evidence: docs/evidence/boundaries/main/main_audio_driver_sequence_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_80008F90
 * - func_800095A0
 * - func_800097CC
 * - func_800099BC
 * - func_80009BE4
 * - func_80009CBC
 * - func_8000A03C
 * - func_8000A348
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

/* Keep address symbols for linking and registered match evidence. */
#define audio_thread_stop func_800093CC
#define audio_dma_callback_new func_80009980
#define audio_bank_cache_release func_80009B2C
#define audio_bank_cache_release_and_queue_reclaim func_80009B4C
#define audio_bank_cache_retain func_80009B90
#define audio_bank_fetch_callback_new func_80009FFC

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
extern s32 D_80040F8C;
extern u8 D_800406B8[];
extern u8 D_800406CC[];
extern u8 D_80040AC8[];
extern u8 D_80040AE0[];
extern OSMesgQueue D_80041298;
extern OSMesgQueue D_800416F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008F90 CURRENT (1811) */
void func_80008F90(AudioDriverConfig *config, s32 priority, AudioDeviceConfig *device) {
    typedef struct {
        Acmd *commands[2];
        AudioTaskRecord *tasks[3];
    } AudioWorkSlots;
    u32 rounded;
    AudioEffectParameters effects;
    AudioDmaNode *dma;
    AudioDmaNode *dmaNext;
    AudioBufferState *buffer;
    AudioBufferState *bufferNext;
    f32 samples;
    s32 rate;
    u32 i;

    func_80012588((s32)&D_8003E370);
    config->dma = D_10009980;
    rate = func_800263D0(device->frequency);
    config->outputRate = rate;
    config->fetch = D_10009FFC;
    config->release = D_10009B2C;
    config->retain = D_10009B90;
    config->releaseNow = D_10009B4C;
    samples = ((f32)device->frames * (f32)rate) / 30.0f;
    D_80040F8C = (s32)samples;
    rounded = D_80040F8C;
    if ((f32)rounded < samples) {
        D_80040F8C = rounded + 1;
        rounded = D_80040F8C;
    }
    rate = 184;
    D_80040F8C = ((rounded / rate) * rate) + rate;
    rounded = D_80040F8C;
    D_80040F88 = rounded - 184;
    D_80040F90 = rounded + 0x54;
    D_80040F84 = 0;
    effects = D_8002AE54;
    config->params[0] = effects.values[0];
    config->params[1] = effects.values[1];
    func_80018DA0(D_8003E640, config);
    D_8003E380 = D_8003E640;
    dma = (AudioDmaNode *)D_800406B8;
    dma->prev = 0;
    dma->next = 0;
    dmaNext = (AudioDmaNode *)D_800406CC;
    do {
        dma[1].next = dma->next;
        dma[1].prev = dma;
        if (dma->next != 0) {
            dma->next->prev = dmaNext;
        }
        dma->next = dmaNext;
        rounded = (u32)func_80012844(0, 0, config->heap, 1, 0x800);
        dmaNext++;
        dma++;
        dma[-1].buffer = (u8 *)rounded;
    } while ((u32)dmaNext < (u32)D_80040AC8);
    dma->buffer = func_80012844(0, 0, config->heap, 1, 0x800);
    func_800226F0(D_80040AC8, 0x4B0);
    buffer = (AudioBufferState *)D_80040AC8;
    buffer->prev = 0;
    buffer->next = 0;
    bufferNext = (AudioBufferState *)D_80040AE0;
    for (i = 0; i < 49; i++) {
        {
            AudioBufferState *linkNode = bufferNext;
            AudioBufferState *linkAfter = buffer;

            buffer[1].next = linkAfter->next;
            buffer[1].prev = linkAfter;
            if (linkAfter->next != 0) {
                linkAfter->next->prev = linkNode;
            }
            linkAfter->next = linkNode;
        }
        buffer++;
        bufferNext++;
        buffer[-1].buffer = 0;
    }
    buffer->buffer = 0;
    i = 0;
    do {
        D_8003E388[i] = func_80012844(0, 0, config->heap, 1, device->maxCommands * 8);
        i++;
    } while (&D_8003E388[i] < (Acmd **)D_8003E390);
    D_80040F94 = device->maxCommands;
    for (i = 0; i < 3; i++) {
        ((AudioWorkSlots *)D_8003E388)->tasks[i] = func_80012844(0, 0, config->heap, 1, 0x90);
        ((AudioWorkSlots *)D_8003E388)->tasks[i]->completion.type = 2;
        ((AudioWorkSlots *)D_8003E388)->tasks[i]->completion.record = ((AudioWorkSlots *)D_8003E388)->tasks[i];
        ((AudioWorkSlots *)D_8003E388)->tasks[i]->buffer = func_80012844(0, 0, config->heap, 1, D_80040F90 * 4);
    }
    func_80023790(&D_8003E608, D_8003E620, 8);
    func_80023790(&D_8003E5D0, D_8003E5E8, 8);
    func_80023790(&D_80041298, D_800412B0, 0x20);
    func_80023790(&D_800416F0, D_80041708, 0x28);
    func_800037F0((ThreadState *)D_8003E3A0, 4, D_10009400, 0, &D_800406A0, priority);
    D_8002AE40 = 1;
    func_80022A60((ThreadState *)D_8003E3A0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008F90 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_80008F90.s")
void func_80022E00(void *);

void audio_thread_stop(void) {
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
            goto dispatch_done;
        case 4:
            done = 1;
            goto dispatch_done;
        case 10:
            done = 1;
            goto dispatch_done;
        }
dispatch_done:
        ;
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
extern volatile u32 D_A4500004;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_800095A0 CURRENT (1380) */
s32 func_800095A0(AudioTaskRecord *record, AudioTaskRecord *previous) {
    u32 physical;
    Acmd *commandEnd;
    s32 commandCount;
    s32 remaining;
    u32 bufferEnd;
    u32 stackPadding[1];

    physical = func_800233C0(record->buffer);
    func_800099BC();
    func_8000A03C();
    remaining = (s32)(D_A4500004 >> 2);
    if (previous != 0) {
        func_80002DB0(previous->adjustedBuffer, previous->samples * 4);
    }
    if (remaining >= 0xF9 && D_80040F84 == 0) {
        record->samples = D_80040F88;
        D_80040F84 = 2;
    } else {
        record->samples = D_80040F8C;
        if (D_80040F84 != 0) {
            D_80040F84--;
        }
    }
    bufferEnd = physical + ((u32)record->samples << 2);
    if ((bufferEnd & 0x1FFF) == 0) {
        physical += 0x10;
        record->adjustedBuffer = record->buffer + 0x10;
    } else {
        record->adjustedBuffer = record->buffer;
    }
    commandEnd = func_80019498(D_8003E388[D_8002AE4C], &commandCount,
                             (s16 *)physical, record->samples);
    if (commandCount == 0) {
        return 0;
    }
    record->scheduler.next = 0;
    record->scheduler.completionQueue = &D_8003E608;
    record->scheduler.completionMessage = &record->completion;
    record->scheduler.flags = 2;
    record->scheduler.framebuffer = 0;
    record->scheduler.task.commands = D_8003E388[D_8002AE4C];
    record->scheduler.task.commandSize =
        (u32)((s32)((u32)commandEnd - (u32)D_8003E388[D_8002AE4C]) >> 3) << 3;
    record->scheduler.task.type = 2;
    record->scheduler.task.boot = D_100290D0;
    record->scheduler.task.bootSize = (u32)D_100291A0 - (u32)D_100290D0;
    record->scheduler.task.flags = 0;
    record->scheduler.task.microcode = D_100291A0;
    record->scheduler.task.microcodeData = D_8002C960;
    record->scheduler.task.microcodeDataSize = 0x800;
    record->scheduler.task.yieldData = 0;
    record->scheduler.task.yieldSize = 0x400;
    func_80024F10();
    func_80023580(&D_8003B200, &record->scheduler, 1);
    D_8002AE4C ^= 1;
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800095A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_800095A0.s")
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_800097CC CURRENT (305) */
s32 func_800097CC(s32 addr, s32 len, void *state) {
    u8 *buffer;
    s32 offset;
    s32 request;
    AudioDmaNode *record;
    AudioDmaNode *previous;
    AudioDmaNode *head;

    request = addr;
    record = (AudioDmaNode *)D_80040F78.field4;
    previous = 0;
    while (record != 0) {
        if ((u32)request < record->address) {
            break;
        }
        previous = record;
        addr = (s32)(record->address + 0x800U);
        if (addr >= (s32)((u32)request + (u32)len)) {
            record->frame = D_8002AE44;
            return (s32)func_800233C0(record->buffer + ((u32)request - record->address));
        }
        record = record->next;
    }
    record = D_80040F78.base;
    if (record == 0 || D_8002AE48 >= 0x20) {
        return 0;
    }
    D_80040F78.base = record->next;
    if (record->next != 0) {
        record->next->prev = record->prev;
    }
    if (record->prev != 0) {
        record->prev->next = record->next;
    }
    if (previous != 0) {
        AudioDmaNode *linkNode = record;
        AudioDmaNode *linkAfter = previous;

        linkNode->next = linkAfter->next;
        linkNode->prev = linkAfter;
        if (linkAfter->next != 0) {
            linkAfter->next->prev = linkNode;
        }
        linkAfter->next = linkNode;
    } else {
        head = (AudioDmaNode *)D_80040F78.field4;
        if (head != 0) {
            D_80040F78.field4 = (s32)record;
            record->next = head;
            record->prev = 0;
            head->prev = record;
        } else {
            D_80040F78.field4 = (s32)record;
            record->next = 0;
            record->prev = 0;
        }
    }
    offset = request & 1;
    buffer = record->buffer;
    request -= offset;
    record->address = request;
    record->frame = D_8002AE44;
    func_80024920(&D_80040F98[D_8002AE48++], 1, 0, request, buffer,
                 0x800, &D_80041298);
    return (s32)(func_800233C0(buffer) + (u32)offset);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800097CC */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_800097CC.s")

ALDMAproc audio_dma_callback_new(void *state) {
    if (D_80040F78.initialized == 0) {
        D_80040F78.field4 = 0;
        D_80040F78.base = D_800406B8;
        D_80040F78.initialized = 1;
    }
    *(void **)state = 0;
    return D_100097CC;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_800099BC CURRENT (395) */
void func_800099BC(void) {
    u32 i;
    void *message;
    AudioDmaNode *record;
    AudioDmaNode *next;
    AudioDmaNode *anchor;

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
                anchor = D_80040F78.base;
                if (anchor != 0) {
                    AudioDmaNode *linkNode = record;
                    AudioDmaNode *linkAfter;

                    record->next = anchor->next;
                    record->prev = anchor;
                    linkAfter = anchor;
                    anchor = linkAfter->next;
                    if (anchor != 0) {
                        anchor->prev = linkNode;
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
#endif /* CONKER_DEFERRED_CANDIDATE func_800099BC */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_800099BC.s")
void audio_bank_cache_release(void *arg0) {
    if (((u32)arg0 & 1) == 0) {
        ((AudioBufferState *)arg0)->count--;
    }
}
void func_80009BE4(void *);

void audio_bank_cache_release_and_queue_reclaim(void *arg0) {
    if (((u32)arg0 & 1) == 0) {
        ((AudioBufferState *)arg0)->count--;
        if (((AudioBufferState *)arg0)->count == 0) {
            func_80009BE4(arg0);
        }
    }
}
void audio_bank_cache_retain(void *arg0) {
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80009BE4 CURRENT (95) */
void func_80009BE4(void *arg0) {
    AudioBufferState *record = arg0;
    AudioBufferState *anchor;
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
    anchor = D_800406A0.freeAnchor;
    if (anchor != 0) {
        {
            AudioBufferState *linkNode = record;
            AudioBufferState *linkAfter;

            linkNode->next = anchor->next;
            linkNode->prev = anchor;
            linkAfter = anchor;
            anchor = linkAfter->next;
            if (anchor != 0) {
                anchor->prev = linkNode;
            }
            linkAfter->next = linkNode;
        }
        return;
    }
    D_800406B0 = record;
    record->next = 0;
    record->prev = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80009BE4 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_80009BE4.s")
s32 func_80003C40(s32, s32, s32, s32);
void func_800043B4(void *, s32);
void func_80022D10(void *, s32);
void func_80023D20(void *, s32);
extern u32 D_8002AE50;
extern TransferIoMessage D_80041330[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80009CBC CURRENT (330) */
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
            anchor = D_800406A0.pending;
            if (anchor != 0) {
                AudioBufferState *linkNode = record;
                AudioBufferState *linkAfter;

                linkNode->next = anchor->next;
                linkNode->prev = anchor;
                linkAfter = anchor;
                anchor = linkAfter->next;
                if (anchor != 0) {
                    anchor->prev = linkNode;
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
#endif /* CONKER_DEFERRED_CANDIDATE func_80009CBC */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_80009CBC.s")

void *D_10009CBC(void *, s32);

ConkerBankFetch audio_bank_fetch_callback_new(void) {
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000A03C CURRENT (685) */
void func_8000A03C(void) {
    u32 i;
    u32 sound;
    s32 found;
    s32 received;
    void *message;
    AudioBufferState *record;
    AudioBufferState *next;
    AudioBufferState *anchor;
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
                    found = 1;
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
                    anchor = D_800406A0.active;
                    if (anchor != 0) {
                        AudioBufferState *linkNode = record;
                        AudioBufferState *linkAfter = anchor;

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
                anchor = D_800406A0.base;
                if (anchor != 0) {
                    AudioBufferState *linkNode = record;
                    AudioBufferState *linkAfter = anchor;

                    linkNode->next = linkAfter->next;
                    linkNode->prev = linkAfter;
                    if (linkAfter->next != 0) {
                        linkAfter->next->prev = linkNode;
                    }
                    linkAfter->next = linkNode;
                } else {
                    D_800406A0.base = record;
                    record->next = 0;
                    record->prev = 0;
                }
                record = next;
            } else {
                record = next;
            }
        } while (next != 0);
    }
    if (D_8003E384 != 0) {
        func_8000A348();
        D_8003E384 = 0;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000A03C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_8000A03C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000A348 CURRENT (65) */
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
                        if (anchor != 0) {
                            anchor->prev = linkNode;
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
#endif /* CONKER_DEFERRED_CANDIDATE func_8000A348 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_8000A348.s")
