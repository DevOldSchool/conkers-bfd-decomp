#include "game_vec.h"
#include "game_particle_data.h"

/* Native particle attachment points; count comes from the consuming descriptor.
 * Evidence: docs/evidence/data-layout/us_particle_points.md
 * The array fills its storage up to the next object; runtime coverage is not claimed.
 */
ParticlePoint D_8008E3B0[14] = {
    { { 0.0f, 0.0f, 114.0f }, 1 },
    { { -44.0f, 8.0f, 114.0f }, 1 },
    { { -91.0f, 19.0f, 86.0f }, 1 },
    { { 44.0f, 8.0f, 114.0f }, 1 },
    { { 91.0f, 19.0f, 86.0f }, 1 },
    { { -1.0f, 58.0f, 98.0f }, 11 },
    { { 62.0f, 19.0f, 62.0f }, 11 },
    { { 74.0f, 94.0f, 62.0f }, 11 },
    { { 112.0f, 44.0f, 24.0f }, 11 },
    { { 38.0f, 121.0f, 71.0f }, 11 },
    { { -62.0f, 19.0f, 62.0f }, 11 },
    { { -74.0f, 94.0f, 62.0f }, 11 },
    { { -112.0f, 44.0f, 24.0f }, 11 },
    { { -38.0f, 121.0f, 71.0f }, 11 },
};
