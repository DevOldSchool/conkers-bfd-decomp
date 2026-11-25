#include "types.h"

/* Evidence: docs/evidence/data-layout/us_scene_ui.md
 * Data-only reconstruction; original object boundaries and runtime coverage are separate.
 */

/* Native scene preloads; the original consumer stops at the first zero word. */

u32 D_80090150[7] = { 4404, 4402, 4406, 1473, 1825, 1823, 0 };
u32 D_8009016C[6] = { 2339, 2340, 2341, 2342, 2982, 0 };
u32 D_80090184[16] = { 2339, 2340, 2341, 2342, 2982, 4702, 4704, 4706, 4708, 4710, 4697, 4698, 4699, 4700, 4701, 0 };
u32 D_800901C4[11] = { 4702, 4704, 4706, 4708, 4710, 4697, 4698, 4699, 4700, 4701, 0 };
