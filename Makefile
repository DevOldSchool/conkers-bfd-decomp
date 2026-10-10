.DEFAULT_GOAL := help
PROFILE ?= us
ASSETS ?= 0
REFRESH ?= 0
ifneq ($(ASSETS),0)
ifneq ($(ASSETS),1)
$(error ASSETS must be 0 or 1)
endif
endif
ASSET_MODE := $(if $(filter 1,$(ASSETS)),rebuilt,original)
ROM_BUILD_DIR := build/$(PROFILE)$(if $(filter 0,$(ASSETS)),/original-assets)
TIMING := python3 scripts/build_timing.py --profile $(PROFILE) --mode $(ASSET_MODE)
SYMBOL ?=
PROFILE_CONFIG := config/profiles/$(PROFILE).yaml
MATERIALIZED_CONFIG := build/config/$(PROFILE)$(if $(filter 0,$(ASSETS)),.original-assets).yaml
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
	-D_LANGUAGE_C -D_FINALROM -D_MIPS_SZLONG=32 -I include -I lib/ultralib/include -O2 -g3 -mips2
PROFILE_CFLAGS_us := -DPROFILE_US=1
PROFILE_CFLAGS_eu := -DPROFILE_EU=1
PROFILE_CFLAGS := $(PROFILE_CFLAGS_$(PROFILE))
PROFILE_RODATA_SCRIPT_us := config/debugger/us-rodata.ld
PROFILE_RODATA_SCRIPT := $(PROFILE_RODATA_SCRIPT_$(PROFILE))
PROFILE_RODATA_VERIFY_us := scripts/verify_debugger_rodata.py
PROFILE_RODATA_VERIFY := $(PROFILE_RODATA_VERIFY_$(PROFILE))
ROM_NAME := conker.$(PROFILE).z64
ROM_PATH := roms/baserom.$(PROFILE).z64
ASM_SRCS := $(shell find asm/$(PROFILE) -type f -name '*.s' ! -path '*/nonmatchings/*' 2>/dev/null)
ASM_OBJS := $(patsubst asm/%.s,$(BUILD_DIR)/asm/%.o,$(ASM_SRCS))
REQUESTED_GOALS := $(patsubst ./%,%,$(if $(MAKECMDGOALS),$(MAKECMDGOALS),help))
ifeq ($(ASSETS),0)
ifneq ($(filter $(BUILD_DIR)/assets/flat/% $(BUILD_DIR)/assets/font/% $(BUILD_DIR)/assets/audio/% $(BUILD_DIR)/assets/models/%,$(REQUESTED_GOALS)),)
$(error Reconstructed asset targets require ASSETS=1 or ./conker build --assets)
endif
endif
# Load the US layout by default, including aliases and future aggregate goals.
# Only goals known not to link the ROM may bypass broken asset fragments.
NON_ROM_GOALS := clean help prepare-reference libultra libultrare profile-libs game-libs \
	game-asm game-asm-prepare game-integrated game-integrated-refresh \
	game-integrated-prepare game-integrated-raw diff \
	build/game-reference/% build/game-integrated/% build/game-libs/%
ifeq ($(PROFILE),us)
ifneq ($(filter-out $(NON_ROM_GOALS),$(REQUESTED_GOALS)),)
PROFILE_PLAN := $(if $(filter 1,$(ASSETS)),make-assets,make-original-assets)
PROFILE_ASSETS := $(shell python3 scripts/profile_config.py $(PROFILE_PLAN) $(PROFILE_CONFIG) || echo __PROFILE_ASSETS_FAILED__)
ifneq ($(filter __PROFILE_ASSETS_FAILED__,$(PROFILE_ASSETS)),)
$(error scripts/profile_config.py $(PROFILE_PLAN) failed; see the error above)
endif
PROFILE_INPUTS := $(patsubst dep=%,%,$(filter dep=%,$(PROFILE_ASSETS)))
FONT_BINS := $(patsubst font=%,%,$(filter font=%,$(PROFILE_ASSETS)))
AUDIO_BANK_BINS := $(patsubst audio=%,%,$(filter audio=%,$(PROFILE_ASSETS)))
MP3_BANK_BINS := $(patsubst mp3=%,%,$(filter mp3=%,$(PROFILE_ASSETS)))
FLAT_BINS := $(patsubst flat=%,%,$(filter flat=%,$(PROFILE_ASSETS)))
TEXTURE_BINS := $(filter assets/flat/textures/%.bin,$(FLAT_BINS))
MODEL_BANK_BINS := $(patsubst model=%,%,$(filter model=%,$(PROFILE_ASSETS)))
MODEL_BINS := $(filter assets/models/bank03/%.bin assets/models/bank09/%.bin,$(MODEL_BANK_BINS))
endif
endif
ifneq ($(PROFILE_ASSETS),)
C_SRCS := $(patsubst source=%,%,$(filter source=%,$(PROFILE_ASSETS)))
else ifneq ($(filter-out $(NON_ROM_GOALS),$(REQUESTED_GOALS)),)
C_SRCS := $(shell python3 scripts/list_integrated_sources.py --overlay main --profile $(PROFILE) 2>/dev/null) \
	$(shell python3 scripts/list_integrated_sources.py --profile-segment debugger --profile $(PROFILE) 2>/dev/null)
endif
C_OBJS := $(patsubst src/%.c,$(BUILD_DIR)/src/%.o,$(C_SRCS))
# Reviewed main tables and literal pools are external to their text units.
PROFILE_MAIN_RODATA_SECTIONS_us := $(if $(filter $(BUILD_DIR)/src/done/main/init_2E50.o,$(C_OBJS)),.main_rodata_init_2e50) $(if $(filter $(BUILD_DIR)/src/done/main/init_11FA0.o,$(C_OBJS)),.main_rodata_init_11fa0)
PROFILE_MAIN_RODATA_SECTIONS := $(strip $(PROFILE_MAIN_RODATA_SECTIONS_$(PROFILE)))
PROFILE_MAIN_RODATA_SCRIPT_us := $(if $(PROFILE_MAIN_RODATA_SECTIONS),config/main/us-rodata.ld)
PROFILE_MAIN_RODATA_SCRIPT := $(PROFILE_MAIN_RODATA_SCRIPT_$(PROFILE))
PROFILE_MAIN_RODATA_VERIFY_us := $(if $(PROFILE_MAIN_RODATA_SCRIPT),scripts/verify_main_rodata.py)
PROFILE_MAIN_RODATA_VERIFY := $(PROFILE_MAIN_RODATA_VERIFY_$(PROFILE))
PROFILE_MAIN_VI_BSS_SCRIPT_us := $(if $(filter $(BUILD_DIR)/src/done/main/init_34E0.o,$(C_OBJS)),config/main/us-vi-bss.ld)
PROFILE_MAIN_VI_BSS_SCRIPT := $(PROFILE_MAIN_VI_BSS_SCRIPT_$(PROFILE))
PROFILE_MAIN_VI_BSS_VERIFY := $(if $(PROFILE_MAIN_VI_BSS_SCRIPT),scripts/verify_main_vi_bss.py)
PROFILE_MAIN_PRIVATE_DATA_SCRIPT_us := build/us/main-private-data.ld
PROFILE_MAIN_PRIVATE_DATA_SCRIPT := $(PROFILE_MAIN_PRIVATE_DATA_SCRIPT_$(PROFILE))
PROFILE_MAIN_PRIVATE_DATA_VERIFY_us := scripts/main_private_data.py
PROFILE_MAIN_PRIVATE_DATA_VERIFY := $(PROFILE_MAIN_PRIVATE_DATA_VERIFY_$(PROFILE))
MAIN_PRIVATE_DATA_SOURCES := $(foreach source,$(C_SRCS),--source $(source))
LDFLAGS := -m elf32btsmip $(if $(PROFILE_RODATA_SCRIPT),-T $(PROFILE_RODATA_SCRIPT)) $(if $(PROFILE_MAIN_RODATA_SCRIPT),-T $(PROFILE_MAIN_RODATA_SCRIPT)) $(if $(PROFILE_MAIN_VI_BSS_SCRIPT),-T $(PROFILE_MAIN_VI_BSS_SCRIPT)) $(if $(PROFILE_MAIN_PRIVATE_DATA_SCRIPT),-T $(PROFILE_MAIN_PRIVATE_DATA_SCRIPT)) -T $(ROM_BUILD_DIR)/conker.$(PROFILE).ld
NORMALIZED_ASM_DIR := $(BUILD_DIR)/normalized-asm
BOOTSTRAP_SYMBOLS := $(BUILD_DIR)/bootstrap-symbols.ld
ifeq ($(PROFILE),us)
FONT_OBJS := $(patsubst assets/%.bin,$(BUILD_DIR)/assets/%.o,$(FONT_BINS))
AUDIO_BANK_OBJS := $(patsubst assets/%.bin,$(BUILD_DIR)/assets/%.o,$(AUDIO_BANK_BINS))
MP3_BANK_OBJS := $(patsubst assets/%.bin,$(BUILD_DIR)/assets/%.o,$(MP3_BANK_BINS))
TEXTURE_OBJS := $(patsubst assets/%.bin,$(BUILD_DIR)/assets/%.o,$(TEXTURE_BINS))
MODEL_OBJS := $(patsubst assets/%.bin,$(BUILD_DIR)/assets/%.o,$(MODEL_BINS))
endif

# US bin segments mirror the reviewed storage map in config/profiles/us.yaml.
ASSET_BINS_us := \
	assets/boot.bin assets/unassigned_after_main.bin $(FONT_BINS) \
	assets/game_archive_index.bin assets/game_code_rzip.bin assets/game_code_gap.bin \
	assets/game_data_rzip.bin assets/game_data_gap.bin assets/unassigned_after_debugger.bin \
	$(FLAT_BINS) assets/assets_flat_gap.bin assets/asset_bank_index.bin \
	assets/asset_bank_00.bin assets/asset_bank_01.bin assets/asset_bank_02.bin \
	$(MODEL_BANK_BINS) assets/asset_bank_04.bin assets/asset_bank_05.bin \
	assets/asset_bank_06.bin assets/asset_bank_07.bin assets/asset_bank_08.bin \
	assets/asset_bank_0a.bin assets/asset_bank_0b.bin \
	assets/asset_bank_0c.bin assets/asset_bank_0d.bin assets/asset_bank_0e.bin \
	assets/asset_bank_0f.bin assets/asset_bank_10.bin assets/asset_bank_11.bin \
	assets/asset_bank_12.bin assets/asset_bank_13.bin assets/asset_bank_14.bin \
	assets/asset_bank_15.bin $(MP3_BANK_BINS) $(AUDIO_BANK_BINS) \
	assets/asset_bank_18.bin assets/asset_bank_19.bin assets/asset_bank_1a.bin \
	assets/asset_bank_1b.bin assets/asset_bank_1c.bin assets/asset_raw_1d.bin \
	assets/unassigned_rom_tail.bin
ASSET_BINS_eu := assets/boot.bin assets/2D810.bin
ASSET_BINS := $(if $(and $(filter us,$(PROFILE)),$(filter 0,$(ASSETS))),$(patsubst original=%,%,$(filter original=%,$(PROFILE_ASSETS))),$(ASSET_BINS_$(PROFILE)))
ASSET_OBJS := $(patsubst assets/%.bin,$(BUILD_DIR)/assets/%.o,$(ASSET_BINS))
GAME_PROFILE := us
GAME_REFERENCE_PROFILE ?= us
GAME_REFERENCE_BUILD_DIR := build/game-reference/$(GAME_REFERENCE_PROFILE)
GAME_REFERENCE_CODE := $(GAME_REFERENCE_BUILD_DIR)/game.code.bin
GAME_INTEGRATED_BUILD_DIR := build/game-integrated/$(GAME_PROFILE)
GAME_INTEGRATED_CODE := $(GAME_INTEGRATED_BUILD_DIR)/game.code.bin
GAME_INTEGRATED_PREPARED := $(GAME_INTEGRATED_BUILD_DIR)/.prepared
GAME_INTEGRATED_LD_SCRIPT := $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.ld
GAME_INTEGRATED_PREPARE_INPUTS := Makefile Dockerfile config/game/us.yaml config/symbols/game-us.txt config/relocs/game-us.txt config/overlays.json \
	scripts/compile_c.py scripts/create_bootstrap_symbols.py scripts/extract_game_code.py \
	scripts/normalize_asm.py scripts/prepare_game_integration.py toolchain/tools.lock.json
GAME_INTEGRATED_ASM_SRCS := $(shell find asm/game_integrated/$(GAME_PROFILE) -type f -name '*.s' ! -path '*/nonmatchings/*' 2>/dev/null)
GAME_INTEGRATED_ASM_OBJS := $(patsubst asm/%.s,$(GAME_INTEGRATED_BUILD_DIR)/asm/%.o,$(GAME_INTEGRATED_ASM_SRCS))
GAME_INTEGRATED_C_SRCS := $(shell python3 scripts/list_integrated_sources.py --overlay game --profile $(GAME_PROFILE) 2>/dev/null)
GAME_INTEGRATED_C_OBJS := $(patsubst src/%.c,$(GAME_INTEGRATED_BUILD_DIR)/src/%.o,$(GAME_INTEGRATED_C_SRCS))
GAME_INTEGRATED_NORMALIZED_ASM_DIR := $(GAME_INTEGRATED_BUILD_DIR)/normalized-asm
GAME_INTEGRATED_BOOTSTRAP_SYMBOLS := $(GAME_INTEGRATED_BUILD_DIR)/bootstrap-symbols.ld
GAME_LIB_DIR := build/game-libs/us
GAME_LIB := $(GAME_LIB_DIR)/libultra_2_0G.a
GAME_RARE_LIB := $(GAME_LIB_DIR)/libultrare.a
GAME_LIB_SYMBOLS := config/game/us-sdk.ld
GAME_RODATA_SCRIPT := config/game/us-rodata.ld
GAME_LIB_OBJECTS := $(addprefix lib/ultralib/build/G/libultra_rom/src/,\
	gu/random.o gu/ortho.o gu/normalize.o gu/mtxcatl.o gu/mtxcatf.o gu/sqrtf.o \
	gu/mtxutil.o \
	io/visetspecial.o io/piread.o io/sirawdma.o io/crc.o io/controller.o \
	io/pfsinit.o io/contreaddata.o io/pfsisplug.o io/contramread.o io/contramwrite.o \
	os/settimer.o os/gettime.o libc/sprintf.o io/contpfs.o io/pfschecker.o)
GAME_RARE_OBJECTS := $(addprefix lib/libultrare/build/libultrare/io/,\
	conteepread.o conteeplongread.o conteepprobe.o) \
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
PROFILE_LIB_G_us := $(PROFILE_LIB_DIR_us)/libultra_2_0G.a
PROFILE_LIB_GD_us := $(PROFILE_LIB_DIR_us)/libultra_2_0G_d.a
PROFILE_LIB_RARE_us := $(PROFILE_LIB_DIR_us)/libultrare.a
PROFILE_LIB_RSP_us := $(PROFILE_LIB_DIR_us)/librsp.a
PROFILE_LIB_DEPS_us := $(PROFILE_LIB_RSP_us) $(PROFILE_LIB_G_us) $(PROFILE_LIB_GD_us) $(PROFILE_LIB_RARE_us)
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
PROFILE_LIB_INPUTS_us := --whole-archive $(PROFILE_LIB_RSP_us) $(PROFILE_LIB_G_us) $(PROFILE_LIB_GD_us) $(PROFILE_LIB_RARE_us) --no-whole-archive
PROFILE_LIB_INPUTS_eu :=
PROFILE_LIB_INPUTS := $(PROFILE_LIB_INPUTS_$(PROFILE))
LDFLAGS += $(PROFILE_LIB_LDFLAGS_$(PROFILE))

.PHONY: help prepare prepare-reference build raw-build diff clean game-asm game-asm-prepare game-integrated game-integrated-refresh game-integrated-prepare game-integrated-raw libultra libultrare profile-libs game-libs

help:
	@printf '%s\n' 'Use ./conker help for the supported contributor commands.'

prepare:
	@test "$(PROFILE)" = us -o "$(PROFILE)" = eu
	@test -f "$(PROFILE_CONFIG)"
	$(TIMING) --stage prepare -- python3 scripts/prepare_rom.py $(PROFILE) $(if $(filter 1,$(ASSETS)),--assets) $(if $(filter 1,$(REFRESH)),--refresh)

prepare-reference:
	@test "$(PROFILE)" = us -o "$(PROFILE)" = eu
	rm -rf "reference/$(PROFILE)"
	python3 scripts/prepare_profile.py "$(PROFILE)" --reference
	splat split "build/config/reference/$(PROFILE).yaml"

build: prepare
	+$(TIMING) --stage compile-link-verify -- $(MAKE) --no-print-directory raw-build PROFILE=$(PROFILE) ASSETS=$(ASSETS)

raw-build: $(ROM_BUILD_DIR)/$(ROM_NAME) $(PROFILE_RODATA_VERIFY) $(PROFILE_MAIN_RODATA_VERIFY) $(PROFILE_MAIN_VI_BSS_VERIFY) $(PROFILE_MAIN_PRIVATE_DATA_VERIFY)
ifneq ($(PROFILE_RODATA_VERIFY),)
	python3 $(PROFILE_RODATA_VERIFY) "$(ROM_BUILD_DIR)/conker.$(PROFILE).elf"
endif
ifneq ($(PROFILE_MAIN_RODATA_VERIFY),)
	python3 $(PROFILE_MAIN_RODATA_VERIFY) "$(ROM_BUILD_DIR)/conker.$(PROFILE).elf" $(foreach section,$(PROFILE_MAIN_RODATA_SECTIONS),--require $(section))
endif
ifneq ($(PROFILE_MAIN_VI_BSS_VERIFY),)
	python3 $(PROFILE_MAIN_VI_BSS_VERIFY) "$(ROM_BUILD_DIR)/conker.$(PROFILE).elf"
endif
ifneq ($(PROFILE_MAIN_PRIVATE_DATA_VERIFY),)
	python3 $(PROFILE_MAIN_PRIVATE_DATA_VERIFY) verify --elf "$(ROM_BUILD_DIR)/conker.$(PROFILE).elf" $(MAIN_PRIVATE_DATA_SOURCES)
endif
	@cmp -s "$(ROM_BUILD_DIR)/$(ROM_NAME)" "$(ROM_PATH)" || { \
		printf '%s\n' "build mismatch: $(ROM_BUILD_DIR)/$(ROM_NAME)" >&2; exit 1; \
	}
	@printf '%s\n' "$(ROM_BUILD_DIR)/$(ROM_NAME): OK"

$(ROM_BUILD_DIR)/$(ROM_NAME): $(ROM_BUILD_DIR)/conker.$(PROFILE).elf
	$(OBJCOPY) -O binary $< $@

$(BOOTSTRAP_SYMBOLS): $(ASM_SRCS) $(C_SRCS) scripts/create_bootstrap_symbols.py
	python3 scripts/create_bootstrap_symbols.py --output $@ asm/$(PROFILE) $(C_SRCS)

# Selection can change through supported integration; regenerate cheaply and
# preserve the file timestamp when the reviewed active mappings are unchanged.
.PHONY: main-private-data-refresh
main-private-data-refresh:

build/us/main-private-data.ld: config/main/private-data.json scripts/main_private_data.py progress/source_units.json main-private-data-refresh
	python3 scripts/main_private_data.py linker --output $@ $(MAIN_PRIVATE_DATA_SOURCES)

$(ROM_BUILD_DIR)/conker.$(PROFILE).elf: $(ROM_BUILD_DIR)/conker.$(PROFILE).ld $(BOOTSTRAP_SYMBOLS) $(ASM_OBJS) $(C_OBJS) $(ASSET_OBJS) $(PROFILE_LIB_DEPS) $(PROFILE_RODATA_SCRIPT) $(PROFILE_MAIN_RODATA_SCRIPT) $(PROFILE_MAIN_VI_BSS_SCRIPT) $(PROFILE_MAIN_PRIVATE_DATA_SCRIPT)
	$(LD) $(LDFLAGS) -T $(BOOTSTRAP_SYMBOLS) -o $@ $(ASM_OBJS) $(C_OBJS) $(ASSET_OBJS) $(PROFILE_LIB_INPUTS)

$(NORMALIZED_ASM_DIR)/%.s: asm/%.s scripts/normalize_asm.py
	python3 scripts/normalize_asm.py $< $@

$(BUILD_DIR)/asm/%.o: $(NORMALIZED_ASM_DIR)/%.s
	@mkdir -p "$(@D)"
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/asm/$(PROFILE)/header.o: src/header.c
	@mkdir -p "$(@D)"
	python3 scripts/compile_c.py --profile $(PROFILE) --output $@ $<

# Focused checks can overwrite this object with physical-address table addends.
# Refresh its compiler output before applying the runtime alias on every build.
.PHONY: main-queue-thread-object-refresh
main-queue-thread-object-refresh:

build/us/src/done/main/init_2E50.o: src/done/main/init_2E50.c scripts/compile_c.py scripts/prepare_main_library_object.py Makefile main-queue-thread-object-refresh
	@mkdir -p "$(@D)"
	python3 scripts/compile_c.py --profile us --output $@.unprepared $<
	python3 scripts/prepare_main_library_object.py $@.unprepared $@ --delta=-0x70000000 --expected-relocations 7

# The selector table has five code pointers using the 0x10000000 runtime alias.
# Rebase their link addresses by -0x70000000; leave float literals unchanged.
# Always compile afresh: focused checks overwrite this object, and rebasing twice
# would corrupt the table. The linker retains its pool for ROM verification.
.PHONY: main-selector-object-refresh
main-selector-object-refresh:

build/us/src/done/main/init_11FA0.o: src/done/main/init_11FA0.c scripts/compile_c.py scripts/prepare_main_library_object.py Makefile main-selector-object-refresh
	@mkdir -p "$(@D)"
	python3 scripts/compile_c.py --profile us --output $@.unprepared $<
	python3 scripts/prepare_main_library_object.py $@.unprepared $@ --delta=-0x70000000 --expected-relocations 5

$(BUILD_DIR)/src/%.o: src/%.c
	@mkdir -p "$(@D)"
	python3 scripts/compile_c.py --profile $(PROFILE) --output $@ $<

# Pack only when an asset target is reached. These are ordinary prerequisites,
# not included makefiles (which Make would refresh even for unrelated goals).
# Packing preserves unchanged parts' mtimes. The object recipes compare the
# fresh on-disk timestamps because Make may cache a part's mtime before packing.
ifeq ($(PROFILE),us)
ASSET_PACK_DEPS := Makefile $(PROFILE_INPUTS) scripts/profile_config.py config/rzip_layouts.json \
	scripts/build_files.py scripts/rzip_archive.py scripts/rzip_extract.py \
	toolchain/python-requirements.txt $(ROM_PATH)
FONT_PARTS := $(patsubst assets/%,$(BUILD_DIR)/fonts/parts/%,$(FONT_BINS))
MP3_BANK_PARTS := $(patsubst assets/%,$(BUILD_DIR)/audio/parts/%,$(MP3_BANK_BINS))
MODEL_PARTS := $(patsubst assets/%,$(BUILD_DIR)/models/parts/%,$(MODEL_BINS))
TEXTURE_PARTS := $(patsubst assets/%,$(BUILD_DIR)/textures/parts/%,$(TEXTURE_BINS))
.PHONY: asset-parts-missing
asset-parts-missing:

ifneq ($(FONT_PARTS),)
FONT_PART_INPUTS := $(wildcard build/fonts/us build/fonts/us/*)
FONT_PARTS_MISSING := $(filter-out $(wildcard $(FONT_PARTS)),$(FONT_PARTS))
ifeq ($(wildcard build/fonts/us/manifest.json),)
FONT_PARTS_MISSING += manifest
endif
$(BUILD_DIR)/fonts/parts.stamp: $(ASSET_PACK_DEPS) scripts/font_splits.py scripts/font_assets.py $(FONT_PART_INPUTS) $(if $(FONT_PARTS_MISSING),asset-parts-missing)
	$(TIMING) --stage fonts -- python3 scripts/font_splits.py build-parts
	@touch $@
$(FONT_PARTS): $(BUILD_DIR)/fonts/parts.stamp ;
endif

ifneq ($(MODEL_PARTS),)
MODEL_INPUTS := $(wildcard build/assets/model-build/us/* build/assets/model-build/us/*/* build/assets/model-build/us/*/*/*)
MODEL_PARTS_MISSING := $(filter-out $(wildcard $(MODEL_PARTS)),$(MODEL_PARTS))
MODEL_MANIFESTS := $(foreach bank,03 09,$(patsubst assets/models/bank$(bank)/%.bin,build/assets/model-build/us/$(bank)/%/manifest.json,$(filter assets/models/bank$(bank)/%.bin,$(MODEL_BINS))))
MODEL_REQUIRED_INPUTS := $(MODEL_MANIFESTS) $(patsubst %/manifest.json,%/model.json,$(MODEL_MANIFESTS))
MODEL_PARTS_MISSING += $(filter-out $(wildcard $(MODEL_REQUIRED_INPUTS)),$(MODEL_REQUIRED_INPUTS))
# Only codecs used by the reviewed native-record reconstruction path.
MODEL_CODEC_DEPS := scripts/model_build.py scripts/model_assets.py scripts/texture_build.py scripts/rzip_pack.py
$(BUILD_DIR)/models/parts.stamp: $(ASSET_PACK_DEPS) $(MODEL_CODEC_DEPS) config/model_build.us.json $(MODEL_INPUTS) $(if $(MODEL_PARTS_MISSING),asset-parts-missing)
	$(TIMING) --stage models -- python3 scripts/model_build.py build-parts
	@touch $@
$(MODEL_PARTS): $(BUILD_DIR)/models/parts.stamp ;
endif

ifneq ($(TEXTURE_PARTS),)
TEXTURE_INPUTS := $(wildcard build/assets/texture-build/us build/assets/texture-build/us/* build/assets/texture-build/us/*/* build/assets/texture-build/us/*/*/*)
TEXTURE_PARTS_MISSING := $(filter-out $(wildcard $(TEXTURE_PARTS)),$(TEXTURE_PARTS))
ifeq ($(wildcard build/assets/texture-build/us/1063/manifest.json),)
TEXTURE_PARTS_MISSING += manifest
endif
TEXTURE_CODEC_DEPS := $(wildcard scripts/texture_*.py) $(wildcard scripts/model_*.py) scripts/hud_assets.py scripts/hud_additional_artwork.py scripts/rzip_pack.py config/texture_encoders.us.json
$(BUILD_DIR)/textures/parts.stamp: $(ASSET_PACK_DEPS) scripts/texture_build.py $(TEXTURE_CODEC_DEPS) $(TEXTURE_INPUTS) $(if $(TEXTURE_PARTS_MISSING),asset-parts-missing)
	$(TIMING) --stage textures -- python3 scripts/texture_build.py build-parts
	@touch $@
$(TEXTURE_PARTS): $(BUILD_DIR)/textures/parts.stamp ;
endif

ifneq ($(MP3_BANK_PARTS),)
MP3_PART_INPUTS := $(wildcard build/assets/mp3-bank/us build/assets/mp3-bank/us/* build/assets/mp3-bank/us/streams/* build/assets/mp3-bank/us/padding/*)
MP3_PARTS_MISSING := $(filter-out $(wildcard $(MP3_BANK_PARTS)),$(MP3_BANK_PARTS))
ifeq ($(wildcard build/assets/mp3-bank/us/manifest.json),)
MP3_PARTS_MISSING += manifest
endif
$(BUILD_DIR)/audio/parts.stamp: $(ASSET_PACK_DEPS) scripts/mp3_bank.py scripts/mp3_assets.py $(MP3_PART_INPUTS) $(if $(MP3_PARTS_MISSING),asset-parts-missing)
	$(TIMING) --stage mp3 -- python3 scripts/mp3_bank.py build-parts
	@touch $@
$(MP3_BANK_PARTS): $(BUILD_DIR)/audio/parts.stamp ;
endif
endif

$(FONT_OBJS): $(BUILD_DIR)/assets/%.o: $(BUILD_DIR)/fonts/parts/%.bin
	@if test ! -f "$@" || test "$<" -nt "$@"; then \
		mkdir -p "$(@D)" && cd $(BUILD_DIR)/fonts/parts && \
		set -x && $(LD) -r -b binary -m elf32btsmip -o $(abspath $@) $*.bin; \
	fi

$(MP3_BANK_OBJS): $(BUILD_DIR)/assets/%.o: $(BUILD_DIR)/audio/parts/%.bin
	@if test ! -f "$@" || test "$<" -nt "$@"; then \
		mkdir -p "$(@D)" && cd $(BUILD_DIR)/audio/parts && \
		set -x && $(LD) -r -b binary -m elf32btsmip -o $(abspath $@) $*.bin; \
	fi

$(TEXTURE_OBJS): $(BUILD_DIR)/assets/%.o: $(BUILD_DIR)/textures/parts/%.bin
	@if test ! -f "$@" || test "$<" -nt "$@"; then \
		mkdir -p "$(@D)" && cd $(BUILD_DIR)/textures/parts && \
		set -x && $(LD) -r -b binary -m elf32btsmip -o $(abspath $@) $*.bin; \
	fi

$(MODEL_OBJS): $(BUILD_DIR)/assets/%.o: $(BUILD_DIR)/models/parts/%.bin
	@if test ! -f "$@" || test "$<" -nt "$@"; then \
		mkdir -p "$(@D)" && cd $(BUILD_DIR)/models/parts && \
		set -x && $(LD) -r -b binary -m elf32btsmip -o $(abspath $@) $*.bin; \
	fi

.PHONY: data-splits-check
data-splits-check:
	python3 scripts/data_boundaries.py

ifeq ($(PROFILE),us)
raw-build: data-splits-check
endif

# Require checked-in bank-17 splits to agree with the loader and sequence descriptors.
.PHONY: audio-boundaries-check
audio-boundaries-check:
	python3 scripts/audio_boundaries.py verify

$(AUDIO_BANK_OBJS): | audio-boundaries-check

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
	$(MAKE) --no-print-directory libultra ULTRALIB_VERSION=G
	$(MAKE) --no-print-directory -C "$(ULTRALIB_DIR)" COMPILER_DIR=/opt/ido VERSION=G TARGET=libultra_d COMPARE=0 MODERN_LD=1 \
		$(addprefix build/G/libultra_d/src/audio/,$(addsuffix .marker,cents2ratio cspgetstate cspgettempo))
	$(MAKE) --no-print-directory libultrare
	@mkdir -p "$(PROFILE_LIB_DIR_us)"
	@mkdir -p "$(PROFILE_LIB_DIR_us)/libultra-members"
	$(OBJCOPY) --redefine-sym __osLeoInterrupt=__osLeoInterruptPhysical \
		$(ULTRALIB_DIR)/build/G/libultra_rom/src/os/initialize.o \
		"$(PROFILE_LIB_DIR_us)/libultra-members/initialize.o"
	rm -f "$(PROFILE_LIB_G_us)"
	$(AR) crs "$(PROFILE_LIB_G_us)" \
		$(addprefix $(ULTRALIB_DIR)/build/G/libultra_rom/src/io/,$(addsuffix .o,ai aigetstat aisetfreq contpfs contramread contramwrite contreaddata controller crc epirawdma leodiskinit leointerrupt pfschecker pfsinit pfsisplug piacs pidma pigetcmdq pigetstat pirawdma pirawread si siacs sirawdma sirawread sirawwrite sp spgetstat sprawdma spsetpc spsetstat sptaskyield sptaskyielded vi viblack vigetcurrcontext vigetcurrframebuf vigetnextframebuf visetevent visetmode viswapbuf viswapcontext)) \
		$(addprefix $(ULTRALIB_DIR)/build/G/libultra_rom/src/libc/,$(addsuffix .o,bcopy bzero ldiv ll string xlitob)) \
		$(addprefix $(ULTRALIB_DIR)/build/G/libultra_rom/src/gu/,$(addsuffix .o,libm_vals sinf sqrtf)) \
		$(addprefix $(ULTRALIB_DIR)/build/G/libultra_rom/src/os/,$(addsuffix .o,createmesgqueue destroythread getcount getsr getthreadpri gettime interrupt invaldcache invalicache jammesg maptlb probetlb recvmesg sendmesg setcompare seteventmesg setfpccsr sethwinterrupt setintmask setsr setthreadpri settimer startthread stopthread thread timerintr unmaptlb virtualtophysical writebackdcache writebackdcacheall)) \
		$(addprefix $(ULTRALIB_DIR)/build/G/libultra_rom/src/vimodes/,$(addsuffix .o,vimodepallan1 vimodempallan1 vimodentsclan1)) \
		"$(PROFILE_LIB_DIR_us)/libultra-members/initialize.o"
	rm -f "$(PROFILE_LIB_GD_us)"
	$(AR) crs "$(PROFILE_LIB_GD_us)" \
		$(addprefix $(ULTRALIB_DIR)/build/G/libultra_d/src/audio/,$(addsuffix .o,cents2ratio cspgetstate cspgettempo))
	@mkdir -p "$(PROFILE_LIB_DIR_us)/libultrare-members"
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
		$(addprefix lib/libultrare/build/libultrare/audio/,$(addsuffix .o,n_synaddplayer n_synsetpriority n_cspplay n_cspstop n_synstopvoice n_synfreevoice n_synsetvol n_synsetpitch n_cspsetpan n_cspsetseq n_cspsetvol n_syndelete n_sl n_cspsendmidi n_synallocfx n_synfx n_synfilter11 n_synfilter12 n_synfilter13 n_synsetpan n_synstartvoiceparam n_event n_synallocvoice n_cseqnextdelta))

game-libs:
	$(MAKE) --no-print-directory libultra ULTRALIB_VERSION=G ULTRALIB_TARGET=libultra_rom
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
	python3 scripts/verify_game_rodata.py "$(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.elf"
	@cmp -s "$(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.bin" "$(GAME_INTEGRATED_CODE)" || { \
		printf '%s\n' "integrated game mismatch: $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.bin" >&2; exit 1; \
	}
	@printf '%s\n' "$(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.bin: OK"

$(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.bin: $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.elf
	$(OBJCOPY) -O binary $< $@

$(GAME_INTEGRATED_BOOTSTRAP_SYMBOLS): $(GAME_INTEGRATED_ASM_SRCS) $(GAME_INTEGRATED_C_SRCS) scripts/create_bootstrap_symbols.py
	python3 scripts/create_bootstrap_symbols.py --output $@ asm/game_integrated/$(GAME_PROFILE) $(GAME_INTEGRATED_C_SRCS)

$(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.elf: $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.ld $(GAME_INTEGRATED_BOOTSTRAP_SYMBOLS) $(GAME_INTEGRATED_ASM_OBJS) $(GAME_INTEGRATED_C_OBJS) $(GAME_LIB) $(GAME_RARE_LIB) $(GAME_LIB_SYMBOLS) $(GAME_RODATA_SCRIPT)
	$(LD) -m elf32btsmip -T $(GAME_LIB_SYMBOLS) -T $(GAME_RODATA_SCRIPT) -T $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.ld -T $(GAME_INTEGRATED_BOOTSTRAP_SYMBOLS) -o $@ $(GAME_INTEGRATED_ASM_OBJS) $(GAME_INTEGRATED_C_OBJS) --whole-archive $(GAME_LIB) $(GAME_RARE_LIB) --no-whole-archive

$(GAME_INTEGRATED_BUILD_DIR)/src/%.o: src/%.c
	@mkdir -p "$(@D)"
	python3 scripts/compile_c.py --profile $(GAME_PROFILE) --output $@ $<
	$(if $(filter game_16EE20.o game_1C1150.o,$(notdir $@)),python3 scripts/split_game_rodata.py $@)

$(filter %/game_16EE20.o %/game_1C1150.o,$(GAME_INTEGRATED_C_OBJS)): scripts/split_game_rodata.py

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

# Splat emits dependencies for the generated GLOBAL_ASM bodies in C scaffolds.
-include $(C_OBJS:.o=.asmproc.d)
