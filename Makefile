PROFILE ?= us
SYMBOL ?=
PROFILE_CONFIG := config/profiles/$(PROFILE).yaml
MATERIALIZED_CONFIG := build/config/$(PROFILE).yaml
BUILD_DIR := build/$(PROFILE)
AS := mips-linux-gnu-as
AR := mips-linux-gnu-ar
CC := /opt/ido/cc
LD := mips-linux-gnu-ld
OBJCOPY := mips-linux-gnu-objcopy
# spimdisasm preserves valid target encodings that GNU as describes as odd-FPR
# double operations. The bootstrap assembler must retain those bytes verbatim.
ASFLAGS := -W -EB -march=vr4300 -mabi=32 -I include
CFLAGS := -c -32 -G 0 -Xfullwarn -Xcpluscomm -signed -nostdinc -non_shared -Wab,-r4300_mul \
	-D_LANGUAGE_C -D_FINALROM -D_MIPS_SZLONG=32 -I include -O2 -g3 -mips2
PROFILE_CFLAGS_us := -DPROFILE_US=1
PROFILE_CFLAGS_eu := -DPROFILE_EU=1
PROFILE_CFLAGS := $(PROFILE_CFLAGS_$(PROFILE))
LDFLAGS := -m elf32btsmip -T $(BUILD_DIR)/conker.$(PROFILE).ld
ROM_NAME := conker.$(PROFILE).z64
ROM_PATH := roms/baserom.$(PROFILE).z64
ASM_SRCS := $(shell find asm/$(PROFILE) -type f -name '*.s' ! -path '*/nonmatchings/*' 2>/dev/null)
ASM_OBJS := $(patsubst asm/%.s,$(BUILD_DIR)/asm/%.o,$(ASM_SRCS))
C_SRCS := $(shell python3 scripts/list_integrated_sources.py --overlay main --profile $(PROFILE) 2>/dev/null)
C_OBJS := $(patsubst src/%.c,$(BUILD_DIR)/src/%.o,$(C_SRCS))
NORMALIZED_ASM_DIR := $(BUILD_DIR)/normalized-asm
BOOTSTRAP_SYMBOLS := $(BUILD_DIR)/bootstrap-symbols.ld
ASSET_BINS_us := assets/boot.bin assets/2D4B0.bin
ASSET_BINS_eu := assets/boot.bin assets/2D810.bin
ASSET_BINS := $(ASSET_BINS_$(PROFILE))
ASSET_OBJS := $(patsubst assets/%.bin,$(BUILD_DIR)/assets/%.o,$(ASSET_BINS))
GAME_PROFILE := us
GAME_REFERENCE_PROFILE ?= us
GAME_REFERENCE_BUILD_DIR := build/game-reference/$(GAME_REFERENCE_PROFILE)
GAME_REFERENCE_CODE := $(GAME_REFERENCE_BUILD_DIR)/game.code.bin
GAME_INTEGRATED_BUILD_DIR := build/game-integrated/$(GAME_PROFILE)
GAME_INTEGRATED_CODE := $(GAME_INTEGRATED_BUILD_DIR)/game.code.bin
GAME_INTEGRATED_PREPARED := $(GAME_INTEGRATED_BUILD_DIR)/.prepared
GAME_INTEGRATED_LD_SCRIPT := $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.ld
GAME_INTEGRATED_PREPARE_INPUTS := Makefile Dockerfile config/game/us.yaml config/symbols/game-us.txt config/overlays.json \
	scripts/compile_c.py scripts/create_bootstrap_symbols.py scripts/extract_game_code.py \
	scripts/normalize_asm.py scripts/prepare_game_integration.py toolchain/tools.lock.json
GAME_INTEGRATED_ASM_SRCS := $(shell find asm/game_integrated/$(GAME_PROFILE) -type f -name '*.s' ! -path '*/nonmatchings/*' 2>/dev/null)
GAME_INTEGRATED_ASM_OBJS := $(patsubst asm/%.s,$(GAME_INTEGRATED_BUILD_DIR)/asm/%.o,$(GAME_INTEGRATED_ASM_SRCS))
GAME_INTEGRATED_C_SRCS := $(shell python3 scripts/list_integrated_sources.py --overlay game --profile $(GAME_PROFILE) 2>/dev/null)
GAME_INTEGRATED_C_OBJS := $(patsubst src/%.c,$(GAME_INTEGRATED_BUILD_DIR)/src/%.o,$(GAME_INTEGRATED_C_SRCS))
GAME_INTEGRATED_NORMALIZED_ASM_DIR := $(GAME_INTEGRATED_BUILD_DIR)/normalized-asm
GAME_INTEGRATED_BOOTSTRAP_SYMBOLS := $(GAME_INTEGRATED_BUILD_DIR)/bootstrap-symbols.ld
GAME_LIB_DIR := build/game-libs/us
GAME_LIB := $(GAME_LIB_DIR)/libultra_2_0I.a
GAME_RARE_LIB := $(GAME_LIB_DIR)/libultrare.a
GAME_LIB_SYMBOLS := config/game/us-sdk.ld
GAME_LIB_OBJECTS := $(addprefix lib/ultralib/build/I/libultra_rom/src/,\
	gu/random.o gu/ortho.o gu/normalize.o gu/mtxcatl.o gu/mtxcatf.o gu/sqrtf.o \
	io/visetspecial.o io/piread.o io/sirawdma.o io/crc.o \
	os/settimer.o os/gettime.o libc/sprintf.o io/contpfs.o io/pfschecker.o)
GAME_RARE_OBJECTS := $(addprefix lib/libultrare/build/libultrare/io/,\
	pfsisplug.o contramread.o contramwrite.o controller.o pfsinit.o contreaddata.o \
	conteepread.o conteeplongread.o conteepprobe.o) \
	lib/libultrare/build/libultrare/gu/mtxutil.o \
	lib/libultrare/build/libultrare/gu/rotate.o \
	lib/libultrare/build/libultrare/gu/cosf.o \
	lib/libultrare/build/libultrare/gu/sinf.o \
	lib/libultrare/build/libultrare/gu/perspective.o \
	lib/libultrare/build/libultrare/gu/expf.o \
	lib/libultrare/build/libultrare/gu/logf.o \
	lib/libultrare/build/libultrare/io/siacs_game.o \
	lib/libultrare/build/libultrare/mp3/playback.o \
	lib/libultrare/build/libultrare/mp3/main.o \
	lib/libultrare/build/libultrare/mp3/util.o \
	lib/libultrare/build/libultrare/mp3/decoder.o \
	lib/libultrare/build/libultrare/mp3/lib_46650.o \
	lib/libultrare/build/libultrare/mp3/lib_47550.o
ULTRALIB_DIR := lib/ultralib
ULTRALIB_VERSION ?= L
ULTRALIB_TARGET ?= libultra_rom
ULTRALIB_BUILD_DIR := $(ULTRALIB_DIR)/build/$(ULTRALIB_VERSION)/$(ULTRALIB_TARGET)
ULTRALIB_MODERN_LD_STAMP := $(ULTRALIB_BUILD_DIR)/.conker-modern-ld
PROFILE_LIB_DIR_us := build/us/lib
PROFILE_LIB_L_us := $(PROFILE_LIB_DIR_us)/libultra_2_0L.a
PROFILE_LIB_LD_us := $(PROFILE_LIB_DIR_us)/libultra_2_0L_d.a
PROFILE_LIB_I_us := $(PROFILE_LIB_DIR_us)/libultra_2_0I.a
PROFILE_LIB_RARE_us := $(PROFILE_LIB_DIR_us)/libultrare.a
PROFILE_LIB_RSP_us := $(PROFILE_LIB_DIR_us)/librsp.a
PROFILE_LIB_DEPS_us := $(PROFILE_LIB_RSP_us) $(PROFILE_LIB_L_us) $(PROFILE_LIB_LD_us) $(PROFILE_LIB_I_us) $(PROFILE_LIB_RARE_us)
PROFILE_LIB_DEPS_eu :=
PROFILE_LIB_DEPS := $(PROFILE_LIB_DEPS_$(PROFILE))
# Linked SDK objects retain their original symbol names. Bind references to
# raw-only code and data at the independently verified US ROM addresses.
# Overlay JAL aliases use the main link PC region (0x8); runtime execution in
# the 0x1 mapping selects the corresponding 0x15 overlay addresses.
PROFILE_LIB_LDFLAGS_us := \
	--defsym=__osEnqueueAndYield=0x800078B4 \
	--defsym=__osEnqueueThread=0x800079D8 \
	--defsym=__osPopThread=0x80007A24 \
	--defsym=__osDispatchThread=0x80007A38 \
	--defsym=__osExceptionPreamble=0x100071D0 \
	--defsym=osMapTLBRdb=0x80008120 \
	--defsym=osTvType=0x80000300 \
	--defsym=osRomBase=0x80000308 \
	--defsym=osResetType=0x8000030C \
	--defsym=osAppNMIBuffer=0x8000031C \
	--defsym=__osPiDevMgr=0x8002AB50 \
	--defsym=__osPiTable=0x8002AB6C \
	--defsym=__osHwIntTable=0x8002AC70 \
	--defsym=__osLeoInterruptPhysical=0x10026B10 \
	--defsym=__conker_print_state=0x80035500 \
	--defsym=__conker_runtime_proutSyncPrintf=0x10002070 \
	--defsym=func_800020D0=_Printf \
	--defsym=func_80002718=_Putfld \
	--defsym=func_80022EC0=memcpy \
	--defsym=func_80023060=ldiv \
	--defsym=func_80022F14=strchr \
	--defsym=func_80022EEC=strlen \
	--defsym=func_800230F0=_Litob \
	--defsym=__conker_audio_fault=0x8003C8E0 \
	--defsym=__conker_audio_1263C=0x8001263C \
	--defsym=n_alSynAddSeqPlayer=__conker_audio_add_player_2 \
	--defsym=__conker_runtime_CSPVoiceHandler=__n_CSPVoiceHandler-0x70000000 \
	--defsym=__conker_runtime_cspVolume=__n_cspVolume-0x70000000 \
	--defsym=__conker_runtime_cspPan=__n_cspPan-0x70000000 \
	--defsym=__conker_runtime_cspPriority=__n_cspPriority-0x70000000 \
	--defsym=__conker_runtime_cspNotify=__n_cspNotify-0x70000000 \
	--defsym=__conker_runtime_cspInstrumentMajor=__n_cspInstrumentMajor-0x70000000 \
	--defsym=__conker_runtime_cspFilterEnable=__n_cspFilterEnable-0x70000000 \
	--defsym=__conker_runtime_cspFilterPitch=__n_cspFilterPitch-0x70000000 \
	--defsym=__conker_runtime_cspFilter11=__n_cspFilter11-0x70000000 \
	--defsym=__conker_runtime_cspSustain=__n_cspSustain-0x70000000 \
	--defsym=__conker_runtime_cspSurround=__n_cspSurround-0x70000000 \
	--defsym=__conker_runtime_cspFXMix=__n_cspFXMix-0x70000000 \
	--defsym=__conker_runtime_cspFXBus=__n_cspFXBus-0x70000000 \
	--defsym=__conker_runtime_cspMP3Major=__n_cspMP3Major-0x70000000 \
	--defsym=__conker_runtime_cspMP3Trigger=__n_cspMP3Trigger-0x70000000 \
	--defsym=__conker_runtime_cspFadeStart=__n_cspFadeStart-0x70000000 \
	--defsym=__conker_runtime_cspFadeUpdate=__n_cspFadeUpdate-0x70000000 \
	--defsym=__conker_runtime_cspFadeRate=__n_cspFadeRate-0x70000000 \
	--defsym=__conker_runtime_cspFadeVolume=__n_cspFadeVolume-0x70000000 \
	--defsym=__conker_osc_sinf=0x85047D60 \
	--defsym=__conker_runtime_osc_init=0x10012E04 \
	--defsym=__conker_runtime_osc_update=0x10012F94 \
	--defsym=__conker_runtime_osc_stop=0x100131D8 \
	--defsym=__conker_runtime_sndpVoiceHandler=_n_sndpVoiceHandler-0x70000000 \
	--defsym=__conker_sound_player_storage=0x80042850 \
	--defsym=g_SndpVolumeTable=0x800428B8 \
	--defsym=__conker_audio_fault_handler=0x80007DA0 \
	--defsym=__conker_game_atan2f=0x850484A0 \
	--defsym=__conker_default_fx_params=0x8002BBE0 \
	--defsym=__conker_mp3_enabled=0x800E0E04 \
	--defsym=__conker_mp3_make_samples=0x851F2E88 \
	--defsym=__conker_audio_fx_pull=0x1001E530 \
	--defsym=__conker_audio_surround=0x800428C0 \
	--defsym=__conker_audio_mono=0x800428C1 \
	--defsym=__conker_audio_headphone=0x800428C2 \
	-u _bzero \
	-u osInvalICache \
	-u osInvalDCache \
	-u _Litob \
	-u __osPiCreateAccessQueue \
	-u _bcopy \
	-u osWritebackDCache \
	-u osSetIntMask \
	-u osWritebackDCacheAll \
	-u __osSiCreateAccessQueue \
	-u osMapTLB \
	-u __sinf \
	-u __ll_div \
	-u __osProbeTLB \
	-u osViModeMpalLan1 \
	-u osViModeNtscLan1 \
	-u __libm_qnan_f \
	-u __osSetSR \
	-u __osGetSR \
	-u __osSetFpcCsr \
	-u osStartThread \
	-u osSetThreadPri \
	-u osStopThread \
	-u osVirtualToPhysical \
	-u osRecvMesg \
	-u osSendMesg \
	-u osCreateMesgQueue \
	-u osGetThreadPri \
	-u __osSpSetStatus \
	-u osGetCount \
	-u __osDequeueThread \
	-u __osSpGetStatus \
	-u osAiGetStatus \
	-u osSpTaskYield \
	-u osGetTime \
	-u osPiGetStatus \
	-u osUnmapTLB \
	-u sqrtf \
	-u __osSetCompare \
	-u osJamMesg
PROFILE_LIB_LDFLAGS_eu :=
PROFILE_LIB_INPUTS_us := --whole-archive $(PROFILE_LIB_RSP_us) $(PROFILE_LIB_L_us) $(PROFILE_LIB_LD_us) $(PROFILE_LIB_I_us) $(PROFILE_LIB_RARE_us) --no-whole-archive
PROFILE_LIB_INPUTS_eu :=
PROFILE_LIB_INPUTS := $(PROFILE_LIB_INPUTS_$(PROFILE))
LDFLAGS += $(PROFILE_LIB_LDFLAGS_$(PROFILE))

.PHONY: help prepare prepare-reference build raw-build diff clean game-asm game-asm-prepare game-integrated game-integrated-refresh game-integrated-prepare game-integrated-raw libultra libultrare profile-libs game-libs

help:
	@printf '%s\n' 'Use ./conker help for the supported contributor commands.'

prepare:
	@test "$(PROFILE)" = us -o "$(PROFILE)" = eu
	@test -f "$(PROFILE_CONFIG)"
	rm -rf "asm/$(PROFILE)"
	python3 scripts/prepare_profile.py "$(PROFILE)"
	splat split "$(MATERIALIZED_CONFIG)"

prepare-reference:
	@test "$(PROFILE)" = us -o "$(PROFILE)" = eu
	rm -rf "reference/$(PROFILE)"
	python3 scripts/prepare_profile.py "$(PROFILE)" --reference
	splat split "build/config/reference/$(PROFILE).yaml"

build: prepare
	$(MAKE) --no-print-directory raw-build PROFILE=$(PROFILE)

raw-build: $(BUILD_DIR)/$(ROM_NAME)
	@cmp -s "$(BUILD_DIR)/$(ROM_NAME)" "$(ROM_PATH)" || { \
		printf '%s\n' "build mismatch: $(BUILD_DIR)/$(ROM_NAME)" >&2; exit 1; \
	}
	@printf '%s\n' "$(BUILD_DIR)/$(ROM_NAME): OK"

$(BUILD_DIR)/$(ROM_NAME): $(BUILD_DIR)/conker.$(PROFILE).elf
	$(OBJCOPY) -O binary $< $@

$(BOOTSTRAP_SYMBOLS): $(ASM_SRCS) $(C_SRCS) scripts/create_bootstrap_symbols.py
	python3 scripts/create_bootstrap_symbols.py --output $@ asm/$(PROFILE) src/game/done

$(BUILD_DIR)/conker.$(PROFILE).elf: $(BUILD_DIR)/conker.$(PROFILE).ld $(BOOTSTRAP_SYMBOLS) $(ASM_OBJS) $(C_OBJS) $(ASSET_OBJS) $(PROFILE_LIB_DEPS)
	$(LD) $(LDFLAGS) -T $(BOOTSTRAP_SYMBOLS) -o $@ $(ASM_OBJS) $(C_OBJS) $(ASSET_OBJS) $(PROFILE_LIB_INPUTS)

$(NORMALIZED_ASM_DIR)/%.s: asm/%.s scripts/normalize_asm.py
	python3 scripts/normalize_asm.py $< $@

$(BUILD_DIR)/asm/%.o: $(NORMALIZED_ASM_DIR)/%.s
	@mkdir -p "$(@D)"
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/asm/$(PROFILE)/header.o: src/header.c
	@mkdir -p "$(@D)"
	python3 scripts/compile_c.py --profile $(PROFILE) --output $@ $<

$(BUILD_DIR)/src/%.o: src/%.c
	@mkdir -p "$(@D)"
	python3 scripts/compile_c.py --profile $(PROFILE) --output $@ $<

$(BUILD_DIR)/assets/%.o: assets/%.bin
	@mkdir -p "$(@D)"
	$(LD) -r -b binary -m elf32btsmip -o $@ $<

clean:
	rm -rf build asm assets reference .splache undefined_funcs_auto.txt undefined_syms_auto.txt

diff:
	@test -n "$(SYMBOL)"
	python3 scripts/diff.py "$(PROFILE)" "$(SYMBOL)"

libultra:
	@test -f "$(ULTRALIB_DIR)/Makefile" || { printf '%s\n' 'lib/ultralib is missing; run git submodule update --init --recursive' >&2; exit 1; }
	@if test -d "$(ULTRALIB_BUILD_DIR)" && test ! -f "$(ULTRALIB_MODERN_LD_STAMP)"; then \
		$(MAKE) --no-print-directory -C "$(ULTRALIB_DIR)" VERSION=$(ULTRALIB_VERSION) TARGET=$(ULTRALIB_TARGET) clean; \
	fi
	# The container supplies IDO and binutils; upstream setup downloads unused tools.
	$(MAKE) --no-print-directory -C "$(ULTRALIB_DIR)" COMPILER_DIR=/opt/ido VERSION=$(ULTRALIB_VERSION) TARGET=$(ULTRALIB_TARGET) COMPARE=0 MODERN_LD=1
	@test -f "$(ULTRALIB_MODERN_LD_STAMP)" || touch "$(ULTRALIB_MODERN_LD_STAMP)"

libultrare:
	$(MAKE) --no-print-directory -C lib/libultrare verify

profile-libs:
	@test "$(PROFILE)" = us
	$(MAKE) --no-print-directory libultra ULTRALIB_VERSION=L
	$(MAKE) --no-print-directory libultra ULTRALIB_VERSION=L ULTRALIB_TARGET=libultra_d
	$(MAKE) --no-print-directory libultra ULTRALIB_VERSION=I
	$(MAKE) --no-print-directory libultrare
	@mkdir -p "$(PROFILE_LIB_DIR_us)"
	rm -f "$(PROFILE_LIB_L_us)"
	$(AR) crs "$(PROFILE_LIB_L_us)" \
		$(addprefix $(ULTRALIB_DIR)/build/L/libultra_rom/src/io/,$(addsuffix .o,aigetstat piacs pigetstat siacs spgetstat spsetstat sptaskyield)) \
		$(addprefix $(ULTRALIB_DIR)/build/L/libultra_rom/src/libc/,$(addsuffix .o,bcopy bzero ll xlitob)) \
		$(addprefix $(ULTRALIB_DIR)/build/L/libultra_rom/src/gu/,$(addsuffix .o,libm_vals sinf sqrtf)) \
		$(addprefix $(ULTRALIB_DIR)/build/L/libultra_rom/src/os/,$(addsuffix .o,createmesgqueue getcount getsr getthreadpri gettime invaldcache invalicache jammesg maptlb probetlb recvmesg sendmesg setcompare setfpccsr setintmask setsr setthreadpri startthread stopthread thread unmaptlb virtualtophysical writebackdcache writebackdcacheall)) \
		$(addprefix $(ULTRALIB_DIR)/build/L/libultra_rom/src/vimodes/,$(addsuffix .o,vimodempallan1 vimodentsclan1))
	rm -f "$(PROFILE_LIB_LD_us)"
	$(AR) crs "$(PROFILE_LIB_LD_us)" \
		$(addprefix $(ULTRALIB_DIR)/build/L/libultra_d/src/audio/,$(addsuffix .o,cents2ratio cspgetstate cspgettempo))
	rm -f "$(PROFILE_LIB_I_us)"
	$(AR) crs "$(PROFILE_LIB_I_us)" \
		$(addprefix $(ULTRALIB_DIR)/build/I/libultra_rom/src/io/,$(addsuffix .o,ai aisetfreq contpfs crc pfschecker pidma pigetcmdq pirawdma pirawread si sirawdma sirawread sirawwrite sp sprawdma spsetpc sptaskyielded viblack vigetcurrcontext vigetcurrframebuf vigetnextframebuf visetevent visetmode viswapbuf viswapcontext)) \
		$(addprefix $(ULTRALIB_DIR)/build/I/libultra_rom/src/libc/,$(addsuffix .o,ldiv string)) \
		$(addprefix $(ULTRALIB_DIR)/build/I/libultra_rom/src/os/,$(addsuffix .o,interrupt seteventmesg sethwinterrupt settimer timerintr))
	@mkdir -p "$(PROFILE_LIB_DIR_us)/libultrare-members"
	$(OBJCOPY) --redefine-sym __osLeoInterrupt=__osLeoInterruptPhysical \
		lib/libultrare/build/libultrare/os/initialize.o \
		"$(PROFILE_LIB_DIR_us)/libultrare-members/initialize.o"
	python3 scripts/prepare_main_library_object.py \
		lib/libultrare/build/libultrare/audio/n_reverb.o \
		"$(PROFILE_LIB_DIR_us)/libultrare-members/n_reverb.o" \
		--delta=-0x70000000 --expected-relocations 8
	python3 scripts/prepare_main_library_object.py \
		lib/libultrare/build/libultrare/audio/n_env.o \
		"$(PROFILE_LIB_DIR_us)/libultrare-members/n_env.o" \
		--delta=-0x70000000 --expected-relocations 17
	python3 scripts/prepare_main_library_object.py \
		lib/libultrare/build/libultrare/audio/n_csplayer.o \
		"$(PROFILE_LIB_DIR_us)/libultrare-members/n_csplayer.o" \
		--delta=-0x70000000 --expected-relocations 145
	python3 scripts/prepare_main_library_object.py \
		lib/libultrare/build/libultrare/audio/n_sndplayer.o \
		"$(PROFILE_LIB_DIR_us)/libultrare-members/n_sndplayer.o" \
		--delta=-0x70000000 --expected-relocations 16
	python3 scripts/prepare_main_library_object.py \
		lib/libultrare/build/libultrare/libc/xprintf.o \
		"$(PROFILE_LIB_DIR_us)/libultrare-members/xprintf.o" \
		--delta=-0x70000000 --expected-relocations 52
	rm -f "$(PROFILE_LIB_RARE_us)"
	$(AR) crs "$(PROFILE_LIB_RARE_us)" \
		lib/libultrare/build/libultrare/libc/syncprintf.o \
		"$(PROFILE_LIB_DIR_us)/libultrare-members/xprintf.o" \
		lib/libultrare/build/libultrare/audio/n_synthesizer.o \
		lib/libultrare/build/libultrare/audio/n_drvrNew.o \
		lib/libultrare/build/libultrare/audio/n_mainbus.o \
		lib/libultrare/build/libultrare/audio/n_load.o \
		lib/libultrare/build/libultrare/audio/alsurround.o \
		lib/libultrare/build/libultrare/audio/n_csq.o \
		lib/libultrare/build/libultrare/audio/n_seqplayer.o \
		lib/libultrare/build/libultrare/audio/n_cspctrl.o \
		lib/libultrare/build/libultrare/audio/n_cspsetbank.o \
		lib/libultrare/build/libultrare/audio/heap.o \
		lib/libultrare/build/libultrare/audio/bnkf.o \
		lib/libultrare/build/libultrare/audio/osc.o \
		"$(PROFILE_LIB_DIR_us)/libultrare-members/n_reverb.o" \
		"$(PROFILE_LIB_DIR_us)/libultrare-members/n_env.o" \
		"$(PROFILE_LIB_DIR_us)/libultrare-members/n_csplayer.o" \
		"$(PROFILE_LIB_DIR_us)/libultrare-members/n_sndplayer.o" \
		lib/libultrare/build/libultrare/audio/n_cspchan.o \
		lib/libultrare/build/libultrare/audio/n_cspsetfxmix.o \
		lib/libultrare/build/libultrare/audio/n_cspsetfxparam.o \
		lib/libultrare/build/libultrare/audio/n_cspevent12.o \
		lib/libultrare/build/libultrare/audio/n_auxbus.o \
		lib/libultrare/build/libultrare/audio/n_resample.o \
		lib/libultrare/build/libultrare/audio/n_resample2.o \
		lib/libultrare/build/libultrare/libc/xldtob.o \
		$(addprefix lib/libultrare/build/libultra/os/,$(addsuffix .o,exceptasm_data syncputchars_data)) \
		$(addprefix lib/libultrare/build/libultrare/io/,$(addsuffix .o,contramread contramwrite contreaddata controller epirawdma leodiskinit leointerrupt pfsinit pfsisplug vi vimodepallan1)) \
		$(addprefix lib/libultrare/build/libultrare/audio/,$(addsuffix .o,n_synaddplayer n_synsetpriority n_cspplay n_cspstop n_synstopvoice n_synfreevoice n_synsetvol n_synsetpitch n_cspsetpan n_cspsetseq n_cspsetvol n_syndelete n_sl n_cspsendmidi n_synallocfx n_synfx n_synfilter11 n_synfilter12 n_synfilter13 n_synsetpan n_synstartvoiceparam n_event n_synallocvoice n_cseqnextdelta)) \
		lib/libultrare/build/libultrare/os/destroythread.o \
		"$(PROFILE_LIB_DIR_us)/libultrare-members/initialize.o"

game-libs:
	$(MAKE) --no-print-directory libultra ULTRALIB_VERSION=I ULTRALIB_TARGET=libultra_rom
	$(MAKE) --no-print-directory libultrare
	$(MAKE) --no-print-directory "$(GAME_LIB)" "$(GAME_RARE_LIB)"

$(GAME_LIB): $(GAME_LIB_OBJECTS) Makefile
	@mkdir -p "$(@D)"
	rm -f "$@"
	$(AR) crs "$@" $(GAME_LIB_OBJECTS)

$(GAME_RARE_LIB): $(GAME_RARE_OBJECTS) Makefile
	@mkdir -p "$(@D)"
	rm -f "$@"
	$(AR) crs "$@" $(GAME_RARE_OBJECTS)

game-asm: game-asm-prepare
	@printf '%s\n' "$(GAME_REFERENCE_PROFILE) game reference assembly: reference/game/$(GAME_REFERENCE_PROFILE)/asm"

game-asm-prepare:
	rm -rf "reference/game/$(GAME_REFERENCE_PROFILE)" "$(GAME_REFERENCE_BUILD_DIR)"
	python3 scripts/extract_game_code.py "$(GAME_REFERENCE_PROFILE)" --output "$(GAME_REFERENCE_CODE)"
	python3 scripts/prepare_game_reference.py "$(GAME_REFERENCE_PROFILE)"
	@splat split "build/config/game-reference.$(GAME_REFERENCE_PROFILE).yaml" > "$(GAME_REFERENCE_BUILD_DIR)/splat.log" 2>&1 || { cat "$(GAME_REFERENCE_BUILD_DIR)/splat.log"; exit 1; }
	@printf '%s\n' "Game reference split generated; details: $(GAME_REFERENCE_BUILD_DIR)/splat.log"

game-integrated: game-integrated-prepare
	$(MAKE) --no-print-directory game-integrated-raw

game-integrated-refresh:
	rm -f "$(GAME_INTEGRATED_PREPARED)"
	$(MAKE) --no-print-directory game-integrated GAME_PROFILE="$(GAME_PROFILE)" PRUNE_NONMATCHING=1

game-integrated-prepare: $(GAME_INTEGRATED_PREPARED)
	@if ! test -d "reference/game/$(GAME_PROFILE)/asm" || ! test -f "$(GAME_INTEGRATED_CODE)" || ! test -f "$(GAME_INTEGRATED_LD_SCRIPT)"; then \
		rm -f "$(GAME_INTEGRATED_PREPARED)"; \
		$(MAKE) --no-print-directory "$(GAME_INTEGRATED_PREPARED)" GAME_PROFILE="$(GAME_PROFILE)"; \
	fi
	python3 scripts/prepare_nonmatching_asm.py --profile "$(GAME_PROFILE)" $(if $(filter 1,$(PRUNE_NONMATCHING)),--prune-stale,)

$(GAME_INTEGRATED_PREPARED): $(GAME_INTEGRATED_PREPARE_INPUTS)
	rm -rf "asm/game_integrated/$(GAME_PROFILE)" "$(GAME_INTEGRATED_BUILD_DIR)"
	@if ! test -d "reference/game/$(GAME_PROFILE)/asm"; then $(MAKE) --no-print-directory game-asm-prepare GAME_REFERENCE_PROFILE=$(GAME_PROFILE); fi
	python3 scripts/extract_game_code.py "$(GAME_PROFILE)" --output "$(GAME_INTEGRATED_CODE)"
	python3 scripts/prepare_game_integration.py
	@splat split "build/config/game-integrated.us.yaml" > "$(GAME_INTEGRATED_BUILD_DIR)/splat.log" 2>&1 || { cat "$(GAME_INTEGRATED_BUILD_DIR)/splat.log"; exit 1; }
	@printf '%s\n' "Integrated game split generated; details: $(GAME_INTEGRATED_BUILD_DIR)/splat.log"
	@touch "$(GAME_INTEGRATED_PREPARED)"

game-integrated-raw: $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.bin
	@cmp -s "$(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.bin" "$(GAME_INTEGRATED_CODE)" || { \
		printf '%s\n' "integrated game mismatch: $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.bin" >&2; exit 1; \
	}
	@printf '%s\n' "$(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.bin: OK"

$(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.bin: $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.elf
	$(OBJCOPY) -O binary $< $@

$(GAME_INTEGRATED_BOOTSTRAP_SYMBOLS): $(GAME_INTEGRATED_ASM_SRCS) $(GAME_INTEGRATED_C_SRCS) scripts/create_bootstrap_symbols.py
	python3 scripts/create_bootstrap_symbols.py --output $@ asm/game_integrated/$(GAME_PROFILE) src/game

$(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.elf: $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.ld $(GAME_INTEGRATED_BOOTSTRAP_SYMBOLS) $(GAME_INTEGRATED_ASM_OBJS) $(GAME_INTEGRATED_C_OBJS) $(GAME_LIB) $(GAME_RARE_LIB) $(GAME_LIB_SYMBOLS)
	$(LD) -m elf32btsmip -T $(GAME_LIB_SYMBOLS) -T $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.ld -T $(GAME_INTEGRATED_BOOTSTRAP_SYMBOLS) -o $@ $(GAME_INTEGRATED_ASM_OBJS) $(GAME_INTEGRATED_C_OBJS) --whole-archive $(GAME_LIB) $(GAME_RARE_LIB) --no-whole-archive

$(GAME_INTEGRATED_BUILD_DIR)/src/%.o: src/%.c
	@mkdir -p "$(@D)"
	python3 scripts/compile_c.py --profile $(GAME_PROFILE) --output $@ $<

$(GAME_INTEGRATED_NORMALIZED_ASM_DIR)/%.s: asm/%.s scripts/normalize_asm.py
	python3 scripts/normalize_asm.py $< $@

$(GAME_INTEGRATED_BUILD_DIR)/asm/%.o: $(GAME_INTEGRATED_NORMALIZED_ASM_DIR)/%.s
	@mkdir -p "$(@D)"
	$(AS) $(ASFLAGS) -o $@ $<

-include $(C_OBJS:.o=.asmproc.d) $(GAME_INTEGRATED_C_OBJS:.o=.asmproc.d)

# RSP source is assembled independently of the R4300 compiler. Verification is
# mandatory before the archive is replaced, including on an incremental build.
.PHONY: rsp
rsp:
	python3 scripts/build_rsp.py

$(PROFILE_LIB_RSP_us): $(wildcard src/rsp/*.s) scripts/build_rsp.py config/rsp/us.json toolchain/tools.lock.json
	python3 scripts/build_rsp.py
