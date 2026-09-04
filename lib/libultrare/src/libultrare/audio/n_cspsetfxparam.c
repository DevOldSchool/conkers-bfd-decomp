#include "n_cspextevent.h"

/* Conker US 0x17F10:0x17F80: posts the extended effect-parameter message. */
void __conker_csp_set_fx_param(ConkerNAudioCSPlayer *seqp, u8 bus, u8 param,
                             u8 section, s32 value)
{
    ConkerNAudioExtendedEvent event;
    event.fx.type = 0x1a;
    event.fx.bus = bus;
    event.fx.param = param;
    event.fx.section = section;
    event.fx.value = value;
    n_alEvtqPostEvent(&seqp->evtq, &event.base, 0, 2);
}
