#include "types.h"

/*
 * Reviewed source unit: src/main/init_49E0.c
 * Boundary evidence: docs/evidence/main_allocator_transfer_controller_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_800049E0
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct SchedulerMessageQueue SchedulerMessageQueue;

typedef struct {
    u8 pad0[0xC];
    u32 flags;
    void *framebuffer;
    u8 pad14[4];
    u8 task[0x40];
    SchedulerMessageQueue *completionQueue;
    void *completionMessage;
} SchedulerTask;

extern SchedulerTask *D_8002AC50;
extern u8 D_8002AC5C;
void func_8515FDA0(s32);
void func_80024830(void *);
s32 func_80023580(SchedulerMessageQueue *, void *, s32);

void func_80005020(void);
extern u8 D_8003A582;
extern u8 D_8003B238;

typedef struct SchedulerClient {
    struct SchedulerClient *next;
    SchedulerMessageQueue *queue;
    u32 flags;
} SchedulerClient;

void func_80004DB0(void);
void func_80004FE0(void);
void func_80003330(u8 *);
void func_8000349C(u8 *);
s32 func_80023440(SchedulerMessageQueue *, void **, s32);
u32 func_80024A30(void);
s32 func_80024A40(void *, u64, u64, SchedulerMessageQueue *, void *);
u32 func_80024B20(u8 *);
void func_80024BA0(void);
void func_80024BC0(void *);
extern SchedulerTask *D_8002AC54;
extern s8 D_8002AC6C;
extern s8 D_8003A580;
extern u8 D_8003A581;
extern u8 D_8003A583;
extern u8 D_8003A584;
extern u8 D_8003A588;
extern u16 D_8003A5C8;
extern SchedulerMessageQueue D_8003B200;
extern SchedulerMessageQueue D_8003B218;
extern SchedulerClient *D_8003B234;
extern u8 D_8003B23A;
extern u8 D_8003B240[];
extern u8 D_800BE900[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_800049E0 CURRENT (1817) */
void func_800049E0(void *unused) {
    void *message;
    SchedulerClient *client;
    u64 delay;
    s32 audioBusy;

    D_8003A581 = 0;
    D_8003A582 = 0;
    D_8003A584 = 1;
    D_8003A583 = 0;
    *(s16 *)D_8003B240 = 1;
    message = 0;
    D_8003A5C8 = 4;
    for (;;) {
        func_80023440(&D_8003B218, &message, 1);
        switch ((s32)message) {
        case 0:
            client = D_8003B234;
            while (client != 0) {
                if ((client->flags & 1) == 0) {
                    func_80023580(client->queue, D_8003B240, 0);
                }
                client = client->next;
            }
            if ((D_8003B238 != 0xFF) && (D_8003B238 < 0xFF)) {
                D_8003B238++;
            }
            if (D_8003B23A != 0) {
                D_8003B23A--;
            }
            audioBusy = D_8003A581;
            if ((audioBusy == 0) && (D_8002AC6C == 0)) {
                if (func_80023440(&D_8003B200, (void **)&D_8002AC54, 0) == 0) {
                    delay = 200000;
                    if ((D_8003A582 != 0) || ((func_80024A30() & 0x80000000U) == 0)) {
                        delay = 20000;
                    }
                    func_80024A40(&D_8003A588, delay, 0, &D_8003B218, (void *)3);
                    D_8002AC6C = 1;
                }
            }
            if (D_8003A581 == 0) {
                func_80004DB0();
            }
            break;
        case 2:
            if (D_8003A582 == 3) {
                if (func_80024B20(D_8002AC50->task) == 1) {
                    func_80003330(D_8002AC54->task);
                    func_8000349C(D_8002AC54->task);
                    D_8003A581 = 1;
                    D_8003A582 = 4;
                } else {
                    D_8003A582 = 1;
                    func_80003330(D_8002AC54->task);
                    func_8000349C(D_8002AC54->task);
                    D_8003A581 = 1;
                    D_8003A583 = 0;
                }
            } else if (D_8003A581 != 0) {
                func_80023580(D_8002AC54->completionQueue, D_8002AC54->completionMessage, 1);
                D_8003A581 = 0;
                if (D_8003A582 == 4) {
                    func_80003330(D_8002AC50->task);
                    func_8000349C(D_8002AC50->task);
                    D_8003A580 = 1;
                    D_8003A582 = 1;
                }
            } else {
                D_8003A583 = 0;
                if (D_8003A584 == 1) {
                    func_80004FE0();
                }
            }
            break;
        case 1:
            D_8003A584 = 1;
            if (D_8003A583 == 0) {
                func_80004FE0();
            }
            break;
        case 3:
            D_8002AC6C = 0;
            if (D_8003A583 != 0) {
                func_80024BA0();
                D_8003A582 = 3;
            } else {
                func_80003330(D_8002AC54->task);
                func_8000349C(D_8002AC54->task);
                D_8003A581 = 1;
            }
            break;
        case 6:
            if (D_8002AC5C == 0) {
                func_80024BC0(D_800BE900);
            }
            break;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800049E0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_49E0/func_800049E0.s")
void func_80004F00(void);
void func_80004FE0(void);
s32 func_80023440(SchedulerMessageQueue *, void **, s32);
void *func_80024E20(void);
void *func_80024E60(void);
extern SchedulerMessageQueue D_8003B1E8;
extern u8 D_8003B239;
extern u8 D_8003B23A;

void func_80004DB0(void) {
    if (D_8003A582 == 0) {
        if (func_80023440(&D_8003B1E8, (void **)&D_8002AC50, 0) == 0) {
            if ((func_80024E20() != D_8002AC50->framebuffer) &&
                (func_80024E60() != D_8002AC50->framebuffer) &&
                ((D_8003B23A == 0) || (D_8003B238 >= D_8003B239))) {
                if ((D_8003B238 != 0xFF) &&
                    ((D_8003B238 >= D_8003B239) || (D_8003B23A == 0))) {
                    D_8003B239 = D_8003B238;
                }
                func_80004F00();
                return;
            }
            D_8003A582 = 2;
        }
    } else if (D_8003A582 == 2) {
        if ((D_8003B23A == 0) || (D_8003B238 >= D_8003B239)) {
            func_80004F00();
        }
    } else if (D_8003A582 == 6) {
        func_80004FE0();
    }
}
void func_80003330(u8 *);
void func_8000349C(u8 *);
extern SchedulerTask *D_8002AC58;
extern s8 D_8003A580;
extern u8 D_8003A583;
extern u8 D_8003A584;
extern SchedulerMessageQueue *D_8003B230;
extern u8 D_8003B240[];
extern s32 D_800BE9E4;
extern u8 D_800C35EA;

void func_80004F00(void) {
    if (D_8002AC5C == 0) {
        func_80003330(D_8002AC50->task);
        func_8000349C(D_8002AC50->task);
        D_8003A580 = 0;
        D_8002AC58 = D_8002AC50;
        D_8003A583 = 1;
        D_8003A584 = 0;
        if ((D_8003B238 == 0xFF) || ((D_8003B238 >= 0xB) && ((D_8003B238 >= 0x15) || (D_800C35EA != 1)))) {
            D_8003B238 = 2;
        }
        D_800BE9E4 = D_8003B238;
        D_8003B238 = 0;
        D_8003A582 = 1;
        func_80023580(D_8003B230, D_8003B240, 0);
    }
}
void func_80004FE0(void) {
    if ((s32)D_8003B238 <= 0) {
        D_8003A582 = 6;
        return;
    }
    func_80005020();
}
void func_80005020(void) {
    void *framebuffer;

    D_8003A582 = 0;
    framebuffer = D_8002AC50->framebuffer;
    if ((D_8002AC50->flags & 0x40) && (D_8002AC5C == 0)) {
        func_8515FDA0((s32)framebuffer);
        func_80024830(framebuffer);
    }
    func_80023580(D_8002AC50->completionQueue, D_8002AC50->completionMessage, 1);
}
