#ifndef CONKER_GAME_FUNCTIONS_H
#define CONKER_GAME_FUNCTIONS_H

#include "types.h"
#include "game_command.h"

struct Game15D730CopyBlock;
struct Game1D2480Effect;
struct Game1944C0EffectB8;
struct Game1BA670State;
struct Game6C960Actor;
struct Game7FA40Owner;
struct GameAB760State;
struct LightEffectActor;

/* Reviewed shared interfaces from matched US definitions.
 * Include this header in both definitions and callers; do not redeclare locally.
 * See docs/decompilation-workflow.md, Shared function declarations.
 */
GameCommand *func_150D8590(GameCommand *, s32);
void func_15143874(s16, f32, f32 *, f32 *);
void func_151AB930(void *);
void func_151C1FB8(void *);
void func_151D0024(void *);
void func_1516972C(void *);
void *func_15169968(void *);
void *func_15149130(s16, s8, s8, s8, u8, u8, s32, u8, s32);
void *func_151491F4(s16, s8, s8, u8, u8, s32, u8, s32);
void func_151494E0(void *, u8);
void *func_15167A68(s32, s32, s32, s32, u8, u8);
f32 func_151423D8(u8);
f32 func_15048A40(u8);
f32 func_150489B0(u8);
void *func_151149AC(u8);
void func_1516979C(void *);
void func_15169804(void *);
void func_15169824(void *);
void func_1514933C(void *);
void func_151478F4(void *);
void func_15147928(void *);
void func_15149368(void *);
void func_1513CA6C(void *);
void func_1513CAA0(void *);
void func_151411A4(void *);
void func_151411C4(void *);
void func_151346EC(void *);
void func_1513470C(void *);
void func_151352EC(void *);
void func_1513530C(void *);
void func_151617C4(void *);
void func_151617E4(void *);
void func_1513173C(void *);
void func_1513175C(void *);
s32 func_15123934(void *, s32, s32, s32, s32);
s32 func_151239CC(void *, s32);
f32 func_15143E64(void *);
void *func_1513418C(void *, s32, u8, s32);
void func_15142314(void *, s32, f32 *);
void func_15048F90(void *, void *, void *);
f32 func_15048FC8(f32 *);
void *func_1515D440(void);
void func_1515F170(s32, u8);
void func_151D3F14(void *, u8, s32);
void *func_15167D84(void *, s32, s32, s8, u8, s32);
void func_151616D0(u8, u8, s32);
void func_151D5404(void *, f32, f32, f32, s16, s16, s32, s32);
void func_151D3FF4(f32 *, u8, s32);
void func_151DAB58(u8, f32, u8, f32 *, s32, u8, s32);
void func_1504332C(u8, u8, u8, u8);
void func_1513F6C0(void *, u8, u8);
void func_1516962C(s32, void *, u8);
s32 func_1506196C(u8 *, s32);
void func_15062BDC(u8 *, f32, f32);
u8 func_151464B8(s16 *);
void func_1513F680(void *, u8, u8, u8, u8);
void func_1517EE40(s32, s32, s32, s32, s8, s32);
s32 func_1502DB20(s32);
void func_1503F7B8(void *);
void func_15165F80(s32, s32, s32, s32, s32, s32, s32, u8, s32);
f32 func_1505A6F8(void *, void *);
void func_15142180(u8, s32 *, s32, f32, f32);
void func_151436B4(f32, f32, f32, f32 *);
s32 func_1517EFAC(s32);
s32 func_1518E298(void *, s32, s32, s32);
s32 func_1514EC1C(s32, s32, s16);
void *func_15190770(void *, s32, u8, s32);
s32 func_15083FB0(u8);
void func_1514EDF0(void *, void *);
void *func_15130280(void *, u8, struct Game15D730CopyBlock *, s32, u8, s32);
void *func_15147DA0(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, void *, s32, u8, s32);
void func_15132570(void *);
void func_1513259C(void *);
void *func_15134908(void *, s32, u8, s32);
void *func_150335C8(void *, void *, s32, s32, s32, s32);
s32 func_150849A0(void *);
void func_1503DE70(void *, s32, s32);
void func_151D74B0(void *, u8, s8, u8, s32);
void func_1502EA98(void *, s32, s32, s32, s32, s32, s32);
void func_15123070(struct108 *);
void func_15052590(struct Game7FA40Owner *);
struct Game1944C0EffectB8 *func_15168800(void *, u8, s32);
void func_1507EABC(struct GameAB760State *);
void func_1518E308(struct Game1BA670State *);
void func_1516D2E0(void *);
void func_1515C244(void *, void *, f32 *, f32 *);
f32 func_1505A72C(void *, void *);
void func_1503F5B8(struct Game6C960Actor *, s32, s32, f32, f32, s32);
s32 func_15161E24(struct LightEffectActor *, u8, u8, s16, s32, s32, s32, s32, s32, s32);
struct Game1D2480Effect *func_151A4FD0(s32, s32, s32, s32, s32, s32, u8, s32);
void *func_1518AADC(s32, s16, u8);

#endif
