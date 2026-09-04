#include <ultra64.h>

/* Complete US 0x1DBA0:0x1DC80. Rare's compact-sequence next-delta helper
 * retains the SDK ALCSeq layout and is a standalone object in this ROM.
 */
char __alCSeqNextDelta(ALCSeq *seq, s32 *pDeltaTicks)
{
    u32 i;
    u32 firstTime = 0xffffffff;
    u32 lastTicks = seq->lastDeltaTicks;

    if (!seq->validTracks) {
        return FALSE;
    }
    for (i = 0; i < 16; i++) {
        if ((seq->validTracks >> i) & 1) {
            if (seq->deltaFlag) {
                seq->evtDeltaTicks[i] -= lastTicks;
            }
            if (seq->evtDeltaTicks[i] < firstTime) {
                firstTime = seq->evtDeltaTicks[i];
            }
        }
    }
    seq->deltaFlag = 0;
    *pDeltaTicks = firstTime;
    return TRUE;
}
