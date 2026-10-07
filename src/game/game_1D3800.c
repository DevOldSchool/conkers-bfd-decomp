#include "types.h"

/*
 * Reviewed source unit: src/game/game_1D3800.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_pointer_singletons_continued.md
 *
 * TODO: Implement these source-unit functions:
 * - func_151A6350
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

typedef struct {
    s16 x, y, z;
    u16 flag;
    s16 s, t;
    u8 color[3], alpha;
} Game1D3800Vertex;
typedef struct {
    u8 pad0[0x2C];
    f32 scale, height, x, y, z;
    u8 pad40[0x80];
    Game1D3800Vertex template[4];
    Game1D3800Vertex *buffers[4];
    u8 pad110[4];
    f32 textureStart;
    u8 pad118[4];
    f32 textureLength;
    u8 pad120[6];
    u8 alpha;
} Game1D3800Owner;
void *func_10022EC0(void *, const void *, u32);
void func_151D5D60(void *, s16, s32, void **, u8 *);
extern f32 D_800DD1D8[], D_800DD1E8[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_151A6350 CURRENT (3944) */
Game1D3800Vertex *func_151A6350(Game1D3800Owner *owner, s32 arg1) {
    Game1D3800Vertex *vertices, *result;
    register f32 offsetZ, offsetX, scale, texture;
    u8 fresh;
    register s32 firstS, lastS;
    s32 tableOffset, edge;
    register Game1D3800Vertex *current, *next;
    u8 *slot;

    func_151D5D60(owner->buffers, ((s16 *)&arg1)[1], 0x40, (void **)&vertices, &fresh);
    result = vertices;
    if (vertices != 0) {
        if (fresh) {
            slot = (u8 *)owner + ((s16 *)&arg1)[1] * 4;
            func_10022EC0((*(Game1D3800Vertex **)(slot + 0x100)), owner->template, 0x40U);
            func_10022EC0((*(Game1D3800Vertex **)(slot + 0x100)) + 4, owner->template, 0x40U);
        }
        tableOffset = ((s16 *)&arg1)[1] * 4;
        edge = 0x7C0;
    } else {
        return 0;
    }
    offsetZ = *(f32 *)((u8 *)D_800DD1D8 + tableOffset);
    scale = owner->scale;
    texture = owner->textureStart;
    offsetZ *= scale;
    offsetX = *(f32 *)((u8 *)D_800DD1E8 + tableOffset) * scale;
    firstS = (s32)texture;
    lastS = (s32)(texture + owner->textureLength);
    vertices->x = (s16)(s32)(owner->x + offsetX);
    vertices->y = (s16)(s32)owner->y;
    vertices->z = (s16)(s32)(owner->z - offsetZ);
    vertices->s = firstS;
    vertices->t = edge;
    vertices->alpha = owner->alpha;
    vertices->flag = 0;
    current = vertices + 1;
    vertices = current;
    next = current + 1;
    current->x = (s16)(s32)(owner->x - offsetX);
    current->y = (s16)(s32)owner->y;
    current->t = 0;
    current->s = firstS;
    current->z = (s16)(s32)(owner->z + offsetZ);
    current->flag = 0;
    current->alpha = owner->alpha;
    vertices = next;
    next->x = (s16)(s32)(owner->x - offsetX);
    vertices->y = (s16)(s32)(owner->y + owner->height);
    vertices->z = (s16)(s32)(owner->z + offsetZ);
    vertices->s = lastS;
    vertices->t = 0;
    vertices->alpha = 0;
    vertices->flag = 0;
    current = vertices + 1;
    vertices = current;
    current->x = (s16)(s32)(owner->x + offsetX);
    current->y = (s16)(s32)(owner->y + owner->height);
    current->t = edge;
    current->alpha = 0;
    current->flag = 0;
    current->s = lastS;
    current->z = (s16)(s32)(owner->z - offsetZ);
    return result;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_151A6350 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_1D3800/func_151A6350.s")
