#include "n_audio_partial.h"
#include "n_audio_commands.h"

/* Conker US 0x210C0:0x214F0: two-pass auxiliary mixer using the
 * physical voices' intrusive auxiliary links, rather than PD's array.
 */
extern f32 sqrtf(f32);
extern Acmd *n_alEnvmixerPull(ConkerNAudioPVoice *, s32, Acmd *);

Acmd *n_alAuxBusPull(s32 sampleOffset, Acmd *cmdptr, s32 fxBus, s32 *numpulls)
{
    Acmd *cmd = cmdptr;
    ConkerNAudioAuxBus *bus = &n_syn->auxBus[fxBus];
    ConkerNAudioPVoice *source;
    s32 count = 0;
    u32 maximum = 1;
    u32 gain;

    *numpulls = 0;
    source = (ConkerNAudioPVoice *)bus->sources.next;
    while (source) {
        source = (ConkerNAudioPVoice *)((u8 *)source - sizeof(ALLink));
        if (source->vvoice && source->vvoice->pvoice && source->vvoice->pvoice->flags99 >= 64) {
            cmd = n_alEnvmixerPull(source, sampleOffset, cmd);
            *numpulls = *numpulls + 1;
            count++;
            if (source->vvoice->pvoice->flags99 > maximum) {
                maximum = source->vvoice->pvoice->flags99;
            }
        }
        source = (ConkerNAudioPVoice *)source->auxNode.next;
    }
    if (count) {
        maximum -= 62;
        if (maximum >= 7) {
            gain = 26755.0f / sqrtf(maximum);
        } else {
            gain = 65536.0f / maximum;
        }
        CONKER_AUDIO_SCALE(cmd++, 1248, gain, maximum);
        CONKER_AUDIO_SCALE(cmd++, 1616, gain, maximum);
    }
    source = (ConkerNAudioPVoice *)bus->sources.next;
    while (source) {
        source = (ConkerNAudioPVoice *)((u8 *)source - sizeof(ALLink));
        if ((source->vvoice && (source->vvoice->pvoice == NULL || source->vvoice->pvoice->flags99 < 64))
            || (source->vvoice == NULL && !fxBus)) {
            Acmd *prev = cmd;
            cmd = n_alEnvmixerPull(source, sampleOffset, cmd);
            if (cmd != prev) {
                *numpulls = *numpulls + 1;
            }
        }
        source = (ConkerNAudioPVoice *)source->auxNode.next;
    }
    return cmd;
}
