#include "types.h"
#include "game_vec.h"

/* Vector table filling its storage up to the next object.
 * Every represented index has a native selector witness in all rounding modes.
 * Upward rounding also permits an index one past the table.
 * Evidence: docs/evidence/data-layout/us_weighted_vectors.md
 */

Vec3f D_800A2568[7] = {
    { 0.0f, 6.76499987f, -3.0f },
    { 0.0f, 10.8240004f, 79.8000031f },
    { 0.0f, 7.66700029f, 91.8000031f },
    { 0.0f, 0.0f, 96.0f },
    { 0.0f, -8.56900024f, 91.8000031f },
    { 0.0f, -10.8240004f, 78.6000061f },
    { 0.0f, -7.66700029f, 0.0f },
};
