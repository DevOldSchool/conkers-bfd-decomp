#include "types.h"

/*
 * Reviewed source unit: src/main/init_4470.c
 * Boundary evidence: docs/evidence/boundaries/main/main_allocator_transfer_controller_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_80004470
 * - func_80004514
 * - func_800046E4
 * - func_8000480C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct TransferThread TransferThread;

typedef struct TransferMessageQueue {
    TransferThread *messageWaiters;
    TransferThread *fullWaiters;
    s32 validCount;
    s32 first;
    s32 messageCount;
    void **messages;
} TransferMessageQueue;

struct TransferThread {
    u8 pad0[0x14];
    s32 id;
};

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

extern TransferThread *D_8002BE00;
void func_80022D10(void *, s32);
s32 func_80024920(TransferIoMessage *, s32, s32, u32, void *, u32, TransferMessageQueue *);

s32 func_80023440(TransferMessageQueue *, void **, s32);
extern TransferMessageQueue D_800388C8;
extern u8 D_8003A571;

void func_800030A0(s32, TransferMessageQueue *, void **, s32);
void func_80023790(TransferMessageQueue *, void **, s32);
extern TransferMessageQueue D_800388B0;
extern void *D_800380E0[];
extern void *D_80038400[];
extern void *D_800388F8[3];
extern TransferMessageQueue D_80038908[];
extern u8 D_8003A570;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80004470 CURRENT (70) */
void func_80004470(void) {
    void **message;
    TransferMessageQueue *queue;
    void **end;

    func_800030A0(0x96, &D_800388B0, D_800380E0, 0xC8);
    message = D_800388F8;
    queue = D_80038908;
    end = D_800388F8 + 3;
    do {
        func_80023790(queue, message, 1);
        message++;
        queue++;
    } while (message != end);
    func_80023790(&D_800388C8, D_80038400, 0x12C);
    D_8003A570 = 0;
    D_8003A571 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80004470 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_4470/func_80004470.s")
void func_8000480C(u32, void *, u32);
extern TransferIoMessage D_80038950[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80004514 CURRENT (1369) */
void func_80004514(u32 source, void *destination, u32 size, s32 blocking) {
    TransferMessageQueue *queue;
    TransferIoMessage request;
    TransferIoMessage *message;
    s32 index;

    index = D_8002BE00->id - 3;
    if ((size < 0xC8U) && (index == 0)) {
        func_8000480C(source, destination, size);
        return;
    }
    if ((index >= 4) || (index < 0)) {
        index = 0;
    }
    if (blocking == 0) {
        if (D_8003A571 == 0x12C) {
            return;
        }
        message = &D_80038950[D_8003A570];
        queue = &D_800388C8;
        if (D_8003A570 == 0x12B) {
            D_8003A570 = 0;
        } else {
            D_8003A570++;
        }
        D_8003A571++;
    } else {
        message = &request;
        queue = &D_80038908[index];
    }
    func_80022D10(destination, size);
    func_80024920(message, 0, 0, source, destination, size, queue);
    if (blocking != 0) {
        func_80023440(queue, 0, 1);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80004514 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_4470/func_80004514.s")
void func_80004674(void) {
    s32 i;

    for (i = 0; i < (s32)D_8003A571; i++) {
        func_80023440(&D_800388C8, 0, 1);
    }
    D_8003A571 = 0;
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_800046E4 CURRENT (20) */
void func_800046E4(u32 source, void *destination, u32 size) {
    TransferIoMessage request;
    void *response;
    TransferMessageQueue *queue;
    s32 index;
    u32 chunk;
    u32 processed;

    processed = 0;
    index = D_8002BE00->id - 3;
    if ((index >= 4) || (index < 0)) {
        index = 0;
    }
    func_80022D10(destination, size);
    if (size != 0) {
        queue = &D_80038908[index];
        do {
            if (size - processed < 0x14000U) {
                chunk = size - processed;
            } else {
                chunk = 0x14000;
            }
            func_80024920(&request, 0, 0, source, destination, chunk, queue);
            func_80023440(queue, &response, 1);
            processed += chunk;
            source += chunk;
            destination = (u8 *)destination + chunk;
        } while (processed < size);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800046E4 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_4470/func_800046E4.s")
typedef union {
    s32 word;
    u16 half[2];
} TransferWord;

extern u32 D_80000308;
extern TransferThread D_80035910;
extern volatile u8 D_8003A572;
extern volatile u8 D_8003A573;
extern volatile u8 D_8003A575;
void func_80022A60(TransferThread *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000480C CURRENT (2031) */
void func_8000480C(u32 source, void *destination, u32 size) {
    u32 count;
    TransferWord data;
    u32 offset;
    u32 readAddress;
    u8 *writeAddress;

    D_8003A572 = 1;
    size = (size + 1) & ~1U;
    while (D_8003A573 != 0) {
    }
    while (*(volatile u32 *)0xA4600010 & 3) {
    }
    source |= D_80000308;
    count = size - 2;
    if (source & 2) {
        size -= 2;
        data.word = *(volatile u32 *)((source - 2) | 0xA0000000);
        count = size - 2;
        offset = 0;
        *(u16 *)((void **)&destination)[0] = data.half[1];
        if (count != 0) {
            readAddress = source + 2;
            writeAddress = ((void **)&destination)[0];
            do {
                data.word = *(volatile u32 *)(readAddress | 0xA0000000);
                offset += 4;
                *(s16 *)(writeAddress + 2) = data.word >> 16;
                readAddress += 4;
                writeAddress += 4;
                *(u16 *)writeAddress = data.word;
            } while (offset < count);
        }
        if (size & 2) {
            data.word = *(volatile u32 *)((source + offset + 2) | 0xA0000000);
            *(u16 *)((u8 *)((void **)&destination)[0] + offset + 2) = data.half[0];
        }
    } else {
        offset = 0;
        if (count != 0) {
            readAddress = source;
            writeAddress = ((void **)&destination)[0];
            do {
                *(u32 *)writeAddress = *(volatile u32 *)(readAddress | 0xA0000000);
                offset += 4;
                readAddress += 4;
                writeAddress += 4;
            } while (offset < count);
        }
        if (size & 2) {
            data.word = *(volatile u32 *)((source + offset) | 0xA0000000);
            *(u16 *)((u8 *)((void **)&destination)[0] + offset) = data.half[0];
        }
    }
    D_8003A572 = 0;
    if (D_8003A575 != 0) {
        func_80022A60(&D_80035910);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000480C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_4470/func_8000480C.s")
