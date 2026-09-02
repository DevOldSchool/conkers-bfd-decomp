CC := /opt/ido/cc
AR := mips-linux-gnu-ar
BUILD_DIR := build
TARGET := $(BUILD_DIR)/libultrare.a

CFLAGS := -c -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm \
	-woff 819,820,852,821,838,649 -I . -I include -I include/PR \
	-I src/libultrare -I src/libultra \
	-DVERSION_US -DLANG_US -DREFRESH_NTSC -DLEFTOVERDEBUG \
	-DLEFTOVERSPECTRUM -DBUGFIX_R0 -DBYTEMATCH -DNDEBUG -DTARGET_N64 \
	-mips2 -32 -O1

SOURCES := \
	src/libultrare/io/contramread.c \
	src/libultrare/io/contramwrite.c \
	src/libultrare/io/contreaddata.c \
	src/libultrare/io/controller.c \
	src/libultrare/io/epirawdma.c \
	src/libultrare/io/leodiskinit.c \
	src/libultrare/io/leointerrupt.c \
	src/libultrare/io/pfsinit.c \
	src/libultrare/io/pfsisplug.c \
	src/libultrare/os/destroythread.c \
	src/libultrare/os/initialize.c
OBJECTS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
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

verify: $(TARGET)
	md5sum --check object-md5s.txt

clean:
	rm -rf "$(BUILD_DIR)"
