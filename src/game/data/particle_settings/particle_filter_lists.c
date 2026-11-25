#include "types.h"
#include "game_particle_data.h"

/* Evidence: docs/evidence/data-layout/us_particle_settings.md
 * Data-only reconstruction; original object boundaries and runtime coverage are separate.
 */

/* Native byte filter lists and their count/pointer records.
 * Inter-list alignment is supplied by the compiler; no original C-object boundary is claimed.
 */
u8 D_8008F728[7] = { 15, 0, 1, 11, 233, 33, 54 };

u8 D_8008F730[1] = { 2 };

u8 D_8008F734[6] = { 50, 56, 57, 55, 105, 207 };

u8 D_8008F73C[10] = { 0, 4, 7, 9, 12, 13, 14, 15, 16, 17 };

u8 D_8008F748[2] = { 2, 6 };

u8 D_8008F74C[1] = { 2 };

ParticleFilter D_8008F750[6] = {
    { 7, D_8008F728 },
    { 1, D_8008F730 },
    { 6, D_8008F734 },
    { 10, D_8008F73C },
    { 2, D_8008F748 },
    { 1, D_8008F74C },
};
