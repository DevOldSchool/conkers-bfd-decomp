PROFILE ?= us
SYMBOL ?=
PROFILE_CONFIG := config/profiles/$(PROFILE).yaml
MATERIALIZED_CONFIG := build/config/$(PROFILE).yaml
BUILD_DIR := build/$(PROFILE)
AS := mips-linux-gnu-as
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
GAME_INTEGRATED_ASM_SRCS := $(shell find asm/game_integrated/$(GAME_PROFILE) -type f -name '*.s' ! -path '*/nonmatchings/*' 2>/dev/null)
GAME_INTEGRATED_ASM_OBJS := $(patsubst asm/%.s,$(GAME_INTEGRATED_BUILD_DIR)/asm/%.o,$(GAME_INTEGRATED_ASM_SRCS))
GAME_INTEGRATED_C_SRCS := $(shell python3 scripts/list_integrated_sources.py --overlay game --profile $(GAME_PROFILE) 2>/dev/null)
GAME_INTEGRATED_C_OBJS := $(patsubst src/%.c,$(GAME_INTEGRATED_BUILD_DIR)/src/%.o,$(GAME_INTEGRATED_C_SRCS))
GAME_INTEGRATED_NORMALIZED_ASM_DIR := $(GAME_INTEGRATED_BUILD_DIR)/normalized-asm
GAME_INTEGRATED_BOOTSTRAP_SYMBOLS := $(GAME_INTEGRATED_BUILD_DIR)/bootstrap-symbols.ld
ULTRALIB_DIR := lib/ultralib
ULTRALIB_VERSION ?= L
ULTRALIB_TARGET ?= libultra_rom

.PHONY: help prepare prepare-reference build raw-build diff clean game-asm game-asm-prepare game-integrated game-integrated-prepare game-integrated-raw libultra

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

$(BUILD_DIR)/conker.$(PROFILE).elf: $(BUILD_DIR)/conker.$(PROFILE).ld $(BOOTSTRAP_SYMBOLS) $(ASM_OBJS) $(C_OBJS) $(ASSET_OBJS)
	$(LD) $(LDFLAGS) -T $(BOOTSTRAP_SYMBOLS) -o $@ $(ASM_OBJS) $(C_OBJS) $(ASSET_OBJS)

$(NORMALIZED_ASM_DIR)/%.s: asm/%.s scripts/normalize_asm.py
	python3 scripts/normalize_asm.py $< $@

$(BUILD_DIR)/asm/%.o: $(NORMALIZED_ASM_DIR)/%.s
	@mkdir -p "$(@D)"
	$(AS) $(ASFLAGS) -o $@ $<

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
	$(MAKE) --no-print-directory -C "$(ULTRALIB_DIR)" COMPILER_DIR=/opt/ido VERSION=$(ULTRALIB_VERSION) TARGET=$(ULTRALIB_TARGET) COMPARE=0 setup
	$(MAKE) --no-print-directory -C "$(ULTRALIB_DIR)" COMPILER_DIR=/opt/ido VERSION=$(ULTRALIB_VERSION) TARGET=$(ULTRALIB_TARGET) COMPARE=0

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

game-integrated-prepare:
	rm -rf "asm/game_integrated/$(GAME_PROFILE)" "$(GAME_INTEGRATED_BUILD_DIR)"
	@if ! test -d "reference/game/$(GAME_PROFILE)/asm"; then $(MAKE) --no-print-directory game-asm-prepare GAME_REFERENCE_PROFILE=$(GAME_PROFILE); fi
	python3 scripts/prepare_nonmatching_asm.py --profile "$(GAME_PROFILE)"
	python3 scripts/extract_game_code.py "$(GAME_PROFILE)" --output "$(GAME_INTEGRATED_CODE)"
	python3 scripts/prepare_game_integration.py
	@splat split "build/config/game-integrated.us.yaml" > "$(GAME_INTEGRATED_BUILD_DIR)/splat.log" 2>&1 || { cat "$(GAME_INTEGRATED_BUILD_DIR)/splat.log"; exit 1; }
	@printf '%s\n' "Integrated game split generated; details: $(GAME_INTEGRATED_BUILD_DIR)/splat.log"

game-integrated-raw: $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.bin
	@cmp -s "$(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.bin" "$(GAME_INTEGRATED_CODE)" || { \
		printf '%s\n' "integrated game mismatch: $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.bin" >&2; exit 1; \
	}
	@printf '%s\n' "$(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.bin: OK"

$(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.bin: $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.elf
	$(OBJCOPY) -O binary $< $@

$(GAME_INTEGRATED_BOOTSTRAP_SYMBOLS): $(GAME_INTEGRATED_ASM_SRCS) $(GAME_INTEGRATED_C_SRCS) scripts/create_bootstrap_symbols.py
	python3 scripts/create_bootstrap_symbols.py --output $@ asm/game_integrated/$(GAME_PROFILE) src/game

$(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.elf: $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.ld $(GAME_INTEGRATED_BOOTSTRAP_SYMBOLS) $(GAME_INTEGRATED_ASM_OBJS) $(GAME_INTEGRATED_C_OBJS)
	$(LD) -m elf32btsmip -T $(GAME_INTEGRATED_BUILD_DIR)/conker.game.us.integrated.ld -T $(GAME_INTEGRATED_BOOTSTRAP_SYMBOLS) -o $@ $(GAME_INTEGRATED_ASM_OBJS) $(GAME_INTEGRATED_C_OBJS)

$(GAME_INTEGRATED_BUILD_DIR)/src/%.o: src/%.c
	@mkdir -p "$(@D)"
	python3 scripts/compile_c.py --profile $(GAME_PROFILE) --output $@ $<

$(GAME_INTEGRATED_NORMALIZED_ASM_DIR)/%.s: asm/%.s scripts/normalize_asm.py
	python3 scripts/normalize_asm.py $< $@

$(GAME_INTEGRATED_BUILD_DIR)/asm/%.o: $(GAME_INTEGRATED_NORMALIZED_ASM_DIR)/%.s
	@mkdir -p "$(@D)"
	$(AS) $(ASFLAGS) -o $@ $<

-include $(C_OBJS:.o=.asmproc.d) $(GAME_INTEGRATED_C_OBJS:.o=.asmproc.d)
