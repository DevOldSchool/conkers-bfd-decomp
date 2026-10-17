/* Synthetic fixture: not copied project or ROM source. */
#ifndef FIXTURE_TYPES_H
#define FIXTURE_TYPES_H
typedef struct SharedVec3 {
    f32 x, y, z;
} SharedVec3;
typedef struct {
    u8 opcode;
    u8 pad1[3];
    u32 word1;
} SharedCommand;
#endif
