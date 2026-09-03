#include <ultra64.h>

/* Conker US 0x128D0:0x12D80: sequence/bank relocation with encoded
 * instrument addresses and an extended ADPCM wave-table field.
 */
typedef struct { ALWaveTable standard; u32 field14; } ConkerBankWave;

void _bnkfPatchBank(ALBank *bank, s32 offset, s32 table, s32 bankAddress);
void _bnkfPatchInst(ALInstrument *inst, s32 address);
void __conker_bnkfPatchPercussion(ALInstrument *, s32);
void __conker_bank_patch_sound(ALSound *s, ALInstrument *offset, void *table);
void _bnkfPatchWaveTable(ALWaveTable *w, s32 offset, s32 table);

void alSeqFileNew(ALSeqFile *file, u8 *base)
{
	s32 offset = (s32) base;
	s32 i;

	/*
	 * patch the file so that offsets are pointers
	 */
	for (i = 0; i < file->seqCount; i++) {
		file->seqArray[i].offset = (u8 *)((u8 *)file->seqArray[i].offset + offset);
	}
}

void __conker_bnkfNew(ALBankFile *file, u8 *table, s32 bankAddress)
{
	s32 offset = (s32) file;
	s32 woffset = (s32) table;
	s32 boffset = bankAddress;

	s32 i;

	/*
	 * check the file format revision in debug libraries
	 */
	if (file->revision != 0x4231) return;

	/*
	 * patch the file so that offsets are pointers
	 */
	for (i = 0; i < file->bankCount; i++) {
		file->bankArray[i] = (ALBank *)((u8 *)file->bankArray[i] + offset);

		if (file->bankArray[i]) {
			_bnkfPatchBank(file->bankArray[i], offset, woffset, boffset);
		}
	}
}

void _bnkfPatchBank(ALBank *bank, s32 offset, s32 table, s32 bankAddress)
{
    s32 i;
    s32 address;
    if (bank->flags) return;
    bank->flags = 1;
    if (bank->percussion) {
        bank->percussion = (ALInstrument *)((u8 *)bank->percussion + offset);
        __conker_bnkfPatchPercussion(bank->percussion, bankAddress);
    }
    for (i = 0; i < bank->instCount; i++) {
        if (bank->instArray[i]) {
            if (i == 0) {
                bank->instArray[i] = (ALInstrument *)((u8 *)bank->instArray[i] + offset);
                _bnkfPatchInst(bank->instArray[i], bankAddress);
            } else {
                address = (bankAddress & ~7) << 5;
                bank->instArray[i] = (ALInstrument *)((u8 *)bank->instArray[i] + address);
            }
        }
    }
}

void __conker_bnkfPatchPercussion(ALInstrument *inst, s32 address)
{
    if (inst->flags) return;
    inst->flags = 1;
    address &= ~7;
    address <<= 5;
    inst->soundArray[0] = (ALSound *)((u8 *)inst->soundArray[0] + address);
}

void _bnkfPatchInst(ALInstrument *inst, s32 address)
{
    s32 i;
    if (inst->flags) return;
    inst->flags = 1;
    address &= ~7;
    address <<= 5;
    for (i = 0; i < inst->soundCount; i++) {
        inst->soundArray[i] = (ALSound *)((u8 *)inst->soundArray[i] + address);
    }
}

void __conker_bank_patch_sound(ALSound *s, ALInstrument *offset, void *table)
{
	if (s->flags) {
		return;
	}

	s->flags = 1;

	s->envelope = (ALEnvelope *)((u8 *)s->envelope + (s32)offset);
	s->keyMap = (ALKeyMap *)((u8 *)s->keyMap + (s32)offset);

	s->wavetable = (ALWaveTable *)((u8 *)s->wavetable + (s32)offset);
	_bnkfPatchWaveTable(s->wavetable, (s32)offset, (s32)table);
}

void _bnkfPatchWaveTable(ALWaveTable *w, s32 offset, s32 table)
{
	w->flags = 1;

	w->base += table;

	if (w->type == AL_ADPCM_WAVE) {
		w->waveInfo.adpcmWave.book  = (ALADPCMBook *)((u8 *)w->waveInfo.adpcmWave.book + offset);

		if (w->waveInfo.adpcmWave.loop) {
			w->waveInfo.adpcmWave.loop = (ALADPCMloop *)((u8 *)w->waveInfo.adpcmWave.loop + offset);
		}
		((ConkerBankWave *)w)->field14 = 0;
	} else if (w->type == AL_RAW16_WAVE) {
		if (w->waveInfo.rawWave.loop) {
			w->waveInfo.rawWave.loop = (ALRawLoop *)((u8 *)w->waveInfo.rawWave.loop + offset);
		}
	}
}
