#include <ultra64.h>

/* Conker US 0x12820:0x128D0: complete audio heap initialization/allocation. */
void alHeapInit(ALHeap *hp, u8 *base, s32 len)
{
	hp->base = base;
	hp->len = len;
	hp->cur = hp->base;
	hp->count = 0;
}

void *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size)
{
	s32 bytes;
	u8 *ptr = 0;

	bytes = (num * size + 0xf) & ~0xf;

	if (hp->cur + bytes <= hp->base + hp->len) {
		ptr = hp->cur;
		hp->cur += bytes;
	} else {

	}

	return ptr;
}
