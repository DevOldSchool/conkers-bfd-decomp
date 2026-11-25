#include "types.h"
#include "game_vec.h"

/* Vector table filling its storage up to the next object.
 * Every represented index has a native selector witness in all rounding modes.
 * Upward rounding also permits an index one past the table.
 * Evidence: docs/evidence/data-layout/us_weighted_vectors.md
 */

Vec3f D_800A24B0[7] = {
    { 10.0f, -2.0f, 73.0f },
    { 10.0f, 7.0f, 211.0f },
    { 10.0f, 0.0f, 231.0f },
    { 10.0f, -17.0f, 238.0f },
    { 10.0f, -36.0f, 231.0f },
    { 10.0f, -41.0f, 209.0f },
    { 10.0f, -34.0f, 78.0f },
};
