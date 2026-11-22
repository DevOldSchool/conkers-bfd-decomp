#include "shared.h"

typedef struct VolatileOwner {
    volatile int flags;
} VolatileOwner;

typedef struct Plain {
    int flags;
} Plain;

extern unsigned char D_80002000[];

/* A volatile parameter is a carrier like a volatile local. */
int fix_volatile_param(volatile int value) {
    return value;
}

/* A cast in the initializer does not make the local a hardware access. */
int fix_volatile_initializer(void) {
    volatile int x = (int)0;

    return x;
}

/* Only the struct that declares the volatile member counts. */
int fix_volatile_member(VolatileOwner *owner, Plain *plain) {
    return plain->flags + owner->flags;
}

/* A block-scope extern belongs to its own function. */
int fix_block_extern(void) {
    extern int gSharedCount;

    return gSharedCount;
}

/* Sees gSharedCount through the header only. */
int fix_after_block_extern(void) {
    return gSharedCount;
}

#if 0
int fix_disabled(void) {
    return 0;
}
#else
/* The live branch of #if 0 / #else. */
int fix_live_branch(void) {
    return 1;
}
#endif

#ifdef FIXTURE_UNDEFINED_MACRO
int fix_counted_once(void) {
    return 0;
}
#else
/* Counted once although both branches define it. */
int fix_counted_once(void) {
    return 1;
}
#endif

/* An indexed byte cast and an offset address are fixed offsets; a byte view of a scalar is not. */
int fix_offset_forms(void *p, int word) {
    return ((unsigned char *)p)[0x58] + *((unsigned char *)&D_80002000 + 4) + ((unsigned char *)&word)[3];
}
