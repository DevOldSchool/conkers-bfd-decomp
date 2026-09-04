#include "n_audio_partial.h"

/* Complete US 0x1C690:0x1C770: two N-audio list insertion helpers.
 * Their identical bodies do not independently establish original API names.
 */
void __conker_audio_add_player_1(ALPlayer *client)
{
    OSIntMask mask = osSetIntMask(OS_IM_NONE);
    client->samplesLeft = n_syn->curSamples;
    client->next = n_syn->head;
    n_syn->head = client;
    osSetIntMask(mask);
}

void __conker_audio_add_player_2(ALPlayer *client)
{
    OSIntMask mask = osSetIntMask(OS_IM_NONE);
    client->samplesLeft = n_syn->curSamples;
    client->next = n_syn->head;
    n_syn->head = client;
    osSetIntMask(mask);
}
