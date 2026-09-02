#include <PR/os.h>

/*
 * Conker's PAL low-resolution, 16-bit, antialiased, non-interlaced mode.
 * Its field timings differ from the stock 2.0I-L osViModePalLan1 object.
 */
OSViMode osViModePalLan1 = {
    OS_VI_PAL_LAN1,
    {
        0x0000311E,
        0x00000140,
        0x0404233A,
        0x00000271,
        0x00150C69,
        0x0C6F0C6E,
        0x00800300,
        0x00000200,
        0x00000000,
    },
    {
        {
            0x00000280,
            0x00000400,
            0x005F0239,
            0x0009026B,
            0x00000002,
        },
        {
            0x00000280,
            0x00000400,
            0x005F0239,
            0x0009026B,
            0x00000002,
        },
    },
};
