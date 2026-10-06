#include "types.h"

/*
 * Reviewed source unit: src/game/game_139410.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_view_command_cores.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1510BF60
 * - func_1510C4AC
 * - func_1510C8A8
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/game_139410/func_1510BF60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_139410/func_1510C4AC.s")
typedef struct { s16 x, y; } Game139410Point;
typedef struct {
    u8 pad0[8];
    s16 x, y;
    u8 padC[4];
} Game139410Vertex;
typedef struct {
    Game139410Point *primary, *secondary;
    u8 primaryCount, secondaryCount, primaryIndex, secondaryIndex;
    u8 disabled, padD;
    u16 phase, rate, amplitude;
} Game139410Record;
typedef struct {
    Game139410Vertex *primary, *secondary;
} Game139410Buffers;

extern Game139410Record *D_800D9E60[];
extern u8 D_800D9E64;
extern Game139410Buffers D_800B0E10;
extern s32 D_800BE9E4;
extern f32 D_800A2CC0;
f32 func_15047D60(f32);
f32 func_15047C00(f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1510C8A8 CURRENT (2898) */
void func_1510C8A8(void) {
    volatile s16 carryX;
    volatile s16 carryY;
    s32 offsetX, offsetY;
    Game139410Record **cursor;
    Game139410Record *record;
    Game139410Vertex *buffer, *vertex;
    s32 entry, index;
    s32 sourceOffset;
    u16 phase;
    f32 angle, cosine, sine, scale;
    f32 amplitude;

    cursor = D_800D9E60;
    entry = 0;
    if ((s32)D_800D9E64 > 0) {
        scale = D_800A2CC0;
        offsetY = carryY;
        offsetX = carryX;
        do {
            record = *cursor;
            if (record->disabled == 0) {
                if (record->primary != 0) {
                    phase = record->phase + record->rate * (u32)D_800BE9E4;
                    record->phase = phase;
                    buffer = D_800B0E10.primary + record->primaryIndex;
                    angle = (f32)(u32)phase * scale;
                    index = 0;
                    cosine = func_15047D60(angle);
                    sine = func_15047C00(angle);
                    vertex = buffer;
                    sourceOffset = 0;
                    amplitude = (f32)(u32)record->amplitude;
                    offsetX = (s16)(s32)(amplitude * cosine);
                    offsetY = (s16)(s32)(amplitude * sine);
                    if ((s32)record->primaryCount > 0) {
                        do {
                            index++;
                            vertex++;
                            vertex[-1].x = ((Game139410Point *)((u8 *)record->primary + sourceOffset))->x + offsetX;
                            vertex[-1].y = ((Game139410Point *)((u8 *)record->primary + sourceOffset))->y + offsetY;
                            sourceOffset += 4;
                        } while (index < (s32)record->primaryCount);
                    }
                }
                index = 0;
                if (record->secondary != 0) {
                    buffer = D_800B0E10.secondary + record->secondaryIndex;
                    if ((s32)record->secondaryCount > 0) {
                        vertex = buffer;
                        sourceOffset = 0;
                        do {
                            index++;
                            vertex++;
                            vertex[-1].x = ((Game139410Point *)((u8 *)record->secondary + sourceOffset))->x + offsetX;
                            vertex[-1].y = ((Game139410Point *)((u8 *)record->secondary + sourceOffset))->y + offsetY;
                            sourceOffset += 4;
                        } while (index < (s32)record->secondaryCount);
                    }
                }
            }
            entry++;
            cursor++;
        } while (entry < (s32)D_800D9E64);
        carryY = offsetY;
        carryX = offsetX;
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1510C8A8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_139410/func_1510C8A8.s")
