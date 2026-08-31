#include "types.h"

/*
 * m2c-derived implementation for func_80001050. The function matches both
 * profiles; this source remains outside game/done until its exact file
 * boundary is integrated into the full-ROM link.
 */
typedef char M2C_UNK;

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

M2C_UNK queue_message(M2C_UNK *, M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK *, s32);
M2C_UNK configure_task(M2C_UNK, M2C_UNK);
M2C_UNK queue_start(M2C_UNK *, s32);
M2C_UNK reset_task(void);
M2C_UNK set_interrupt_mask(s32);
s32 get_interrupt_mask(void);
M2C_UNK enable_interrupts(s32);
M2C_UNK start_task(M2C_UNK *);
extern M2C_UNK D_100010F8;
extern M2C_UNK bss_start;
extern M2C_UNK task_stack;
extern M2C_UNK task_queue;
extern M2C_UNK queue_end;

void func_80001050(void) {
    queue_start(&bss_start, &queue_end - &bss_start);
    configure_task(1, 0x1F);
    reset_task();
    set_interrupt_mask(get_interrupt_mask() | 0x20000000 | 0x04000000);
    enable_interrupts(0x01000000);
    queue_message(&task_queue, 1, &D_100010F8, 0, &task_stack, 5);
    start_task(&task_queue);
}
