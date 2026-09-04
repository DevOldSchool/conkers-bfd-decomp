/* Original US SDK relocation targets; see docs/evidence/game_sdk_tail_text_bounds.md.
 * Some overlay copies retain calls into the main executable, including calls
 * to functions defined in their own archive member. Explicit assignments
 * preserve those bindings without changing SDK source or object instructions.
 */
__osDisableInt = 0x10022DC0;
__osRestoreInt = 0x10022DE0;
__osViNext = 0x8002BDE4;
__osTimerList = 0x8002BD70;
__osInsertTimer = 0x10024128;
__osSetTimerIntr = 0x100240B4;
osGetCount = 0x10024770;
__osBaseCounter = 0x800429B8;
__osCurrentTime = 0x800429B0;
memcpy = 0x10022EC0;
_Printf = 0x100020D0;
sqrtf = 0x10026530;
guMtxIdentF = 0x151EFE00;
guMtxF2L = 0x151EFD00;
guMtxL2F = 0x151EFEB8;
guMtxXFMF = 0x151F0140;
guMtxCatF = 0x151F01E0;
__osContRamRead = 0x10025C20;
__osContRamWrite = 0x10025870;
__osSumcalc = 0x10027910;
__osIdCheckSum = 0x1002796C;
__osRepairPackId = 0x100279D4;
__osCheckPackId = 0x10027DEC;
__osGetId = 0x10027F84;
__osCheckId = 0x100281E0;
__osPfsRWInode = 0x100282DC;
__osPfsSelectBank = 0x100285FC;
corrupted_init = 0x10028D34;
corrupted = 0x10028EE8;

/* Additional complete SDK objects: docs/evidence/game_sdk_additional_objects.md. */
__osPiGetAccess = 0x10023720;
osPiRawReadIo = 0x100267A0;
__osPiRelAccess = 0x10023764;
__osSiDeviceBusy = 0x10027630;
osWritebackDCache = 0x10023D20;
osVirtualToPhysical = 0x100233C0;
osInvalDCache = 0x10022D10;
__osSiGetAccess = 0x10025750;
__osSiRelAccess = 0x10025794;
__osSiRawStartDma = 0x100257C0;
osRecvMesg = 0x10023440;
__osMaxControllers = 0x80042A51;
__osContLastCmd = 0x80042A50;
__osPfsRequestData = 0x10025170;
__osPfsGetInitData = 0x1002526C;
__osPfsGetStatus = 0x10027714;
__osContAddressCrc = 0x10025FD0;
__osContDataCrc = 0x10026080;

/* Rare EEPROM overrides reuse the game's status helper, PIF RAM, and
 * asynchronous transaction waiter. */
__osEepStatus = 0x151DD710;
__conker_game_eepPifRam = 0x800E0A30;
__conker_eeprom_wait = 0x151DCFD8;

/* Controller objects: docs/evidence/game_sdk_controller_objects.md. */
osGetTime = 0x10024F40;
osClockRate = 0x8002BD10;
__ll_mul = 0x10026968;
__ull_div = 0x10026868;
osCreateMesgQueue = 0x10023790;
osSetTimer = 0x10024A40;
__osPackRequestData = 0x10025608;
__osContGetInitData = 0x10025538;
__osSiCreateAccessQueue = 0x10025700;
osPfsChecker = 0x10028670;

/* The earlier rotation copy calls the game's own math helpers. */
__conker_game_sinf = 0x15047D60;
__conker_game_cosf = 0x15047C00;
__conker_game_guMtxIdentF = 0x150A7BC0;
__conker_game_guMtxF2L = 0x150A7790;
__osSiAccessQueueEnabled = 0x8002BE20;
__osSiAccessQueue = 0x80042AA8;
__conker_game_siAccessBuf = 0x800E0D20;
osSendMesg = 0x10023580;
__libm_qnan_f = 0x8002C920;

SECTIONS
{
    /* The initialized seed lives in the separately preserved RZIP game-data
     * payload at offset 0xEE50. All 16 bytes match random.o .data. NOLOAD binds
     * its section-relative relocations without adding data to the code image.
     */
    .sdk_random_data 0x80091970 (NOLOAD) :
    {
        build/game-libs/us/libultra_2_0I.a:random.o(.data);
    }
    ASSERT(SIZEOF(.sdk_random_data) == 0x10, "unexpected SDK random data size")

    /* Complete initialized rotation data, preserved in the RZIP data payload
     * at offset 0x162A0. See game_sdk_rotation_variant.md for byte evidence.
     */
    .sdk_rotate_data 0x80098DC0 (NOLOAD) :
    {
        build/game-libs/us/libultrare.a:rotate.o(.data);
    }
    ASSERT(SIZEOF(.sdk_rotate_data) == 0x10, "unexpected SDK rotation data size")

    /* Entire scalar and polynomial sections of the single-precision trig
     * variants; each is byte-verified in the preserved game-data payload.
     */
    .sdk_cosf_data 0x80085EA0 (NOLOAD) :
    {
        build/game-libs/us/libultrare.a:cosf.o(.data);
    }
    ASSERT(SIZEOF(.sdk_cosf_data) == 0x10, "unexpected cosine data size")
    .sdk_cosf_rodata 0x80098D70 (NOLOAD) :
    {
        build/game-libs/us/libultrare.a:cosf.o(.rodata);
    }
    ASSERT(SIZEOF(.sdk_cosf_rodata) == 0x20, "unexpected cosine rodata size")
    .sdk_sinf_data 0x80085EB0 (NOLOAD) :
    {
        build/game-libs/us/libultrare.a:sinf.o(.data);
    }
    ASSERT(SIZEOF(.sdk_sinf_data) == 0x10, "unexpected sine data size")
    .sdk_sinf_rodata 0x80098D90 (NOLOAD) :
    {
        build/game-libs/us/libultrare.a:sinf.o(.rodata);
    }
    ASSERT(SIZEOF(.sdk_sinf_rodata) == 0x20, "unexpected sine rodata size")
    .sdk_perspective_rodata 0x80098DB0 (NOLOAD) :
    {
        build/game-libs/us/libultrare.a:perspective.o(.rodata);
    }
    ASSERT(SIZEOF(.sdk_perspective_rodata) == 0x10, "unexpected perspective rodata size")

    /* The overlay shares the main executable's existing PIF RAM allocation.
     * Bind the entire original section without adding bytes to the code image.
     */
    .sdk_pfs_bss 0x800429D0 (NOLOAD) :
    {
        build/game-libs/us/libultrare.a:pfsisplug.o(.bss);
    }
    ASSERT(SIZEOF(.sdk_pfs_bss) == 0x40, "unexpected SDK PIF RAM size")

    /* Complete controller sections share the reviewed main allocations.
     * The initialized section is all zero in both object and retail ROM.
     */
    .sdk_controller_data 0x8002BE10 (NOLOAD) :
    {
        build/game-libs/us/libultrare.a:controller.o(.data);
    }
    ASSERT(SIZEOF(.sdk_controller_data) == 0x10, "unexpected SDK controller data size")
    .sdk_controller_bss 0x80042A10 (NOLOAD) :
    {
        build/game-libs/us/libultrare.a:controller.o(.bss);
    }
    ASSERT(SIZEOF(.sdk_controller_bss) == 0x90, "unexpected SDK controller BSS size")
}

/* Rare MP3 stream callbacks and external storage; see the MP3 evidence note. */
bcopy = 0x10023A10;
bzero = 0x100226F0;
strlen = 0x10022EEC;
__conker_mp3_stream = 0x800E1880;
__conker_mp3_state = 0x800E0E04;
__conker_mp3_text_callback = 0x800E0E00;

/* Decoder workspace remains external; utility calls use archive exports. */
__conker_mp3_huffman_base = 0x800E0E28;
__conker_mp3_sinf = 0x15047D60;
__conker_mp3_pow = 0x1504A400;
sine_block = 0x800E0E38;
var8009c644 = 0x800E0E30;
var8009c648 = 0x800E1078;
var8009c650 = 0x800E0E20;
var8009c6d8 = 0x800E1080;
var8009c6dc = 0x800E1480;

SECTIONS
{
    /* These complete emitted sections equal the separately compressed game
     * data payload; NOLOAD preserves the executable-only overlay image.
     */
    .sdk_mp3_decoder_data 0x80091990 (NOLOAD) :
    {
        build/game-libs/us/libultrare.a:decoder.o(.data);
    }
    ASSERT(SIZEOF(.sdk_mp3_decoder_data) == 0x90, "unexpected MP3 decoder data size")
    .sdk_mp3_decoder_rodata 0x800ABB20 (NOLOAD) :
    {
        build/game-libs/us/libultrare.a:decoder.o(.rodata);
    }
    ASSERT(SIZEOF(.sdk_mp3_decoder_rodata) == 0x5130, "unexpected MP3 decoder rodata size")
}

/* Complete Rare math constants match the separately compressed game data. */
SECTIONS
{
    .sdk_expf_rodata 0x800990A0 (NOLOAD) :
    {
        build/game-libs/us/libultrare.a:expf.o(.rodata);
    }
    ASSERT(SIZEOF(.sdk_expf_rodata) == 0x10, "unexpected exponential rodata size")
    .sdk_logf_rodata 0x800990B0 (NOLOAD) :
    {
        build/game-libs/us/libultrare.a:logf.o(.rodata);
    }
    ASSERT(SIZEOF(.sdk_logf_rodata) == 0x10, "unexpected logarithm rodata size")
}

/* Whole MP3 transform constants, including the following transform's table. */
SECTIONS
{
    .sdk_mp3_transform_rodata 0x800B0C50 (NOLOAD) :
    {
        build/game-libs/us/libultrare.a:lib_46650.o(.rodata);
    }
    ASSERT(SIZEOF(.sdk_mp3_transform_rodata) == 0x170, "unexpected MP3 transform rodata size")
}

/* MP3 playback storage and service dependencies; see playback evidence. */
g_Mp3Vars = 0x800e0d80;
__conker_mp3_alloc = 0x10003c40;
__conker_mp3_pin = 0x100043b4;
__conker_mp3_free = 0x10004074;
__conker_mp3_load_asset = 0x1502b5c8;
__conker_mp3_lookup_base = 0x800e0e24;
__conker_mp3_assets_loaded = 0x800e0e2c;
__conker_mp3_level = 0x800be9f0;
__conker_audio_headphone = 0x800428c2;
__conker_audio_mono = 0x800428c1;
n_eqpower = 0x8002bc10;
n_syn = 0x8002ba44;
_getRate = 0x10020e18;
_getVol = 0x10021028;
n_alFxInitlpfilter_mono = 0x1001cf38;
osSetIntMask = 0x10024880;
/* Preserve the existing raw-name reference from the asset/DMA setup caller. */
func_151F3C4C = mp3_handle_dma;
