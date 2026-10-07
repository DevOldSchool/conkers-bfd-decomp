#include "types.h"

/*
 * Reviewed source unit: src/main/init_4470.c
 * Boundary evidence: docs/evidence/main_allocator_transfer_controller_boundaries.md
 *
 * TODO: Implement these source-unit functions:
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
extern void *D_80038904[];
extern TransferMessageQueue D_80038908[];
extern u8 D_8003A570;

void func_80004470(void) {
    s32 index;

    func_800030A0(0x96, &D_800388B0, D_800380E0, 0xC8);
    index = 0;
    for (;;) {
        func_80023790(&D_80038908[index], &D_800388F8[index], 1);
        index++;
        if (D_80038904 == &D_800388F8[index]) {
            break;
        }
    }
    func_80023790(&D_800388C8, D_80038400, 0x12C);
    D_8003A570 = 0;
    D_8003A571 = 0;
}
void func_8000480C(u32, void *, u32);
extern TransferIoMessage D_80038950[];

void func_80004514(u32 source, void *destination, u32 size, s32 blocking) {
    TransferMessageQueue *queue;
    TransferIoMessage request;
    TransferIoMessage *message;
    s32 index;
    u8 messageIndex;

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
        messageIndex = D_8003A570;
        message = &D_80038950[messageIndex];
        queue = &D_800388C8;
        if (messageIndex == 0x12B) {
            D_8003A570 = 0;
        } else {
            D_8003A570 = messageIndex + 1;
        }
        D_8003A571++;
    } else {
        message = &request;
        queue = &D_80038908[index];
    }
    func_80022D10(destination, ((s32 *)&size)[0]);
    func_80024920(message, 0, 0, source, destination, size, queue);
    if (blocking != 0) {
        func_80023440(queue, 0, 1);
    }
}
void func_80004674(void) {
    s32 i;

    for (i = 0; i < (s32)D_8003A571; i++) {
        func_80023440(&D_800388C8, 0, 1);
    }
    D_8003A571 = 0;
}
void func_800046E4(u32 source, void *destination, u32 size) {
    TransferIoMessage request;
    void *response;
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
        do {
            if (size - processed < 0x14000U) {
                chunk = size - processed;
            } else {
                chunk = 0x14000;
            }
            func_80024920(&request, 0, 0, source, destination, chunk, &D_80038908[index]);
            func_80023440(&D_80038908[index], &response, 1);
            processed += chunk;
            source += chunk;
            destination = (u8 *)destination + chunk;
        } while (processed < size);
    }
}
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

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000480C CURRENT (1154) */
void func_8000480C(u32 source, void *destination, u32 size) {
    u32 count;
    TransferWord data;
    u32 status;
    u32 offset;
    u32 readAddress;
    u8 *writeAddress;

    D_8003A572 = 1;
    size = (size + 1) & ~1U;
    while (D_8003A573 != 0) {
    }
    while ((status = *(volatile u32 *)0xA4600010) & 3) {
    }
    source |= D_80000308;
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
        count = size - 2;
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
