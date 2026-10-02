#include "types.h"

/*
 * Reviewed source unit: src/main/init_8180.c
 * Boundary evidence: docs/evidence/main_sequence_api_mp3_adapter_boundaries.md
 *
 * TODO: Implement these source-unit functions:
 * - func_80008180
 * - func_800084D8
 * - func_8000853C
 * - func_80008570
 * - func_800085B8
 * - func_800085F8
 * - func_8000862C
 * - func_80008660
 * - func_800086FC
 * - func_80008744
 * - func_80008790
 * - func_80008824
 * - func_8000886C
 * - func_800088F0
 * - func_80008988
 * - func_80008A4C
 * - func_80008A94
 * - func_80008B2C
 * - func_80008B60
 * - func_80008BC0
 * - func_80008C04
 * - func_80008C6C
 * - func_80008CE8
 * - func_80008EE0
 * - func_80008F24
 * - func_80008F58
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008180.s")
typedef struct SequencePlayer SequencePlayer;

extern SequencePlayer *D_8003C900[];
s32 func_80017A80(SequencePlayer *player);
void func_80017AA0(SequencePlayer *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_800084D8 CURRENT (277) */
void func_800084D8(s32 arg0) {
    SequencePlayer **player;

    player = &D_8003C900[arg0 & 0xFF];
    if (func_80017A80(*player) == 0 || func_80017A80(*player) == 3) {
        func_80017AA0(*player);
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800084D8 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_800084D8.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000853C CURRENT (225) */
s32 func_8000853C(s32 arg0) {
    arg0 &= 0xFF;
    return func_80017A80(D_8003C900[arg0]);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000853C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_8000853C.s")
void func_80017AF0(SequencePlayer *player, void *value);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008570 CURRENT (225) */
void func_80008570(s32 arg0, void *arg1) {
    s32 index;

    index = arg0 & 0xFF;
    func_80017AF0(D_8003C900[index], arg1);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008570 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008570.s")
void func_800085A4(s32 arg0, s32 arg1, s32 arg2) {
}
void func_80017B04(SequencePlayer *, s32, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_800085B8 CURRENT (892) */
void func_800085B8(s32 arg0, s32 channel, s32 value) {
    func_80017B04(D_8003C900[arg0 & 0xFF], channel, value & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800085B8 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_800085B8.s")
void func_80017BB8(SequencePlayer *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_800085F8 CURRENT (225) */
void func_800085F8(s32 arg0, s32 channel) {
    s32 index;

    index = arg0 & 0xFF;
    func_80017BB8(D_8003C900[index], channel);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800085F8 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_800085F8.s")
void func_80017C00(SequencePlayer *, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000862C CURRENT (225) */
void func_8000862C(s32 arg0, s32 channel) {
    func_80017C00(D_8003C900[arg0 & 0xFF], channel);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000862C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_8000862C.s")
void func_80017C68(SequencePlayer *, s32, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008660 CURRENT (2427) */
void func_80008660(s32 arg0, s32 channel, s32 volume, s32 duration) {
    if (duration > 0) {
        duration = (duration * 10) / 60;
        if (duration == 0) {
            duration = 1;
        } else if (duration >= 0x80) {
            duration = 0x7F;
        }
    } else {
        duration = 0;
    }
    func_80017C68(D_8003C900[arg0 & 0xFF], channel & 0xFF,
                  volume & 0xFF, duration & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008660 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008660.s")
void func_80017CE0(SequencePlayer *, s32, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_800086FC CURRENT (1309) */
void func_800086FC(s32 arg0, s32 channel, s32 value) {
    func_80017CE0(D_8003C900[arg0 & 0xFF], channel & 0xFF, value & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800086FC */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_800086FC.s")
void func_80017D80(SequencePlayer *, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008744 CURRENT (1307) */
void func_80008744(s32 arg0, s32 channel, s32 value) {
    func_80017D80(D_8003C900[arg0 & 0xFF], channel & 0xFF, value & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008744 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008744.s")
void func_80008660(s32, s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008790 CURRENT (1265) */
void func_80008790(s32 arg0, s32 channels, s32 arg2, s32 duration) {
    s32 channel;

    arg0 &= 0xFF;
    arg2 &= 0xFF;
    for (channel = 0; channel != 0x10; channel++) {
        if ((1 << channel) & channels) {
            func_80008660(arg0 & 0xFF, channel & 0xFF, arg2 & 0xFF, duration);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008790 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008790.s")
void func_80017D30(SequencePlayer *, s32, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008824 CURRENT (1309) */
void func_80008824(s32 arg0, s32 channel, s32 value) {
    func_80017D30(D_8003C900[arg0 & 0xFF], channel & 0xFF, value & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008824 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008824.s")
void func_80008824(s32, s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_8000886C CURRENT (695) */
void func_8000886C(s32 arg0, s32 channels, s32 arg2) {
    s32 channel;
    u8 player;
    u8 volume;

    player = arg0;
    volume = arg2;
    for (channel = 0; channel != 0x10; channel++) {
        if ((1 << channel) & channels) {
            func_80008824(player, channel & 0xFF, volume);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_8000886C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_8000886C.s")
void func_800085F8(s32, s32);
void func_8000862C(s32, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_800088F0 CURRENT (1200) */
void func_800088F0(s32 arg0, s32 channels, s32 enabled) {
    s32 player;
    s32 channel;

    player = arg0 & 0xFF;
    for (channel = 0; channel != 0x10; channel++) {
        if ((1 << channel) & channels) {
            if (enabled != 0) {
                func_8000862C(player & 0xFF, channel);
            } else {
                func_800085F8(player & 0xFF, channel);
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_800088F0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_800088F0.s")
typedef struct {
    u8 pad0[0xD];
    u8 fadeVolume;
    u8 padE[0x2E];
} SequenceChannel;

struct SequencePlayer {
    u8 pad0[0x30];
    u16 channelMask;
    u8 pad32[0x2E];
    SequenceChannel *channels;
};

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008988 CURRENT (805) */
void func_80008988(s32 arg0, s32 channels, s32 enabled) {
    s32 channel;
    s32 player;

    player = arg0 & 0xFF;
    for (channel = 0; channel != 0x10; channel++) {
        if ((1 << channel) & channels) {
            if (enabled != 0) {
                D_8003C900[player]->channelMask |= channels;
            } else {
                D_8003C900[player]->channelMask &= channels ^ 0xFFFF;
            }
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008988 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008988.s")
#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008A4C CURRENT (955) */
u8 func_80008A4C(s32 arg0, s32 channel) {
    return D_8003C900[arg0 & 0xFF]->channels[channel & 0xFF].fadeVolume;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008A4C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008A4C.s")
void func_80017E4C(SequencePlayer *, u8, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008A94 CURRENT (1625) */
void func_80008A94(s32 arg0, s32 channels, s32 value) {
    s32 channel;

    for (channel = 0; channel != 0x10; channel++) {
        if ((1 << channel) & channels) {
            func_80017E4C(D_8003C900[arg0 & 0xFF], channel & 0xFF, value & 0xFF);
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008A94 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008A94.s")
s32 func_80017EC0(SequencePlayer *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008B2C CURRENT (225) */
s32 func_80008B2C(s32 arg0) {
    return func_80017EC0(D_8003C900[arg0 & 0xFF]);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008B2C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008B2C.s")
void func_80017F10(SequencePlayer *, u8, u8, u8, s32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008B60 CURRENT (2449) */
void func_80008B60(s32 arg0, s32 bus, s32 param, s32 section, s32 value) {
    func_80017F10(D_8003C900[arg0 & 0xFF], bus & 0xFF, param & 0xFF,
                  section & 0xFF, value);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008B60 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008B60.s")
void func_80017DF0(SequencePlayer *, f32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008BC0 CURRENT (225) */
void func_80008BC0(s32 arg0, f32 arg1, f32 arg2) {
    func_80017DF0(D_8003C900[arg0 & 0xFF], arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008BC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008BC0.s")
/* ALCSeq and ALCSeqMarker prefixes and sizes from the compact-sequence API. */
typedef struct {
    void *base;
    u8 pad4[0xF4];
} SequenceData;

typedef struct {
    u32 validTracks;
    s32 lastTicks;
    u8 pad8[0xE4];
} SequenceMarker;

extern SequenceData D_8003CA58[];
extern SequenceMarker D_8003CD48[][8];
void func_80018790(SequenceData *, SequenceMarker *, u32, u32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008C04 CURRENT (1868) */
void func_80008C04(s32 arg0, s32 count, s32 first) {
    func_80018790(&D_8003CA58[arg0 & 0xFF], D_8003CD48[arg0 & 0xFF],
                  count & 0xFF, first);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008C04 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008C04.s")
void func_800186DC(SequenceData *, SequenceMarker *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008C6C CURRENT (595) */
void func_80008C6C(s32 arg0, s32 marker) {
    func_800186DC(&D_8003CA58[arg0 & 0xFF],
                  &D_8003CD48[arg0 & 0xFF][marker & 0xFF]);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008C6C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008C6C.s")
typedef struct {
    u8 *address;
    s32 length;
} SequenceFileEntry;

typedef struct {
    s16 revision;
    s16 count;
    SequenceFileEntry entries[1];
} SequenceFile;

s32 func_80003C40(s32, s32, s32, s32);
void func_80004074(s32);
s32 func_80004514(s32, void *, u32, s32);
void func_80017B30(SequencePlayer *);
void func_80017F80(SequenceData *, u8 *);
void func_80018C60(SequencePlayer *);
void func_80018CB0(SequencePlayer *, SequenceData *);
extern u16 D_8003C910[];
extern u16 D_8003CA3C[];
extern s32 D_8003CA48[];
extern SequenceFile *D_8003CD40;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008CE8 CURRENT (1867) */
s32 func_80008CE8(s32 arg0, s32 sequence) {
    SequencePlayer **player;
    u32 count;
    u16 *current;
    s32 *buffer;
    u16 *length;
    s32 address;
    SequenceData *data;

    player = &D_8003C900[arg0 & 0xFF];
    count = 0;
    func_80018C60(*player);
    while (func_80017A80(*player) != 0 && count != 2000000) {
        count++;
    }
    if (count >= 2000000U) {
        func_80018C60(*player);
        while (func_80017A80(*player) != 0 && count < 4000000U) {
            count++;
        }
    }
    current = &D_8003CA3C[arg0 & 0xFF];
    if (sequence != *current) {
        buffer = &D_8003CA48[arg0 & 0xFF];
        if (*buffer != 0) {
            func_80004074(*buffer);
            *buffer = 0;
        }
        length = &D_8003C910[sequence];
        address = (s32)D_8003CD40->entries[sequence].address;
        *buffer = func_80003C40(*length, 0xFF, 2, 2);
        if (*buffer == 0) {
            return -1;
        }
        func_80004514(address, (void *)*buffer, (*length + 0xF) & ~0xF, 1);
        *current = sequence;
    }
    data = &D_8003CA58[arg0 & 0xFF];
    func_80017F80(data, (u8 *)D_8003CA48[arg0 & 0xFF]);
    func_80018CB0(*player, data);
    func_80017B30(*player);
    return 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008CE8 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008CE8.s")
void func_80018D00(SequencePlayer *, s16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008EE0 CURRENT (295) */
void func_80008EE0(s32 arg0, s32 volume) {
    func_80018D00(D_8003C900[arg0 & 0xFF], (s16)volume);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008EE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008EE0.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008F24 CURRENT (225) */
void func_80008F24(s32 arg0) {
    func_80018C60(D_8003C900[arg0 & 0xFF]);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008F24 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008F24.s")
void func_80018D50(SequencePlayer *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008F58 CURRENT (225) */
void func_80008F58(s32 arg0) {
    func_80018D50(D_8003C900[arg0 & 0xFF]);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008F58 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008F58.s")
