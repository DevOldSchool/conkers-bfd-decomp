#include "n_audio_partial.h"

/* Complete US 0x1E480:0x1E4A0, including the IDO return and padding bytes. */
void n_alSynDelete(void)
{
    n_syn->head = 0;
}
