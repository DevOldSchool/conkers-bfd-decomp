#include "types.h"

/* Evidence: docs/evidence/data-layout/us_scene_ui.md
 * Data-only reconstruction; original object boundaries and runtime coverage are separate.
 */

/* Scene header selectors zero through four; zero disables loading. */
extern u32 D_80090150[7];
extern u32 D_8009016C[6];
extern u32 D_80090184[16];
extern u32 D_800901C4[11];

u32 *D_80082B20[5] = {
    0,
    D_8009016C,
    D_80090184,
    D_800901C4,
    D_80090150,
};
