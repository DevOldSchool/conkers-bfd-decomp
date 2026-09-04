#include "n_audio_partial.h"
#include "n_audio_commands.h"

/* Complete Conker US 0x1FB40:0x1FFE0. The main bus conditionally draws MP3
 * samples, orders auxiliary buses, mixes stereo, then applies output filters.
 */
extern s32 __conker_mp3_enabled;
extern s32 __conker_mp3_make_samples(s32, Acmd **);
extern u8 __conker_bus_route[];
extern u8 __conker_bus_invert[];
extern void n_alFxInitlpfilter_mono(ConkerNAudioOutputLP *, f32);

Acmd *n_alMainBusPull(s32 sampleOffset, Acmd *p)
{
    Acmd *ptr = p;
    s32 i;
    s32 bus;

    if (!__conker_mp3_enabled || !__conker_mp3_make_samples(184, &ptr)) {
        aClearBuffer(ptr++, 1248, 736);
        aClearBuffer(ptr++, 1984, 736);
    }
    bus = 0;
    for (i = 1; i < n_syn->maxAuxBusses; i++) {
        if (n_syn->auxBus[i].outputLP->amount > 0) {
            bus = i;
        }
    }
    for (i = 0; i < n_syn->maxAuxBusses; i++, bus++) {
        if (bus >= n_syn->maxAuxBusses) {
            bus = 0;
        }
        if (i) {
            aClearBuffer(ptr++, 1984, 736);
        }
        ptr = n_syn->mainBus->handler(sampleOffset, ptr, bus);
        if (__conker_bus_route[bus]) {
            if (__conker_bus_invert[bus]) {
                aMix(ptr++, 0, 0x8000, 1984, 1248);
            } else {
                aMix(ptr++, 0, 0x7fff, 1984, 1616);
            }
        } else {
            if (__conker_bus_invert[bus]) {
                aMix(ptr++, 0, 0x8000, 1984, 1616);
            } else {
                aMix(ptr++, 0, 0x7fff, 1984, 1616);
            }
            aMix(ptr++, 0, 0x7fff, 1984, 1248);
        }
        if (n_syn->auxBus[bus].outputLP->amount > 0) {
            ConkerNAudioOutputLP *output = n_syn->auxBus[bus].outputLP;
            if (output->first) {
                n_alFxInitlpfilter_mono(output, n_syn->outputRate);
            }
            aLoadADPCM(ptr++, 32, osVirtualToPhysical(output->coefficients));
            CONKER_AUDIO_POLE_FILTER(ptr++, 0, 1248, 0, osVirtualToPhysical(output->stateLeft) & 0xffffff);
            CONKER_AUDIO_POLE_FILTER(ptr++, 0, 1616, 0, osVirtualToPhysical(output->stateRight) & 0xffffff);
            output->first = 0;
        }
    }
    return ptr;
}
