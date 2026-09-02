#include <PR/ultratypes.h>

/*
 * Complete Conker copy of xprintf.o's initialized data section. Its read-only
 * data is kept in a separate build object because it is interleaved with the
 * target's broader raw data region.
 */
char __conkerXprintfSpaces[] = "                                ";
char __conkerXprintfZeroes[] = "00000000000000000000000000000000";
