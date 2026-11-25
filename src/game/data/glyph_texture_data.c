#include "types.h"

/* Evidence: docs/evidence/data-layout/us_glyph_texture_reconstruction.md
 * Native glyph cases prove each frame extent independently of storedCount.
 * This contiguous reconstruction does not establish an original C-object boundary.
 */

typedef struct {
    u32 *frames;
    u8 storedCount;
    u16 width;
    u16 height;
    u8 format;
    u8 size;
} GlyphTextureDescriptor;

typedef struct {
    u32 frames[1];
    GlyphTextureDescriptor descriptor;
} GlyphTexture1;

typedef struct {
    u32 frames[2];
    GlyphTextureDescriptor descriptor;
} GlyphTexture2;

typedef struct {
    u32 frames[4];
    GlyphTextureDescriptor descriptor;
} GlyphTexture4;

typedef struct {
    u32 frames[10];
    GlyphTextureDescriptor descriptor;
} GlyphTexture10;

typedef struct {
    GlyphTexture1 glyphA8;
    GlyphTexture1 glyphA9;
    GlyphTexture1 glyphAE;
    GlyphTexture1 glyphAF;
    GlyphTexture1 glyphB0;
    GlyphTexture1 glyphAA;
    GlyphTexture1 glyphAB;
    GlyphTexture1 glyphAC;
    GlyphTexture1 glyphAD;
    GlyphTexture10 glyphB1;
    GlyphTexture4 glyphB2;
    GlyphTexture4 glyphB4;
    GlyphTexture4 glyphB3;
    GlyphTexture4 glyphB5;
    GlyphTexture1 glyphB6;
    GlyphTexture1 glyphB7;
    GlyphTexture1 glyphB8;
    GlyphTexture1 glyphB9;
    GlyphTexture1 glyphBA;
    GlyphTexture2 glyphBB;
} GlyphTextureData;

GlyphTextureData D_800915D8 = {
    {
        { 2164 },
        { D_800915D8.glyphA8.frames, 0, 32, 32, 0, 3 },
    },
    {
        { 2168 },
        { D_800915D8.glyphA9.frames, 0, 32, 32, 0, 3 },
    },
    {
        { 7731 },
        { D_800915D8.glyphAE.frames, 0, 16, 32, 0, 2 },
    },
    {
        { 2941 },
        { D_800915D8.glyphAF.frames, 0, 32, 16, 0, 2 },
    },
    {
        { 3668 },
        { D_800915D8.glyphB0.frames, 0, 32, 16, 0, 2 },
    },
    {
        { 2985 },
        { D_800915D8.glyphAA.frames, 0, 32, 32, 0, 2 },
    },
    {
        { 3744 },
        { D_800915D8.glyphAB.frames, 0, 32, 32, 0, 2 },
    },
    {
        { 4695 },
        { D_800915D8.glyphAC.frames, 0, 32, 32, 0, 2 },
    },
    {
        { 1689 },
        { D_800915D8.glyphAD.frames, 0, 32, 32, 0, 2 },
    },
    {
        { 2023, 2024, 2025, 2026, 2027, 2028, 2027, 2026, 2025, 2024 },
        { D_800915D8.glyphB1.frames, 10, 32, 32, 0, 3 },
    },
    {
        { 4096, 4097, 4098, 4099 },
        { D_800915D8.glyphB2.frames, 3, 16, 16, 0, 2 },
    },
    {
        { 4235, 4236, 4237, 4238 },
        { D_800915D8.glyphB4.frames, 3, 16, 16, 0, 2 },
    },
    {
        { 4320, 4321, 4322, 4323 },
        { D_800915D8.glyphB3.frames, 3, 16, 16, 0, 2 },
    },
    {
        { 3069, 3070, 3071, 3072 },
        { D_800915D8.glyphB5.frames, 3, 16, 16, 0, 2 },
    },
    {
        { 4225 },
        { D_800915D8.glyphB6.frames, 1, 16, 16, 0, 2 },
    },
    {
        { 3361 },
        { D_800915D8.glyphB7.frames, 1, 16, 16, 0, 2 },
    },
    {
        { 3746 },
        { D_800915D8.glyphB8.frames, 1, 16, 16, 0, 2 },
    },
    {
        { 4535 },
        { D_800915D8.glyphB9.frames, 1, 16, 16, 0, 2 },
    },
    {
        { 3309 },
        { D_800915D8.glyphBA.frames, 1, 32, 16, 0, 2 },
    },
    {
        { 1659, 1660 },
        { D_800915D8.glyphBB.frames, 2, 16, 16, 0, 2 },
    },
};
