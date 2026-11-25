#include "types.h"
#include "game_vec.h"

/* Vector table filling its storage up to the next object.
 * Every represented index has a native selector witness in all rounding modes.
 * Upward rounding also permits an index one past the table.
 * Evidence: docs/evidence/data-layout/us_weighted_vectors.md
 */

Vec3f D_800A2520[6] = {
    { 10.0f, 22.0f, 211.0f },
    { 10.0f, 7.0f, 236.0f },
    { 10.0f, -19.0f, 248.0f },
    { 10.0f, -40.0f, 243.0f },
    { 10.0f, -50.0f, 213.0f },
    { 10.0f, -47.0f, 79.0f },
};
