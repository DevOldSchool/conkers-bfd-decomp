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

typedef struct VolatileChain {
    VolatileOwner *owner;
} VolatileChain;

/* A dereferenced base cannot be resolved: the member name decides. */
int fix_volatile_deref(VolatileOwner **pp) {
    return (*pp)->flags;
}

/* Nor can a member chain. */
int fix_volatile_chain(VolatileChain *chain) {
    return chain->owner->flags;
}

/* `else p = b;` is a statement, not a declaration of p. */
int fix_declared_after_else(VolatileOwner *a, VolatileOwner *b, int c) {
    VolatileOwner *p;

    if (c) {
        p = a;
    } else
        p = b;
    return p->flags;
}

/* `return a;` is a statement, not a declaration of a. */
int fix_declared_after_return(VolatileOwner *a) {
    if (!a) {
        return a;
    }
    return a->flags;
}

/* Offsets past a scalar's size, and byte views of a pointer, are fixed offsets. */
int fix_scalar_offsets(int c) {
    int word;

    if (c) {
        word = 1;
    } else
        word = 2;
    return *(int *)((unsigned char *)&word + 0x20) + ((unsigned char *)&gWordPtr)[1] + ((unsigned char *)&word)[3];
}

#ifdef SHARED_FEATURE
/* A macro from an included header selects this branch. */
int fix_header_macro(void) {
    return 1;
}
#else
int fix_header_macro_missing(void) {
    return 0;
}
#endif

#define FIXTURE_LOCAL
#undef FIXTURE_LOCAL
#ifdef FIXTURE_LOCAL
int fix_after_undef_missing(void) {
    return 0;
}
#else
/* #undef takes the macro away again. */
int fix_after_undef(void) {
    return 1;
}
#endif
