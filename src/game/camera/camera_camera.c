#include "types.h"

/*
 * Reviewed source unit: src/game/camera/camera_camera.c
 * Boundary evidence: docs/evidence/boundaries/game/mapping/game_beta_camera_rope_bee.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15122C5C
 * - func_1512317C
 * - func_15123568
 * - func_151236D0
 * - func_15123A54
 * - func_151247C0
 * - func_15124B18
 * - func_15124C38
 * - func_151254F4
 * - func_151256BC
 * - func_15125DB4
 * - func_15126378
 * - func_15127520
 * - func_151277B0
 * - func_151279A0
 * - func_15128030
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

s32 func_150859AC(s32, s32);
s32 func_15123934(void *, s32, s32, s32, s32);
s32 func_151239CC(void *, s32);
void func_15122C5C(void *);
void func_1512C490(void *);
extern s32 D_80082FA0;
extern s32 D_800894B0;
extern f32 D_800A34D0;
extern s32 D_800BEA08;
extern u8 D_800BEAC0;
extern u8 D_800C35EA;
extern s32 D_800D2DB4;
extern u8 *D_800DBFF0;

void func_15122AE0(void) {
    f32 scale = (f32)D_800BEA08 * D_800A34D0;
    s32 i;
    u8 *camera;

    for (i = 0; D_80082FA0 >= i; i = (s16)(i + 1)) {
        camera = D_800DBFF0 + i * 0x9A0;
        if (func_150859AC((s16)i, 0) != 0 || i == 0) {
            *(f32 *)(camera + 0x7B4) = scale;
            if (D_800BEAC0 == 0 || D_800C35EA != 0 || D_800D2DB4 != 0) {
                func_151239CC(camera, 5);
                func_15122C5C(camera);
            } else {
                func_15123934(camera, 0x2000, 0, *(s32 *)(camera + 0x134), 5);
                func_1512C490(camera);
            }
        }
    }
    D_800894B0++;
}
void func_15097798(s32);
void func_1510B128(s32, f32, f32, f32, f32);
void func_15123070(struct108 *);
void func_15123508(void *);
void func_15125394(void *);
void func_15125594(void *);
void func_151256BC(u8 *);
void func_15126138(u8 *);
void func_15127EB8(struct108 *);
void func_151283B8(void *);
s32 func_15128540(u8 *);
void func_15128680(s32);
void func_1512B100(void *);
void func_1512C150(void *);
void func_1512C200(s32);
void func_15130230(void *, void *);

void func_151287E0(void *, void *, void *);
void func_15128CB0(void *);
void func_1512BB10(void *);
void func_1512C068(void *);
void func_1512C20C(void *);
void func_1512D390(void *);
void func_1512D980(void *);
void func_1512E8E0(void *);
void func_15125A6C(struct108 *);
void func_15125DB4(void *);
void func_15125C40();
void func_151284C4();
void func_1512317C(u8 *);
void func_15123568(u8 *);
void func_15125924(u8 *);
extern f32 D_800A34D4;
extern s32 D_800BE728;
extern s32 D_800BE628;
extern s32 D_800BE9F0;
extern u8 D_800DBFF4[];
extern u16 D_800BE710[];
typedef struct Camera22CVector { f32 x, y, z; } Camera22CVector;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15122C5C CURRENT (795) */
void func_15122C5C(void *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fv0;
    f32 blend;
    s16 temp_v1;
    s32 temp_v0_5;
    s32 temp_v0_6;
    u8 temp_v0_2;
    u8 temp_v0_3;
    void *temp_a0;
    void *temp_a1;
    void *temp_v0;

    if ((*(u8 *)((u8 *)(arg0) + 0x23C)) != 0) {
        *(Camera22CVector *)((u8 *)arg0 + 0x2E0) = *(Camera22CVector *)((u8 *)(u8 *)arg0 + 0x2BC);
        *(Camera22CVector *)((u8 *)arg0 + 0x2EC) = *(Camera22CVector *)((u8 *)(u8 *)arg0 + 0x2F8);
    }
    temp_v0 = (*(void **)((u8 *)(arg0) + 0x3D4));
    temp_a0 = (u8 *)arg0 + 0x2BC;
    temp_a1 = (u8 *)arg0 + 0x2F8;
    if (temp_v0 != 0) {
        temp_v1 = (*(s16 *)((u8 *)(arg0) + 0x73C));
        if ((temp_v1 != 3) && (((*(s32 *)((u8 *)(arg0) + 0x2C)) != 0x100) || (temp_v1 != 0))) {
            (*(u8 *)((u8 *)(arg0) + 0x23E)) = (u8) (*(u8 *)((u8 *)(temp_v0) + 0x78));
        }
    }
    if (D_800DBFF4[(*(u8 *)((u8 *)(arg0) + 0x23D))] != 4) {
        (*(s32 *)((u8 *)(arg0) + 0x5F0)) = (s32) ((*(s32 *)((u8 *)(arg0) + 0x5F0)) & ~4);
    }
    if (!(*(s32 *)((u8 *)arg0 + 0x2C) & 0x400000)) {
        *(Camera22CVector *)temp_a0 = *(Camera22CVector *)((u8 *)arg0 + 0x2E0);
        *(Camera22CVector *)temp_a1 = *(Camera22CVector *)((u8 *)arg0 + 0x2EC);
    }
    temp_v0_2 = (*(u8 *)((u8 *)(arg0) + 0x23D));
    (*(s32 *)((u8 *)(arg0) + 0x36C)) = (s32) ((s32 *)D_800BE728)[temp_v0_2];
    (*(u16 *)((u8 *)(arg0) + 0x36A)) = (u16) D_800BE710[temp_v0_2];
    *(Camera22CVector *)((u8 *)arg0 + 0x304) = *(Camera22CVector *)temp_a1;
    *(f32 *)((u8 *)arg0 + 0x358) = *(f32 *)((u8 *)arg0 + 0x35C);
    *(Camera22CVector *)((u8 *)arg0 + 0x2C8) = *(Camera22CVector *)temp_a0;
    if ((*(u8 *)((u8 *)(arg0) + 0x23C)) != 0) {
        (*(f32 *)((u8 *)(arg0) + 0x19C)) = (f32) (*(f32 *)((u8 *)(arg0) + 0x1A4));
        (*(f32 *)((u8 *)(arg0) + 0x1A0)) = (f32) (*(f32 *)((u8 *)(arg0) + 0x1A8));
    } else {
        temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0x19C));
        temp_fv1 = (*(f32 *)((u8 *)(arg0) + 0x1A0));
        blend = D_800A34D4;
        (*(f32 *)((u8 *)(arg0) + 0x19C)) = (f32) ((((*(f32 *)((u8 *)(arg0) + 0x1A4)) - temp_fv0) * blend) + temp_fv0);
        (*(f32 *)((u8 *)(arg0) + 0x1A0)) = (f32) ((((*(f32 *)((u8 *)(arg0) + 0x1A8)) - temp_fv1) * blend) + temp_fv1);
    }
    if ((*(s32 *)((u8 *)(arg0) + 0x2C)) & 0x100) {
        var_fv0 = 16.0f;
    } else {
        var_fv0 = 0.0f;
    }
    temp_v0_3 = (*(u8 *)((u8 *)(arg0) + 0x23D));
    func_1510B128((s32) temp_v0_3, (*(f32 *)((u8 *)(arg0) + 0x19C)), (*(f32 *)((u8 *)(arg0) + 0x1A0)), (*(f32 *)((u8 *)(((u8 *)D_800BE628 + (temp_v0_3 * 0x180))) + 0x84)), var_fv0);
    func_15097798((s32) (*(u8 *)((u8 *)(arg0) + 0x23D)));
    func_15125A6C((u8 *) arg0);
    func_15128CB0(arg0);
    func_15125DB4(arg0);
    temp_v0 = (*(void **)((u8 *)(arg0) + 0x3D4));
    if (((*(u8 *)((u8 *)(temp_v0) + 0x120)) != 0) && ((*(u8 *)((u8 *)(temp_v0) + 0x197)) != 0)) {
        func_15127EB8(arg0);
    }
    if (func_15128540((u8 *) arg0) == 0) {
        temp_v0_5 = (*(s32 *)((u8 *)(arg0) + 0x84));
        if ((temp_v0_5 & 0x08000000) && !(temp_v0_5 & 0x400)) {
            func_1512E8E0(arg0);
        }
        func_15130230(arg0, (void *) D_800BE9F0);
        func_15126138((u8 *) arg0);
        func_15125C40((void *) arg0);
        func_15128680((s32) arg0);
        func_1512317C((u8 *) arg0);
        func_15125394(arg0);
        temp_v0_6 = (*(s32 *)((u8 *)(arg0) + 0x84));
        if (!(temp_v0_6 & 0x08000000) && !(temp_v0_6 & 0x400)) {
            func_1512E8E0(arg0);
        }
        func_15123568((u8 *) arg0);
        func_1512C200((s32) arg0);
        func_15125924((u8 *) arg0);
        func_151283B8(arg0);
        if ((*(u8 *)((u8 *)(arg0) + 0x23C)) != 0) {
            func_15125594(arg0);
            func_15123070(arg0);
            func_151283B8(arg0);
            func_151283B8(arg0);
        }
        func_15123508(arg0);
        if (((*(s32 *)((u8 *)(arg0) + 0x84)) & 2) && ((*(u8 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D4))) + 0x120)) == 0)) {
            func_1512D390(arg0);
        }
        func_15125594(arg0);
        func_151256BC((u8 *) arg0);
        func_1512D980(arg0);
        func_1512C068(arg0);
        func_1512B100(arg0);
        func_1512C20C(arg0);
        func_1512BB10(arg0);
        if ((*(u8 *)((u8 *)(arg0) + 0x23C)) != 0) {
            func_1512C068(arg0);
            func_1512B100(arg0);
            func_1512C20C(arg0);
            func_1512BB10(arg0);
        }
        func_15125594(arg0);
        func_15123070(arg0);
        if ((*(u16 *)((u8 *)(arg0) + 0x7F4)) == 0) {
            func_151287E0(arg0, 0, 0);
        }
        func_1512C150(arg0);
        func_151284C4((void *) arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15122C5C */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15122C5C.s")

void func_15048F90(void *, void *, void *);
f32 func_15048FC8();

void func_15123070(struct108 *arg0) {
    f32 temp_f0;
    struct17 tmp;

    if ((arg0->unk6C8 != 0) && ((arg0->unk6FC == 10) || (arg0->unk6FC == 14))) {
        f32 hi = 360.0f;
        func_15048F90(&arg0->unk618, &arg0->unk2A4, &tmp);
        arg0->unk390 = arg0->unk37C - func_15048FC8(&tmp);
    } else {
        temp_f0 = (arg0->unk3D0->unk40 - arg0->unk37C) - 180.0f;
        if (temp_f0 < 0.0f) {
            do {
                temp_f0 += 360.0f;
            } while (temp_f0 < 0.0f);
        }
        arg0->unk390 = temp_f0;
    }
    if (arg0->unk390 < -360.0f) {
        do {
            arg0->unk390 += 360.0f;
        } while (arg0->unk390 < -360.0f);
    }
}
void func_150495B0(f32 *, f32, f32 *, f32, f32, f32);
void func_1511FC60(void *);
s32 func_15125490(void *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512317C CURRENT (3910) */
void func_1512317C(u8 *arg0) {
    u8 *target;
    u8 *other;
    u16 *status;
    s32 flags;
    s32 first_flag;
    s32 second_flag;
    s32 special;
    s32 blocked;
    s16 state;

    target = *(u8 **)(arg0 + 0x3D0);
    flags = *(s32 *)(arg0 + 0x5F0);
    first_flag = flags & 0x100;
    second_flag = flags & 0x200;
    special = target[0x104] != 0 && (flags = arg0[0x23E], flags != 9) && flags != 0x38 && flags != 0x39 &&
        flags != 0x3B && flags != 0x37 && flags != 0x15 && flags != 0x26 && flags != 0x3A;
    blocked = (*(s32 *)(arg0 + 0x2C) & 0x80) != 0 ||
        (*(s32 *)(arg0 + 0x84) & 0x1000000) != 0 ||
        (*(f32 *)(target + 0x28) != 0.0f && target[0xAD] == 0 &&
         *(s32 *)(*(u8 **)(arg0 + 0x3D4) + 0x9C) == 0 &&
         first_flag == 0 && second_flag == 0 && arg0[0x23E] != 3) ||
        (target[0x65] != 0 && first_flag == 0 && second_flag == 0) ||
        special != 0 || func_15125490(arg0) != 0 ||
        (target = *(u8 **)(arg0 + 0x3D0), target[0x1CA] == 0) ||
        (other = *(u8 **)(arg0 + 0x3D4),
         ((other[0x4E] & 0xF) == 1 && *(f32 *)(target + 0x3C) > 15.0f) ||
         other[0x1AC] != 0);
    if ((**(u16 **)(arg0 + 0x36C) & 0x10) && blocked == 0) {
        if ((*(u16 *)(arg0 + 0x36A) & 0x10) &&
            func_15123934(arg0, 0x100, 4, *(s32 *)(arg0 + 0x134), 1) != 0) {
            func_1511FC60(arg0);
        }
    } else {
        if (*(s32 *)(arg0 + 0x2C) == 0x100 && *(s16 *)(arg0 + 0x73C) == 0) {
            func_151239CC(arg0, 1);
            (*(u8 **)(arg0 + 0x3D4))[0x198] = 0;
            (*(u8 **)(arg0 + 0x3D4))[0x197] = 0;
            status = *(u16 **)(arg0 + 0x36C);
            *(s16 *)(arg0 + 0x5F8) = 1;
            *(s16 *)(arg0 + 0x5FC) = 2;
            *(u16 *)(arg0 + 0x36A) &= 0xFFEF;
            *status &= 0xFFEF;
        }
        if (*(s32 *)(arg0 + 0x2C) == 0x100 || *(s16 *)(arg0 + 0x73C) != 0) {
            status = *(u16 **)(arg0 + 0x36C);
            *(u16 *)(arg0 + 0x36A) &= ~0x10;
            *status &= ~0x10;
        }
        (*(u8 **)(arg0 + 0x3D4))[0x198] = *(s16 *)(arg0 + 0x73C);
        state = *(s16 *)(arg0 + 0x73C);
        if (state != 0 || state == 3) {
            func_150495B0((f32 *)(arg0 + 0x74C), 0.0f, (f32 *)(arg0 + 0x79C),
                4.0f, 9.0f, *(f32 *)(arg0 + 0x7B4));
            func_150495B0((f32 *)(arg0 + 0x754), 0.0f, (f32 *)(arg0 + 0x7A0),
                4.0f, 9.0f, *(f32 *)(arg0 + 0x7B4));
        }
        if (*(s32 *)(arg0 + 0x2C) != 0x100 && *(s16 *)(arg0 + 0x73C) != 0) {
            *(s16 *)(arg0 + 0x73C) = 0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512317C */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_1512317C.s")
void func_15123508(void *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x84) & 2) {
        if ((*(u16 *)((u8 *)arg0 + 0x36A) & 2) && (*(s32 *)((u8 *)arg0 + 0x698) == 0)) {
            *(s32 *)((u8 *)arg0 + 0x6B0) = -1;
        }
        if ((*(u16 *)((u8 *)arg0 + 0x36A) & 1) && (*(s32 *)((u8 *)arg0 + 0x698) == 0)) {
            *(s32 *)((u8 *)arg0 + 0x6B0) = 1;
        }
    }
}
void func_15124B18(u8 *);
void func_15125608(f32 *);
extern f32 D_800A34D8;
extern s32 D_800BE9E4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15123568 CURRENT (230) */
void func_15123568(u8 *arg0) {
    if (*(u8 *)(*(u8 **)(arg0 + 0x3D4) + 0x120) == 4 &&
        *(s32 *)(arg0 + 0x2C) != 0x40 &&
        *(u8 *)(arg0 + 0x92C) == 0) {
        *(f32 *)(arg0 + 0x7C0) = D_800A34D8;
        *(s16 *)(arg0 + 0x1B4) = 1;
        func_15124B18(arg0);
        *(f32 *)(arg0 + 0x198) = 0.0f;
        *(f32 *)(arg0 + 0x190) = 0.0f;
        return;
    }
    if (*(s32 *)(arg0 + 0x7B8) > 0) {
        *(s32 *)(arg0 + 0x7B8) -= D_800BE9E4;
        if (*(s32 *)(arg0 + 0x7B8) < 0) {
            *(s32 *)(arg0 + 0x7B8) = 0;
        }
    } else if ((*(s32 *)(arg0 + 0x84) & 4) &&
               (*(u16 *)(arg0 + 0x36A) & 8) &&
               *(s32 *)(arg0 + 0xDC) != 4 &&
               (*(s32 *)(arg0 + 0x6C8) == 0 ||
                *(s32 *)(arg0 + 0x6FC) == 4U) &&
               (*(u8 *)(*(u8 **)(arg0 + 0x3D0) + 0xAD) != 1 ||
                *(s16 *)(arg0 + 0x1B4) != 1) &&
               *(s16 *)(arg0 + 0x1B4) != 1) {
        do {
            *(s16 *)(arg0 + 0x1B4) -= 1;
            if (*(s16 *)(arg0 + 0x1B4) <= 0) {
                *(s16 *)(arg0 + 0x1B4) = 3;
            }
        } while (!(*(s16 *)(arg0 + 0x1E0) &
                   (1 << *(s16 *)(arg0 + 0x1B4))));
        func_15124B18(arg0);
        func_15125608((f32 *)arg0);
        *(s32 *)(arg0 + 0x7B8) = 0x14;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15123568 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15123568.s")
void func_1515BA10(s32);
void func_1515BA1C(s16);
void func_1515BA48(s32);
void func_1515BA54(s16);
void func_1515BA80(s16);
void func_1515BAAC(s16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151236D0 CURRENT (1285) */
void func_151236D0(u8 *arg0) {
    s32 temp_a2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_v1;
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = (*(void **)((u8 *)(arg0) + 0x3D4));
    var_v1 = (*(s32 *)((u8 *)(arg0) + 0x5F0));
    temp_a2 = var_v1 & 1;
    if (temp_v0 != 0) {
        if (((*(s32 *)((u8 *)(temp_v0) + 0x9C)) != 0) || (((*(u8 *)((u8 *)(temp_v0) + 0x95)) != 0) && ((*(u8 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0x137)) == 0))) {
            (*(s32 *)((u8 *)(arg0) + 0x5F0)) = (s32) (var_v1 | 0x40);
        } else {
            (*(s32 *)((u8 *)(arg0) + 0x5F0)) = (s32) (var_v1 & ~0x40);
        }
        if ((*(f32 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0x28)) == 0.0f) {
            (*(s32 *)((u8 *)(arg0) + 0x5F0)) = (s32) ((*(s32 *)((u8 *)(arg0) + 0x5F0)) & ~0x400);
        }
        temp_v0_2 = (*(void **)((u8 *)(arg0) + 0x3D4));
        if (((*(s16 *)((u8 *)(temp_v0_2) + 8)) != 0) && ((*(u8 *)((u8 *)(temp_v0_2) + 0x16)) == 0)) {
            (*(s32 *)((u8 *)(arg0) + 0x5F0)) = (s32) ((*(s32 *)((u8 *)(arg0) + 0x5F0)) | 8);
        } else {
            (*(s32 *)((u8 *)(arg0) + 0x5F0)) = (s32) ((*(s32 *)((u8 *)(arg0) + 0x5F0)) & ~8);
        }
        if ((*(u8 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D4))) + 0x4E)) == 2) {
            var_v1 = (*(s32 *)((u8 *)(arg0) + 0x5F0)) | 0x80;
        } else {
            var_v1 = (*(s32 *)((u8 *)(arg0) + 0x5F0)) & ~0x80;
        }
        (*(s32 *)((u8 *)(arg0) + 0x5F0)) = var_v1;
    }
    if (((*(f32 *)((u8 *)(arg0) + 0x2FC)) <= (*(f32 *)((u8 *)(arg0) + 0x360))) && ((*(s32 *)((u8 *)(arg0) + 0x2C)) != 0x100)) {
        (*(s32 *)((u8 *)(arg0) + 0x5F0)) = (s32) (var_v1 | 1);
    } else {
        (*(s32 *)((u8 *)(arg0) + 0x5F0)) = (s32) (var_v1 & ~1);
    }
    if ((*(u8 *)((u8 *)(arg0) + 0x23C)) != 0) {
        if ((*(s32 *)((u8 *)(arg0) + 0x5F0)) & 1) {
            func_1515BA80((s16) (*(u8 *)((u8 *)(arg0) + 0x23D)));
            return;
        }
        func_1515BA48((s32) (*(u8 *)((u8 *)(arg0) + 0x23D)));
        (*(f32 *)((u8 *)(arg0) + 0x7B0)) = 0.0f;
        return;
    }
    if (temp_a2 == 0) {
        temp_v1 = (*(s32 *)((u8 *)(arg0) + 0x5F0));
        if (temp_v1 & 1) {
            if ((temp_v1 & 4) || ((*(s32 *)((u8 *)(arg0) + 0x2C)) & 0x40000)) {
                func_1515BA80((s16) (*(u8 *)((u8 *)(arg0) + 0x23D)));
                return;
            }
            func_1515BAAC((s16) (*(u8 *)((u8 *)(arg0) + 0x23D)));
            return;
        }
    }
    temp_v1_2 = (*(s32 *)((u8 *)(arg0) + 0x5F0));
    temp_v0_3 = temp_v1_2 & 1;
    if ((temp_a2 != 0) && (temp_v0_3 == 0)) {
        if ((temp_v1_2 & 4) || ((*(s32 *)((u8 *)(arg0) + 0x2C)) & 0x40000)) {
            func_1515BA48((s32) (*(u8 *)((u8 *)(arg0) + 0x23D)));
            (*(f32 *)((u8 *)(arg0) + 0x7B0)) = 0.0f;
            return;
        }
        func_1515BA54((s16) (*(u8 *)((u8 *)(arg0) + 0x23D)));
        func_15124B18(arg0);
        return;
    }
    if (temp_v0_3 != 0) {
        func_1515BA1C((s16) (*(u8 *)((u8 *)(arg0) + 0x23D)));
        return;
    }
    func_1515BA10((s32) (*(u8 *)((u8 *)(arg0) + 0x23D)));
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151236D0 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151236D0.s")
void func_15125394(void *);

s32 func_15123934(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v1 = (u8 *)arg0 + (arg4 * 2);
    if (*(s16 *)(temp_v1 + 0x20C) == 0) {
        *(u16 *)(temp_v1 + 2) = *(u16 *)arg0;
        temp_v0 = (u8 *)arg0 + (arg4 * 4);
        *(s32 *)(temp_v0 + 0x30) = *(s32 *)((u8 *)arg0 + 0x2C);
        *(s32 *)(temp_v0 + 0x88) = *(s32 *)((u8 *)arg0 + 0x84);
        *(s32 *)(temp_v0 + 0xE0) = *(s32 *)((u8 *)arg0 + 0xDC);
        *(s32 *)(temp_v0 + 0x138) = *(s32 *)((u8 *)arg0 + 0x134);
        *(s16 *)(temp_v1 + 0x1B6) = *(s16 *)((u8 *)arg0 + 0x1B4);
        *(s16 *)(temp_v1 + 0x1E2) = *(s16 *)((u8 *)arg0 + 0x1E0);
        *(s32 *)((u8 *)arg0 + 0x2C) = arg1;
        *(s32 *)((u8 *)arg0 + 0xDC) = arg2;
        *(s32 *)((u8 *)arg0 + 0x134) = arg3;
        *(s16 *)(temp_v1 + 0x20C) = 1;
        func_15125394(arg0);
        return 1;
    }
    return 0;
}
s32 func_151239CC(void *arg0, s32 arg1) {
    if (*(s16 *)((u8 *)arg0 + (arg1 * 2) + 0x20C) != 0) {
        *(u16 *)arg0 = *(u16 *)((u8 *)arg0 + (arg1 * 2) + 2);
        *(s32 *)((u8 *)arg0 + 0x2C) = *(s32 *)((u8 *)arg0 + (arg1 * 4) + 0x30);
        *(s32 *)((u8 *)arg0 + 0xDC) = *(s32 *)((u8 *)arg0 + (arg1 * 4) + 0xE0);
        *(s32 *)((u8 *)arg0 + 0x84) = *(s32 *)((u8 *)arg0 + (arg1 * 4) + 0x88);
        *(s32 *)((u8 *)arg0 + 0x134) = *(s32 *)((u8 *)arg0 + (arg1 * 4) + 0x138);
        *(s16 *)((u8 *)arg0 + 0x1B4) = *(s16 *)((u8 *)arg0 + (arg1 * 2) + 0x1B6);
        *(s16 *)((u8 *)arg0 + 0x1E0) = *(s16 *)((u8 *)arg0 + (arg1 * 2) + 0x1E2);
        func_15124B18(arg0);
        *(s16 *)((u8 *)arg0 + (arg1 * 2) + 0x20C) = 0;
        return 1;
    }
    return 0;
}
f32 func_15047C00(f32);
f32 func_15047D60(f32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
f32 fabsf(f32);
#pragma intrinsic(fabsf)
u32 func_150ADA20(void);
void func_1504917C(void *, void *);
void func_15049688(void *, f32, void *, f32, f32, f32);
void func_150AD8B0(f32 *, f32 *, f32 *);
f32 func_150AD900(f32 *, f32 *);
s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, s16 *, f32 *, f32 *, f32 *, f32 *, s32 *, void *, f32);
extern u8 D_800C3671;
extern f32 D_800895B0;
extern f32 D_800A34DC;
extern f32 D_800A34E0;
extern f32 D_800A34E4;
extern f32 D_800A34E8;
extern f32 D_800A34EC;
extern f32 D_800A34F0;
extern f32 D_800A34F4;
extern f32 D_800A34F8;
extern u8 D_800BE616;
extern u8 D_800BEA0C;
extern f32 D_800DC000;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15123A54 CURRENT (5742) */
void func_15123A54(u8 *arg0) {
    f32 sp114;
    f32 sp110;
    f32 direction[3];
    s16 triangle[9];
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    s16 other_triangle[9];
    f32 spC4;
    f32 spBC;
    f32 edge_a[3];
    f32 edge_b[3];
    f32 normal[3];
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 vertex_a[3];
    f32 vertex_b[3];
    f32 vertex_c[3];
    f32 old_distance;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_v0;
    s32 temp_v1;
    u16 *temp_v0_4;
    u8 temp_t6;

    temp_fv1 = (*(f32 *)((u8 *)(arg0) + 0x374));
    sp110 = temp_fv1;
    (*(u8 *)((u8 *)(arg0) + 0x600)) = 0U;
    (*(f32 *)((u8 *)(arg0) + 0x604)) = temp_fv1;
    if (D_800C3671 == 0) {
        temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0x6F8));
        if (temp_fv0 != 0.0f) {
            if (temp_fv0 < temp_fv1) {
                (*(f32 *)((u8 *)(arg0) + 0x374)) = temp_fv0;
            } else {
                (*(f32 *)((u8 *)(arg0) + 0x374)) = temp_fv1;
            }
        }
        if ((*(u8 *)((u8 *)(arg0) + 0x23C)) == 0) {
            if (((*(s32 *)((u8 *)(arg0) + 0x5F0)) & 0x10) && (*(*(u16 **)((u8 *)(arg0) + 0x36C)) & 0x10)) {
                (*(f32 *)((u8 *)(arg0) + 0x374)) = 130.0f;
            }
            if (((*(s16 *)((u8 *)(arg0) + 0x73C)) == 0) && ((*(s32 *)((u8 *)(arg0) + 0x5F0)) & 0x40)) {
                (*(f32 *)((u8 *)(arg0) + 0x374)) = 420.0f;
            }
            if ((*(s32 *)((u8 *)(arg0) + 0x2C)) & 0x403) {
                if ((*(u16 *)((u8 *)(arg0) + 0x36A)) & 4) {
                    (*(u8 *)((u8 *)(arg0) + 0x8E4)) = 1U;
                    (*(s32 *)((u8 *)(arg0) + 0x8E8)) = 0xB4;
                    (*(f32 *)((u8 *)(arg0) + 0x8E0)) = 0.0f;
                } else {
                    temp_v1 = *(*(u16 **)((u8 *)(arg0) + 0x36C)) & 4;
                    if ((temp_v1 != 0) || ((*(u8 *)((u8 *)(arg0) + 0x8E4)) != 0)) {
                        temp_v0 = (*(u8 *)((u8 *)(arg0) + 0x8E4));
                        if ((temp_v0 != 0) && (temp_v1 != 0)) {
                            temp_t6 = temp_v0 + D_800BEA08;
                            temp_v1 = temp_t6 & 0xFF;
                            (*(u8 *)((u8 *)(arg0) + 0x8E4)) = temp_t6;
                            if (temp_v1 >= 0x10) {
                                (*(u8 *)((u8 *)(arg0) + 0x8E4)) = 0xFU;
                                temp_v0 = (*(u8 *)((u8 *)(arg0) + 0x8E4));
                            } else {
                                (*(u8 *)((u8 *)(arg0) + 0x8E4)) = (u8) temp_v1;
                                temp_v0 = (*(u8 *)((u8 *)(arg0) + 0x8E4));
                            }
                        }
                        if (temp_v0 == 0xF) {
                            (*(u8 *)((u8 *)(arg0) + 0x8EC)) = 1U;
                            (*(s32 *)((u8 *)(arg0) + 0x7B8)) = 0x14;
                            (*(f32 *)((u8 *)(arg0) + 0x374)) = 300.0f;
                            (*(f32 *)((u8 *)(arg0) + 0x348)) = 150.0f;
                            func_15049688(arg0 + 0x37C, (*(f32 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0x40)) - 180.0f, arg0 + 0x8E0, 1.5f, 2.0f, (*(f32 *)((u8 *)(arg0) + 0x7B4)));
                            if (!(*(*(u16 **)((u8 *)(arg0) + 0x36C)) & 4)) {
                                (*(u8 *)((u8 *)(arg0) + 0x8E4)) = 0U;
                            }
                        } else {
                            func_15049688(arg0 + 0x37C, (*(f32 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0x40)) - 180.0f, arg0 + 0x8E0, 2.0f, 4.0f, (*(f32 *)((u8 *)(arg0) + 0x7B4)));
                        }
                        (*(f32 *)((u8 *)(arg0) + 0x39C)) = (f32) ((*(f32 *)((u8 *)(arg0) + 0x37C)) * D_800A34DC);
                        if (((s32) (*(u8 *)((u8 *)(arg0) + 0x8E4)) < 0xF) && !(*(*(u16 **)((u8 *)(arg0) + 0x36C)) & 4)) {
                            if ((*(s16 *)((u8 *)(arg0) + 0x298)) == 0) {
                                (*(s32 *)((u8 *)(arg0) + 0x8E8)) -= D_800BEA08;
                                if ((*(s32 *)((u8 *)(arg0) + 0x8E8)) <= 0) {
                                    (*(u8 *)((u8 *)(arg0) + 0x8E4)) = 0U;
                                } else if (fabsf((*(f32 *)((u8 *)(arg0) + 0x37C)) - ((*(f32 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0x40)) - 180.0f)) <= 2.0f) {
                                    (*(u8 *)((u8 *)(arg0) + 0x8E4)) = 0U;
                                }
                            } else {
                                (*(u8 *)((u8 *)(arg0) + 0x8E4)) = 0U;
                            }
                        }
                    } else if ((*(u8 *)((u8 *)(arg0) + 0x8EC)) != 0) {
                        func_15124B18(arg0);
                        (*(u8 *)((u8 *)(arg0) + 0x8EC)) = 0U;
                        (*(u8 *)((u8 *)(arg0) + 0x8E4)) = 0U;
                    }
                }
            }
        } else {
            (*(f32 *)((u8 *)(arg0) + 0x39C)) = (f32) ((*(f32 *)((u8 *)(arg0) + 0x37C)) * D_800A34E0);
        }
        sp114 = (*(f32 *)((u8 *)(arg0) + 0x39C));
        if (D_800BEA0C != 0) {
            (*(f32 *)((u8 *)(arg0) + 0x37C)) = (f32) ((*(f32 *)((u8 *)(arg0) + 0x37C)) + (1.0f * (*(f32 *)((u8 *)(arg0) + 0x7E0)) * (f32) D_800BEA08));
            temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0x37C)) * D_800A34E4;
            (*(f32 *)((u8 *)(arg0) + 0x39C)) = temp_fv0;
            sp114 = temp_fv0;
        } else if (func_150ADA20() & 1) {
            (*(f32 *)((u8 *)(arg0) + 0x7E0)) = -1.0f;
        } else {
            (*(f32 *)((u8 *)(arg0) + 0x7E0)) = 1.0f;
        }
        if (((*(u8 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D4))) + 0x95)) != 0) && ((*(s32 *)((u8 *)(arg0) + 0x5F0)) & 0x40)) {
            sp114 = (*(f32 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0x40)) + 180.0f;
            func_15049688(arg0 + 0x37C, sp114, arg0 + 0x844, 2.0f, 4.0f, (*(f32 *)((u8 *)(arg0) + 0x7B4)));
            temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0x37C)) * D_800A34E8;
            (*(f32 *)((u8 *)(arg0) + 0x39C)) = temp_fv0;
            sp114 = temp_fv0;
            (*(f32 *)((u8 *)(arg0) + 0x374)) = (f32) D_800A34EC;
        }
        if ((*(s32 *)((u8 *)(arg0) + 0x2C)) != 0x2000) {
            temp_fa0 = (*(f32 *)((u8 *)(arg0) + 0x2F8)) - (*(f32 *)((u8 *)(arg0) + 0x2BC));
            temp_fv1 = (*(f32 *)((u8 *)(arg0) + 0x300)) - (*(f32 *)((u8 *)(arg0) + 0x2C4));
            (*(f32 *)((u8 *)(arg0) + 0x370)) = sqrtf((temp_fa0 * temp_fa0) + (temp_fv1 * temp_fv1));
            if (((*(s16 *)((u8 *)(arg0) + 0x73C)) != 0) || ((*(u8 *)((u8 *)(arg0) + 0x23C)) != 0) || ((*(u8 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0x102)) != 0) || ((temp_v0 = (*(s32 *)((u8 *)(arg0) + 0x84)), ((temp_v0 & 0x1000) == 0)) && ((*(u8 *)((u8 *)(arg0) + 0x92C)) == 0) && !(temp_v0 & 0x40000) && !((*(s32 *)((u8 *)(arg0) + 0x5F0)) & 0x80))) {
                direction[0] = func_15047D60((*(f32 *)((u8 *)(arg0) + 0x39C)));
                direction[1] = 0.0f;
                temp_fv0 = func_15047C00((*(f32 *)((u8 *)(arg0) + 0x39C)));
                direction[2] = temp_fv0;
                if ((func_150AC9C0((*(f32 *)((u8 *)(arg0) + 0x2A4)), (*(f32 *)((u8 *)(arg0) + 0x2A8)) + 140.0f, (*(f32 *)((u8 *)(arg0) + 0x2AC)), direction[0], direction[1], temp_fv0, 0, triangle, &spE4, &spE8, &spEC, &spE0, 0, 0, (*(f32 *)((u8 *)(arg0) + 0x374)) + 30.0f) != 0) && (spE0 < (*(f32 *)((u8 *)(arg0) + 0x374)))) {
                    spBC = func_15047D60((*(f32 *)((u8 *)(arg0) + 0x39C)) + D_800A34F0) * (*(f32 *)((u8 *)(arg0) + 0x374));
                    spC4 = func_15047C00((*(f32 *)((u8 *)(arg0) + 0x39C)) + D_800A34F4) * (*(f32 *)((u8 *)(arg0) + 0x374));
                    vertex_a[0] = (f32) triangle[0];
                    vertex_a[1] = (f32) triangle[1];
                    vertex_a[2] = (f32) triangle[2];
                    vertex_b[0] = (f32) triangle[3];
                    vertex_b[1] = (f32) triangle[4];
                    vertex_b[2] = (f32) triangle[5];
                    vertex_c[0] = (f32) triangle[6];
                    vertex_c[1] = (f32) triangle[7];
                    vertex_c[2] = (f32) triangle[8];
                    func_15048F90(vertex_a, vertex_b, edge_a);
                    func_15048F90(vertex_a, vertex_c, edge_b);
                    func_150AD8B0(edge_b, edge_a, normal);
                    func_1504917C(normal, normal);
                    if ((D_800A34F8 < func_150AD900(direction, normal)) && (func_150AC9C0((*(f32 *)((u8 *)(arg0) + 0x2A4)) - spBC, (*(f32 *)((u8 *)(arg0) + 0x2A8)) + 140.0f, (*(f32 *)((u8 *)(arg0) + 0x2AC)) - spC4, spBC, 0.0f, spC4, 0, other_triangle, &sp8C, &sp90, &sp94, &sp88, 0, 0, (*(f32 *)((u8 *)(arg0) + 0x374)) + 30.0f) != 0) && ((temp_fv1 = sp8C - spE4, temp_fa0 = sp94 - spEC, (sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0)) < 1.0f)) || ((*(s32 *)((u8 *)(arg0) + 0x5F0)) & 0x10) || (temp_v0 = (*(u8 *)((u8 *)(arg0) + 0x23E)), (temp_v0 == 0xC)) || (temp_v0 == 9) || (temp_v0 == 0x38) || (temp_v0 == 0x39) || (temp_v0 == 0x37) || (temp_v0 == 0x3B) || (temp_v0 == 0x12) || (temp_v0 == 0x15) || (temp_v0 == 0x26) || (temp_v0 == 0x3A) || ((*(u8 *)((u8 *)(arg0) + 0x23C)) != 0))) {
                        old_distance = (*(f32 *)((u8 *)(arg0) + 0x374));
                        if ((*(s16 *)((u8 *)(arg0) + 0x73C)) != 0) {
                            temp_fv0 = spE0 - 16.0f;
                        } else {
                            temp_fv0 = spE0 - 12.0f;
                        }
                        if (temp_fv0 < 50.0f) {
                            spE0 = 50.0f;
                        } else {
                            spE0 = temp_fv0;
                        }
                        temp_fv1 = (*(f32 *)((u8 *)(arg0) + 0x374));
                        if (spE0 < temp_fv1) {
                            (*(f32 *)((u8 *)(arg0) + 0x374)) = spE0;
                        } else {
                            (*(f32 *)((u8 *)(arg0) + 0x374)) = temp_fv1;
                        }
                        if ((*(u8 *)((u8 *)(arg0) + 0x23E)) == 3) {
                            (*(f32 *)((u8 *)(arg0) + 0x348)) = (f32) ((*(f32 *)((u8 *)(arg0) + 0x348)) * ((*(f32 *)((u8 *)(arg0) + 0x374)) / old_distance));
                            if ((*(s32 *)((u8 *)(arg0) + 0x5F0)) & 0x10) {
                                temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0x348));
                                temp_fv1 = (*(f32 *)((u8 *)(arg0) + 0x2C0)) - (*(f32 *)((u8 *)(arg0) + 0x354));
                                if (temp_fv0 < temp_fv1) {
                                    (*(f32 *)((u8 *)(arg0) + 0x348)) = temp_fv1;
                                } else {
                                    (*(f32 *)((u8 *)(arg0) + 0x348)) = temp_fv0;
                                }
                            }
                        }
                        (*(u8 *)((u8 *)(arg0) + 0x600)) = 1U;
                        (*(f32 *)((u8 *)(arg0) + 0x604)) = spE0;
                    }
                }
            }
            if ((*(u16 *)((u8 *)(arg0) + 0x7F4)) != 0) {
                (*(f32 *)((u8 *)(arg0) + 0x374)) = (f32) D_800DC000;
            }
            if ((*(u8 *)((u8 *)(arg0) + 0x23C)) != 0) {
                (*(f32 *)((u8 *)(arg0) + 0x370)) = (f32) (*(f32 *)((u8 *)(arg0) + 0x374));
                (*(f32 *)((u8 *)(arg0) + 0x258)) = 0.0f;
                if ((*(s32 *)((u8 *)(arg0) + 0x84)) & 0x200000) {
                    if ((*(s32 *)((u8 *)(arg0) + 0x2C)) & 0x40) {
                        (*(f32 *)((u8 *)(arg0) + 0x974)) = 1.0f;
                        (*(f32 *)((u8 *)(arg0) + 0x964)) = 1.0f;
                        (*(f32 *)((u8 *)(arg0) + 0x978)) = 2.0f;
                        (*(f32 *)((u8 *)(arg0) + 0x968)) = 2.0f;
                    } else {
                        (*(f32 *)((u8 *)(arg0) + 0x978)) = 8.0f;
                        (*(f32 *)((u8 *)(arg0) + 0x968)) = 8.0f;
                        (*(f32 *)((u8 *)(arg0) + 0x974)) = 6.0f;
                        (*(f32 *)((u8 *)(arg0) + 0x964)) = 6.0f;
                    }
                    (*(f32 *)((u8 *)(arg0) + 0x984)) = 0.0f;
                    (*(f32 *)((u8 *)(arg0) + 0x988)) = 0.0f;
                }
            } else {
                if (((*(s32 *)((u8 *)(arg0) + 0x7B8)) != 0) || (temp_v0 = (*(s32 *)((u8 *)(arg0) + 0x2C)), ((temp_v0 & 0x100) != 0)) || ((temp_v0 & 0x80) && (*(*(u16 **)((u8 *)(arg0) + 0x36C)) & 0x10))) {
                    (*(f32 *)((u8 *)(arg0) + 0x3B4)) = 6.0f;
                    (*(f32 *)((u8 *)(arg0) + 0x3B8)) = 10.0f;
                } else if ((D_800BE616 != 0) || ((*(s32 *)((u8 *)(arg0) + 0x84)) & 0x200000)) {
                    if (temp_v0 & 0x40) {
                        (*(f32 *)((u8 *)(arg0) + 0x974)) = 1.0f;
                        (*(f32 *)((u8 *)(arg0) + 0x978)) = 2.0f;
                    } else {
                        (*(f32 *)((u8 *)(arg0) + 0x974)) = 6.0f;
                        (*(f32 *)((u8 *)(arg0) + 0x978)) = 8.0f;
                    }
                    func_150495B0((f32 *) (arg0 + 0x964), (*(f32 *)((u8 *)(arg0) + 0x974)), (f32 *) (arg0 + 0x984), 1.0f, 2.0f, (*(f32 *)((u8 *)(arg0) + 0x7B4)));
                    func_150495B0((f32 *) (arg0 + 0x968), (*(f32 *)((u8 *)(arg0) + 0x978)), (f32 *) (arg0 + 0x988), 1.0f, 2.0f, (*(f32 *)((u8 *)(arg0) + 0x7B4)));
                    (*(f32 *)((u8 *)(arg0) + 0x3B4)) = (f32) (*(f32 *)((u8 *)(arg0) + 0x964));
                    (*(f32 *)((u8 *)(arg0) + 0x3B8)) = (f32) (*(f32 *)((u8 *)(arg0) + 0x968));
                } else if (((*(u8 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0x102)) != 0) || ((*(u8 *)((u8 *)(arg0) + 0x8EC)) != 0) || (((*(u8 *)((u8 *)(arg0) + 0x92C)) != 0) && ((*(u16 *)((u8 *)(arg0) + 0x920)) & 0x40))) {
                    (*(f32 *)((u8 *)(arg0) + 0x3B4)) = 6.0f;
                    (*(f32 *)((u8 *)(arg0) + 0x3B8)) = 8.0f;
                } else if (((*(u16 *)((u8 *)(arg0) + 0x36A)) & 3) || (temp_v0 & 0x40)) {
                    (*(f32 *)((u8 *)(arg0) + 0x3B4)) = 1.0f;
                    (*(f32 *)((u8 *)(arg0) + 0x3B8)) = 2.0f;
                } else {
                    (*(f32 *)((u8 *)(arg0) + 0x3B4)) = 2.0f;
                    (*(f32 *)((u8 *)(arg0) + 0x3B8)) = 3.0f;
                }
                if (D_800BEA0C == 0) {
                    if ((*(u8 *)((u8 *)(arg0) + 0x600)) != 0) {
                        if (((*(s16 *)((u8 *)(arg0) + 0x73C)) != 0) || (D_800BE616 != 0)) {
                            func_150495B0((f32 *) (arg0 + 0x370), (*(f32 *)((u8 *)(arg0) + 0x374)), (f32 *) (arg0 + 0x258), 8.0f, 10.0f, (*(f32 *)((u8 *)(arg0) + 0x7B4)));
                        } else {
                            func_150495B0((f32 *) (arg0 + 0x370), (*(f32 *)((u8 *)(arg0) + 0x374)), (f32 *) (arg0 + 0x258), 6.0f, 8.0f, (*(f32 *)((u8 *)(arg0) + 0x7B4)));
                        }
                    } else {
                        func_150495B0((f32 *) (arg0 + 0x370), (*(f32 *)((u8 *)(arg0) + 0x374)), (f32 *) (arg0 + 0x258), (*(f32 *)((u8 *)(arg0) + 0x3B4)), (*(f32 *)((u8 *)(arg0) + 0x3B8)), (*(f32 *)((u8 *)(arg0) + 0x7B4)));
                    }
                } else if ((D_800895B0 == 0.0f) && (((*(u8 *)((u8 *)(arg0) + 0x3E8)) != 0) || ((*(u8 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0x102)) != 0))) {
                    func_150495B0((f32 *) (arg0 + 0x370), 200.0f, (f32 *) (arg0 + 0x258), 4.0f, 8.0f, (*(f32 *)((u8 *)(arg0) + 0x7B4)));
                } else {
                    func_150495B0((f32 *) (arg0 + 0x370), 200.0f, (f32 *) (arg0 + 0x258), 0.5f, 1.0f, (*(f32 *)((u8 *)(arg0) + 0x7B4)));
                }
            }
            (*(f32 *)((u8 *)(arg0) + 0x2F8)) = (f32) ((func_15047D60(sp114) * (*(f32 *)((u8 *)(arg0) + 0x370))) + (*(f32 *)((u8 *)(arg0) + 0x2BC)));
            temp_fv0 = func_15047C00(sp114);
            temp_fa1 = (*(f32 *)((u8 *)(arg0) + 0x2C4));
            temp_fa0 = (*(f32 *)((u8 *)(arg0) + 0x2F8)) - (*(f32 *)((u8 *)(arg0) + 0x2BC));
            temp_ft4 = (temp_fv0 * (*(f32 *)((u8 *)(arg0) + 0x370))) + temp_fa1;
            (*(f32 *)((u8 *)(arg0) + 0x300)) = temp_ft4;
            temp_ft5 = temp_ft4 - temp_fa1;
            temp_fv0 = sqrtf((temp_fa0 * temp_fa0) + (temp_ft5 * temp_ft5));
            (*(f32 *)((u8 *)(arg0) + 0x370)) = temp_fv0;
            if ((2.0f * (*(f32 *)((u8 *)(arg0) + 0x374))) < temp_fv0) {
                temp_v0_4 = (*(u16 **)((u8 *)(arg0) + 0x36C));
                temp_v1 = *temp_v0_4;
                if ((temp_v1 & 3) && (D_800BE616 == 0)) {
                    *temp_v0_4 = temp_v1 & 0xFFFC;
                    (*(u16 *)((u8 *)(arg0) + 0x36A)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x36A)) & 0xFFFC);
                }
            }
            (*(f32 *)((u8 *)(arg0) + 0x374)) = sp110;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15123A54 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15123A54.s")
typedef struct {
    u8 pad_0[0x244];
    s16 field_244;
    u8 pad_246[2];
    void *field_248;
} CameraCameraState;

extern u8 D_800CC2D0[];

void func_15124770(CameraCameraState *arg0, s32 arg1) {
    if (arg1 != 0) {
        arg0->field_244 = arg1;
        arg0->field_248 = D_800CC2D0 + (arg1 * 0x32C);
    } else {
        arg0->field_244 = 0;
        arg0->field_248 = 0;
    }
}
f32 func_15047C00(f32);
f32 func_15047D60(f32);
void func_150495B0(f32 *, f32, f32 *, f32, f32, f32);
void func_15125594(void *);
extern f32 D_800A34FC;
extern f32 D_800A3500;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151247C0 CURRENT (1280) */
void func_151247C0(void *arg0) {
    u8 *camera = arg0;
    u8 *target;
    u8 *other;
    s32 state;
    f32 x;
    f32 z;
    f32 smoothing;
    f32 offset_x;
    f32 offset_z;

    if (*(u16 *)(camera + 0x7F4) == 0) {
        target = *(u8 **)(camera + 0x3D4);
        if (target != 0) {
            state = (target[0x95] | *(s32 *)(target + 0x9C)) & 0xFF;
        } else {
            state = 0;
        }
        if (state != 0) {
            *(f32 *)(camera + 0x674) = 0.25f;
        } else {
            *(f32 *)(camera + 0x674) = 1.0f;
        }
        if (camera[0x23C] != 0) {
            *(f32 *)(camera + 0x670) = *(f32 *)(camera + 0x674);
            *(f32 *)(camera + 0x678) = 0.0f;
        } else {
            func_150495B0((f32 *)(camera + 0x670), *(f32 *)(camera + 0x674),
                (f32 *)(camera + 0x678), *(f32 *)(camera + 0x3B4) * 0.25f,
                *(f32 *)(camera + 0x3B8) * 0.25f, *(f32 *)(camera + 0x7B4));
        }
        if (*(s16 *)(camera + 0x244) != 0) {
            if (camera[0x23C] != 0) {
                target = *(u8 **)(camera + 0x3D0);
                other = *(u8 **)(camera + 0x248);
                *(f32 *)(camera + 0x2A4) = (*(f32 *)(target + 0x14) + *(f32 *)(other + 0x14)) * 0.5f;
                *(f32 *)(camera + 0x2A8) = (*(f32 *)(target + 0x18) + *(f32 *)(other + 0x18)) * 0.5f;
                *(f32 *)(camera + 0x2AC) = (*(f32 *)(target + 0x1C) + *(f32 *)(other + 0x1C)) * 0.5f;
            } else {
                target = *(u8 **)(camera + 0x3D0);
                other = *(u8 **)(camera + 0x248);
                x = *(f32 *)(camera + 0x2A4);
                smoothing = *(f32 *)(camera + 0x670);
                z = *(f32 *)(camera + 0x2AC);
                *(f32 *)(camera + 0x2A4) = x + (((*(f32 *)(target + 0x14) + *(f32 *)(other + 0x14)) * 0.5f - x) * smoothing);
                *(f32 *)(camera + 0x2A8) = (*(f32 *)(target + 0x18) + *(f32 *)(other + 0x18)) * 0.5f;
                *(f32 *)(camera + 0x2AC) = z + (((*(f32 *)(target + 0x1C) + *(f32 *)(other + 0x1C)) * 0.5f - z) * smoothing);
            }
        } else {
            if (camera[0x23C] != 0) {
                target = *(u8 **)(camera + 0x3D0);
                *(f32 *)(camera + 0x2A4) = *(f32 *)(target + 0x14);
                *(f32 *)(camera + 0x2AC) = *(f32 *)(target + 0x1C);
            } else {
                target = *(u8 **)(camera + 0x3D0);
                x = *(f32 *)(camera + 0x2A4);
                smoothing = *(f32 *)(camera + 0x670);
                z = *(f32 *)(camera + 0x2AC);
                *(f32 *)(camera + 0x2A4) = x + ((*(f32 *)(target + 0x14) - x) * smoothing);
                *(f32 *)(camera + 0x2AC) = z + ((*(f32 *)(target + 0x1C) - z) * smoothing);
            }
            *(f32 *)(camera + 0x2A8) = *(f32 *)(*(u8 **)(camera + 0x3D0) + 0x18);
        }
        x = 0.0f;
        if (*(f32 *)(camera + 0x994) != x || *(f32 *)(camera + 0x99C) != x) {
            x = *(f32 *)(camera + 0x99C);
            if (camera[0x23C] != 0) {
                *(f32 *)(camera + 0x994) = x;
                *(f32 *)(camera + 0x998) = 0.0f;
            } else {
                func_150495B0((f32 *)(camera + 0x994), x, (f32 *)(camera + 0x998),
                    4.0f, 6.0f, *(f32 *)(camera + 0x7B4));
            }
            offset_x = func_15047D60(*(f32 *)(camera + 0x39C) - D_800A34FC) * *(f32 *)(camera + 0x994);
            offset_z = func_15047C00(*(f32 *)(camera + 0x39C) - D_800A3500) * *(f32 *)(camera + 0x994);
            *(f32 *)(camera + 0x2A4) += offset_x;
            *(f32 *)(camera + 0x2AC) += offset_z;
        }
        *(f32 *)(camera + 0x2BC) = *(f32 *)(camera + 0x2A4);
        *(f32 *)(camera + 0x2C4) = *(f32 *)(camera + 0x2AC);
        func_15125594(camera);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151247C0 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151247C0.s")
f32 func_15047C00(f32);                             /* extern */
f32 func_15047D60(f32);                             /* extern */

void func_15124AB4(void *arg0) {
    *(f32 *)((u8 *)arg0 + 0x668) = (f32) -func_15047D60(*(f32 *)((u8 *)arg0 + 0x398));
    *(f32 *)((u8 *)arg0 + 0x66C) = func_15047C00(*(f32 *)((u8 *)arg0 + 0x398));
    *(f32 *)((u8 *)arg0 + 0x664) = (f32) (*(f32 *)((u8 *)arg0 + 0x66C) * func_15047D60(*(f32 *)((u8 *)arg0 + 0x39C)));
    *(f32 *)((u8 *)arg0 + 0x66C) = (f32) (*(f32 *)((u8 *)arg0 + 0x66C) * func_15047C00(*(f32 *)((u8 *)arg0 + 0x39C)));
}
extern f32 D_800A34B0[];
extern s32 D_800BE9F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15124B18 CURRENT (15) */
void func_15124B18(u8 *arg0) {
    s16 temp_t7;
    s32 temp_t8;
    f32 *temp_v0;

    if (*(s16 *)(arg0 + 0x1B4) == 0) {
        *(s16 *)(arg0 + 0x1B4) = 4;
    }
    temp_t8 = *(s32 *)(arg0 + 0x2C) & 0x80;
    if ((temp_t8 != 0) &&
        (**(u16 **)(arg0 + 0x36C) & 0x10)) {
        *(f32 *)(arg0 + 0x348) = 40.0f;
        *(f32 *)(arg0 + 0x34C) = 40.0f;
        *(f32 *)(arg0 + 0x374) = 150.0f;
        return;
    }
    if (temp_t8 != 0) {
        *(f32 *)(arg0 + 0x348) =
            *(f32 *)(arg0 + 0x2FC) - *(f32 *)(arg0 + 0x354);
        return;
    }
    if ((temp_t8 != 0) &&
        ((*(u8 **)(arg0 + 0x3D0))[0x102] == 0) &&
        (D_800BE9F0 != 0x17)) {
        *(f32 *)(arg0 + 0x348) = 40.0f;
        *(f32 *)(arg0 + 0x34C) = 40.0f;
        *(f32 *)(arg0 + 0x374) = 150.0f;
        return;
    }
    if ((*(u8 **)(arg0 + 0x3D0))[0x102] != 0) {
        *(f32 *)(arg0 + 0x348) = 40.0f;
        *(f32 *)(arg0 + 0x34C) = 40.0f;
        *(f32 *)(arg0 + 0x374) = 194.0f;
        return;
    }
    temp_t7 = *(s16 *)(arg0 + 0x1B4);
    temp_v0 = &D_800A34B0[temp_t7 * 2];
    *(f32 *)(arg0 + 0x374) = temp_v0[0];
    *(f32 *)(arg0 + 0x348) = temp_v0[1];
    *(f32 *)(arg0 + 0x34C) = *(f32 *)(arg0 + 0x348);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15124B18 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15124B18.s")
void func_1507C3E0(void *, s16 *, s16 *, s16 *);
void func_1507E1D0(void *, f32 *, f32 *, f32 *);
extern u8 D_800C3671;
extern f32 D_800A3504;
extern f32 D_800A3508;
extern f32 D_800A350C;
extern f32 D_800A3510;
extern f32 D_800A3514;
extern f32 D_800A3518;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15124C38 CURRENT (3092) */
void func_15124C38(void *arg0, s32 arg1) {
    s16 sp52;
    s16 sp50;
    s16 sp4E;
    f32 zero;
    f32 temp_ft4;
    f32 value;
    f32 var_fa0;
    f32 var_fa1;
    f32 selection;
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v1_2;
    void *temp_v0_3;
    void *temp_v1;

    if (((*(u16 *)((u8 *)(arg0) + 0x7F4)) == 0) || (arg1 != 0)) {
        temp_v1 = (*(void **)((u8 *)(arg0) + 0x3D4));
        if (temp_v1 != 0) {
            if (((*(u8 *)((u8 *)(temp_v1) + 0x4E)) & 0xF) == 1) {
                if ((*(s32 *)((u8 *)(arg0) + 0x2C)) & 0x100) {
                    var_fa1 = (f32) (*(s16 *)((u8 *)(temp_v1) + 0x114)) * D_800A3504;
                } else {
                    var_fa1 = (f32) (*(s16 *)((u8 *)(temp_v1) + 0x114)) * D_800A3508;
                }
            } else if ((*(s32 *)((u8 *)(arg0) + 0x2C)) & 0x100) {
                if ((*(u8 *)((u8 *)(arg0) + 0x23E)) == 0) {
                    if ((*(f32 *)((u8 *)(arg0) + 0x77C)) < -15.0f) {
                        var_fa1 = ((f32) (*(s16 *)((u8 *)(temp_v1) + 0x114)) * D_800A350C) + (f32) (*(s16 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0xCC));
                    } else {
                        var_fa1 = ((f32) (*(s16 *)((u8 *)(temp_v1) + 0x114)) * 0.75f) + (f32) (*(s16 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0xCC));
                    }
                } else {
                    var_fa1 = ((f32) (*(s16 *)((u8 *)(temp_v1) + 0x114)) * D_800A3510) + ((f32) (*(s16 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0xCC)));
                }
            } else if (((*(u8 *)((u8 *)(arg0) + 0x23C)) == 0) && ((*(u8 *)((u8 *)(arg0) + 0x600)) != 0)) {
                var_fa1 = (f32) (*(s16 *)((u8 *)(temp_v1) + 0x114)) + (f32) (*(s16 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0xCC));
            } else {
                var_fa1 = ((f32) (*(s16 *)((u8 *)(temp_v1) + 0x114)) * 0.75f) + ((f32) (*(s16 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0xCC)));
            }
            temp_v0 = (*(s32 *)((u8 *)(arg0) + 0x5F0));
            if (temp_v0 & 0x100) {
                var_fa1 += 50.0f;
            } else if (temp_v0 & 0x200) {
                var_fa1 += 150.0f;
            } else if (temp_v0 & 0x800) {
                var_fa1 = 135.0f;
            }
        } else {
            func_1507C3E0((*(void **)((u8 *)(arg0) + 0x3D0)), &sp52, &sp50, &sp4E);
            var_fa1 = (f32) sp52;
            temp_v1 = (*(void **)((u8 *)(arg0) + 0x3D4));
        }
        if ((*(u8 *)((u8 *)temp_v1 + 0x120)) != 0) {
            f32 sp48;
            f32 sp44;
            f32 sp40;

            func_1507E1D0((*(void **)((u8 *)(arg0) + 0x3D0)), &sp40, &sp44, &sp48);
            func_150495B0((f32 *)((u8 *)arg0 + 0x2C0), sp44, (f32 *)((u8 *)arg0 + 0x2A0), 4.0f, 8.0f, (*(f32 *)((u8 *)(arg0) + 0x7B4)));
            return;
        }
        temp_v0 = (*(u8 *)((u8 *)(arg0) + 0x23E));
        temp_v1_2 = (*(s32 *)((u8 *)(arg0) + 0x2C));
        if (((temp_v0 == 0xC) || (temp_v0 == 9) || (temp_v0 == 0x38) || (temp_v0 == 0x39) || (temp_v0 == 0x37) || (temp_v0 == 0x3B) || (temp_v0 == 0x12) || (temp_v0 == 0x15) || (temp_v0 == 0x26) || (temp_v0 == 0x3A)) && (temp_v1_2 & 0x100)) {
            var_fa1 += 30.0f;
        }
        if ((temp_v1_2 & 0x80) || (func_15125490(arg0) != 0)) {
            zero = 0.0f;
            var_fa0 = (*(f32 *)((u8 *)(temp_v0_3 = (*(void **)((u8 *)(arg0) + 0x3D0))) + 0x18)) + (var_fa1 * 0.25f);
        } else {
            temp_v1_2 = (*(s32 *)((u8 *)(arg0) + 0x84));
            temp_a0 = temp_v1_2 & 0x20000000;
            if (temp_a0 != 0) {
                zero = 0.0f;
                var_fa0 = ((*(f32 *)((u8 *)(temp_v0_3 = (*(void **)((u8 *)(arg0) + 0x3D0))) + 0x180))) + var_fa1;
                goto height_done;
            }
            if ((D_800C3671 != 0) || (temp_v0_3 = (*(void **)((u8 *)(arg0) + 0x3D0)), ((*(u8 *)((u8 *)(temp_v0_3) + 0x137)) != 0)) || ((*(u16 *)((u8 *)(temp_v0_3) + 0x84)) == 0x194) || ((*(u8 *)((u8 *)(temp_v0_3) + 0xAD)) == 1)) {
                zero = 0.0f;
                var_fa0 = (*(f32 *)((u8 *)(temp_v0_3 = (*(void **)((u8 *)(arg0) + 0x3D0))) + 0x18)) + var_fa1;
            } else {
                if ((D_800A3514 == (*(f32 *)((u8 *)(arg0) + 0x360))) && (temp_a0 == 0) && !(temp_v1_2 & 0x200000) && ((*(f32 *)((u8 *)(temp_v0_3) + 0x28)) < 170.0f) && ((*(f32 *)((u8 *)(arg0) + 0x370)) > 300.0f)) {
                    zero = 0.0f;
                    var_fa0 = ((*(f32 *)((u8 *)(temp_v0_3) + 0x180))) + var_fa1;
                } else {
                    zero = 0.0f;
                    temp_ft4 = (*(f32 *)((u8 *)(temp_v0_3) + 0x28));
                    value = temp_ft4 * D_800A3518;
                    value = value < zero ? zero : (value > 1.0f ? 1.0f : value);
                    var_fa0 = ((*(f32 *)((u8 *)(temp_v0_3) + 0x180)) + (temp_ft4 * value)) + var_fa1;
                }
            }
        }
height_done:
        temp_v1_2 = (*(u8 *)((u8 *)(temp_v0_3) + 0x102));
        if (temp_v1_2 != 0) {
            value = (*(f32 *)((u8 *)(temp_v0_3) + 0x18));
            if ((*(f32 *)((u8 *)(arg0) + 0x370)) < 100.0f) {
                if ((*(f32 *)((u8 *)(arg0) + 0x2FC)) < value) {
                    var_fa0 = value - 10.0f;
                } else {
                    var_fa0 = value + 10.0f;
                }
            } else {
                var_fa0 = value;
            }
        }
        if (arg1 != 0) {
            *(f32 *)arg1 = var_fa0;
            return;
        }
        if ((*(u8 *)((u8 *)(arg0) + 0x23C)) != 0) {
            (*(f32 *)((u8 *)(arg0) + 0x2C0)) = var_fa0;
            (*(f32 *)((u8 *)(arg0) + 0x2A0)) = zero;
            return;
        }
        temp_v0 = ((*(s32 *)((u8 *)(arg0) + 0x84)) & 0x200000);
        if ((*(s32 *)((u8 *)(arg0) + 0x5F0)) & 0x80) {
            value = 5.0f;
            selection = 8.0f;
        } else if ((*(s32 *)((u8 *)(arg0) + 0x2C)) & 0x100) {
            value = 5.0f;
            selection = 9.0f;
        } else if (temp_v1_2 != 0) {
            value = 7.0f;
            selection = 9.0f;
        } else {
            value = 4.0f;
            selection = 8.0f;
        }
        if (temp_v0 && (var_fa0 < (*(f32 *)((u8 *)(arg0) + 0x2CC)))) {
            value *= 2.0f;
            selection *= 2.0f;
        }
        func_150495B0((f32 *)((u8 *)arg0 + 0x2C0), var_fa0, (f32 *)((u8 *)arg0 + 0x2A0), value, selection, (*(f32 *)((u8 *)(arg0) + 0x7B4)));
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15124C38 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15124C38.s")

f32 func_150484A0(f32, f32);                        /* extern */
extern f32 D_800A351C;
extern f32 D_800A3520;

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
void func_1512523C(void *arg0) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fa1;

    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x2BC) - *(f32 *)((u8 *)arg0 + 0x2F8);
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x2C4) - *(f32 *)((u8 *)arg0 + 0x300);
    temp_fv0 = sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0));
    if (temp_fv0 < 0.0f) {
        var_fa1 = -temp_fv0;
    } else {
        var_fa1 = temp_fv0;
    }
    temp_fv1_2 = func_150484A0(*(f32 *)((u8 *)arg0 + 0x2FC) - *(f32 *)((u8 *)arg0 + 0x2C0), var_fa1) * D_800A351C;
    *(f32 *)((u8 *)arg0 + 0x388) = temp_fv1_2;
    if (temp_fv1_2 > 180.0f) {
        *(f32 *)((u8 *)arg0 + 0x388) = (f32) (*(f32 *)((u8 *)arg0 + 0x388) - 360.0f);
    }
    *(f32 *)((u8 *)arg0 + 0x388) = (f32) -*(f32 *)((u8 *)arg0 + 0x388);
    *(f32 *)((u8 *)arg0 + 0x388) = (f32) (*(f32 *)((u8 *)arg0 + 0x388) - *(f32 *)((u8 *)arg0 + 0x3A8));
    *(f32 *)((u8 *)arg0 + 0x388) = (f32) (*(f32 *)((u8 *)arg0 + 0x38C) + *(f32 *)((u8 *)arg0 + 0x388));
    *(f32 *)((u8 *)arg0 + 0x398) = (f32) (*(f32 *)((u8 *)arg0 + 0x388) * D_800A3520);
}
f32 func_15048FC8(f32 *, void *);                   /* extern */
extern f32 D_800A3524;

void func_15125330(void *arg0) {
    f32 vector[3];
    f32 temp_fv0;

    vector[0] = *(f32 *)((u8 *)arg0 + 0x2BC) - *(f32 *)((u8 *)arg0 + 0x2F8);
    vector[1] = 0.0f;
    vector[2] = *(f32 *)((u8 *)arg0 + 0x2C4) - *(f32 *)((u8 *)arg0 + 0x300);
    temp_fv0 = func_15048FC8(vector, arg0);
    *(f32 *)((u8 *)arg0 + 0x37C) = temp_fv0;
    *(f32 *)((u8 *)arg0 + 0x39C) = (f32) (temp_fv0 * D_800A3524);
}
void func_15125394(void *arg0) {
    s32 var_v0;
    s32 temp_v1;
    s32 mask;

    var_v0 = 0;
    temp_v1 = *(s32 *)((u8 *)arg0 + 0x2C);
    if (!(temp_v1 & 1)) {
        do {
            var_v0 += 1;
            mask = 1 << var_v0;
        } while (!(temp_v1 & mask));
    }
    *(s16 *)((u8 *)arg0 + 0) = var_v0;
}
void func_15124AB4(void *);
void func_1512523C(void *);
void func_15125330(void *);
void func_15127EB8(struct108 *);
void func_1512C490(void *);
extern f32 D_800A3528;

s32 func_151253CC(u8 *arg0) {
    f32 value;
    f32 scale;

    if (*(s32 *)(arg0 + 0x2C) & 0x40000) {
        *(s32 *)(arg0 + 0x84) &= ~0x4F;
        *(s32 *)(arg0 + 0x84) |= 0x2680;
        value = 0.0f;
        *(f32 *)(arg0 + 0x3A8) = value;
        *(f32 *)(arg0 + 0x5E8) = value;
        *(f32 *)(arg0 + 0x38C) = value;
        func_15125330(arg0);
        func_1512523C(arg0);
        scale = D_800A3528;
        value = *(f32 *)(arg0 + 0x37C);
        *(f32 *)(arg0 + 0x380) = value;
        *(f32 *)(arg0 + 0x3A0) = value * scale;
        *(f32 *)(arg0 + 0x398) = *(f32 *)(arg0 + 0x388) * scale;
        func_15124AB4(arg0);
        if ((*(u8 **)(arg0 + 0x3D4))[0x197] != 0) {
            func_15127EB8(arg0);
        }
        func_1512C490(arg0);
        return 1;
    }
    return 0;
}
typedef struct {
    u8 pad_0[0x14];
    f32 field_14;
    f32 field_18;
    f32 field_1C;
    u8 pad_20[0x8D];
    u8 field_AD;
    u8 pad_AE[0x6A];
    f32 field_118;
} CameraCameraTarget;

typedef struct {
    u8 pad_0[0x84];
    u32 field_84;
    u8 pad_88[0x1B4];
    u8 field_23C;
    u8 pad_23D[0x73];
    f32 field_2B0;
    f32 field_2B4;
    f32 field_2B8;
    u8 pad_2BC[0x114];
    CameraCameraTarget *field_3D0;
    u8 pad_3D4[0x22A];
    s16 field_5FE;
} CameraCameraTargetState;

f32 fabsf(f32);
#pragma intrinsic(fabsf)

s32 func_15125490(void *arg0) {
    typedef struct {
        u8 pad0[0x18];
        f32 unk18;
        u8 pad1C[0x91];
        u8 unkAD;
        u8 padAE[0x6A];
        f32 unk118;
    } Obj15125490;
    typedef struct {
        u8 pad0[0x3D0];
        Obj15125490 *unk3D0;
    } Local15125490;
    Local15125490 *a;
    Obj15125490 *v0;
    s32 v1;

    a = arg0;
    v0 = a->unk3D0;
    if (v0->unkAD == 1) {
        v1 = (s32)fabsf(v0->unk18 - v0->unk118);
        if (v1 < 0x64) {
            return 0;
        }
        if (v1 >= 0x12D) {
            return 1;
        }
    } else {
        v0 = 0;
    }
    if ((v0 && 0) && 0) {
        return (s32)0;
    }
}
extern f32 D_800A352C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151254F4 CURRENT (120) */
void func_151254F4(void *arg0, s32 arg1) {
    f32 scale;

    scale = D_800A352C;
    *(f32 *)((u8 *)arg0 + 0x3A0) = *(f32 *)((u8 *)arg0 + 0x380) * scale;
    *(f32 *)((u8 *)arg0 + 0x398) = *(f32 *)((u8 *)arg0 + 0x388) * scale;
    func_15124AB4(arg0);
    func_151239CC(arg0, 1);
    *((u8 *)*(void **)((u8 *)arg0 + 0x3D4) + 0x198) = 0;
    *(s16 *)((u8 *)arg0 + 0x73C) = 0;
    *(void **)((u8 *)arg0 + 0x3D0) = (void *)(D_800CC2D0 + (arg1 * 0x32C));
    *(f32 *)((u8 *)arg0 + 0x670) = 0.0f;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151254F4 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151254F4.s")
extern f32 D_800A3530;

void func_15125594(void *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;

    func_1512523C(arg0);
    func_15125330(arg0);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x37C);
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x5E8);
    *(f32 *)((u8 *)arg0 + 0x380) = (f32) (temp_fv0 - temp_fv1);
    if (temp_fv0 < temp_fv1) {
        *(f32 *)((u8 *)arg0 + 0x380) = (f32) (*(f32 *)((u8 *)arg0 + 0x380) + 360.0f);
    }
    *(f32 *)((u8 *)arg0 + 0x3A0) = (f32) (*(f32 *)((u8 *)arg0 + 0x380) * D_800A3530);
    func_15124AB4(arg0);
}
void func_15125608(f32 *arg0) {
    arg0[0x93] = 3.0f;
    arg0[0x94] = 2.5f;
}
extern u8 D_800DBFF4[];
extern u8 D_800DBFF5;
extern u8 D_800DBFF6[];

void func_15125628(void) {
    u8 v0;
    u8 *p4 = D_800DBFF4;
    u8 *p5 = &D_800DBFF5;
    u8 *p6 = &D_800DBFF6;
    u8 *p7 = &D_800DBFF6[1];

    v0 = *p4;
    if (v0 != 0) {
        *p4 = v0 - 1;
    }
    v0 = *p5;
    if (v0 != 0) {
        *p5 = v0 - 1;
    }
    v0 = *p6;
    if (v0 != 0) {
        *p6 = v0 - 1;
    }
    v0 = *p7;
    if (v0 != 0) {
        *p7 = v0 - 1;
    }
}

void func_15125690(void *arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = &D_800DBFF4[*(u8 *)((u8 *)arg0 + 0x23D)];
    if ((s32) *temp_v0 < arg1) {
        *temp_v0 = (u8) arg1;
    }
}
void func_1508EF80(f32 *, f32 *, f32, f32 *);
u32 func_150ADA20(void);
extern f32 D_800BE9A4;
extern f32 D_800A3534;
extern f32 D_800A3538;
extern f32 D_800A353C;
extern f32 D_800A3540;
extern f32 D_800A3544;
extern f32 D_800A3548;
extern f32 D_800A354C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151256BC CURRENT (295) */
void func_151256BC(u8 *arg0) {
    f32 random;
    f32 bound;
    u32 random_bits;
    f32 sine;
    f32 previous;
    f32 factor;
    f32 first_scale;
    f32 second_scale;
    f32 phase;
    s32 flags;
    f32 *first;
    f32 *second;

    flags = *(s32 *)(arg0 + 0x2C);
    if ((flags & 0x80000) || ((*(s32 *)(arg0 + 0x5F0) & 8) && !(flags & 0x40000))) {
        random_bits = func_150ADA20() % 3U;
        bound = D_800A3534;
        random = (f32)random_bits;
        *(f32 *)(arg0 + 0x29C) += (random + random) * D_800A3538 * D_800BE9A4;
        while (bound < *(f32 *)(arg0 + 0x29C)) {
            *(f32 *)(arg0 + 0x29C) -= bound;
        }
        sine = func_15047D60(*(f32 *)(arg0 + 0x29C));
        previous = *(f32 *)(arg0 + 0x5EC);
        *(f32 *)(arg0 + 0x5EC) = previous + ((sine * 4.0f - previous) * D_800A353C);
        factor = *(f32 *)(arg0 + 0x5EC) * D_800A3540;
        if (*(s32 *)(arg0 + 0x2C) & 0x80000) {
            first_scale = 4.0f;
            second_scale = 4.0f;
        } else {
            first_scale = 1.0f;
            second_scale = 20.0f;
        }
        first = (f32 *)(arg0 + 0x2F8);
        second = (f32 *)(arg0 + 0x2BC);
        func_1508EF80(first, second, factor * first_scale, first);
        func_1508EF80(second, first, factor * second_scale, second);
        return;
    }
    phase = *(f32 *)(arg0 + 0x29C);
    if (phase != 0.0f) {
        *(f32 *)(arg0 + 0x29C) = phase - phase * D_800A3544;
        sine = func_15047D60(*(f32 *)(arg0 + 0x29C));
        previous = *(f32 *)(arg0 + 0x5EC);
        first = (f32 *)(arg0 + 0x2F8);
        second = (f32 *)(arg0 + 0x2BC);
        *(f32 *)(arg0 + 0x5EC) = previous + ((sine * 4.0f - previous) * D_800A3548);
        factor = *(f32 *)(arg0 + 0x5EC) * D_800A354C;
        func_1508EF80(first, second, factor, first);
        func_1508EF80(second, first, factor * 20.0f, second);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151256BC */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151256BC.s")
s32 func_15123934(void *, s32, s32, s32, s32);
s32 func_151239CC(void *, s32);

void func_15125924(u8 *arg0) {
    s32 type;
    s32 value;
    u8 *target;

    target = *(u8 **)(arg0 + 0x3D4);
    if (target != 0) {
        type = target[0x4E];
        value = (s32)*(f32 *)(target + 0x1C);
    } else {
        value = 0;
        type = 0;
    }
    if (!(*(s32 *)(arg0 + 0x2C) & 0x40) &&
        ((*(s32 *)(arg0 + 0x84) & 0x4000) ||
         (*(u8 **)(arg0 + 0x3D0))[0x102] != 0)) {
        if ((func_15125490(arg0) != 0) &&
            (type == 0) && (value == 0)) {
            if ((func_15123934(arg0, 0x80, 1, 1, 0xD) != 0) &&
                (*(s32 *)(arg0 + 0x6C8) == 0)) {
                func_15124B18(arg0);
                *(s32 *)(arg0 + 0x5F0) |= 0x1000;
            }
        } else {
            s32 flags;
            f32 difference;

            if (*(s32 *)(arg0 + 0x2C) & 0x80) {
                func_151239CC(arg0, 0xD);
                *(f32 *)(arg0 + 0x190) = 0.0f;
            }
            flags = *(s32 *)(arg0 + 0x5F0);
            if (flags & 0x1000) {
                difference = *(f32 *)(arg0 + 0x2FC) - *(f32 *)(arg0 + 0x354);
                *(s32 *)(arg0 + 0x5F0) = flags & ~0x1000;
                *(f32 *)(arg0 + 0x344) = difference;
                *(f32 *)(arg0 + 0x348) = difference;
            }
        }
    }
}
typedef struct CameraFixedViewState {
    s32 enabled;
    s32 mode;
    f32 field_08;
    u8 pad_0C[0x14];
    f32 field_20;
    u8 pad_24[4];
    f32 field_28;
} CameraFixedViewState;

void func_1512D560(void *, s32, s32);
extern f32 D_800A3550;
extern f32 D_800A3554;
extern CameraFixedViewState D_800C3600;
extern f32 D_800C3614;
extern f32 D_800C3618;
extern f32 D_800C361C;
extern f32 D_800C3624;
extern s8 D_800C365C;

void func_15125A6C(struct108 *arg0) {
    f32 offsetCos;
    f32 offsetSin;
    f32 radius;
    f32 yaw;
    f32 offsetRadius;
    f32 height;
    f32 trig;
    f32 angle;
    f32 offsetAngle;
    u8 mode;

    mode = arg0->unk23E;
    if (mode == 0x2A) {
        yaw = arg0->unk3D0->unk40;
        if (arg0->unk2C != 0x40000) {
            func_1512D560(arg0, 5, 0);
            arg0->unk7E4 = 1U;
        }
        *D_800DBFF4 = 3;
        ((struct168 *)&D_800C3600)->unk0 = 1;
        ((struct168 *)&D_800C3600)->unk4 = 0;
        radius = 138.0f;
        offsetRadius = 46.0f;
        height = 96.0f;
        angle = yaw * D_800A3550;
        trig = func_15047D60(angle);
        offsetAngle = (yaw - 90.0f) * D_800A3554;
        offsetSin = func_15047D60(offsetAngle);
        D_800C3614 = (offsetSin * offsetRadius) + (arg0->unk3D0->x_position + (radius * trig));
        D_800C3618 = arg0->unk3D0->y_position + height;
        trig = func_15047C00(angle);
        offsetCos = func_15047C00(offsetAngle);
        D_800C361C = (offsetCos * offsetRadius) + (arg0->unk3D0->z_position + (radius * trig));
        ((struct168 *)&D_800C3600)->unk20 = 0.0f;
        D_800C3624 = -180.0f;
        ((struct168 *)&D_800C3600)->unk8 = 0.0f;
        ((struct168 *)&D_800C3600)->unk28 = yaw - 180.0f;
        D_800C365C = 0;
        func_1512D560(arg0, 7, &D_800C3600);
        return;
    }
    if (arg0->unk7E4 != 0) {
        func_1512D560(arg0, 6, 0);
        arg0->unk7E4 = 0U;
    }
}
typedef struct CameraCameraTransition {
    u8 pad0[0x23E];
    u8 mode;
    u8 pad23F[0x12B];
    u16 status36A;
    u16 *status36C;
    u8 pad370[0x60];
    u8 *position;
    u8 pad3D4[0x21C];
    s32 flags;
    u8 pad5F4[0x1D8];
    s32 timer;
} CameraCameraTransition;

void func_1509BFB0(s32, s32, s32, s32, ...);
extern u8 D_800D1940;

void func_15125C40(CameraCameraTransition *arg0) {
    s32 isSpecial;
    s32 isActive;
    s32 mode;

    mode = arg0->mode;
    isSpecial = D_800D1940 == 0x42 && mode == 0x1A;
    isActive = mode == 3 || mode == 0x1A || isSpecial;
    arg0->timer--;
    if (isActive != 0) {
        if (arg0->timer == 0) {
            if (isSpecial != 0) {
                func_1509BFB0(3, 0x9000, 0x18,
                              (s32)*(f32 *)(arg0->position + 0x40), 0, 0xFA);
            } else if (mode == 0x1A) {
                func_1509BFB0(3, 0x9000, 0x18, 0, 0, 0xFA);
            }
            arg0->flags |= 2;
            *arg0->status36C |= 0x10;
            arg0->status36A |= 0x10;
            arg0->timer = 1;
        }
    } else {
        if ((arg0->flags & 2) && (isActive == 0)) {
            func_1509BFB0(1, 0x9000, 0x10, 0);
            func_1509BFB0(1, 0x9000, 0xF, 0);
            arg0->flags &= ~2;
        }
        arg0->timer = 2;
    }
}
extern s16 D_80084480;
extern u16 D_800BE710[];
extern u8 D_800C3671;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15125DB4 CURRENT (2680) */
void func_15125DB4(void *arg0) {
    s16 temp_v1_3;
    u16 *temp_v0;
    s32 temp_v1;
    void *temp_v1_2;

    temp_v1 = (*(u8 *)((u8 *)(arg0) + 0x23E));
    if (((*(u8 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D4))) + 0x120)) != 0) || (D_80084480 != 0)) {
        temp_v0 = (*(u16 **)((u8 *)(arg0) + 0x36C));
        (*(u16 *)((u8 *)(arg0) + 0x36A)) = 0U;
        *temp_v0 &= 0xFFE0;
        return;
    }
    if (temp_v1 != 0) {
        if ((temp_v1 == 2) || (temp_v1 == 0x12) || (temp_v1 == 0x13) || (temp_v1 == 0xA) || (temp_v1 == 0x34) || (temp_v1 == 0x10) || (temp_v1 == 0xF)) {
            if (temp_v1 == 0xF) {
                func_1509BFB0(3, 0x9000, 0x18, 0x25, 0x13, 0x1E0);
            }
            temp_v0 = (*(u16 **)((u8 *)(arg0) + 0x36C));
            *temp_v0 |= 0x10;
            temp_v0 = (*(u16 **)((u8 *)(arg0) + 0x36C));
            (*(u16 *)((u8 *)(arg0) + 0x36A)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x36A)) | 0x10);
            *temp_v0 &= 0xFFF0;
        } else {
            (*(u16 *)((u8 *)(arg0) + 0x36A)) = (u16) D_800BE710[(*(s16 *)((u8 *)(arg0) + 0x368))];
        }
        if ((temp_v1 == 3) || (temp_v1 == 0xD) || (temp_v1 == 0x1A) || (temp_v1 == 0x2A)) {
            temp_v0 = (*(u16 **)((u8 *)(arg0) + 0x36C));
            (*(u16 *)((u8 *)(arg0) + 0x36A)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x36A)) & ~0xF);
            *temp_v0 &= ~0xF;
        }
        if (temp_v1 == 0x29) {
            temp_v0 = (*(u16 **)((u8 *)(arg0) + 0x36C));
            *temp_v0 |= 0x10;
            (*(u16 *)((u8 *)(arg0) + 0x36A)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x36A)) | 0x10);
        }
    } else if ((*(s32 *)((u8 *)(arg0) + 0x2C)) & 0x100) {
        temp_v0 = (*(u16 **)((u8 *)(arg0) + 0x36C));
        (*(u16 *)((u8 *)(arg0) + 0x36A)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x36A)) & 0xFFF0);
        *temp_v0 &= 0xFFF0;
    }
    if (((*(u8 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0xAD)) == 1) && ((*(s32 *)((u8 *)(arg0) + 0x2C)) & 0x80)) {
        temp_v0 = (*(u16 **)((u8 *)(arg0) + 0x36C));
        (*(u16 *)((u8 *)(arg0) + 0x36A)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x36A)) & 0xFFE3);
        *temp_v0 &= 0xFFF3;
    }
    if ((*(s32 *)((u8 *)(arg0) + 0x84)) & 0x200000) {
        (*(u16 *)((u8 *)(arg0) + 0x36A)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x36A)) & ~0xF);
    }
    if ((D_800C3671 != 0) || ((*(s32 *)((u8 *)(arg0) + 0x5F0)) & 0x80)) {
        temp_v0 = (*(u16 **)((u8 *)(arg0) + 0x36C));
        (*(u16 *)((u8 *)(arg0) + 0x36A)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x36A)) & 0xFFE0);
        *temp_v0 &= 0xFFE0;
    }
    temp_v1_2 = (*(void **)((u8 *)(arg0) + 0x3D4));
    if (((*(u8 *)((u8 *)(temp_v1_2) + 0x7D)) != 0) || ((*(u8 *)((u8 *)(temp_v1_2) + 0x1AC)) != 0) || ((*(u8 *)((u8 *)(temp_v1_2) + 0x27)) != 0)) {
        temp_v0 = (*(u16 **)((u8 *)(arg0) + 0x36C));
        (*(u16 *)((u8 *)(arg0) + 0x36A)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x36A)) & 0xFFEF);
        *temp_v0 &= 0xFFEF;
    }
    if (((*(u8 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D4))) + 0x95)) != 0) || (((*(s16 *)((u8 *)(arg0) + 0x5FC)) != 0) && ((*(u8 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D4))) + 0x1B3)) != 0))) {
        temp_v0 = (*(u16 **)((u8 *)(arg0) + 0x36C));
        (*(u16 *)((u8 *)(arg0) + 0x36A)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x36A)) & ~0x1F);
        *temp_v0 &= ~0x1F;
    }
    if ((((*(s32 *)((u8 *)(arg0) + 0x2C)) & 0x100) && ((*(s16 *)((u8 *)(arg0) + 0x73C)) == 0)) || ((*(s16 *)((u8 *)(arg0) + 0x73C)) == 3)) {
        temp_v0 = (*(u16 **)((u8 *)(arg0) + 0x36C));
        (*(u16 *)((u8 *)(arg0) + 0x36A)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x36A)) & ~0x10);
        *temp_v0 &= ~0x10;
    }
    if ((*(s32 *)((u8 *)(arg0) + 0x2C)) & 0x40) {
        temp_v1_3 = (*(s16 *)((u8 *)(arg0) + 0x84A));
        if (temp_v1_3 != 0) {
            temp_v0 = (*(u16 **)((u8 *)(arg0) + 0x36C));
            (*(s16 *)((u8 *)(arg0) + 0x84A)) = (s16) (temp_v1_3 - D_800BE9E4);
            (*(u16 *)((u8 *)(arg0) + 0x36A)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x36A)) & ~0x10);
            *temp_v0 &= ~0x10;
            if ((*(s16 *)((u8 *)(arg0) + 0x84A)) <= 0) {
                (*(s16 *)((u8 *)(arg0) + 0x84A)) = 0;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15125DB4 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15125DB4.s")
void func_151220D0(void *);
void func_151247C0(void *);
void func_15124C38(void *, s32);

void func_15126138(u8 *arg0) {
    u8 *target;

    func_151247C0(arg0);
    target = *(u8 **)(arg0 + 0x3D0);
    if (((*(f32 *)(arg0 + 0x2B0) != *(f32 *)(target + 0x14)) ||
         (*(f32 *)(arg0 + 0x2B4) != *(f32 *)(target + 0x18)) ||
         (*(f32 *)(arg0 + 0x2B8) != *(f32 *)(target + 0x1C))) &&
        (*(s32 *)(arg0 + 0x2C) & ~0x100)) {
        *(s16 *)(arg0 + 0x298) = 1;
        *(s16 *)(arg0 + 0x7E6) = 0x3C;
        *(s8 *)(arg0 + 0x8ED) = 0;
    } else {
        *(s16 *)(arg0 + 0x298) = 0;
    }
    if (*(s32 *)(arg0 + 0x84) & 0x200000) {
        target = *(u8 **)(arg0 + 0x3D0);
        if ((*(s32 *)target != 0x1E) &&
            (target[0x102] == 0) &&
            (**(u16 **)(arg0 + 0x36C) & 0xF) &&
            !(*(s32 *)(arg0 + 0x2C) & 0x40)) {
            func_151220D0(arg0);
        }
    }
    func_15124C38(arg0, 0);
}
typedef struct Camera2623CVector {
    f32 x;
    f32 y;
    f32 z;
} Camera2623CVector;

void func_15143134(f32 *, f32 *, s32);

void func_1512623C(u8 *arg0, u8 *arg1, s32 arg2, f32 *arg3, f32 *arg4,
                   f32 *arg5, s32 arg6) {
    s32 saved_result;
    Camera2623CVector input;
    Camera2623CVector output;
    s32 mode;
    s32 result;

    result = 1;
    if (*(s32 *)(arg0 + 0x1D4) != 0) {
        result = 0;
        if (arg6 != 0) {
            mode = 3;
            input.x = 0.0f;
            input.z = 0.0f;
            input.y = 20.0f;
        } else if (arg2 == 0x1B) {
            mode = 4;
            input.y = 116.0f;
            input.x = 0.0f;
            input.z = 130.0f;
        } else {
            result = 1;
        }
        if (result == 0) {
            arg2 = *(s32 *)(arg0 + 0x1D4);
            arg2 += mode << 6;
            func_15143134(&input.x, &output.x, (saved_result = result, arg2));
            result = saved_result;
            *arg3 = output.x;
            *arg4 = output.y;
            *arg5 = output.z;
        }
    }
    if (result != 0) {
        *arg3 = *(f32 *)(arg0 + 0x14);
        *arg4 = ((f32)*(s16 *)(arg1 + 0x114) * 0.75f) + *(f32 *)(arg0 + 0x18);
        *arg5 = *(f32 *)(arg0 + 0x1C);
    }
}
void func_15048758(f32 *);
void func_150627D4(void *);
void func_1510B32C(s32, f32, f32, f32);
s32 func_1000FA64(s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
void func_151C9BA0(u8 *, s32);
s32 func_15127520(u8 *, s32, s32, s32, s32, s32, u16 *);
s32 func_151277B0(u8 *, s32, s32, s32, s32, s32, u16 *);
extern f32 D_800A3558;
extern f32 D_800A355C;
extern f32 D_800A3560;
extern f32 D_800A3564;
extern f32 D_800A3568;
extern f32 D_800A356C;
extern f32 D_800A3570;
extern f32 D_800A3574;
extern f32 D_800A3578;
extern f32 D_800A357C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15126378 CURRENT (13092) */
s32 func_15126378(u8 *arg0) {
    u8 *var_t0;
    u8 *spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    s32 spB4;
    f32 spAC;
    f32 spA4;
    union { f32 value; u32 bits; } sound_product;
    s32 sp98;
    Camera22CVector direction;
    f32 sp88;
    s32 sp58;
    u8 *sp54;
    u8 *sp50;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft2;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_ft5;
    s32 temp_t2;
    s32 var_v1;
    s8 temp_a0;
    s8 temp_a1;
    u8 *temp_a1_2;
    u8 *temp_a2;
    u8 *target;
    u8 temp_v0_9;
    u8 var_a0;
    u8 var_v0;

    target = (u8 *)D_800BE628 + ((*(u8 *)((u8 *)(arg0) + 0x23D)) * 0x180);
    temp_fv0 = (*(f32 *)((u8 *)(target) + 0x6C));
    var_t0 = (*(u8 **)((u8 *)(arg0) + 0x3D4));
    spC0 = (*(f32 *)((u8 *)(target) + 0x70)) / temp_fv0;
    spBC = -(temp_fv0 - 5.0f);
    spB8 = temp_fv0 * D_800A3558;
    spB4 = (*(u8 *)((u8 *)(arg0) + 0x23E));
    if (((spB4 == 0xC) && ((*(u16 *)((u8 *)((*(u8 **)((u8 *)(arg0) + 0x3D0))) + 0x84)) != 0x76)) || (spB4 == 0x1B)) {
        target = (*(void **)((u8 *)(arg0) + 0x36C));
        (*(u16 *)((u8 *)(arg0) + 0x36A)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x36A)) | 0x10);
        (*(u16 *)((u8 *)(target) + 0)) = (u16) ((*(u16 *)((u8 *)(target) + 0)) | 0x10);
    }
    var_a0 = (*(u8 *)((u8 *)(var_t0) + 0x197));
    if ((var_a0 == 0) && ((target = (*(void **)((u8 *)(arg0) + 0x36C)), ((*(s8 *)((u8 *)(target) + 2)) != 0)) || ((*(s8 *)((u8 *)(target) + 3)) != 0))) {
        (*(s8 *)((u8 *)(var_t0) + 0x194)) = 1;
        var_a0 = (*(u8 *)((u8 *)(var_t0) + 0x197));
    }
    target = (*(u8 **)((u8 *)(arg0) + 0x3D0));
    var_v1 = (*(u8 *)((u8 *)(target) + 0x65));
    if (var_v1 != 0) {
        spC8 = (var_v1 * 0x32C) - 0x32C + D_800CC2D0;
    } else {
        spC8 = target;
    }
    var_v1 = (*(u8 *)((u8 *)(var_t0) + 0x11A)) == 2;
    if (var_v1 == 0) {
        var_v1 = spB4 == 0x1B;
        if (var_v1 == 0) {
            var_v1 = spB4 == 0x1F;
            if (var_v1 == 0) {
                var_v1 = spB4 == 0x29;
            }
        }
    }
    if (((spB4 == 0x23) || (spB4 == 0x24) || (spB4 == 0x16) || (spB4 == 0x18) || (spB4 == 0x41) || (spB4 == 0xC) || (spB4 == 0x14) || (spB4 == 0x3F) || (spB4 == 0x1B) || (spB4 == 0x1F) || (spB4 == 0x29)) && ((*(u16 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x36C))) + 0)) & 0x10) && (var_v1 != 0) && (((s32) (*(f32 *)((u8 *)(target) + 0x28)) == 0) || ((s32) (*(f32 *)((u8 *)(spC8) + 0x28)) == 0)) && ((*(u8 *)((u8 *)(target) + 0x104)) == 0) && (var_a0 == 0)) {
        sp58 = spB4 == 0x1F;
        (*(s8 *)((u8 *)((*(u8 **)((u8 *)(arg0) + 0x3D4))) + 0x198)) = 0;
        (*(s16 *)((u8 *)(arg0) + 0x73C)) = 0;
        if (((sp58 != 0) || (spB4 == 0x29)) && !((*(s32 *)((u8 *)(arg0) + 0x5F0)) & 4)) {
            spAC = ((*(f32 *)((u8 *)(spC8) + 0x40)) - 90.0f) - ((f32) (*(s16 *)((u8 *)(spC8) + 0x2E4)) * D_800A3558);
            (*(s8 *)((u8 *)(var_t0) + 0x194)) = 1;
        } else {
            spAC = (*(f32 *)((u8 *)((*(u8 **)((u8 *)(arg0) + 0x3D0))) + 0x40)) - 90.0f;
        }
        func_15048758(&spAC);
        spA4 = spAC * D_800A355C;
        func_151239CC(arg0, 1);
        (*(s8 *)((u8 *)(var_t0) + 0x197)) = 2;
        func_151C9BA0(arg0, spB4);
        sp54 = arg0 + 0x2F8;
        func_1512623C(spC8, (*(u8 **)((u8 *)(arg0) + 0x3D4)), spB4, (f32 *) sp54, (f32 *) (arg0 + 0x2FC), (f32 *) (arg0 + 0x300), (*(s32 *)((u8 *)(arg0) + 0x5F0)) & 0x10);
        (*(f32 *)((u8 *)(arg0) + 0x2BC)) = (f32) ((func_15047D60(spA4) * 100.0f) + (*(f32 *)((u8 *)(arg0) + 0x2F8)));
        (*(f32 *)((u8 *)(arg0) + 0x2C0)) = (f32) ((*(f32 *)((u8 *)((*(u8 **)((u8 *)(arg0) + 0x3D0))) + 0x18)) + ((f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)(arg0) + 0x3D4))) + 0x114)) * 0.75f));
        (*(f32 *)((u8 *)(arg0) + 0x2C4)) = (f32) ((func_15047C00(spA4) * 100.0f) + (*(f32 *)((u8 *)(arg0) + 0x300)));
        *(Camera22CVector *)(var_t0 + 0x13C) = *(Camera22CVector *)sp54;
        (*(f32 *)((u8 *)(var_t0) + 0x18C)) = (f32) (*(f32 *)((u8 *)(arg0) + 0x37C));
        *(Camera22CVector *)(var_t0 + 0x160) = *(Camera22CVector *)sp54;
        if (spB4 != (*(s32 *)((u8 *)(var_t0) + 0x190))) {
            if (spB4 == 0x1B) {
                temp_fv0 = 1.0f;
            } else if (spB4 == 0x16) {
                temp_fv0 = 0.75f;
            } else {
                temp_fv0 = 0.5f;
            }
            if ((spB4 == 0x18) || (spB4 == 0x41) || (spB4 == 0x3F) || (spB4 == 0x14) || (spB4 == 0x12)) {
                if (temp_fv0 < 0.0f) {
                    temp_fv0 = 0.0f;
                } else {
                    if (D_800A3560 < temp_fv0) {
                        temp_fv1 = D_800A3560;
                    } else {
                        temp_fv1 = temp_fv0;
                    }
                    temp_fv0 = temp_fv1;
                }
            }
            (*(u8 *)((u8 *)(var_t0) + 0x194)) = 1U;
            (*(s32 *)((u8 *)(var_t0) + 0x190)) = spB4;
            (*(f32 *)((u8 *)(var_t0) + 0x184)) = (f32) (((0.0f - spBC) * temp_fv0) + spBC);
        }
        if ((*(u8 *)((u8 *)(var_t0) + 0x194)) != 0) {
            (*(f32 *)((u8 *)(var_t0) + 0x174)) = spAC;
            (*(f32 *)((u8 *)(var_t0) + 0x178)) = 0.0f;
            (*(f32 *)((u8 *)(var_t0) + 0x170)) = 0.0f;
            (*(f32 *)((u8 *)(var_t0) + 0x17C)) = 0.0f;
            (*(f32 *)((u8 *)(var_t0) + 0x180)) = 0.0f;
            (*(u8 *)((u8 *)(var_t0) + 0x194)) = 0U;
            (*(f32 *)((u8 *)(var_t0) + 0x16C)) = (f32) (*(f32 *)((u8 *)(var_t0) + 0x174));
        }
        temp_fv0 = (*(f32 *)((u8 *)(var_t0) + 0x184));
        (*(f32 *)((u8 *)(var_t0) + 0x188)) = (f32) (temp_fv0 * spC0);
        (*(f32 *)((u8 *)(arg0) + 0x19C)) = temp_fv0;
        (*(f32 *)((u8 *)(arg0) + 0x1A0)) = (f32) (*(f32 *)((u8 *)(var_t0) + 0x188));
        (*(f32 *)((u8 *)(arg0) + 0x1A4)) = (f32) (*(f32 *)((u8 *)(var_t0) + 0x184));
        (*(f32 *)((u8 *)(arg0) + 0x1A8)) = (f32) (*(f32 *)((u8 *)(var_t0) + 0x188));
        func_1510B32C((s32) (*(u8 *)((u8 *)(arg0) + 0x23D)), (*(f32 *)((u8 *)(arg0) + 0x19C)), (*(f32 *)((u8 *)(arg0) + 0x1A0)), 1.0f);
        (*(f32 *)((u8 *)(((u8 *)D_800BE628 + ((*(u8 *)((u8 *)(arg0) + 0x23D)) * 0x180))) + 0x84)) = 1.0f;
        func_150627D4((*(u8 **)((u8 *)(arg0) + 0x3D0)));
        D_800DBFF4[(*(u8 *)((u8 *)(arg0) + 0x23D))] = 2;
        if ((spB4 == 0x24) || (spB4 == 0x23)) {
            func_1000FA64(0x605, 0, 0, 0, 0x6590, 0x12C, 0x12B, func_15127520, (s32)arg0, (u32) (-(*(f32 *)((u8 *)(arg0) + 0x1A4)) * D_800A3564), 0, 0);
            goto block_64;
        }
        if ((spB4 == 0x1B) || (sp58 != 0) || (spB4 == 0x29)) {
            sound_product.value = (*(f32 *)((u8 *)(var_t0) + 0x174)) * (*(f32 *)((u8 *)(var_t0) + 0x178));
            func_1000FA64(0x622, 0, 0, 0, 0x6590, 0x12C, 0x12B, func_15127520, (s32)arg0, (u32) (-(*(f32 *)((u8 *)(arg0) + 0x1A4)) * D_800A3568) | 0x80000000, 0x100, 0);
            func_1000FA64(0x622, 0, 0, 0, 0x3E80, 0x12C, 0x12B, func_151277B0, (s32)arg0, sound_product.bits, 0x100, 0);
block_64:
            ;
        }
        (*(u8 *)((u8 *)(spC8) + 0x2FC)) = (u8) ((*(u8 *)((u8 *)(spC8) + 0x2FC)) | (1 << (*(u8 *)((u8 *)(arg0) + 0x23D))));
        (*(u8 *)((u8 *)(spC8) + 0x74)) = (u8) ((*(u8 *)((u8 *)(spC8) + 0x74)) | (1 << (*(u8 *)((u8 *)(arg0) + 0x23D))));
        var_a0 = (*(u8 *)((u8 *)(var_t0) + 0x197));
    }
    var_v0 = var_a0;
    if (var_a0 == 0) {
        return 0;
    }
    if (var_v0 == 2) {
        sp54 = arg0 + 0x2F8;
        sp98 = (s32) (*(u16 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x36C))) + 0));
        func_1512623C(spC8, (*(u8 **)((u8 *)(arg0) + 0x3D4)), (s32) spB4, (f32 *) sp54, (f32 *) (arg0 + 0x2FC), (f32 *) (arg0 + 0x300), (*(s32 *)((u8 *)(arg0) + 0x5F0)) & 0x10);
        temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0x19C)) / spBC;
        if (temp_fv0 < 0.0f) {
            temp_fv0 = 0.0f;
        } else {
            if (temp_fv0 > 1.0f) {
                temp_fv1 = 1.0f;
            } else {
                temp_fv1 = temp_fv0;
            }
            spC4 = temp_fv1;
            temp_fv0 = spC4;
        }
        if (!(sp98 & 0x10) || (spB4 == 0) || ((*(u8 *)((u8 *)(var_t0) + 0x1AC)) != 0) || ((target = (*(u8 **)((u8 *)(arg0) + 0x3D0)), ((*(u8 *)((u8 *)(target) + 0x1CA)) == 0)) && (spB4 != 0x29)) || ((temp_t2 = spB4 == 0x1B, ((*(u8 *)((u8 *)(target) + 0x104)) != 0)) && ((*(u8 *)((u8 *)(target) + 0x65)) == 0) && ((s32) (*(f32 *)((u8 *)(target) + 0x28)) != 0) && (spB4 != 0x1F) && (spB4 != 0x29))) {
            func_15127EB8(arg0);
            return 0;
        }
        sp50 = var_t0 + 0x13C;
        sp58 = spB4 == 0x1F;
        if (temp_t2 != 0) {
            temp_fa0 = 19.0f;
            var_ft5 = 31.0f;
        } else {
            temp_fa0 = 25.0f;
            var_ft5 = 90.0f;
        }
        target = (*(void **)((u8 *)(arg0) + 0x36C));
        temp_a0 = (*(s8 *)((u8 *)(target) + 2));
        if (temp_a0 < 0) {
            var_v1 = -1;
        } else {
            var_v1 = 1;
        }
        spC4 = temp_fv0;
        temp_fv1 = (f32) temp_a0;
        temp_a1 = (*(s8 *)((u8 *)(target) + 3));
        temp_fv0 = 1.0f / (((var_ft5 - temp_fa0) * spC4) + temp_fa0);
        temp_ft4 = temp_fv0 * temp_fv0;
        temp_fv0 = (f32) temp_a1;
        temp_fa1 = (f32) var_v1 * (temp_fv1 * temp_fv1 * temp_ft4);
        if (temp_a1 < 0) {
            var_v1 = -1;
        } else {
            var_v1 = 1;
        }
        temp_fa0 = (f32) var_v1 * (temp_fv0 * temp_fv0 * temp_ft4);
        if (temp_t2 != 0) {
            temp_fa1 = temp_fa1 * 0.25f;
            temp_fa0 = temp_fa0 * 0.5f;
            if (temp_fa1 < -3.0f) {
                temp_fa1 = -3.0f;
            } else {
                if (temp_fa1 > 3.0f) {
                    temp_fv1 = 3.0f;
                } else {
                    temp_fv1 = temp_fa1;
                }
                temp_fa1 = temp_fv1;
            }
            if (temp_fa0 < -3.0f) {
                temp_fa0 = -3.0f;
            } else if (temp_fa0 > 3.0f) {
                temp_fa0 = 3.0f;
            } else {
            }
        } else if (spB4 == 0xC) {
            temp_fa1 *= 1.5f;
            temp_fa0 *= 1.5f;
        }
        (*(f32 *)((u8 *)(var_t0) + 0x174)) = (f32) ((*(f32 *)((u8 *)(var_t0) + 0x174)) - temp_fa1);
        (*(f32 *)((u8 *)(var_t0) + 0x178)) = (f32) ((*(f32 *)((u8 *)(var_t0) + 0x178)) + temp_fa0);
        func_15048758((f32 *) (var_t0 + 0x174));
        if ((sp58 != 0) || (spB4 == 0x29)) {
            temp_fv1 = -80.0f;
            temp_fv0 = *(f32 *)(var_t0 + 0x178);
            if (temp_fv0 < temp_fv1) {
                *(f32 *)(var_t0 + 0x178) = temp_fv1;
            } else {
                temp_fa0 = 30.0f;
                if (temp_fa0 < temp_fv0) {
                    temp_fv1 = temp_fa0;
                } else {
                    temp_fv1 = temp_fv0;
                }
                *(f32 *)(var_t0 + 0x178) = temp_fv1;
            }
        } else if (temp_t2 != 0) {
            temp_fv1 = -60.0f;
            temp_fv0 = *(f32 *)(var_t0 + 0x178);
            if (temp_fv0 < temp_fv1) {
                *(f32 *)(var_t0 + 0x178) = temp_fv1;
            } else {
                temp_fa0 = 50.0f;
                if (temp_fa0 < temp_fv0) {
                    temp_fv1 = temp_fa0;
                } else {
                    temp_fv1 = temp_fv0;
                }
                *(f32 *)(var_t0 + 0x178) = temp_fv1;
            }
        } else {
            temp_fv1 = -80.0f;
            temp_fv0 = *(f32 *)(var_t0 + 0x178);
            if (temp_fv0 < temp_fv1) {
                *(f32 *)(var_t0 + 0x178) = temp_fv1;
            } else {
                temp_fa0 = 80.0f;
                if (temp_fa0 < temp_fv0) {
                    temp_fv1 = temp_fa0;
                } else {
                    temp_fv1 = temp_fv0;
                }
                *(f32 *)(var_t0 + 0x178) = temp_fv1;
            }
        }
        func_15049688(var_t0 + 0x16C, (*(f32 *)((u8 *)(var_t0) + 0x174)), var_t0 + 0x17C, 6.0f, 8.0f, (*(f32 *)((u8 *)(arg0) + 0x7B4)));
        func_15049688(var_t0 + 0x170, (*(f32 *)((u8 *)(var_t0) + 0x178)), var_t0 + 0x180, 6.0f, 8.0f, (*(f32 *)((u8 *)(arg0) + 0x7B4)));
        if ((spB4 != 0x16) && (spB4 != 0xC) && ((spB4 != 0x29) || (spB4 != 0x1F) || (D_800BE616 != 0)) && ((sp98 & 0xC) != 0xC)) {
            if (sp98 & 8) {
                temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0x1A4));
                if ((spBC < temp_fv0) && (spB4 != 0xC)) {
                    (*(f32 *)((u8 *)(arg0) + 0x1A4)) = (f32) (temp_fv0 - spB8);
                    *(f32 *)(arg0 + 0x1A8) = (*(f32 *)((u8 *)(arg0) + 0x1A8)) - (spB8 * spC0);
                    goto camera_zoom_done;
                }
            }
            if (sp98 & 4) {
                temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0x1A4));
                if (temp_fv0 < 0.0f) {
                    (*(f32 *)((u8 *)(arg0) + 0x1A4)) = (f32) (temp_fv0 + spB8);
                    *(f32 *)(arg0 + 0x1A8) = (*(f32 *)((u8 *)(arg0) + 0x1A8)) + (spB8 * spC0);
                }
            }
        }
camera_zoom_done:
        temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0x1A4));
        if (spB4 == 0x24) {
            if (temp_fv0 < spBC) {
                (*(f32 *)((u8 *)(arg0) + 0x1A4)) = spBC;
            } else {
                if (temp_fv0 > 0.0f) {
                    temp_fv1 = 0.0f;
                } else {
                    temp_fv1 = temp_fv0;
                }
                (*(f32 *)((u8 *)(arg0) + 0x1A4)) = temp_fv1;
            }
            temp_fv1 = spBC * spC0;
            temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0x1A8));
            if (temp_fv0 < temp_fv1) {
                *(f32 *)(arg0 + 0x1A8) = temp_fv1;
            } else {
                temp_fa0 = 0.0f;
                if (temp_fa0 < temp_fv0) {
                    temp_fv1 = temp_fa0;
                } else {
                    temp_fv1 = temp_fv0;
                }
                *(f32 *)(arg0 + 0x1A8) = temp_fv1;
            }
        } else if (temp_t2 != 0) {
            temp_fa0 = spBC * 0.5f;
            if (temp_fv0 < temp_fa0) {
                (*(f32 *)((u8 *)(arg0) + 0x1A4)) = temp_fa0;
            } else {
                if (temp_fv0 > 0.0f) {
                    temp_fv1 = 0.0f;
                } else {
                    temp_fv1 = temp_fv0;
                }
                (*(f32 *)((u8 *)(arg0) + 0x1A4)) = temp_fv1;
            }
            temp_fv1 = temp_fa0 * spC0;
            temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0x1A8));
            if (temp_fv0 < temp_fv1) {
                *(f32 *)(arg0 + 0x1A8) = temp_fv1;
            } else {
                temp_fa0 = 0.0f;
                if (temp_fa0 < temp_fv0) {
                    temp_fv1 = temp_fa0;
                } else {
                    temp_fv1 = temp_fv0;
                }
                *(f32 *)(arg0 + 0x1A8) = temp_fv1;
            }
        } else {
            temp_fa0 = spBC * 0.75f;
            if (temp_fv0 < temp_fa0) {
                (*(f32 *)((u8 *)(arg0) + 0x1A4)) = temp_fa0;
            } else {
                if (temp_fv0 > 0.0f) {
                    temp_fv1 = 0.0f;
                } else {
                    temp_fv1 = temp_fv0;
                }
                (*(f32 *)((u8 *)(arg0) + 0x1A4)) = temp_fv1;
            }
            temp_fv1 = temp_fa0 * spC0;
            temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0x1A8));
            if (temp_fv0 < temp_fv1) {
                *(f32 *)(arg0 + 0x1A8) = temp_fv1;
            } else {
                temp_fa0 = 0.0f;
                if (temp_fa0 < temp_fv0) {
                    temp_fv1 = temp_fa0;
                } else {
                    temp_fv1 = temp_fv0;
                }
                *(f32 *)(arg0 + 0x1A8) = temp_fv1;
            }
        }
        temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0x1A4));
        (*(f32 *)((u8 *)(arg0) + 0x19C)) = temp_fv0;
        (*(f32 *)((u8 *)(arg0) + 0x1A0)) = (f32) (*(f32 *)((u8 *)(arg0) + 0x1A8));
        (*(f32 *)((u8 *)(var_t0) + 0x184)) = temp_fv0;
        (*(f32 *)((u8 *)(var_t0) + 0x188)) = (f32) (*(f32 *)((u8 *)(arg0) + 0x1A8));
        direction.x = 1.0f;
        sp88 = func_15047C00((*(f32 *)((u8 *)(var_t0) + 0x170)) * D_800A356C) * direction.x;
        temp_ft2 = func_15047D60((*(f32 *)((u8 *)(var_t0) + 0x170)) * D_800A3570) * direction.x;
        direction.x = sp88;
        direction.y = temp_ft2;
        sp88 = func_15047C00((*(f32 *)((u8 *)(var_t0) + 0x16C)) * D_800A3574) * direction.x;
        temp_ft2 = func_15047D60((*(f32 *)((u8 *)(var_t0) + 0x16C)) * D_800A3578) * direction.x;
        direction.x = sp88;
        temp_a1_2 = var_t0 + 0x148;
        temp_a2 = var_t0 + 0x130;
        direction.z = temp_ft2;
        target = (*(u8 **)((u8 *)(arg0) + 0x3D0));
        (*(f32 *)((u8 *)(arg0) + 0x2BC)) = (f32) ((*(f32 *)((u8 *)(arg0) + 0x2F8)) + sp88);
        (*(f32 *)((u8 *)(arg0) + 0x2C0)) = (f32) ((*(f32 *)((u8 *)(arg0) + 0x2FC)) + direction.y);
        (*(f32 *)((u8 *)(arg0) + 0x2C4)) = (f32) ((*(f32 *)((u8 *)(arg0) + 0x300)) + direction.z);
        (*(f32 *)((u8 *)(arg0) + 0x2A4)) = (f32) (*(f32 *)((u8 *)(target) + 0x14));
        (*(f32 *)((u8 *)(arg0) + 0x2A8)) = (f32) (*(f32 *)((u8 *)(target) + 0x18));
        (*(f32 *)((u8 *)(arg0) + 0x2AC)) = (f32) (*(f32 *)((u8 *)(target) + 0x1C));
        *(Camera22CVector *)temp_a1_2 = *(Camera22CVector *)(arg0 + 0x2BC);
        *(Camera22CVector *)(sp50 + 0) = *(Camera22CVector *)sp54;
        *(Camera22CVector *)temp_a2 = direction;
        func_15048F90(sp50, temp_a1_2, temp_a2);
        (*(f32 *)((u8 *)(((u8 *)D_800BE628 + ((*(u8 *)((u8 *)(arg0) + 0x23D)) * 0x180))) + 0x84)) = (f32) ((D_800A357C * spC4) + 1.0f);
        temp_v0_9 = (*(u8 *)((u8 *)(arg0) + 0x23D));
        func_1510B128((s32) temp_v0_9, (*(f32 *)((u8 *)(arg0) + 0x19C)), (*(f32 *)((u8 *)(arg0) + 0x1A0)), (*(f32 *)((u8 *)(((u8 *)D_800BE628 + (temp_v0_9 * 0x180))) + 0x84)), (71.0f * spC4) + 54.0f);
        var_v0 = 1;
    }
    return (s32) var_v0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15126378 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15126378.s")
void func_100111C8(u16);
void func_10010F30(s32, s32, s32, s32, s32);
void func_151CC290(s32);
extern u16 D_800894E0[][3];
extern f32 D_800A3580;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15127520 CURRENT (859) */
s32 func_15127520(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6) {
    u32 packed;
    u32 index;
    u32 previous;
    u8 *state;
    u16 *sounds;
    s32 changed;
    s32 flags;
    u16 sound;
    f32 amount;

    packed = *(u32 *)(arg0 + 0x1C);
    state = *(u8 **)(arg0 + 0x18);
    index = packed >> 31;
    previous = packed & 0xFFFFFF;
    sounds = D_800894E0[index];
    amount = *(f32 *)(state + 0x1A4) * D_800A3580;
    changed = 0;
    if (*arg6 == sounds[2]) {
        *arg6 = 0;
    }
    *(s16 *)(arg0 + 2) = (s32)*(f32 *)(*(u8 **)(state + 0x3D0) + 0x14);
    *(s16 *)(arg0 + 4) = (s32)*(f32 *)(*(u8 **)(state + 0x3D0) + 0x18);
    *(s16 *)(arg0 + 6) = (s32)*(f32 *)(*(u8 **)(state + 0x3D0) + 0x1C);
    if ((*(u8 **)(state + 0x3D4))[0x197] == 2) {
        packed = (u32)amount;
        if (previous != packed) {
            changed = 1;
            *(u32 *)(arg0 + 0x1C) = (index << 31) | packed;
        }
        if (changed != 0) {
            if (*arg6 != sounds[0]) {
                sound = *(u16 *)(arg0 + 0x24);
                if (sound != 0) {
                    func_100111C8(sound);
                }
                *(u16 *)(arg0 + 0x24) = 0;
                *(s32 *)(arg0 + 0x10) &= ~0x80;
                *arg6 = sounds[0];
            }
            flags = *(s32 *)(arg0 + 0x10);
        } else if (*arg6 == sounds[0]) {
            sound = *(u16 *)(arg0 + 0x24);
            if (sound != 0) {
                func_100111C8(sound);
            }
            *(u16 *)(arg0 + 0x24) = 0;
            *arg6 = sounds[1];
            func_10010F30(sounds[1], 0x4E20, 0x40, 0, 0);
            flags = *(s32 *)(arg0 + 0x10) & ~0x80;
            *(u32 *)(arg0 + 0x10) = flags;
        } else {
            flags = *(s32 *)(arg0 + 0x10);
            if (flags & 0x80) {
                func_151CC290((s32)state);
                func_10010F30(sounds[2], 0x4E20, 0x40, 0, 0);
                flags = *(s32 *)(arg0 + 0x10);
            }
        }
    } else {
        return 1;
    }
    *(s32 *)(arg0 + 0x10) = flags & ~0x80;
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15127520 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15127520.s")
void func_100111C8(u16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151277B0 CURRENT (1522) */
s32 func_151277B0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, u16 *arg6) {
    union { f32 value; u32 bits; } product;
    u32 previous;
    u32 current;
    s32 changed;
    u16 sound;
    u16 otherSound;
    u32 packed;
    u32 timer;
    u8 *state;
    u8 *owner;

    owner = *(u8 **)(arg0 + 0x18);
    packed = *(u32 *)(arg0 + 0x1C);
    state = *(u8 **)(owner + 0x3D4);
    changed = 0;
    previous = packed & 0xFFFFFF;
    timer = packed >> 24;
    product.value = *(f32 *)(state + 0x174) * *(f32 *)(state + 0x178);
    current = product.bits & 0xFFFFFF;
    if (*arg6 == 0x622) {
        *arg6 = 0;
    }
    *(s16 *)(arg0 + 2) = (s32)*(f32 *)(*(u8 **)(owner + 0x3D0) + 0x14);
    *(s16 *)(arg0 + 4) = (s32)*(f32 *)(*(u8 **)(owner + 0x3D0) + 0x18);
    *(s16 *)(arg0 + 6) = (s32)*(f32 *)(*(u8 **)(owner + 0x3D0) + 0x1C);
    if ((*(u8 **)(owner + 0x3D4))[0x197] == 2) {
        if (previous != current) {
            if (timer < 10U) {
                if ((u32)(previous - current) >= 101U) {
                    timer += D_800BE9E4;
                }
            } else {
                changed = 1;
            }
        } else {
            timer = 0;
        }
        *(u32 *)(arg0 + 0x1C) = (timer << 24) | current;
        if (changed != 0) {
            if (*arg6 != 0x61C) {
                sound = *(u16 *)(arg0 + 0x24);
                if (sound != 0) {
                    func_100111C8(sound);
                }
                *(u16 *)(arg0 + 0x24) = 0;
                *(s32 *)(arg0 + 0x10) &= ~0x80;
                *arg6 = 0x61C;
            }
        } else if (*arg6 == 0x61C) {
            otherSound = *(u16 *)(arg0 + 0x24);
            if (otherSound != 0) {
                func_100111C8(otherSound);
            }
            *(u16 *)(arg0 + 0x24) = 0;
            *arg6 = 0x61D;
            *(s32 *)(arg0 + 0x10) &= ~0x80;
        }
    } else {
        return 1;
    }
    if (*(u16 *)(arg0 + 0x24) == 0 && *arg6 == 0) {
        *(s32 *)(arg0 + 0x10) &= ~0x80;
    }
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151277B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151277B0.s")
void func_15048758(f32 *);
void func_15049688(void *, f32, void *, f32, f32, f32);
void func_150627D4(void *);
extern f32 D_800A3584;
extern f32 D_800A3588;
extern f32 D_800A358C;
extern f32 D_800A3590;
extern f32 D_800A3594;
extern f32 D_800A3598;
extern f32 D_800A359C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151279A0 CURRENT (2861) */
s32 func_151279A0(u8 *arg0, u16 *arg1) {
    s32 mode;
    Camera22CVector point;
    Camera22CVector origin;
    f32 scale;
    Camera22CVector direction;
    f32 horizontal;
    s32 buttons;
    f32 angle;
    Camera22CVector *destination;
    s32 state;
    u8 *target;

    target = *(u8 **)(arg0 + 0x31C);
    mode = target[0x78];
    scale = (f32)D_800BE9E4 * D_800A3584;
    if (mode == 0xC || mode == 0x1B) {
        *arg1 |= 0x10;
    }
    if ((mode == 0x23 || mode == 0x24 || mode == 0x16 || mode == 0x12 ||
         mode == 0x18 || mode == 0x41 || mode == 0xC || mode == 0x14 ||
         mode == 0x3F || mode == 0x1B || mode == 0x1F || mode == 0x29) &&
        (*arg1 & 0x10) && target[0x197] == 0) {
        target[0x197] = 2;
        *(Camera22CVector *)(target + 0x13C) = origin;
        *(f32 *)(target + 0x178) = 0.0f;
        *(f32 *)(target + 0x170) = 0.0f;
        *(f32 *)(target + 0x17C) = 0.0f;
        *(f32 *)(target + 0x180) = 0.0f;
        *(f32 *)(target + 0x174) = *(f32 *)(arg0 + 0x40) - 90.0f;
        *(f32 *)(target + 0x16C) = *(f32 *)(target + 0x174);
        func_150627D4(arg0);
    }
    state = target[0x197];
    if (state == 0) {
        return 0;
    }
    if (state == 2) {
        buttons = *arg1;
        point.x = *(f32 *)(arg0 + 0x14);
        angle = (*(f32 *)(arg0 + 0x40) - 90.0f) * D_800A3588;
        point.y = *(f32 *)(arg0 + 0x18) + (f32)*(s16 *)(target + 0x114) * 0.75f;
        point.z = *(f32 *)(arg0 + 0x1C);
        origin = point;
        point.x = func_15047D60(angle) * 100.0f + origin.x;
        point.z = func_15047C00(angle) * 100.0f + origin.z;
        origin.y += *(f32 *)(arg0 + 0x18) - *(f32 *)(arg0 + 0x30);
        if (!(buttons & 0x10) || mode == 0) {
            target[0x197] = 0;
            func_150627D4(arg0);
            return 0;
        }
        angle = D_800A358C;
        *(f32 *)(target + 0x174) -= (f32)((s8 *)arg1)[2] * angle;
        *(f32 *)(target + 0x178) += (f32)((s8 *)arg1)[3] * angle;
        destination = (Camera22CVector *)(target + 0x13C);
        func_15048758((f32 *)(target + 0x174));
        if (mode == 0x1F || mode == 0x29) {
            angle = *(f32 *)(target + 0x178);
            *(f32 *)(target + 0x178) = angle < -20.0f ? -20.0f : angle > 80.0f ? 80.0f : angle;
        } else {
            angle = *(f32 *)(target + 0x178);
            *(f32 *)(target + 0x178) = angle < -80.0f ? -80.0f : angle > 80.0f ? 80.0f : angle;
        }
        func_15049688(target + 0x16C, *(f32 *)(target + 0x174), target + 0x17C, 6.0f, 8.0f, scale);
        func_15049688(target + 0x170, *(f32 *)(target + 0x178), target + 0x180, 6.0f, 8.0f, scale);
        direction.x = 1.0f;
        horizontal = func_15047C00(*(f32 *)(target + 0x170) * D_800A3590) * direction.x;
        direction.y = func_15047D60(*(f32 *)(target + 0x170) * D_800A3594) * direction.x;
        direction.x = horizontal;
        horizontal = func_15047C00(*(f32 *)(target + 0x16C) * D_800A3598) * direction.x;
        direction.z = func_15047D60(*(f32 *)(target + 0x16C) * D_800A359C) * direction.x;
        direction.x = horizontal;
        point.x = origin.x + horizontal;
        point.y = origin.y + direction.y;
        mode = 1;
        point.z = origin.z + direction.z;
        *(Camera22CVector *)(target + 0x148) = point;
        *destination = origin;
        *(Camera22CVector *)(target + 0x130) = direction;
        return mode;
    }
    return mode;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151279A0 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_151279A0.s")

void func_150627D4(void *);
void func_1510B32C(s32, f32, f32, f32);
void func_151C9ED4(void *);
extern s32 D_800BE628;

void func_15127EB8(struct108 *arg0)
{
  struct127 *v0;
  struct127 *v1;
  u8 index;
  func_151239CC(arg0, 1);
  arg0->unk3D4->unk197 = 0;
  func_151C9ED4(arg0);
  arg0->unk19C = 0.0f;
  arg0->unk1A0 = 0.0f;
  arg0->unk1A4 = 0.0f;
  arg0->unk1A8 = 0.0f;
  func_1510B32C(arg0->unk23D, 0.0f, 0.0f, 1.0f);
  *((f32 *) ((D_800BE628 + (arg0->unk23D * 0x180)) + 0x84)) = 1.0f;
  func_150627D4(arg0->unk3D0);
  D_800DBFF4[arg0->unk23D] = 2;
  v1 = arg0->unk3D0;
  index = v1->unk65;
  if (index)
  {
    v0 = &((struct127 *)D_800CC2D0)[index - 1];
  }
  else
  {
    v0 = v1;
  }
  v0->pad2FC[0] &= ~(1 << arg0->unk23D);
  v0->unk74 &= ~(1 << arg0->unk23D);
  arg0->unk23C = 1;
}
extern void func_1512A390(void);

void func_15127FEC(void *arg0, void *arg1, void *arg2) {
    *(s16 *)((u8 *) arg0 + 0x7F4) = 1;
    *(f32 *)((u8 *) arg0 + 0x7F8) = *(f32 *)((u8 *) arg0 + 0x2A4);
    *(f32 *)((u8 *) arg0 + 0x7FC) = *(f32 *)((u8 *) arg0 + 0x2A8);
    *(f32 *)((u8 *) arg0 + 0x800) = *(f32 *)((u8 *) arg0 + 0x2AC);
    func_1512A390();
}
f32 func_15048720(f32, f32, f32);
void func_15123568(u8 *);
void func_15124C38(void *, s32);
void func_15125594(void *);
void func_151287E0(void *, void *, void *);

extern f32 D_800A35A0;
extern f32 D_800A35A4;
extern f32 D_800A35A8;
extern f32 D_800DC004;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_15128030 CURRENT (2548) */
s32 func_15128030(u8 *arg0) {
    s32 var_a1;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 temp_v0;
    u8 mode;
    u8 *temp_s1;
    void *temp_v0_2;

    temp_s1 = arg0 + 0x7F4;
    mode = arg0[0x23C];
    if (mode != 0) {
        (*(s16 *)((u8 *)(arg0) + 0x834)) = 0;
        (*(u16 *)((u8 *)(arg0) + 0x7F4)) = 0U;
        (*(f32 *)((u8 *)(arg0) + 0x820)) = (f32) D_800A35A0;
        return 0;
    } else {
        temp_v0 = *(u16 *)temp_s1;
        switch (temp_v0) {                              /* irregular */
        case 0:
            return 0;
        case 1:
            temp_v0_2 = (*(void **)((u8 *)(arg0) + 0x3D0));
            temp_fv1 = (*(f32 *)((u8 *)(arg0) + 0x2F8)) - (*(f32 *)((u8 *)(temp_v0_2) + 0x14));
            temp_fa0 = (*(f32 *)((u8 *)(arg0) + 0x300)) - (*(f32 *)((u8 *)(temp_v0_2) + 0x1C));
            (*(f32 *)((u8 *)(temp_s1) + 0x1C)) = sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0));
            (*(f32 *)((u8 *)(arg0) + 0x5E8)) = 0.0f;
            (*(f32 *)((u8 *)(arg0) + 0x660)) = 0.0f;
            (*(f32 *)((u8 *)(arg0) + 0x3A8)) = 0.0f;
            (*(f32 *)((u8 *)(arg0) + 0x65C)) = 0.0f;
            (*(f32 *)((u8 *)(arg0) + 0x83C)) = (f32) ((*(f32 *)((u8 *)(arg0) + 0x2FC)) - (*(f32 *)((u8 *)(arg0) + 0x35C)));
            func_15125594(arg0);
            (*(f32 *)((u8 *)(temp_s1) + 0x20)) = (f32) (*(f32 *)((u8 *)(arg0) + 0x37C));
            func_151287E0(arg0, temp_s1 + 0x34, temp_s1 + 0x38);
            (*(u16 *)((u8 *)(arg0) + 0x840)) = (u16) (*(u16 *)((u8 *)(temp_s1) + 0x40));
            (*(f32 *)((u8 *)(temp_s1) + 0x3C)) = 0.0f;
            *(u16 *)temp_s1 = 2U;
            /* fallthrough */
        case 2:
            mode = arg0[0x23C];
            temp_v0 = (s16) (*(u16 *)((u8 *)(arg0) + 0x840));
            var_a1 = temp_v0 == 0;
            if (mode != 0) {
                var_a1 = 1;
                (*(f32 *)((u8 *)(temp_s1) + 0x3C)) = 1.0f;
                (*(u16 *)((u8 *)(arg0) + 0x840)) = 0U;
            } else {
                (*(f32 *)((u8 *)(temp_s1) + 0x3C)) = (f32) (1.0f - ((f32) temp_v0 / (f32)(u32)*(u16 *)(temp_s1 + 0x40)));
            }
            func_15123568(arg0);
            (*(f32 *)((u8 *)(temp_s1) + 0x28)) = (f32) (*(f32 *)((u8 *)(arg0) + 0x374));
            (*(f32 *)((u8 *)(arg0) + 0x838)) = (f32) (*(f32 *)((u8 *)(arg0) + 0x348));
            (*(f32 *)((u8 *)(temp_s1) + 0x10)) = (f32) (*(f32 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0x14));
            func_15124C38(arg0, (s32) (temp_s1 + 0x14));
            temp_fv0 = (*(f32 *)((u8 *)(temp_s1) + 0x2C));
            (*(f32 *)((u8 *)(temp_s1) + 0x18)) = (f32) (*(f32 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x3D0))) + 0x1C));
            if (temp_fv0 < 0.0f) {
                do {
                    temp_fv0 += 360.0f;
                } while (temp_fv0 < 0.0f);
            }
            temp_v0_2 = (*(void **)((u8 *)(arg0) + 0x3D0));
            (*(f32 *)((u8 *)(arg0) + 0x2A4)) = (f32) (*(f32 *)((u8 *)(temp_v0_2) + 0x14));
            (*(f32 *)((u8 *)(arg0) + 0x2A8)) = (f32) (*(f32 *)((u8 *)(temp_v0_2) + 0x18));
            (*(f32 *)((u8 *)(arg0) + 0x390)) = temp_fv0;
            (*(f32 *)((u8 *)(arg0) + 0x2AC)) = (f32) (*(f32 *)((u8 *)(temp_v0_2) + 0x1C));
            if (temp_fv0 < -360.0f) {
                do {
                    (*(f32 *)((u8 *)(arg0) + 0x390)) = (f32) ((*(f32 *)((u8 *)(arg0) + 0x390)) + 360.0f);
                } while ((*(f32 *)((u8 *)(arg0) + 0x390)) < -360.0f);
            }
            temp_fv0 = (*(f32 *)((u8 *)(temp_s1) + 4));
            (*(f32 *)((u8 *)(arg0) + 0x2BC)) = (f32) (((*(f32 *)((u8 *)(temp_s1) + 0x3C)) * ((*(f32 *)((u8 *)(temp_s1) + 0x10)) - temp_fv0)) + temp_fv0);
            temp_fv1 = (*(f32 *)((u8 *)(temp_s1) + 8));
            (*(f32 *)((u8 *)(arg0) + 0x2C0)) = (f32) (((*(f32 *)((u8 *)(temp_s1) + 0x3C)) * ((*(f32 *)((u8 *)(temp_s1) + 0x14)) - temp_fv1)) + temp_fv1);
            temp_fa0 = (*(f32 *)((u8 *)(temp_s1) + 0xC));
            (*(f32 *)((u8 *)(arg0) + 0x2C4)) = (f32) (((*(f32 *)((u8 *)(temp_s1) + 0x3C)) * ((*(f32 *)((u8 *)(temp_s1) + 0x18)) - temp_fa0)) + temp_fa0);
            if ((*(s32 *)((u8 *)(arg0) + 0x2C)) != 0x40) {
                temp_fv0 = func_15048720((*(f32 *)((u8 *)(temp_s1) + 0x3C)), (*(f32 *)((u8 *)(temp_s1) + 0x20)), (*(f32 *)((u8 *)(temp_s1) + 0x2C)));
                (*(f32 *)((u8 *)(arg0) + 0x37C)) = temp_fv0;
                (*(f32 *)((u8 *)(arg0) + 0x39C)) = (f32) (temp_fv0 * D_800A35A4);
            }
            temp_fv1 = (*(f32 *)((u8 *)(temp_s1) + 0x1C));
            D_800DC000 = ((*(f32 *)((u8 *)(temp_s1) + 0x3C)) * ((*(f32 *)((u8 *)(temp_s1) + 0x28)) - temp_fv1)) + temp_fv1;
            temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0x83C));
            D_800DC004 = ((*(f32 *)((u8 *)(temp_s1) + 0x3C)) * ((*(f32 *)((u8 *)(arg0) + 0x838)) - temp_fv0)) + temp_fv0;
            (*(f32 *)((u8 *)(arg0) + 0x5E8)) = func_15048720((*(f32 *)((u8 *)(temp_s1) + 0x3C)), 0.0f, (*(f32 *)((u8 *)(temp_s1) + 0x34)));
            temp_fv0 = func_15048720((*(f32 *)((u8 *)(temp_s1) + 0x3C)), 0.0f, (*(f32 *)((u8 *)(temp_s1) + 0x38)));
            (*(f32 *)((u8 *)(arg0) + 0x3A8)) = temp_fv0;
            if (var_a1 != 0) {
                (*(s16 *)((u8 *)(arg0) + 0x834)) = 0;
                (*(u16 *)((u8 *)(arg0) + 0x7F4)) = 0U;
                (*(s32 *)((u8 *)(arg0) + 0x84)) = (s32) ((*(s32 *)((u8 *)(arg0) + 0x84)) | 8);
                (*(f32 *)((u8 *)(arg0) + 0x820)) = (f32) D_800A35A8;
                return (s32)*(u8 **)(arg0 + 0x3D0);
            }
            (*(u16 *)((u8 *)(arg0) + 0x840)) = (u16) ((u32) (s32) (s16) (*(u16 *)((u8 *)(arg0) + 0x840)) - (u32) D_800BE9E4);
            if ((s16) (*(u16 *)((u8 *)(arg0) + 0x840)) < 0) {
                (*(u16 *)((u8 *)(arg0) + 0x840)) = 0U;
            }
            return 1;
        default:
            return (s32) temp_v0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_15128030 */
#pragma GLOBAL_ASM("asm/nonmatchings/camera/camera_camera/func_15128030.s")
void func_15120158();
void func_15121C80(void *, f32);
void func_15122170();
void func_15122440();
void func_15129934();
void func_1512DEA4();

void func_151283B8(void *arg0) {
    switch (*(s32 *)((u8 *)arg0 + 0x2C)) {
        case 0x80:
            func_15122440(arg0);
            return;
        case 0x40:
            func_15129934(arg0);
            return;
        case 1:
            func_15122980(arg0);
            return;
        case 8:
            func_15121C80(arg0, 0.0f);
            return;
        case 2:
            func_151220D0(arg0);
            return;
        case 0x400:
            func_15122170(arg0);
            return;
        case 0x800:
            func_15122980(arg0);
            return;
        case 0x100:
            func_15120158(arg0);
            return;
        case 0x800000:
            func_1512DEA4(arg0);
            break;
        case 0x2000:
            return;
    }
}
void func_15128774(CameraCameraTargetState *, CameraCameraTarget *); /* extern */

void func_151284C4(CameraCameraTargetState *arg0) {
    u8 temp_v1;
    CameraCameraTarget *target;

    func_1512C490(arg0);
    target = arg0->field_3D0;
    temp_v1 = arg0->field_23C;
    arg0->field_2B0 = target->field_14;
    arg0->field_2B4 = target->field_18;
    arg0->field_2B8 = target->field_1C;
    if (temp_v1 != 0) {
        arg0->field_23C = temp_v1 - 1;
    }
    if ((arg0->field_84 & 8) && (arg0->field_5FE <= 0)) {
        arg0->field_5FE = 0x3C;
        func_15128774(arg0, arg0->field_3D0);
    }
}
s32 func_151253CC(u8 *);
s32 func_15128030(u8 *);
void func_1512A360(void *);
void func_151256BC(u8 *);
void func_151236D0(u8 *);
void func_1512E4B0(u8 *);
void func_151219D0(u8 *);
void func_1512D380(s32);
s32 func_15126378(u8 *);
typedef struct CameraCameraTriple {
    s32 x;
    s32 y;
    s32 z;
} CameraCameraTriple;

s32 func_15128540(u8 *arg0) {
    s32 temp_v0;

    if (func_151253CC(arg0) != 0) {
        return 1;
    }
    if (func_15128030(arg0) != 0) {
        return 0;
    }
    temp_v0 = *(s32 *)(arg0 + 0x2C);
    if (temp_v0 & 0x80000) {
        func_1512A360(arg0);
        *(CameraCameraTriple *)(arg0 + 0x2BC) =
            *(CameraCameraTriple *)(arg0 + 0x2A4);
        func_151256BC(arg0);
        func_151236D0(arg0);
        func_151284C4((CameraCameraTargetState *)arg0);
        return 1;
    }
    if (temp_v0 & 0x100000) {
        func_1512E4B0(arg0);
        func_151236D0(arg0);
        func_151284C4((CameraCameraTargetState *)arg0);
        return 1;
    }
    if (temp_v0 & 0x200000) {
        func_151219D0(arg0);
        func_151236D0(arg0);
        func_151284C4((CameraCameraTargetState *)arg0);
        return 1;
    }
    if (temp_v0 & 0x400000) {
        func_1512D380((s32)arg0);
        func_151236D0(arg0);
        func_151284C4((CameraCameraTargetState *)arg0);
        return 1;
    }
    if (func_15126378(arg0) != 0) {
        func_151284C4((CameraCameraTargetState *)arg0);
        return 1;
    }
    return 0;
}
void func_15128680(s32 arg0) {

}
void func_1512868C(u8 *arg0) {
    s32 var_v1;
    s32 temp_v0;
    u8 *temp_v1;

    for (var_v1 = 0; var_v1 < 0x15; var_v1++) {
        *(s16 *)(arg0 + 0x20C + var_v1 * 2) = 0;
    }
    *(s32 *)((u8 *)arg0 + 0x2C) = 1;
    *(s32 *)((u8 *)arg0 + 0xDC) = 0;
    *(s32 *)((u8 *)arg0 + 0x134) = 1;
    *(s32 *)((u8 *)arg0 + 0x84) = 0xE;
    *(s16 *)((u8 *)arg0 + 0x1B4) = 3;
    func_15124B18(arg0);
    temp_v0 = *(u8 *)((u8 *)arg0 + 0x23D);
    temp_v1 = (void *)((temp_v0 * 0x32C) + D_800CC2D0);
    *(void **)((u8 *)arg0 + 0x3D0) = temp_v1;
    *(s16 *)((u8 *)arg0 + 0x3CC) = (s16) temp_v0;
    *(s16 *)((u8 *)arg0 + 0x368) = (s16) temp_v0;
    *(void **)((u8 *)arg0 + 0x3D4) = *(void **)(temp_v1 + 0x31C);
    *(f32 *)((u8 *)arg0 + 0x190) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x198) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x18C) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x194) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x674) = 1.0f;
    *(s8 *)(*(u8 **)(arg0 + 0x3D4) + 0x198) = 0;
    *(s16 *)((u8 *)arg0 + 0x73C) = 0;
}
extern f32 D_800A35AC;

void func_15128774(CameraCameraTargetState *arg0, CameraCameraTarget *arg1) {
    u8 *camera = (u8 *)arg0;
    u8 *object = (u8 *)arg1;
    f32 coordinate;

    *(f32 *)(camera + 0x35C) = *(f32 *)(object + 0x180);
    coordinate = *(f32 *)(object + 0x14);
    *(f32 *)(camera + 0x2F8) = coordinate;
    *(f32 *)(camera + 0x304) = coordinate;
    coordinate = *(f32 *)(object + 0x18);
    *(f32 *)(camera + 0x2FC) = coordinate;
    *(f32 *)(camera + 0x308) = coordinate;
    coordinate = *(f32 *)(object + 0x1C);
    *(f32 *)(camera + 0x300) = coordinate;
    *(f32 *)(camera + 0x30C) = coordinate;
    *(f32 *)(camera + 0x37C) =
        *(f32 *)(*(u8 **)(camera + 0x3D0) + 0x40) - 180.0f;
    *(f32 *)(*(u8 **)(camera + 0x3D4) + 0x18C) = D_800A35AC;
    camera[0x23C] = 1;
}
