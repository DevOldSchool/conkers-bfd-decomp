#include "types.h"

/*
 * Reviewed source unit: src/main/init_34E0.c
 * Boundary evidence: docs/evidence/main_system_wrapper_boundaries.md
 * Storage evidence: docs/evidence/main_init_vi_layout.md
 */

/* Keep address symbols for linking and registered match evidence. */
#define vi_timer_manager_init func_800034E0
#define vi_timer_manager_thread_entry func_80003658

typedef struct ThreadState ThreadState;
typedef struct MessageQueue {
    ThreadState *receiveThreads;
    ThreadState *sendThreads;
    s32 validCount;
    s32 first;
    s32 messageCount;
    void **messages;
} MessageQueue;
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

typedef struct ViMessage {
    MessageHeader header;
    void *dramAddress;
    u32 deviceAddress;
    u32 size;
    PiHandle *handle;
} ViMessage;

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
static u64 viThreadStack[512];
static MessageQueue D_80037DD0;
static void *D_80037DE8[5];
static ViMessage D_80037E00;
static ViMessage D_80037E18;

void vi_timer_manager_init(s32 priority) {
    s32 savedMask;
    s32 oldPriority;
    s32 currentPriority;

    if (D_8002AB70.active != 0) {
        return;
    }
    func_80023EB0();
    func_80023790(&D_80037DD0, D_80037DE8, 5);
    D_80037E00.header.type = 0xD;
    D_80037E00.header.priority = 0;
    D_80037E00.header.returnQueue = 0;
    D_80037E18.header.type = 0xE;
    D_80037E18.header.priority = 0;
    D_80037E18.header.returnQueue = 0;
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
                  (u8 *)viThreadStack + sizeof(viThreadStack), priority);
    func_800242B0();
    func_80022A60(&D_80036BA0);
    func_80022DE0(savedMask);
    if (oldPriority != -1) {
        func_80022BB0(0, oldPriority);
    }
}
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
extern u64 D_800429B0;
extern u32 D_800429B8;
extern u32 D_800429BC;

void vi_timer_manager_thread_entry(void *argument) {
    ViContext *context;
    DeviceManager *manager;
    MessageHeader *message;
    static u16 D_80037E30;
    s32 first;
    u32 count;

    message = 0;
    first = 0;
    context = func_80024400();
    D_80037E30 = context->retraceCount;
    if (D_80037E30 == 0) {
        D_80037E30 = 1;
    }
    manager = argument;
    while (1) {
        func_80023440(manager->eventQueue, (void **) &message, 1);
        switch (message->type) {
        case 0xD:
            func_80024410();
            D_80037E30--;
            if (D_80037E30 == 0) {
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
