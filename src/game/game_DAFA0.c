#include "types.h"

/*
 * Reviewed source unit: src/game/game_DAFA0.c
 * Boundary evidence: docs/evidence/game_raw_exception_entry_family.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150ADAF0
 * - func_150AE280
 * - func_150AE36C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_DAFA0/func_150ADAF0.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AE280 CURRENT (5435) */
void func_150AE280(void) {
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AE280 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAFA0/func_150AE280.s")
s32 func_150AE35C(s32 arg0) {
    return 1;
}
typedef struct {
    s16 position[3];
    u16 flag;
    s16 s, t;
    u8 color[4];
} GameAE36CVertex;

void *func_10022EC0(void *, const void *, u32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_15142914(void *, f32, f32, f32, f32, f32, f32, f32, f32);
void func_151D5D60(void *, s16, s32, void **, u8 *);
extern f32 D_800DD1D8[], D_800DD1E8[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150AE36C CURRENT (280) */
void *func_150AE36C(u8 *arg0, s16 arg1) {
    GameAE36CVertex *vertices;
    void *result;
    f32 dx;
    f32 dz;
    f32 z;
    f32 y;
    f32 x;
    f32 scale;
    s32 offset;
    f32 transform[4][4];
    u8 created;

    func_151D5D60(arg0 + 0x100, arg1, 0x40, (void **)&vertices, &created);
    result = vertices;
    if (vertices != 0) {
        if (created != 0) {
            func_10022EC0(*(void **)(arg0 + arg1 * 4 + 0x100), arg0 + 0xC0, 0x40);
            func_10022EC0(*(u8 **)(arg0 + arg1 * 4 + 0x100) + 0x40, arg0 + 0xC0, 0x40);
        }
        offset = arg1 * 4;
    } else {
        return 0;
    }
    func_15142914(transform, (*(f32 **)(arg0 + 0x160))[6], (*(f32 **)(arg0 + 0x160))[7], (*(f32 **)(arg0 + 0x160))[8],
        (*(f32 **)(arg0 + 0x160))[9], (*(f32 **)(arg0 + 0x160))[10], (*(f32 **)(arg0 + 0x160))[14], (*(f32 **)(arg0 + 0x160))[15], (*(f32 **)(arg0 + 0x160))[16]);
    func_150A7960(transform, *(f32 *)(arg0 + 0x34),
        *(f32 *)(arg0 + 0x38), *(f32 *)(arg0 + 0x3C), &x, &y, &z);
    scale = *(f32 *)(arg0 + 0x2C);
    dx = *(f32 *)((u8 *)D_800DD1E8 + offset) * scale;
    dz = *(f32 *)((u8 *)D_800DD1D8 + offset) * scale;
    vertices[0].flag = 0;
    vertices[1].flag = 0;
    vertices[2].flag = 0;
    vertices[3].flag = 0;
    vertices[0].position[0] = vertices[3].position[0] = (s32)(x + dx);
    vertices[0].position[1] = vertices[1].position[1] = (s32)y;
    vertices[0].position[2] = vertices[3].position[2] = (s32)(z - dz);
    vertices[1].position[0] = vertices[2].position[0] = (s32)(x - dx);
    vertices[2].position[1] = vertices[3].position[1] = (s32)(*(f32 *)(arg0 + 0x30) + y);
    vertices[1].position[2] = vertices[2].position[2] = (s32)(z + dz);
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150AE36C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAFA0/func_150AE36C.s")
