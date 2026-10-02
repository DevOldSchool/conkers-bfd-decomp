#include "types.h"

/*
 * Reviewed source unit: src/main/init_34E0.c
 * Boundary evidence: docs/evidence/main_system_wrapper_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_800034E0
 * - func_80003658
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct ThreadState ThreadState;
typedef struct MessageQueue MessageQueue;
typedef struct PiHandle PiHandle;

typedef struct DeviceManager {
    s32 active;
    ThreadState *thread;
    MessageQueue *commandQueue;
    MessageQueue *eventQueue;
    MessageQueue *accessQueue;
    s32 (*dma)(s32, u32, void *, u32);
    s32 (*extendedDma)(PiHandle *, s32, u32, void *, u32);
} DeviceManager;

typedef struct MessageHeader {
    u16 type;
    u8 priority;
    u8 status;
    MessageQueue *returnQueue;
} MessageHeader;

void func_80023EB0(void);
void func_800242B0(void);
void func_80023790(MessageQueue *, void **, s32);
void func_800237C0(s32, MessageQueue *, void *);
s32 func_80023830(ThreadState *);
void func_80022BB0(ThreadState *, s32);
s32 func_80022DC0(void);
void func_80022DE0(s32);
void func_80022A60(ThreadState *);
void func_800037F0(ThreadState *, s32, void (*)(void *), void *, void *, s32);
void D_10003658(void *);
extern DeviceManager D_8002AB70;
extern ThreadState D_80036BA0;
extern MessageQueue D_80037DD0;
extern void *D_80037DE8[5];
extern MessageHeader D_80037E00;
extern MessageHeader D_80037E18;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_800034E0 CURRENT (350) */
void func_800034E0(s32 priority) {
    s32 savedMask;
    s32 oldPriority;
    s32 currentPriority;

    if (D_8002AB70.active != 0) {
        return;
    }
    func_80023EB0();
    func_80023790(&D_80037DD0, D_80037DE8, 5);
    D_80037E00.type = 0xD;
    D_80037E00.priority = 0;
    D_80037E00.returnQueue = 0;
    D_80037E18.type = 0xE;
    D_80037E18.priority = 0;
    D_80037E18.returnQueue = 0;
    func_800237C0(7, &D_80037DD0, &D_80037E00);
    func_800237C0(3, &D_80037DD0, &D_80037E18);
    oldPriority = -1;
    currentPriority = func_80023830(0);
    if (currentPriority < priority) {
        oldPriority = currentPriority;
        func_80022BB0(0, priority);
    }
    savedMask = func_80022DC0();
    D_8002AB70.active = 1;
    D_8002AB70.thread = &D_80036BA0;
    D_8002AB70.commandQueue = &D_80037DD0;
    D_8002AB70.eventQueue = &D_80037DD0;
    D_8002AB70.accessQueue = 0;
    D_8002AB70.dma = 0;
    D_8002AB70.extendedDma = 0;
    func_800037F0(&D_80036BA0, 0, D_10003658, &D_8002AB70,
                  &D_80037DD0, priority);
    func_800242B0();
    func_80022A60(&D_80036BA0);
    func_80022DE0(savedMask);
    if (oldPriority != -1) {
        func_80022BB0(0, oldPriority);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800034E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_34E0/func_800034E0.s")
typedef struct ViContext {
    u16 state;
    u16 retraceCount;
    void *frame;
    void *mode;
    u32 control;
    MessageQueue *messageQueue;
    void *message;
} ViContext;

s32 func_80023440(MessageQueue *, void **, s32);
s32 func_80023580(MessageQueue *, void *, s32);
void func_80023F3C(void);
ViContext *func_80024400(void);
void func_80024410(void);
u32 func_80024770(void);
extern u16 D_80037E30;
extern u64 D_800429B0;
extern u32 D_800429B8;
extern u32 D_800429BC;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80003658 CURRENT (1484) */
void func_80003658(void *argument) {
    ViContext *context;
    DeviceManager *manager;
    MessageHeader *message;
    s32 first;
    u32 count;
    u16 retrace;

    message = 0;
    first = 0;
    context = func_80024400();
    retrace = context->retraceCount;
    D_80037E30 = retrace;
    if (retrace == 0) {
        D_80037E30 = 1;
    }
    manager = argument;
    while (1) {
        func_80023440(manager->eventQueue, (void **) &message, 1);
        switch (message->type) {
        case 0xD:
            func_80024410();
            retrace = D_80037E30 - 1;
            D_80037E30 = retrace;
            if (retrace == 0) {
                context = func_80024400();
                if (context->messageQueue != 0) {
                    func_80023580(context->messageQueue, context->message, 0);
                }
                D_80037E30 = context->retraceCount;
            }
            D_800429BC++;
            if (first) {
                count = func_80024770();
                D_800429B0 = count;
                first = 0;
            }
            count = D_800429B8;
            D_800429B8 = func_80024770();
            count = D_800429B8 - count;
            D_800429B0 = D_800429B0 + count;
            break;
        case 0xE:
            func_80023F3C();
            break;
        default:
            break;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80003658 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_34E0/func_80003658.s")
