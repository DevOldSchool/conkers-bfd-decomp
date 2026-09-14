#include "types.h"

/*
 * Reviewed source unit: src/game/game_126BD0.c
 * Boundary evidence: docs/evidence/game_raw_structural_families_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150F9720
 * - func_150F97EC
 * - func_150F9950
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct Game126BD0LookupRecord {
    u8 first;
    u8 second;
} Game126BD0LookupRecord;

typedef struct Game126BD0Message {
    s32 value;
    u8 selector;
} Game126BD0Message;

extern Game126BD0LookupRecord D_800A1C40[];
void func_151494E0(Game126BD0Message *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150F9720 CURRENT (908) */
void func_150F9720(s32 arg0) {
    Game126BD0Message message;
    Game126BD0Message *message_ptr;
    Game126BD0LookupRecord *record;
    s32 index;

    index = arg0 & 0xFF;
    record = &D_800A1C40[index];
    message.value = 0;
    message_ptr = &message;
    message.selector = record->first;
    func_151494E0(message_ptr, 0x42);
    message.selector = record->second;
    func_151494E0(message_ptr, 0x42);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150F9720 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_126BD0/func_150F9720.s")
void func_150F9788(s32 arg0) {

}
void func_1514933C(s32);

void func_150F9794(s32 arg0) {
    func_150F9788(arg0);
    func_1514933C(arg0);
}
void func_15149368(s32 arg0);

void func_150F97C0(s32 arg0) {
    func_150F9788(arg0);
    func_15149368(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_126BD0/func_150F97EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_126BD0/func_150F9950.s")
