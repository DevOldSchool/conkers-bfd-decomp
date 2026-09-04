#ifndef CONKER_N_AUDIO_COMMANDS_H
#define CONKER_N_AUDIO_COMMANDS_H
#include <PR/abi.h>

/* N-audio's packed pole-filter command uses the second word's high byte
 * for the table selector and its low 24 bits for the state address.
 */
#define CONKER_AUDIO_POLE_FILTER(pkt, flags, buffer, table, state) { \
    Acmd *cmd = (Acmd *)(pkt); \
    cmd->words.w0 = _SHIFTL(A_POLEF, 24, 8) | \
        _SHIFTL(flags, 16, 8) | _SHIFTL(buffer, 0, 16); \
    cmd->words.w1 = _SHIFTL(table, 24, 8) | \
        _SHIFTL((u32)(state), 0, 24); \
}
/* Rare's opcode-zero command scales a main output buffer. */
#define CONKER_AUDIO_SCALE(pkt, outp, gain, count) { \
    Acmd *_a = (Acmd *)(pkt); \
    _a->words.w0 = _SHIFTL(A_SPNOOP, 24, 8) | _SHIFTL(outp, 0, 16); \
    _a->words.w1 = _SHIFTL(gain, 16, 16) | _SHIFTL(count, 0, 16); \
}
#define CONKER_AUDIO_RESAMPLE(pkt, state, flags, pitch, input, output) { \
    Acmd *cmd = (Acmd *)(pkt); \
    cmd->words.w0 = _SHIFTL(A_RESAMPLE, 24, 8) | _SHIFTL(state, 0, 24); \
    cmd->words.w1 = _SHIFTL(flags, 30, 2) | _SHIFTL(pitch, 14, 16) | \
        _SHIFTL(input, 2, 12) | _SHIFTL(output, 0, 2); \
}
#define CONKER_AUDIO_LOAD_BUFFER(pkt, count, dest, source) { \
    Acmd *_a = (Acmd *)(pkt); \
    _a->words.w0 = _SHIFTL(A_LOADBUFF, 24, 8) | _SHIFTL(count, 12, 12) | \
        _SHIFTL(dest, 0, 12); \
    _a->words.w1 = (u32)(source); \
}
#define CONKER_AUDIO_ADPCM(pkt, state, flags, count, align, dest) { \
    Acmd *_a = (Acmd *)(pkt); \
    _a->words.w0 = _SHIFTL(A_ADPCM, 24, 8) | _SHIFTL(state, 0, 24); \
    _a->words.w1 = _SHIFTL(flags, 28, 4) | _SHIFTL(count, 16, 12) | \
        _SHIFTL(align, 12, 4) | _SHIFTL(dest, 0, 12); \
}
#define CONKER_AUDIO_SAVE_BUFFER(pkt, count, source, dest) { \
    Acmd *_a = (Acmd *)(pkt); \
    _a->words.w0 = _SHIFTL(A_SAVEBUFF, 24, 8) | _SHIFTL(count, 12, 12) | \
        _SHIFTL(source, 0, 12); \
    _a->words.w1 = (u32)(dest); \
}
#define CONKER_AUDIO_SET_VOLUME(pkt, flags, volume, target, rate) { \
    Acmd *_a = (Acmd *)(pkt); \
    _a->words.w0 = _SHIFTL(A_SETVOL, 24, 8) | _SHIFTL(flags, 16, 8) | \
        _SHIFTL(volume, 0, 16); \
    _a->words.w1 = _SHIFTL(target, 16, 16) | _SHIFTL(rate, 0, 16); \
}
#define CONKER_AUDIO_ENV_MIXER(pkt, flags, volume, state) { \
    Acmd *_a = (Acmd *)(pkt); \
    _a->words.w0 = _SHIFTL(A_ENVMIXER, 24, 8) | _SHIFTL(flags, 16, 8) | \
        _SHIFTL(volume, 0, 16); \
    _a->words.w1 = (u32)(state); \
}
#endif
