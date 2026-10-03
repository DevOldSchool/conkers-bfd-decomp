#include "types.h"

/*
 * Reviewed source unit: src/game/game_48FD0.c
 * Boundary evidence: docs/evidence/game_raw_controller_io_group.md
 *
 * TODO: Implement these source-unit functions:
 * - func_1501BBB8
 * - func_1501C010
 * - func_1501C17C
 * - func_1501C1B0
 * - func_1501C57C
 *
 * Unmatched members use generated GLOBAL_ASM placeholders below.
 */

u64 func_10026968(u64, u64);
u64 func_10026868(u64, u64);
s32 func_10024A40(void *, u64, u64, void *, void *);
extern u64 D_8002BD10;
extern u8 D_80084064;
extern u8 D_8003B218[];
extern u8 D_800BE6E0[];
extern f32 D_80096960;
void func_1501C0F0(u8, f32, f32);

void func_1501BB20(void) {
    u64 temp_ret;

    if (D_80084064 != 0) {
        temp_ret = func_10026968(25ULL, D_8002BD10);
        temp_ret = func_10026868(temp_ret, 1000000ULL);
        func_10024A40(D_800BE6E0, temp_ret, 0ULL, D_8003B218, (void *)6);
        D_80084064 = 0;
    }
}
/* SDK message queue and per-channel Pak records; see PR/os_message.h and PR/os_pfs.h. */
typedef struct Game48FD0Queue {
    void *receiveThreads;
    void *sendThreads;
    s32 validCount;
    s32 first;
    s32 messageCount;
    void **messages;
} Game48FD0Queue;

/* SDK OSContPad layout: a six-byte record, four controller channels. */
typedef struct Game48FD0Pad {
    u16 button;
    s8 stickX;
    s8 stickY;
    u8 error;
} Game48FD0Pad;

s32 func_10023440(Game48FD0Queue *, void **, s32);
void func_10024C84(Game48FD0Pad *);
void func_1501C57C(void);
void func_151DD8C0(void);
extern Game48FD0Queue D_800BE900;
extern void *D_800BE990;
extern u8 D_80084060[4];
extern s8 D_8008FD90;
extern u16 D_800BE700[4];
extern u16 D_800BE708[4];
extern u16 D_800BE710[4];
extern u16 D_800BE718[4];
extern u16 D_800BE720[4];
extern Game48FD0Pad *D_800BE730[4];
extern u8 D_800BE740;
extern Game48FD0Pad D_800BE748[4];
extern Game48FD0Pad D_800BE918[4];
extern u16 D_800BE930[4];
extern s32 D_800BE9F0;
extern u8 D_800E0B94;
extern u8 D_800E0B95;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501BBB8 CURRENT (13530) */
s32 func_1501BBB8(void) {
    Game48FD0Pad pads[4];
    Game48FD0Pad *input;
    Game48FD0Pad *output;
    u16 *history;
    u16 *edges;
    s32 channel;
    s32 playerCount;
    s32 mode;
    s32 magnitude;
    s32 sign;
    s8 x;
    s8 y;
    u8 physical;
    u16 buttons;

    input = D_800BE748;
    history = D_800BE718;
    do {
        *history++ = input->button;
        input++;
    } while (input < D_800BE748 + 4);
    func_10023440(&D_800BE900, &D_800BE990, 1);
    func_10024C84(pads);
    func_1501C57C();
    D_80084064 = 1;
    D_800BE740 = 0;
    for (channel = 0; channel != 4; channel++) {
        if (pads[channel].error != 0) {
            pads[channel].button = 0;
            pads[channel].stickX = 0;
            pads[channel].stickY = 0;
        } else {
            D_800BE740 |= 1 << channel;
        }
    }
    playerCount = 4;
    if (D_800BE9F0 != 0x1D) {
        playerCount = D_8008FD90;
    }
    for (channel = 0; channel != 4; channel++) {
        physical = D_80084060[channel];
        if (physical < 4 && channel < playerCount) {
            buttons = pads[physical].button;
            D_800BE748[channel].stickX = pads[physical].stickX;
            D_800BE748[channel].stickY = pads[physical].stickY;
            D_800BE748[channel].button = buttons;
            D_800BE748[channel].button |= D_800BE720[physical];
            D_800BE720[physical] = 0;
        } else {
            D_800BE748[channel].button = 0;
            D_800BE748[channel].stickX = 0;
            D_800BE748[channel].stickY = 0;
        }
    }
    input = D_800BE748;
    output = D_800BE918;
    history = D_800BE708;
    edges = D_800BE930;
    do {
        buttons = input->button;
        x = input->stickX;
        *edges++ = ~*history & buttons;
        output->button = buttons;
        *history = buttons;
        magnitude = x < 0 ? -x : x;
        if (magnitude >= 8) {
            sign = x < 0 ? -1 : 1;
            output->stickX = x - sign * 7;
        } else {
            output->stickX = 0;
        }
        y = input->stickY;
        input++;
        magnitude = y < 0 ? -y : y;
        if (magnitude >= 8) {
            sign = y < 0 ? -1 : 1;
            output->stickY = y - sign * 7;
        } else {
            output->stickY = 0;
        }
        output++;
        history++;
    } while (output < D_800BE918 + 4);
    if (D_800E0B94 == 2 || D_800E0B95 == 2) {
        mode = 1;
        func_151DD8C0();
    } else {
        mode = 0;
    }
    input = D_800BE748;
    history = D_800BE700;
    edges = D_800BE710;
    do {
        buttons = input->button;
        *edges++ = ~*history & buttons;
        *history = buttons;
        if (mode == 0) {
            x = input->stickX;
            magnitude = x < 0 ? -x : x;
            if (magnitude >= 8) {
                sign = x < 0 ? -1 : 1;
                input->stickX = x - sign * 7;
            } else {
                input->stickX = 0;
            }
            y = input->stickY;
            magnitude = y < 0 ? -y : y;
            if (magnitude >= 8) {
                sign = y < 0 ? -1 : 1;
                input->stickY = y - sign * 7;
            } else {
                input->stickY = 0;
            }
        }
        history++;
        input++;
    } while (history != D_800BE700 + 4);
    return (s32) D_800BE730;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501BBB8 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501BBB8.s")

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501C010 CURRENT (1149) */
void func_1501C010(s32 arg0, s32 arg1) {
    f32 temp_fv0;
    f32 var_fa0;
    f32 var_ft1;
    f32 var_fv1;
    s32 var_a1;
    s32 var_v0;

    arg0 &= 0xFF;
    arg1 &= 0xFF;
    var_a1 = arg1;
    var_v0 = var_a1;
    if (var_a1 >= 9) {
        var_a1 = 8;
        var_v0 = 8;
    }
    if (var_v0 == 8) {
        var_fv1 = 20.0f;
        var_fa0 = 0.0f;
    } else if (var_v0 == 0) {
        var_fv1 = 0.0f;
        var_fa0 = 99.0f;
    } else {
        var_ft1 = (f32)var_a1;
        if (var_a1 < 0) {
            var_ft1 += 4294967296.0f;
        }
        temp_fv0 = (var_ft1 - 1.0f) * D_80096960 * 5.0f;
        var_fv1 = temp_fv0 + 2.0f;
        var_fa0 = 7.0f - temp_fv0;
    }
    func_1501C0F0(arg0, var_fv1, var_fa0);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501C010 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C010.s")
extern u8 D_800BE93C[4];
extern u8 D_800BE944[4];
extern f32 D_800BE950[4];
extern f32 D_800BE960[4];
extern f32 D_800BE970[4];
extern f32 D_800BE980[4];

void func_1501C0F0(u8 arg0, f32 arg1, f32 arg2) {
    u8 temp_v0;

    temp_v0 = D_80084060[arg0];
    if ((temp_v0 < 4) && (D_800BE944[temp_v0] != 0)) {
        D_800BE93C[temp_v0] = 1;
        D_800BE950[temp_v0] = 0.0f;
        D_800BE960[temp_v0] = arg1;
        D_800BE970[temp_v0] = arg2;
        D_800BE980[temp_v0] = arg1 + arg2;
    }
}

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501C17C CURRENT (200) */
void func_1501C17C(s32 arg0) {

    arg0 = arg0 & 0xFF;
    {
        u8 temp_v0 = D_80084060[arg0];
    if ((s32)temp_v0 < 4) {
        D_800BE93C[temp_v0] = 0;
    }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501C17C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C17C.s")
typedef struct Game48FD0Pak {
    s32 status;
    void *queue;
    s32 channel;
    u8 id[32];
    u8 label[32];
    s32 version;
    s32 directorySize;
    s32 inodeTable;
    s32 mirrorInodeTable;
    s32 directoryTable;
    s32 inodeStartPage;
    u8 banks;
    u8 activeBank;
} Game48FD0Pak;


s32 func_100057E0(Game48FD0Queue *, Game48FD0Pak *, s32);
s32 func_10005570(Game48FD0Pak *);
s32 func_100056A0(Game48FD0Pak *);
extern Game48FD0Pak D_800BE760[4];
extern u8 D_800BE938;
extern u8 D_800BE940[4];
extern u8 D_800BE948[4];
extern f32 D_800BE9A4;
extern u8 D_800BEAC0;
extern u8 D_800BEAC1;
extern u8 D_800BEAC2;
extern u8 D_800BEAC3;
extern u8 D_800E0A00;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501C1B0 CURRENT (730) */
void func_1501C1B0(void) {
    s32 channel;
    u8 *available;
    f32 period;
    u8 enabled;

    available = D_800BE944;
    channel = 0;
    do {
        if (D_800BE938 != 0) {
            if (func_100057E0(&D_800BE900, &D_800BE760[channel], channel) == 0) {
                if (*available == 0) {
                    *available = 1;
                    D_800BE93C[channel] = 0;
                    D_800BE940[channel] = 0;
                    D_800BE948[channel] = 0;
                    D_800BE950[channel] = 0.0f;
                    D_800BE960[channel] = 1.0f;
                    D_800BE970[channel] = 1.0f;
                    D_800BE980[channel] = 2.0f;
                    func_10005570(&D_800BE760[channel]);
                }
            } else {
                *available = 0;
            }
        }
        if (*available != 0) {
            if (D_800BEAC3 != 0 || D_800E0A00 != 0) {
                func_100057E0(&D_800BE900, &D_800BE760[channel], channel);
                func_10005570(&D_800BE760[channel]);
                D_800BE948[channel] = 0;
                D_800BE93C[channel] = 0;
            }
            if (D_800BEAC1 == 0 && D_800BEAC0 == 0 && D_800BEAC2 == 0 &&
                D_800BEAC3 == 0 && D_800E0A00 == 0) {
                switch (D_800BE93C[channel]) {
                case 0:
                    if (D_800BE940[channel] == 1) {
                        func_100057E0(&D_800BE900, &D_800BE760[channel], channel);
                        func_10005570(&D_800BE760[channel]);
                        D_800BE948[channel] = 0;
                    }
                    break;
                case 1:
                    D_800BE950[channel] += D_800BE9A4;
                    period = D_800BE980[channel];
                    enabled = 1;
                    if (period < D_800BE950[channel]) {
                        do {
                            D_800BE950[channel] -= period;
                        } while (period < D_800BE950[channel]);
                    }
                    if (D_800BE960[channel] <= D_800BE950[channel]) {
                        enabled = 0;
                    }
                    if (enabled != 0) {
                        if (D_800BE948[channel] == 0) {
                            func_100056A0(&D_800BE760[channel]);
                        }
                    } else if (D_800BE948[channel] == 1) {
                        func_10005570(&D_800BE760[channel]);
                    }
                    D_800BE948[channel] = enabled;
                    break;
                }
            }
            D_800BE940[channel] = D_800BE93C[channel];
        }
        channel++;
        available++;
    } while (channel != 4);
    D_800BE938 = 0;
    D_800BEAC3 = 0;
    D_800E0A00 = 0;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501C1B0 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C1B0.s")

void func_1501C17C(s32);

void func_1501C53C(void) {
    s32 temp_t6;
    s32 var_s0;

    var_s0 = 0;
    do {
        func_1501C17C(var_s0 & 0xFF);
        var_s0 += 1;
        temp_t6 = var_s0 & 0xFF;
    } while ((var_s0 = temp_t6) < 4);
}
void func_10004074(s32);
void func_150064E0(void);
void func_15007168(void);
s32 func_151DCFD8(s32);
void func_15006590(s8);
void func_15006BEC(s8);
void func_1500707C(s8);
void func_1500727C(void);
void func_15007360(void);
void func_15007440(void);
void func_15007558(void);
u8 func_151DD460(void *);
extern s8 D_80082BB4;
extern u8 D_80084068;
extern s8 D_800BE3EC;
extern s32 D_800BE3F0;

#if 0 /* CONKER_DEFERRED_CANDIDATE func_1501C57C CURRENT (2320) */
void func_1501C57C(void) {
    s32 count;
    s8 action;
    u8 status;

    func_151DCFD8(0);
    action = D_80082BB4;
    if (action != 0) {
        status = D_80084068;
        if (status != 2) {
            D_80084068 = func_151DD460(&D_800BE900);
            status = *(volatile u8 *)&D_80084068;
            action = D_80082BB4;
        }
        if (status != 2) {
            switch (action) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                break;
            }
            count = 19;
            if (count > 0) {
                for (; count > 0; count--) {
                }
            }
            if (action == 1) {
                func_150064E0();
            } else if (action == 4) {
                func_15007168();
            }
            D_80082BB4 = 0;
            return;
        }
        switch (action) {
        case 1:
            func_15006590(D_800BE3EC);
            break;
        case 2:
            func_15006BEC(D_800BE3EC);
            break;
        case 3:
            func_1500707C(D_800BE3EC);
            break;
        case 4:
            func_1500727C();
            break;
        case 5:
            func_15007360();
            break;
        case 6:
            func_15007440();
            break;
        case 7:
            func_15007558();
            break;
        }
        D_80082BB4 = 0;
        if (D_800BE3F0 != 0) {
            func_10004074(D_800BE3F0 - 8);
            D_800BE3F0 = 0;
        }
    }
}
#endif /* CONKER_DEFERRED_CANDIDATE func_1501C57C */
#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C57C.s")
