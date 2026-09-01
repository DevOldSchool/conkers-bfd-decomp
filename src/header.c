#include "types.h"

typedef struct N64RomHeader {
    u32 piBsdDomain1;
    u32 clockRate;
    u32 entrypoint;
    u32 revision;
    u32 checksum1;
    u32 checksum2;
    u32 unknown18;
    u32 unknown1C;
    char internalName[20];
    u32 unknown34;
    u32 cartridge;
    char cartridgeId[2];
    char countryCode;
    u8 version;
} N64RomHeader;

typedef char N64RomHeaderSizeCheck[(sizeof(N64RomHeader) == 0x40) ? 1 : -1];

#if defined(PROFILE_US)
#define ROM_CHECKSUM_1 0x30C7AC50
#define ROM_CHECKSUM_2 0x7704072D
#define ROM_COUNTRY_CODE 'E'
#elif defined(PROFILE_EU)
#define ROM_CHECKSUM_1 0x373F5889
#define ROM_CHECKSUM_2 0x9A6CA80A
#define ROM_COUNTRY_CODE 'P'
#else
#error "A supported Conker ROM profile is required"
#endif

N64RomHeader gN64RomHeader = {
    0x80371240,
    0x0000000F,
    0x80001000,
    0x00001447,
    ROM_CHECKSUM_1,
    ROM_CHECKSUM_2,
    0x00000000,
    0x00000000,
    "CONKER BFD          ",
    0x00000000,
    0x0000004E,
    { 'F', 'U' },
    ROM_COUNTRY_CODE,
    0x00,
};
