/* Compile with the existing Mupen SDK; exercises PCM capture without a ROM. */
#define _POSIX_C_SOURCE 200809L
#include <assert.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../scripts/mupen_audio_capture.c"
static uint32_t read32(const unsigned char *p) {
    return p[0] | ((uint32_t)p[1]<<8) | ((uint32_t)p[2]<<16) | ((uint32_t)p[3]<<24);
}
int main(int argc, char **argv) {
    unsigned char ram[8] = {0x78,0x56,0x34,0x12,0xbc,0x9a,0xf0,0xde}, bytes[52];
    unsigned int address=0, length=8, dac=2210;
    AUDIO_INFO info={0}; FILE *file; char path[1024];
    assert(argc==2); assert(setenv("CONKER_AUDIO_CAPTURE_DIR",argv[1],1)==0);
    info.RDRAM=ram; info.AI_DRAM_ADDR_REG=&address;
    info.AI_LEN_REG=&length; info.AI_DACRATE_REG=&dac;
    assert(PluginStartup(NULL,NULL,NULL)==M64ERR_SUCCESS);
    assert(InitiateAudio(info)); assert(RomOpen());
    AiDacrateChanged(0); AiLenChanged(); RomClosed();
    snprintf(path,sizeof(path),"%s/ai-000-%u.wav",argv[1],frequency);
    file=fopen(path,"rb"); assert(file); assert(fread(bytes,1,52,file)==52); fclose(file);
    assert(!memcmp(bytes,"RIFF",4)); assert(read32(bytes+4)==44);
    assert(read32(bytes+24)==48681812/2211); assert(read32(bytes+40)==8);
    assert(!memcmp(bytes+44,"\x34\x12\x78\x56\xf0\xde\xbc\x9a",8));
    /* A fresh plugin instance must refuse to replace the capture above. */
    PluginStartup(NULL,NULL,NULL); AiDacrateChanged(0); AiLenChanged();
    assert(failed && !output);
    /* New rate opens a distinct part; invalid DMA never reads RAM. */
    failed=0; dac=1104; AiDacrateChanged(0); AiLenChanged(); RomClosed();
    address=1; length=4; AiLenChanged(); assert(failed);
    failed=0; address=0x800000; length=4; AiLenChanged(); assert(failed);
    failed=0; address=0; length=3; AiLenChanged(); assert(failed);
    failed=0; dac=UINT_MAX; AiDacrateChanged(0); assert(failed);
    PluginShutdown();
    /* Optional US request sampling uses N64 big-endian halfword addressing. */
    {
        char directory[1024], csv_path[1200], line[128];
        unsigned char *large_ram = calloc(1, 0x800000);
        assert(large_ram);
        snprintf(directory, sizeof(directory), "%s/probe", argv[1]);
        assert(mkdir(directory, 0700) == 0);
        setenv("CONKER_AUDIO_CAPTURE_DIR", directory, 1);
        setenv("CONKER_AUDIO_US_MP3_REQUEST_LOG", "1", 1);
        setenv("CONKER_AUDIO_US_HEALTH_LOG", "1", 1);
        info.RDRAM = large_ram; address = 0; length = 4; dac = 2210;
        PluginStartup(NULL,NULL,NULL); InitiateAudio(info); assert(RomOpen());
        AiDacrateChanged(0);
        large_ram[0xcc49a ^ 3] = 6;
        large_ram[0x427f4 ^ 3] = 0; large_ram[0x427f5 ^ 3] = 239;
        AiLenChanged(); AiLenChanged();
        large_ram[0xcc49a ^ 3] = 5;
        large_ram[0x427f5 ^ 3] = 240; AiLenChanged(); RomClosed();
        snprintf(csv_path, sizeof(csv_path), "%s/us-mp3-requests.csv", directory);
        file = fopen(csv_path, "r"); assert(file);
        assert(fgets(line, sizeof(line), file) && strstr(line, "last_requested_id"));
        assert(fgets(line, sizeof(line), file) && !strcmp(line, "0.000000000,239\n"));
        assert(fgets(line, sizeof(line), file) && strstr(line, ",240\n"));
        assert(!fgets(line, sizeof(line), file)); fclose(file);
        assert(large_ram[0xcc49a ^ 3] == 5); /* observer performs no writes */
        snprintf(csv_path, sizeof(csv_path), "%s/us-health.csv", directory);
        file = fopen(csv_path, "r"); assert(file);
        assert(fgets(line, sizeof(line), file) && strstr(line, "health_byte"));
        assert(fgets(line, sizeof(line), file) && !strcmp(line, "0.000000000,6\n"));
        assert(fgets(line, sizeof(line), file) && strstr(line, ",5\n"));
        assert(!fgets(line, sizeof(line), file)); fclose(file);
        PluginStartup(NULL,NULL,NULL); assert(!RomOpen()); PluginShutdown();
        unsetenv("CONKER_AUDIO_US_HEALTH_LOG");
        unsetenv("CONKER_AUDIO_US_MP3_REQUEST_LOG"); free(large_ram);
    }
    puts("AI capture PCM, header, rate, overwrite and DMA safety checks passed");
    return 0;
}
