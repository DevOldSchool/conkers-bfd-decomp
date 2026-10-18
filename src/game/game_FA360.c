#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_FA360.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_selected_segments_extended.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150CCEB0
 * - func_150CD17C
 * - func_150CD59C
 * - func_150CD7F8
 * - func_150CDB6C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_FA360/func_150CCEB0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_FA360/func_150CD17C.s")
void *func_10022EC0(void *, const void *, u32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_150A8050(void *, f32, f32, f32);
void func_151D5D60(void *, s16, s32, void **, u8 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CD59C CURRENT (2665) */
void *func_150CD59C(u8 *arg0, s32 arg1) {
    void *vertices;
    void *base;
    f32 matrix[16];
    f32 corners[4][3];
    u8 fresh;
    u8 *buffers;
    u8 *template;
    f32 *point;
    s32 i;
    s32 next_i;

    arg1 = (s16)arg1;
    func_151D5D60(arg0 + 0x100, (s16)arg1, 0x40, &vertices, &fresh);
    base = vertices;
    if (vertices != 0) {
        if (fresh != 0) {
            buffers = arg0 + arg1 * 4;
            template = arg0 + 0xC0;
            func_10022EC0(*(void **)(buffers + 0x100), template, 0x40U);
            func_10022EC0(*(u8 **)(buffers + 0x100) + 0x40, template, 0x40U);
        }
    } else {
        return 0;
    }
    corners[0][0] = *(f32 *)(arg0 + 0x2C);
    corners[0][2] = 0.0f;
    corners[0][1] = *(f32 *)(arg0 + 0x30);
    corners[1][0] = -*(f32 *)(arg0 + 0x2C);
    corners[1][2] = 0.0f;
    corners[1][1] = *(f32 *)(arg0 + 0x30);
    corners[2][0] = -*(f32 *)(arg0 + 0x2C);
    corners[2][2] = 0.0f;
    corners[2][1] = -*(f32 *)(arg0 + 0x30);
    corners[3][0] = *(f32 *)(arg0 + 0x2C);
    corners[3][2] = 0.0f;
    corners[3][1] = -*(f32 *)(arg0 + 0x30);
    func_150A8050(matrix, *(f32 *)(arg0 + 0x40),
                 *(f32 *)(arg0 + 0x44), *(f32 *)(arg0 + 0x48));
    matrix[12] = *(f32 *)(arg0 + 0x34);
    matrix[13] = *(f32 *)(arg0 + 0x38);
    matrix[14] = *(f32 *)(arg0 + 0x3C);
    if (*(f32 *)(arg0 + 0x114) < 0.0f) {
        matrix[12] += *(f32 *)(arg0 + 0x4C);
        matrix[13] += *(f32 *)(arg0 + 0x50);
        matrix[14] += *(f32 *)(arg0 + 0x54);
    }
    i = 0;
    do {
        point = corners[i];
        func_150A7960(matrix, point[0], point[1], 0.0f,
                     &point[0], &point[1], &point[2]);
        *(s16 *)vertices = (s32)point[0];
        next_i = (i + 1) & 0xFF;
        *(s16 *)((u8 *)vertices + 2) = (s32)point[1];
        *(s16 *)((u8 *)vertices + 4) = (s32)point[2];
        *(s16 *)((u8 *)vertices + 6) = 0;
        vertices = (u8 *)vertices + 0x10;
        i = next_i;
    } while (i < 4);
    return base;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CD59C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FA360/func_150CD59C.s")
typedef struct {
    s32 countBase, countRange;
    Vec3f position;
    s16 angleBase, angleRange, pitchBase, pitchRange;
    f32 speedBase, speedRange, field24;
    f32 scaleBase, scaleRange;
    s8 colorIndex;
    u8 pad31;
    s16 lifeBase, lifeRange;
    u8 pad36[2];
    f32 field38, field3C, field40, field44, field48;
} GameFA360Particle;
typedef struct { f32 values[5]; } GameFA360Angles;

f32 func_150ADA68(void);
void func_1514373C(f32, f32, f32 *, f32 *);
void func_15152874(GameFA360Particle *, u8, s32);
f32 fabsf(f32);
#pragma intrinsic(fabsf)
extern s32 D_80082FA4;
extern GameFA360Angles D_80088874;
extern u8 *D_800DBFF0;
extern f32 D_800BE9A4;
extern f32 D_800A0754, D_800A0758, D_800A075C;
extern f64 D_800A0760, D_800A0768;
extern f32 D_800A0770, D_800A0774, D_800A0778, D_800A077C, D_800A0780;
extern f32 D_800A0784, D_800A0788, D_800A078C, D_800A0790;
extern f32 D_800A0794, D_800A0798, D_800A079C, D_800A07A0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CD7F8 CURRENT (1565) */
void func_150CD7F8(u8 *arg0) {
    f32 random;
    GameFA360Particle particle;
    GameFA360Angles angles;
    f32 angle;
    f32 yaw;
    f64 radiusBase;
    f64 radiusRange;
    s32 index;
    f32 *pending;

    pending = (f32 *)(arg0 + 0x28);
    *pending += D_800A0754 * D_800BE9A4 * *(f32 *)(arg0 + 0x2C);
    if (*pending > 1.0f) {
        particle.pitchBase = -23;
        particle.pitchRange = 6;
        particle.colorIndex = 0;
        particle.field24 = D_800A0758;
        particle.field48 = D_800A075C;
        radiusBase = D_800A0760;
        radiusRange = D_800A0768;
        do {
            angles = D_80088874;
            index = (func_150ADA20() % 5U) & 0xFF;
            angle = func_150ADA68() * D_800A0770 + angles.values[index];
            yaw = *(f32 *)(D_800DBFF0 + D_80082FA4 * 0x9A0 + 0x380) - 180.0f;
            if (yaw > 360.0f) {
                do { yaw -= 360.0f; } while (yaw > 360.0f);
            }
            if (yaw < 0.0f) {
                do { yaw += 360.0f; } while (yaw < 0.0f);
            }
            yaw *= D_800A0774;
            if (fabsf(angle - yaw) < D_800A0778) {
                random = func_150ADA68();
                particle.position.y = D_800A077C * random + D_800A0780 + 500.0f;
                func_1514373C(angle, (f32)((f64)random * radiusRange + radiusBase),
                              &particle.position.x, &particle.position.z);
                particle.countBase = 15;
                particle.countRange = 20;
                particle.angleRange = 12;
                particle.lifeBase = 0x226;
                particle.lifeRange = 0;
                particle.field3C = 15.0f;
                particle.field38 = 15.0f;
                particle.field44 = D_800A0784;
                particle.field40 = D_800A0784;
                particle.angleBase = (s32)((angle + D_800A0788 - D_800A078C) * D_800A0790);
                particle.speedBase = D_800A0794;
                particle.speedRange = D_800A0798;
                particle.scaleBase = D_800A079C;
                particle.scaleRange = D_800A07A0;
                func_15152874(&particle, arg0[0xC], arg0[1]);
            }
            *pending -= 1.0f;
        } while (*pending > 1.0f);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CD7F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FA360/func_150CD7F8.s")

extern s32 D_80088870;
extern f32 D_800A07A4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150CDB6C CURRENT (110) */
void func_150CDB6C(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 0x100) && (D_80088870 != 0)) {
        *(f32 *)((u8 *)(D_80088870 + 0x28) + 4) = (f32) ((f32) arg0 * D_800A07A4);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150CDB6C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_FA360/func_150CDB6C.s")
