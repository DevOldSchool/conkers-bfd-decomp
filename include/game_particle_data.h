#ifndef CONKER_GAME_PARTICLE_DATA_H
#define CONKER_GAME_PARTICLE_DATA_H

#include "types.h"
#include "game_vec.h"

/* Particle descriptor records shared by the game data tables.
 * Promoted from identical copies in src/game/data/particle_* sources.
 * Evidence: docs/evidence/data-layout/us_particle_settings.md,
 * us_particle_points.md and us_particle_variants.md.
 */
typedef struct {
    f32 field00;
    f32 field04;
    f32 field08;
    f32 field0C;
    f32 field10;
    f32 field14;
    f32 field18;
    f32 field1C;
    f32 field20;
    f32 field24;
    s16 field28;
    s16 field2A;
    f32 field2C;
    f32 field30;
    s16 field34;
    s16 field36;
    u8 field38;
    u8 field39;
    u8 field3A;
    u8 field3B;
    u8 field3C;
    u8 field3D;
    u8 field3E;
    u8 field3F;
} ParticleParameters;

typedef struct {
    Vec3f position;
    s16 joint;
} ParticlePoint;

typedef struct {
    ParticleParameters *parameters;
    s32 pointCount;
    ParticlePoint *points;
    f32 field0C;
    s32 field10;
    s16 field14;
    s16 field16;
    u8 field18;
    u8 field19;
    f32 field1C;
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    u8 field34;
} ParticleDescriptor;

typedef struct {
    s16 count;
    u8 *values;
} ParticleFilter;

#endif
