#include "n_audio_partial.h"

/* Complete US 0x18DA0:0x18E60. The driver's address is the globals base;
 * only the driver prefix is needed here. The two pointers own .data=0x10.
 */
typedef struct {
    ConkerNAudioSynth drvr;
} ConkerNAudioGlobals;

ConkerNAudioGlobals *n_alGlobals = 0;
ConkerNAudioSynth *n_syn = 0;

extern void n_alSynNew(ConkerNAudioConfig *config);
extern void n_alSynDelete(void);

void n_alInit(ConkerNAudioGlobals *globals, ConkerNAudioConfig *config)
{
    if (!n_alGlobals) {
        n_alGlobals = globals;
        if (!n_syn) {
            n_syn = &n_alGlobals->drvr;
            n_alSynNew(config);
        }
    }
}

void n_alClose(ConkerNAudioGlobals *globals)
{
    if (n_alGlobals) {
        n_alSynDelete();
        n_alGlobals = 0;
        n_syn = 0;
    }
}
