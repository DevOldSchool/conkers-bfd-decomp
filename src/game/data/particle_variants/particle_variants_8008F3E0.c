#include "game_vec.h"
#include "game_particle_data.h"

/* Evidence: docs/evidence/data-layout/us_particle_variants.md
 * Native ordinals reach 5; the array fills its storage up to the next object.
 */

extern ParticleDescriptor D_8008ED80[24];

ParticleDescriptor *D_8008F3E0[18] = {
    &D_8008ED80[4], &D_8008ED80[5], &D_8008ED80[8],
    &D_8008ED80[4], &D_8008ED80[5], &D_8008ED80[8],
    &D_8008ED80[4], &D_8008ED80[5], &D_8008ED80[8],
    &D_8008ED80[4], &D_8008ED80[5], &D_8008ED80[8],
    &D_8008ED80[4], &D_8008ED80[5], &D_8008ED80[8],
    &D_8008ED80[4], &D_8008ED80[5], &D_8008ED80[8],
};
