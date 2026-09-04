#include <PR/ultratypes.h>

/* Conker US 0x2070:0x20D0. The disabled output callback remains callable,
 * and the wrapper clears the external debugger halfword before formatting.
 */
extern s16 __conker_print_state;
extern void *__conker_runtime_proutSyncPrintf(void *, const char *, u32);
extern s32 _Printf(void *(*output)(void *, const char *, u32),
                   void *arg, const char *fmt, char *args);

void *proutSyncPrintf(void *str, const char *buf, u32 n)
{
    return (void *)1;
}

void osSyncPrintf(const char *fmt, ...)
{
    char *args = (char *)&fmt + sizeof(fmt);

    __conker_print_state = 0;
    _Printf(__conker_runtime_proutSyncPrintf, (void *)0, fmt, args);
}
