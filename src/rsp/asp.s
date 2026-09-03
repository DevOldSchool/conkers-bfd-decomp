// Derived from n64decomp/perfect_dark 169ed48bdcbfb3b568b028bd5bebb27680073514.
// See LICENSE and README.md in this directory for provenance and Conker changes.
.rsp

// flags

OS_TASK_DP_WAIT         equ 0x0002

// rdp rd flags
DPC_STATUS_XBUS_DMA     equ 0x0001
DPC_STATUS_DMA_BUSY     equ 0x0100
DPC_STATUS_START_VALID  equ 0x0400

// rdp wr flags
DPC_STATUS_CLR_XBUS     equ 0x0001

// sp status flags
SP_STATUS_SET_SIG7      equ 0x4000

.macro jumpTableEntry, addr
    .dh addr & 0xffff
.endmacro

.macro OverlayEntry, loadStart, loadEnd, imemAddr
    .dw loadStart
    .dh (loadEnd - loadStart - 1) & 0xffff
    .dh (imemAddr) & 0xffff
.endmacro

.create DATA_FILE, 0x0000

// 0x0000
data_0000: // overlay 0
    OverlayEntry orga(Overlay0Address), orga(Overlay0End), Overlay0Address
// 0x0008
data_0008: // overlay 1
    OverlayEntry orga(Overlay1Address), orga(Overlay1End), Overlay1Address

Overlay0DataLoadAddress:
Overlay1DataLoadAddress:

// OVERLAY 0 DATA
Overlay0DataStart:

// 0x0010
dispatchTable:
    jumpTableEntry cmd_DISABLE
    jumpTableEntry cmd_ADPCM
    jumpTableEntry cmd_CLEARBUFF
    jumpTableEntry cmd_ENVMIXER
    jumpTableEntry cmd_LOADBUFF
    jumpTableEntry cmd_RESAMPLE
    jumpTableEntry cmd_SAVEBUFF
    jumpTableEntry cmd_MP3
    jumpTableEntry cmd_MP3ADDY
    jumpTableEntry cmd_SETVOL
    jumpTableEntry cmd_DMEMMOVE
    jumpTableEntry cmd_LOADADPCM
    jumpTableEntry cmd_MIXER
    jumpTableEntry cmd_INTERLEAVE
    jumpTableEntry cmd_16EC
    jumpTableEntry cmd_SETLOOP

// 0x0030
data_0_0030:
.dh 0xf000, 0x0f00, 0x00f0, 0x000f, 0x0001, 0x0010, 0x0100, 0x1000

// 0x0040
data_0_0040:
.dh 0x0002, 0x0004, 0x0006, 0x0008, 0x000a, 0x000c, 0x000e, 0x0010

// 0x0050
data_0_0050:
.dh 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001

// 0x0060
data_0_0060:
.dh 0x0000, 0x0020, 0x0002, 0x0800, 0x0008, 0x7fff, 0x0100, 0x0200

// 0x0070: lane selectors for the two resampler output pairs.
data_0_0070:
.dh 0, 1, 0, 0, 0, 1, 0, 0

// 0x0080: second pair, shifted two lanes from data_0_0070.
data_0_0080:
.dh 0, 0, 0, 1, 0, 0, 0, 1

// 0x0090: fractional ramp for the envelope mixer (eighths in Q16).
data_0_0090:
.dh 0x2000, 0x4000, 0x6000, 0x8000, 0xa000, 0xc000, 0xe000, 0xffff

// 0x00a0: signed fractional gains used by the Conker envelope sign flags.
data_0_00A0:
.dh 0x999a, 0xb334, 0xcccd, 0xe667, 0x1999, 0x3333, 0x4ccc, 0x6666

// 0x00b0: reserved vector slot, before the resampling filter coefficients.
.dh 0, 0, 0, 0, 0, 0, 0, 0

// 0x00c0
data_0_00C0:
.word 0x0c3966ad, 0x0d46ffdf, 0x0b396696, 0x0e5fffd8, 0x0a446669, 0x0f83ffd0, 0x095a6626, 0x10b4ffc8
.word 0x087d65cd, 0x11f0ffbf, 0x07ab655e, 0x1338ffb6, 0x06e464d9, 0x148cffac, 0x0628643f, 0x15ebffa1
.word 0x0577638f, 0x1756ff96, 0x04d162cb, 0x18cbff8a, 0x043561f3, 0x1a4cff7e, 0x03a46106, 0x1bd7ff71
.word 0x031c6007, 0x1d6cff64, 0x029f5ef5, 0x1f0bff56, 0x022a5dd0, 0x20b3ff48, 0x01be5c9a, 0x2264ff3a
.word 0x015b5b53, 0x241eff2c, 0x010159fc, 0x25e0ff1e, 0x00ae5896, 0x27a9ff10, 0x00635720, 0x297aff02
.word 0x001f559d, 0x2b50fef4, 0xffe2540d, 0x2d2cfee8, 0xffac5270, 0x2f0dfedb, 0xff7c50c7, 0x30f3fed0
.word 0xff534f14, 0x32dcfec6, 0xff2e4d57, 0x34c8febd, 0xff0f4b91, 0x36b6feb6, 0xfef549c2, 0x38a5feb0
.word 0xfedf47ed, 0x3a95feac, 0xfece4611, 0x3c85feab, 0xfec04430, 0x3e74feac, 0xfeb6424a, 0x4060feaf
.word 0xfeaf4060, 0x424afeb6, 0xfeac3e74, 0x4430fec0, 0xfeab3c85, 0x4611fece, 0xfeac3a95, 0x47edfedf
.word 0xfeb038a5, 0x49c2fef5, 0xfeb636b6, 0x4b91ff0f, 0xfebd34c8, 0x4d57ff2e, 0xfec632dc, 0x4f14ff53
.word 0xfed030f3, 0x50c7ff7c, 0xfedb2f0d, 0x5270ffac, 0xfee82d2c, 0x540dffe2, 0xfef42b50, 0x559d001f
.word 0xff02297a, 0x57200063, 0xff1027a9, 0x589600ae, 0xff1e25e0, 0x59fc0101, 0xff2c241e, 0x5b53015b
.word 0xff3a2264, 0x5c9a01be, 0xff4820b3, 0x5dd0022a, 0xff561f0b, 0x5ef5029f, 0xff641d6c, 0x6007031c
.word 0xff711bd7, 0x610603a4, 0xff7e1a4c, 0x61f30435, 0xff8a18cb, 0x62cb04d1, 0xff961756, 0x638f0577
.word 0xffa115eb, 0x643f0628, 0xffac148c, 0x64d906e4, 0xffb61338, 0x655e07ab, 0xffbf11f0, 0x65cd087d
.word 0xffc810b4, 0x6626095a, 0xffd00f83, 0x66690a44, 0xffd80e5f, 0x66960b39, 0xffdf0d46, 0x66ad0c39

Overlay0DataEnd:

// OVERLAY 1 DATA
.headersize Overlay1DataLoadAddress - orga()
Overlay1DataStart:

// 0x0010
data_1_0010:
.dh 0xfec4, 0xfb14, 0xf4fa, 0xec84, 0xe1c4, 0xd4dc, 0xc5e4, 0xa268

// 0x0020
data_1_0020:
.dh 0x8e3a, 0x78ae, 0x61f8, 0x4a50, 0x31f2, 0x1916, 0x8000, 0x0000

// 0x0030
data_1_0030:
.dh 0xffb2, 0xfd3a, 0xf854, 0xf10a, 0xe76c, 0xdb94, 0xcda0, 0xbdae

// 0x0040
data_1_0040:
.dh 0xabec, 0x9880, 0x839c, 0xdae8, 0xac7c, 0x7c68, 0x4b20, 0x1920

// 0x0050
data_1_0050:
.dh 0xb504, 0xa57e, 0x0001, 0x6a09, 0x0002, 0xd413, 0x0005, 0xa827

// 0x0060
// ?
.dh 0x0000, 0xfff3, 0x005d, 0xff38, 0x037a, 0xf736, 0x0b37, 0xc00e
.dh 0x7fff, 0x3ff2, 0x0b37, 0x08ca, 0x037a, 0x00c8, 0x005d, 0x000d

// 0x0080
DeWindowLUT:
.word 0x0000fff3, 0x005dff38, 0x037af736, 0x0b37c00e, 0x7fff3ff2, 0x0b3708ca, 0x037a00c8, 0x005d000d
.word 0x0000fff2, 0x005fff1d, 0x0369f697, 0x0a2abce7, 0x7feb3ccb, 0x0c2b082b, 0x038500af, 0x005b000b
.word 0x0000fff2, 0x005fff1d, 0x0369f697, 0x0a2abce7, 0x7feb3ccb, 0x0c2b082b, 0x038500af, 0x005b000b
.word 0x0000fff1, 0x0061ff02, 0x0354f5f9, 0x0905b9c4, 0x7fb039a4, 0x0d08078c, 0x038c0098, 0x0058000a
.word 0x0000fff1, 0x0061ff02, 0x0354f5f9, 0x0905b9c4, 0x7fb039a4, 0x0d08078c, 0x038c0098, 0x0058000a
.word 0x0000ffef, 0x0062fee6, 0x033bf55c, 0x07c8b6a4, 0x7f4d367e, 0x0dce06ee, 0x038f0080, 0x00560009
.word 0x0000ffef, 0x0062fee6, 0x033bf55c, 0x07c8b6a4, 0x7f4d367e, 0x0dce06ee, 0x038f0080, 0x00560009
.word 0x0000ffee, 0x0063feca, 0x031cf4c3, 0x0671b38c, 0x7ec2335d, 0x0e7c0652, 0x038e006b, 0x00530008
.word 0x0000ffee, 0x0063feca, 0x031cf4c3, 0x0671b38c, 0x7ec2335d, 0x0e7c0652, 0x038e006b, 0x00530008
.word 0x0000ffec, 0x0064feac, 0x02f7f42c, 0x0502b07c, 0x7e123041, 0x0f1405b7, 0x038a0056, 0x00500007
.word 0x0000ffec, 0x0064feac, 0x02f7f42c, 0x0502b07c, 0x7e123041, 0x0f1405b7, 0x038a0056, 0x00500007
.word 0x0000ffeb, 0x0064fe8e, 0x02cef399, 0x037aad75, 0x7d3a2d2c, 0x0f970520, 0x03820043, 0x004d0007
.word 0x0000ffeb, 0x0064fe8e, 0x02cef399, 0x037aad75, 0x7d3a2d2c, 0x0f970520, 0x03820043, 0x004d0007
.word 0xffffffe9, 0x0063fe6f, 0x029ef30b, 0x01d8aa7b, 0x7c3d2a1f, 0x1004048b, 0x03770030, 0x004a0006
.word 0xffffffe9, 0x0063fe6f, 0x029ef30b, 0x01d8aa7b, 0x7c3d2a1f, 0x1004048b, 0x03770030, 0x004a0006
.word 0xffffffe7, 0x0062fe4f, 0x0269f282, 0x001fa78d, 0x7b1a271c, 0x105d03f9, 0x036a001f, 0x00460006
.word 0xffffffe7, 0x0062fe4f, 0x0269f282, 0x001fa78d, 0x7b1a271c, 0x105d03f9, 0x036a001f, 0x00460006
.word 0xffffffe4, 0x0061fe2f, 0x022ff1ff, 0xfe4ca4af, 0x79d32425, 0x10a2036c, 0x03590010, 0x00430005
.word 0xffffffe4, 0x0061fe2f, 0x022ff1ff, 0xfe4ca4af, 0x79d32425, 0x10a2036c, 0x03590010, 0x00430005
.word 0xffffffe2, 0x005efe10, 0x01eef184, 0xfc61a1e1, 0x78692139, 0x10d302e3, 0x03460001, 0x00400004
.word 0xffffffe2, 0x005efe10, 0x01eef184, 0xfc61a1e1, 0x78692139, 0x10d302e3, 0x03460001, 0x00400004
.word 0xffffffe0, 0x005bfdf0, 0x01a8f111, 0xfa5f9f27, 0x76db1e5c, 0x10f2025e, 0x0331fff3, 0x003d0004
.word 0xffffffe0, 0x005bfdf0, 0x01a8f111, 0xfa5f9f27, 0x76db1e5c, 0x10f2025e, 0x0331fff3, 0x003d0004
.word 0xffffffde, 0x0057fdd0, 0x015bf0a7, 0xf8459c80, 0x752c1b8e, 0x110001de, 0x0319ffe7, 0x003a0003
.word 0xffffffde, 0x0057fdd0, 0x015bf0a7, 0xf8459c80, 0x752c1b8e, 0x110001de, 0x0319ffe7, 0x003a0003
.word 0xfffeffdb, 0x0053fdb0, 0x0108f046, 0xf61399ee, 0x735c18d1, 0x10fd0163, 0x0300ffdc, 0x00370003
.word 0xfffeffdb, 0x0053fdb0, 0x0108f046, 0xf61399ee, 0x735c18d1, 0x10fd0163, 0x0300ffdc, 0x00370003
.word 0xfffeffd8, 0x004dfd90, 0x00b0eff0, 0xf3cc9775, 0x716c1624, 0x10ea00ee, 0x02e5ffd2, 0x00330003
.word 0xfffeffd8, 0x004dfd90, 0x00b0eff0, 0xf3cc9775, 0x716c1624, 0x10ea00ee, 0x02e5ffd2, 0x00330003
.word 0xfffeffd6, 0x0047fd72, 0x0051efa6, 0xf16f9514, 0x6f5e138a, 0x10c8007e, 0x02caffc9, 0x00300003
.word 0xfffeffd6, 0x0047fd72, 0x0051efa6, 0xf16f9514, 0x6f5e138a, 0x10c8007e, 0x02caffc9, 0x00300003
.word 0xfffeffd3, 0x0040fd54, 0xffecef68, 0xeefc92cd, 0x6d331104, 0x10980014, 0x02acffc0, 0x002d0002
.word 0xfffeffd3, 0x0040fd54, 0xffecef68, 0xeefc92cd, 0x6d331104, 0x10980014, 0x02acffc0, 0x002d0002
.word 0x0030ffc9, 0x02ca007e, 0x10c8138a, 0x6f5e9514, 0xf16fefa6, 0x0051fd72, 0x0047ffd6, 0xfffe0003
.word 0x0030ffc9, 0x02ca007e, 0x10c8138a, 0x6f5e9514, 0xf16fefa6, 0x0051fd72, 0x0047ffd6, 0xfffe0003
.word 0x0033ffd2, 0x02e500ee, 0x10ea1624, 0x716c9775, 0xf3cceff0, 0x00b0fd90, 0x004dffd8, 0xfffe0003
.word 0x0033ffd2, 0x02e500ee, 0x10ea1624, 0x716c9775, 0xf3cceff0, 0x00b0fd90, 0x004dffd8, 0xfffe0003
.word 0x0037ffdc, 0x03000163, 0x10fd18d1, 0x735c99ee, 0xf613f046, 0x0108fdb0, 0x0053ffdb, 0xfffe0003
.word 0x0037ffdc, 0x03000163, 0x10fd18d1, 0x735c99ee, 0xf613f046, 0x0108fdb0, 0x0053ffdb, 0xfffe0003
.word 0x003affe7, 0x031901de, 0x11001b8e, 0x752c9c80, 0xf845f0a7, 0x015bfdd0, 0x0057ffde, 0xffff0003
.word 0x003affe7, 0x031901de, 0x11001b8e, 0x752c9c80, 0xf845f0a7, 0x015bfdd0, 0x0057ffde, 0xffff0004
.word 0x003dfff3, 0x0331025e, 0x10f21e5c, 0x76db9f27, 0xfa5ff111, 0x01a8fdf0, 0x005bffe0, 0xffff0004
.word 0x003dfff3, 0x0331025e, 0x10f21e5c, 0x76db9f27, 0xfa5ff111, 0x01a8fdf0, 0x005bffe0, 0xffff0004
.word 0x00400001, 0x034602e3, 0x10d32139, 0x7869a1e1, 0xfc61f184, 0x01eefe10, 0x005effe2, 0xffff0004
.word 0x00400001, 0x034602e3, 0x10d32139, 0x7869a1e1, 0xfc61f184, 0x01eefe10, 0x005effe2, 0xffff0005
.word 0x00430010, 0x0359036c, 0x10a22425, 0x79d3a4af, 0xfe4cf1ff, 0x022ffe2f, 0x0061ffe4, 0xffff0005
.word 0x00430010, 0x0359036c, 0x10a22425, 0x79d3a4af, 0xfe4cf1ff, 0x022ffe2f, 0x0061ffe4, 0xffff0006
.word 0x0046001f, 0x036a03f9, 0x105d271c, 0x7b1aa78d, 0x001ff282, 0x0269fe4f, 0x0062ffe7, 0xffff0006
.word 0x0046001f, 0x036a03f9, 0x105d271c, 0x7b1aa78d, 0x001ff282, 0x0269fe4f, 0x0062ffe7, 0xffff0006
.word 0x004a0030, 0x0377048b, 0x10042a1f, 0x7c3daa7b, 0x01d8f30b, 0x029efe6f, 0x0063ffe9, 0xffff0006
.word 0x004a0030, 0x0377048b, 0x10042a1f, 0x7c3daa7b, 0x01d8f30b, 0x029efe6f, 0x0063ffe9, 0xffff0007
.word 0x004d0043, 0x03820520, 0x0f972d2c, 0x7d3aad75, 0x037af399, 0x02cefe8e, 0x0064ffeb, 0x00000007
.word 0x004d0043, 0x03820520, 0x0f972d2c, 0x7d3aad75, 0x037af399, 0x02cefe8e, 0x0064ffeb, 0x00000007
.word 0x00500056, 0x038a05b7, 0x0f143041, 0x7e12b07c, 0x0502f42c, 0x02f7feac, 0x0064ffec, 0x00000007
.word 0x00500056, 0x038a05b7, 0x0f143041, 0x7e12b07c, 0x0502f42c, 0x02f7feac, 0x0064ffec, 0x00000008
.word 0x0053006b, 0x038e0652, 0x0e7c335d, 0x7ec2b38c, 0x0671f4c3, 0x031cfeca, 0x0063ffee, 0x00000008
.word 0x0053006b, 0x038e0652, 0x0e7c335d, 0x7ec2b38c, 0x0671f4c3, 0x031cfeca, 0x0063ffee, 0x00000009
.word 0x00560080, 0x038f06ee, 0x0dce367e, 0x7f4db6a4, 0x07c8f55c, 0x033bfee6, 0x0062ffef, 0x00000009
.word 0x00560080, 0x038f06ee, 0x0dce367e, 0x7f4db6a4, 0x07c8f55c, 0x033bfee6, 0x0062ffef, 0x0000000a
.word 0x00580098, 0x038c078c, 0x0d0839a4, 0x7fb0b9c4, 0x0905f5f9, 0x0354ff02, 0x0061fff1, 0x0000000a
.word 0x00580098, 0x038c078c, 0x0d0839a4, 0x7fb0b9c4, 0x0905f5f9, 0x0354ff02, 0x0061fff1, 0x0000000b
.word 0x005b00af, 0x0385082b, 0x0c2b3ccb, 0x7febbce7, 0x0a2af697, 0x0369ff1d, 0x005ffff2, 0x0000000b
.word 0x005b00af, 0x0385082b, 0x0c2b3ccb, 0x7febbce7, 0x0a2af697, 0x0369ff1d, 0x005ffff2, 0x0000000d
.word 0x005d00c8, 0x037a08ca, 0x0b373ff2, 0x7fffc00e, 0x0b37f736, 0x037aff38, 0x005dfff3, 0x0000000d
.word 0x005d00c8, 0x037a08ca, 0x0b373ff2, 0x7fffc00e, 0x0b37f736, 0x037aff38, 0x005dfff3, 0x00000000

Overlay1DataEnd:

// OVERLAY 0 BSS
.headersize Overlay0DataEnd - orga()
Overlay0BssStart:

// 0x02c0
nextTaskEntry_len equ 0x140
nextTaskEntry:
    .skip 0x140

// 0x0400
adpcmTable:
    .skip 0x100

// 0x0500
data_0_0500:
    .skip 0x170

// 0x0670
data_0_0670:
    .skip 0x370

// 0x09e0
data_0_09E0:
    .skip 0x170

// 0x0b50
data_0_0B50:
    .skip 0x170

// 0x0cc0
data_0_0CC0:
    .skip 0x170

// 0x0e30
data_0_0E30:
    .skip 0x180

// 0x0fb0
data_0_0FB0_neg equ -(0x1000 - data_0_0FB0)
data_0_0FB0:
    .skip 0x10

// 0xfc0
data_0_0FC0_neg equ -(0x1000 - data_0_0FC0)
data_0_0FC0:
    .skip 0x30

Overlay0BssEnd:

.if Overlay0BssEnd > 0x1000-0x10
    .error "Not enough room in DMEM"
.endif

// OVERLAY 1 BSS
.headersize Overlay1DataEnd - orga()
Overlay1BssStart:

// 0x08a0
data_1_08A0:
    .skip 0x448

// 0x0ce8
data_1_0CE8:
    .skip 0x8

// 0x0cf0
data_1_0CF0:
    .skip 0x180

// 0x0e70
data_1_0E70:
    .skip 0x180

Overlay1BssEnd:

.if Overlay1BssEnd > 0x1000-0x10
    .error "Not enough room in DMEM"
.endif

// Shared bss

// 0x0ff0
audioStruct_0 equ 0x0
audioStruct_4 equ 0x4
audioStruct_8 equ 0x8
audioStruct_C equ 0xc
audioStruct:
    .skip 0x10

.close

.create CODE_FILE, 0x04001080

// Register names
cmd_w0 equ k0
cmd_w1 equ t9

// OVERLAY 0
Overlay0Address:

// on entry from rspboot, at contains a pointer to the OSTask
entry:
    mfc0    a1, DPC_STATUS
    lw      gp, 0x30(at)                   // task_data
    lw      k1, 0x34(at)                   // task_data_size
    andi    a0, a1, DPC_STATUS_XBUS_DMA
    beqz    a0, no_dma
     andi    a0, a1, DPC_STATUS_DMA_BUSY
    beqz    a0, no_dma
     mfc0    a0, DPC_STATUS
dpc_dma_busy:
    andi    a0, a0, DPC_STATUS_DMA_BUSY
    bgtz    a0, dpc_dma_busy
     mfc0    a0, DPC_STATUS
no_dma:
    addi    t8, zero, 0xfa0
    lw      a1, 0x10(at)                    // ucode dram addr
    lw      a0, (data_0000)(zero)          // overlay 0 start
    add     a0, a0, a1                      // convert overlay 0 start to dram addr
    sw      a0, (data_0000)(zero)
    lw      a0, (data_0008)(zero)          // overlay 1 start
    add     a0, a0, a1                      // convert overlay 1 start to dram addr
    sw      a0, (data_0008)(zero)
    lw      a1, 0x18(at)                    // ucode_data dram addr
    sw      a1, (audioStruct + 0x8)(zero)   // save ucode_data dram addr
    jal     load_acmd_list
     add     v0, zero, gp
    mfc0    v0, SP_DMA_BUSY

dma_wait_then_dispatch:
@@dma_busy:
    bnez    v0, @@dma_busy
     mfc0    v0, SP_DMA_BUSY
dispatch_cmd:
// Conker decrements the local batch count here, once for every command.
    lw      cmd_w0, 0(sp)                  // first cmd word
    lw      cmd_w1, 4(sp)                  // second cmd word
    addi    gp, gp, 8
    srl     at, cmd_w0, 0x17                // cmd byte << 1
    andi    at, at, 0xfe
    lh      at, (dispatchTable)(at)         // load jtbl label
    jr      at                              // enter cmd handler
     addi    k1, k1, -8                    // decrement task_data_size
    break

next_cmd:
    addi    fp, fp, -0x8
    bgtz    fp, dispatch_cmd
     addi    sp, sp, 8
    blez    k1, task_done
     ori     at, zero, SP_STATUS_SET_SIG7
    jal     load_acmd_list
     add     v0, zero, gp
    j       dma_wait_then_dispatch
     mfc0    v0, SP_DMA_BUSY

task_done:
@@dma_busy:
    mfc0    v0, SP_DMA_BUSY
    bnez    v0, @@dma_busy
     nop
    mtc0    zero, SP_SEMAPHORE
    mtc0    at, SP_STATUS
    break
forever:
    b       forever
     nop

load_acmd_list:
    addi    a1, $ra, 0
    addi    v1, k1, 0
    addi    a0, v1, -nextTaskEntry_len
    blez    a0, .L04001168
     addi    at, zero, nextTaskEntry
    addi    v1, zero, nextTaskEntry_len
.L04001168:
    addi    fp, v1, 0
    jal     dma_read
     addi    v1, v1, -1
    jr      a1
     addi    sp, zero, nextTaskEntry

/***************************************************************
 *  RDRAM -> SP Mem DMA Transfer
 *      at = SP Mem Addr
 *      v0 = RDRAM Addr
 *      v1 = Length - 1
 */
dma_read:
    mfc0    a0, SP_DMA_FULL
@@dma_full:
    bnez    a0, @@dma_full
     mfc0    a0, SP_DMA_FULL
    mtc0    at, SP_MEM_ADDR
    mtc0    v0, SP_DRAM_ADDR
    jr      $ra
     mtc0    v1, SP_RD_LEN

/***************************************************************
 *  SP Mem -> RDRAM DMA Transfer
 *      at = SP Mem Addr
 *      v0 = RDRAM Addr
 *      v1 = Length - 1
 */
dma_write:
    mfc0    a0, SP_DMA_FULL
@@dma_full:
    bnez    a0, @@dma_full
     mfc0    a0, SP_DMA_FULL
    mtc0    at, SP_MEM_ADDR
    mtc0    v0, SP_DRAM_ADDR
    jr      $ra
     mtc0    v1, SP_WR_LEN

/***************************************************************
 *  Wait for ongoing DMA to complete
 */
dma_wait:
@@dma_busy:
    mfc0    a0, SP_DMA_BUSY
    bnez    a0, @@dma_busy
     nop
    jr      $ra
     nop

/***************************************************************
 *  Loads overlay 0 once overlay 1 exits
 */
reload_overlay_0:
    lh      v1, (data_0000 + 0x4)(zero)
    lw      v0, (data_0000 + 0x0)(zero)
    lh      at, (data_0008 + 0x6)(zero)
    add     v0, v0, at
    sub     v1, v1, at
    lh      at, (data_0000 + 0x6)(zero)
    sub     v0, v0, at
    add     v1, v1, at
    jal     dma_read
     lh      at, (data_0008 + 0x6)(zero)
    lw      v0, (audioStruct + 0x8)(zero)        // ucode_data dram addr
    addi    v0, v0, orga(Overlay0DataStart)
    addi    at, zero, orga(Overlay0DataLoadAddress)
    jal     dma_read
     addi    v1, zero, org(Overlay0DataEnd)-org(Overlay0DataStart)-1
    jal     dma_wait
     nop
    j       next_cmd
     nop

/***************************************************************
 *  Loads overlay 1 and enters the proper handler for the MP3 cmd
 */
cmd_MP3:
    lh      at, (data_0008 + 0x6)(zero)        // Load overlay 1 imem addr
    lw      v0, (data_0008 + 0x0)(zero)        // Load overlay 1 dram addr
    jal     dma_read
     lh      v1, (data_0008 + 0x4)(zero)        // load overlay 1 length
    jal     dma_wait
     nop
    j       cmd_MP3_overlay1                    // jump to overlay 1 code
     nop

    nop
.align 8
Overlay1LoadAddress:
    nop
    nop

/***************************************************************
 *  ZZXXAAAA XXXXBBBB
 *      Z = cmd
 *      X = pad
 *      A = dmem addr
 *      B = length
 */
cmd_CLEARBUFF:
    andi    v0, cmd_w1, 0xffff      // load length
    vxor    $v1, $v1, $v1           // Zero out $v1
    addi    at, cmd_w0, data_0_0500
@@loop:
    sdv     $v1[0], 0x0(at)         // Store zero'd $v1
    sdv     $v1[0], 0x8(at)
    addi    v0, v0, -0x10
    bgtz    v0, @@loop              // loop until whole region is cleared
     addi    at, at, 0x10
    j       next_cmd
     nop


cmd_LOADBUFF:
    sll     v1, cmd_w0, 8
    srl     v1, v1, 0x14
    beqz    v1, next_cmd
     addi    at, cmd_w0, data_0_0500
    sll     v0, cmd_w1, 8
    srl     v0, v0, 8
    jal     dma_read
     addi    v1, v1, -1
    mfc0    at, SP_DMA_BUSY
@@dma_busy:
    bnez    at, @@dma_busy
     mfc0    at, SP_DMA_BUSY
    j       next_cmd
     nop


cmd_SAVEBUFF:
    sll     v1, cmd_w0, 8
    srl     v1, v1, 0x14
    beqz    v1, next_cmd
     addi    at, cmd_w0, data_0_0500
    sll     v0, cmd_w1, 8
    srl     v0, v0, 8
    jal     dma_write
     addi    v1, v1, -1
    mfc0    at, SP_DMA_BUSY
@@dma_busy:
    bnez    at, @@dma_busy
     mfc0    at, SP_DMA_BUSY
    j       next_cmd
     nop


cmd_LOADADPCM:
    sll     v0, cmd_w1, 8
    srl     v0, v0, 8
    addi    at, zero, adpcmTable
    andi    v1, cmd_w0, 0xffff
    jal     dma_read
     addi    v1, v1, -1
    mfc0    at, SP_DMA_BUSY
@@dma_busy:
    bnez    at, @@dma_busy
     mfc0    at, SP_DMA_BUSY
    j       next_cmd
     nop


cmd_SETVOL:
    srl     v1, cmd_w0, 0x10
    andi    at, v1, 4
    beqz    at, .L04001340
     andi    at, v1, 2
    beqz    at, .L04001334
     srl     v0, cmd_w1, 0x10
    sh      cmd_w0, 0x50(t8)
    sh      v0, 0x4c(t8)
    sh      cmd_w1, 0x4e(t8)
.L04001334:
    sh      cmd_w0, 0x46(t8)
    sh      v0, 0x48(t8)
    sh      cmd_w1, 0x4a(t8)
.L04001340:
    srl     v0, cmd_w1, 0x10
    sh      cmd_w0, 0x40(t8)
    sh      v0, 0x42(t8)
    j       next_cmd
     sh      cmd_w1, 0x44(t8)


cmd_INTERLEAVE:
    addi    at, zero, 0x170
    addi    a0, zero, data_0_0500
    addi    v0, zero, data_0_09E0
    addi    v1, zero, data_0_0B50
@@loop:
    lqv     $v1[0], 0x0(v0)
    lqv     $v2[0], 0x0(v1)
    addi    at, at, -0x10
    addi    v0, v0, 0x10
    addi    v1, v1, 0x10
    ssv     $v1[0], 0x0(a0)
    ssv     $v2[0], 0x2(a0)
    ssv     $v1[2], 0x4(a0)
    ssv     $v2[2], 0x6(a0)
    ssv     $v1[4], 0x8(a0)
    ssv     $v2[4], 0xa(a0)
    ssv     $v1[6], 0xc(a0)
    ssv     $v2[6], 0xe(a0)
    ssv     $v1[8], 0x10(a0)
    ssv     $v2[8], 0x12(a0)
    ssv     $v1[10], 0x14(a0)
    ssv     $v2[10], 0x16(a0)
    ssv     $v1[12], 0x18(a0)
    ssv     $v2[12], 0x1a(a0)
    ssv     $v1[14], 0x1c(a0)
    ssv     $v2[14], 0x1e(a0)
    bgtz    at, @@loop
     addi    a0, a0, 0x20
    j       next_cmd
     nop


cmd_DMEMMOVE:
    andi    at, cmd_w1, 0xffff
    addi    v0, cmd_w0, data_0_0500
    srl     v1, cmd_w1, 0x10
    addi    v1, v1, 0x500
@@loop:
    ldv     $v1[0], 0x0(v0)
    ldv     $v2[0], 0x8(v0)
    addi    at, at, -0x10
    addi    v0, v0, 0x10
    sdv     $v1[0], 0x0(v1)
    sdv     $v2[0], 0x8(v1)
    bgtz    at, @@loop
     addi    v1, v1, 0x10
    j       next_cmd
     nop


cmd_SETLOOP:
    sll     at, cmd_w1, 8
    srl     at, at, 8
    j       next_cmd
     sw      at, (audioStruct + 0xc)(zero)

/***************************************************************
 *  ZZAAAAAA XXBBBBBB
 *      Z = cmd
 *      X = padding
 *      A = ?
 *      B = rdram address
 */
cmd_MP3ADDY:
// Conker stores the MP3 pointer only; the command high word is unused.
    sll     at, cmd_w1, 8                   // remove top 8 bits
    srl     at, at, 8
    j       next_cmd
     sw      at, (audioStruct + 0x4)(zero)    // store 24-bit value


cmd_ADPCM:
    lqv     $v31[0], (data_0_0060)(zero)
    srl     s7, cmd_w1, 0xc
    vxor    $v25, $v25, $v25
    andi    s7, s7, 0xf
    vxor    $v24, $v24, $v24
    addi    s7, s7, 0x500
    vxor    $v13, $v13, $v13
    andi    at, cmd_w1, 0xfff
    vxor    $v14, $v14, $v14
    addi    at, at, 0x500
    vxor    $v15, $v15, $v15
    srl     s5, cmd_w1, 0x10
    vxor    $v16, $v16, $v16
    andi    s5, s5, 0xfff
    vxor    $v17, $v17, $v17
    sll     s4, cmd_w0, 8
    vxor    $v18, $v18, $v18
    srl     s4, s4, 8
    vxor    $v19, $v19, $v19
    addi    v1, zero, 0x20-1
    srl     t5, cmd_w1, 0x1c
    andi    v0, t5, 1
    bgtz    v0, .L040014F4
     addi    s6, s7, 1
    andi    v0, t5, 2
    beqz    v0, .L040014AC
     addi    v0, s4, 0
    lw      v0, (audioStruct + 0xc)(zero)
.L040014AC:
    mfc0    t5, SP_DMA_FULL
@@dma_full:
    bnez    t5, @@dma_full
     mfc0    t5, SP_DMA_FULL
    mtc0    at, SP_MEM_ADDR
    mtc0    v0, SP_DRAM_ADDR
    mtc0    v1, SP_RD_LEN
    addi    s3, zero, data_0_0030
    addi    s2, zero, adpcmTable
    ldv     $v25[0], 0x0(s3)
    ldv     $v24[8], 0x0(s3)
    ldv     $v23[0], 0x8(s3)
    ldv     $v23[8], 0x8(s3)
    mfc0    a1, SP_DMA_BUSY
.L040014E0:
    bnez    a1, .L040014E0
     mfc0    a1, SP_DMA_BUSY
    add     zero, zero, zero
    j       .L040014EC
     lqv     $v27[0], 0x10(at)
.L040014F4:
    addi    s3, zero, data_0_0030
    vxor    $v27, $v27, $v27
    addi    s2, zero, adpcmTable
    ldv     $v25[0], 0x0(s3)
    ldv     $v24[8], 0x0(s3)
    ldv     $v23[0], 0x8(s3)
    ldv     $v23[8], 0x8(s3)
    sqv     $v27[0], 0x0(at)
    sqv     $v27[0], 0x10(at)
.L040014EC:
    beqz    s5, .L040016C8
     addi    at, at, 0x20
    ldv     $v12[0], 0x0(s6)
    lbu     t2, (s7)
    addi    t5, zero, 0xc
    addi    t4, zero, 1
    andi    t6, t2, 0xf
    sll     t6, t6, 5
    vand    $v10, $v25, $v12[0]
    add     s0, t6, s2
    vand    $v9, $v24, $v12[1]
    srl     s1, t2, 4
    vand    $v8, $v25, $v12[2]
    sub     s1, t5, s1
    vand    $v7, $v24, $v12[3]
    addi    t5, s1, -1
    sll     t4, t4, 0xf
    srlv    t3, t4, t5
    mtc2    t3, $v22[0]
    lqv     $v21[0], 0x0(s0)
    lqv     $v20[0], 0x10(s0)
    addi    s0, s0, -2
    lrv     $v19[0], 0x20(s0)
    addi    s0, s0, -2
    lrv     $v18[0], 0x20(s0)
    addi    s0, s0, -2
    lrv     $v17[0], 0x20(s0)
    addi    s0, s0, -2
    lrv     $v16[0], 0x20(s0)
    addi    s0, s0, -2
    lrv     $v15[0], 0x20(s0)
    addi    s0, s0, -2
    lrv     $v14[0], 0x20(s0)
    addi    s0, s0, -2
    lrv     $v13[0], 0x20(s0)
.L040015A4:
    addi    s6, s6, 9
    vmudn   $v30, $v10, $v23
    addi    s7, s7, 9
    vmadn   $v30, $v9, $v23
    lbu     t2, (s7)
    vmudn   $v29, $v8, $v23
    ldv     $v12[0], 0x0(s6)
    vmadn   $v29, $v7, $v23
    addi    t5, zero, 0xc
    blez    s1, .L040015D8
     andi    t6, t2, 0xf
    vmudm   $v30, $v30, $v22[0]
    vmudm   $v29, $v29, $v22[0]
.L040015D8:
    sll     t6, t6, 5
    vmudh   $v11, $v21, $v27[6]
    add     s0, t6, s2
    vmadh   $v11, $v20, $v27[7]
    vmadh   $v11, $v19, $v30[0]
    vmadh   $v11, $v18, $v30[1]
    srl     s1, t2, 4
    vmadh   $v11, $v17, $v30[2]
    vmadh   $v11, $v16, $v30[3]
    sub     s1, t5, s1
    vmadh   $v28, $v15, $v30[4]
    addi    t5, s1, -1
    vmadh   $v11, $v14, $v30[5]
    vmadh   $v11, $v13, $v30[6]
    vmadh   $v11, $v30, $v31[3]
    srlv    t3, t4, t5
    vsar    $v26, $v6, $v28[1]
    mtc2    t3, $v22[0]
    vsar    $v28, $v6, $v28[0]
    vand    $v10, $v25, $v12[0]
    vand    $v9, $v24, $v12[1]
    vand    $v8, $v25, $v12[2]
    vand    $v7, $v24, $v12[3]
    vmudn   $v11, $v26, $v31[1]
    vmadh   $v28, $v28, $v31[1]
    vmudh   $v11, $v19, $v29[0]
    addi    t7, s0, -2
    vmadh   $v11, $v18, $v29[1]
    lrv     $v19[0], 0x20(t7)
    vmadh   $v11, $v17, $v29[2]
    addi    t7, t7, -2
    vmadh   $v11, $v16, $v29[3]
    lrv     $v18[0], 0x20(t7)
    vmadh   $v11, $v15, $v29[4]
    addi    t7, t7, -2
    vmadh   $v11, $v14, $v29[5]
    lrv     $v17[0], 0x20(t7)
    vmadh   $v11, $v13, $v29[6]
    addi    t7, t7, -2
    vmadh   $v11, $v29, $v31[3]
    lrv     $v16[0], 0x20(t7)
    vmadh   $v11, $v21, $v28[6]
    addi    t7, t7, -2
    vmadh   $v11, $v20, $v28[7]
    lrv     $v15[0], 0x20(t7)
    vsar    $v26, $v6, $v27[1]
    addi    t7, t7, -2
    vsar    $v27, $v6, $v27[0]
    lrv     $v14[0], 0x20(t7)
    addi    t7, t7, -2
    lrv     $v13[0], 0x20(t7)
    lqv     $v21[0], 0x0(s0)
    vmudn   $v11, $v26, $v31[1]
    lqv     $v20[0], 0x10(s0)
    vmadh   $v27, $v27, $v31[1]
    addi    s5, s5, -0x20
    sqv     $v28[0], 0x0(at)
    addi    at, at, 0x20
    bgtz    s5, .L040015A4
     sqv     $v27[0], -0x10(at)
.L040016C8:
    addi    at, at, -0x20
    jal     dma_write
     addi    v0, s4, 0
    mfc0    a1, SP_DMA_BUSY
@@dma_busy:
    bnez    a1, @@dma_busy
     mfc0    a1, SP_DMA_BUSY
    j       next_cmd
     and     zero, zero, zero


cmd_16EC:
    addi    s4, zero, adpcmTable
    vxor    $v26, $v26, $v26
    lw      s1, (s4)
    beqz    s1, .L0400196C
     addi    s7, cmd_w0, 0x500
    ldv     $v18[0], 0x0(s4)
    vxor    $v25, $v25, $v25
    add     v0, cmd_w1, zero
    addi    s5, s7, -4
    addi    s3, s7, -2
    vxor    $v24, $v24, $v24
    vxor    $v23, $v23, $v23
    addi    v1, zero, 7
    vxor    $v22, $v22, $v22
    addi    s6, zero, 0x170
    vxor    $v21, $v21, $v21
    srl     s0, cmd_w0, 0x10
    vxor    $v20, $v20, $v20
    andi    s0, s0, 1
    vxor    $v19, $v19, $v19
    lw      s2, 2(s4)
    bgtz    s0, .L040017C0
     addi    at, t8, 0
    mfc0    s0, SP_DMA_FULL
@@dma_full:
    bnez    s0, @@dma_full
     mfc0    s0, SP_DMA_FULL
    mtc0    at, SP_MEM_ADDR
    mtc0    v0, SP_DRAM_ADDR
    mtc0    v1, SP_RD_LEN
    llv     $v26[0], 0x10(s4)
    addi    s4, s4, -2
    ldv     $v25[0], 0x10(s4)
    addi    s4, s4, 2
    llv     $v24[4], 0x10(s4)
    addi    s4, s4, -2
    ldv     $v23[4], 0x10(s4)
    addi    s4, s4, 2
    llv     $v22[8], 0x10(s4)
    addi    s4, s4, -2
    ldv     $v21[8], 0x10(s4)
    addi    s4, s4, 2
    llv     $v20[12], 0x10(s4)
    lsv     $v19[14], 0x10(s4)
    lsv     $v19[0], 0x12(s4)
    mfc0    a1, SP_DMA_BUSY
@@dma_busy:
    bnez    a1, @@dma_busy
     mfc0    a1, SP_DMA_BUSY
    llv     $v15[0], 0x0(at)
    beqz    s2, .L0400180C
     llv     $v28[12], 0x4(at)
    j       .L0400182C
     lsv     $v11[0], 0x2(at)
.L040017C0:
    llv     $v26[0], 0x10(s4)
    addi    s4, s4, -2
    vxor    $v15, $v15, $v15
    ldv     $v25[0], 0x10(s4)
    addi    s4, s4, 2
    vxor    $v11, $v11, $v11
    llv     $v24[4], 0x10(s4)
    addi    s4, s4, -2
    vxor    $v28, $v28, $v28
    ldv     $v23[4], 0x10(s4)
    addi    s4, s4, 2
    llv     $v22[8], 0x10(s4)
    addi    s4, s4, -2
    ldv     $v21[8], 0x10(s4)
    addi    s4, s4, 2
    llv     $v20[12], 0x10(s4)
    lsv     $v19[14], 0x10(s4)
    bnez    s2, .L0400182C
     lsv     $v19[0], 0x12(s4)
.L0400180C:
    lqv     $v30[0], 0x0(s7)
    lrv     $v15[0], 0x10(s5)
    vsub    $v31, $v30, $v15
    vmulf   $v16, $v19, $v28[6]
    vmulf   $v31, $v31, $v18[0]
    vadd    $v16, $v16, $v16
    j       .L04001824
     vmov    $v29[7], $v28[7]
.L0400182C:
    lqv     $v30[0], 0x0(s7)
    lrv     $v11[0], 0x10(s3)
    lrv     $v15[0], 0x10(s5)
    vmulf   $v30, $v30, $v18[0]
    vmulf   $v11, $v11, $v18[1]
    vmulf   $v15, $v15, $v18[0]
    vmulf   $v16, $v19, $v28[6]
    vadd    $v31, $v30, $v11
    vadd    $v16, $v16, $v16
    vadd    $v31, $v31, $v15
.L04001854:
    vmulf   $v17, $v26, $v28[7]
    vadd    $v27, $v16, $v31[0]
    vmov    $v29[7], $v28[7]
    addi    s6, s6, -0x10
    vadd    $v17, $v17, $v17
    vadd    $v28, $v27, $v17
    vadd    $v27, $v17, $v31[1]
    vmulf   $v16, $v25, $v28[0]
    vor     $v14, $v29, $v29
    lqv     $v11[0], 0x10(s3)
    vmov    $v29[0], $v28[0]
    vadd    $v16, $v16, $v16
    vadd    $v28, $v27, $v16
    vadd    $v27, $v16, $v31[2]
    vmulf   $v17, $v24, $v28[1]
    lrv     $v11[0], 0x20(s3)
    bnez    s2, .L040018A0
     vmov    $v29[1], $v28[1]
    sqv     $v14[0], -0x10(s7)
.L040018A0:
    vadd    $v17, $v17, $v17
    vadd    $v28, $v27, $v17
    or      s2, zero, zero
    vadd    $v27, $v17, $v31[3]
    vmulf   $v16, $v23, $v28[2]
    vmov    $v29[2], $v28[2]
    vmulf   $v11, $v11, $v18[1]
    lqv     $v30[0], 0x10(s7)
    vadd    $v16, $v16, $v16
    vadd    $v28, $v27, $v16
    vadd    $v27, $v16, $v31[4]
    vmulf   $v17, $v22, $v28[3]
    vmov    $v29[3], $v28[3]
    vadd    $v17, $v17, $v17
    lqv     $v15[0], 0x10(s5)
    vmulf   $v30, $v30, $v18[0]
    vadd    $v28, $v27, $v17
    vadd    $v27, $v17, $v31[5]
    vmulf   $v16, $v21, $v28[4]
    vmov    $v29[4], $v28[4]
    vadd    $v16, $v16, $v16
    lrv     $v15[0], 0x20(s5)
    vadd    $v11, $v11, $v30
    vadd    $v28, $v27, $v16
    vadd    $v27, $v16, $v31[6]
    vmulf   $v17, $v20, $v28[5]
    vmov    $v29[5], $v28[5]
    vmulf   $v13, $v15, $v18[0]
    vadd    $v17, $v17, $v17
    vadd    $v28, $v27, $v17
    vadd    $v27, $v17, $v31[7]
    vmulf   $v16, $v19, $v28[6]
    addi    s5, s5, 0x10
    vmov    $v29[6], $v28[6]
    addi    s3, s3, 0x10
    vadd    $v31, $v11, $v13
    vadd    $v16, $v16, $v16
    vadd    $v28, $v27, $v16
    bgtz    s6, .L04001854
     addi    s7, s7, 0x10
    vmov    $v29[7], $v28[7]
.L04001824:
    vor     $v14, $v29, $v29
    slv     $v15[0], 0x0(at)
    slv     $v29[12], 0x4(at)
    jal     dma_write
     sqv     $v14[0], -0x10(s7)
    mfc0    a1, SP_DMA_BUSY
@@dma_busy:
    bnez    a1, @@dma_busy
     mfc0    a1, SP_DMA_BUSY
    j       next_cmd
     nop
.L0400196C:
    srl     s3, cmd_w1, 0x18
    addi    s4, zero, adpcmTable
    vxor    $v21, $v21, $v21
    beqz    s3, .L04001984
     addi    s7, zero, data_0_0500
    addi    s7, zero, data_0_0670
.L04001984:
    lqv     $v28[0], 0x10(s4)
    vxor    $v22, $v22, $v22
    mtc2    cmd_w0, $v18[10]
    vxor    $v23, $v23, $v23
    sll     cmd_w0, cmd_w0, 2
    vxor    $v24, $v24, $v24
    mtc2    cmd_w0, $v20[0]
    vxor    $v25, $v25, $v25
    sll     v0, cmd_w1, 8
    vxor    $v26, $v26, $v26
    srl     v0, v0, 8
    vxor    $v27, $v27, $v27
    addi    v1, zero, 7
    addi    s3, zero, 4
    mtc2    s3, $v18[0]
    addi    s6, zero, 0x170
    vmudm   $v20, $v28, $v20[0]
    srl     s3, cmd_w0, 0x10
    andi    s3, s3, 1
    bgtz    s3, .L04001A40
     sqv     $v20[0], 0x10(s4)
    addi    at, t8, 0
    mfc0    s3, SP_DMA_FULL
@@dma_full:
    bnez    s3, @@dma_full
     mfc0    s3, SP_DMA_FULL
    mtc0    at, SP_MEM_ADDR
    mtc0    v0, SP_DRAM_ADDR
    mtc0    v1, SP_RD_LEN
    addi    s4, s4, -2
    lrv     $v27[0], 0x20(s4)
    addi    s4, s4, -2
    lrv     $v26[0], 0x20(s4)
    addi    s4, s4, -2
    lrv     $v25[0], 0x20(s4)
    addi    s4, s4, -2
    lrv     $v24[0], 0x20(s4)
    addi    s4, s4, -2
    lrv     $v23[0], 0x20(s4)
    addi    s4, s4, -2
    lrv     $v22[0], 0x20(s4)
    addi    s4, s4, -2
    lrv     $v21[0], 0x20(s4)
    mfc0    a1, SP_DMA_BUSY
@@dma_busy:
    bnez    a1, @@dma_busy
     mfc0    a1, SP_DMA_BUSY
    j       .L04001A7C
     ldv     $v30[8], 0x0(at)
.L04001A40:
    addi    s4, s4, -2
    vxor    $v30, $v30, $v30
    lrv     $v27[0], 0x20(s4)
    addi    s4, s4, -2
    lrv     $v26[0], 0x20(s4)
    addi    s4, s4, -2
    lrv     $v25[0], 0x20(s4)
    addi    s4, s4, -2
    lrv     $v24[0], 0x20(s4)
    addi    s4, s4, -2
    lrv     $v23[0], 0x20(s4)
    addi    s4, s4, -2
    lrv     $v22[0], 0x20(s4)
    addi    s4, s4, -2
    lrv     $v21[0], 0x20(s4)
.L04001A7C:
    lqv     $v31[0], 0x0(s7)
.L04001A80:
    vmudh   $v20, $v28, $v30[7]
    vmadh   $v20, $v27, $v31[0]
    addi    s6, s6, -0x10
    vmadh   $v20, $v26, $v31[1]
    vmadh   $v20, $v25, $v31[2]
    sqv     $v30[0], -0x10(s7)
    vmadh   $v20, $v24, $v31[3]
    vmadh   $v30, $v23, $v31[4]
    vmadh   $v20, $v22, $v31[5]
    vmadh   $v20, $v21, $v31[6]
    vmadh   $v20, $v31, $v18[5]
    lqv     $v31[0], 0x10(s7)
    vsar    $v29, $v19, $v30[1]
    vsar    $v30, $v19, $v30[0]
    vmudn   $v20, $v29, $v18[0]
    vmadh   $v30, $v30, $v18[0]
    bgtz    s6, .L04001A80
     addi    s7, s7, 0x10
    addi    at, s7, -8
    jal     dma_write
     sqv     $v30[0], -0x10(s7)
    mfc0    a1, SP_DMA_BUSY
@@dma_busy:
    bnez    a1, @@dma_busy
     mfc0    a1, SP_DMA_BUSY
    j       next_cmd
     nop


cmd_DISABLE:
    addi    v0, zero, 0x170
    addi    at, cmd_w0, data_0_0500
    mtc2    cmd_w1, $v1[0]
    srl     v1, cmd_w1, 0x10
    mtc2    v1, $v1[2]
@@loop:
    lqv     $v2[0], 0x0(at)
    addi    v0, v0, -0x10
    addi    at, at, 0x10
    vmudh   $v3, $v2, $v1[0]
    vmudm   $v3, $v3, $v1[1]
    bgtz    v0, @@loop
     sqv     $v3[0], -0x10(at)
    j       next_cmd
     addi    fp, fp, -8


cmd_RESAMPLE:
    sll     v0, cmd_w0, 8
    vxor    $v23, $v23, $v23
    srl     v0, v0, 8
    addi    v1, zero, 0x10-1
    srl     s5, cmd_w1, 0x1e
    bgtz    s5, .L04001B80
     addi    at, t8, 0
    mfc0    a0, SP_DMA_FULL
@@dma_full:
    bnez    a0, @@dma_full
     mfc0    a0, SP_DMA_FULL
    mtc0    at, SP_MEM_ADDR
    mtc0    v0, SP_DRAM_ADDR
    mtc0    v1, SP_RD_LEN
    srl     s4, cmd_w1, 2
    addi    s4, s4, 0x4f8
    lqv     $v31[0], (data_0_0050)(zero)
    lqv     $v25[0], (data_0_0040)(zero)
    mfc0    a1, SP_DMA_BUSY
@@dma_busy:
    bnez    a1, @@dma_busy
     mfc0    a1, SP_DMA_BUSY
    ldv     $v19[0], 0x0(t8)
    j       .L04001B9C
     lsv     $v24[14], 0x8(t8)
.L04001B80:
    srl     s4, cmd_w1, 2
    addi    s4, s4, 0x4f8
    lqv     $v31[0], (data_0_0050)(zero)
    vxor    $v19, $v19, $v19
    lqv     $v25[0], (data_0_0040)(zero)
    vxor    $v24, $v24, $v24
.L04001B9C:
    mtc2    s4, $v21[4]
    addi    a0, zero, data_0_00C0
    mtc2    a0, $v21[6]
    vsub    $v25, $v25, $v31
    srl     a0, cmd_w1, 0xe
    mtc2    a0, $v21[8]
    addi    a0, zero, 0x40
    mtc2    a0, $v21[10]
    vsub    $v25, $v25, $v31
    sdv     $v19[0], 0(s4)
    lqv     $v28[0], (data_0_0070)(zero)
    lqv     $v30[0], (data_0_0060)(zero)
    vmudm   $v24, $v31, $v24[7]
    vmadm   $v23, $v25, $v21[4]
    addi    s6, zero, 0x170
    vmadn   $v24, $v31, $v30[0]
    lqv     $v26[0], (data_0_0080)(zero)
    vmudn   $v22, $v31, $v21[2]
    lqv     $v25[0], (data_0_0040)(zero)
    vmadn   $v22, $v23, $v30[2]
    vxor    $v29, $v28, $v28[1q]
    andi    a0, cmd_w1, 3
    vmudl   $v20, $v24, $v21[5]
    beqz    a0, .L04001C08
     addi    s7, zero, data_0_0500
    addi    s7, zero, data_0_0670
.L04001C08:
    ssv     $v24[7], 0x8(t8)
    vmudn   $v20, $v20, $v30[4]
    sqv     $v22[0], (data_0_0FB0_neg)(zero)
    vmadn   $v20, $v31, $v21[3]
    vxor    $v27, $v26, $v26[1q]
    sqv     $v20[0], (data_0_0FC0_neg)(zero)
    lh      s5, (data_0_0FB0 + 0)(zero)
    lh      t5, (data_0_0FB0 + 0x10)(zero)
    lh      s1, (data_0_0FB0 + 0x8)(zero)
    lh      t1, (data_0_0FB0 + 0x18)(zero)
    lh      s4, (data_0_0FB0 + 0x2)(zero)
    lh      t4, (data_0_0FB0 + 0x12)(zero)
    lh      s0, (data_0_0FB0 + 0xa)(zero)
    lh      t0, (data_0_0FB0 + 0x1a)(zero)
    lh      s3, (data_0_0FB0 + 0x4)(zero)
    lh      t3, (data_0_0FB0 + 0x14)(zero)
    lh      t7, (data_0_0FB0 + 0xc)(zero)
    lh      a3, (data_0_0FB0 + 0x1c)(zero)
    lh      s2, (data_0_0FB0 + 0x6)(zero)
    lh      t2, (data_0_0FB0 + 0x16)(zero)
    lh      t6, (data_0_0FB0 + 0xe)(zero)
    lh      a2, (data_0_0FB0 + 0x1e)(zero)
.L04001C5C:
    ldv     $v19[0], 0x0(s5)
    vmudm   $v24, $v31, $v24[7]
    ldv     $v18[0], 0x0(t5)
    vmadh   $v24, $v31, $v23[7]
    ldv     $v19[8], 0x0(s1)
    vmadm   $v23, $v25, $v21[4]
    ldv     $v18[8], 0x0(t1)
    vmadn   $v24, $v31, $v30[0]
    ldv     $v17[0], 0x0(s4)
    vmudn   $v22, $v31, $v21[2]
    ldv     $v16[0], 0x0(t4)
    ldv     $v17[8], 0x0(s0)
    vmadn   $v22, $v23, $v30[2]
    ldv     $v16[8], 0x0(t0)
    vmudl   $v20, $v24, $v21[5]
    ldv     $v15[0], 0x0(s3)
    ldv     $v14[0], 0x0(t3)
    ldv     $v15[8], 0x0(t7)
    ldv     $v14[8], 0x0(a3)
    vmudn   $v20, $v20, $v30[4]
    ldv     $v13[0], 0x0(s2)
    vmadn   $v20, $v31, $v21[3]
    ldv     $v12[0], 0x0(t2)
    ldv     $v13[8], 0x0(t6)
    vmulf   $v11, $v19, $v18
    ldv     $v12[8], 0x0(a2)
    vmulf   $v10, $v17, $v16
    sqv     $v22[0], data_0_0FB0_neg(zero)
    vmulf   $v9, $v15, $v14
    sqv     $v20[0], data_0_0FC0_neg(zero)
    lh      s5, (data_0_0FB0 + 0)(zero)
    lh      t5, (data_0_0FB0 + 0x10)(zero)
    vmulf   $v8, $v13, $v12
    lh      s1, (data_0_0FB0 + 0x8)(zero)
    vadd    $v11, $v11, $v11[1q]
    lh      t1, (data_0_0FB0 + 0x18)(zero)
    vadd    $v10, $v10, $v10[1q]
    lh      s4, (data_0_0FB0 + 0x2)(zero)
    vadd    $v9, $v9, $v9[1q]
    lh      t4, (data_0_0FB0 + 0x12)(zero)
    vadd    $v8, $v8, $v8[1q]
    lh      s0, (data_0_0FB0 + 0xa)(zero)
    vadd    $v11, $v11, $v11[2h]
    lh      t0, (data_0_0FB0 + 0x1a)(zero)
    vadd    $v10, $v10, $v10[2h]
    lh      s3, (data_0_0FB0 + 0x4)(zero)
    vadd    $v9, $v9, $v9[2h]
    lh      t3, (data_0_0FB0 + 0x14)(zero)
    vadd    $v8, $v8, $v8[2h]
    lh      t7, (data_0_0FB0 + 0xc)(zero)
    vmudn   $v7, $v29, $v11[0h]
    lh      a3, (data_0_0FB0 + 0x1c)(zero)
    vmadn   $v7, $v28, $v10[0h]
    lh      s2, (data_0_0FB0 + 0x6)(zero)
    vmadn   $v7, $v27, $v9[0h]
    lh      t2, (data_0_0FB0 + 0x16)(zero)
    vmadn   $v7, $v26, $v8[0h]
    lh      t6, (data_0_0FB0 + 0xe)(zero)
    lh      a2, (data_0_0FB0 + 0x1e)(zero)
    addi    s6, s6, -0x10
    blez    s6, .L04001D5C
     sqv     $v7[0], 0x0(s7)
    j       .L04001C5C
     addi    s7, s7, 0x10
.L04001D5C:
    ldv     $v19[0], 0x0(s5)
    ssv     $v24[0], 0x8(t8)
    jal     dma_write
     sdv     $v19[0], 0x0(t8)
    mfc0    a1, SP_DMA_BUSY
@@dma_busy:
    bnez    a1, @@dma_busy
     mfc0    a1, SP_DMA_BUSY
    j       next_cmd
     nop


cmd_ENVMIXER:
    sll     v0, cmd_w1, 8
    srl     v0, v0, 8
    lqv     $v31[0], (data_0_0050)(zero)
    lqv     $v10[0], (data_0_0060)(zero)
    lqv     $v30[0], (data_0_0090)(zero)
    vxor    $v0, $v0, $v0
    srl     t6, cmd_w0, 0x10
    andi    t7, t6, 1
    bgtz    t7, .L04001DD0
     addi    at, t8, 0
    jal     dma_read
     addi    v1, zero, 0x50-1
    mfc0    a1, SP_DMA_BUSY
@@dma_busy:
    bnez    a1, @@dma_busy
     mfc0    a1, SP_DMA_BUSY
    lqv     $v20[0], 0x0(t8)
    lqv     $v21[0], 0x10(t8)
    lqv     $v18[0], 0x20(t8)
    lqv     $v19[0], 0x30(t8)
.L04001DD0:
    lqv     $v24[0], 0x40(t8)
    addi    s0, zero, data_0_0500
    addi    s5, zero, data_0_09E0
    addi    s4, zero, data_0_0B50
    addi    s3, zero, data_0_0CC0
    addi    s2, zero, data_0_0E30
    addi    s1, zero, 0x170
    mfc2    s6, $v24[8]
// Both halfword sign flags select Conker's two envelope gain vectors.
    mfc2    t6, $v24[12]
    vand    $v9, $v31, $v24
    mfc2    t5, $v24[14]
    vsub    $v9, $v0, $v9
    andi    t6, t6, 2
    bnez    t6, env_dry_gain_ready
     lqv     $v8[0], (data_0_00A0)(zero)
    vadd    $v8, $v0, $v10[5]
env_dry_gain_ready:
    andi    t5, t5, 2
    vxor    $v9, $v9, $v10[5]
    bnez    t5, env_wet_gain_ready
     lqv     $v7[0], (data_0_00A0)(zero)
    vadd    $v7, $v0, $v10[5]
env_wet_gain_ready:
    vmulf   $v8, $v8, $v9[6]
    vmulf   $v7, $v7, $v9[7]
    beqz    t7, .L04001EDC
     mfc2    s7, $v24[2]
    addi    v1, zero, 0x4f
    vxor    $v20, $v20, $v20
    lsv     $v20[14], 0x50(t8)
    vxor    $v21, $v21, $v21
    lqv     $v17[0], 0x0(s0)
    vxor    $v18, $v18, $v18
    mtc2    cmd_w0, $v18[14]
    vmudl   $v23, $v30, $v24[2]
    lqv     $v29[0], 0x0(s5)
    vmadn   $v23, $v30, $v24[1]
    lqv     $v27[0], 0x0(s3)
    vmadh   $v20, $v31, $v20[7]
    lqv     $v28[0], 0x0(s4)
    vmadn   $v21, $v31, $v0[0]
    bgez    s7, .L04001E54
     vxor    $v19, $v19, $v19
    j       .L04001E4C
     vge     $v20, $v20, $v24[0]
.L04001E54:
    vlt     $v20, $v20, $v24[0]
.L04001E4C:
    vmulf   $v8, $v17, $v8
    vmudl   $v23, $v30, $v24[5]
    lqv     $v26[0], 0x0(s2)
    vmadn   $v23, $v30, $v24[4]
    addi    s1, s1, -0x10
    vmadh   $v18, $v31, $v18[7]
    addi    s0, s0, 0x10
    vmadn   $v19, $v31, $v0[0]
    vmulf   $v16, $v20, $v24[6]
    bgez    s6, .L04001E8C
     vmulf   $v15, $v20, $v24[7]
    j       .L04001E84
     vge     $v18, $v18, $v24[3]
.L04001E8C:
    vlt     $v18, $v18, $v24[3]
.L04001E84:
    vmulf   $v29, $v29, $v10[5]
    vmacf   $v29, $v8, $v16
    vmulf   $v27, $v27, $v10[5]
    vmacf   $v27, $v8, $v15
    vmudh   $v8, $v31, $v9[6]
    vmulf   $v17, $v17, $v7
    vmudh   $v7, $v31, $v9[7]
    vmulf   $v16, $v18, $v24[6]
    vmulf   $v15, $v18, $v24[7]
    sqv     $v29[0], 0x0(s5)
    vmulf   $v28, $v28, $v10[5]
    addi    s5, s5, 0x10
    vmacf   $v28, $v17, $v16
    sqv     $v27[0], 0x0(s3)
    vmulf   $v26, $v26, $v10[5]
    addi    s3, s3, 0x10
    vmacf   $v26, $v17, $v15
    sqv     $v28[0], 0x0(s4)
    addi    s4, s4, 0x10
    sqv     $v26[0], 0x0(s2)
    addi    s2, s2, 0x10
.L04001EDC:
    vaddc   $v21, $v21, $v24[2]
    vadd    $v20, $v20, $v24[1]
.L04001EE4:
    lqv     $v29[0], 0x0(s5)
    vaddc   $v19, $v19, $v24[5]
    lqv     $v17[0], 0x0(s0)
    bgez    s7, .L04001F00
     vadd    $v18, $v18, $v24[4]
    j       .L04001F04
     vge     $v20, $v20, $v24[0]
.L04001F00:
    vlt     $v20, $v20, $v24[0]
.L04001F04:
    vmulf   $v8, $v17, $v8
    bgez    s6, .L04001F18
     lqv     $v27[0], 0x0(s3)
    j       .L04001F10
     vge     $v18, $v18, $v24[3]
.L04001F18:
    vlt     $v18, $v18, $v24[3]
.L04001F10:
    vmulf   $v16, $v20, $v24[6]
    sqv     $v20[0], 0x0(t8)
    vmulf   $v15, $v20, $v24[7]
    sqv     $v21[0], 0x10(t8)
    vmulf   $v29, $v29, $v10[5]
    vmacf   $v29, $v8, $v16
    lqv     $v28[0], 0x0(s4)
    vmulf   $v27, $v27, $v10[5]
    lqv     $v26[0], 0x0(s2)
    vmacf   $v27, $v8, $v15
    vmudh   $v8, $v31, $v9[6]
    vmulf   $v17, $v17, $v7
    vmudh   $v7, $v31, $v9[7]
    addi    s1, s1, -0x10
    vaddc   $v21, $v21, $v24[2]
    addi    s0, s0, 0x10
    vadd    $v20, $v20, $v24[1]
    sqv     $v29[0], 0x0(s5)
    vmulf   $v16, $v18, $v24[6]
    addi    s5, s5, 0x10
    vmulf   $v15, $v18, $v24[7]
    sqv     $v27[0], 0x0(s3)
    vmulf   $v28, $v28, $v10[5]
    addi    s3, s3, 0x10
    vmacf   $v28, $v17, $v16
    vmulf   $v26, $v26, $v10[5]
    vmacf   $v26, $v17, $v15
    sqv     $v28[0], 0x0(s4)
    addi    s4, s4, 0x10
    blez    s1, .L04001F98
     sqv     $v26[0], 0x0(s2)
    j       .L04001EE4
     addi    s2, s2, 0x10
.L04001F98:
    sqv     $v18[0], 0x20(t8)
    sqv     $v19[0], 0x30(t8)
    jal     dma_write
     sqv     $v24[0], 0x40(t8)
    j       next_cmd
     nop


cmd_MIXER:
    lqv     $v31[0], (data_0_0060)(zero)
    addi    s6, cmd_w1, data_0_0500
    lqv     $v28[0], 0x0(s6)
    srl     s7, cmd_w1, 0x10
    addi    s7, s7, 0x500
    lqv     $v29[0], 0x0(s7)
    mtc2    cmd_w0, $v30[0]
    addi    s5, zero, 0x170
@@loop:
    vmulf   $v27, $v28, $v31[5]
    addi    s5, s5, -0x10
    addi    s7, s7, 0x10
    addi    s6, s6, 0x10
    vmacf   $v27, $v29, $v30[0]
    lqv     $v28[0], 0x0(s6)
    lqv     $v29[0], 0x0(s7)
    bgtz    s5, @@loop
     sqv     $v27[0], -0x10(s6)
    j       next_cmd
     nop

.align 8
Overlay0End:

.if Overlay0End > 0x04002000
    .error "Not enough room in IMEM for Overlay 0"
.endif

.headersize Overlay1LoadAddress - orga()
// OVERLAY 1
Overlay1Address:

cmd_MP3_overlay1:
    lw      s1, (audioStruct + 0x4)(zero)   // set by MP3ADDY, mp3 address?
    lw      s0, (audioStruct + 0x8)(zero)   // ucode_data dram addr
    lw      t7, (audioStruct + 0xc)(zero)
    add     v0, s1, zero
    addi    at, zero, data_1_08A0
    jal     dma_read                        // dma mp3 data
     addi    v1, zero, 0x440-1
    add     v0, s1, zero
    addi    at, zero, nextTaskEntry
    jal     dma_write                       // write part of dmem over the mp3 data
     addi    v1, zero, nextTaskEntry_len-1
    jal     dma_wait
     nop
    addi    v0, s0, orga(Overlay1DataStart)
    addi    at, zero, orga(Overlay1DataLoadAddress)
    jal     dma_read
     addi    v1, zero, org(Overlay1DataEnd)-org(Overlay1DataStart)-1
    jal     dma_wait
     nop
    sll     s5, cmd_w1, 8                  // remove top 8 bits
    srl     s5, s5, 8
    add     s6, zero, s5                 // save
    addi    v1, zero, 0x188
    addi    s4, zero, 0x480
    add     v0, zero, s5
    addi    s5, s5, 8
    addi    at, zero, data_1_0CE8
    addi    t6, zero, data_1_08A0
    addi    t5, t6, 0x220
    andi    t4, cmd_w0, 0x1e
mp3_decode_loop:
    jal     dma_read
     addi    v1, v1, -1
    addi    v1, zero, 0x180
    addi    s4, s4, -0x180
    addi    s2, zero, 0x180
    addi    s7, zero, data_1_0CF0
    jal     dma_wait
     addi    s3, zero, data_1_0E70
mp3_decode_innerloop:
    andi    t6, t6, 0xffe0
    andi    t5, t5, 0xffe0
    or      t6, t6, t4
    or      t5, t5, t4
    lsv     $v0[0], 0x0(s7)
    lsv     $v31[0], 0x3e(s7)
    lsv     $v1[0], 0x2(s7)
    lsv     $v30[0], 0x3c(s7)
    lsv     $v2[0], 0x6(s7)
    lsv     $v28[0], 0x38(s7)
    vadd    $v0, $v0, $v31
    lsv     $v3[0], 0x4(s7)
    lsv     $v29[0], 0x3a(s7)
    vadd    $v1, $v1, $v30
    lsv     $v4[0], 0xe(s7)
    lsv     $v24[0], 0x30(s7)
    vadd    $v2, $v2, $v28
    lsv     $v5[0], 0xc(s7)
    lsv     $v25[0], 0x32(s7)
    vadd    $v3, $v3, $v29
    lsv     $v6[0], 0x8(s7)
    lsv     $v27[0], 0x36(s7)
    vadd    $v4, $v4, $v24
    lsv     $v7[0], 0xa(s7)
    lsv     $v26[0], 0x34(s7)
    vadd    $v5, $v5, $v25
    lsv     $v8[0], 0x1e(s7)
    lsv     $v16[0], 0x20(s7)
    vadd    $v6, $v6, $v27
    lsv     $v9[0], 0x1c(s7)
    lsv     $v17[0], 0x22(s7)
    vadd    $v7, $v7, $v26
    lsv     $v10[0], 0x18(s7)
    lsv     $v19[0], 0x26(s7)
    vadd    $v8, $v8, $v16
    lsv     $v11[0], 0x1a(s7)
    lsv     $v18[0], 0x24(s7)
    vadd    $v9, $v9, $v17
    lsv     $v12[0], 0x10(s7)
    lsv     $v23[0], 0x2e(s7)
    vadd    $v10, $v10, $v19
    lsv     $v13[0], 0x12(s7)
    lsv     $v22[0], 0x2c(s7)
    vadd    $v11, $v11, $v18
    lsv     $v14[0], 0x16(s7)
    lsv     $v20[0], 0x28(s7)
    vadd    $v12, $v12, $v23
    lsv     $v15[0], 0x14(s7)
    lsv     $v21[0], 0x2a(s7)
    vadd    $v13, $v13, $v22
    vadd    $v14, $v14, $v20
    vadd    $v15, $v15, $v21
    jal     func_04001AB0
     nop
    lqv     $v0[0], (data_1_0050)(zero)
    vsub    $v11, $v16, $v17
    addi    t0, t6, 0x100
    vadd    $v16, $v16, $v17
    addi    t2, t5, 0x100
    vxor    $v1, $v1, $v1
    addi    t1, t6, 0x200
    vsub    $v16, $v1, $v16
    addi    t3, t5, 0x200
    vmudm   $v11, $v11, $v0[0]
    vadd    $v2, $v18, $v19
    vsub    $v3, $v18, $v19
    ssv     $v11[0], 0x0(t6)
    vsub    $v11, $v1, $v11
    ssv     $v16[0], 0x0(t3)
    ssv     $v11[0], 0x0(t5)
    vsub    $v2, $v1, $v2
    vmudm   $v17, $v3, $v0[3]
    ssv     $v2[0], 0x0(t2)
    vmadh   $v3, $v3, $v0[2]
    vadd    $v3, $v3, $v2
    ssv     $v3[0], 0x0(t0)
    vsub    $v5, $v20, $v21
    vadd    $v4, $v20, $v21
    vadd    $v6, $v22, $v23
    vsub    $v7, $v22, $v23
    vmudm   $v17, $v5, $v0[3]
    vmadh   $v5, $v5, $v0[2]
    vsub    $v4, $v1, $v4
    vmudm   $v17, $v7, $v0[5]
    ssv     $v4[0], -0x80(t3)
    vmadh   $v7, $v7, $v0[4]
    vsub    $v5, $v5, $v4
    vsub    $v4, $v1, $v4
    vadd    $v6, $v6, $v6
    vsub    $v7, $v7, $v5
    vsub    $v4, $v4, $v6
    vsub    $v5, $v5, $v6
    ssv     $v7[0], -0x80(t1)
    ssv     $v4[0], -0x80(t2)
    ssv     $v5[0], -0x80(t0)
    vsub    $v9, $v24, $v25
    vadd    $v8, $v24, $v25
    vmudm   $v17, $v9, $v0[3]
    vmadh   $v9, $v9, $v0[2]
    vsub    $v11, $v26, $v27
    vadd    $v10, $v26, $v27
    vsub    $v13, $v28, $v29
    vadd    $v2, $v8, $v9
    vmudm   $v17, $v11, $v0[5]
    vmadh   $v11, $v11, $v0[4]
    vmudm   $v17, $v13, $v0[5]
    vmadh   $v13, $v13, $v0[4]
    vadd    $v12, $v28, $v29
    vadd    $v11, $v11, $v2
    vadd    $v10, $v10, $v10
    vsub    $v13, $v13, $v2
    vadd    $v12, $v12, $v12
    vadd    $v14, $v30, $v31
    vsub    $v15, $v30, $v31
    vadd    $v3, $v8, $v10
    vadd    $v14, $v14, $v14
    vadd    $v13, $v13, $v12
    vmudm   $v17, $v15, $v0[7]
    vmadh   $v15, $v15, $v0[6]
    vadd    $v14, $v14, $v14
    vsub    $v15, $v15, $v11
    vsub    $v14, $v14, $v3
    vsub    $v14, $v1, $v14
    vsub    $v17, $v13, $v10
    vadd    $v9, $v9, $v14
    vsub    $v11, $v11, $v2
    ssv     $v9[0], 0x40(t6)
    vsub    $v11, $v11, $v13
    ssv     $v17[0], -0x40(t0)
    vsub    $v12, $v8, $v12
    ssv     $v11[0], 0x40(t0)
    vsub    $v8, $v1, $v8
    ssv     $v15[0], -0x40(t1)
    vsub    $v10, $v1, $v10
    ssv     $v12[0], 0x40(t2)
    ssv     $v8[0], -0x40(t3)
    vsub    $v10, $v10, $v12
    ssv     $v14[0], 0x40(t5)
    ssv     $v10[0], -0x40(t2)
    lsv     $v0[0], 0x0(s7)
    lsv     $v31[0], 0x3e(s7)
    lsv     $v1[0], 0x2(s7)
    lsv     $v30[0], 0x3c(s7)
    lsv     $v2[0], 0x6(s7)
    lsv     $v28[0], 0x38(s7)
    lsv     $v3[0], 0x4(s7)
    lsv     $v29[0], 0x3a(s7)
    vsub    $v0, $v0, $v31
    lqv     $v31[0], (data_0_0030)(zero)
    vsub    $v1, $v1, $v30
    vsub    $v2, $v2, $v28
    lsv     $v4[0], 0xe(s7)
    vsub    $v3, $v3, $v29
    lsv     $v24[0], 0x30(s7)
    vmudm   $v0, $v0, $v31[0]
    lsv     $v5[0], 0xc(s7)
    vmudm   $v1, $v1, $v31[1]
    lsv     $v25[0], 0x32(s7)
    vmudm   $v2, $v2, $v31[3]
    lsv     $v6[0], 0x8(s7)
    vmudm   $v3, $v3, $v31[2]
    lsv     $v27[0], 0x36(s7)
    vadd    $v0, $v0, $v0
    lsv     $v7[0], 0xa(s7)
    vadd    $v1, $v1, $v1
    lsv     $v26[0], 0x34(s7)
    vadd    $v2, $v2, $v2
    lqv     $v30[0], (data_1_0040)(zero)
    vadd    $v3, $v3, $v3
    lsv     $v8[0], 0x1e(s7)
    vsub    $v4, $v4, $v24
    lsv     $v16[0], 0x20(s7)
    vsub    $v5, $v5, $v25
    lsv     $v9[0], 0x1c(s7)
    vsub    $v6, $v6, $v27
    lsv     $v17[0], 0x22(s7)
    vsub    $v7, $v7, $v26
    lsv     $v10[0], 0x18(s7)
    vmudm   $v4, $v4, $v31[7]
    lsv     $v19[0], 0x26(s7)
    vmudm   $v5, $v5, $v31[6]
    lsv     $v11[0], 0x1a(s7)
    vmudm   $v6, $v6, $v31[4]
    lsv     $v18[0], 0x24(s7)
    vmudm   $v7, $v7, $v31[5]
    vadd    $v4, $v4, $v4
    vadd    $v5, $v5, $v5
    vadd    $v6, $v6, $v6
    vadd    $v7, $v7, $v7
    lsv     $v12[0], 0x10(s7)
    vsub    $v8, $v8, $v16
    lsv     $v23[0], 0x2e(s7)
    vsub    $v9, $v9, $v17
    lsv     $v13[0], 0x12(s7)
    vsub    $v10, $v10, $v19
    lsv     $v22[0], 0x2c(s7)
    vsub    $v11, $v11, $v18
    lsv     $v14[0], 0x16(s7)
    vmudm   $v8, $v8, $v30[7]
    lsv     $v20[0], 0x28(s7)
    vmudm   $v9, $v9, $v30[6]
    lsv     $v15[0], 0x14(s7)
    vmudm   $v10, $v10, $v30[4]
    lsv     $v21[0], 0x2a(s7)
    vmudm   $v11, $v11, $v30[5]
    vsub    $v12, $v12, $v23
    vsub    $v13, $v13, $v22
    vsub    $v14, $v14, $v20
    vsub    $v15, $v15, $v21
    vmudm   $v12, $v12, $v30[0]
    vmudm   $v13, $v13, $v30[1]
    vmudm   $v14, $v14, $v30[3]
    vmudm   $v15, $v15, $v30[2]
    vadd    $v12, $v12, $v12
    vadd    $v13, $v13, $v13
    vadd    $v15, $v15, $v15
    jal     func_04001AB0
     nop
    vadd    $v2, $v18, $v19
    vsub    $v3, $v18, $v19
    lqv     $v19[0], (data_1_0050)(zero)
    vmudm   $v0, $v16, $v19[0]
    lqv     $v18[0], (data_1_0020)(zero)
    vmacf   $v1, $v17, $v19[1]
    vmudm   $v0, $v16, $v18[6]
    vmadm   $v0, $v17, $v18[6]
    vxor    $v16, $v16, $v16
    vsub    $v2, $v16, $v2
    vmudm   $v17, $v3, $v19[3]
    vmadh   $v3, $v3, $v19[2]
    vadd    $v4, $v20, $v21
    vadd    $v4, $v4, $v0
    vsub    $v5, $v20, $v21
    vmudm   $v17, $v5, $v19[3]
    vmadh   $v5, $v5, $v19[2]
    vadd    $v5, $v5, $v1
    vadd    $v6, $v22, $v23
    vadd    $v6, $v6, $v6
    vadd    $v6, $v6, $v0
    vsub    $v6, $v6, $v2
    vsub    $v7, $v22, $v23
    vmudm   $v17, $v7, $v19[5]
    vmadh   $v7, $v7, $v19[4]
    vadd    $v7, $v7, $v0
    vsub    $v0, $v16, $v0
    vadd    $v7, $v7, $v1
    ssv     $v0[0], -0x20(t3)
    vadd    $v7, $v7, $v3
    vsub    $v0, $v16, $v0
    vadd    $v8, $v24, $v25
    vsub    $v9, $v24, $v25
    vmudm   $v17, $v9, $v19[3]
    vmadh   $v9, $v9, $v19[2]
    vadd    $v10, $v26, $v27
    vadd    $v10, $v10, $v10
    vadd    $v10, $v10, $v8
    vsub    $v11, $v26, $v27
    vmudm   $v17, $v11, $v19[5]
    vmadh   $v11, $v11, $v19[4]
    vadd    $v11, $v11, $v8
    vadd    $v11, $v11, $v9
    vadd    $v12, $v28, $v29
    vadd    $v12, $v12, $v12
    vsub    $v12, $v4, $v12
    vsub    $v13, $v28, $v29
    vmudm   $v17, $v13, $v19[5]
    ssv     $v12[0], 0x20(t2)
    vmadh   $v13, $v13, $v19[4]
    vsub    $v13, $v13, $v12
    vsub    $v13, $v13, $v5
    vadd    $v14, $v30, $v31
    vadd    $v14, $v14, $v14
    vadd    $v14, $v14, $v14
    vsub    $v14, $v6, $v14
    vsub    $v15, $v30, $v31
    vmudm   $v17, $v15, $v19[7]
    ssv     $v14[0], 0x20(t5)
    vmadh   $v15, $v15, $v19[6]
    vsub    $v15, $v15, $v7
    vadd    $v14, $v14, $v1
    ssv     $v14[0], 0x20(t6)
    ssv     $v15[0], -0x20(t1)
    vadd    $v9, $v9, $v10
    vadd    $v1, $v1, $v6
    vsub    $v6, $v10, $v6
    vsub    $v1, $v9, $v1
    ssv     $v6[0], 0x60(t5)
    vadd    $v10, $v10, $v2
    vsub    $v10, $v4, $v10
    ssv     $v10[0], -0x60(t2)
    vsub    $v12, $v2, $v12
    ssv     $v12[0], -0x20(t2)
    vadd    $v5, $v4, $v5
    vsub    $v4, $v8, $v4
    ssv     $v4[0], 0x60(t2)
    vsub    $v0, $v0, $v8
    ssv     $v0[0], -0x60(t3)
    vsub    $v7, $v7, $v11
    ssv     $v7[0], -0x60(t1)
    vsub    $v11, $v11, $v3
    ssv     $v1[0], 0x60(t6)
    vsub    $v11, $v11, $v5
    ssv     $v11[0], 0x60(t0)
    vsub    $v3, $v3, $v13
    ssv     $v3[0], 0x20(t0)
    vadd    $v13, $v13, $v2
    ssv     $v13[0], -0x20(t0)
    vsub    $v2, $v5, $v2
    vsub    $v2, $v2, $v9
    ssv     $v2[0], -0x60(t0)
    andi    t1, t6, 0xffe0
    addi    t2, zero, DeWindowLUT
    sub     t2, t2, t4
    lqv     $v2[0], 0x0(t1)
    lqv     $v1[0], 0x0(t2)
    lrv     $v1[0], 0x10(t2)
    lqv     $v4[0], 0x10(t1)
    lqv     $v3[0], 0x10(t2)
    lrv     $v3[0], 0x20(t2)
    lqv     $v6[0], 0x20(t1)
    lqv     $v5[0], 0x40(t2)
    lrv     $v5[0], 0x50(t2)
    lqv     $v8[0], 0x30(t1)
    lqv     $v7[0], 0x50(t2)
    lrv     $v7[0], 0x60(t2)
    vmulf   $v2, $v2, $v1
    addi    t3, zero, data_1_0CE8
    vmulf   $v4, $v4, $v3
    ldv     $v20[0], 0x0(t3)
    vmulf   $v6, $v6, $v5
    addi    t3, zero, 8
    vmulf   $v8, $v8, $v7
.L04001800:
    addi    t2, t2, 0x80
    vadd    $v9, $v2, $v2[2h]
    addi    t1, t1, 0x40
    vadd    $v10, $v4, $v4[2h]
    lqv     $v1[0], 0x0(t2)
    vadd    $v11, $v6, $v6[2h]
    lrv     $v1[0], 0x10(t2)
    vadd    $v12, $v8, $v8[2h]
    lqv     $v3[0], 0x10(t2)
    vadd    $v13, $v2, $v2[3h]
    lrv     $v3[0], 0x20(t2)
    vadd    $v14, $v4, $v4[3h]
    lqv     $v5[0], 0x40(t2)
    vadd    $v15, $v6, $v6[3h]
    lrv     $v5[0], 0x50(t2)
    vadd    $v16, $v8, $v8[3h]
    lqv     $v7[0], 0x50(t2)
    vadd    $v0, $v9, $v13[1h]
    lrv     $v7[0], 0x60(t2)
    vadd    $v17, $v10, $v14[1h]
    lqv     $v2[0], 0x0(t1)
    vadd    $v18, $v11, $v15[1h]
    lqv     $v4[0], 0x10(t1)
    vadd    $v19, $v12, $v16[1h]
    lqv     $v6[0], 0x20(t1)
    vadd    $v0, $v0, $v17
    lqv     $v8[0], 0x30(t1)
    vadd    $v18, $v18, $v19
    vmulf   $v2, $v2, $v1
    vadd    $v0, $v0, $v0[4]
    vmulf   $v4, $v4, $v3
    vadd    $v18, $v18, $v18[4]
    vmulf   $v6, $v6, $v5
    ssv     $v0[0], 0x0(s3)
    vmulf   $v8, $v8, $v7
    addi    t3, t3, -1
    ssv     $v18[0], 0x2(s3)
    bgtz    t3, .L04001800
     addi    s3, s3, 4
    vadd    $v9, $v2, $v2[2h]
    andi    t0, t4, 2
    vadd    $v10, $v4, $v4[2h]
    vadd    $v13, $v2, $v2[3h]
    vadd    $v14, $v4, $v4[3h]
    vadd    $v0, $v9, $v10
    vadd    $v0, $v0, $v0[4]
    vadd    $v17, $v13, $v14
    addi    t1, t1, -0x40
    vadd    $v17, $v17, $v17[5]
    vmudm   $v2, $v0, $v20[1]
    vmadh   $v0, $v0, $v20[0]
    vmudm   $v4, $v17, $v20[1]
    addi    t3, zero, data_1_0CE8
    vmadh   $v17, $v17, $v20[0]
    bnez    t0, .L040018E8
     ssv     $v0[0], 0x0(s3)
    llv     $v20[4], 0x0(t3)
    ssv     $v17[2], 0x0(s3)
.L040018E8:
    addi    t2, zero, DeWindowLUT + 0x43e
    sub     t2, t2, t4
    lqv     $v2[0], 0x20(t1)
    lqv     $v1[0], 0x0(t2)
    lrv     $v1[0], 0x10(t2)
    lqv     $v4[0], 0x30(t1)
    lqv     $v3[0], 0x10(t2)
    lrv     $v3[0], 0x20(t2)
    lqv     $v6[0], 0x0(t1)
    lqv     $v5[0], 0x40(t2)
    lrv     $v5[0], 0x50(t2)
    lqv     $v8[0], 0x10(t1)
    lqv     $v7[0], 0x50(t2)
    lrv     $v7[0], 0x60(t2)
    vmulf   $v2, $v2, $v1
    addi    t3, zero, 8
    vmulf   $v4, $v4, $v3
    vmulf   $v6, $v6, $v5
    vmulf   $v8, $v8, $v7
.L04001934:
    addi    t2, t2, 0x80
    vadd    $v9, $v2, $v2[2h]
    addi    t1, t1, -0x40
    vadd    $v10, $v4, $v4[2h]
    lqv     $v1[0], 0x0(t2)
    vadd    $v11, $v6, $v6[2h]
    lrv     $v1[0], 0x10(t2)
    vadd    $v12, $v8, $v8[2h]
    lqv     $v3[0], 0x10(t2)
    vadd    $v13, $v2, $v2[3h]
    lrv     $v3[0], 0x20(t2)
    vadd    $v14, $v4, $v4[3h]
    lqv     $v5[0], 0x40(t2)
    vadd    $v15, $v6, $v6[3h]
    lrv     $v5[0], 0x50(t2)
    vadd    $v16, $v8, $v8[3h]
    lqv     $v7[0], 0x50(t2)
    vsub    $v0, $v9, $v13[1h]
    lrv     $v7[0], 0x60(t2)
    vsub    $v17, $v10, $v14[1h]
    lqv     $v2[0], 0x20(t1)
    vsub    $v18, $v11, $v15[1h]
    lqv     $v4[0], 0x30(t1)
    vsub    $v19, $v12, $v16[1h]
    lqv     $v6[0], 0x0(t1)
    vadd    $v0, $v0, $v17
    lqv     $v8[0], 0x10(t1)
    vadd    $v18, $v18, $v19
    vmulf   $v2, $v2, $v1
    vadd    $v0, $v0, $v0[4]
    vmulf   $v4, $v4, $v3
    vadd    $v18, $v18, $v18[4]
    addi    t3, t3, -1
    vmulf   $v6, $v6, $v5
    ssv     $v0[0], 0x2(s3)
    vmulf   $v8, $v8, $v7
    ssv     $v18[0], 0x4(s3)
    bgtz    t3, .L04001934
     addi    s3, s3, 4
    addi    t0, s3, 2
    lqv     $v0[0], -0x40(s3)
    lqv     $v17[0], -0x30(s3)
    lqv     $v2[0], -0x20(t0)
    lrv     $v2[0], -0x10(t0)
    lqv     $v4[0], -0x10(t0)
    vmudm   $v6, $v0, $v20[1]
    lrv     $v4[0], 0x0(t0)
    vmadh   $v0, $v0, $v20[0]
    vmudm   $v6, $v2, $v20[3]
    sqv     $v0[0], -0x40(s3)
    vmadh   $v2, $v2, $v20[2]
    vmudm   $v6, $v17, $v20[1]
    sqv     $v2[0], -0x20(t0)
    srv     $v2[0], -0x10(t0)
    vmadh   $v17, $v17, $v20[0]
    vmudm   $v6, $v4, $v20[3]
    sqv     $v17[0], -0x30(s3)
    vmadh   $v4, $v4, $v20[2]
    sqv     $v4[0], -0x10(t0)
    srv     $v4[0], 0x0(t0)
    add     t3, zero, t6
    add     t6, zero, t5
    add     t5, zero, t3
    addi    t4, t4, -2
    andi    t4, t4, 0x1e
    addi    s2, s2, -0x40
    bgtz    s2, mp3_decode_innerloop
     addi    s7, s7, 0x40
    addi    at, zero, data_1_0E70
    add     v0, zero, s6                  // write out decoded
    jal     dma_write
     addi    v1, v1, -1
    addi    v1, v1, 1
    addi    s6, s6, 0x180
    addi    s5, s5, 0x180
    jal     dma_wait
     add     v0, zero, s5
    bgtz    s4, mp3_decode_loop            // loop until done decoding all
     addi    at, zero, data_1_0CF0
    add     v0, s1, zero
    addi    at, zero, nextTaskEntry
    jal     dma_read                        // read back the saved dmem
     addi    v1, zero, nextTaskEntry_len-1
    addi    at, zero, data_1_08A0
    jal     dma_write                       // write back the mp3 data that was pasted over by dmem contents
     addi    v1, zero, 0x440-1
    lw      t3, (data_1_0CE8)(zero)
    jal     dma_wait                        // wait for dmas to complete
     nop
    sw      s1, (audioStruct + 0x4)(zero)
    sw      s0, (audioStruct + 0x8)(zero)   // ucode_data dram addr
    sw      t7, (audioStruct + 0xc)(zero)
    sw      t3, (audioStruct + 0x0)(zero)
    j       reload_overlay_0
     nop

func_04001AB0:
    vadd    $v16, $v0, $v8
    vadd    $v17, $v1, $v9
    vadd    $v18, $v2, $v10
    vadd    $v19, $v3, $v11
    vadd    $v20, $v4, $v12
    vadd    $v21, $v5, $v13
    vadd    $v22, $v6, $v14
    vadd    $v23, $v7, $v15
    vsub    $v24, $v0, $v8
    lqv     $v8[0], (data_1_0010)(zero)
    vsub    $v25, $v1, $v9
    lqv     $v9[0], (data_1_0020)(zero)
    vsub    $v26, $v2, $v10
    vsub    $v27, $v3, $v11
    vmudm   $v24, $v24, $v8[0]
    vmudm   $v25, $v25, $v8[2]
    vsub    $v28, $v4, $v12
    vsub    $v29, $v5, $v13
    vmudm   $v26, $v26, $v8[6]
    vmudm   $v27, $v27, $v8[4]
    vsub    $v30, $v6, $v14
    vsub    $v31, $v7, $v15
    vmudm   $v28, $v28, $v9[5]
    vmudm   $v29, $v29, $v9[3]
    vmudm   $v30, $v30, $v8[7]
    vmudm   $v31, $v31, $v9[1]
    vsub    $v4, $v16, $v20
    vsub    $v5, $v17, $v21
    vadd    $v0, $v16, $v20
    vadd    $v1, $v17, $v21
    vmudm   $v4, $v4, $v8[1]
    vmudm   $v5, $v5, $v8[5]
    vsub    $v6, $v18, $v22
    vsub    $v7, $v19, $v23
    vadd    $v2, $v18, $v22
    vadd    $v3, $v19, $v23
    vmudm   $v6, $v6, $v9[4]
    vmudm   $v7, $v7, $v9[0]
    vsub    $v12, $v24, $v28
    vsub    $v13, $v25, $v29
    vadd    $v10, $v26, $v30
    vadd    $v11, $v27, $v31
    vsub    $v14, $v26, $v30
    vsub    $v15, $v27, $v31
    vmudm   $v12, $v12, $v8[1]
    vmudm   $v13, $v13, $v8[5]
    vmudm   $v14, $v14, $v9[4]
    vmudm   $v15, $v15, $v9[0]
    vadd    $v8, $v24, $v28
    vadd    $v9, $v25, $v29
    vadd    $v16, $v0, $v2
    vadd    $v17, $v1, $v3
    vsub    $v18, $v0, $v2
    lqv     $v0[0], (data_1_0010)(zero)
    vsub    $v19, $v1, $v3
    lqv     $v2[0], (data_1_0020)(zero)
    vadd    $v20, $v4, $v6
    vadd    $v21, $v5, $v7
    vsub    $v22, $v4, $v6
    vsub    $v23, $v5, $v7
    vmudm   $v18, $v18, $v0[3]
    vmudm   $v19, $v19, $v2[2]
    vmudm   $v22, $v22, $v0[3]
    vmudm   $v23, $v23, $v2[2]
    vsub    $v26, $v8, $v10
    vsub    $v27, $v9, $v11
    vadd    $v24, $v8, $v10
    vadd    $v25, $v9, $v11
    vmudm   $v26, $v26, $v0[3]
    vmudm   $v27, $v27, $v2[2]
    vsub    $v30, $v12, $v14
    vsub    $v31, $v13, $v15
    vadd    $v28, $v12, $v14
    vadd    $v29, $v13, $v15
    vmudm   $v30, $v30, $v0[3]
    vmudm   $v31, $v31, $v2[2]
    jr      $ra
     nop

// Four trailing no-ops are part of Conker's 0x9C0-byte MP3 overlay.
// They are covered by its DMA descriptor, after the final jr ra delay slot.
    nop
    nop
    nop
    nop
.align 8
Overlay1End:

.if Overlay1End > 0x04002000
    .error "Not enough room in IMEM for Overlay 1"
.endif

.close
