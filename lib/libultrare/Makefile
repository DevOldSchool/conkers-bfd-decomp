CC := /opt/ido/cc
AR := mips-linux-gnu-ar
AS := mips-linux-gnu-as
CPP := /opt/ido/cc -E
OBJCOPY := mips-linux-gnu-objcopy
BUILD_DIR := build
TARGET := $(BUILD_DIR)/libultrare.a

CFLAGS := -c -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm \
	-woff 819,820,852,821,838,649 -I . -I include -I include/PR \
	-I src/libultrare -I src/libultra \
	-DVERSION_US -DLANG_US -DREFRESH_NTSC -DLEFTOVERDEBUG \
	-DLEFTOVERSPECTRUM -DBUGFIX_R0 -DBYTEMATCH -DNDEBUG -DTARGET_N64 \
	-mips2 -32 -O1

SOURCES := \
	src/libultrare/libc/xldtob.c \
	src/libultrare/libc/xprintf.c \
	src/libultrare/mp3/playback.c \
	src/libultrare/gu/expf.c \
	src/libultrare/gu/logf.c \
	src/libultrare/mp3/decoder.c \
	src/libultrare/mp3/main.c \
	src/libultrare/audio/n_sndplayer.c \
	src/libultrare/audio/n_cspsetbank.c \
	src/libultrare/audio/n_csplayer.c \
	src/libultrare/audio/n_cspctrl.c \
	src/libultrare/audio/osc.c \
	src/libultrare/audio/heap.c \
	src/libultrare/audio/bnkf.c \
	src/libultrare/audio/n_seqplayer.c \
	src/libultrare/audio/n_csq.c \
	src/libultrare/audio/alsurround.c \
	src/libultrare/audio/n_env.c \
	src/libultrare/audio/n_reverb.c \
	src/libultrare/audio/n_load.c \
	src/libultrare/audio/n_resample2.c \
	src/libultrare/audio/n_auxbus.c \
	src/libultrare/audio/n_resample.c \
	src/libultrare/audio/n_cspchan.c \
	src/libultrare/audio/n_cspsetfxmix.c \
	src/libultrare/audio/n_cspsetfxparam.c \
	src/libultrare/audio/n_cspevent12.c \
	src/libultrare/audio/n_mainbus.c \
	src/libultrare/audio/n_drvrNew.c \
	src/libultrare/audio/n_synthesizer.c \
	src/libultrare/libc/syncprintf.c \
	src/libultrare/audio/n_cseqnextdelta.c \
	src/libultrare/audio/n_synallocvoice.c \
	src/libultrare/audio/n_event.c \
	src/libultrare/audio/n_synfilter11.c \
	src/libultrare/audio/n_synfilter12.c \
	src/libultrare/audio/n_synfilter13.c \
	src/libultrare/audio/n_synsetpan.c \
	src/libultrare/audio/n_synstartvoiceparam.c \
	src/libultrare/audio/n_synfx.c \
	src/libultrare/audio/n_cspsendmidi.c \
	src/libultrare/audio/n_synallocfx.c \
	src/libultrare/audio/n_cspsetpan.c \
	src/libultrare/audio/n_cspsetseq.c \
	src/libultrare/audio/n_cspsetvol.c \
	src/libultrare/audio/n_syndelete.c \
	src/libultrare/audio/n_sl.c \
	src/libultrare/audio/n_cspplay.c \
	src/libultrare/audio/n_cspstop.c \
	src/libultrare/audio/n_synstopvoice.c \
	src/libultrare/audio/n_synfreevoice.c \
	src/libultrare/audio/n_synsetvol.c \
	src/libultrare/audio/n_synsetpitch.c \
	src/libultrare/audio/n_synaddplayer.c \
	src/libultrare/audio/n_synsetpriority.c \
	src/libultra/os/exceptasm_data.c \
	src/libultra/os/syncputchars_data.c \
	src/libultrare/gu/mtxutil.c \
	src/libultrare/gu/rotate.c \
	src/libultrare/gu/cosf.c \
	src/libultrare/gu/sinf.c \
	src/libultrare/gu/perspective.c \
	src/libultrare/io/contramread.c \
	src/libultrare/io/contramwrite.c \
	src/libultrare/io/contreaddata.c \
	src/libultrare/io/controller.c \
	src/libultrare/io/conteepread.c \
	src/libultrare/io/conteeplongread.c \
	src/libultrare/io/conteepprobe.c \
	src/libultrare/io/epirawdma.c \
	src/libultrare/io/leodiskinit.c \
	src/libultrare/io/leointerrupt.c \
	src/libultrare/io/pfsinit.c \
	src/libultrare/io/pfsisplug.c \
	src/libultrare/io/siacs_game.c \
	src/libultrare/io/vi.c \
	src/libultrare/io/vimodepallan1.c \
	src/libultrare/os/destroythread.c \
	src/libultrare/os/initialize.c
ASM_SOURCES := src/libultrare/mp3/util.S src/libultrare/mp3/lib_46650.S src/libultrare/mp3/lib_47550.S
OBJECTS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SOURCES)) $(patsubst src/%.S,$(BUILD_DIR)/%.o,$(ASM_SOURCES))
HEADERS := $(shell find include src -type f -name '*.h')

.PHONY: all verify clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p "$(@D)"
	rm -f "$@"
	$(AR) crs "$@" $(OBJECTS)

$(BUILD_DIR)/%.o: src/%.c $(HEADERS)
	@mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -o "$@" "$<"
	$(if $(REMOVE_MDEBUG),$(OBJCOPY) --remove-section .mdebug "$@",@true)

# Independently sourced Rare MP3 assembly retains its instruction bodies.
$(BUILD_DIR)/%.o: src/%.S $(HEADERS) src/libultrare/mp3/macros.inc
	@mkdir -p "$(@D)"
	$(CPP) -P -D_LANGUAGE_ASSEMBLY -D_MIPSEB -I src/libultrare/mp3 -I ../ultralib/include -I ../ultralib/include/PR "$<" > "$@.s"
	$(AS) -EB -march=vr4300 -mabi=32 -o "$@" "$@.s"

# Matrix routines use the SDK 2.0I graphics optimization level. Other Rare
# objects retain their accepted O1 flags and object checksums.
$(BUILD_DIR)/libultrare/gu/mtxutil.o: CFLAGS := $(filter-out -O1,$(CFLAGS)) -O3
$(BUILD_DIR)/libultrare/gu/rotate.o: CFLAGS := $(filter-out -O1,$(CFLAGS)) -O2 -g3
$(BUILD_DIR)/libultrare/gu/cosf.o $(BUILD_DIR)/libultrare/gu/sinf.o $(BUILD_DIR)/libultrare/gu/perspective.o $(addprefix $(BUILD_DIR)/libultrare/gu/,expf.o logf.o): CFLAGS := $(filter-out -O1,$(CFLAGS)) -O2 -g3
$(addprefix $(BUILD_DIR)/libultrare/io/,conteepread.o conteeplongread.o conteepprobe.o): CFLAGS := $(filter-out -O1,$(CFLAGS)) -O2 -g3
$(BUILD_DIR)/libultrare/audio/%.o $(BUILD_DIR)/libultrare/mp3/%.o: CFLAGS += -g2
$(BUILD_DIR)/libultrare/libc/syncprintf.o $(BUILD_DIR)/libultrare/libc/xprintf.o $(BUILD_DIR)/libultrare/libc/xldtob.o: CFLAGS := $(filter-out -O1,$(CFLAGS)) -O2 -g3

# IDO debug metadata contains the build hostname and timestamp. Keep the
# scheduling effects of -g2/-g3, but omit this non-runtime section from the
# reconstructed objects before recording reproducible object checksums.
RECONSTRUCTED_DEBUG_OBJECTS := $(BUILD_DIR)/libultrare/libc/syncprintf.o $(BUILD_DIR)/libultrare/libc/xprintf.o $(BUILD_DIR)/libultrare/libc/xldtob.o $(addprefix $(BUILD_DIR)/libultrare/gu/,rotate.o cosf.o sinf.o perspective.o expf.o logf.o) \
	$(addprefix $(BUILD_DIR)/libultrare/io/,conteepread.o conteeplongread.o conteepprobe.o) \
	$(filter $(BUILD_DIR)/libultrare/audio/% $(BUILD_DIR)/libultrare/mp3/%,$(OBJECTS))
$(RECONSTRUCTED_DEBUG_OBJECTS): REMOVE_MDEBUG := 1
$(RECONSTRUCTED_DEBUG_OBJECTS): Makefile

verify: $(TARGET)
	md5sum --check object-md5s.txt

clean:
	rm -rf "$(BUILD_DIR)"
