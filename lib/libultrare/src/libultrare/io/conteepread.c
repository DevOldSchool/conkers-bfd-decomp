#include <PR/os_internal.h>
#include <PR/rcp.h>
#include <io/controller.h>
#include <io/siint.h>

/* Rare's overlay reuses the game's existing PIF RAM allocation. */
extern OSPifRam __conker_game_eepPifRam;

#define CONT_RANGE_ERROR -1

static void __osPackEepReadData(u8 address);

s32 osEepromRead(OSMesgQueue *mq, u8 address, u8 *buffer)
{
    s32 ret = 0;
    s32 i = 0;
    u16 type;
    u8 *ptr;
    OSContStatus sdata;
    __OSContEepromFormat eepromformat;

    ptr = (u8 *)&__conker_game_eepPifRam.ramarray;
    __osSiGetAccess();
    ret = __osEepStatus(mq, &sdata);
    type = sdata.type & (CONT_EEPROM | CONT_EEP16K);

    if (ret == 0) {
        switch (type) {
        case CONT_EEPROM:
            if (address >= EEPROM_MAXBLOCKS) {
                ret = CONT_RANGE_ERROR;
            }
            break;
        case CONT_EEPROM | CONT_EEP16K:
            if (address >= EEP16K_MAXBLOCKS) {
                ret = CONT_RANGE_ERROR;
            }
            break;
        default:
            ret = CONT_NO_RESPONSE_ERROR;
        }
    }

    if (ret != 0) {
        __osSiRelAccess();
        return ret;
    }

    while (sdata.status & CONT_EEPROM_BUSY) {
        __osEepStatus(mq, &sdata);
    }

    __osPackEepReadData(address);
    ret = __osSiRawStartDma(OS_WRITE, &__conker_game_eepPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &__conker_game_eepPifRam);
    __osContLastCmd = CONT_CMD_READ_EEPROM;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    for (i = 0; i < MAXCONTROLLERS; i++) {
        ptr++;
    }

    eepromformat = *(__OSContEepromFormat *)ptr;
    ret = CHNL_ERR(eepromformat);

    if (ret == 0) {
        for (i = 0; i < ARRLEN(eepromformat.data); i++) {
            *buffer++ = eepromformat.data[i];
        }
    }
    __osSiRelAccess();
    return ret;
}

static void __osPackEepReadData(u8 address)
{
    u8 *ptr = (u8 *)&__conker_game_eepPifRam.ramarray;
    __OSContEepromFormat eepromformat;
    s32 i;

    __conker_game_eepPifRam.pifstatus = CONT_CMD_EXE;

    eepromformat.txsize = CONT_CMD_READ_EEPROM_TX;
    eepromformat.rxsize = CONT_CMD_READ_EEPROM_RX;
    eepromformat.cmd = CONT_CMD_READ_EEPROM;
    eepromformat.address = address;

    for (i = 0; i < MAXCONTROLLERS; i++) {
        *ptr++ = 0;
    }

    *(__OSContEepromFormat *)ptr = eepromformat;
    ptr += sizeof(__OSContEepromFormat);
    ptr[0] = CONT_CMD_END;
}
