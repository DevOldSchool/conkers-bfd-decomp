#include "types.h"

/*
 * Reviewed source unit: src/game/game_6D800.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_dispatcher_callback_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15040350
 * - func_150403C8
 * - func_15040754
 * - func_1504082C
 * - func_15040A40
 * - func_15040A78
 * - func_15040CC8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

extern s32 D_800848B0[];
extern void (*D_800844B0[])(void *);
extern s32 D_800C6860[];
extern s8 D_800C68A0;
extern s8 D_800C68A1;
void func_150403C8(s32, s32, s32);
void func_1500390C(s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15040350 CURRENT (795) */
void func_15040350(s32 arg0, s32 arg1) {
    s32 *entry;
    s32 saved_arg0;

    saved_arg0 = arg0;
    D_800848B0[0] = 0;
    D_800C68A0 = 0;
    D_800C68A1 = 0;
    arg0 = (s32)&D_800C68A0;
    entry = D_800C6860;
fill_entry:
    entry += 4;
    entry[-3] = -1;
    entry[-2] = -1;
    entry[-1] = -1;
    entry[-4] = -1;
    if ((u32)entry != (u32)arg0) {
        goto fill_entry;
    }
    D_800C6860[0] = 0;
    func_150403C8(saved_arg0, arg1, 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15040350 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6D800/func_15040350.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_6D800/func_150403C8.s")
s32 func_1504072C(s32 arg0) {
    if (arg0 & 7) {
        return 1;
    }
    return 0;
}
void func_15040748(s32 arg0) {

}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15040754 CURRENT (85) */
s32 func_15040754(void *arg0) {
    u32 temp_v1;

    temp_v1 = *(u32 *)((u8 *)arg0 + 0);
    if ((s32)(((temp_v1 >> 1) & 0x7F) - ((temp_v1 >> 0xC) & 0xFF)) < 0) {
        return 1;
    }
    return func_1504072C(*(s32 *)((u8 *)arg0 + 4));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15040754 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6D800/func_15040754.s")
void func_150407A0(void) {

}
void func_150407A8(s32 arg0) {
}
void func_150407B4(s32 arg0) {
}
void func_150407C0(s32 arg0) {
}
void func_150407CC(s32 arg0) {
}
void func_150407D8(s32 arg0) {
}
void func_150407E4(s32 arg0) {
}
void func_150407F0(s32 arg0) {
}
void func_150407FC(s32 arg0) {
}
void func_15040808(s32 arg0) {
}
void func_15040814(s32 arg0) {
}
void func_15040820(s32 arg0) {
}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_1504082C CURRENT (650) */
s32 func_1504082C(u32 *arg0) {
    u32 temp_v1;

    temp_v1 = *arg0;
    if (((temp_v1 >> 0x10) & 1) || ((temp_v1 >> 8) & 0xFF & 1) || (temp_v1 & 0xFF & 1)) {
        return 1;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1504082C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6D800/func_1504082C.s")
void func_1504086C(s32 arg0) {
}
void func_15040878(s32 arg0) {
}
void func_15040884(s32 arg0) {
}
void func_15040890(s32 arg0) {
}
void func_1504089C(s32 arg0) {
}
void func_150408A8(s32 arg0) {
}
void func_150408B4(s32 arg0) {
}
void func_150408C0(s32 arg0) {
}
void func_150408CC(s32 *arg0) {
    func_1504072C(arg0[1]);
}
void func_150408F0(s32 arg0) {
}
void func_150408FC(s32 arg0) {

}
void func_15040908(s32 arg0) {

}
void func_15040914(s32 arg0) {

}
void func_15040920(s32 arg0) {

}
void func_1504092C(s32 arg0) {

}
void func_15040938(s32 arg0) {

}
void func_15040944(s32 arg0) {

}
void func_15040950(s32 arg0) {

}
void func_1504095C(s32 arg0) {

}
void func_15040968(s32 arg0) {

}
void func_15040974(s32 arg0) {

}
void func_15040980(s32 arg0) {

}
void func_1504098C(s32 arg0) {

}
void func_15040998(s32 arg0) {

}
void func_150409A4(s32 arg0) {

}
void func_150409B0(s32 arg0) {

}
void func_150409BC(s32 arg0) {

}
void func_150409C8(s32 arg0) {

}
void func_150409D4(s32 arg0) {

}
void func_150409E0(s32 arg0) {

}
void func_150409EC(s32 arg0) {

}
void func_150409F8(s32 arg0) {

}
void func_15040A04(s32 arg0) {

}
void func_15040A10(s32 arg0) {

}
void func_15040A1C(s32 arg0) {

}
void func_15040A28(s32 arg0) {

}
void func_15040A34(s32 arg0) {

}
#if 0 /* CONKER_DEFERRED_CANDIDATE func_15040A40 CURRENT (200) */
void func_15040A40(s32 arg0) {

}
#endif /* CONKER_DEFERRED_CANDIDATE func_15040A40 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6D800/func_15040A40.s")
void func_15040A54(s32 arg0) {

}
void func_15040A60(s32 arg0) {

}
void func_15040A6C(s32 arg0) {

}
typedef struct {
    u32 word0;
    u32 word1;
} Game6D800Command;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15040A78 CURRENT (5288) */
void func_15040A78(u32 arg0, u32 arg1, u32 arg2) {
    u32 stack[20];
    u8 active;
    s32 depth;
    s32 *segment;
    u32 current;
    u8 opcode;
    u32 address;
    u32 word;
    s32 offset;
    s32 count;
    s32 index;

    depth = 0;
    for (segment = D_800C6860; segment != D_800C6860 + 16; segment++) {
        *segment = -1;
    }
    D_800C6860[0] = 0;
    active = 0;
    current = arg0;
    if (arg2 >= current) {
        do {
            if (current == arg1) {
                active = 1;
            }
            opcode = *(u8 *)current;
            if (active) {
                D_800844B0[opcode]((void *)current);
            }
            if (current == arg2) {
                active = 0;
            }
            switch (opcode) {
            case 0xDF:
                depth--;
                current = stack[depth];
                break;
            case 0xDE:
                stack[depth] = current + 8;
                address = ((Game6D800Command *)current)->word1;
                depth++;
                current += 8;
                if (D_800C6860[(address >> 24) & 0xF] != -1) {
                    current = ((address & 0xFFFFFF) + D_800C6860[(address >> 24) & 0xF]) | 0x80000000;
                } else {
                    depth--;
                }
                break;
            case 0xDB:
                word = ((Game6D800Command *)current)->word0;
                address = ((Game6D800Command *)current)->word1;
                offset = word & 0xFFFF;
                if (((word >> 16) & 0xFF) == 6) {
                    D_800C6860[offset >> 2] = address;
                }
                current += 8;
                break;
            case 1:
                if (active) {
                    word = ((Game6D800Command *)current)->word0;
                    count = (word >> 12) & 0xFF;
                    index = 0;
                    if (count > 0) {
                        do {
                            index++;
                        } while (index != count);
                    }
                }
                current += 8;
                break;
            case 0xDA:
                current += 8;
                break;
            case 0xDC:
                current += 8;
                break;
            default:
                current += 8;
                break;
            }
        } while (arg2 >= current || depth > 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15040A78 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6D800/func_15040A78.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15040CC8 CURRENT (1908) */
void func_15040CC8(s32 arg0) {
    s32 var_s0;
    u8 *var_s0_2;

    var_s0 = 0;
    do {
        var_s0 += 1;
    } while (var_s0 < 0x10);
    var_s0_2 = (u8 *)arg0 - 0xA0;
    do {
        D_800844B0[*var_s0_2](var_s0_2);
        var_s0_2 += 8;
    } while (var_s0_2 != (u8 *)arg0 - 0x50);
    if (D_800848B0[0] != 0) {
        func_1500390C(D_800848B0[0]);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15040CC8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_6D800/func_15040CC8.s")
void func_15040D60(s32 arg0) {

}
void func_15040D6C(s32 arg0) {

}
void func_15040D78(s32 arg0) {

}
