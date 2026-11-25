#include "types.h"

/* Data-only reconstruction; no original C-object boundary is claimed.
 * Evidence: docs/evidence/data-layout/us_resource_handlers.md
 * The tables hold heterogeneous code addresses. This unit never calls them;
 * individual declarations retain the existing/native integer-register ABI.
 */

typedef void (*ResourceHandlerAddress)(void);

typedef struct GameCB1C0Record GameCB1C0Record;
typedef struct GameCB3D0Record GameCB3D0Record;
typedef struct GameCA630Input GameCA630Input;
typedef struct GameCBBE0Args GameCBBE0Args;
typedef struct struct215 struct215;
typedef struct {
    s32 pad0[2];
    s32 first;
    s32 second;
    s32 third;
    s32 fourth;
} GameCB3D0Query;

extern s32 func_15096D78(s32 descriptor, s32 operation, void *fields);
extern s32 func_1509759C(s32 arg0, s32 arg1, s32 *arg2);
extern s32 func_15097910(s32 arg0, u8 arg1);
extern s32 func_150979CC(s32 arg0, void *arg1);
extern s32 func_15097A8C(s32 descriptor, s32 operation, void *fields);
extern s32 func_15099C14(s32 descriptor, s32 operation, void *fields);
extern s32 func_1509C440(s32 arg0, s32 arg1, void *arg2);
extern s32 func_1509C7C8(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_1509D180(s32 descriptor, void *fields);
extern void func_1509D780(s32 arg0, u8 *arg1);
extern void func_1509D8FC(s32 arg0, s32 arg1, GameCA630Input *arg2);
extern s32 func_1509DBBC(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_1509DD50(s32 arg0, GameCB1C0Record *arg1);
extern s32 func_1509DDC4(s32 arg0, u16 arg1);
extern s32 func_1509DDFC(s32 arg0, s32 arg1, struct215 *arg2);
extern s32 func_1509DEC4(s32 arg0, s32 arg1, void *arg2);
extern void func_1509DF20(s32 arg0, GameCB3D0Record *arg1);
extern void func_1509DFB4(s32 arg0, s32 arg1);
extern s32 func_1509DFC4(s32 descriptor, s32 operation, void *fields);
extern s32 func_1509E3DC(volatile s32 arg0, u32 arg1, GameCB3D0Query *arg2);
extern s32 func_1509E640(s32 arg0, s32 arg1, void *arg2);
extern s32 func_1509E6F0(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_1509E730(s32 arg0, u32 kind, GameCBBE0Args *args);
extern s32 func_1509E8A0(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_1509E900(s32 descriptor, s32 operation, void *fields);
extern s32 func_1509ED74(s32 descriptor, s32 operation, void *fields);
extern s32 func_1509EFF0(s32 descriptor, void *fields);
extern s32 func_1509F248(s32 arg0, s32 *arg1);
extern s32 func_1509F284(s32 arg0, s32 arg1, void *arg2);
extern s32 func_1509F33C(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_1509F800(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_1509F818(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_1509F850(s32 descriptor, s32 operation, void *fields);
extern s32 func_1509FE0C(s32 arg0, s32 arg1, s32 *arg2);
extern s32 func_150A0264(s32 arg0, s32 *arg1);
extern s32 func_150A02D0(s32 arg0, s32 arg1, s32 *arg2);
extern s32 func_150A0374(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_150A03B0(s32 arg0, u32 arg1, void *arg2);
extern s32 func_150A04D8(s32 descriptor, s32 operation, void *fields);

#define HANDLER_ADDRESS(function) ((ResourceHandlerAddress)(function))

ResourceHandlerAddress D_80088420[15] = {
    0,
    HANDLER_ADDRESS(func_15097910),
    0,
    0,
    0,
    0,
    HANDLER_ADDRESS(func_1509EFF0),
    HANDLER_ADDRESS(func_1509DD50),
    0,
    0,
    HANDLER_ADDRESS(func_150A0264),
    0,
    0,
    HANDLER_ADDRESS(func_1509D180),
    HANDLER_ADDRESS(func_1509DF20),
};

ResourceHandlerAddress D_8008845C[15] = {
    0,
    HANDLER_ADDRESS(func_150979CC),
    0,
    0,
    0,
    0,
    HANDLER_ADDRESS(func_1509F248),
    HANDLER_ADDRESS(func_1509DDC4),
    0,
    0,
    0,
    0,
    0,
    HANDLER_ADDRESS(func_1509D780),
    HANDLER_ADDRESS(func_1509DFB4),
};

ResourceHandlerAddress D_80088498[15] = {
    HANDLER_ADDRESS(func_1509C7C8),
    HANDLER_ADDRESS(func_15099C14),
    HANDLER_ADDRESS(func_1509ED74),
    HANDLER_ADDRESS(func_150A04D8),
    HANDLER_ADDRESS(func_1509FE0C),
    HANDLER_ADDRESS(func_1509E6F0),
    HANDLER_ADDRESS(func_1509F33C),
    HANDLER_ADDRESS(func_1509DEC4),
    HANDLER_ADDRESS(func_1509759C),
    HANDLER_ADDRESS(func_1509E8A0),
    HANDLER_ADDRESS(func_150A0374),
    HANDLER_ADDRESS(func_1509F800),
    0,
    HANDLER_ADDRESS(func_1509DBBC),
    HANDLER_ADDRESS(func_1509E3DC),
};

ResourceHandlerAddress D_800884D4[15] = {
    HANDLER_ADDRESS(func_1509C440),
    HANDLER_ADDRESS(func_15097A8C),
    HANDLER_ADDRESS(func_1509E900),
    HANDLER_ADDRESS(func_150A03B0),
    HANDLER_ADDRESS(func_1509F850),
    HANDLER_ADDRESS(func_1509E640),
    HANDLER_ADDRESS(func_1509F284),
    HANDLER_ADDRESS(func_1509DDFC),
    HANDLER_ADDRESS(func_15096D78),
    HANDLER_ADDRESS(func_1509E730),
    HANDLER_ADDRESS(func_150A02D0),
    HANDLER_ADDRESS(func_1509F818),
    0,
    HANDLER_ADDRESS(func_1509D8FC),
    HANDLER_ADDRESS(func_1509DFC4),
};
