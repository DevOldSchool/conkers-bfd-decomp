#include "types.h"

/*
 * Reviewed source unit: src/main/init_8180.c
 * Boundary evidence: docs/evidence/boundaries/main/main_sequence_api_mp3_adapter_boundaries.md
 */

typedef struct SequencePlayer SequencePlayer;
typedef struct {
    u8 *address;
    s32 length;
} SequenceFileEntry;

typedef struct {
    s16 revision;
    s16 count;
    SequenceFileEntry entries[1];
} SequenceFile;

typedef struct AudioHeap AudioHeap;
typedef struct AudioBank AudioBank;

typedef struct {
    s16 revision;
    s16 count;
    AudioBank *banks[1];
} AudioBankFile;

typedef struct {
    s32 maxVoices;
    s32 maxPhysicalVoices;
    s32 maxUpdates;
    s32 maxFxBuses;
    void *dma;
    void *fetch;
    void *release;
    void *retain;
    void *releaseNow;
    void *waveBase;
    AudioHeap *heap;
    s32 outputRate;
    u8 fxTypes[2];
    u8 pad32[2];
    s32 *params[2];
} AudioDriverConfig;

typedef struct {
    u32 frequency;
    u32 frames;
    s32 maxCommands;
} AudioDeviceConfig;

typedef struct {
    s32 maxVoices;
    s32 maxEvents;
    u8 maxChannels;
    u8 debugFlags;
    u8 padA[2];
    AudioHeap *heap;
    void *initOsc;
    void *updateOsc;
    void *stopOsc;
} SequencePlayerConfig;

typedef struct {
    s32 maxStates;
    s32 maxEvents;
    s32 maxSounds;
    AudioHeap *heap;
    void *waveBase;
    u16 maxVolumes;
} AudioSoundConfig;

void func_800046E4(u32, void *, u32);
void func_80008F90(AudioDriverConfig *, s32, AudioDeviceConfig *);
void func_80012820(AudioHeap *, u8 *, s32);
void *func_80012844(u8 *, s32, AudioHeap *, s32, s32);
void func_800128D0(SequenceFile *, u8 *);
void func_80012934(AudioBankFile *, u8 *, s32);
void func_800131FC(SequencePlayerConfig *, s32);
void func_80013320(SequencePlayer *, SequencePlayerConfig *);
void func_80015550(SequencePlayer *, AudioBank *);
void func_800155A0(AudioSoundConfig *);
void func_80017870(u8);
void func_80017944(s32, s32);
void *func_8502B020(s32 *, s32, ...);
s32 func_8502B8E0(void *, s32, s32, ...);
s32 func_8502B9B4(s32, ...);
extern AudioBank *D_8003E368;
extern AudioHeap D_8003E370;
extern u8 D_80044B20[];
s32 func_80003C40(s32, s32, s32, s32);
void func_80004074(void *);
extern SequencePlayer *D_8003C900[];
extern u8 D_8003C90C[];
extern u16 D_8003C910[];
extern u16 D_8003CA3C[];
extern s32 D_8003CA48[];
extern SequenceFile *D_8003CD40;

void func_80008180(void) {
    AudioSoundConfig soundConfig;
    s32 bankSize;
    u32 bankAddress;
    AudioDriverConfig driverConfig;
    s32 sequenceSize;
    SequencePlayerConfig playerConfig;
    AudioDeviceConfig deviceConfig;
    AudioBankFile *bankFile;
    SequenceFile *header;
    u32 sequenceAddress;
    u8 *waveBase;
    s32 i;

    func_80012820(&D_8003E370, D_80044B20, 0x3E000);
    driverConfig.maxVoices = 0x2C;
    driverConfig.maxPhysicalVoices = 0x28;
    driverConfig.maxUpdates = 0x40;
    driverConfig.maxFxBuses = 2;
    driverConfig.dma = 0;
    driverConfig.fxTypes[0] = 6;
    driverConfig.fxTypes[1] = 6;
    driverConfig.outputRate = 0;
    driverConfig.heap = &D_8003E370;
    deviceConfig.frequency = 0x5604;
    deviceConfig.frames = 1;
    deviceConfig.maxCommands = 0xC00;
    driverConfig.waveBase = func_8502B020(0, 2, 0x17, 2);
    func_80008F90(&driverConfig, 0xC, &deviceConfig);
    bankSize = func_8502B9B4(2, 0x17, 0);
    bankFile = (AudioBankFile *)func_80003C40(bankSize, 0xFF, 2, 0);
    func_8502B8E0(bankFile, bankSize, 2, 0x17, 0);
    bankAddress = (u32)func_8502B020(0, 2, 0x17, 1);
    waveBase = func_8502B020(0, 2, 0x17, 2);
    func_80012934(bankFile, waveBase, bankAddress);
    D_8003E368 = bankFile->banks[0];
    sequenceAddress = (u32)func_8502B020(0, 2, 0x17, 3);
    header = (SequenceFile *)func_80003C40(0x10, 1, 2, 0);
    func_800046E4(sequenceAddress, header, 0x10);
    sequenceSize = header->count * 8 + 4;
    func_80004074(header);
    D_8003CD40 = (SequenceFile *)func_80003C40(sequenceSize, 0xFF, 2, 0);
    func_800046E4(sequenceAddress, D_8003CD40, (sequenceSize + 0xF) & ~0xF);
    func_800128D0(D_8003CD40, (u8 *)sequenceAddress);
    for (i = 0; i < 150; i++) {
        D_8003C910[i] = D_8003CD40->entries[i].length;
        if (D_8003C910[i] & 1) {
            D_8003C910[i]++;
        }
    }
    playerConfig.maxVoices = 0x2C;
    playerConfig.maxEvents = 0x68;
    playerConfig.debugFlags = 0;
    playerConfig.maxChannels = 0x10;
    playerConfig.heap = &D_8003E370;
    func_800131FC(&playerConfig, 0x58);
    i = 0;
    do {
        D_8003CA3C[i] = 0xFFFF;
        D_8003CA48[i] = 0;
        D_8003C900[i] = func_80012844(0, 0, &D_8003E370, 1, 0x90);
        func_80013320(D_8003C900[i], &playerConfig);
        func_80015550(D_8003C900[i], bankFile->banks[0]);
        i++;
    } while ((SequencePlayer **)D_8003C90C != &D_8003C900[i]);
    soundConfig.maxEvents = 0x40;
    soundConfig.maxStates = 0x40;
    soundConfig.maxSounds = 0x14;
    soundConfig.maxVolumes = 8;
    soundConfig.heap = &D_8003E370;
    soundConfig.waveBase = waveBase;
    func_800155A0(&soundConfig);
    func_80017870(4);
    func_80017944(0, 2);
    func_80017944(1, 2);
}

s32 func_80017A80(SequencePlayer *player);
void func_80017AA0(SequencePlayer *);

void func_800084D8(u8 arg0) {
    if (func_80017A80(D_8003C900[arg0]) == 0 ||
        func_80017A80(D_8003C900[arg0]) == 3) {
        func_80017AA0(D_8003C900[arg0]);
    }
}

s32 func_8000853C(u8 arg0) {
    return func_80017A80(D_8003C900[arg0]);
}
void func_80017AF0(SequencePlayer *player, void *value);

void func_80008570(u8 arg0, void *arg1) {
    s32 index;

    index = arg0;
    func_80017AF0(D_8003C900[index], arg1);
}
void func_800085A4(s32 arg0, s32 arg1, s32 arg2) {
}
void func_80017B04(SequencePlayer *, s32, u8);

void func_800085B8(u8 arg0, s32 channel, u8 value) {
    func_80017B04(D_8003C900[arg0], channel, value);
}
void func_80017BB8(SequencePlayer *, s32);

void func_800085F8(u8 arg0, s32 channel) {
    s32 index;

    index = arg0;
    func_80017BB8(D_8003C900[index], channel);
}
void func_80017C00(SequencePlayer *, s32);

void func_8000862C(u8 arg0, s32 channel) {
    func_80017C00(D_8003C900[arg0], channel);
}
void func_80017C68(SequencePlayer *, s32, u8, u8);

void func_80008660(u8 arg0, u8 channel, u8 volume, s32 duration) {
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
    func_80017C68(D_8003C900[arg0], channel, volume, duration);
}
void func_80017CE0(SequencePlayer *, s32, u8);

void func_800086FC(u8 arg0, u8 channel, u8 value) {
    func_80017CE0(D_8003C900[arg0], channel, value);
}
void func_80017D80(SequencePlayer *, u8, u8);

void func_80008744(u8 arg0, u8 channel, u8 value) {
    func_80017D80(D_8003C900[arg0], channel, value);
}
void func_80008660(u8, u8, u8, s32);

void func_80008790(u8 arg0, s32 channels, u8 arg2, s32 duration) {
    s32 channel;

    for (channel = 0; channel != 0x10; channel++) {
        if ((1 << channel) & channels) {
            func_80008660(arg0, channel, arg2, duration);
        }
    }
}
void func_80017D30(SequencePlayer *, s32, u8);

void func_80008824(u8 arg0, u8 channel, u8 value) {
    func_80017D30(D_8003C900[arg0], channel, value);
}
void func_80008824(u8, u8, u8);

void func_8000886C(u8 arg0, s32 channels, u8 arg2) {
    s32 channel;

    for (channel = 0; channel != 0x10; channel++) {
        if ((1 << channel) & channels) {
            func_80008824(arg0, channel, arg2);
        }
    }
}
void func_800085F8(u8, s32);
void func_8000862C(u8, s32);

void func_800088F0(u8 arg0, s32 channels, s32 enabled) {
    s32 player;
    s32 channel;

    player = arg0;
    for (channel = 0; channel != 0x10; channel++) {
        if ((1 << channel) & channels) {
            if (enabled != 0) {
                func_8000862C(arg0, channel);
            } else {
                func_800085F8(player, channel);
            }
        }
    }
}
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

void func_80008988(u8 arg0, s32 channels, s32 enabled) {
    s32 channel;
    s32 player;

    player = arg0;
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
u8 func_80008A4C(u8 arg0, u8 channel) {
    return D_8003C900[arg0]->channels[channel].fadeVolume;
}
void func_80017E4C(SequencePlayer *, u8, u8);

void func_80008A94(u8 arg0, s32 channels, s32 value) {
    s32 channel;

    for (channel = 0; channel != 0x10; channel++) {
        if ((1 << channel) & channels) {
            func_80017E4C(D_8003C900[arg0], channel, value);
        }
    }
}
s32 func_80017EC0(SequencePlayer *);

s32 func_80008B2C(u8 arg0) {
    return func_80017EC0(D_8003C900[arg0]);
}
void func_80017F10(SequencePlayer *, u8, u8, u8, s32);

void func_80008B60(u8 arg0, u8 bus, u8 param, u8 section, s32 value) {
    func_80017F10(D_8003C900[arg0], bus, param, section, value);
}
void func_80017DF0(SequencePlayer *, f32, f32);

void func_80008BC0(u8 arg0, f32 arg1, f32 arg2) {
    func_80017DF0(D_8003C900[arg0], arg1, arg2);
}
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

void func_80008C04(u8 arg0, u8 count, s32 first) {
    func_80018790(&D_8003CA58[arg0], D_8003CD48[arg0],
                  count, first);
}
void func_800186DC(SequenceData *, SequenceMarker *);

void func_80008C6C(u8 arg0, u8 marker) {
    func_800186DC(&D_8003CA58[arg0],
                  &D_8003CD48[arg0][marker]);
}

s32 func_80004514(s32, void *, u32, s32);
void func_80017B30(SequencePlayer *);
void func_80017F80(SequenceData *, u8 *);
void func_80018C60(SequencePlayer *);
void func_80018CB0(SequencePlayer *, SequenceData *);

s32 func_80008CE8(u8 arg0, s32 sequence) {
    s32 address;
    u32 count;

    count = 0;
    func_80018C60(D_8003C900[arg0]);
    while (func_80017A80(D_8003C900[arg0]) != 0 && count != 2000000) {
        count++;
    }
    if (count >= 2000000U) {
        func_80018C60(D_8003C900[arg0]);
        while (func_80017A80(D_8003C900[arg0]) != 0 && count < 4000000U) {
            count++;
        }
    }
    if (sequence != D_8003CA3C[arg0]) {
        if (D_8003CA48[arg0] != 0) {
            func_80004074((void *)D_8003CA48[arg0]);
            D_8003CA48[arg0] = 0;
        }
        address = (s32)D_8003CD40->entries[sequence].address;
        D_8003CA48[arg0] = func_80003C40(D_8003C910[sequence], 0xFF, 2, 2);
        if (D_8003CA48[arg0] == 0) {
            return -1;
        }
        func_80004514(address, (void *)D_8003CA48[arg0],
                      (D_8003C910[sequence] + 0xF) & ~0xF, 1);
        D_8003CA3C[arg0] = sequence;
    }
    func_80017F80(&D_8003CA58[arg0], (u8 *)D_8003CA48[arg0]);
    func_80018CB0(D_8003C900[arg0], &D_8003CA58[arg0]);
    func_80017B30(D_8003C900[arg0]);
    return 0;
}
void func_80018D00(SequencePlayer *, s16);

void func_80008EE0(u8 arg0, s32 volume) {
    func_80018D00(D_8003C900[arg0], (s16)volume);
}

void func_80008F24(u8 arg0) {
    func_80018C60(D_8003C900[arg0]);
}
void func_80018D50(SequencePlayer *);

void func_80008F58(u8 arg0) {
    func_80018D50(D_8003C900[arg0]);
}
