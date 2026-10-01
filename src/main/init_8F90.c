#include "types.h"
#include "../lib/ultralib/include/PR/abi.h"

/*
 * Reviewed source unit: src/main/init_8F90.c
 * Boundary evidence: docs/evidence/main_audio_driver_sequence_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_80008F90
 * - func_80009400
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

typedef struct AudioBufferState {
    struct AudioBufferState *next;
    struct AudioBufferState *prev;
    s32 savedValue;
    s32 *ownerSlot;
    u8 pad10[4];
    s8 count;
    u8 state;
    u8 field16;
} AudioBufferState;

typedef struct {
    u8 initialized;
    u8 pad1[3];
    AudioBufferState *active;
    void *base;
    s32 fieldC;
    AudioBufferState *freeAnchor;
} AudioBankManager;

extern AudioBankManager D_800406A0;

#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_80008F90.s")
void func_80022E00(void *);
extern u8 D_8002AE40;
extern u8 D_8003E3A0[];

void func_800093CC(void) {
    if (D_8002AE40 != 0) {
        func_80022E00(D_8003E3A0);
    }
}
typedef struct MessageQueue MessageQueue;
typedef struct AudioTaskRecord AudioTaskRecord;

typedef struct AudioSchedulerClient {
    struct AudioSchedulerClient *next;
    MessageQueue *queue;
    u32 flags;
} AudioSchedulerClient;

typedef struct {
    s16 type;
    u8 pad2[2];
    AudioTaskRecord *record;
} AudioCompletionMessage;

void func_800051C8(AudioSchedulerClient *, MessageQueue *);
s32 func_800095A0(AudioTaskRecord *, AudioTaskRecord *);
void func_80018E0C(void *);
s32 func_80023440(MessageQueue *, void **, s32);
extern u8 D_8002AC5C;
extern u32 D_8002AE44;
extern AudioTaskRecord *D_8003E390[3];
extern MessageQueue D_8003E5D0;
extern MessageQueue D_8003E608;
extern u8 D_8003E640[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80009400 CURRENT (1050) */
void func_80009400(s32 arg0) {
    s32 done;
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
    do {
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
    } while (done == 0);
    func_80018E0C(D_8003E640);
    for (;;) {
        func_80023440(&D_8003E5D0, &message, 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80009400 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_80009400.s")
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
    MessageQueue *completionQueue;
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

u32 func_800233C0(void *);
s32 func_80002DB0(void *, u32);
void func_800099BC(void);
void func_8000A03C(void);
Acmd *func_80019498(Acmd *, s32 *, s16 *, s32);
void func_80024F10(void);
s32 func_80023580(MessageQueue *, void *, s32);
extern Acmd *D_8003E388[];
extern u8 D_100290D0[];
extern u8 D_100291A0[];
extern u8 D_8002C960[];
extern s32 D_8002AE4C;
extern u8 D_80040F84;
extern s32 D_80040F88;
extern s32 D_80040F8C;
extern MessageQueue D_8003B200;
extern volatile u32 D_A4500004;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_800095A0 CURRENT (1682) */
s32 func_800095A0(AudioTaskRecord *record, AudioTaskRecord *previous) {
    u32 physical;
    Acmd *commandEnd;
    s32 commandCount;
    s32 remaining;

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
    if (((physical + record->samples * 4) & 0x1FFF) == 0) {
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
typedef s32 (*ALDMAproc)(s32 addr, s32 len, void *state);

typedef struct {
    u8 initialized;
    u8 pad1[3];
    s32 field4;
    void *base;
} AudioDmaManager;

extern AudioDmaManager D_80040F78;
extern u8 D_800406B8[];
s32 D_100097CC(s32, s32, void *);

typedef struct AudioDmaNode {
    struct AudioDmaNode *next;
    struct AudioDmaNode *prev;
    u32 address;
    u32 frame;
    u8 *buffer;
} AudioDmaNode;

extern MessageQueue D_80041298;
extern u32 D_8002AE48;

typedef struct TransferMessageQueue TransferMessageQueue;
typedef struct {
    u16 type;
    u8 priority;
    u8 status;
    TransferMessageQueue *returnQueue;
    void *dramAddress;
    u32 deviceAddress;
    u32 size;
    void *piHandle;
} TransferIoMessage;

s32 func_80024920(TransferIoMessage *, s32, s32, u32, void *, u32,
                 TransferMessageQueue *);
extern TransferIoMessage D_80040F98[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_800097CC CURRENT (1135) */
s32 func_800097CC(s32 addr, s32 len, void *state) {
    u8 *buffer;
    s32 offset;
    u32 start;
    AudioDmaNode *record;
    AudioDmaNode *previous;
    AudioDmaNode *head;

    record = (AudioDmaNode *)D_80040F78.field4;
    previous = 0;
    while (record != 0) {
        start = record->address;
        if ((u32)addr < start) {
            break;
        }
        previous = record;
        if ((s32)(start + 0x800U) >= (s32)((u32)addr + (u32)len)) {
            record->frame = D_8002AE44;
            return (s32)func_800233C0(record->buffer + ((u32)addr - start));
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
        record->next = previous->next;
        record->prev = previous;
        if (previous->next != 0) {
            previous->next->prev = record;
        }
        previous->next = record;
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
    offset = addr & 1;
    buffer = record->buffer;
    addr -= offset;
    record->address = addr;
    record->frame = D_8002AE44;
    func_80024920(&D_80040F98[D_8002AE48++], 1, 0, addr, buffer,
                 0x800, (TransferMessageQueue *)&D_80041298);
    return (s32)(func_800233C0(buffer) + (u32)offset);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800097CC */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_800097CC.s")

ALDMAproc func_80009980(void *state) {
    if (D_80040F78.initialized == 0) {
        D_80040F78.field4 = 0;
        D_80040F78.base = D_800406B8;
        D_80040F78.initialized = 1;
    }
    *(void **)state = 0;
    return D_100097CC;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_800099BC CURRENT (976) */
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
                if (record->next != 0) {
                    record->next->prev = record->prev;
                }
                if (record->prev != 0) {
                    record->prev->next = record->next;
                }
                anchor = D_80040F78.base;
                if (anchor != 0) {
                    record->next = anchor->next;
                    record->prev = anchor;
                    if (anchor->next != 0) {
                        anchor->next->prev = record;
                    }
                    anchor->next = record;
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80009BE4 CURRENT (810) */
void func_80009BE4(void *arg0) {
    AudioBufferState *record = arg0;
    AudioBufferState *anchor;

    if ((u32)arg0 & 1) {
        D_8003C8E0 = 0x0F000004;
        func_850AD770();
        return;
    }
    *record->ownerSlot = record->savedValue;
    if (record == D_800406A0.active) {
        D_800406A0.active = record->next;
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
            AudioBufferState *linkAfter = anchor;

            linkNode->next = linkAfter->next;
            linkNode->prev = linkAfter;
            if (linkAfter->next != 0) {
                linkAfter->next->prev = linkNode;
            }
            linkAfter->next = linkNode;
        }
        return;
    }
    D_800406A0.freeAnchor = record;
    record->next = 0;
    record->prev = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80009BE4 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_80009BE4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_80009CBC.s")
typedef void *(*ConkerBankFetch)(void *, s32);

extern u8 D_80040AC8[];
void *D_10009CBC(void *, s32);

ConkerBankFetch func_80009FFC(void) {
    if (D_800406A0.initialized == 0) {
        D_800406A0.active = 0;
        D_800406A0.base = D_80040AC8;
        D_800406A0.fieldC = 0;
        D_800406A0.freeAnchor = 0;
        D_800406A0.initialized = 1;
    }
    return D_10009CBC;
}
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_8000A03C.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000A348 CURRENT (475) */
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
                        AudioBufferState *linkAfter = anchor;

                        linkNode->next = linkAfter->next;
                        linkNode->prev = linkAfter;
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
#endif /* CONKER_DEFERRED_CANDIDATE func_8000A348 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_8000A348.s")
