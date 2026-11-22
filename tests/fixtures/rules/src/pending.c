#include "shared.h"

extern int D_80001234;

typedef struct Shared {
    int count;
} Shared;

typedef struct Local {
    unsigned char kind;
    unsigned char pad1[3];
    volatile int state;
} Local;

int func_80001000(void *arg0) {
    return *(int *)((unsigned char *)arg0 + 0x58) + D_80001234;
}

int func_80001040(unsigned char *arg0) {
    volatile int mask;

    mask = *(int *)(arg0 + 0x10);
    if (mask) {
    }
    mask = mask;
    return mask * 1;
}

int func_80001080(Local *local, Shared *shared) {
    if (local->state)
        return local->pad1[0];
    return shared->count + 0;
}

/* Uses a block-scope extern. */
int func_800010C0(void) {
    extern int D_80005678;

    do {
        D_80005678++;
    } while (0);
    ;
    return D_80005678;
}

#if 0
int Disabled(void) {
    return 0;
}
#endif
