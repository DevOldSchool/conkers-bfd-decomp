#include "mp3_stream.h"
#include "audio/n_audio_partial.h"
#include "audio/n_audio_commands.h"

/* Conker US 0x1F2960:0x1F3DE0: Rare MP3 playback, filtering and DMA.
 * Runtime storage and asset services remain external; this view does not
 * claim ownership of the original BSS allocation.
 */
#define SAMPLE184(delta) ((((delta) + 183) / 184) * 184)
#define MP3STATE_IDLE 0
#define MP3STATE_PLAYING 1
#define MP3STATE_PAUSED 2
#define MP3STATE_STOPPED 3
#define MP3STATE_LOADING 5
#define MP3STATE_LOAD_PAUSED 6
#define MP3STATE_UNPAUSING 7
#define N_AL_MAIN_L_OUT 0x4e0
#define N_AL_MAIN_R_OUT 0x650
#define N_AL_TEMP_2 0x2e0
#define N_EQPOWER_LENGTH 128
#define SAMPLES 184
#define n_aLoadBuffer CONKER_AUDIO_LOAD_BUFFER
#define n_aSetVolume CONKER_AUDIO_SET_VOLUME
#define n_aEnvMixer CONKER_AUDIO_ENV_MIXER

typedef struct {
    s16 frequency, amount;
    s32 state;
    s16 coefficients[16];
    s32 first;
    POLEF_STATE *stateLeft;
} ConkerMp3Filter;
struct mp3vars {
    s32 romaddr;
    struct asistream *stream;
    ENVMIX_STATE *em_state;
    s16 em_pan, em_volume, em_cvolL, em_cvolR, em_dryamt, em_wetamt;
    u16 em_lratl;
    s16 em_lratm, em_ltgt;
    u16 em_rratl;
    s16 em_rratm, em_rtgt, em_first;
    s32 em_delta, em_segEnd;
    ConkerMp3Filter filter;
    s32 filesize, dmaoffset;
    u16 *var8009c3c8;
    s32 var8009c3cc, var8009c3d0;
    u32 *var8009c3d4[1];
    u32 var8009c3d8;
    void *dmafunc;
    void *textCallback;
    u32 state, currentvol, field8C, var8009c3e8;
    s16 currentpan, targetpan;
    u8 statetimer, dualchannel;
};
extern struct mp3vars g_Mp3Vars;
extern f32 *var8009c644;
extern struct mp3decfourbytes **var8009c650;
extern u8 *__conker_mp3_lookup_base;
extern u8 *__conker_mp3_huffman_base;
extern u8 __conker_mp3_assets_loaded;
extern s32 __conker_mp3_level;
extern u8 __conker_audio_headphone, __conker_audio_mono;
extern s16 n_eqpower[];
void *__conker_mp3_alloc(s32, s32, s32, s32);
void *__conker_mp3_load_asset(s32, s32, s32, s32);
void __conker_mp3_pin(void *, s32);
void __conker_mp3_free(void *);
s32 mp3dec_init(void);
struct asistream *mp3main_start_file(s32, void *, s32);
s32 mp3main_continue_file(struct asistream *, u16 **, s32 *);
void n_alFxInitlpfilter_mono(ConkerNAudioOutputLP *, f32);
s16 _getRate(f32, f32, s32, u16 *);
s16 _getVol(s16, s32, s16, u16);
void mp3_stop(void);
void mp3_update_vars(struct mp3vars *);
void mp3_dma(void);
#define	aMp3ExecDma(pkt, a, b)                               \
{                                                            \
	Acmd *_a = (Acmd *)pkt;                                  \
	_a->words.w0 = _SHIFTL(0x07, 24, 8) | _SHIFTL(a, 0, 16); \
	_a->words.w1 = b;                                        \
}

#define	aMp3SetAddr(pkt, a)              \
{                                        \
	Acmd *_a = (Acmd *)pkt;              \
	_a->words.w0 = _SHIFTL(0x08, 24, 8); \
	_a->words.w1 = a;                    \
}


void mp3_play_file(s32 romaddr, s32 filesize)
{
    if (g_Mp3Vars.dmafunc == NULL) return;
    g_Mp3Vars.state = 4;
    if (!__conker_mp3_assets_loaded) {
        __conker_mp3_assets_loaded = 1;
        var8009c644 = __conker_mp3_alloc(0x8000, 0xff, 2, 1);
        if (var8009c644 == NULL) {
            __conker_mp3_assets_loaded = 0;
            return;
        }
        var8009c650 = __conker_mp3_load_asset(0, 2, 0x17, 4);
        if (var8009c650) __conker_mp3_pin(var8009c650, 0xff);
        __conker_mp3_lookup_base = __conker_mp3_load_asset(0, 2, 0x17, 5);
        if (__conker_mp3_lookup_base) __conker_mp3_pin(__conker_mp3_lookup_base, 0xff);
        __conker_mp3_huffman_base = __conker_mp3_load_asset(0, 2, 0x17, 6);
        if (__conker_mp3_huffman_base) __conker_mp3_pin(__conker_mp3_huffman_base, 0xff);
        if (!var8009c650 || !__conker_mp3_lookup_base || !__conker_mp3_huffman_base) {
            if (var8009c650) __conker_mp3_free(var8009c650);
            if (__conker_mp3_lookup_base) __conker_mp3_free(__conker_mp3_lookup_base);
            if (__conker_mp3_huffman_base) __conker_mp3_free(__conker_mp3_huffman_base);
            __conker_mp3_free(var8009c644);
            var8009c644 = NULL;
            __conker_mp3_assets_loaded = 0;
            return;
        }
        mp3dec_init();
    }
    g_Mp3Vars.romaddr = romaddr;
    g_Mp3Vars.filesize = filesize;
    g_Mp3Vars.dmaoffset = 0;
    g_Mp3Vars.var8009c3e8 = 0;
    g_Mp3Vars.statetimer = 5;
    g_Mp3Vars.state = MP3STATE_LOADING;
}

void mp3_stop(void)
{
    OSIntMask mask = osSetIntMask(1);
    g_Mp3Vars.state = MP3STATE_STOPPED;
    osSetIntMask(mask);
}

void mp3_pause(void)
{
    OSIntMask mask = osSetIntMask(1);
    if (g_Mp3Vars.state == MP3STATE_LOADING) g_Mp3Vars.state = MP3STATE_LOAD_PAUSED;
    else g_Mp3Vars.state = MP3STATE_PAUSED;
    osSetIntMask(mask);
}

void mp3_unpause(void)
{
    OSIntMask mask = osSetIntMask(1);
    if (g_Mp3Vars.state == MP3STATE_PAUSED) {
        g_Mp3Vars.statetimer = 5;
        g_Mp3Vars.state = MP3STATE_UNPAUSING;
    } else if (g_Mp3Vars.state == MP3STATE_LOAD_PAUSED) {
        g_Mp3Vars.statetimer = 5;
        g_Mp3Vars.state = MP3STATE_LOADING;
    }
    osSetIntMask(mask);
}

s32 mp3_is_busy(void)
{
    s32 result = 0;
    OSIntMask mask = osSetIntMask(1);
    if (g_Mp3Vars.state == MP3STATE_PLAYING || g_Mp3Vars.state == MP3STATE_LOADING ||
        g_Mp3Vars.state == MP3STATE_LOAD_PAUSED || g_Mp3Vars.state == MP3STATE_UNPAUSING ||
        g_Mp3Vars.state == MP3STATE_PAUSED) result = g_Mp3Vars.state;
    osSetIntMask(mask);
    return result;
}

void mp3_set_vol(s32 vol, s32 samples)
{
    OSIntMask mask = osSetIntMask(1);
    if (vol < 0) g_Mp3Vars.currentvol = 0;
    else if (vol > 0x7fff) g_Mp3Vars.currentvol = 0x7fff;
    else g_Mp3Vars.currentvol = vol;
    g_Mp3Vars.var8009c3e8 = samples;
    osSetIntMask(mask);
}

void mp3_set_pan(s32 pan, s32 immediate)
{
    if (pan > 127) pan = 127;
    else if (pan < 0) pan = 0;
    g_Mp3Vars.targetpan = pan;
    if (immediate) g_Mp3Vars.currentpan = g_Mp3Vars.targetpan;
}

void mp3_set_filter(s32 amount, s32 frequency)
{
    g_Mp3Vars.filter.amount = amount;
    g_Mp3Vars.filter.frequency = frequency;
    if (!g_Mp3Vars.filter.first) g_Mp3Vars.filter.first = 2;
}
s32 mp3_make_samples(s32 arg0, Acmd **cmdList)
{
	s32 i;
	s32 diff;
	s32 numchannels = 0;
	u16 *sp58;
	u16 *sp54 = NULL;
	s32 sp50;
	s32 sp4c = N_AL_MAIN_L_OUT;
	s32 sp48 = N_AL_MAIN_R_OUT;

	if (g_Mp3Vars.currentpan != g_Mp3Vars.targetpan) {
		diff = g_Mp3Vars.targetpan - g_Mp3Vars.currentpan;

		if (diff >= -2 && diff <= 2) {
			g_Mp3Vars.currentpan += diff;
		} else if (diff >= 3) {
			g_Mp3Vars.currentpan += 2;
		} else {
			g_Mp3Vars.currentpan -= 2;
		}
	}

	if (g_Mp3Vars.state == MP3STATE_LOADING) {
		mp3_dma();

		if (g_Mp3Vars.statetimer == 0) {
			g_Mp3Vars.stream = mp3main_start_file(0, g_Mp3Vars.dmafunc, g_Mp3Vars.filesize);

			if (g_Mp3Vars.stream == NULL) {
				g_Mp3Vars.dmaoffset = 0;
                g_Mp3Vars.var8009c3e8 = 0;
                g_Mp3Vars.statetimer = 5;
                mp3_dma();
                g_Mp3Vars.state = MP3STATE_LOADING;
                return 0;
			} else {
				g_Mp3Vars.state = MP3STATE_PLAYING;
				g_Mp3Vars.em_first = 1;
				g_Mp3Vars.var8009c3c8 = NULL;
				g_Mp3Vars.var8009c3cc = 0;
				g_Mp3Vars.var8009c3d0 = 0;
				g_Mp3Vars.var8009c3d8 = 0;

				bzero(g_Mp3Vars.var8009c3d4[0], 0x440);
			}
		} else {
			g_Mp3Vars.statetimer--;
		}
	}

	if (g_Mp3Vars.state == MP3STATE_UNPAUSING) {
		mp3_dma();

		if (g_Mp3Vars.statetimer == 0) {
			g_Mp3Vars.state = MP3STATE_PLAYING;
		} else {
			g_Mp3Vars.statetimer--;
		}
	}

	if (g_Mp3Vars.state == MP3STATE_PLAYING) {
		if (arg0 + g_Mp3Vars.var8009c3d0 > g_Mp3Vars.var8009c3cc) {
			g_Mp3Vars.var8009c3cc -= g_Mp3Vars.var8009c3d0;

			if (g_Mp3Vars.var8009c3cc != 0 && g_Mp3Vars.var8009c3c8 != NULL) {
				sp54 = &g_Mp3Vars.var8009c3c8[g_Mp3Vars.var8009c3d0];
				sp50 = g_Mp3Vars.var8009c3cc;
			}

			g_Mp3Vars.var8009c3d0 = 0;
			g_Mp3Vars.var8009c3cc = 0;

			if (mp3main_continue_file(g_Mp3Vars.stream, &sp58, &numchannels)) {
				g_Mp3Vars.var8009c3c8 = sp58;

				for (i = 0; i < numchannels; i++) {
					aMp3SetAddr((*cmdList)++, osVirtualToPhysical(g_Mp3Vars.var8009c3d4[i]));
					aMp3ExecDma((*cmdList)++, g_Mp3Vars.var8009c3d8, osVirtualToPhysical(sp58));

					sp58 += 580;
				}

				g_Mp3Vars.var8009c3d8 = (g_Mp3Vars.var8009c3d8 - 0x24) & 0x1e;
				g_Mp3Vars.var8009c3cc = 0x240;
				g_Mp3Vars.dualchannel = numchannels == 2;
			} else {
				// empty
			}
		}

		mp3_dma();

		if (!g_Mp3Vars.dualchannel) {
			sp4c = 0;
		}

		if (sp54 != NULL) {
			n_aLoadBuffer((*cmdList)++, sp50 + sp50, sp4c, osVirtualToPhysical(sp54));

			if (g_Mp3Vars.dualchannel) {
				sp54 += 580;
				n_aLoadBuffer((*cmdList)++, sp50 + sp50, sp48, osVirtualToPhysical(sp54));
			}

			sp4c += sp50 + sp50;
			sp48 += sp50 + sp50;
			arg0 -= sp50;
		}

		if (arg0 > 0 && g_Mp3Vars.var8009c3c8 != NULL) {
			sp54 = &g_Mp3Vars.var8009c3c8[g_Mp3Vars.var8009c3d0];

			n_aLoadBuffer((*cmdList)++, arg0 + arg0, sp4c, osVirtualToPhysical(sp54));

			if (g_Mp3Vars.dualchannel) {
				sp54 += 580;
				n_aLoadBuffer((*cmdList)++, arg0 + arg0, sp48, osVirtualToPhysical(sp54));
			}

			g_Mp3Vars.var8009c3d0 += arg0;
		}

		mp3_update_vars(&g_Mp3Vars);

		if (!g_Mp3Vars.dualchannel) {
			aClearBuffer((*cmdList)++, N_AL_MAIN_L_OUT, N_AL_TEMP_2);
            aClearBuffer((*cmdList)++, 0x7c0, N_AL_TEMP_2);
            if (g_Mp3Vars.filter.amount > 0) {
                if (g_Mp3Vars.filter.first) n_alFxInitlpfilter_mono((ConkerNAudioOutputLP *)&g_Mp3Vars.filter, 22020.0f);
                aLoadADPCM((*cmdList)++, 0x20, osVirtualToPhysical(g_Mp3Vars.filter.coefficients) & 0xffffff);
                if (g_Mp3Vars.filter.first == 2) g_Mp3Vars.filter.first = 0;
                CONKER_AUDIO_POLE_FILTER((*cmdList)++, g_Mp3Vars.filter.first, 0, 0,
                    osVirtualToPhysical(g_Mp3Vars.filter.stateLeft) & 0xffffff);
                g_Mp3Vars.filter.first = 0;
            }

			if (g_Mp3Vars.em_first) {
				g_Mp3Vars.em_first = 0;

				g_Mp3Vars.em_ltgt = (g_Mp3Vars.em_volume * n_eqpower[g_Mp3Vars.em_pan]) >> 15;
				g_Mp3Vars.em_lratm = _getRate(g_Mp3Vars.em_cvolL, g_Mp3Vars.em_ltgt, g_Mp3Vars.em_segEnd, &g_Mp3Vars.em_lratl);

				g_Mp3Vars.em_rtgt = (g_Mp3Vars.em_volume * n_eqpower[N_EQPOWER_LENGTH - g_Mp3Vars.em_pan - 1]) >> 15;
				g_Mp3Vars.em_rratm = _getRate(g_Mp3Vars.em_cvolR, g_Mp3Vars.em_rtgt, g_Mp3Vars.em_segEnd, &g_Mp3Vars.em_rratl);

				n_aSetVolume((*cmdList)++, A_VOL | A_LEFT, g_Mp3Vars.em_cvolL, g_Mp3Vars.em_dryamt, g_Mp3Vars.em_wetamt);
				n_aSetVolume((*cmdList)++, A_VOL | A_RIGHT, g_Mp3Vars.em_rtgt, g_Mp3Vars.em_rratm, g_Mp3Vars.em_rratl);
				n_aSetVolume((*cmdList)++, A_RATE, g_Mp3Vars.em_ltgt, g_Mp3Vars.em_lratm, g_Mp3Vars.em_lratl);
				n_aEnvMixer((*cmdList)++, A_INIT, g_Mp3Vars.em_cvolR, osVirtualToPhysical(g_Mp3Vars.em_state));
			} else {
				n_aEnvMixer((*cmdList)++, A_CONTINUE, 0, osVirtualToPhysical(g_Mp3Vars.em_state));
			}

			g_Mp3Vars.em_delta += SAMPLES;

			if (g_Mp3Vars.em_delta > g_Mp3Vars.em_segEnd) {
				g_Mp3Vars.em_delta = g_Mp3Vars.em_segEnd;
			}
		}
    } else if (g_Mp3Vars.state == MP3STATE_STOPPED && __conker_mp3_level != 0x35) {
        if (__conker_mp3_assets_loaded) {
            __conker_mp3_free(var8009c650);
            __conker_mp3_free(__conker_mp3_lookup_base);
            __conker_mp3_free(__conker_mp3_huffman_base);
            __conker_mp3_assets_loaded = 0;
        }
        if (var8009c644) {
            __conker_mp3_free(var8009c644);
            var8009c644 = NULL;
        }
        g_Mp3Vars.state = MP3STATE_IDLE;
        return 0;
    } else {
        return 0;
    }
    return 1;
}

void mp3_update_vars(struct mp3vars *vars)
{
	if (vars->em_volume != vars->currentvol || vars->em_pan != vars->currentpan) {
		if (vars->em_delta >= vars->em_segEnd) {
			vars->em_ltgt = (n_eqpower[vars->em_pan] * vars->em_volume >> 15);
			vars->em_rtgt = (n_eqpower[N_EQPOWER_LENGTH - vars->em_pan - 1] * vars->em_volume >> 15);
			vars->em_delta = vars->em_segEnd;
			vars->em_cvolL = vars->em_ltgt;
			vars->em_cvolR = vars->em_rtgt;
		} else {
			vars->em_cvolL = _getVol(vars->em_cvolL, vars->em_delta, vars->em_lratm, vars->em_lratl);
			vars->em_cvolR = _getVol(vars->em_cvolR, vars->em_delta, vars->em_rratm, vars->em_rratl);
		}

		if (vars->em_cvolL == 0) {
			vars->em_cvolL = 1;
		}

		if (vars->em_cvolR == 0) {
			vars->em_cvolR = 1;
		}

		vars->em_volume = vars->currentvol;
        if (vars->em_volume == 0 && vars->var8009c3e8) mp3_stop();

		if (vars->em_pan != vars->currentpan) {
			if (__conker_audio_headphone) {
				vars->em_pan = (vars->currentpan >> 1) + 32;
			} else {
				if (__conker_audio_mono) {
					vars->em_pan = AL_PAN_CENTER;
				} else {
					vars->em_pan = vars->currentpan;
				}
			}

		}

		vars->em_delta = 0;
		vars->em_segEnd = SAMPLE184(vars->var8009c3e8);
		vars->em_first = 1;
	}
}

void mp3_set_text_callback(void *fn)
{
    g_Mp3Vars.textCallback = fn;
}

void mp3_set_dma_func(void *fn)
{
    g_Mp3Vars.dmafunc = fn;
}

s32 mp3_handle_dma(s32 arg0, u8 *dst, s32 len, s32 dmaoffset)
{
    u8 *bufptr;
    ALDMAproc proc;
    if (dmaoffset != -1) g_Mp3Vars.dmaoffset = dmaoffset;
    if (g_Mp3Vars.dmaoffset + len > g_Mp3Vars.filesize) len = g_Mp3Vars.filesize - g_Mp3Vars.dmaoffset;
    proc = n_syn->dma(&bufptr);
    bufptr = (u8 *)proc(g_Mp3Vars.romaddr + g_Mp3Vars.dmaoffset, len, NULL);
    if (bufptr == NULL) return 0;
    bufptr = (u8 *)((u32)bufptr + 0x80000000);
    osInvalDCache(bufptr, len);
    bcopy(bufptr, dst, len);
    g_Mp3Vars.dmaoffset += len;
    return len;
}

void mp3_dma(void)
{
    u8 *bufptr;
    ALDMAproc proc;
    proc = n_syn->dma(&bufptr);
    proc(g_Mp3Vars.romaddr + g_Mp3Vars.dmaoffset, 0x810, NULL);
}
