#include "types.h"

/*
 * Reviewed source unit: src/game/game_15B200.c
 * Boundary evidence: docs/evidence/game_remaining_upstream_c_groups.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1512DD50
 * - func_1512DEA4
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

f32 func_150AD930(f32 *);         /* extern */

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512DD50 CURRENT (4780) */
void func_1512DD50(u8 *arg0) {
    f32 sp40;
    f32 vector[3];
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    u8 *temp_v0;
    u8 *temp_v1;

    sp40 = (f32) *(s16 *)((u8 *)arg0 + 0x710);
    temp_fv1 = (f32) *(s16 *)((u8 *)arg0 + 0x712);
    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x720) * temp_fv1;
    temp_fa0 = *(f32 *)((u8 *)arg0 + 0x724) * temp_fv1;
    temp_fv0_2 = *(f32 *)((u8 *)arg0 + 0x728) * temp_fv0;
    temp_fa1 = -temp_fv0 * *(f32 *)((u8 *)arg0 + 0x72C);
    *(f32 *)((u8 *)arg0 + 0x878) = (f32) ((f32) *(s16 *)((u8 *)arg0 + 0x70E) - temp_fa0);
    *(f32 *)((u8 *)arg0 + 0x874) = (f32) ((f32) *(s16 *)((u8 *)arg0 + 0x70C) - temp_fv0_2);
    *(f32 *)((u8 *)arg0 + 0x87C) = (f32) (sp40 - temp_fa1);
    vector[0] = 2.0f * temp_fv0_2;
    vector[1] = 2.0f * temp_fa0;
    vector[2] = 2.0f * temp_fa1;
    temp_fv1_2 = 1.0f / func_150AD930(vector);
    temp_v0 = (void *)(arg0 + 0x870);
    temp_v1 = (void *)(arg0 + 0x6FC);
    *(f32 *)((u8 *)temp_v0 + 0x1C) = temp_fv1_2;
    *(f32 *)((u8 *)temp_v0 + 0x10) = (f32) (temp_fv1_2 * vector[0]);
    *(f32 *)((u8 *)temp_v0 + 0x14) = (f32) (temp_fv1_2 * vector[1]);
    *(f32 *)((u8 *)temp_v0 + 0x18) = (f32) (temp_fv1_2 * vector[2]);
    *(f32 *)((u8 *)temp_v0 + 0x20) = (f32) *(u32 *)(temp_v1 + 0x20);
    *(f32 *)((u8 *)temp_v0 + 0x24) = (f32) *(u32 *)(temp_v1 + 8);
    *(f32 *)((u8 *)temp_v0 + 0x28) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x2C) = 0.0f;
    *(s8 *)((u8 *)arg0 + 0x870) = (s8) *(s32 *)((u8 *)temp_v1 + 0x1C);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512DD50 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15B200/func_1512DD50.s")
typedef struct Game15B200Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Game15B200Vec3;

typedef struct Game15B200Camera {
    u8 mode;
    u8 unknown1[3];
    Game15B200Vec3 origin;
    Game15B200Vec3 direction;
    f32 inverse;
    f32 speed;
    f32 vertical;
    f32 acceleration;
    f32 maximum;
    f32 accelerationVelocity;
    f32 maximumVelocity;
    Game15B200Vec3 target;
} Game15B200Camera;

typedef struct Game15B200Actor {
    u8 unknown0[0x23C];
    u8 immediate;
    u8 unknown23D[0x7F];
    Game15B200Vec3 anchor;
    u8 unknown2C8[0x30];
    Game15B200Vec3 position;
    u8 unknown304[0xBC];
    Game15B200Vec3 velocity;
    u8 unknown3CC[0x3E8];
    f32 timestep;
    u8 unknown7B8[0xB8];
    Game15B200Camera camera;
} Game15B200Actor;

f32 sqrtf(f32);
__pragma(1, sqrtf);
void func_150495B0(f32 *, f32, f32 *, f32, f32, f32);
extern f32 D_800A3710;
extern f32 D_800A3714;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1512DEA4 CURRENT (4583) */
void func_1512DEA4(Game15B200Actor *actor) {
    Game15B200Vec3 offset;
    f32 x;
    f32 y;
    f32 z;
    f32 dx;
    f32 dy;
    volatile f32 dz;
    f32 distance;
    f32 speed;
    Game15B200Camera *camera;
    s32 mode;

    x = actor->camera.origin.x;
    y = actor->camera.origin.y;
    dx = x - actor->anchor.x;
    z = actor->camera.origin.z;
    dy = y - actor->anchor.y;
    dz = z - actor->anchor.z;
    camera = &actor->camera;
    distance = sqrtf((dx * dx) + (dy * dy) + (dz * dz));
    actor->camera.target.x = x + actor->camera.direction.x * distance;
    actor->camera.target.y = y + actor->camera.direction.y * distance;
    actor->camera.target.z = z + actor->camera.direction.z * distance;
    offset.y = actor->camera.vertical;
    mode = actor->camera.mode;
    if (mode != 0) {
        camera = &actor->camera;
        if (mode != 1) {
            camera = &actor->camera;
            if (mode != 2) {
                camera = &actor->camera;
                if (mode != 3) {
                    camera = &actor->camera;
                } else {
                    speed = camera->speed;
                    offset.x = speed * -camera->direction.x;
                    offset.z = speed * -camera->direction.z;
                }
            } else {
                speed = camera->speed;
                offset.x = speed * camera->direction.x;
                offset.z = speed * camera->direction.z;
            }
        } else {
            speed = camera->speed;
            offset.x = speed * -camera->direction.z;
            offset.z = speed * camera->direction.x;
        }
    } else {
        speed = camera->speed;
        offset.x = speed * camera->direction.z;
        offset.z = speed * -camera->direction.x;
    }
    camera->target.x += offset.x;
    camera->target.y += offset.y;
    camera->target.z += offset.z;
    if (actor->immediate != 0) {
        actor->position.x = camera->target.x;
        actor->position.y = camera->target.y;
        actor->position.z = camera->target.z;
        camera->acceleration = 40.0f;
        camera->maximum = 40.0f;
        return;
    }
    func_150495B0(&camera->acceleration, 10.0f, &camera->accelerationVelocity, 0.6f, D_800A3710, actor->timestep);
    func_150495B0(&camera->maximum, 10.0f, &camera->maximumVelocity, 0.6f, D_800A3714, actor->timestep);
    func_150495B0(&actor->position.x, camera->target.x, &actor->velocity.x, camera->acceleration, camera->maximum, actor->timestep);
    func_150495B0(&actor->position.y, camera->target.y, &actor->velocity.y, camera->acceleration, camera->maximum, actor->timestep);
    func_150495B0(&actor->position.z, camera->target.z, &actor->velocity.z, camera->acceleration, camera->maximum, actor->timestep);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1512DEA4 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_15B200/func_1512DEA4.s")
