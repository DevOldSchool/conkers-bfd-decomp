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
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_800084D8.s")
typedef struct SequencePlayer SequencePlayer;

extern SequencePlayer *D_8003C900[];
s32 func_80017A80(SequencePlayer *player);

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
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008790.s")
void func_80017D30(SequencePlayer *, s32, u8);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008824 CURRENT (1309) */
void func_80008824(s32 arg0, s32 channel, s32 value) {
    func_80017D30(D_8003C900[arg0 & 0xFF], channel & 0xFF, value & 0xFF);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008824 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008824.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_8000886C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_800088F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008988.s")
typedef struct {
    u8 pad0[0xD];
    u8 fadeVolume;
    u8 padE[0x2E];
} SequenceChannel;

struct SequencePlayer {
    u8 pad0[0x60];
    SequenceChannel *channels;
};

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008A4C CURRENT (955) */
u8 func_80008A4C(s32 arg0, s32 channel) {
    return D_8003C900[arg0 & 0xFF]->channels[channel & 0xFF].fadeVolume;
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008A4C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008A4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008A94.s")
s32 func_80017EC0(SequencePlayer *);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008B2C CURRENT (225) */
s32 func_80008B2C(s32 arg0) {
    return func_80017EC0(D_8003C900[arg0 & 0xFF]);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008B2C */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008B2C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008B60.s")
void func_80017DF0(SequencePlayer *, f32, f32);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008BC0 CURRENT (225) */
void func_80008BC0(s32 arg0, f32 arg1, f32 arg2) {
    func_80017DF0(D_8003C900[arg0 & 0xFF], arg1, arg2);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008BC0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008BC0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008C04.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008C6C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008CE8.s")
void func_80018D00(SequencePlayer *, s16);

#if 0 /* CONKER_DEFERRED_CANDIDATE func_80008EE0 CURRENT (295) */
void func_80008EE0(s32 arg0, s32 volume) {
    func_80018D00(D_8003C900[arg0 & 0xFF], (s16)volume);
}
#endif /* CONKER_DEFERRED_CANDIDATE func_80008EE0 */
#pragma GLOBAL_ASM("asm/nonmatchings/main/init_8180/func_80008EE0.s")
void func_80018C60(SequencePlayer *);

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
