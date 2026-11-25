#include "game_vec.h"

/* Evidence: docs/evidence/data-layout/us_model_effect.md
 * Data-only reconstruction; original object boundaries and runtime coverage are separate.
 */

/* Native effect-profile offsets, model selectors and mode bytes. */
typedef struct {
    Vec3f offset;
    u16 modelSelector;
    u8 mode;
} ModelEffectProfile;

ModelEffectProfile D_800A3FD8[20] = {
    { { 0.0f, 30.0f, 8.0f }, 58, 0 },
    { { 0.0f, 20.0f, 30.0f }, 48, 0 },
    { { 0.0f, 30.0f, 8.0f }, 68, 1 },
    { { 0.0f, 30.0f, 8.0f }, 75, 0 },
    { { 0.0f, 30.0f, 8.0f }, 129, 0 },
    { { 0.0f, 30.0f, 8.0f }, 178, 0 },
    { { 0.0f, 30.0f, 8.0f }, 178, 0 },
    { { 0.0f, 30.0f, 8.0f }, 58, 0 },
    { { 0.0f, 30.0f, 8.0f }, 187, 0 },
    { { 0.0f, 30.0f, 8.0f }, 188, 0 },
    { { 0.0f, 30.0f, 8.0f }, 188, 1 },
    { { 0.0f, 30.0f, 8.0f }, 152, 0 },
    { { 0.0f, 20.0f, 30.0f }, 48, 0 },
    { { 0.0f, 20.0f, 30.0f }, 48, 0 },
    { { 0.0f, 20.0f, 30.0f }, 218, 0 },
    { { 0.0f, 20.0f, 30.0f }, 68, 1 },
    { { 0.0f, 20.0f, 30.0f }, 227, 2 },
    { { 0.0f, 20.0f, 30.0f }, 211, 2 },
    { { 0.0f, 20.0f, 30.0f }, 211, 1 },
    { { 0.0f, 30.0f, 8.0f }, 58, 0 },
};
