#include "types.h"

/*
 * Reviewed source unit: src/main/init_A420.c
 * Boundary evidence: docs/evidence/main_spatial_audio_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_8000A420
 * - func_8000A750
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
/* The raw alias consumes F12; the provider overwrites its extra float formal. */
f32 func_850487E0(f32);
s32 func_850AD960(s32, s32, s32, s32);
s32 func_850AD9A0(s32, s32, s32);
extern f32 D_8002C200;
extern f64 D_8002C208;
extern f32 D_8002C210;
extern f32 D_8002C214;
extern f64 D_8002C218;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000A420 CURRENT (230) */
s32 func_8000A420(s32 x, s32 unusedY, s32 z, f32 rotation,
                  s32 distanceX, s32 distanceY, s32 distanceZ,
                  s32 flaggedLimit, s32 otherLimit, s32 *panOut,
                  s32 *attenuationOut, s32 *distanceOut) {
    s16 value;
    s32 distance;
    f32 ratio;
    s32 rounded;
    s32 mode;
    s32 gain;

    mode = 0x80;
    if (flaggedLimit & 0x8000) {
        flaggedLimit &= 0x7FFF;
        distance = func_850AD960(distanceX, distanceZ, 0, 0);
    } else {
        distance = func_850AD9A0(distanceX, distanceY, distanceZ);
    }
    gain = 0x7FFF - ((s32)(((u32)otherLimit - (u32)distance) << 15) / (otherLimit - flaggedLimit));
    if (gain >= 0x191) {
        if (panOut != 0) {
            if (func_850AD960(x, z, 0, 0) >= 0x1F) {
                ratio = sqrtf((f32)(x * x + z * z));
                if (D_8002C200 < ratio) {
                    ratio = (f32)x / ratio;
                }
                rounded = (s32)((f64)func_850487E0(ratio) * D_8002C208);
                value = rounded;
                if (z > 0) {
                    if ((s16)rounded < 0) {
                        value = -0x80 - (s16)rounded;
                    } else {
                        value = 0x80 - (s16)rounded;
                    }
                }
                value += rotation * D_8002C210;
                value = (s8)value;
                if (value >= 0x60 || value < -0x60) {
                    value = 0;
                } else if (value >= 0x20) {
                    value = 0x5F - value;
                } else if (value < -0x20) {
                    value = -0x5F - value;
                } else {
                    mode = 0;
                    value += value;
                }
                *panOut = (value + 0x40) | mode;
            } else {
                *panOut = 0x40;
            }
        }
        if (0x7FFF - ((s32)(((u32)otherLimit - (u32)distance) << 15) / (otherLimit - flaggedLimit)) < 0) {
            gain = 0;
        }
        if (gain >= 0x8000) {
            gain = 0x7FFF;
        }
        *attenuationOut = gain;
    } else {
        *attenuationOut = 0;
    }
    if (distanceOut != 0) {
        *distanceOut = distance;
    }
    return distance;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000A420 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_A420/func_8000A420.s")
typedef struct SpatialPoint {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[2];
} SpatialPoint;

extern SpatialPoint **D_800D2104;
extern u8 *D_800D2108;
f32 func_850AD900(f32 *, f32 *);
f32 func_850AD930(f32 *);
void func_85049148(f32 *, f32, f32 *);
s32 func_8000A420(s32, s32, s32, f32, s32, s32, s32, s32, s32,
                  s32 *, s32 *, s32 *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000A750 CURRENT (28265) */
s32 func_8000A750(s32 index, s32 panX, s32 panY, s32 panZ, f32 rotation,
                  s32 distanceX, s32 distanceY, s32 distanceZ,
                  s32 nearLimit, s32 farLimit, s32 *panOut,
                  s32 *attenuationOut, s32 *distanceOut) {
    s32 leftDistance;
    s32 rightDistance;
    s32 outside;
    s16 selectedX;
    s16 selectedY;
    s16 selectedZ;
    f32 direction[3];
    f32 relative[3];
    f32 length;
    f32 lengthSquared;
    f32 dot;
    SpatialPoint **slot;
    SpatialPoint *base;
    SpatialPoint *point;
    s32 closest;
    s32 bestDistance;
    s32 previousDistance;
    s32 currentDistance;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 segment;
    s32 i;
    s32 count;

    outside = 0;
    count = D_800D2108[index];
    previousDistance = 0x7FFFFFFF;
    closest = -2;
    bestDistance = 0x7FFFFFFF;
    if (count == 0) {
        return 0;
    }
    slot = &D_800D2104[index];
    base = *slot;
    point = base;
    for (i = 0; i < count; i++, point++) {
        dx = distanceX - point->x;
        dy = distanceY - point->y;
        dz = distanceZ - point->z;
        currentDistance = dx * dx + dy * dy + dz * dz;
        if (currentDistance < bestDistance) {
            closest = i;
            leftDistance = previousDistance;
            bestDistance = dx * dx + dy * dy + dz * dz;
            previousDistance = currentDistance;
            continue;
        }
        if (i == closest + 1) {
            rightDistance = dx * dx + dy * dy + dz * dz;
        }
        previousDistance = currentDistance;
    }
    segment = closest;
    point = base + closest;
    selectedX = point->x;
    selectedY = point->y;
    selectedZ = point->z;
    if (count >= 2 && bestDistance >= 0x6D61) {
        if (closest >= count - 1 || leftDistance < rightDistance) {
            segment--;
            point--;
        }
        direction[0] = (f32)(point[1].x - point->x);
        direction[1] = (f32)((*slot)[segment + 1].y - (*slot)[segment].y);
        direction[2] = (f32)((*slot)[segment + 1].z - (*slot)[segment].z);
        relative[0] = (f32)(distanceX - (*slot)[segment].x);
        relative[1] = (f32)(distanceY - (*slot)[segment].y);
        relative[2] = (f32)(distanceZ - (*slot)[segment].z);
        dot = func_850AD900(direction, relative);
        if (dot < 0.0f) {
            outside = 1;
        } else {
            length = func_850AD930(direction);
            lengthSquared = length * length;
            if (lengthSquared < dot) {
                outside = 1;
            }
        }
        if (outside != 0) {
            func_850AD900(direction, relative);
            if (leftDistance < rightDistance) {
                segment++;
            } else {
                segment--;
            }
            slot = &D_800D2104[index];
            direction[0] = (f32)((*slot)[segment + 1].x - (*slot)[segment].x);
            direction[1] = (f32)((*slot)[segment + 1].y - (*slot)[segment].y);
            direction[2] = (f32)((*slot)[segment + 1].z - (*slot)[segment].z);
            relative[0] = (f32)(distanceX - (*slot)[segment].x);
            relative[1] = (f32)(distanceY - (*slot)[segment].y);
            relative[2] = (f32)(distanceZ - (*slot)[segment].z);
            dot = func_850AD900(direction, relative);
            length = func_850AD930(direction);
            lengthSquared = length * length;
        }
        if (lengthSquared != 0.0f) {
            if (dot < lengthSquared) {
                func_85049148(direction, dot / lengthSquared, direction);
            }
            point = D_800D2104[index] + segment;
            selectedX = (s16)(s32)((f32)point->x + direction[0]);
            selectedY = (s16)(s32)((f32)point->y + direction[1]);
            selectedZ = (s16)(s32)((f32)point->z + direction[2]);
        }
    }
    return func_8000A420(selectedX - panX, selectedY - panY, selectedZ - panZ,
                         rotation, selectedX - distanceX, selectedY - distanceY,
                         selectedZ - distanceZ, nearLimit, farLimit,
                         panOut, attenuationOut, distanceOut);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000A750 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_A420/func_8000A750.s")

s32 func_8000B060(f32 x, f32 y, s32 offset) {
    s16 value;
    s16 mode;
    f32 ratio;
    s32 rounded;

    ratio = sqrtf(x * x + y * y);
    if (D_8002C214 < ratio) {
        ratio = x / ratio;
    }
    mode = 0x80;
    rounded = (s32)((f64)func_850487E0(ratio) * D_8002C218);
    value = rounded;
    if (y > 0.0f) {
        if ((s16)rounded < 0) {
            value = -0x80 - (s16)rounded;
        } else {
            value = 0x80 - (s16)rounded;
        }
    }
    value += offset;
    value = (s8)value;
    if (value >= 0x60 || value < -0x60) {
        value = 0;
    } else if (value >= 0x20) {
        value = 0x5F - value;
    } else if (value < -0x20) {
        value = -0x5F - value;
    } else {
        mode = 0;
        value += value;
    }
    return (value + 0x40) | mode;
}
