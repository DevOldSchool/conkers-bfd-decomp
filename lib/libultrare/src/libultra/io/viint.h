#ifndef _VIINT_H_
#define _VIINT_H_

#include <PR/os_internal.h>

/* Video standards reported by osTvType. */
#define OS_TV_TYPE_PAL  0
#define OS_TV_TYPE_NTSC 1
#define OS_TV_TYPE_MPAL 2

/* Internal VI state: blank the display until a frame buffer is installed. */
#define VI_STATE_BLACK 0x20

/* Scaling state retained by each VI context. */
typedef struct {
    f32 factor;
    u16 offset;
    u32 scale;
} __OSViScale;

/* State shared by the public VI calls and the VI manager. */
typedef struct {
    u16 state;
    u16 retraceCount;
    void *framep;
    OSViMode *modep;
    u32 control;
    OSMesgQueue *msgq;
    OSMesg msg;
    __OSViScale x;
    __OSViScale y;
} __OSViContext;

extern __OSViContext *__osViCurr;
extern __OSViContext *__osViNext;

extern void __osViInit(void);
extern void __osViSwapContext(void);

#endif /* _VIINT_H_ */
