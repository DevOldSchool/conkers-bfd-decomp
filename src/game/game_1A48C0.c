#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_1A48C0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_compact_display_resource_pairs.md
 *
 * TODO: Implement these source-unit functions:
 * - func_15177410
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A48C0/func_15177410.s")

typedef struct Game1A48C0Vertex {
    s16 x, y, z;
    u8 pad06[0xA];
} Game1A48C0Vertex;

typedef struct Game1A48C0Mesh {
    f32 position[3];
    u8 pad0C[4];
    s16 x, y, z;
    u16 count;
    u8 pad18[8];
    Game1A48C0Vertex *buffers[2];
    Game1A48C0Vertex *source;
    f32 scale[3];
    u8 pad38[0x37];
    u8 flags;
} Game1A48C0Mesh;

typedef struct Game1A48C0Entry {
    u8 id;
    u8 flags;
    u8 mode;
    u8 pad03;
    u8 data04[0x14];
    u8 data18[8];
    s32 unk20;
    s32 unk24;
    s32 unk28;
} Game1A48C0Entry;

void func_150A6FA0(Game1A48C0Vertex *, u16, void *, s32, s32, Game1A48C0Vertex *);
void func_150A70C0(Game1A48C0Vertex *, u16, void *, s32, Game1A48C0Vertex *);
void func_150A71C8(Game1A48C0Vertex *, u16, void *, void *, s32, Game1A48C0Vertex *);
void func_150A7360(Game1A48C0Vertex *, u16, void *, void *, s32, s32, Game1A48C0Vertex *);
void func_150A751C(Game1A48C0Vertex *, u16, void *, s32, s32, s32, Game1A48C0Vertex *);
void func_1511490C(void *, void *);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
extern u8 D_800BE9C0;
extern Game1A48C0Entry *D_800DD410[];
extern u8 D_800DD418;

void func_15177A94(void) {
    Game1A48C0Entry *entry;
    Game1A48C0Mesh *mesh;
    s32 i;
    s32 j;
    f32 matrix[4][4];
    f32 x;
    f32 y;
    f32 z;
    Game1A48C0Vertex *vertices;

    for (i = 0; i < D_800DD418; i++) {
        entry = D_800DD410[i];
        mesh = func_151149AC(entry->id);
        if (!(mesh->flags & 0xF)) {
            continue;
        }
        if (entry->mode == 0) {
            vertices = mesh->source;
        } else {
            vertices = mesh->buffers[D_800BE9C0];
        }
        if ((entry->flags & 3) == 1) {
            if ((entry->flags & 4) == 4) {
                func_150A7360(mesh->buffers[D_800BE9C0], mesh->count, entry->data04, entry->data18, entry->unk24, entry->unk20, vertices);
            } else {
                func_150A71C8(mesh->buffers[D_800BE9C0], mesh->count, entry->data04, entry->data18, entry->unk24, vertices);
            }
        } else if ((entry->flags & 3) == 0) {
            if ((entry->flags & 4) == 4) {
                func_150A6FA0(mesh->buffers[D_800BE9C0], mesh->count, entry->data04, entry->unk24, entry->unk20, vertices);
            } else {
                func_150A70C0(mesh->buffers[D_800BE9C0], mesh->count, entry->data04, entry->unk24, vertices);
            }
        } else if ((entry->flags & 3) == 2) {
            if ((entry->flags & 4) == 4) {
                func_150A751C(mesh->buffers[D_800BE9C0], mesh->count, entry->data04, entry->unk28, entry->unk24, entry->unk20, vertices);
            }
        }
    }
    for (i = 0; i < D_800DD418; i++) {
        entry = D_800DD410[i];
        mesh = func_151149AC(entry->id);
        if (mesh->flags & 0xF) {
            if (entry->mode == 0) {
                mesh = func_151149AC(entry->id);
                if (mesh->position[0] == 0.0f && mesh->position[1] == 0.0f && mesh->position[2] == 0.0f &&
                    mesh->scale[0] == 1.0f && mesh->scale[1] == 1.0f && mesh->scale[2] == 1.0f) {
                    for (j = 0; j < mesh->count; j++) {
                        mesh->buffers[D_800BE9C0][j].x = mesh->source[j].x + mesh->x;
                        mesh->buffers[D_800BE9C0][j].y += mesh->y;
                        mesh->buffers[D_800BE9C0][j].z = mesh->source[j].z + mesh->z;
                    }
                } else {
                    func_1511490C(matrix, mesh);
                    for (j = 0; j < mesh->count; j++) {
                        func_150A7960(matrix, mesh->source[j].x, mesh->buffers[D_800BE9C0][j].y, mesh->source[j].z, &x, &y, &z);
                        mesh->buffers[D_800BE9C0][j].x = x;
                        mesh->buffers[D_800BE9C0][j].y = y;
                        mesh->buffers[D_800BE9C0][j].z = z;
                    }
                }
            }
        }
    }
}
