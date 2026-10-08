#ifndef CONKER_GAME_FUNCTIONS_H
#define CONKER_GAME_FUNCTIONS_H

#include "types.h"
#include "game_command.h"

/* Reviewed shared interfaces from matched US definitions.
 * Include this header in both definitions and callers; do not redeclare locally.
 * See docs/decompilation-workflow.md, Shared function declarations.
 */
GameCommand *func_150D8590(GameCommand *, s32);
void func_15143874(s16, f32, f32 *, f32 *);
void func_151AB930(void *);
void func_151C1FB8(void *);
void func_151D0024(void *);

#endif
