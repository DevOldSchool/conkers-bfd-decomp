#include "game_vec.h"
#include "game_particle_data.h"

/* Evidence: docs/evidence/data-layout/us_particle_settings.md
 * Data-only reconstruction; original object boundaries and runtime coverage are separate.
 */

/* Native particle selection graph; no original C-array boundary is claimed. */
typedef struct {
    ParticleDescriptor **variants;
    s16 filterCount;
    ParticleFilter *filters;
} ParticleCategory;

extern ParticleCategory D_8008F780[16];

ParticleCategory *D_8008D5E0[16] = {
    &D_8008F780[0],
    &D_8008F780[1],
    &D_8008F780[3],
    &D_8008F780[4],
    &D_8008F780[7],
    &D_8008F780[5],
    &D_8008F780[6],
    &D_8008F780[2],
    &D_8008F780[8],
    &D_8008F780[9],
    &D_8008F780[10],
    &D_8008F780[11],
    &D_8008F780[12],
    &D_8008F780[13],
    &D_8008F780[14],
    &D_8008F780[15],
};
