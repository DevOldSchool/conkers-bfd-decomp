#ifndef CONKER_LIBULTRA_OS_H
#define CONKER_LIBULTRA_OS_H

#include "types.h"
#include "PR/os_message.h"

/* Message-queue entry points in the main executable, not yet named. */
s32 func_80023440(OSMesgQueue *, OSMesg *, s32);
s32 func_80023580(OSMesgQueue *, OSMesg, s32);
void func_80023790(OSMesgQueue *, OSMesg *, s32);
void func_800237C0(s32, OSMesgQueue *, OSMesg);

#endif
