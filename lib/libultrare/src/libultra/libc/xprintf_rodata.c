#include <PR/ultratypes.h>

/*
 * Complete Conker copy of xprintf.o's read-only data. It is emitted in a
 * dedicated initialized-data object so it can retain its reviewed position
 * among the target's still-raw data sections. The switch table stores the
 * target's 0x10000000 execution aliases because the Rare formatting text
 * remains in the independently generated raw map.
 */
char __conkerXprintfQualifiers[] = "hlL";
char __conkerXprintfFlags[] = {' ', '+', '-', '#', '0', '\0'};
u32 __conkerXprintfFlagBits[] = {1, 2, 4, 8, 16, 0};
u32 __conkerXprintfJumpTable[] = {
    0x10002A98, 0x10002D7C, 0x10002A98, 0x10002D7C,
    0x10002D7C, 0x10002D7C, 0x10002D7C, 0x10002D7C,
    0x10002D7C, 0x10002D7C, 0x10002D7C, 0x10002D7C,
    0x10002D7C, 0x10002D7C, 0x10002D7C, 0x10002D7C,
    0x10002D7C, 0x10002D7C, 0x10002D7C, 0x10002944,
    0x10002D7C, 0x10002D7C, 0x10002D7C, 0x10002D7C,
    0x10002D7C, 0x10002D7C, 0x10002D7C, 0x10002D7C,
    0x10002D7C, 0x10002D7C, 0x10002798, 0x100027D0,
    0x10002A98, 0x10002A98, 0x10002A98, 0x10002D7C,
    0x100027D0, 0x10002D7C, 0x10002D7C, 0x10002D7C,
    0x10002D7C, 0x10002C00, 0x10002944, 0x10002CD0,
    0x10002D7C, 0x10002D7C, 0x10002D18, 0x10002D7C,
    0x10002944, 0x10002D7C, 0x10002D7C, 0x10002944,
};
