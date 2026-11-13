#include "types.h"

/*
 * Reviewed source unit: src/game/game_770F0.c
 * Boundary evidence: docs/evidence/boundaries/game/families/game_raw_preserved_helper_groups.md
 */

void func_15049C40(void *arg0, void *arg1) {
    f32 dot;

    dot = (*(f32 *)((u8 *)arg0 + 0) * *(f32 *)((u8 *)arg1 + 0)) + (*(f32 *)((u8 *)arg0 + 4) * *(f32 *)((u8 *)arg1 + 4)) + (*(f32 *)((u8 *)arg0 + 8) * *(f32 *)((u8 *)arg1 + 8)) + (*(f32 *)((u8 *)arg0 + 0xC) * *(f32 *)((u8 *)arg1 + 0xC));
    if (dot < 0.0f) {
        *(f32 *)((u8 *)arg1 + 0) = (f32) -*(f32 *)((u8 *)arg1 + 0);
        *(f32 *)((u8 *)arg1 + 4) = (f32) -*(f32 *)((u8 *)arg1 + 4);
        *(f32 *)((u8 *)arg1 + 8) = (f32) -*(f32 *)((u8 *)arg1 + 8);
        *(f32 *)((u8 *)arg1 + 0xC) = (f32) -*(f32 *)((u8 *)arg1 + 0xC);
    }
}
typedef struct {
    s32 indices[3];
} Game770F0IndexCycle;

f32 func_10026530(f32);
extern Game770F0IndexCycle D_80085FF0;
extern f32 D_80099090;

void func_15049CB8(f32 matrix[4][4], f32 *result) {
    f32 root;
    s32 i;
    s32 j;
    s32 k;

    root = matrix[0][0] + matrix[1][1] + matrix[2][2] + 1.0f;
    if (D_80099090 < root) {
        f32 scale;

        root = func_10026530(root);
        scale = 0.5f / root;
        result[0] = root * 0.5f;
        result[1] = (matrix[1][2] - matrix[2][1]) * scale;
        result[2] = (matrix[2][0] - matrix[0][2]) * scale;
        result[3] = (matrix[0][1] - matrix[1][0]) * scale;
    } else {
        Game770F0IndexCycle cycle;
        f32 scale;

        cycle = D_80085FF0;
        i = 0;
        if (matrix[0][0] < matrix[1][1]) {
            i = 1;
        }
        if (matrix[i][i] < matrix[2][2]) {
            i = 2;
        }
        j = cycle.indices[i];
        k = cycle.indices[j];
        root = func_10026530((matrix[i][i] - matrix[j][j] - matrix[k][k]) + 1.0f);
        scale = 0.5f / root;
        result[i + 1] = root * 0.5f;
        result[0] = (matrix[j][k] - matrix[k][j]) * scale;
        result[j + 1] = (matrix[i][j] + matrix[j][i]) * scale;
        result[k + 1] = (matrix[i][k] + matrix[k][i]) * scale;
    }
}
/* Call context: func_15047D60: unique active project prototype */
/* Call context: func_15048360: unique active project prototype */
f32 func_15047D60(f32);
f32 func_15048360(f32);
extern f32 D_80099094;
extern f32 D_80099098;

void func_15049EDC(f32 *q0, f32 *q1, f32 t, f32 *out) {
    f32 dot;
    f32 inv;

    dot = q0[0] * q1[0] + q0[1] * q1[1] + q0[2] * q1[2] + q0[3] * q1[3];
    if (dot < D_80099094) {
        inv = 1.0f - t;
        out[0] = inv * q0[0] - q1[0] * t;
        out[1] = inv * q0[1] - q1[1] * t;
        out[2] = inv * q0[2] - q1[2] * t;
        out[3] = inv * q0[3] - q1[3] * t;
    } else if (dot <= D_80099098) {
        f32 angleA;
        f32 angleB;
        f32 sinTheta;
        f32 scale0;
        f32 theta;
        f32 scale1;

        theta = func_15048360(dot);
        angleA = (1.0f - t) * theta;
        angleB = t * theta;
        sinTheta = func_15047D60(theta);
        scale0 = func_15047D60(angleA) / sinTheta;
        scale1 = func_15047D60(angleB) / sinTheta;
        out[0] = scale0 * q0[0] + q1[0] * scale1;
        out[1] = scale0 * q0[1] + q1[1] * scale1;
        out[2] = scale0 * q0[2] + q1[2] * scale1;
        out[3] = scale0 * q0[3] + q1[3] * scale1;
    } else {
        inv = 1.0f - t;
        out[0] = inv * q0[0] + q1[0] * t;
        out[1] = inv * q0[1] + q1[1] * t;
        out[2] = inv * q0[2] + q1[2] * t;
        out[3] = inv * q0[3] + q1[3] * t;
    }
}
void func_1504A140(f32 *q, f32 m[4][4]) {
    f32 s;
    f32 ys;
    f32 zs;
    f32 ws;
    f32 xy;
    f32 xz;
    f32 xw;
    f32 yy;
    f32 yz;
    f32 yw;
    f32 zz;
    f32 zw;
    f32 ww;

    s = 2.0f / (q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
    ys = q[1] * s;
    zs = q[2] * s;
    ws = q[3] * s;
    xy = q[0] * ys;
    xz = q[0] * zs;
    xw = q[0] * ws;
    yy = q[1] * ys;
    yz = q[1] * zs;
    yw = q[1] * ws;
    zz = q[2] * zs;
    zw = q[2] * ws;
    ww = q[3] * ws;
    m[0][0] = 1.0f - (zz + ww);
    m[0][1] = yz + xw;
    m[0][2] = yw - xz;
    m[1][0] = yz - xw;
    m[1][1] = 1.0f - (yy + ww);
    m[1][2] = zw + xy;
    m[2][0] = yw + xz;
    m[2][1] = zw - xy;
    m[2][2] = 1.0f - (yy + zz);
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;
}
