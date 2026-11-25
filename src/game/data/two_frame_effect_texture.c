#include "types.h"

/* Evidence: docs/evidence/data-layout/us_two_frame_effect_data.md
 * Native type-nine constructor and renderer select frames zero and one.
 */
typedef struct {
    u32 *frames;
    u8 storedCount;
    u16 width;
    u16 height;
    u8 format;
    u8 size;
} TwoFrameTextureDescriptor;

typedef struct {
    u32 frames[2];
    TwoFrameTextureDescriptor descriptor;
} TwoFrameTexture;

TwoFrameTexture D_8009060C = {
    { 2990, 2988 },
    { D_8009060C.frames, 2, 32, 44, 2, 1 },
};
