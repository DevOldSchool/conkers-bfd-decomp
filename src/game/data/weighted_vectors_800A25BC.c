#include "types.h"
#include "game_vec.h"

/* Vector table filling its storage up to the next object.
 * Every represented index has a native selector witness in all rounding modes.
 * Upward rounding also permits an index one past the table.
 * Evidence: docs/evidence/data-layout/us_weighted_vectors.md
 */

Vec3f D_800A25BC[6] = {
    { 0.0f, 17.5890007f, 79.8000031f },
    { 0.0f, 10.8240004f, 94.8000031f },
    { 0.0f, -0.90200001f, 102.000008f },
    { 0.0f, -10.3730001f, 99.0000076f },
    { 0.0f, -14.8830004f, 81.0f },
    { 0.0f, -13.5299997f, 0.600000024f },
};
