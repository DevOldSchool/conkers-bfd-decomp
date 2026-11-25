#include "types.h"

/* Evidence: docs/evidence/data-layout/us_scene_ui.md
 * Data-only reconstruction; original object boundaries and runtime coverage are separate.
 */

/* Native decimal renderer clamps to 0..9999999 and uses seven descending powers. */
s32 D_80090074[10] = { 2226, 2192, 2219, 2216, 2178, 2177, 2210, 2209, 2176, 2191 };
s32 D_8009009C[7] = { 1, 10, 100, 1000, 10000, 100000, 1000000 };
