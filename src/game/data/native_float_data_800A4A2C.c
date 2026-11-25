#include "types.h"

/* Nine records are bounded by the native stepped-pointer loop.
 * Evidence: docs/evidence/data-layout/us_native_float_address_flow.md
 */

typedef struct { s32 first, count; } Game168A90Range;

Game168A90Range D_800A4A2C[9] = {
    { 0, 12 },
    { 12, 16 },
    { 28, 16 },
    { 44, 16 },
    { 60, 16 },
    { 76, 16 },
    { 92, 16 },
    { 108, 16 },
    { 124, 16 },
};
