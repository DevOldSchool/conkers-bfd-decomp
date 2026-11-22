#ifndef SHARED_H
#define SHARED_H

typedef struct Shared {
    int count;
    float scale;
} Shared;

#define SHARED_FEATURE 1

extern int gSharedCount;
extern unsigned int *gWordPtr;

#endif
