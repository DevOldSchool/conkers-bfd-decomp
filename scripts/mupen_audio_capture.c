/* SPDX-License-Identifier: MIT
 * Record Mupen64Plus AI DMA PCM before host playback/resampling.
 * Run only with an RSP that executes audio microcode (ProcessAList is empty).
 * CONKER_AUDIO_CAPTURE_DIR must name a fresh, existing private directory.
 */
#define M64P_PLUGIN_PROTOTYPES 1
#include <m64p_common.h>
#include <m64p_plugin.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#error "This AI capture plugin currently supports little-endian hosts only"
#endif

static AUDIO_INFO audio;
static FILE *output;
static uint32_t frequency = 33600, data_bytes, part;
static int failed;
static void *debug_context;
static void (*debug_callback)(void *, int, const char *);
static void fail(const char *message) {
    failed = 1;
    if (debug_callback) debug_callback(debug_context, M64MSG_ERROR, message);
}

static void little16(FILE *file, uint16_t value) {
    fputc(value & 255, file); fputc(value >> 8, file);
}
static void little32(FILE *file, uint32_t value) {
    little16(file, value & 65535); little16(file, value >> 16);
}
static void header(FILE *file, uint32_t bytes) {
    rewind(file);
    fwrite("RIFF", 1, 4, file); little32(file, bytes + 36);
    fwrite("WAVEfmt ", 1, 8, file); little32(file, 16);
    little16(file, 1); little16(file, 2); little32(file, frequency);
    little32(file, frequency * 4); little16(file, 4); little16(file, 16);
    fwrite("data", 1, 4, file); little32(file, bytes);
}
static void close_part(void) {
    if (output) { header(output, data_bytes); fclose(output); output = NULL; }
}
EXPORT m64p_error CALL PluginStartup(m64p_dynlib_handle core, void *context,
                                     void (*debug)(void *, int, const char *)) {
    (void)core; debug_context = context; debug_callback = debug;
    failed = 0; part = 0; data_bytes = 0; frequency = 33600;
    return M64ERR_SUCCESS;
}
EXPORT m64p_error CALL PluginShutdown(void) { close_part(); return M64ERR_SUCCESS; }
EXPORT m64p_error CALL PluginGetVersion(m64p_plugin_type *type, int *version,
                                       int *api, const char **name, int *caps) {
    if (type) *type = M64PLUGIN_AUDIO;
    if (version) *version = 0x010000;
    if (api) *api = 0x020000;
    if (name) *name = "Conker private AI PCM capture";
    if (caps) *caps = 0;
    return M64ERR_SUCCESS;
}
EXPORT int CALL InitiateAudio(AUDIO_INFO info) { audio = info; return 1; }
EXPORT int CALL RomOpen(void) { return getenv("CONKER_AUDIO_CAPTURE_DIR") != NULL; }
EXPORT void CALL RomClosed(void) { close_part(); }
EXPORT void CALL AiDacrateChanged(int system) {
    uint32_t clock = system == 1 ? 49656530 : system == 2 ? 48628316 : 48681812;
    uint32_t next = clock / ((uint64_t)*audio.AI_DACRATE_REG + 1);
    if (next < 4000 || next > 192000) { fail("AI capture rejected an invalid DAC rate or unsafe output"); return; }
    if (next != frequency) { close_part(); frequency = next; }
}
EXPORT void CALL AiLenChanged(void) {
    uint32_t address = *audio.AI_DRAM_ADDR_REG & 0xffffff;
    uint32_t length = *audio.AI_LEN_REG;
    const char *directory = getenv("CONKER_AUDIO_CAPTURE_DIR");
    unsigned char converted[16384];
    char filename[1024];
    if (failed || !directory || length == 0) return;
    if ((length & 3) || (address & 3) || address > 0x800000 || length > 0x800000 - address ||
        data_bytes > 0x40000000 - length) { fail("AI capture rejected an invalid DAC rate or unsafe output"); return; }
    if (!output) {
        int written = snprintf(filename, sizeof(filename), "%s/ai-%03u-%u.wav", directory, part++, frequency);
        if (written < 0 || (size_t)written >= sizeof(filename)) { fail("AI capture rejected an invalid DAC rate or unsafe output"); return; }
        output = fopen(filename, "wbx"); /* never truncate an earlier capture */
        if (!output) { fail("AI capture rejected an invalid DAC rate or unsafe output"); return; }
        data_bytes = 0; header(output, 0); fseek(output, 44, SEEK_SET);
    }
    for (uint32_t offset = 0; offset < length;) {
        uint32_t count = length - offset;
        if (count > sizeof(converted)) count = sizeof(converted);
        for (uint32_t i = 0; i < count; i += 4) {
            /* Core memory uses little-endian 32-bit words: [Rlo,Rhi,Llo,Lhi]. */
            const unsigned char *p = audio.RDRAM + address + offset + i;
            converted[i] = p[2]; converted[i + 1] = p[3];
            converted[i + 2] = p[0]; converted[i + 3] = p[1];
        }
        if (fwrite(converted, 1, count, output) != count) { fail("AI capture write failed"); break; }
        data_bytes += count; offset += count;
    }
}
EXPORT void CALL ProcessAList(void) {}
EXPORT void CALL SetSpeedFactor(int percent) { (void)percent; }
EXPORT void CALL VolumeUp(void) {}
EXPORT void CALL VolumeDown(void) {}
EXPORT int CALL VolumeGetLevel(void) { return 100; }
EXPORT void CALL VolumeSetLevel(int level) { (void)level; }
EXPORT void CALL VolumeMute(void) {}
EXPORT const char * CALL VolumeGetString(void) { return "AI capture (unscaled)"; }
