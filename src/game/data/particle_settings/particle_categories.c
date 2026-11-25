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

extern ParticleFilter D_8008F750[6];
extern ParticleDescriptor *D_8008F2C0[];
extern ParticleDescriptor *D_8008F2F0[];
extern ParticleDescriptor *D_8008F368[];
extern ParticleDescriptor *D_8008F3E0[];
extern ParticleDescriptor *D_8008F428[];
extern ParticleDescriptor *D_8008F470[];
extern ParticleDescriptor *D_8008F4A0[];
extern ParticleDescriptor *D_8008F4E8[];
extern ParticleDescriptor *D_8008F518[];
extern ParticleDescriptor *D_8008F590[];
extern ParticleDescriptor *D_8008F608[];
extern ParticleDescriptor *D_8008F638[];
extern ParticleDescriptor *D_8008F668[];
extern ParticleDescriptor *D_8008F698[];
extern ParticleDescriptor *D_8008F6C8[];
extern ParticleDescriptor *D_8008F6F8[];

ParticleCategory D_8008F780[16] = {
    { D_8008F2C0, 0, 0 },
    { D_8008F2F0, 3, &D_8008F750[0] },
    { D_8008F368, 3, &D_8008F750[0] },
    { D_8008F3E0, 1, &D_8008F750[3] },
    { D_8008F428, 1, &D_8008F750[4] },
    { D_8008F470, 0, 0 },
    { D_8008F4A0, 1, &D_8008F750[5] },
    { D_8008F4E8, 0, 0 },
    { D_8008F518, 3, &D_8008F750[0] },
    { D_8008F590, 3, &D_8008F750[0] },
    { D_8008F608, 0, 0 },
    { D_8008F638, 0, 0 },
    { D_8008F668, 0, 0 },
    { D_8008F698, 0, 0 },
    { D_8008F6C8, 0, 0 },
    { D_8008F6F8, 0, 0 },
};
