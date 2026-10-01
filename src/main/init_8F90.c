#include "types.h"

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
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_80009400.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_800095A0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8F90/func_800097CC.s")
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

ALDMAproc func_80009980(void *state) {
    if (D_80040F78.initialized == 0) {
        D_80040F78.field4 = 0;
        D_80040F78.base = D_800406B8;
        D_80040F78.initialized = 1;
    }
    *(void **)state = 0;
    return D_100097CC;
}
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
