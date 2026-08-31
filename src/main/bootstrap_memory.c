#include "types.h"

#if PROFILE_US
#define clear_bootstrap_region func_80001420
#define bootstrap_region D_80043B40
#else
#define clear_bootstrap_region func_800014B0
#define bootstrap_region D_80043ED0
#endif

extern char bootstrap_region;

void clear_bootstrap_region(void) {
    s32 count;
    s32 *tmp;

    for (tmp = (s32 *)&bootstrap_region, count = 4064;
         (unsigned int)tmp < (unsigned int)&bootstrap_region + count;
         tmp++) {
        *tmp = 0;
    }
}
