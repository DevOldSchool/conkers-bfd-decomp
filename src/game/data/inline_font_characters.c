#include "types.h"

/* Exact 80-byte character-to-glyph search order; this is not a C string.
 * Each group selects one eight-glyph row in the I4 font atlas.
 * Evidence: docs/evidence/data-layout/us_inline_font.md
 * Data-only reconstruction, not a claim about original C-object boundaries.
 */
const u8 D_800848D0[80] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'h', 'i', /* glyphs  0.. 7 */
    'u', 'v', 's', 'n', 'o', 'r', 'm', '.', /* glyphs  8..15 */
    'k', 'l', 'x', 'z', '4', '3', '2', '1', /* glyphs 16..23 */
    '5', '6', '7', '8', '9', '0', '_', '!', /* glyphs 24..31 */
    'g', 'j', 'p', 'q', 'y', 't', 'w', ',', /* glyphs 32..39 */
    'E', 'F', 'G', 'H', 'K', 'L', 'N', 'O', /* glyphs 40..47 */
    'P', 'R', 'S', 'U', 'V', 'X', 'Z', '@', /* glyphs 48..55 */
    'J', 'M', ':', 'W', 'I', 'Y', 'A', 'B', /* glyphs 56..63 */
    'C', 'D', '_', 'T', '"', '+', '-', '=', /* glyphs 64..71 */
    'Q', '%', '/', '?', '(', ')', ' ', '*', /* glyphs 72..79 */
};
