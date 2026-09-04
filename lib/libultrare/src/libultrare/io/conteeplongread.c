#include <PR/os_internal.h>
#include <io/controller.h>

/* Rare waits for the game's pending EEPROM transaction before a long read. */
extern s32 __conker_eeprom_wait(s32 mode);

s32 osEepromLongRead(OSMesgQueue *mq, u8 address, u8 *buffer, s32 length)
{
    s32 ret = 0;

    while (__conker_eeprom_wait(1) != 0) {
    }

    while (length > 0) {
        ERRCK(osEepromRead(mq, address, buffer));
        length -= EEPROM_BLOCK_SIZE;
        address++;
        buffer += EEPROM_BLOCK_SIZE;
    }

    return ret;
}
