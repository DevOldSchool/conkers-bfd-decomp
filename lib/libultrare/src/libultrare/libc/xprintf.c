#include <PR/ultratypes.h>
#include "../../../../ultralib/include/compiler/ido/stdarg.h"

/* Conker US Rare formatter, 0x20D0:0x2DB0. Independent lineage: Perfect Dark
 * 169ed48bdcbfb3b568b028bd5bebb27680073514; MIT notice: src/rsp/LICENSE.
 * Owns complete text, data and rodata; see the formatter reconstruction note.
 */

/* Same SDK formatting descriptor used by xldtob and the linked _Litob. */
typedef struct {
    union { s64 ll; f64 ld; } v;
    u8 *s;
    s32 n0, nz0, n1, nz1, n2, nz2;
    s32 prec, width;
    u32 nchar, flags;
    u8 qual;
} ConkerPft;

u8 D_8002AAF0[33] = "                                ";
u8 D_8002AB14[33] = "00000000000000000000000000000000";
const u8 D_8002BF80[] = "hlL";
const u8 D_8002BF84[] = {' ', '+', '-', '#', '0', '\0'};
const u32 D_8002BF8C[] = {1, 2, 4, 8, 16, 0};
extern u8 *func_80022F14(const u8 *text, s32 code);
extern u32 func_80022EEC(const u8 *text);
extern void func_800230F0(ConkerPft *px, u8 code);
extern void func_80001550(ConkerPft *px, u8 code);
void _Putfld(ConkerPft *px, va_list *args, u8 type, u8 *buffer);

#define FLAGS_SPACE 1
#define FLAGS_PLUS 2
#define FLAGS_MINUS 4
#define FLAGS_HASH 8
#define FLAGS_ZERO 16
#define NULL ((void *)0)
#define spaces D_8002AAF0
#define zeroes D_8002AB14

#define ISDIGIT(x) ((x >= '0' && x <= '9'))

#define ATOI(dst, src)				   \
	for (dst = 0; ISDIGIT(*src); ++src)  \
	{									\
		if (dst < 999)				   \
			dst = dst * 10 + *src - '0'; \
	}

#define MAX_PAD ((sizeof(spaces) - 1))

#define PAD(s, n)											 \
	if (0 < (n))											  \
	{														 \
		int i, j = (n);									   \
		for (; 0 < j; j -= i)								 \
		{													 \
			i = MAX_PAD < (unsigned int)j ? (int)MAX_PAD : j; \
			PUT(s, i);										\
		}													 \
	}

#define PUT(s, n)								\
	if (0 < (n))								 \
	{											\
		if ((arg = (*prout)(arg, s, n)) != NULL) \
			x.nchar += (n);					   \
		else									 \
			return x.nchar;					   \
	}

s32 _Printf(void *(*prout)(void *, const u8 *, u32), void *arg, const u8 *fmt, va_list args)
{
	ConkerPft x;
	x.nchar = 0;

	while (1) {
        const u8 *s;
        u8 c;
        const u8 *t;
        u8 ac[32];
        /* Preserve the observed eight-byte unused stack reservation. */
        u32 unused_stack[2];

		s = fmt;

		for (c = *s++; c > 0; c = *s++) {
            if (c == '%') {
                s--;
                break;
            }
        }

		PUT(fmt, s - fmt);

		if (c == 0) {
			return x.nchar;
		}

		fmt = ++s;

		for (x.flags = 0; (t = func_80022F14(D_8002BF84, *s)) != NULL; s++) {
			x.flags |= D_8002BF8C[t - D_8002BF84];
		}

		if (*s == '*') {
			x.width = va_arg(args, int);

			if (x.width < 0) {
				x.width = -x.width;
				x.flags |= FLAGS_MINUS;
			}

			s++;
		} else {
			ATOI(x.width, s);
		}

		if (*s != '.') {
			x.prec = -1;
		} else if (*++s == '*') {
			x.prec = va_arg(args, int);
			++s;
		} else {
			ATOI(x.prec, s);
		}

		x.qual = func_80022F14(D_8002BF80, *s) ? *s++ : '\0';

		if (x.qual == 'l' && *s == 'l') {
			x.qual = 'L';
			++s;
		}

		_Putfld(&x, &args, *s, ac);

		x.width = x.width - x.n0 - x.nz0 - x.n1 - x.nz1 - x.n2 - x.nz2;

        {
        if (!(x.flags & FLAGS_MINUS)) {
            s32 i, j;
            if (x.width > 0) {
                j = x.width;
                for (; j > 0; j -= i) {
                    i = MAX_PAD < (u32)j ? (s32)MAX_PAD : j;
                    PUT(spaces, i);
                }
            }
        }

		PUT(ac, x.n0);
		PAD(zeroes, x.nz0);
		PUT(x.s, x.n1);
		PAD(zeroes, x.nz1);
		PUT(x.s + x.n1, x.n2);
		PAD(zeroes, x.nz2);

		if (x.flags & FLAGS_MINUS) {
			PAD(spaces, x.width);
		}

        }
		fmt = s + 1;
	}

	return 0;
}
void _Putfld(ConkerPft *x, va_list *args, u8 type, u8 *buff)
{
	x->n0 = x->nz0 = x->n1 = x->nz1 = x->n2 = x->nz2 = 0;

	switch (type) {
	case 'c':
		buff[x->n0++] = va_arg(*args, int);
		break;
	case 'd':
	case 'i':
		if (x->qual == 'l') {
			x->v.ll = va_arg(*args, int);
		} else if (x->qual == 'L') {
			x->v.ll = va_arg(*args, s64);
		} else {
			x->v.ll = va_arg(*args, int);
		}

		if (x->qual == 'h') {
			x->v.ll = (s16)x->v.ll;
		}

		if (x->v.ll < 0) {
			buff[x->n0++] = '-';
		} else if (x->flags & FLAGS_PLUS) {
			buff[x->n0++] = '+';
		} else if (x->flags & FLAGS_SPACE) {
			buff[x->n0++] = ' ';
		}

		x->s = (u8 *)&buff[x->n0];

		func_800230F0(x, type);
		break;
	case 'x':
	case 'X':
	case 'u':
	case 'o':
		if (x->qual == 'l') {
			x->v.ll = va_arg(*args, int);
		} else if (x->qual == 'L') {
			x->v.ll = va_arg(*args, s64);
		} else {
			x->v.ll = va_arg(*args, int);
		}

		if (x->qual == 'h') {
			x->v.ll = (u16)x->v.ll;
		} else if (x->qual == 0) {
			x->v.ll = (unsigned int)x->v.ll;
		}

		if (x->flags & FLAGS_HASH) {
			buff[x->n0++] = '0';

			if (type == 'x' || type == 'X') {
				buff[x->n0++] = type;
			}
		}

		x->s = (u8 *)&buff[x->n0];
		func_800230F0(x, type);
		break;
	case 'e':
	case 'f':
	case 'g':
	case 'E':
	case 'G':
		x->v.ld = x->qual == 'L' ? va_arg(*args, f64) : va_arg(*args, f64);

		if (*(u16 *)&x->v.ld & 0x8000) {
			buff[x->n0++] = '-';
		} else if (x->flags & FLAGS_PLUS) {
			buff[x->n0++] = '+';
		} else if (x->flags & FLAGS_SPACE) {
			buff[x->n0++] = ' ';
		}

		x->s = (u8 *)&buff[x->n0];
		func_80001550(x, type);
		break;
	case 'n':
		if (x->qual == 'h') {
			*(va_arg(*args, u16 *)) = x->nchar;
		} else if (x->qual == 'l') {
			*va_arg(*args, unsigned int *) = x->nchar;
		} else if (x->qual == 'L') {
			*va_arg(*args, u64 *) = x->nchar;
		} else {
			*va_arg(*args, unsigned int *) = x->nchar;
		}
		break;
	case 'p':
		x->v.ll = (long)va_arg(*args, void *);
		x->s = (u8 *)&buff[x->n0];
		func_800230F0(x, 'x');
		break;
	case 's':
		x->s = va_arg(*args, u8 *);
		x->n1 = func_80022EEC(x->s);

		if (x->prec >= 0 && x->n1 > x->prec) {
			x->n1 = x->prec;
		}
		break;
	case '%':
		buff[x->n0++] = '%';
		break;
	default:
		buff[x->n0++] = type;
		break;
	}
}
