#include "types.h"
#include "game_functions.h"

/*
 * Reviewed source unit: src/game/game_111670.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_state_resource_helpers.md
 *
 * TODO: Implement these source-unit functions:
 * - func_150E42F8
 * - func_150E4550
 * - func_150E4928
 * - func_150E5810
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_15047D60(f32);
f32 func_15047C00(f32);
extern s16 D_800D99F0[];
extern void *D_800DBFF0;

void func_150E41C0(void) {
    s32 x;
    s32 y;
    s32 z;
    f32 zero = 0.0f;
    f32 horizontal;
    f32 depth;
    f32 trig;
    f32 cosine;
    f32 angle;

    x = (s32)*(f32 *)((u8 *)D_800DBFF0 + 0x2F8);
    y = (s32)*(f32 *)((u8 *)D_800DBFF0 + 0x2FC);
    z = (s32)*(f32 *)((u8 *)D_800DBFF0 + 0x300);
    angle = *(f32 *)((u8 *)D_800DBFF0 + 0x398);
    trig = func_15047D60(angle);
    cosine = func_15047C00(angle);
    horizontal = 500.0f * trig;
    depth = -500.0f * cosine;
    angle = *(f32 *)((u8 *)D_800DBFF0 + 0x3A0);
    trig = func_15047D60(angle);
    cosine = func_15047C00(angle);
    x = (s32)((f32)x + (zero + (depth * trig)));
    z = (s32)((f32)z + ((depth * cosine) - zero));
    y = (s32)((f32)y + horizontal);
    D_800D99F0[0] = x;
    D_800D99F0[2] = z;
    D_800D99F0[1] = y;
}
/* Call context: func_1510F8CC: matched US definition in src/game/game_13BB20.c */
s32 func_1510F8CC(s32);

void func_150E4550(f32, f32, f32, s32, s32, s32, s32); /* extern */
s32 func_1510F8D8(s32, s32, s32, s32 *);        /* extern */
extern f32 D_800A1060;
extern s32 D_800DBE3C;
extern s32 D_800DBE4C;
extern s32 *D_800DBE5C;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E42F8 CURRENT (80) */
void func_150E42F8(s32 arg0) {
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_a2;
    s32 sp70;
    s32 temp_v0_2;
    s32 sp68;
    s32 temp_lo;
    s32 var_s3;
    f32 temp_fs0;
    s32 sp58;

    sp58 = 0;
    var_s3 = 0;
    sp70 = (s32) D_800D99F0[0];
    sp68 = (s32) D_800D99F0[2];
    if (arg0 > 0) {
        temp_fs0 = D_800A1060;
        do {
            temp_s0 = ((s32)func_150ADA20() % 500) + sp70;
            temp_a2 = ((s32)func_150ADA20() % 500) + sp68;
            temp_v0 = func_1510F8D8(temp_s0, 0x2710, temp_a2, &sp58);
            if ((temp_fs0 != (f32) temp_v0) && (sp58 != 0)) {
                temp_lo = (s32) (sp58 - D_800DBE3C) / 12;
                if ((temp_lo >= 0) && (temp_lo < D_800DBE4C)) {
                    temp_v0_2 = func_1510F8CC(D_800DBE5C[temp_lo]);
                    if (temp_v0_2 != 0) {
                        func_150E4550((f32) temp_s0, (f32) temp_v0, (f32) temp_a2, 0, temp_v0_2, sp58, 0xFF);
                    }
                }
            }
            var_s3 += 1;
        } while (var_s3 != arg0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E42F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E42F8.s")
void func_150E4514(s32 arg0) {
    func_150E41C0();
    func_150E42F8(arg0 / 30);
}
typedef struct {
    u16 object, particle;
    u8 chance, secondary, minimum, range;
} GameE4550Material;

typedef struct {
    u8 pad00[0x84];
    u16 width, height;
    u8 pad88[4];
    s16 x, y, z, scaleX, scaleY;
    u8 pad96[2];
    s16 flags;
    u8 pad9A[6];
    u8 kind, padA1, type, padA3, alpha, padA5[3];
} GameE4550Packet;

void func_100226F0(void *, s32);
s32 func_151EF610(void);
void func_1516865C(void *, s32, s32, s32, s32);
void func_151C329C(f32 *, u8, s32);
void func_150E4E04(f32, f32, f32, s32, s32, s32, s32);
void func_15171D4C(f32, f32, f32, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32, s32);
void func_15171F04(f32, f32, f32, s32, s16, u16, u8, s32, s32, s32, s32, u8, s32);
extern GameE4550Material D_800A1070[];
extern u16 D_800A1110[][2];
extern f32 D_800A111C[];
extern u8 D_800D9963[];

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E4550 CURRENT (1457) */
void func_150E4550(f32 arg0, f32 arg1, f32 arg2, s32 arg3,
                   s32 arg4, s32 arg5, s32 arg6) {
    s32 count;
    s32 lifetime;
    s32 special;
    s32 type;
    GameE4550Packet packet;
    f32 position[3];
    GameE4550Material *entry;
    s32 index;

    special = 0;
    lifetime = 120;
    if (arg4 & 0x8000) {
        arg4 ^= 0x8000;
        special = 0x8000;
    }
    entry = &D_800A1070[arg4];
    if (entry->particle != 0) {
        count = func_151EF610() % entry->range + entry->minimum + 1;
        if (arg3 != 1) lifetime = 30;
        type = entry->particle;
        count = (s32)(D_800A111C[arg3] * (f32)count);
        if (type == 0x13) {
            func_15171D4C(arg0, arg1, arg2, 30, 0, 0x13, 0.0f,
                          0, count, 0xF, 0x55, 0, 0xFF, 0);
        } else if (arg5 != 0) {
            func_15171F04(arg0, arg1, arg2, arg5, (s16)lifetime,
                          0xB5AD, (u8)type, count, 0, 0, 0, 0xFF, 0);
        } else {
            func_15171D4C(arg0, arg1, arg2, (s16)lifetime, 0xB5AD,
                          type, 0.0f, 0, count, 0, 0, 0, 0xFF, 0);
        }
    }
    type = entry->secondary;
    if (type != 0) {
        func_150E4E04(arg0, arg1, arg2, type | special, arg3, arg5, arg6);
    }
    if (arg3 != 0 && func_151EF610() % 100 < entry->chance) {
        position[0] = arg0;
        position[2] = arg2;
        position[1] = arg1 + 20.0f;
        func_151C329C(position, 0xFF, 1);
        if (arg6 != 0xFF) D_800D9963[arg6 * 0x1C] = 100;
    } else if (arg6 != 0xFF) D_800D9963[arg6 * 0x1C] = 0;
    if (entry->object != 0) {
        index = arg3 * 4;
        func_100226F0(&packet, 0xA8);
        packet.x = (s32)arg0;
        packet.type = 0xD;
        packet.y = (s32)arg1;
        packet.kind = entry->object;
        packet.z = (s32)arg2;
        packet.flags = 0x2A00;
        packet.scaleX = 1;
        packet.scaleY = 1;
        packet.alpha = 0xFF;
        packet.width = *(u16 *)((u8 *)D_800A1110 + index);
        packet.height = *(u16 *)((u8 *)D_800A1110 + index + 2);
        func_1516865C(&packet, 0xB4, 0xB4, 0xB4, 0xFF);
        func_15168800(&packet, 0xFF, 0);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E4550 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4550.s")
typedef struct GameE4928State {
    u8 pad00[0x10];
    s16 x;
    u8 pad12[2];
    s16 z;
    u8 pad16[0xA];
    u8 *buffers[2];
    u8 pad28[0x18];
    s32 material;
    s32 *materials;
    u8 pad48[8];
    u16 radius;
    u8 pad52[6];
    u16 firstSurface;
} GameE4928State;

typedef struct GameE4928Vertex {
    s16 x, y, z;
    u8 other[10];
} GameE4928Vertex;

s32 func_150A43E0(s32, s32, s32, void *);
void func_150A44F0(s32, void *, s32);
void func_150A7960(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_1510F800(s32);
s32 func_151EF610(void);
void func_1511490C(void *, void *);
extern f32 D_800A1128;
extern u8 D_800BE9C0;
extern u8 D_800D3300[];
extern s32 D_800DBEF0, D_800DBEF4;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E4928 CURRENT (3705) */
void func_150E4928(GameE4928State *arg0) {
    s16 selectedIndex;
    s32 attempts;
    volatile s32 queryState;
    s32 bestHeight;
    GameE4928Vertex *vertices[3];
    u32 *selected;
    s32 x;
    s32 hits;
    s32 z;
    u32 scan;
    volatile s32 material;
    s32 recordHeight;
    GameE4928Vertex transformed[3];
    f32 outX, outY, outZ;
    f32 matrix[16];
    GameE4928Vertex *output;
    GameE4928Vertex **vertex;
    f32 height;

    height = D_800A1128;
    hits = (s32)((u32)arg0 - (u32)D_800DBEF4) / 160;
    attempts = 5;
    if (hits < D_800DBEF0 && hits >= 0) {
        selectedIndex = hits;
        queryState = 0;
        func_1510F800(2);
        func_150A44F0(1, &selectedIndex, 0);
        do {
            x = arg0->x;
            z = arg0->z;
            if (arg0->radius != 0) {
                hits = func_151EF610();
                bestHeight = arg0->radius;
                x = (hits % bestHeight) * 2 + x - bestHeight;
                hits = func_151EF610();
                bestHeight = arg0->radius;
                z = (hits % bestHeight) * 2 + z - bestHeight;
            }
            hits = func_150A43E0(x, z, 1, &selectedIndex);
            if (hits != 0) {
                bestHeight = -0x800000;
                hits--;
                attempts = 0;
                if (hits + 1 != 0) {
                    scan = hits * 0x10 + (u32)D_800D3300;
                    do {
                        recordHeight = *(s32 *)scan;
                        if (bestHeight < recordHeight) {
                            bestHeight = recordHeight;
                            selected = *(u32 **)(scan + 4);
                            height = (f32)bestHeight * 0.00390625f;
                        }
                        scan -= 0x10;
                        recordHeight = hits;
                        hits--;
                    } while (recordHeight != 0);
                }
                hits = 1;
            } else {
                attempts--;
            }
        } while (attempts != 0);
        if (hits != 0) {
            if (arg0->materials != NULL) {
                material = *(s32 *)((u32)arg0->materials +
                    ((s32)((u32)selected - (u32)D_800DBE3C) / 12) * 4 -
                    arg0->firstSurface * 4);
            } else {
                material = arg0->material;
            }
            func_1511490C(matrix, arg0);
            if (selected != NULL) {
                vertex = vertices;
                output = transformed;
                scan = (u32)(transformed + 3);
                vertices[0] = (GameE4928Vertex *)(selected[0] + (u32)arg0->buffers[D_800BE9C0]);
                vertices[1] = (GameE4928Vertex *)(selected[1] + (u32)arg0->buffers[D_800BE9C0]);
                vertices[2] = (GameE4928Vertex *)(selected[2] + (u32)arg0->buffers[D_800BE9C0]);
                do {
                    func_150A7960(matrix, (f32)(*vertex)->x, (f32)(*vertex)->y,
                                  (f32)(*vertex)->z, &outX, &outY, &outZ);
                    vertex++;
                    output->x = (s32)outX;
                    output->y = (s32)outY;
                    vertex[-1] = output;
                    output++;
                    output[-1].z = (s32)outZ;
                } while ((u32)output != scan);
                selected = (u32 *)vertices;
            }
            func_150E4550((f32)x, height, (f32)z, 1, func_1510F8CC(material), (s32)selected, 0);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E4928 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4928.s")

extern s32 D_800BE9E4;

typedef struct {
    u8 pad0[0x90];
    s32 f90;
    s16 f94;
    s16 f96;
    s16 f98;
    u8 pad9A[0xA2 - 0x9A];
    s16 fA2;
    s16 fA4;
    u8 padA6[0xB4 - 0xA6];
    u8 fB4;
} Game111670Fader;

void func_150E4CBC(Game111670Fader *a) {
    if (a->f90 < 9) {
        a->fA4 = (f32)(a->f90 * 90 / 9 * a->f96) * 0.00390625f;
    } else {
        a->fA4 = ((90 - (a->f90 * 90 - 810) / 600) * a->f96) * 0.00390625f;
        if (a->fB4 > D_800BE9E4 * 17) {
            a->fB4 -= D_800BE9E4 * 17;
        } else {
            a->f98 = -1;
        }
    }
    a->fA2 = (s32)(a->f94 * 14.0f) >> 8;
    if (a->f90 > 0x260) {
        a->f98 = -1;
    }
    a->f90 += D_800BE9E4;
}
typedef struct GameE4E04Triangle {
    f32 values[3][3];
} GameE4E04Triangle;

typedef struct GameE4E04Packet {
    void *data;
    u8 pad04[8];
    s16 field0C, field0E;
    s16 x, y, z;
    s16 velocityX, velocityZ;
    u8 pad1A[5];
    s8 field1F;
    s16 velocityY;
    s16 field22;
    s16 field24, field26;
    s16 field28;
    s8 field2A;
    u8 pad2B;
    u8 red, green, blue, alpha;
    u8 pad30[4];
    s16 field34;
    u8 pad36[2];
} GameE4E04Packet;

void func_150440A0(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
f32 func_150ADA68(void);
void func_15049350();
void func_150E5558(f32, f32, f32, f32, f32, f32, s32, s32);
extern f32 D_800CC210, D_800CC214, D_800CC218;
extern u8 D_8009187C[], D_800918A0[], D_800918AC[], D_80090520[];
extern u8 D_800D9960[];
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)
f32 fabsf(f32);
#pragma intrinsic(fabsf)

void func_150E4E04(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    f32 base;
    f32 range;
    f32 x;
    f32 y;
    f32 z;
    s32 noMatrix;
    s32 doubled;
    s32 i;
    GameE4E04Triangle triangle;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 length;
    f32 speed;
    f32 matrix[16];
    GameE4E04Packet packet;
    f32 scale;
    s32 count;
    s32 ok;
    s32 skip;
    u8 angle;

    scale = 815.0f;
    ok = 1;
    count = 1;
    noMatrix = 0;
    doubled = 0;
    skip = 0;
    speed = scale;
    func_100226F0(&packet, 0x38);
    if (arg3 & 0x8000) {
        skip = 1;
        arg3 ^= 0x8000;
    }
    if (arg5 != 0) {
        for (i = 0; i < 3; i++) {
            triangle.values[i][0] = ((s16 **)arg5)[i][0];
            triangle.values[i][1] = ((s16 **)arg5)[i][1];
            triangle.values[i][2] = ((s16 **)arg5)[i][2];
        }
        func_15049350(triangle);
        nx = -D_800CC210;
        ny = -D_800CC214;
        nz = -D_800CC218;
        length = sqrtf(nx * nx + ny * ny + nz * nz);
        if (length < 0.0001f) {
            return;
        }
        nx /= length;
        ny /= length;
        nz /= length;
        if (arg6 != 0xFF && fabsf(ny) < 0.9f) {
            func_150440A0(matrix, 0.0f, 0.0f, 0.0f, nx, ny, nz, 0.0f, 1.0f, 0.0f);
            func_150A7960(matrix, 0.0f, 0.0f, 1.0f, (f32 *)(D_800D9960 + arg6 * 0x1C + 0x10),
                          (f32 *)(D_800D9960 + arg6 * 0x1C + 0x14), (f32 *)(D_800D9960 + arg6 * 0x1C + 0x18));
        } else {
            noMatrix = 1;
        }
    } else {
        noMatrix = 1;
    }
    if (arg6 != 0xFF && noMatrix != 0) {
        D_800D9963[arg6 * 0x1C] = 0;
    }
    if (skip != 0) {
        return;
    }
    packet.x = (s32)arg0;
    packet.y = (s32)arg1;
    packet.z = (s32)arg2;
    packet.red = 0xB4;
    packet.green = 0xB4;
    packet.blue = 0xB4;
    packet.alpha = 0xFF;
    packet.field1F = -1;
    packet.field34 = 0;
    packet.field0C = 0;
    packet.field0E = 0;
    base = (f32)D_800A1110[arg4][1] * 95.0f * 0.00390625f;
    range = (f32)D_800A1110[arg4][1] * 130.0f * 0.00390625f;
    if (arg3 == 0x11) {
        packet.data = D_8009187C;
    } else if (arg3 == 0xA) {
        packet.data = D_800918A0;
    } else if (arg3 == 4 || arg3 == 9) {
        packet.data = D_800918A0;
    } else if (arg3 == 8) {
        packet.data = D_80090520;
        base = 180.0f;
        range = 200.0f;
    } else {
        packet.data = D_800918AC;
    }
    if (arg4 == 2) {
        doubled = 1;
        packet.field22 = -0x175;
        count = 12;
        speed *= 0.5f * (f32)(func_151EF610() % 3 + 1);
    } else if (arg4 == 0) {
        packet.field22 = -0xDA;
        count = 12;
        speed = scale * 0.5f;
    } else {
        packet.field22 = -0xDA;
    }
    while (count-- && ok) {
        f32 velocity;
        velocity = func_150ADA68() * 957.0f + speed;
        angle = func_151EF610() % 256;
        if (doubled != 0) {
            velocity += velocity;
        }
        if (noMatrix != 0) {
            nx = func_15048A40(angle);
            ny = 1.0f;
            nz = func_150489B0(angle);
        } else {
            scale = func_15048A40(angle);
            func_150A7960(matrix, scale * 0.5f, func_150489B0(angle) * 0.5f, 1.0f,
                          &nx, &ny, &nz);
        }
        x = 0.315f * nx;
        y = ny;
        z = 0.315f * nz;
        packet.field28 = func_151EF610() % 2 + 0x182;
        packet.velocityX = velocity * x;
        packet.velocityY = velocity * y;
        packet.velocityZ = velocity * z;
        func_151EF610();
        packet.field2A = 0xA;
        packet.field24 = func_150ADA68() * range + base;
        packet.field26 = func_150ADA68() * range + base;
        if (func_15167D84(&packet, 0, 0, -1, 0xFF, 0) == NULL) {
            ok = 0;
        }
    }
    if ((arg3 == 4 || arg3 == 9 || arg3 == 5) && func_151EF610() % 5 == 0) {
        func_150E5558(arg0, arg1, arg2, nx, ny, nz, arg3, arg4);
    }
}
typedef struct Game111670Effect {
    f32 field0, field4, field8, fieldC;
    f32 angle[3], scale[3], position[3], velocity[3], acceleration[3];
    f32 field4C;
    s32 flags;
    s16 duration, kind;
    u8 field58, pad59[3];
    s32 field5C;
    u8 color[9], pad69, field6A, pad6B;
    s32 field6C;
    u8 field70, pad71;
    s16 field72, field74;
    u8 pad76[6];
} Game111670Effect;

void func_100226F0(void *, s32);
f32 func_150484A0(f32, f32);
f32 func_150ADA68(void);
s32 func_151EF610(void);
void *func_15132A4C(void *, s32, s32, s32, u8, s32);

void func_150E5558(f32 arg0, f32 arg1, f32 arg2, f32 arg3,
                   f32 arg4, f32 arg5, s32 arg6, s32 arg7) {
    Game111670Effect packet;
    f32 pitch;
    register f32 yaw;
    f32 fraction, one;

    func_100226F0(&packet, 0x7C);
    if (arg4 != 0.0f) {
        pitch = func_150484A0(arg3, arg4) * 57.295776f;
    } else {
        pitch = 90.0f;
    }
    if (arg5 != 0.0f) {
        yaw = func_150484A0(arg3, arg5) * 57.295776f;
    } else {
        yaw = 90.0f;
    }
    one = 1.0f;
    packet.angle[1] = yaw;
    packet.angle[2] = pitch;
    packet.scale[0] = one;
    packet.scale[1] = one;
    packet.scale[2] = one;
    packet.field0 = one;
    packet.field8 = 0.17f;
    packet.fieldC = 0.17f;
    packet.position[0] = arg0;
    packet.position[1] = arg1;
    packet.position[2] = arg2;
    packet.angle[0] = 0.0f;
    if (arg6 == 4) {
        packet.kind = 6;
        packet.field4 = 0.6f;
    } else if (arg6 == 9) {
        packet.kind = 8;
        packet.field4 = 0.3f;
    } else {
        packet.kind = 7;
        packet.field4 = 0.3f;
    }
    packet.duration = func_151EF610() % 60 + 60;
    packet.flags = 0x29E9;
    fraction = func_150ADA68();
    packet.field4C = -0.78f;
    yaw = fraction * 4.6f + 1.5f;
    packet.velocity[0] = yaw * arg3;
    packet.velocity[1] = -yaw * arg4;
    packet.velocity[2] = yaw * arg5;
    packet.acceleration[0] = func_150ADA68() * 6.0f + -3.0f;
    packet.acceleration[2] = func_150ADA68() * 6.0f + -3.0f;
    fraction = func_150ADA68() * 6.0f + -3.0f;
    packet.field58 = 0;
    packet.field5C = 0;
    packet.acceleration[1] = fraction;
    packet.color[0] = 0xFF;
    packet.color[1] = 1;
    packet.color[2] = 0;
    packet.color[3] = 3;
    packet.color[4] = 0;
    packet.color[5] = 0;
    packet.color[6] = 0;
    packet.color[7] = 0;
    packet.color[8] = 0;
    packet.field6A = 2;
    packet.field6C = 0;
    packet.field70 = 0;
    packet.field72 = 0x20;
    packet.field74 = 7;
    func_15132A4C(&packet, 3, 0xFF, 0, 0xFF, 0);
}

typedef struct Game111670Point {
    f32 values[3];
} Game111670Point;

typedef struct Game111670Triangle {
    Game111670Point vertices[3];
} Game111670Triangle;

typedef struct Game111670PackedPoint {
    s16 values[3];
} Game111670PackedPoint;

typedef struct Game111670Motion {
    u8 pad0[0x10];
    f32 heightFactor, bounce;
    u8 pad18[0x24];
    f32 height;
    u8 pad40[4];
    f32 velocity[3], acceleration[3];
    u8 pad5C[4];
    u32 flags;
} Game111670Motion;

void func_15048F58(void *, void *, void *);
void func_15049148(void *, f32, void *);
f32 func_150AD900(f32 *, f32 *);
f32 func_150AD930(void *);
void func_15049350(Game111670Triangle);
extern f32 D_800A1160, D_800A1164, D_800A1168;
extern f32 D_800CC210, D_800CC214, D_800CC218;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_150E5810 CURRENT (942) */
s32 func_150E5810(Game111670Motion *motion, s32 unused1, s32 unused2, s32 unused3,
                  f32 height, Game111670PackedPoint *vertices) {
    Game111670Triangle triangle;
    f32 value;
    f32 vertical;
    f32 factor;
    register s32 i;
    f32 velocity[3];
    f32 normal[3];
    f32 unit[3];

    motion->height = motion->heightFactor * D_800A1160 + height;
    vertical = motion->velocity[1];
    if (vertical > -2.0f) {
        motion->velocity[0] = 0.0f;
        motion->flags &= ~0x6FU;
        motion->velocity[1] = 0.0f;
        motion->velocity[2] = 0.0f;
    } else {
        if (vertices != 0) {
            for (i = 0; i != 3; i++) {
                triangle.vertices[i].values[0] = vertices[i].values[0];
                triangle.vertices[i].values[1] = vertices[i].values[1];
                triangle.vertices[i].values[2] = vertices[i].values[2];
            }
            func_15049350(triangle);
            normal[0] = -D_800CC210;
            normal[1] = -D_800CC214;
            normal[2] = -D_800CC218;
            value = func_150AD930(normal);
            if (D_800A1164 < value) {
                func_15049148(normal, 1.0f / value, unit);
                velocity[0] = motion->velocity[0];
                velocity[1] = motion->velocity[1];
                velocity[2] = motion->velocity[2];
                func_15049148(unit,
                              2.0f * func_150AD900(unit, velocity),
                              normal);
                func_15048F58(velocity, normal, normal);
                value = motion->bounce;
                factor = D_800A1168;
                motion->velocity[0] = value * normal[0] * factor;
                motion->velocity[1] = value * normal[1];
                motion->velocity[2] = value * normal[2] * factor;
            }
        } else {
            value = motion->bounce;
            motion->velocity[0] *= value;
            motion->velocity[1] = -vertical * value;
            motion->velocity[2] *= value;
        }
        value = motion->bounce;
        motion->acceleration[0] *= value;
        motion->acceleration[1] *= value;
        motion->acceleration[2] *= value;
    }
    return 1;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_150E5810 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E5810.s")
