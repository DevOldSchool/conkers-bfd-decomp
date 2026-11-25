#include "types.h"

/* Reconstructed resource metadata; no original C-object boundary is claimed.
 * Evidence: docs/evidence/data-layout/us_resource_descriptors.md
 */

/* Matches the consumer-local ResourceDescriptor in game_C9EC0.c. */
typedef struct ResourceDescriptor {
    const char *name;
    s32 packed_id;
    u16 field_8;
    u16 field_A;
    const u16 *dependencies;
    const u16 *related_dependencies;
} ResourceDescriptor;

extern const char D_8009E834[];
extern const char D_8009E84C[];
extern const char D_8009E860[];
extern const char D_8009E878[];
extern const char D_8009E890[];
extern const char D_8009E8AC[];
extern const char D_8009E8C8[];
extern const char D_8009E8EC[];
extern const char D_8009E900[];
extern const char D_8009E910[];
extern const char D_8009E928[];
extern const char D_8009E93C[];
extern const char D_8009E950[];
extern const char D_8009E960[];
extern const char D_8009E974[];
extern const char D_8009E98C[];
extern const char D_8009E9AC[];
extern const char D_8009E9B8[];
extern const char D_8009E9C8[];
extern const char D_8009E9D8[];
extern const char D_8009E9F4[];
extern const char D_8009EA04[];
extern const char D_8009EA20[];
extern const char D_8009EA30[];
extern const char D_8009EA44[];
extern const char D_8009EA54[];
extern const char D_8009EA68[];
extern const char D_8009EA7C[];
extern const char D_8009EA90[];
extern const char D_8009EAA8[];
extern const char D_8009EAB8[];
extern const char D_8009EAD0[];
extern const char D_8009EAE8[];
extern const char D_8009EB00[];
extern const char D_8009EB10[];
extern const char D_8009EB24[];
extern const char D_8009EB40[];
extern const char D_8009EB54[];
extern const char D_8009EB68[];
extern const char D_8009EB80[];
extern const char D_8009EB94[];
extern const char D_8009EBA8[];
extern const char D_8009EBBC[];
extern const char D_8009EBC8[];
extern const char D_8009EBDC[];
extern const char D_8009EBEC[];
extern const char D_8009EC04[];
extern const char D_8009EC14[];
extern const char D_8009EC28[];
extern const char D_8009EC34[];
extern const char D_8009EC4C[];
extern const char D_8009EC5C[];
extern const char D_8009EC70[];
extern const char D_8009EC7C[];
extern const char D_8009EC8C[];
extern const char D_8009ECA0[];
extern const char D_8009ECB0[];
extern const char D_8009ECC0[];
extern const char D_8009ECD4[];
extern const char D_8009ECE8[];
extern const char D_8009ECFC[];
extern const char D_8009ED0C[];
extern const char D_8009ED24[];
extern const char D_8009ED34[];
extern const char D_8009ED44[];
extern const char D_8009ED54[];
extern const char D_8009ED6C[];
extern const char D_8009ED80[];
extern const char D_8009ED98[];
extern const char D_8009EDA8[];
extern const char D_8009EDB4[];
extern const char D_8009EDC4[];
extern const char D_8009EDD8[];
extern const char D_8009EDE8[];
extern const char D_8009EE00[];
extern const char D_8009EE18[];
extern const char D_8009EE28[];
extern const char D_8009EE3C[];
extern const char D_8009EE54[];
extern const char D_8009EE64[];
extern const char D_8009EE78[];
extern const char D_8009EE88[];
extern const char D_8009EE9C[];
extern const char D_8009EEAC[];
extern const char D_8009EEB8[];
extern const char D_8009EECC[];
extern const char D_8009EEDC[];
extern const char D_8009EEEC[];
extern const char D_8009EF00[];
extern const char D_8009EF10[];
extern const char D_8009EF1C[];
extern const char D_8009EF30[];
extern const char D_8009EF40[];
extern const char D_8009EF50[];
extern const char D_8009EF5C[];
extern const char D_8009EF6C[];
extern const char D_8009EF78[];
extern const char D_8009EF94[];
extern const char D_8009EFA4[];
extern const char D_8009EFB0[];
extern const char D_8009EFC0[];
extern const char D_8009EFCC[];
extern const char D_8009EFD4[];
extern const char D_8009EFE4[];
extern const char D_8009EFF0[];
extern const char D_8009EFFC[];
extern const char D_8009F008[];
extern const char D_8009F018[];
extern const char D_8009F02C[];
extern const char D_8009F03C[];
extern const char D_8009F04C[];
extern const char D_8009F060[];
extern const char D_8009F074[];
extern const char D_8009F098[];
extern const char D_8009F0A4[];
extern const char D_8009F0B0[];
extern const u16 D_8009E470[];
extern const u16 D_8009E474[];
extern const u16 D_8009E478[];
extern const u16 D_8009E47C[];
extern const u16 D_8009E480[];
extern const u16 D_8009E484[];
extern const u16 D_8009E488[];
extern const u16 D_8009E48C[];
extern const u16 D_8009E490[];
extern const u16 D_8009E498[];
extern const u16 D_8009E49C[];
extern const u16 D_8009E4A8[];
extern const u16 D_8009E4AC[];
extern const u16 D_8009E4B4[];
extern const u16 D_8009E4BC[];
extern const u16 D_8009E4CC[];
extern const u16 D_8009E4D4[];
extern const u16 D_8009E4DC[];
extern const u16 D_8009E4E0[];
extern const u16 D_8009E4E4[];
extern const u16 D_8009E4E8[];
extern const u16 D_8009E4F0[];
extern const u16 D_8009E4F8[];
extern const u16 D_8009E4FC[];
extern const u16 D_8009E504[];
extern const u16 D_8009E508[];
extern const u16 D_8009E50C[];
extern const u16 D_8009E510[];
extern const u16 D_8009E514[];
extern const u16 D_8009E51C[];
extern const u16 D_8009E528[];
extern const u16 D_8009E52C[];
extern const u16 D_8009E530[];
extern const u16 D_8009E534[];
extern const u16 D_8009E540[];
extern const u16 D_8009E54C[];
extern const u16 D_8009E550[];
extern const u16 D_8009E560[];
extern const u16 D_8009E564[];
extern const u16 D_8009E568[];
extern const u16 D_8009E570[];
extern const u16 D_8009E574[];
extern const u16 D_8009E57C[];
extern const u16 D_8009E580[];
extern const u16 D_8009E584[];
extern const u16 D_8009E588[];
extern const u16 D_8009E58C[];
extern const u16 D_8009E598[];
extern const u16 D_8009E5A4[];
extern const u16 D_8009E5B0[];
extern const u16 D_8009E5B4[];
extern const u16 D_8009E5B8[];
extern const u16 D_8009E5C0[];
extern const u16 D_8009E5C4[];
extern const u16 D_8009E5C8[];
extern const u16 D_8009E5CC[];
extern const u16 D_8009E5D0[];
extern const u16 D_8009E5D4[];
extern const u16 D_8009E5D8[];
extern const u16 D_8009E5E0[];
extern const u16 D_8009E5E8[];
extern const u16 D_8009E5EC[];
extern const u16 D_8009E5F4[];
extern const u16 D_8009E5F8[];
extern const u16 D_8009E600[];
extern const u16 D_8009E608[];
extern const u16 D_8009E60C[];
extern const u16 D_8009E618[];
extern const u16 D_8009E61C[];
extern const u16 D_8009E620[];
extern const u16 D_8009E624[];
extern const u16 D_8009E628[];
extern const u16 D_8009E62C[];
extern const u16 D_8009E630[];
extern const u16 D_8009E634[];
extern const u16 D_8009E638[];
extern const u16 D_8009E63C[];
extern const u16 D_8009E640[];
extern const u16 D_8009E648[];
extern const u16 D_8009E650[];
extern const u16 D_8009E658[];
extern const u16 D_8009E660[];
extern const u16 D_8009E664[];
extern const u16 D_8009E668[];
extern const u16 D_8009E674[];
extern const u16 D_8009E67C[];
extern const u16 D_8009E684[];
extern const u16 D_8009E688[];
extern const u16 D_8009E68C[];
extern const u16 D_8009E690[];
extern const u16 D_8009E694[];
extern const u16 D_8009E698[];
extern const u16 D_8009E69C[];
extern const u16 D_8009E6A0[];
extern const u16 D_8009E6A8[];
extern const u16 D_8009E6AC[];
extern const u16 D_8009E6B0[];
extern const u16 D_8009E6B4[];
extern const u16 D_8009E6BC[];
extern const u16 D_8009E6C0[];
extern const u16 D_8009E6C4[];
extern const u16 D_8009E6C8[];
extern const u16 D_8009E6CC[];
extern const u16 D_8009E6D0[];
extern const u16 D_8009E6D4[];
extern const u16 D_8009E6D8[];
extern const u16 D_8009E6DC[];
extern const u16 D_8009E6E0[];
extern const u16 D_8009E6E4[];
extern const u16 D_8009E6EC[];
extern const u16 D_8009E6F0[];
extern const u16 D_8009E6F4[];
extern const u16 D_8009E6F8[];
extern const u16 D_8009E700[];
extern const u16 D_8009E704[];
extern const u16 D_8009E708[];
extern const u16 D_8009E70C[];
extern const u16 D_8009E710[];
extern const u16 D_8009E714[];
extern const u16 D_8009E720[];
extern const u16 D_8009E728[];
extern const u16 D_8009E72C[];
extern const u16 D_8009E734[];
extern const u16 D_8009E738[];
extern const u16 D_8009E73C[];
extern const u16 D_8009E740[];
extern const u16 D_8009E744[];
extern const u16 D_8009E748[];
extern const u16 D_8009E74C[];
extern const u16 D_8009E754[];
extern const u16 D_8009E758[];
extern const u16 D_8009E75C[];
extern const u16 D_8009E760[];
extern const u16 D_8009E764[];
extern const u16 D_8009E768[];
extern const u16 D_8009E76C[];
extern const u16 D_8009E770[];
extern const u16 D_8009E774[];
extern const u16 D_8009E778[];
extern const u16 D_8009E77C[];
extern const u16 D_8009E780[];
extern const u16 D_8009E784[];
extern const u16 D_8009E788[];
extern const u16 D_8009E78C[];
extern const u16 D_8009E790[];
extern const u16 D_8009E794[];
extern const u16 D_8009E798[];
extern const u16 D_8009E79C[];
extern const u16 D_8009E7A0[];
extern const u16 D_8009E7A4[];
extern const u16 D_8009E7A8[];
extern const u16 D_8009E7AC[];
extern const u16 D_8009E7B4[];
extern const u16 D_8009E7B8[];
extern const u16 D_8009E7BC[];
extern const u16 D_8009E7C0[];
extern const u16 D_8009E7C4[];
extern const u16 D_8009E7C8[];
extern const u16 D_8009E7CC[];
extern const u16 D_8009E7D0[];
extern const u16 D_8009E7D4[];
extern const u16 D_8009E7DC[];
extern const u16 D_8009E7E0[];
extern const u16 D_8009E7E4[];
extern const u16 D_8009E7E8[];
extern const u16 D_8009E7EC[];
extern const u16 D_8009E7F0[];
extern const u16 D_8009E7F4[];
extern const u16 D_8009E7F8[];
extern const u16 D_8009E7FC[];
extern const u16 D_8009E800[];
extern const u16 D_8009E804[];
extern const u16 D_8009E808[];
extern const u16 D_8009E810[];
extern const u16 D_8009E818[];
extern const u16 D_8009E820[];
extern const u16 D_8009E824[];
extern const u16 D_8009E82C[];
extern const u16 D_8009E830[];

ResourceDescriptor D_80087430[204] = {
    { D_8009E834, (s32)0xA0000002, 0x0029, 0xD000, D_8009E474, D_8009E470 },
    { 0, (s32)0x60000000, 0x0029, 0xD000, D_8009E480, D_8009E470 },
    { 0, (s32)0x60000000, 0x0029, 0xD000, D_8009E484, D_8009E470 },
    { 0, (s32)0x60000000, 0x0029, 0xD000, D_8009E488, D_8009E470 },
    { D_8009E84C, (s32)0x20000003, 0x0029, 0xD000, D_8009E478, D_8009E47C },
    { D_8009E860, (s32)0x20000004, 0x0029, 0xD000, D_8009E48C, D_8009E490 },
    { D_8009E878, (s32)0x20000005, 0x0029, 0xD006, D_8009E498, D_8009E49C },
    { 0, (s32)0x60000000, 0x0029, 0xD006, D_8009E4A8, D_8009E470 },
    { 0, (s32)0x60000000, 0x0029, 0xD000, D_8009E470, D_8009E470 },
    { D_8009E890, (s32)0x20000006, 0x0029, 0xD000, D_8009E470, D_8009E470 },
    { D_8009E8AC, (s32)0xA0000007, 0x0006, 0xD000, D_8009E4AC, D_8009E470 },
    { D_8009E8C8, (s32)0x20000008, 0x0006, 0xD000, D_8009E4B4, D_8009E4BC },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E4DC, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E4CC, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E4D4, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E4E0, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E4E4, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E470, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E4E8, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E470, D_8009E470 },
    { D_8009E8EC, (s32)0xA0000009, 0x0006, 0xD00B, D_8009E470, D_8009E4F0 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E4F8, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD00B, D_8009E4FC, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD006, D_8009E504, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E508, D_8009E470 },
    { D_8009E900, (s32)0x0000000A, 0x0006, 0xD000, D_8009E470, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E50C, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E510, D_8009E470 },
    { D_8009E910, (s32)0x20000010, 0x0006, 0xD006, D_8009E514, D_8009E51C },
    { 0, (s32)0x60000000, 0x0006, 0xD006, D_8009E528, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E52C, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E570, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E570, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E574, D_8009E470 },
    { D_8009E928, (s32)0xA000002F, 0x0019, 0x0000, D_8009E57C, D_8009E470 },
    { D_8009E93C, (s32)0xA000000B, 0x0006, 0xD000, D_8009E470, D_8009E5A4 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E580, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E584, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E588, D_8009E470 },
    { D_8009E950, (s32)0x2000000C, 0x0006, 0xD000, D_8009E58C, D_8009E598 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E470, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD000, D_8009E470, D_8009E470 },
    { D_8009E960, (s32)0x2000005D, 0x003B, 0xD002, D_8009E530, D_8009E470 },
    { D_8009E974, (s32)0xA0000043, 0x0027, 0x0000, D_8009E534, D_8009E540 },
    { D_8009E98C, (s32)0x20000044, 0x0027, 0x0000, D_8009E54C, D_8009E470 },
    { D_8009E9AC, (s32)0xA0000015, 0x000C, 0xD000, D_8009E5E0, D_8009E5E8 },
    { 0, (s32)0x60000000, 0x000C, 0xD000, D_8009E5B0, D_8009E470 },
    { 0, (s32)0x60000000, 0x000C, 0xD000, D_8009E470, D_8009E470 },
    { 0, (s32)0x60000000, 0x000C, 0xD000, D_8009E5B4, D_8009E470 },
    { 0, (s32)0x60000000, 0x000C, 0xD000, D_8009E470, D_8009E470 },
    { 0, (s32)0x60000000, 0x000C, 0xD000, D_8009E470, D_8009E470 },
    { 0, (s32)0x60000000, 0x000C, 0xD000, D_8009E5B8, D_8009E470 },
    { 0, (s32)0x60000000, 0x000C, 0xD000, D_8009E470, D_8009E470 },
    { 0, (s32)0x60000000, 0x000C, 0xD000, D_8009E5C0, D_8009E470 },
    { D_8009E9B8, (s32)0x20000017, 0x000C, 0xD000, D_8009E5C4, D_8009E470 },
    { D_8009E9C8, (s32)0x20000018, 0x000C, 0xD000, D_8009E5C8, D_8009E5CC },
    { D_8009E9D8, (s32)0x20000019, 0x000C, 0xD000, D_8009E5D0, D_8009E470 },
    { 0, (s32)0x60000000, 0x000C, 0xD000, D_8009E470, D_8009E470 },
    { 0, (s32)0x60000000, 0x000C, 0xD005, D_8009E5D4, D_8009E470 },
    { D_8009E9F4, (s32)0xA0000016, 0x000C, 0xD005, D_8009E5D8, D_8009E470 },
    { D_8009EA04, (s32)0xA000001A, 0x0001, 0xD000, D_8009E5EC, D_8009E470 },
    { D_8009EA20, (s32)0x2000001B, 0x0001, 0xD001, D_8009E5F8, D_8009E470 },
    { 0, (s32)0x60000000, 0x0001, 0xD001, D_8009E600, D_8009E470 },
    { D_8009EA30, (s32)0x2000001C, 0x0001, 0xD001, D_8009E608, D_8009E470 },
    { 0, (s32)0x60000000, 0x0001, 0xD000, D_8009E5F4, D_8009E470 },
    { D_8009EA44, (s32)0x2000001D, 0x0001, 0xD000, D_8009E60C, D_8009E470 },
    { D_8009EA54, (s32)0x20000020, 0x0001, 0xD002, D_8009E620, D_8009E470 },
    { D_8009EA68, (s32)0x2000001E, 0x0010, 0xD000, D_8009E618, D_8009E470 },
    { D_8009EA7C, (s32)0x2000001F, 0x0010, 0xD000, D_8009E61C, D_8009E470 },
    { D_8009EA90, (s32)0xA0000021, 0x0007, 0xD000, D_8009E668, D_8009E470 },
    { D_8009EAA8, (s32)0x20000025, 0x0007, 0xD001, D_8009E658, D_8009E660 },
    { 0, (s32)0x60000000, 0x0007, 0xD001, D_8009E664, D_8009E470 },
    { D_8009EAB8, (s32)0x2000002E, 0x0007, 0xD002, D_8009E674, D_8009E67C },
    { 0, (s32)0x60000000, 0x0007, 0xD002, D_8009E684, D_8009E688 },
    { 0, (s32)0x60000000, 0x0007, 0xD000, D_8009E470, D_8009E68C },
    { D_8009EAD0, (s32)0x20000026, 0x0012, 0xD000, D_8009E624, D_8009E470 },
    { D_8009EAE8, (s32)0x20000027, 0x0012, 0xD000, D_8009E628, D_8009E470 },
    { D_8009EB00, (s32)0x20000028, 0x0012, 0xD000, D_8009E62C, D_8009E470 },
    { 0, (s32)0x60000000, 0x0012, 0xD000, D_8009E630, D_8009E470 },
    { D_8009EB10, (s32)0x2000002D, 0x0012, 0xD002, D_8009E638, D_8009E470 },
    { D_8009EB24, (s32)0x20000029, 0x0017, 0xD000, D_8009E634, D_8009E470 },
    { D_8009EB40, (s32)0x20000023, 0x000B, 0xD000, D_8009E640, D_8009E470 },
    { 0, (s32)0x60000000, 0x000B, 0xD000, D_8009E650, D_8009E470 },
    { D_8009EB54, (s32)0x20000024, 0x000B, 0xD000, D_8009E470, D_8009E648 },
    { 0, (s32)0x60000000, 0x000B, 0xD000, D_8009E470, D_8009E470 },
    { D_8009EB68, (s32)0x20000022, 0x000B, 0xD000, D_8009E63C, D_8009E470 },
    { 0, (s32)0x60000000, 0x000B, 0xD000, D_8009E470, D_8009E470 },
    { D_8009EB80, (s32)0x20000030, 0x0002, 0xD000, D_8009E690, D_8009E470 },
    { 0, (s32)0x60000000, 0x0002, 0xD000, D_8009E694, D_8009E470 },
    { D_8009EB94, (s32)0x20000033, 0x0002, 0xD005, D_8009E698, D_8009E470 },
    { 0, (s32)0x60000000, 0x0002, 0xD005, D_8009E698, D_8009E470 },
    { 0, (s32)0x60000000, 0x0002, 0xD000, D_8009E6AC, D_8009E470 },
    { 0, (s32)0x60000000, 0x0002, 0xD000, D_8009E6B0, D_8009E470 },
    { 0, (s32)0x60000000, 0x0002, 0xD000, D_8009E69C, D_8009E470 },
    { D_8009EBA8, (s32)0x20000034, 0x0002, 0xD007, D_8009E6A0, D_8009E470 },
    { 0, (s32)0x60000000, 0x0002, 0xD000, D_8009E6A0, D_8009E470 },
    { D_8009EBBC, (s32)0x20000036, 0x0002, 0xD002, D_8009E6A8, D_8009E470 },
    { 0, (s32)0x60000000, 0x0002, 0xD003, D_8009E6C8, D_8009E470 },
    { D_8009EBC8, (s32)0x2000003C, 0x0002, 0xD006, D_8009E6CC, D_8009E470 },
    { 0, (s32)0x60000000, 0x0002, 0xD004, D_8009E470, D_8009E470 },
    { 0, (s32)0x60000000, 0x0002, 0xD004, D_8009E6D0, D_8009E470 },
    { 0, (s32)0x60000000, 0x0042, 0x0000, D_8009E470, D_8009E470 },
    { D_8009EBDC, (s32)0x20000031, 0x0043, 0xD001, D_8009E6EC, D_8009E470 },
    { D_8009EBEC, (s32)0x20000032, 0x0043, 0xD001, D_8009E6F0, D_8009E470 },
    { D_8009EC04, (s32)0x20000035, 0x0043, 0xD000, D_8009E6F4, D_8009E470 },
    { D_8009EC14, (s32)0x2000003D, 0x0043, 0xD000, D_8009E6F8, D_8009E470 },
    { 0, (s32)0x60000000, 0x0044, 0x0000, D_8009E470, D_8009E470 },
    { D_8009EC28, (s32)0x20000038, 0x0031, 0xD000, D_8009E6B4, D_8009E470 },
    { D_8009EC34, (s32)0x20000037, 0x0031, 0xD000, D_8009E6B4, D_8009E470 },
    { 0, (s32)0x60000000, 0x0031, 0xD000, D_8009E470, D_8009E470 },
    { D_8009EC4C, (s32)0x20000039, 0x0031, 0xD000, D_8009E6BC, D_8009E470 },
    { 0, (s32)0x60000000, 0x0031, 0xD000, D_8009E6C0, D_8009E470 },
    { D_8009EC5C, (s32)0x2000003A, 0x0031, 0xD000, D_8009E6C4, D_8009E470 },
    { D_8009EC70, (s32)0xA0000040, 0x0014, 0xD000, D_8009E708, D_8009E470 },
    { D_8009EC7C, (s32)0x20000041, 0x0014, 0xD000, D_8009E70C, D_8009E470 },
    { D_8009EC8C, (s32)0x20000042, 0x0014, 0xD000, D_8009E710, D_8009E470 },
    { 0, (s32)0x60000000, 0x0037, 0xD002, D_8009E710, D_8009E470 },
    { D_8009ECA0, (s32)0x8000000D, 0x002C, 0xD000, D_8009E714, D_8009E720 },
    { 0, (s32)0x40000000, 0x002C, 0xD000, D_8009E728, D_8009E470 },
    { 0, (s32)0x60000000, 0x002C, 0xD001, D_8009E470, D_8009E470 },
    { D_8009ECB0, (s32)0x2000000F, 0x002C, 0xD001, D_8009E72C, D_8009E470 },
    { 0, (s32)0x60000000, 0x002C, 0xD001, D_8009E470, D_8009E470 },
    { D_8009ECC0, (s32)0xA0000011, 0x0035, 0xD000, D_8009E550, D_8009E470 },
    { D_8009ECD4, (s32)0x20000012, 0x0035, 0xD000, D_8009E560, D_8009E470 },
    { D_8009ECE8, (s32)0x20000013, 0x0035, 0xD000, D_8009E564, D_8009E470 },
    { 0, (s32)0x60000000, 0x0035, 0xD000, D_8009E470, D_8009E470 },
    { D_8009ECFC, (s32)0xA0000014, 0x0037, 0xD004, D_8009E568, D_8009E470 },
    { 0, (s32)0x60000000, 0x0019, 0x0000, D_8009E470, D_8009E470 },
    { 0, (s32)0x60000000, 0x0019, 0x0000, D_8009E470, D_8009E470 },
    { 0, (s32)0x60000000, 0x0019, 0x0000, D_8009E470, D_8009E470 },
    { D_8009ED0C, (s32)0xA000003E, 0x0032, 0x0000, D_8009E700, D_8009E470 },
    { D_8009ED24, (s32)0x2000003F, 0x0032, 0x0000, D_8009E704, D_8009E470 },
    { D_8009ED34, (s32)0x0000000E, 0x0000, 0xD000, D_8009E734, D_8009E470 },
    { 0, (s32)0x40000000, 0x0000, 0xD000, D_8009E734, D_8009E738 },
    { D_8009ED44, (s32)0x2000002A, 0x000A, 0xD000, D_8009E73C, D_8009E470 },
    { D_8009ED54, (s32)0x2000002B, 0x000A, 0xD000, D_8009E740, D_8009E470 },
    { D_8009ED6C, (s32)0x2000002C, 0x000A, 0xD004, D_8009E744, D_8009E470 },
    { 0, (s32)0x60000000, 0x000A, 0xD004, D_8009E748, D_8009E470 },
    { D_8009ED80, (s32)0x2000004C, 0x0004, 0xD000, D_8009E74C, D_8009E470 },
    { 0, (s32)0x60000000, 0x0004, 0xD001, D_8009E754, D_8009E470 },
    { 0, (s32)0x60000000, 0x0023, 0xD002, D_8009E758, D_8009E470 },
    { D_8009ED98, (s32)0x2000005C, 0x0004, 0x0000, D_8009E75C, D_8009E470 },
    { D_8009EDA8, (s32)0x2000004D, 0x001B, 0xD000, D_8009E760, D_8009E470 },
    { 0, (s32)0x60000000, 0x001B, 0xD004, D_8009E764, D_8009E470 },
    { D_8009EDB4, (s32)0x2000004E, 0x001E, 0xD000, D_8009E768, D_8009E470 },
    { D_8009EDC4, (s32)0x20000050, 0x0026, 0xD000, D_8009E76C, D_8009E470 },
    { D_8009EDD8, (s32)0x20000051, 0x0026, 0xD000, D_8009E770, D_8009E470 },
    { D_8009EDE8, (s32)0x20000052, 0x001C, 0xD000, D_8009E790, D_8009E470 },
    { D_8009EE00, (s32)0x20000053, 0x001C, 0xD000, D_8009E794, D_8009E470 },
    { 0, (s32)0x60000000, 0x001C, 0xD000, D_8009E798, D_8009E470 },
    { D_8009EE18, (s32)0x20000054, 0x001C, 0xD002, D_8009E79C, D_8009E7A0 },
    { D_8009EE28, (s32)0x20000055, 0x001C, 0xD002, D_8009E7A4, D_8009E7A8 },
    { 0, (s32)0x60000000, 0x000E, 0xD000, D_8009E7AC, D_8009E7B4 },
    { 0, (s32)0x60000000, 0x000E, 0xD000, D_8009E7B8, D_8009E470 },
    { D_8009EE3C, (s32)0x20000056, 0x000E, 0xD000, D_8009E7BC, D_8009E470 },
    { D_8009EE54, (s32)0x20000058, 0x000E, 0xD000, D_8009E7C0, D_8009E470 },
    { D_8009EE64, (s32)0x20000057, 0x0028, 0x0000, D_8009E7C4, D_8009E470 },
    { 0, (s32)0x60000000, 0x0028, 0x0000, D_8009E7C8, D_8009E470 },
    { D_8009EE78, (s32)0xA000004A, 0x0013, 0x0000, D_8009E774, D_8009E778 },
    { D_8009EE88, (s32)0x2000004B, 0x0013, 0x0000, D_8009E774, D_8009E77C },
    { 0, (s32)0x60000000, 0x0013, 0x0000, D_8009E780, D_8009E470 },
    { D_8009EE9C, (s32)0x20000059, 0x0023, 0x0000, D_8009E784, D_8009E470 },
    { D_8009EEAC, (s32)0x2000005A, 0x0023, 0x0000, D_8009E788, D_8009E470 },
    { D_8009EEB8, (s32)0x2000005B, 0x0023, 0xD002, D_8009E78C, D_8009E470 },
    { D_8009EECC, (s32)0x2000004F, 0x002F, 0xD000, D_8009E7CC, D_8009E470 },
    { 0, (s32)0x60000000, 0x002F, 0xD000, D_8009E7D0, D_8009E470 },
    { D_8009EEDC, (s32)0xA0000045, 0x0041, 0x0000, D_8009E7D4, D_8009E470 },
    { D_8009EEEC, (s32)0x20000046, 0x0041, 0xD004, D_8009E7DC, D_8009E470 },
    { 0, (s32)0x60000000, 0x003D, 0x0000, D_8009E7E0, D_8009E470 },
    { D_8009EF00, (s32)0x20000047, 0x003C, 0xD005, D_8009E7E0, D_8009E470 },
    { 0, (s32)0x60000000, 0x003C, 0xD005, D_8009E7E4, D_8009E470 },
    { D_8009EF10, (s32)0x20000048, 0x003C, 0x0000, D_8009E7E8, D_8009E470 },
    { 0, (s32)0x60000000, 0x003C, 0x0000, D_8009E7E8, D_8009E470 },
    { D_8009EF1C, (s32)0x20000049, 0x003C, 0x0000, D_8009E7EC, D_8009E470 },
    { 0, (s32)0x60000000, 0x0041, 0x0000, D_8009E7F0, D_8009E470 },
    { D_8009EF30, (s32)0xA000005E, 0x0039, 0xD001, D_8009E7F4, D_8009E470 },
    { 0, (s32)0x60000000, 0x0039, 0xD001, D_8009E7F8, D_8009E470 },
    { D_8009EF40, (s32)0x2000005F, 0x0036, 0x0000, D_8009E7FC, D_8009E470 },
    { D_8009EF50, (s32)0x20000060, 0x003A, 0x0000, D_8009E800, D_8009E470 },
    { D_8009EF5C, (s32)0x2000003B, 0x0038, 0x0000, D_8009E6D4, D_8009E470 },
    { D_8009EF6C, (s32)0x20000061, 0x0040, 0x0000, D_8009E6D8, D_8009E470 },
    { D_8009EF78, (s32)0x20000062, 0x0040, 0xD003, D_8009E6DC, D_8009E470 },
    { D_8009EF94, (s32)0x20000063, 0x0040, 0xD001, D_8009E6E0, D_8009E470 },
    { D_8009EFA4, (s32)0xA0000065, 0x001A, 0x0000, D_8009E470, D_8009E470 },
    { D_8009EFB0, (s32)0x20000066, 0x0024, 0x0000, D_8009E470, D_8009E470 },
    { D_8009EFC0, (s32)0x20000067, 0x002B, 0x0000, D_8009E470, D_8009E470 },
    { D_8009EFCC, (s32)0x20000068, 0x002D, 0x0000, D_8009E470, D_8009E470 },
    { D_8009EFD4, (s32)0x20000069, 0x0030, 0x0000, D_8009E470, D_8009E470 },
    { D_8009EFE4, (s32)0x2000006A, 0x0033, 0x0000, D_8009E470, D_8009E470 },
    { D_8009EFF0, (s32)0x2000006B, 0x0034, 0x0000, D_8009E470, D_8009E470 },
    { D_8009EFFC, (s32)0x2000006C, 0x003F, 0x0000, D_8009E470, D_8009E470 },
    { D_8009F008, (s32)0x20000001, 0x0018, 0x0000, D_8009E470, D_8009E470 },
    { D_8009F018, (s32)0x2000006E, 0x0029, 0x0009, D_8009E808, D_8009E470 },
    { D_8009F02C, (s32)0x2000006F, 0x0006, 0xD000, D_8009E810, D_8009E470 },
    { D_8009F03C, (s32)0x20000070, 0x0006, 0xD000, D_8009E818, D_8009E470 },
    { D_8009F04C, (s32)0xA000006D, 0x0039, 0x0000, D_8009E804, D_8009E470 },
    { D_8009F060, (s32)0x20000071, 0x0035, 0x0000, D_8009E820, D_8009E470 },
    { 0, (s32)0x60000000, 0x0006, 0xD01A, D_8009E824, D_8009E470 },
    { 0, (s32)0x60000000, 0x0039, 0xD001, D_8009E82C, D_8009E470 },
    { D_8009F074, (s32)0x20000064, 0x0040, 0x0000, D_8009E6E4, D_8009E470 },
    { 0, (s32)0x60000000, 0x001D, 0x0000, D_8009E470, D_8009E470 },
    { D_8009F098, (s32)0xA0000000, 0x0021, 0x0000, D_8009E470, D_8009E470 },
    { D_8009F0A4, (s32)0x20000072, 0x0022, 0x0000, D_8009E470, D_8009E470 },
    { D_8009F0B0, (s32)0x20000073, 0x0018, 0x0000, D_8009E830, D_8009E470 },
};
