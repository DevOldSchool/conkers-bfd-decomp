#include "game_vec.h"
#include "game_particle_data.h"

/* Evidence: docs/evidence/data-layout/us_particle_variants.md
 * Native ordinals reach 5; the array fills its storage up to the next object.
 */

extern ParticleDescriptor D_8008ED80[24];

ParticleDescriptor *D_8008F2F0[30] = {
    &D_8008ED80[2], &D_8008ED80[3], &D_8008ED80[1], &D_8008ED80[2], &D_8008ED80[2],
    &D_8008ED80[2], &D_8008ED80[3], &D_8008ED80[1], &D_8008ED80[2], &D_8008ED80[2],
    &D_8008ED80[2], &D_8008ED80[3], &D_8008ED80[1], &D_8008ED80[2], &D_8008ED80[2],
    &D_8008ED80[2], &D_8008ED80[3], &D_8008ED80[1], &D_8008ED80[2], &D_8008ED80[2],
    &D_8008ED80[2], &D_8008ED80[3], &D_8008ED80[1], &D_8008ED80[2], &D_8008ED80[2],
    &D_8008ED80[2], &D_8008ED80[3], &D_8008ED80[1], &D_8008ED80[2], &D_8008ED80[2],
};
