#include "game_vec.h"
#include "game_particle_data.h"

/* Evidence: docs/evidence/data-layout/us_particle_variants.md
 * Native ordinals reach 5; the array fills its storage up to the next object.
 */

extern ParticleDescriptor D_8008ED80[24];

ParticleDescriptor *D_8008F4E8[12] = {
    &D_8008ED80[9], &D_8008ED80[9],
    &D_8008ED80[9], &D_8008ED80[9],
    &D_8008ED80[9], &D_8008ED80[9],
    &D_8008ED80[9], &D_8008ED80[9],
    &D_8008ED80[9], &D_8008ED80[9],
    &D_8008ED80[9], &D_8008ED80[9],
};
