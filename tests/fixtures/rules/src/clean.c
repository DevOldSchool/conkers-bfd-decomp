#include "shared.h"

/*
 * Sums a table with stride indexing; uses the header's global and type.
 */
int clean_sum(Shared *shared, int *table, int k) {
    int total;

    total = table[k * 3 + 0] + table[k * 3 + 1];
    if (shared->count != 0) {
        total += gSharedCount;
    }
    while (total > 100) {
        total -= 100;
    }
    return total;
}

/* Reads a hardware register at a literal address. */
unsigned int clean_read_status(void) {
    return *(volatile unsigned int *)0xA4600010;
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_00000000 CURRENT (12) */
int parked_offset(unsigned char *p) {
    return *(int *)(p + 0x10);
}
#endif
