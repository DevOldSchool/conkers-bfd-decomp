# US game_40490 angle and effect float constants

The unit's rodata is one first-use literal pool at 0x80096688..0x800966B3, owned by three functions in source order.
The checksum-validated US game-data archive (ROM SHA1 `4cbadd3c4e0729dec46af64ad018050eada4f47a`, game-data base
0x80082B20) holds exactly the single-precision values of the C literals listed below.

- `func_150144B8` converts two packet angles from degrees to radians and scales a packed byte. It loads `0.017453292f`
  (pi/180) and `0.7853982f` (pi/4) from 0x80096688 (`3C8EFA35 3F490FDB`). With extern symbols IDO allocates the
  function differently (CURRENT 207); the literals reproduce the raw function.
- `func_1501474C` rotates a rectangle by its packet angle. It loads `0.017453292f` twice, once for the sine and once
  for the cosine argument, from 0x80096690 and 0x80096694 (`3C8EFA35 3C8EFA35`). It matched with the extern symbols
  `D_80096690`/`D_80096694` and keeps CURRENT (0) with the literals.
- `func_15014B60` spawns a six-light effect with randomised angles. It loads `0.000015259022f` (1/65535) three
  times, `0.15258789f`, `0.001f` and `0.45776367f` with `0.000001f` from 0x80096698..0x800966B3 (`37800080 37800080
  3E1C4000 3A83126F 37800080 3EEA6000 358637BD`); IDO emits one word per use of the angle scale in the unrolled
  first-use order. The raw function had no C candidate; with these literals it is CURRENT (0). `360.0f` is built
  with `lui`.

The generated `game_40490.o` has 0x30 bytes of `.rodata`: the 0x2C-byte payload in load order followed by 4 zero
alignment bytes, with no data relocations. `config/game/us-rodata.ld` maps it as an INFO section at 0x80096688 with a
0x30 extent assertion and a 0x2C payload; `config/data/us.json` records the owner. The alignment bytes fall at
0x800966B4 (`C61C4000`, -10000.0f), which a later member of this unit still reads through the extern `D_800966B4`; they do not describe ROM contents
and only the payload is compared. The preceding words (`3A83126F`, `2F0BCDFE`) belong to other functions' pools and
stay outside this mapping. No reference assembly, compiler flag or verifier changes are involved.
