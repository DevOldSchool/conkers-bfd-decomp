#include "types.h"
#include "game_functions.h"
#include "game_effect_graphics.h"

/* Native 104-entry effect-type table, 52 bytes per record.
 * Evidence: docs/evidence/data-layout/us_effect_types.md
 * Data-only reconstruction; no original C-object boundary is claimed.
 * Callback addresses are stored here and never invoked by this unit.
 */
typedef void (*EffectCallbackAddress)(void);

/* Preserve active callback types locally without changing shared headers.
 * Tagged pointer types need only forward declarations; anonymous types
 * retain their existing definitions for cross-unit type compatibility.
 */
/* src/game/effects/blood.c */
typedef struct {
    s32 field00;
    union {
        s32 word;
        u8 bytes[4];
    } field04;
    u8 field08;
    u8 field09;
} Blood347CCEvent;
/* src/game/effects/blood.c */
typedef struct {
    u8 pad00[0x18];
    u8 field18;
    u8 pad19[3];
    s32 field1C;
    u8 pad20[0x1D];
    u8 field3D;
} Blood347CCState;
/* src/game/effects/blood.c */
typedef struct BloodState BloodState;
/* src/game/game_193E50.c */
typedef struct DisplayCommand193E50 DisplayCommand193E50;
/* src/game/game_13AE20.c */
typedef struct { u32 first, second; } Game13AE20Command;
/* src/game/game_174BF0.c */
typedef struct {
    u8 pad_0[0x20];
    s32 field_20;
} Game174BF0State;
/* src/done/game/game_1765E0.c */
typedef struct {
    u8 pad_0[0x12];
    s8 drawCallbackIndex;
} Game1765E0DispatchState;
/* src/done/game/game_1765E0.c */
typedef struct Game1765E0Effect Game1765E0Effect;
/* src/done/game/game_1765E0.c */
typedef struct {
    u8 pad_0[0x13];
    u8 callbackSetIndex;
} Game1765E0State;
/* src/game/game_193430.c */
typedef struct {
    u8 pad_0[0x92];
    u8 field_92;
    u8 pad_93[3];
    s16 field_96;
    u8 pad_98[6];
    s16 field_9E;
} Game193430State;
/* src/game/game_1944C0.c */
typedef struct Game1944C0Command Game1944C0Command;
/* src/game/game_1944C0.c */
typedef struct Game1944C0RenderState Game1944C0RenderState;
/* src/game/game_19A8B0.c */
typedef struct Game19A8B0Motion Game19A8B0Motion;
/* src/game/game_19F150.c */
typedef struct Game19F150Object Game19F150Object;
/* src/game/game_1A5C00.c */
typedef struct Game1A5C00Owner Game1A5C00Owner;
/* src/game/game_1B0740.c */
typedef struct Game1B0740Command Game1B0740Command;
/* src/done/game/game_1CBE20.c */
typedef struct Game1CBE20Effect Game1CBE20Effect;
/* src/game/game_1FFF60.c */
typedef struct Game1FFF60Motion Game1FFF60Motion;
/* src/done/game/game_1FFB70.c */
typedef struct GameD2830Command GameD2830Command;
/* src/done/game/game_1FFB70.c */
typedef struct GameD2830State GameD2830State;
/* src/game/game_F2820.c */
typedef struct {
    u8 pad_0[0x38];
    u8 field_38;
} GameF2820State;
/* src/game/effects/holtenrope.c */
typedef struct HoltenRopeEffect HoltenRopeEffect;

/* Active declarations and native integer-register call-site views.
 * Native views use the declaration-evidence exclusion marker so matching
 * tools do not promote them into general function signatures. Renderer views
 * retain their v0 cursor result; this address-only unit invokes no callbacks.
 */
extern void *func_150A6860(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_150C09B0(s32 arg0, s32 arg1, u8 arg2);
extern void func_150C09F0(void *arg0);
extern void func_150C0A1C(void *arg0);
extern void func_150C0C38(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_150C5470(GameF2820State *arg0);
extern void func_150C54C0(GameF2820State *arg0);
extern void func_150C5568(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_150C56A4(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_150C5CC4(void *arg0, void *arg1, u8 arg2);
extern void func_150C8A68(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_150C8DB8(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_150E1D14(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_150E28DC(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_150E2F90(s32 arg0, s32 arg1, s16 arg2);
extern void func_150E2FC0(void *arg0, void *arg1, u8 arg2);
extern void func_150E3738(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_151041E4(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_1510448C(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1510608C(void *arg0);
extern void *func_151067B8(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15106EF8(void *arg0);
extern void func_15106F24(void *arg0);
extern void func_15106F50(void *arg0, s32 arg1, u8 arg2, s32 arg3);
extern void func_1510DA84(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_1510E120(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern Game13AE20Command *func_1510E634(Game13AE20Command *arg0, s32 arg1, s32 arg2);
extern void func_151303EC(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_15130A9C(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1513177C(void *arg0);
extern void func_151317C8(void *arg0);
extern void func_15131C2C(void *arg0, s32 arg1, u8 arg2);
extern void func_151321D0(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_151323AC(void *arg0);
extern void func_151323F8(void *arg0);
extern void func_15132A88(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_15132B80(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15133588(void *node, void *context, s32 event); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_151342BC(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern s32 func_151346D0(s32 arg0, void *arg1, s32 arg2);
extern void func_1513472C(BloodState *arg0);
extern void func_1513477C(BloodState *arg0);
extern void func_151347CC(Blood347CCState *arg0, Blood347CCEvent *arg1, u8 arg2);
extern void func_151349D0(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15134C98(BloodState *arg0, s32 arg1, u8 arg2);
extern void func_15134E48(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1513532C(struct102 *arg0);
extern void func_151353A8(struct102 *arg0);
extern void func_15135480(void *node, void *context, s32 event); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1513B798(void *arg0);
extern void *func_1513B83C(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1513BA10(void *arg0);
extern void func_1513BA44(void *arg0);
extern void func_1513BA78(void *arg0, void *arg1, u8 arg2);
extern void func_1513C060(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1513C9B0(void *arg0);
extern void func_1513C9FC(void *arg0);
extern void func_1513CB58(void *arg0);
extern void func_1513CBA4(void *arg0);
extern void *func_1513CBF0(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1513CF9C(s32 arg0, s32 arg1, u8 arg2);
extern void func_1513CFE4(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_1513DB00(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1513DF9C(void *arg0, s32 arg1, u8 arg2);
extern void *func_151406AC(void *display_list, s32 type, s32 group, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15147740(u8 *arg0);
extern void func_151479E0(Game174BF0State *arg0);
extern void func_15147A30(Game174BF0State *arg0);
extern void *func_15147C4C(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15147D1C(void *arg0, s32 arg1, u8 arg2);
extern void func_15149264(Game1765E0Effect *object);
extern void func_15149394(Game1765E0State *arg0);
extern void func_151493E4(Game1765E0State *arg0);
extern void func_15149434(void *arg0, void *arg1, u8 arg2);
extern s32 func_15149490(s32 arg0, Game1765E0DispatchState *arg1, s16 arg2);
extern void func_15154C90(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_15154D80(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15155564(void *arg0, s32 arg1, u8 arg2);
extern void func_1515589C(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_15155CFC(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15155EF8(void *arg0);
extern void func_15156028(void *node, void *context, s32 event); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_151563B8(u8 *arg0);
extern void *func_151564F8(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15156FB8(void *arg0);
extern void func_15156FE4(void *arg0);
extern void func_15157248(void *arg0);
extern void func_1515728C(void *arg0);
extern void func_151572D0(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_15157420(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15157D88(s32 arg0, s32 arg1, u8 arg2);
extern void func_15158224(void *arg0);
extern void *func_151582C8(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15158AA4(void *arg0);
extern void func_15158AD0(void *arg0);
extern void func_15158B3C(void *arg0, void *arg1, u8 arg2);
extern void func_15158CD4(void *arg0);
extern void func_15158D00(void *arg0);
extern void func_15158D2C(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15158FA4(u8 *arg0, u8 *arg1, u8 arg2);
extern void func_1515BAE0(u8 *arg0);
extern void *func_1515BBF0(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1515BF50(void *arg0);
extern void func_1515BF7C(void *arg0);
extern void func_1515BFA8(u8 *arg0);
extern void func_1515C0B8(s32 arg0, s32 arg1, u8 arg2);
extern void func_1515FFEC(void *arg0);
extern void func_15160090(void *arg0, s32 arg1, u8 arg2);
extern void func_151603FC(void *arg0);
extern void func_151604A0(void *arg0, u8 *arg1, u8 arg2);
extern void func_15161804(void *arg0);
extern void func_15161860(void *arg0);
extern void func_1516489C(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15166204(Game193430State *arg0);
extern void *func_15166268(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_151668B8(void *display_list, s32 type, s32 group, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15166B50(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern DisplayCommand193E50 *func_15166D68(DisplayCommand193E50 *displayList, u8 *object, s32 unused);
extern void *func_15166F6C(void *display_list, s32 type, s32 group, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern DisplayCommand193E50 *func_15166FD8(DisplayCommand193E50 *arg0, s32 arg1, s32 arg2);
extern void func_15167B44(void *arg0);
extern void *func_15167C58(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15167E0C(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern s32 func_15168118(s32, void *, s16);
extern void func_15168870(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15168A2C(void *arg0);
extern void func_15168BAC(void *arg0);
extern void *func_15168C4C(Game1944C0Command *arg0, Game1944C0RenderState *arg1, s32 arg2);
extern s32 func_15169668(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_15169988(void *arg0);
extern void *func_15169A48(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1516AA70(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_1516B6BC(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1516D400(void); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1516D678(Game19A8B0Motion *arg0);
extern void *func_1516D738(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1516DB90(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15171FC0(Game19F150Object *arg0);
extern void *func_151720C4(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15175958(void *);
extern void func_1517685C(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15176B84(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void * func_15176DF0(u32 *, u8 *, s16);
extern void *func_151770C8(u32 *gdl, u8 *arg1, s16 arg2);
extern s32 func_15178750(s32 arg0, void *arg1, s16 arg2);
extern void func_151787AC(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15178DA4(Game1A5C00Owner *arg0);
extern void func_1517A1EC(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_1517A3A0(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1517A84C(u8 *arg0);
extern s32 func_1517A958(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_1517AB7C(s32 arg0, s32 arg1, s16 arg2);
extern Game1B0740Command *func_15183BA4(Game1B0740Command *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_15187978(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_15187A98(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15189A00(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1518AA10(u8 *arg0);
extern void func_1518BD60(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1518C850(void *arg0, void *arg1, u8 arg2);
extern void func_1518D6E0(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1518E4CC(void *arg0);
extern void func_1518E4F8(void *arg0);
extern void func_1518F49C(u8 *arg0, s32 arg1, u8 arg2);
extern void func_15190840(void *arg0);
extern void func_1519086C(void *arg0);
extern void func_15190898(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_15191980(void *node, void *context, s32 event); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_1519EA04(Game1CBE20Effect *arg0);
extern void func_151A5070(u8 *arg0);
extern void func_151A5130(s32 arg0, void *arg1, s16 arg2, s32 arg3);
extern void func_151A55D4(void *arg0, s32 arg1, u8 arg2);
extern void func_151A7A90(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_151A7D6C(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_151A8584(s32 arg0);
extern void func_151A85D4(s32 arg0);
extern void func_151A8A20(void *arg0, s32 arg1, u8 arg2);
extern void func_151ACB60(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_151ACB94(s32 arg0, s32 arg1, u8 arg2);
extern void func_151AD174(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void *func_151AD92C(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_151AE640(void *arg0, void *arg1, u8 arg2);
extern void func_151B3184(HoltenRopeEffect *arg0);
extern void *func_151B32C8(void *display_list, void *node, s32 selector); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_151B3A34(void *arg0, s32 arg1, u8 arg2);
extern void func_151B4C6C(void *arg0);
extern void func_151B4C98(void *arg0);
extern void func_151B9CB0(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_151D275C(void *arg0);
extern void *func_151D2830(GameD2830Command *arg0, GameD2830State *arg1, s16 arg2);
extern void func_151D2C40(Game1FFF60Motion *arg0);
extern void func_151D2DCC(void *arg0);
extern void func_151D2E14(void *arg0);
extern void func_151D2E5C(void *arg0, void *arg1, u8 arg2);
extern void func_151D2F90(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_151D31F4(void *arg0);
extern void func_151D3220(void *arg0);
extern void func_151D324C(void *arg0, void *arg1, u8 arg2);
extern void func_151D8A24(void *node); /* CONKER_ABI_DISCARDED_RETURN */
extern void func_151D8B88(void *arg0);
extern void func_151D8BB4(void *arg0);
extern void func_151D8D5C(void *arg0, s32 arg1, u8 arg2);

/* Display-list types and extents come from the reviewed SDK data owners. */

typedef struct EffectType {
    EffectCallbackAddress process;
    EffectCallbackAddress process_secondary;
    EffectCallbackAddress render;
    EffectCallbackAddress update;
    Gfx *before_display_list;
    EffectCallbackAddress pre_render;
    EffectCallbackAddress initialize;
    EffectCallbackAddress traverse;
    EffectCallbackAddress post_render;
    Gfx *after_display_list;
    EffectCallbackAddress destroy;
    EffectCallbackAddress destroy_secondary;
    s8 render_mode;
} EffectType;

#define EFFECT_CALLBACK(function) ((EffectCallbackAddress)(function))

EffectType D_8008B4A8[104] = {
    { /* type   0 */
        EFFECT_CALLBACK(func_15169824), 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type   1 */
        EFFECT_CALLBACK(func_15168A2C), 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type   2 */
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type   3 */
        EFFECT_CALLBACK(func_15167B44), 0, EFFECT_CALLBACK(func_15167C58), 0,
        D_800873D0, 0, 0, 0,
        0, D_80087408, 0, 0, 1
    },
    { /* type   4 */
        EFFECT_CALLBACK(func_15166204), 0, EFFECT_CALLBACK(func_15166268), 0,
        D_8008B3A0, EFFECT_CALLBACK(func_151668B8), 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type   5 */
        EFFECT_CALLBACK(func_15167E0C), 0, EFFECT_CALLBACK(func_15168118), 0,
        D_800873D0, EFFECT_CALLBACK(func_15169668), 0, 0,
        0, D_80087408, 0, 0, 1
    },
    { /* type   6 */
        EFFECT_CALLBACK(func_15187978), 0, EFFECT_CALLBACK(func_15187A98), 0,
        D_8008D4F0, 0, 0, 0,
        0, D_8008D520, 0, 0, 1
    },
    { /* type   7 */
        EFFECT_CALLBACK(func_151B9CB0), 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, 0
    },
    { /* type   8 */
        EFFECT_CALLBACK(func_1517A1EC), 0, EFFECT_CALLBACK(func_1517A3A0), 0,
        D_8008CE20, EFFECT_CALLBACK(func_1517A958), 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type   9 */
        EFFECT_CALLBACK(func_1517A84C), 0, EFFECT_CALLBACK(func_1517A3A0), 0,
        D_8008CE20, EFFECT_CALLBACK(func_1517A958), 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type  10 */
        EFFECT_CALLBACK(func_15175958), 0, EFFECT_CALLBACK(func_15176DF0), 0,
        0, EFFECT_CALLBACK(func_15183BA4), 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type  11 */
        EFFECT_CALLBACK(func_150E1D14), 0, EFFECT_CALLBACK(func_150E28DC), 0,
        D_800889E0, 0, 0, EFFECT_CALLBACK(func_150E2FC0),
        EFFECT_CALLBACK(func_150E2F90), 0, 0, 0, 1
    },
    { /* type  12 */
        EFFECT_CALLBACK(func_1517A1EC), 0, EFFECT_CALLBACK(func_1517A3A0), 0,
        D_8008CE40, EFFECT_CALLBACK(func_1517A958), 0, 0,
        EFFECT_CALLBACK(func_1517AB7C), D_80087408, 0, 0, 1
    },
    { /* type  13 */
        EFFECT_CALLBACK(func_15166B50), 0, EFFECT_CALLBACK(func_15166D68), 0,
        D_8008B440, EFFECT_CALLBACK(func_15166F6C), 0, 0,
        EFFECT_CALLBACK(func_15166FD8), 0, 0, 0, 1
    },
    { /* type  14 */
        EFFECT_CALLBACK(func_15168870), 0, EFFECT_CALLBACK(func_150A6860), 0,
        D_8008B480, 0, 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type  15 */
        EFFECT_CALLBACK(func_15171FC0), 0, EFFECT_CALLBACK(func_151720C4), 0,
        D_8008CC30, 0, 0, 0,
        0, D_8008CC58, 0, 0, 0
    },
    { /* type  16 */
        EFFECT_CALLBACK(func_15168BAC), 0, EFFECT_CALLBACK(func_15168C4C), 0,
        0, 0, 0, 0,
        0, D_8008B498, 0, 0, 0
    },
    { /* type  17 */
        EFFECT_CALLBACK(func_1516DB90), 0, 0, 0,
        0, 0, EFFECT_CALLBACK(func_1516D400), 0,
        0, 0, 0, 0, 0
    },
    { /* type  18 */
        EFFECT_CALLBACK(func_1516D678), 0, EFFECT_CALLBACK(func_1516D738), 0,
        D_8008CB70, 0, 0, 0,
        0, D_8008CB90, 0, 0, 1
    },
    { /* type  19 */
        EFFECT_CALLBACK(func_1517685C), 0, EFFECT_CALLBACK(func_151770C8), 0,
        0, EFFECT_CALLBACK(func_15183BA4), 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type  20 */
        EFFECT_CALLBACK(func_15175958), 0, EFFECT_CALLBACK(func_15176DF0), 0,
        0, EFFECT_CALLBACK(func_15183BA4), 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type  21 */
        EFFECT_CALLBACK(func_15176B84), 0, EFFECT_CALLBACK(func_15176DF0), 0,
        0, EFFECT_CALLBACK(func_15183BA4), 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type  22 */
        EFFECT_CALLBACK(func_15176B84), 0, EFFECT_CALLBACK(func_15176DF0), 0,
        0, EFFECT_CALLBACK(func_15183BA4), 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type  23 */
        EFFECT_CALLBACK(func_15176B84), 0, EFFECT_CALLBACK(func_15176DF0), 0,
        0, EFFECT_CALLBACK(func_15183BA4), 0, 0,
        0, 0, 0, 0, 0
    },
    { /* type  24 */
        EFFECT_CALLBACK(func_15176B84), 0, EFFECT_CALLBACK(func_15176DF0), 0,
        0, EFFECT_CALLBACK(func_15183BA4), 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type  25 */
        EFFECT_CALLBACK(func_151321D0), 0, EFFECT_CALLBACK(func_15132B80), EFFECT_CALLBACK(func_15132A88),
        0, 0, 0, EFFECT_CALLBACK(func_15133588),
        0, 0, EFFECT_CALLBACK(func_151323AC), EFFECT_CALLBACK(func_151323F8), 1
    },
    { /* type  26 */
        EFFECT_CALLBACK(func_15189A00), 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type  27 */
        EFFECT_CALLBACK(func_1513C060), 0, EFFECT_CALLBACK(func_1513CBF0), 0,
        D_80089EB8, 0, 0, EFFECT_CALLBACK(func_1513CF9C),
        0, D_80089ED8, EFFECT_CALLBACK(func_1513C9B0), EFFECT_CALLBACK(func_1513C9FC), 1
    },
    { /* type  28 */
        EFFECT_CALLBACK(func_1513CFE4), 0, EFFECT_CALLBACK(func_1513DB00), 0,
        D_80089EB8, EFFECT_CALLBACK(func_151406AC), 0, EFFECT_CALLBACK(func_1513DF9C),
        0, D_80089ED8, EFFECT_CALLBACK(func_1513CB58), EFFECT_CALLBACK(func_1513CBA4), 1
    },
    { /* type  29 */
        EFFECT_CALLBACK(func_1518AA10), 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type  30 */
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type  31 */
        EFFECT_CALLBACK(func_1518BD60), 0, 0, 0,
        0, 0, 0, EFFECT_CALLBACK(func_1518C850),
        0, 0, 0, 0, -1
    },
    { /* type  32 */
        EFFECT_CALLBACK(func_15190898), 0, 0, 0,
        0, 0, 0, EFFECT_CALLBACK(func_15191980),
        0, 0, EFFECT_CALLBACK(func_15190840), EFFECT_CALLBACK(func_1519086C), -1
    },
    { /* type  33 */
        EFFECT_CALLBACK(func_1518D6E0), 0, 0, 0,
        0, 0, 0, EFFECT_CALLBACK(func_1518F49C),
        0, 0, EFFECT_CALLBACK(func_1518E4CC), EFFECT_CALLBACK(func_1518E4F8), 0
    },
    { /* type  34 */
        EFFECT_CALLBACK(func_15147740), 0, EFFECT_CALLBACK(func_15147C4C), 0,
        D_8008A1D0, 0, 0, EFFECT_CALLBACK(func_15147D1C),
        0, D_8008A1F0, EFFECT_CALLBACK(func_151479E0), EFFECT_CALLBACK(func_15147A30), 1
    },
    { /* type  35 */
        EFFECT_CALLBACK(func_15149264), 0, EFFECT_CALLBACK(func_15149490), 0,
        D_8008A470, 0, 0, EFFECT_CALLBACK(func_15149434),
        0, D_8008A498, EFFECT_CALLBACK(func_15149394), EFFECT_CALLBACK(func_151493E4), 1
    },
    { /* type  36 */
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type  37 */
        EFFECT_CALLBACK(func_150C0C38), 0, 0, 0,
        0, 0, 0, EFFECT_CALLBACK(func_150C09B0),
        0, 0, EFFECT_CALLBACK(func_150C09F0), EFFECT_CALLBACK(func_150C0A1C), -1
    },
    { /* type  38 */
        EFFECT_CALLBACK(func_1519EA04), 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type  39 */
        EFFECT_CALLBACK(func_150E3738), 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type  40 */
        EFFECT_CALLBACK(func_151342BC), 0, EFFECT_CALLBACK(func_151346D0), 0,
        0, 0, 0, EFFECT_CALLBACK(func_151347CC),
        0, 0, EFFECT_CALLBACK(func_1513472C), EFFECT_CALLBACK(func_1513477C), 0
    },
    { /* type  41 */
        EFFECT_CALLBACK(func_15134E48), 0, 0, 0,
        0, 0, 0, EFFECT_CALLBACK(func_15135480),
        0, 0, EFFECT_CALLBACK(func_1513532C), EFFECT_CALLBACK(func_151353A8), -1
    },
    { /* type  42 */
        EFFECT_CALLBACK(func_151349D0), 0, 0, 0,
        0, 0, 0, EFFECT_CALLBACK(func_15134C98),
        0, 0, 0, 0, -1
    },
    { /* type  43 */
        EFFECT_CALLBACK(func_151303EC), 0, EFFECT_CALLBACK(func_15130A9C), 0,
        D_80089700, 0, 0, EFFECT_CALLBACK(func_15131C2C),
        0, D_80089730, EFFECT_CALLBACK(func_1513177C), EFFECT_CALLBACK(func_151317C8), 1
    },
    { /* type  44 */
        EFFECT_CALLBACK(func_151563B8), 0, EFFECT_CALLBACK(func_151564F8), 0,
        D_8008AD40, 0, 0, 0,
        0, 0, EFFECT_CALLBACK(func_15156FB8), EFFECT_CALLBACK(func_15156FE4), 1
    },
    { /* type  45 */
        EFFECT_CALLBACK(func_151A7A90), 0, EFFECT_CALLBACK(func_151A7D6C), 0,
        D_8008F910, 0, 0, EFFECT_CALLBACK(func_151A8A20),
        0, D_8008F930, EFFECT_CALLBACK(func_151A8584), EFFECT_CALLBACK(func_151A85D4), 1
    },
    { /* type  46 */
        EFFECT_CALLBACK(func_15158D2C), 0, 0, 0,
        0, 0, 0, EFFECT_CALLBACK(func_15158FA4),
        0, 0, EFFECT_CALLBACK(func_15158CD4), EFFECT_CALLBACK(func_15158D00), -1
    },
    { /* type  47 */
        0, EFFECT_CALLBACK(func_151AD174), EFFECT_CALLBACK(func_151AD92C), 0,
        0, 0, 0, EFFECT_CALLBACK(func_151AE640),
        0, 0, 0, 0, 1
    },
    { /* type  48 */
        0, EFFECT_CALLBACK(func_151ACB60), 0, 0,
        0, 0, 0, EFFECT_CALLBACK(func_151ACB94),
        0, 0, 0, 0, -1
    },
    { /* type  49 */
        EFFECT_CALLBACK(func_150C8A68), 0, EFFECT_CALLBACK(func_150C8DB8), 0,
        D_80088828, 0, 0, 0,
        0, D_80088848, 0, 0, 1
    },
    { /* type  50 */
        EFFECT_CALLBACK(func_1515BFA8), 0, 0, 0,
        0, 0, 0, EFFECT_CALLBACK(func_1515C0B8),
        0, 0, EFFECT_CALLBACK(func_1515BF50), EFFECT_CALLBACK(func_1515BF7C), -1
    },
    { /* type  51 */
        EFFECT_CALLBACK(func_151B3184), 0, EFFECT_CALLBACK(func_151B32C8), 0,
        D_8008FB18, 0, 0, EFFECT_CALLBACK(func_151B3A34),
        0, D_8008FB40, EFFECT_CALLBACK(func_151B4C6C), EFFECT_CALLBACK(func_151B4C98), 1
    },
    { /* type  52 */
        EFFECT_CALLBACK(func_1515FFEC), 0, 0, 0,
        0, 0, 0, EFFECT_CALLBACK(func_15160090),
        0, 0, 0, 0, -1
    },
    { /* type  53 */
        EFFECT_CALLBACK(func_151603FC), 0, 0, 0,
        0, 0, 0, EFFECT_CALLBACK(func_151604A0),
        0, 0, EFFECT_CALLBACK(func_15161804), EFFECT_CALLBACK(func_15161860), -1
    },
    { /* type  54 */
        EFFECT_CALLBACK(func_151572D0), 0, EFFECT_CALLBACK(func_15157420), 0,
        D_8008AD60, 0, 0, EFFECT_CALLBACK(func_15157D88),
        0, D_8008AD80, EFFECT_CALLBACK(func_15157248), EFFECT_CALLBACK(func_1515728C), 1
    },
    { /* type  55 */
        EFFECT_CALLBACK(func_15158224), 0, EFFECT_CALLBACK(func_151582C8), 0,
        D_8008ADD0, 0, 0, EFFECT_CALLBACK(func_15158B3C),
        0, D_8008ADF0, EFFECT_CALLBACK(func_15158AA4), EFFECT_CALLBACK(func_15158AD0), 1
    },
    { /* type  56 */
        EFFECT_CALLBACK(func_1513B798), 0, EFFECT_CALLBACK(func_1513B83C), 0,
        D_80089BC0, 0, 0, EFFECT_CALLBACK(func_1513BA78),
        0, D_80089C08, EFFECT_CALLBACK(func_1513BA10), EFFECT_CALLBACK(func_1513BA44), 1
    },
    { /* type  57 */
        EFFECT_CALLBACK(func_1516489C), 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type  58 */
        EFFECT_CALLBACK(func_151787AC), 0, 0, 0,
        0, 0, 0, 0,
        0, 0, EFFECT_CALLBACK(func_15178DA4), EFFECT_CALLBACK(func_15178DA4), 0
    },
    { /* type  59 */
        EFFECT_CALLBACK(func_15167E0C), 0, EFFECT_CALLBACK(func_15178750), 0,
        D_800873D0, EFFECT_CALLBACK(func_15169668), 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type  60 */
        EFFECT_CALLBACK(func_151D275C), 0, EFFECT_CALLBACK(func_151D2830), 0,
        0, 0, 0, 0,
        0, 0, 0, 0, 0
    },
    { /* type  61 */
        EFFECT_CALLBACK(func_151D2C40), 0, 0, 0,
        0, 0, 0, EFFECT_CALLBACK(func_151D2E5C),
        0, 0, EFFECT_CALLBACK(func_151D2DCC), EFFECT_CALLBACK(func_151D2E14), -1
    },
    { /* type  62 */
        EFFECT_CALLBACK(func_151D2F90), 0, 0, 0,
        0, 0, 0, EFFECT_CALLBACK(func_151D324C),
        0, 0, EFFECT_CALLBACK(func_151D31F4), EFFECT_CALLBACK(func_151D3220), -1
    },
    { /* type  63 */
        EFFECT_CALLBACK(func_151D8A24), 0, 0, 0,
        0, 0, 0, EFFECT_CALLBACK(func_151D8D5C),
        0, 0, EFFECT_CALLBACK(func_151D8B88), EFFECT_CALLBACK(func_151D8BB4), -1
    },
    { /* type  64 */
        EFFECT_CALLBACK(func_1510608C), 0, EFFECT_CALLBACK(func_151067B8), 0,
        D_80088BE0, 0, 0, EFFECT_CALLBACK(func_15106F50),
        0, D_80088C00, EFFECT_CALLBACK(func_15106EF8), EFFECT_CALLBACK(func_15106F24), 1
    },
    { /* type  65 */
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type  66 */
        EFFECT_CALLBACK(func_15167E0C), 0, EFFECT_CALLBACK(func_15168118), 0,
        D_800873D0, EFFECT_CALLBACK(func_15169668), 0, 0,
        0, D_80087408, 0, 0, 1
    },
    { /* type  67 */
        EFFECT_CALLBACK(func_15171FC0), 0, EFFECT_CALLBACK(func_151720C4), 0,
        D_8008CC30, 0, 0, 0,
        0, D_8008CC58, 0, 0, 0
    },
    { /* type  68 */
        EFFECT_CALLBACK(func_15175958), 0, EFFECT_CALLBACK(func_15176DF0), 0,
        0, EFFECT_CALLBACK(func_15183BA4), 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type  69 */
        EFFECT_CALLBACK(func_15175958), 0, EFFECT_CALLBACK(func_15176DF0), 0,
        0, EFFECT_CALLBACK(func_15183BA4), 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type  70 */
        EFFECT_CALLBACK(func_150C5568), 0, EFFECT_CALLBACK(func_150C56A4), 0,
        D_80088768, 0, 0, EFFECT_CALLBACK(func_150C5CC4),
        0, D_80088790, EFFECT_CALLBACK(func_150C5470), EFFECT_CALLBACK(func_150C54C0), 1
    },
    { /* type  71 */
        EFFECT_CALLBACK(func_151303EC), 0, EFFECT_CALLBACK(func_15130A9C), 0,
        D_80089700, 0, 0, EFFECT_CALLBACK(func_15131C2C),
        0, D_80089730, EFFECT_CALLBACK(func_1513177C), EFFECT_CALLBACK(func_151317C8), 1
    },
    { /* type  72 */
        EFFECT_CALLBACK(func_151321D0), 0, EFFECT_CALLBACK(func_15132B80), EFFECT_CALLBACK(func_15132A88),
        0, 0, 0, EFFECT_CALLBACK(func_15133588),
        0, 0, EFFECT_CALLBACK(func_151323AC), EFFECT_CALLBACK(func_151323F8), 1
    },
    { /* type  73 */
        EFFECT_CALLBACK(func_1513CFE4), 0, EFFECT_CALLBACK(func_1513DB00), 0,
        D_80089EB8, 0, 0, EFFECT_CALLBACK(func_1513DF9C),
        0, D_80089ED8, EFFECT_CALLBACK(func_1513CB58), EFFECT_CALLBACK(func_1513CBA4), 1
    },
    { /* type  74 */
        EFFECT_CALLBACK(func_1513C060), 0, EFFECT_CALLBACK(func_1513CBF0), 0,
        D_80089EB8, 0, 0, EFFECT_CALLBACK(func_1513CF9C),
        0, D_80089ED8, EFFECT_CALLBACK(func_1513C9B0), EFFECT_CALLBACK(func_1513C9FC), 1
    },
    { /* type  75 */
        EFFECT_CALLBACK(func_1510DA84), 0, EFFECT_CALLBACK(func_1510E120), 0,
        D_800890C0, 0, 0, 0,
        EFFECT_CALLBACK(func_1510E634), 0, 0, 0, 1
    },
    { /* type  76 */
        EFFECT_CALLBACK(func_151572D0), 0, EFFECT_CALLBACK(func_15157420), 0,
        D_8008AD60, 0, 0, EFFECT_CALLBACK(func_15157D88),
        0, D_8008AD80, EFFECT_CALLBACK(func_15157248), EFFECT_CALLBACK(func_1515728C), 1
    },
    { /* type  77 */
        EFFECT_CALLBACK(func_15147740), 0, EFFECT_CALLBACK(func_15147C4C), 0,
        D_8008A1D0, 0, 0, EFFECT_CALLBACK(func_15147D1C),
        0, D_8008A1F0, EFFECT_CALLBACK(func_151479E0), EFFECT_CALLBACK(func_15147A30), 1
    },
    { /* type  78 */
        0, EFFECT_CALLBACK(func_151AD174), EFFECT_CALLBACK(func_151AD92C), 0,
        0, 0, 0, EFFECT_CALLBACK(func_151AE640),
        0, 0, 0, 0, 1
    },
    { /* type  79 */
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type  80 */
        EFFECT_CALLBACK(func_1515589C), 0, EFFECT_CALLBACK(func_15155CFC), 0,
        0, 0, 0, EFFECT_CALLBACK(func_15156028),
        0, D_8008AD30, EFFECT_CALLBACK(func_15155EF8), EFFECT_CALLBACK(func_15155EF8), 0
    },
    { /* type  81 */
        EFFECT_CALLBACK(func_1516AA70), 0, EFFECT_CALLBACK(func_1516B6BC), 0,
        D_800873D0, 0, 0, 0,
        0, D_80087408, 0, 0, -1
    },
    { /* type  82 */
        EFFECT_CALLBACK(func_151303EC), 0, EFFECT_CALLBACK(func_15130A9C), 0,
        D_80089700, 0, 0, EFFECT_CALLBACK(func_15131C2C),
        0, D_80089730, EFFECT_CALLBACK(func_1513177C), EFFECT_CALLBACK(func_151317C8), 1
    },
    { /* type  83 */
        EFFECT_CALLBACK(func_151563B8), 0, EFFECT_CALLBACK(func_151564F8), 0,
        D_8008AD40, 0, 0, 0,
        0, 0, EFFECT_CALLBACK(func_15156FB8), EFFECT_CALLBACK(func_15156FE4), 1
    },
    { /* type  84 */
        EFFECT_CALLBACK(func_1513B798), 0, EFFECT_CALLBACK(func_1513B83C), 0,
        D_80089BC0, 0, 0, EFFECT_CALLBACK(func_1513BA78),
        0, D_80089C08, EFFECT_CALLBACK(func_1513BA10), EFFECT_CALLBACK(func_1513BA44), 1
    },
    { /* type  85 */
        EFFECT_CALLBACK(func_15158224), 0, EFFECT_CALLBACK(func_151582C8), 0,
        D_8008ADD0, 0, 0, EFFECT_CALLBACK(func_15158B3C),
        0, D_8008ADF0, EFFECT_CALLBACK(func_15158AA4), EFFECT_CALLBACK(func_15158AD0), 1
    },
    { /* type  86 */
        EFFECT_CALLBACK(func_1513CFE4), 0, EFFECT_CALLBACK(func_1513DB00), 0,
        D_80089EB8, EFFECT_CALLBACK(func_151406AC), 0, EFFECT_CALLBACK(func_1513DF9C),
        0, D_80089ED8, EFFECT_CALLBACK(func_1513CB58), EFFECT_CALLBACK(func_1513CBA4), 1
    },
    { /* type  87 */
        EFFECT_CALLBACK(func_15154C90), 0, EFFECT_CALLBACK(func_15154D80), 0,
        D_8008AC70, 0, 0, EFFECT_CALLBACK(func_15155564),
        0, D_8008AC98, 0, 0, 1
    },
    { /* type  88 */
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type  89 */
        EFFECT_CALLBACK(func_1517A1EC), 0, EFFECT_CALLBACK(func_1517A3A0), 0,
        D_8008CE40, EFFECT_CALLBACK(func_1517A958), 0, 0,
        EFFECT_CALLBACK(func_1517AB7C), 0, 0, 0, 1
    },
    { /* type  90 */
        EFFECT_CALLBACK(func_151A5070), 0, EFFECT_CALLBACK(func_151A5130), 0,
        D_800873D0, 0, 0, EFFECT_CALLBACK(func_151A55D4),
        0, D_80087408, 0, 0, 1
    },
    { /* type  91 */
        EFFECT_CALLBACK(func_151572D0), 0, EFFECT_CALLBACK(func_15157420), 0,
        D_8008AD60, 0, 0, EFFECT_CALLBACK(func_15157D88),
        0, D_8008AD80, EFFECT_CALLBACK(func_15157248), EFFECT_CALLBACK(func_1515728C), 1
    },
    { /* type  92 */
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type  93 */
        EFFECT_CALLBACK(func_15154C90), 0, EFFECT_CALLBACK(func_15154D80), 0,
        D_8008AC70, 0, 0, EFFECT_CALLBACK(func_15155564),
        0, D_8008AC98, 0, 0, 1
    },
    { /* type  94 */
        EFFECT_CALLBACK(func_15169988), 0, EFFECT_CALLBACK(func_15169A48), 0,
        D_800873D0, EFFECT_CALLBACK(func_15169668), 0, 0,
        0, D_80087408, 0, 0, 1
    },
    { /* type  95 */
        EFFECT_CALLBACK(func_15149264), 0, EFFECT_CALLBACK(func_15149490), 0,
        D_8008A470, 0, 0, EFFECT_CALLBACK(func_15149434),
        0, D_8008A498, EFFECT_CALLBACK(func_15149394), EFFECT_CALLBACK(func_151493E4), 1
    },
    { /* type  96 */
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type  97 */
        EFFECT_CALLBACK(func_1515BAE0), 0, EFFECT_CALLBACK(func_1515BBF0), 0,
        D_8008B050, 0, 0, 0,
        0, D_8008B068, 0, 0, 1
    },
    { /* type  98 */
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type  99 */
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type 100 */
        0, EFFECT_CALLBACK(func_151041E4), EFFECT_CALLBACK(func_1510448C), 0,
        0, 0, 0, 0,
        0, 0, 0, 0, 1
    },
    { /* type 101 */
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, -1
    },
    { /* type 102 */
        EFFECT_CALLBACK(func_1516DB90), 0, 0, 0,
        0, 0, EFFECT_CALLBACK(func_1516D400), 0,
        0, 0, 0, 0, 0
    },
    { /* type 103 */
        EFFECT_CALLBACK(func_1516D678), 0, EFFECT_CALLBACK(func_1516D738), 0,
        D_8008CB70, 0, 0, 0,
        0, D_8008CB90, 0, 0, 1
    },
};

#undef EFFECT_CALLBACK
