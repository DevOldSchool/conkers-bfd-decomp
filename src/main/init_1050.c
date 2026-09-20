#include "types.h"

/*
 * Reviewed source unit: src/main/init_1050.c
 * Boundary evidence: docs/evidence/main_bootstrap_source_units.md
 *
 * TODO: Implement these source-unit functions:
 * - func_80001194
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#if PROFILE_US
#define queue_start func_800226F0
#define configure_task func_800061F8
#define reset_task func_80022790
#define set_interrupt_mask func_80022A30
#define get_interrupt_mask func_80022A40
#define enable_interrupts func_80022A50
#define queue_message func_800037F0
#define start_task func_80022A60
#define bss_start D_8002D4B0
#define task_stack D_8002D8B0
#define task_queue D_800318B0
#define queue_end D_80043B40
#else
#define queue_start func_80022A10
#define configure_task func_800064E8
#define reset_task func_80022AB0
#define set_interrupt_mask func_80022D50
#define get_interrupt_mask func_80022D60
#define enable_interrupts func_80022D70
#define queue_message func_80003880
#define start_task func_80022D80
#define bss_start D_8002D810
#define task_stack D_8002DC10
#define task_queue D_80031C10
#define queue_end D_80043ED0
#endif

void queue_message(void *, s32, void *, s32, void *, s32);
void configure_task(s32, s32);
void func_800034E0(s32);
void func_80003920(void);
void func_80003930(void);
void func_80003BD0(void);
s32 func_80003C40(s32, s32, s32, s32);
s32 func_80003C6C(s32, s32, s32, s32, s32);
void func_80004470(void);
s32 func_80004514(s32, void *, u32, s32);
void func_80005218(void);
s32 func_80006240(s32, s32 *, s32);
void func_8000709C(void);
void func_80022C90(void *, s32);
void func_80022D10(void *, s32);
void func_80022BB0(void *, s32);
void func_80001420(void);
void func_80004074(s32);
void func_80005B04(s32);
void func_80005BE0(void);
void func_85007830(void);
void queue_start(void *, s32);
void reset_task(void);
void set_interrupt_mask(s32);
s32 get_interrupt_mask(void);
void enable_interrupts(s32);
void start_task(void *);
extern u8 D_100010F8;
extern u8 D_10001194;
extern u8 D_15000000;
extern u8 D_151FA130;
extern u8 D_19EA88;
extern u8 D_42450;
extern s32 D_80000310;
extern s32 D_8000030C;
extern u8 D_8002AC5C;
extern s32 D_8002AAE8[2];
extern u8 D_80032B30;
extern u8 D_80033330;
extern s32 D_800354F8;
extern s32 D_800354FC;
extern s32 D_8003809C;
extern s32 D_8003BE74;
extern s32 D_80082B20;
extern u8 D_800E9D10;
extern u8 bss_start;
extern u8 task_stack;
extern u8 task_queue;
extern u8 D_80031AE0;
extern u8 queue_end;

void func_80001050(void) {
    queue_start(&bss_start, &queue_end - &bss_start);
    configure_task(1, 0x1F);
    reset_task();
    set_interrupt_mask(get_interrupt_mask() | 0x20000000 | 0x04000000);
    enable_interrupts(0x01000000);
    queue_message(&task_queue, 1, &D_100010F8, 0, &task_stack, 5);
    start_task(&task_queue);
}

void func_800010F8(s32 arg0) {
    func_80004470();
    queue_message(&D_80031AE0, 3, &D_10001194, arg0, &task_queue, 10);
    if ((D_8002AC5C == 0) && (D_80000310 == 0x17D9)) {
        start_task(&D_80031AE0);
    }
    func_80022BB0(&task_queue, 0);
loop:
    goto loop;
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80001194 CURRENT (60) */
void func_80001194(s32 arg0) {
    u32 sp28;
    u32 block_count;
    s32 sp44;
    s32 sp40;
    s32 offset;
    s32 clear_size;
    s32 i;
    s32 *framebuffers;

    func_80005218();
    clear_size = 0x80400000 - (s32)&queue_end;
    if (D_8000030C == 0) {
        queue_start(&queue_end, clear_size);
    } else {
        queue_start(&D_800E9D10, 0x80400000 - (s32)&D_800E9D10);
    }
    func_80022C90(&queue_end, clear_size);
    func_80022D10(&queue_end, clear_size);
    func_80003920();
    func_80003930();
    func_80003BD0();
    func_8000709C();
    if (!clear_size) {
    }
    block_count = func_80003C6C(0x1ECC0, 0xFF, 3, 1, 0);
    clear_size = (s32)D_8002AAE8;
    framebuffers = (s32 *)clear_size;
    sp40 = 0x10000;
    if (!sp40) {
    }
    framebuffers[0] = block_count;
    goto allocate_second_framebuffer;
allocate_second_framebuffer:
    sp40 |= 0xECC0;
    framebuffers[1] = func_80003C6C(sp40, 0xFF, 3, 1, 0);
    func_800034E0(0xFE);
    offset = (s32)&D_42450;
    func_80004514(offset, &D_80082B20, 0x10U, 1);
    if (!offset) {
    }
    sp44 = D_80082B20 + offset;
    sp28 = (u32)&D_19EA88 - sp44;
    sp40 = func_80003C40(sp28, 1, 2, 0);
    func_80004514(sp44, (void *)sp40, sp28, 1);
    func_80006240(sp40, &D_80082B20, D_8003809C);
    func_80004074(sp40);
    D_800354F8 = ((s32)&D_80033330 + 0xF) & ~0xF;
    block_count = ((u32)&D_151FA130 - (u32)&D_15000000 + 0xFFF) >> 12;
    D_800354FC = ((s32)&D_80032B30 + 0xF) & ~0xF;
    sp28 = block_count + 1;
    func_80004514(offset + 4, (void *)D_800354FC,
                  ((((block_count + 2) << 2) + 0xF) | 0xF) ^ 0xF, 1);
    for (i = 0; i < sp28; i++) {
        ((s32 *)D_800354FC)[i] =
            (((s32 *)D_800354FC)[i] ^ 0x8039CCCA) + offset;
    }
    D_8003BE74 = 0;
    func_80005B04(0xEB);
    func_80001420();
    func_80005BE0();
    func_85007830();
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80001194 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_1050/func_80001194.s")
