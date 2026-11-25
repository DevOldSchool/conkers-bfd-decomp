#include "types.h"

/* Joint verification record; compatible with the existing source declaration.
 * Native selector witnesses cover all six weight fields and the total.
 * No original whole-object boundary or gameplay reachability is inferred.
 * Evidence: docs/evidence/data-layout/us_weighted_record_joint.md
 */

struct { f32 weights[6]; f32 total; } D_800A2504 = {
    { 138.293121f, 21.189621f, 18.3847771f, 20.248457f, 22.5610275f, 131.18689f },
    351.863892f
};
