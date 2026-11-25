#include "types.h"

/* Original scene choices select the first creation row.
 * Its count-eight callback proves eight float pairs.
 * Five eight-entry rows fill the storage up to 8008CFA0; only the first row's
 * consumption is traced, and no gameplay activation is asserted.
 * Evidence: docs/evidence/data-layout/us_native_fp_control.md
 */

typedef struct { s16 creator, count; } Game36680CreationChoice;

Game36680CreationChoice D_8008CF00[5][8] = {
    {
        { 0, 1 },
        { 0, 2 },
        { 4, 0 },
        { 0, 4 },
        { 4, 1 },
        { 0, 6 },
        { 4, 2 },
        { 0, 8 },
    },
    {
        { 1, 500 },
        { 1, 250 },
        { 1, 125 },
        { 1, 62 },
        { 1, 46 },
        { 1, 31 },
        { 1, 15 },
        { 0, 1 },
    },
    {
        { 2, 1 },
        { 2, 2 },
        { 2, 3 },
        { 2, 4 },
        { 2, 5 },
        { 2, 6 },
        { 2, 7 },
        { 0, 1 },
    },
    {
        { 3, 1 },
        { 3, 2 },
        { 3, 3 },
        { 3, 4 },
        { 3, 5 },
        { 3, 6 },
        { 3, 7 },
        { 0, 1 },
    },
    {
        { 5, 1 },
        { 5, 2 },
        { 5, 3 },
        { 5, 4 },
        { 5, 5 },
        { 5, 6 },
        { 0, 1 },
        { 0, 3 },
    },
};
