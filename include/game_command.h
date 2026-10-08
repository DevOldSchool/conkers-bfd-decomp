#ifndef CONKER_GAME_COMMAND_H
#define CONKER_GAME_COMMAND_H

#include "types.h"

/* Four-byte header used by the game command stream. */
typedef struct GameCommand {
    s16 opcode;
    s16 value;
} GameCommand;

#endif
