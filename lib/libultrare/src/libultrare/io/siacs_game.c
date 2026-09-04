#include <PR/os_internal.h>

/* The retail overlay uses existing main SI state and a distinct game buffer.
 * External declarations preserve those references without attributing an
 * unproved surrounding BSS section to this text object.
 */
extern u32 __osSiAccessQueueEnabled;
extern OSMesgQueue __osSiAccessQueue;
extern OSMesg __conker_game_siAccessBuf[];

void __osSiCreateAccessQueue(void)
{
    __osSiAccessQueueEnabled = 1;
    osCreateMesgQueue(&__osSiAccessQueue, __conker_game_siAccessBuf, 1);
    osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
}

void __osSiGetAccess(void)
{
    OSMesg dummyMesg;
    if (!__osSiAccessQueueEnabled) {
        __osSiCreateAccessQueue();
    }
    osRecvMesg(&__osSiAccessQueue, &dummyMesg, OS_MESG_BLOCK);
}

void __osSiRelAccess(void)
{
    osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
}
