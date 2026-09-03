#ifndef CONKER_N_AUDIO_LIST_H
#define CONKER_N_AUDIO_LIST_H
#include <PR/libaudio.h>

/* SDK list operations as scoped C blocks, matching Conker inline use. */
#define CONKER_AUDIO_LINK(element, after) { \
    ALLink *linkNode = (element); \
    ALLink *linkAfter = (after); \
    linkNode->next = linkAfter->next; \
    linkNode->prev = linkAfter; \
    if (linkAfter->next) { \
        linkAfter->next->prev = linkNode; \
    } \
    linkAfter->next = linkNode; \
}

#define CONKER_AUDIO_UNLINK(element) { \
    ALLink *unlinkNode = (element); \
    if (unlinkNode->next) { \
        unlinkNode->next->prev = unlinkNode->prev; \
    } \
    if (unlinkNode->prev) { \
        unlinkNode->prev->next = unlinkNode->next; \
    } \
}

#endif
