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
