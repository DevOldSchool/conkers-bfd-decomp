#include "game_vec.h"
#include "game_particle_data.h"

/* Native particle attachment points; count comes from the consuming descriptor.
 * Evidence: docs/evidence/data-layout/us_particle_points.md
 * The array fills its storage up to the next object; runtime coverage is not claimed.
 */
ParticlePoint D_8008E490[11] = {
    { { 0.0f, 31.0f, 0.0f }, 13 },
    { { 35.0f, 2.0f, 28.0f }, 13 },
    { { 17.0f, 2.0f, -31.0f }, 13 },
    { { 56.0f, 2.0f, -31.0f }, 13 },
    { { 56.0f, 2.0f, 38.0f }, 13 },
    { { 0.0f, 28.0f, 0.0f }, 14 },
    { { 17.0f, 28.0f, 27.0f }, 14 },
    { { 61.0f, 28.0f, 18.0f }, 14 },
    { { 61.0f, 28.0f, -39.0f }, 14 },
    { { 50.0f, 10.0f, 1.0f }, 15 },
    { { 34.0f, 21.0f, 3.0f }, 17 },
};
