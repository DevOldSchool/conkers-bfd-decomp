#include "types.h"

/*
 * Reviewed source unit: src/game/game_193E50.c
 * Boundary evidence: docs/evidence/game_raw_display_transition_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151669A0
 * - func_15166B50
 * - func_15166D68
 * - func_15166F6C
 * - func_15166FD8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void *func_15167A68(s32, s32, s32, s32, u8, u8);
void func_1517E05C(s32, s32, s32);
void func_15043D90(s32, f32, f32, volatile s32, f32, f32, f32, f32, f32, f32);
void func_15043E68(s32, f32, f32, volatile s32, f32, f32, f32);
u32 func_150ADA20(void);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151669A0 CURRENT (781) */
void func_151669A0(s32 arg0, s32 arg1, s32 arg2, f32 arg3, u8 arg4, s32 arg5) {
    u8 *object;
    u8 *cursor;
    s32 random_offset;
    s32 byte_offset;
    f32 x;
    f32 y;
    f32 z;

    object = func_15167A68(0xD, arg5, 0xE0, 1, arg4, 1);
    if (object != 0) {
        object[0xD0] = 0xA;
        *(s16 *)(object + 0xD2) = arg0;
        *(s16 *)(object + 0xD4) = arg1;
        *(f32 *)(object + 0xD8) = arg3;
        *(s16 *)(object + 0xD6) = arg2;
        random_offset = func_150ADA20() & 0x7F;
        byte_offset = 0;
        cursor = object + 0x10;
        x = (f32)arg0;
        y = (f32)arg1;
        z = (f32)arg2;
        do {
            if (arg3 != 1.0f) {
                func_15043D90((s32)cursor, 0.0f, (f32)random_offset, 0,
                               arg3, arg3, arg3, x, y, z);
            } else {
                func_15043E68((s32)cursor, 0.0f, (f32)random_offset, 0,
                               x, y, z);
            }
            random_offset += func_150ADA20() & 0x3F;
            byte_offset += 0x40;
            cursor += 0x40;
            random_offset += 0x5A;
        } while (byte_offset != 0xC0);
        func_1517E05C(arg0, arg1, arg2);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151669A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_151669A0.s")
typedef struct EffectDescriptor193E50 {
    u8 *resource;
    s32 field04;
    s32 field08;
    s16 field0C;
    s16 field0E;
    s16 x;
    s16 y;
    s16 z;
    s16 field16;
    s16 field18;
    s16 field1A;
    u8 pad1C[3];
    u8 kind;
    s16 field20;
    s16 field22;
    s16 field24;
    s16 field26;
    s16 field28;
    u8 field2A;
    u8 field2B;
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    u8 pad30[4];
    s16 field34;
} EffectDescriptor193E50;

void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_15167D84(void *, s32, s32, s32, u8, s32);
void func_1516972C(u8 *);
void func_151EFEB8(void *, s32);
extern u8 *D_8008CA4C[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15166B50 CURRENT (3691) */
void func_15166B50(u8 *object) {
    f32 transform[4][4];
    f32 x;
    f32 y;
    f32 z;
    u8 *matrix;
    s32 offset;
    s32 remaining;
    EffectDescriptor193E50 effect;

    remaining = --object[0xD0];
    if (remaining == 5) {
        effect.resource = D_8008CA4C[0];
        effect.field04 = 0;
        effect.field08 = 4;
        effect.field0C = 0;
        effect.field16 = 0;
        effect.field18 = 0;
        effect.field1A = 0;
        effect.kind = 5;
        effect.field20 = 0;
        effect.field22 = 0;
        offset = 0;
        matrix = object + 0x10;
        effect.field24 = (s32) (*(f32 *) (object + 0xD8) * 4000.0f);
        effect.field28 = 0x200;
        effect.field2A = 0;
        effect.field2B = 0;
        effect.red = 0xFF;
        effect.green = 0xFF;
        effect.blue = 0xFF;
        effect.alpha = 0xFF;
        effect.field34 = 0;
        effect.field26 = (s32) (*(f32 *) (object + 0xD8) * 4000.0f);
        do {
            func_151EFEB8(transform, (s32) matrix);
            func_150A7960(transform, -400.0f, 10.0f, 0.0f, &x, &y, &z);
            effect.field0E = (func_150ADA20() & 0x7F) + 0x55;
            effect.x = (s32) x;
            effect.y = (s32) y;
            effect.z = (s32) z;
            func_15167D84(&effect, 0, 0, -1, object[0xC], object[1]);
            offset += 0x40;
            matrix += 0x40;
        } while (offset != 0xC0);
        return;
    }
    if (remaining == 0) {
        func_1516972C(object);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15166B50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_15166B50.s")
typedef struct DisplayCommand193E50 {
    u32 word0;
    u32 word1;
} DisplayCommand193E50;

extern u8 D_8008B3E0[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15166D68 CURRENT (2685) */
DisplayCommand193E50 *func_15166D68(DisplayCommand193E50 *displayList,
                                     u8 *object, s32 unused) {
    u8 *matrix;
    s32 offset;
    s32 vertical;
    u32 upper;
    u32 lower;

    offset = 0;
    matrix = object + 0x10;
    do {
        {
            DisplayCommand193E50 *command = displayList++;
            command->word0 = 0xDA380003;
            command->word1 = (u32) matrix;
        }
        {
            DisplayCommand193E50 *command = displayList++;
            command->word0 = 0x0100600C;
            command->word1 = (u32) D_8008B3E0;
        }
        {
            DisplayCommand193E50 *command = displayList++;
            vertical = 0x2800 - ((object[0xD0] << 12) / 10);
            upper = (u32) vertical << 16;
            command->word0 = 0x02140000;
            command->word1 = upper + 0x2000;
        }
        {
            DisplayCommand193E50 *command = displayList++;
            command->word0 = 0x02140002;
            command->word1 = upper + 0x2000;
        }
        {
            DisplayCommand193E50 *command = displayList++;
            command->word0 = 0x02140004;
            command->word1 = upper + 0x2400;
        }
        {
            DisplayCommand193E50 *command = displayList++;
            lower = (u32) (vertical + 0x800) << 16;
            command->word0 = 0x02140006;
            command->word1 = lower + 0x2000;
        }
        {
            DisplayCommand193E50 *command = displayList++;
            command->word0 = 0x02140008;
            command->word1 = lower + 0x2000;
        }
        {
            DisplayCommand193E50 *command = displayList++;
            command->word0 = 0x0214000A;
            command->word1 = lower + 0x2400;
        }
        {
            DisplayCommand193E50 *command = displayList++;
            command->word0 = 0x050A0600;
            command->word1 = 0;
        }
        {
            DisplayCommand193E50 *command = displayList++;
            command->word0 = 0x05040A00;
            command->word1 = 0;
        }
        {
            DisplayCommand193E50 *command = displayList++;
            command->word0 = 0x0502080A;
            command->word1 = 0;
        }
        {
            DisplayCommand193E50 *command = displayList++;
            command->word0 = 0x05020A04;
            command->word1 = 0;
        }
        offset += 0x40;
        matrix += 0x40;
    } while (offset != 0xC0);
    return displayList;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15166D68 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_15166D68.s")

s32 func_15094F70(s32, void *, s32, void *, s32, s32, s32, s32, s32);
extern u8 D_8009054C;
extern s32 D_800DD220;
extern s32 D_800DD224;
extern u8 *D_800DD228;
extern u8 D_800DD230;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15166F6C CURRENT (883) */
void func_15166F6C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_800DD228 = &D_8009054C;
    func_15094F70(arg0, &D_8009054C, D_800DD220, &D_800DD230, 0, 0, 0,
                   D_800DD224, 3);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15166F6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_15166F6C.s")
extern u8 D_80089470;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15166FD8 CURRENT (485) */
void *func_15166FD8(void *arg0, s32 arg1, s32 arg2) {
    u32 *temp_v1;

    temp_v1 = arg0;
    temp_v1[0] = 0xDA380003;
    temp_v1[1] = (u32)&D_80089470;
    return temp_v1 + 2;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15166FD8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_15166FD8.s")
