#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_100810.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_owner_audio_effect.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150D3360
 * - func_150D3A68
 * - func_150D3FD4
 * - func_150D4300
 * - func_150D49C0
 * - func_150D4D58
 * - func_150D5124
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

void func_150D4C2C(void *arg0);

#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D3360.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D3A68.s")
extern f32 D_800A0A10;
extern u8 D_800C35EA;
extern void *D_800DBFF0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D3FD4 CURRENT (6598) */
s32 func_150D3FD4(void *arg0) {
    void **volatile sp8C;
    u8 *sp88;
    volatile f32 sp84;
    volatile f32 sp80;
    u8 *sp7C;
    f32 sourceX;
    f32 sourceY;
    f32 sourceZ;
    f32 scale;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fs2;
    f32 var_fs3;
    f32 var_fv0;
    f32 var_fv1;
    void **temp_t6;
    s32 temp_a1;
    s32 var_a0;
    u8 *var_t0;
    s32 var_v0;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_t6 = *(void ***)((u8 *)arg0 + 0x98);
    sp8C = temp_t6;
    var_t0 = *(u8 **)((u8 *)arg0 + 0x94);
    if (D_800C35EA != 1) {
        sp88 = var_t0;
        var_t0 = sp88;
        if (func_1515C0F8(*temp_t6, &sp7C) != 0) {
            var_fv1 = func_15143E64(sp7C);
        } else {
            var_fv1 = 0.0f;
        }
    } else if (*(s32 *)((u8 *)D_800DBFF0 + 0x5F0) & 4) {
        var_fv1 = 0.0f;
    } else {
        var_fv1 = 128.0f;
    }
    if (var_fv1 < 10.0f) {
        var_fs3 = 0.0f;
    } else if (var_fv1 > 70.0f) {
        var_fs3 = 600.0f;
    } else {
        var_fs3 = (var_fv1 - 10.0f) * D_800A0A10 * 600.0f;
    }
    if (*(s8 *)((u8 *)arg0 + 0x2C) >= 2) {
        var_fs2 = 0.0f;
        var_a0 = *(s8 *)((u8 *)arg0 + 0x2E) - 1;
        if (var_a0 < 0) {
            var_a0 = *(u8 *)((u8 *)arg0 + 0x25) - 1;
        }
        if (var_a0 != *(s8 *)((u8 *)arg0 + 0x2D)) {
            do {
                temp_a1 = var_a0;
                var_a0 -= 1;
                if (var_a0 < 0) {
                    var_a0 = *(u8 *)((u8 *)arg0 + 0x25) - 1;
                }
                temp_v1 = (temp_a1 * 0x14) + var_t0;
                temp_ft4 = *(f32 *)((u8 *)temp_v1 + 0xC);
                var_fs2 += temp_ft4;
                if (var_fs3 < var_fs2) {
                    if (temp_ft4 != 0.0f) {
                        temp_fa1 = (var_fs2 - var_fs3) / temp_ft4;
                        sourceX = *(f32 *)((u8 *)temp_v1 + 0);
                        sourceY = *(f32 *)((u8 *)temp_v1 + 4);
                        sourceZ = *(f32 *)((u8 *)temp_v1 + 8);
                        temp_v0 = (var_a0 * 0x14) + var_t0;
                        temp_fv0 = *(f32 *)((u8 *)temp_v0 + 0);
                        temp_fv1 = *(f32 *)((u8 *)temp_v0 + 4);
                        temp_fa0 = *(f32 *)((u8 *)temp_v0 + 8);
                        *(f32 *)((u8 *)temp_v0 + 0) = (f32) (temp_fv0 - ((temp_fv0 - sourceX) * temp_fa1));
                        *(f32 *)((u8 *)temp_v0 + 4) = (f32) (temp_fv1 - ((temp_fv1 - sourceY) * temp_fa1));
                        *(f32 *)((u8 *)temp_v0 + 8) = (f32) (temp_fa0 - ((temp_fa0 - sourceZ) * temp_fa1));
                        *(f32 *)((u8 *)temp_v1 + 0xC) = (f32) (*(f32 *)((u8 *)temp_v1 + 0xC) * (1.0f - temp_fa1));
                    }
                    var_fs2 = var_fs3;
                    if (var_a0 != *(s8 *)((u8 *)arg0 + 0x2D)) {
                        do {
                            *(s8 *)((u8 *)arg0 + 0x2D) = (s8) (*(s8 *)((u8 *)arg0 + 0x2D) + 1);
                            if (*(u8 *)((u8 *)arg0 + 0x25) == *(s8 *)((u8 *)arg0 + 0x2D)) {
                                *(s8 *)((u8 *)arg0 + 0x2D) = 0;
                            }
                            *(s8 *)((u8 *)arg0 + 0x2C) = (s8) (*(s8 *)((u8 *)arg0 + 0x2C) - 1);
                        } while (var_a0 != *(s8 *)((u8 *)arg0 + 0x2D));
                    }
                }
            } while (var_a0 != *(s8 *)((u8 *)arg0 + 0x2D));
        }
        if (var_fs2 != 0.0f) {
            var_fa0 = 1.0f / var_fs2;
        } else {
            var_fa0 = 0.0f;
        }
        sp80 = var_fa0;
        sp84 = var_fs2;
    }
    if (*(s8 *)((u8 *)arg0 + 0x2C) >= 2) {
        var_v0 = *(s8 *)((u8 *)arg0 + 0x2E);
        var_fv0 = sp84;
        scale = *(f32 *)((u8 *)sp8C + 0x14) * sp80;
        do {
            var_v0 -= 1;
            if (var_v0 < 0) {
                var_v0 = *(u8 *)((u8 *)arg0 + 0x25) - 1;
            }
            temp_v1_2 = (var_v0 * 0x14) + var_t0;
            *(f32 *)((u8 *)temp_v1_2 + 0x10) = (f32) (var_fv0 * scale);
            var_fv0 -= *(f32 *)((u8 *)temp_v1_2 + 0xC);
        } while (var_v0 != *(s8 *)((u8 *)arg0 + 0x2D));
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D3FD4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D3FD4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D4300.s")
void *func_1503195C(void *, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D49C0 CURRENT (1441) */
void func_150D49C0(u8 *arg0, void *arg1, s32 arg2) {
    s32 var_v0;
    u8 *temp_a0;
    u8 *temp_v0;
    u8 *temp_v1;
    s32 var_a1;

    arg2 &= 0xFF;
    temp_v1 = *(u8 **)(arg0 + 0x98);
    if ((arg2 == 0) || (arg2 == 0x2E) || (arg2 == 3)) {
        if ((*(u8 **)arg1 == *(u8 **)temp_v1) ||
            (temp_v1[4] == *(u8 *)((u8 *)arg1 + 4))) {
            func_1516972C((s32)arg0);
        }
    } else if (arg2 == 0x2D) {
        temp_v0 = *(u8 **)arg1;
        temp_a0 = *(u8 **)temp_v1;
        if (temp_v0 == temp_a0) {
            temp_a0 = *(u8 **)((u8 *)arg1 + 4);
            *(u8 **)temp_v1 = temp_a0;
            var_a1 = 0x79;
            temp_v1[4] = *((u8 *)arg1 + 9);
            if (temp_a0[4] == 0x48) {
                var_a1 = 0x7A;
            }
            var_v0 = (s32)func_1503195C(temp_a0, var_a1, 0);
            goto block_15;
        }
        if (*(u8 **)((u8 *)arg1 + 4) == temp_a0) {
            *(u8 **)temp_v1 = temp_v0;
            var_a1 = 0x79;
            temp_v1[4] = *((u8 *)arg1 + 8);
            if (temp_v0[4] == 0x48) {
                var_a1 = 0x7A;
            }
            var_v0 = (s32)func_1503195C(temp_v0, var_a1, 0);
block_15:
            *(s32 *)(temp_v1 + 8) = var_v0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D49C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D49C0.s")
s32 func_1514654C(void *, s32, s32, void **, void **, s32);
extern u8 D_800A09D0;
extern u8 D_800A09DC;

s32 func_150D4AE0(f32 *arg0, f32 *arg1, void *arg2, s32 arg3) {
    void *sp30[2];
    void *sp28[2];

    if (*(s32 *)((u8 *)arg2 + 0x1D4) != 0) {
        sp30[0] = &D_800A09D0;
        sp30[1] = &D_800A09DC;
        sp28[0] = arg0;
        sp28[1] = arg1;
        if (func_1514654C(arg2, arg3, 0, sp30, sp28, 2) != 0) {
            return 1;
        }
        return 0;
    }
    arg0[0] = *(f32 *)((u8 *)arg2 + 0x14);
    arg0[1] = *(f32 *)((u8 *)arg2 + 0x18) + 100.0f;
    arg0[2] = *(f32 *)((u8 *)arg2 + 0x1C);
    arg1[0] = *(f32 *)((u8 *)arg2 + 0x14);
    arg1[1] = *(f32 *)((u8 *)arg2 + 0x18) + 100.0f + 500.0f;
    arg1[2] = *(f32 *)((u8 *)arg2 + 0x1C);
    return 2;
}
void func_150D4BD4(void *arg0) {
    func_150D4C2C(arg0);
    func_151478F4(arg0);
}
void func_150D4C00(void *arg0) {
    func_150D4C2C(arg0);
    func_15147928(arg0);
}
void func_1000FD38(void *, void *, s32);
extern s8 D_8008FD8C;
s32 func_150D5124(u8 *, s32, u32 *, s32, s32 *, s32, u16 *);

void func_150D4C2C(void *arg0) {
    void *temp_s0;

    temp_s0 = *(void **)((u8 *)arg0 + 0x98);
    if (D_8008FD8C < 5) {
        func_1000FD38((void *)&func_150D5124, temp_s0, 0x5B3);
    }
    func_1000FD38((void *)&func_150D5124, temp_s0, 0x5B4);
    func_1000FD38((void *)&func_150D5124, temp_s0, 0x5BC);
    if (*(void **)((u8 *)temp_s0 + 0xC) != 0) {
        func_1516972C(*(void **)((u8 *)temp_s0 + 0xC));
    }
    if (*(void **)((u8 *)temp_s0 + 0x10) != 0) {
        func_1516972C(*(void **)((u8 *)temp_s0 + 0x10));
    }
}
extern s32 D_800BE9E4;
extern s32 D_800A09C0[];
extern f32 D_800A0A14;
s32 func_150ADA20(void);

s32 func_150D4CC4(void *arg0) {
    f32 temp_fv0;
    void *temp_v1;

    temp_v1 = (u8 *)arg0 + 0x110;
    *(s16 *)((u8 *)arg0 + 0x170) =
        (s16)(*(s16 *)((u8 *)arg0 + 0x170) - D_800BE9E4);
    if (*(s16 *)((u8 *)arg0 + 0x170) < 0) {
        *(s8 *)((u8 *)arg0 + 0x18) =
            (s8)D_800A09C0[func_150ADA20() & 3];
        *(s16 *)((u8 *)arg0 + 0x170) =
            (s16)((func_150ADA20() & 7) + 3);
    }
    temp_fv0 = *(f32 *)((u8 *)temp_v1 + 0x48);
    *(f32 *)((u8 *)temp_v1 + 0x48) +=
        (*(f32 *)((u8 *)arg0 + 0x174) - temp_fv0) * D_800A0A14;
    return 1;
}

typedef struct {
    s32 field00, field04;
    s16 field08, field0A;
    s32 field0C, field10;
    u8 colors[8];
    u8 field1C, field1D;
    s16 field1E, field20, field22;
    f32 scale, size1, size2;
    Vec3f position, base, velocity;
    f32 field54;
    s32 flags, field5C;
    u8 field60, field61;
    s8 field62, field63, field64;
    u8 field65, field66, pad67[9];
} Game100810Descriptor;

f32 func_150ADA68(void);
void func_15143794(s16, s16, f32, void *);
extern f32 D_800A0A18, D_800A0A1C, D_800A0A20, D_800A0A24, D_800A0A28;
extern Vec3f D_800A5480;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D4D58 CURRENT (2653) */
void func_150D4D58(Vec3f *arg0, Vec3f *arg1, f32 arg2,
                   s32 arg3, s32 arg4) {
    Game100810Descriptor packet;
    s16 yawBase;
    s32 count;
    s32 first, second;
    f32 scaleBase, scaleRange;

    count = (u32)func_150ADA20() % 11U;
    packet.field08 = 0x2203;
    packet.field00 = 0x200005;
    packet.field04 = 0;
    packet.field0C = 0;
    packet.field10 = 0;
    packet.colors[0] = 255;
    packet.colors[1] = 255;
    packet.colors[2] = 255;
    packet.colors[3] = 255;
    packet.colors[4] = 255;
    packet.colors[5] = 255;
    packet.colors[6] = 255;
    packet.field1C = 255;
    packet.position = *arg0;
    packet.base = D_800A5480;
    packet.field1E = 10;
    packet.field20 = 25;
    packet.field61 = 7;
    packet.field62 = -1;
    scaleBase = D_800A0A1C;
    count += 10;
    packet.field22 = 1;
    packet.flags = 0x4C207;
    packet.field60 = 0;
    packet.field63 = -1;
    packet.field64 = -1;
    packet.field65 = 0;
    packet.field5C = 0;
    packet.field66 = 255;
    yawBase = ((s16)(s32)(arg2 * D_800A0A18) >> 8) + 0x40;
    scaleRange = D_800A0A20;
    packet.scale = 1.0f;
    do {
        arg2 = func_150ADA68() * scaleRange + scaleBase;
        packet.field1D = D_800A09C0[func_150ADA20() & 3];
        packet.field0A = (u32)func_150ADA20() % 18U + 27;
        packet.colors[7] = (u32)func_150ADA20() % 156U + 100;
        packet.size2 = packet.size1 = func_150ADA68() * 233.0f + 199.0f;
        first = func_150ADA20();
        second = func_150ADA20();
        func_15143794((s16)((u32)first % 130U + yawBase),
                      (s16)((u32)second % 81U - 64),
                      func_150ADA68() * 10.0f + 5.0f, &packet.velocity);
        packet.velocity.x -= arg1->x * arg2;
        packet.velocity.z -= arg1->z * arg2;
        packet.field54 = func_150ADA68() * D_800A0A24 + D_800A0A28;
        packet.flags &= ~0xC0;
        first = (func_150ADA20() & 1) ? 0x80 : 0;
        if (func_150ADA20() & 1) {
            second = 0x40;
        } else {
            second = 0;
        }
        second |= first;
        packet.flags |= second;
        func_15130280(&packet, 1, 0, 0, ((u8 *)&arg3)[3], arg4);
        count--;
    } while (count > 0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D4D58 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D4D58.s")

void func_100111C8(u16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150D5124 CURRENT (635) */
s32 func_150D5124(u8 *arg0, s32 arg1, u32 *arg2, s32 arg3, s32 *arg4, s32 arg5, u16 *arg6) {
    s32 kind;
    s32 target = 0;
    s32 pitch = 0;
    u8 *state;
    s32 level;
    s32 currentPitch;
    u8 *owner;
    f32 speed;

    kind = *(s32 *)(arg0 + 0x1C);
    state = *(u8 **)(arg0 + 0x18);
    level = *(s32 *)(arg0 + 0xC);
    currentPitch = *arg4;
    if (kind == 0x5B3) {
        owner = *(u8 **)state;
        if (owner != 0) {
            speed = *(f32 *)(owner + 0x28);
            target = speed * 25.0f;
            if (target > 5000) {
                target = 5000;
            } else if (target < 500) {
                target = 0;
            }
            pitch += speed * 5.0f;
            if (pitch > 1000) {
                pitch = 1000;
            }
        }
        if (state[5] == 2) {
            target += 7000;
        } else if (state[5] == 1) {
            target += 7000;
            pitch = 400;
        } else {
            pitch = 400;
            if (target != 0) {
                level = target;
            }
        }
    } else if (kind == 0x5BC) {
        target = 24000;
        if (state[5] == 0) {
            level = 24000;
        } else {
            target = 400;
        }
    } else if (kind == 0x5B4) {
        if (state[5] == 0) {
            target = 16000;
            pitch = 400;
            level = 16000;
        } else if (state[5] == 1 || D_8008FD8C >= 5) {
            target = 12000;
        } else {
            pitch = 400;
        }
    }
    if (level != target) {
        if (level < target) {
            level += D_800BE9E4 << 8;
            if (level > target) {
                level = target;
            }
        } else {
            level -= D_800BE9E4 << 8;
            if (level < target) {
                level = target;
            }
        }
    }
    if (currentPitch != pitch) {
        if (currentPitch < pitch) {
            currentPitch += D_800BE9E4 << 8;
            if (currentPitch > pitch) {
                currentPitch = pitch;
            }
        } else {
            currentPitch -= D_800BE9E4 * 8;
            if (currentPitch < pitch) {
                currentPitch = pitch;
            }
        }
    }
    if (level < 500) {
        level = 0;
    } else if (*arg6 == 0) {
        *(s16 *)arg0 = kind;
        *arg6 = kind;
    }
    *(s16 *)(arg0 + 2) = (s32)*(f32 *)(*(u8 **)state + 0x14);
    *(s16 *)(arg0 + 4) = (s32)*(f32 *)(*(u8 **)state + 0x18);
    *(s16 *)(arg0 + 6) = (s32)*(f32 *)(*(u8 **)state + 0x1C);
    if (D_800C35EA == 1) {
        *(s32 *)(arg0 + 0xC) = level >> 1;
        *arg2 >>= 1;
    } else {
        *(s32 *)(arg0 + 0xC) = level;
    }
    *(s16 *)(arg0 + 0x20) = currentPitch;
    *arg4 = (s16)currentPitch;
    if (*arg2 == 0) {
        if (*(u16 *)(arg0 + 0x24) != 0) {
            func_100111C8(*(u16 *)(arg0 + 0x24));
            *(u16 *)(arg0 + 0x24) = 0;
        }
        *arg6 = 0;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150D5124 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D5124.s")
