#include "types.h"

/* Original scene choices select the first creation row.
 * Its count-eight callback proves eight float pairs.
 * Unrelated byte data follows the eight pairs; no gameplay activation is
 * asserted.
 * Evidence: docs/evidence/data-layout/us_native_fp_control.md
 */

f32 D_80095C64[8][2] = {
    { 0.5f, 0.5f },
    { 0.300000012f, 0.119999997f },
    { 0.699999988f, 0.879999995f },
    { 0.899999976f, 0.400000006f },
    { 0.100000001f, 0.600000024f },
    { 0.600000024f, 0.25f },
    { 0.300000012f, 0.75f },
    { 0.800000012f, 0.200000003f },
};
