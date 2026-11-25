#include "types.h"

/* Evidence: docs/evidence/data-layout/us_literal_effect_data.md
 * Native selectors establish these extents; grouping does not infer original C objects.
 */

typedef struct {
    u32 resource;
    u8 storedCount;
    u16 width;
    u16 height;
    u8 format;
    u8 size;
} LiteralScalarTexture;

LiteralScalarTexture D_80091840 = { 1205, 1, 32, 32, 5, 2 };
