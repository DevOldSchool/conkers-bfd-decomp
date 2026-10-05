#include "types.h"
#include <../lib/ultralib/include/compiler/ido/stdarg.h>

/*
 * Provisional debugger C collection: memory, string, and formatting helpers.
 * US virtual range: 0x16001AD0..0x16003650 (exclusive end).
 * Evidence: docs/evidence/us_debugger_overlay.md
 *
 * Original source-object ownership remains unreviewed; this collection is
 * not registered as a source unit. Individual full-span C matches are tracked
 * independently. Preserve function order and the canonical GLOBAL_ASM bodies
 * for deferred candidates until their full registered spans match.
 * Loaded data and the privileged TLB capture routine remain separate raw ASM.
 */

/* Keep address symbols for linking and registered match evidence. */
#define debugger_copy_bytes func_16001AD0
#define debugger_string_length func_16001B00
#define debugger_sprintf func_16001B34
#define debugger_append_bytes func_16001B8C
#define debugger_vformat_to_callback func_16001BB4
#define debugger_format_field func_160021FC
#define debugger_format_f64 func_1600288C
#define debugger_unscale_f64 func_16002D2C
#define debugger_format_decimal_digits func_16002DE4
#define debugger_format_integer_digits func_160033A8

void *debugger_copy_bytes(void *dst, const void *src, u32 count) {
    u8 *out = dst;
    const u8 *in = src;

    while (count > 0) {
        *out = *in;
        out++;
        in++;
        count--;
    }
    return dst;
}
s32 debugger_string_length(const u8 *text) {
    const u8 *cursor = text;
    s32 length = 0;

    while (*cursor != 0) {
        length++;
        cursor++;
    }
    return length;
}
void *debugger_append_bytes(void *dst, const u8 *src, u32 count);
s32 debugger_vformat_to_callback(void *(*output)(void *, const u8 *, u32), void *arg,
                 const u8 *format, va_list args);

s32 debugger_sprintf(u8 *dst, const u8 *format, ...) {
    va_list args;
    s32 length;

    va_start(args, format);
    length = debugger_vformat_to_callback(debugger_append_bytes, dst, format, args);
    va_end(args);
    if (length >= 0) {
        dst[length] = 0;
    }
    return length;
}
void *debugger_copy_bytes(void *dst, const void *src, u32 count);

void *debugger_append_bytes(void *dst, const u8 *src, u32 count) {
    return (u8 *)debugger_copy_bytes(dst, src, count) + count;
}
/* SDK formatting descriptor shared by the debugger formatting helpers. */
typedef struct {
    union { s64 ll; f64 ld; } v;
    u8 *s;
    s32 n0, nz0, n1, nz1, n2, nz2;
    s32 prec, width;
    u32 nchar, flags;
    u8 qual;
} ConkerPft;

extern u8 D_16003C70[33];
extern u8 D_16003C94[33];
extern const u8 D_16004800[4];
extern const u8 D_16004804[6];
extern const u32 D_1600480C[6];
u8 *func_10022F14(const u8 *text, s32 code);
void debugger_format_field(ConkerPft *px, va_list *args, u8 type, u8 *buffer);

#define FLAGS_SPACE 1
#define FLAGS_PLUS 2
#define FLAGS_MINUS 4
#define FLAGS_HASH 8
#define FLAGS_ZERO 16
#define NULL ((void *)0)
#define spaces D_16003C70
#define zeroes D_16003C94

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

s32 debugger_vformat_to_callback(void *(*prout)(void *, const u8 *, u32), void *arg, const u8 *fmt, va_list args)
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

		for (x.flags = 0; (t = func_10022F14(D_16004804, *s)) != NULL; s++) {
			x.flags |= D_1600480C[t - D_16004804];
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

		x.qual = func_10022F14(D_16004800, *s) ? *s++ : '\0';

		if (x.qual == 'l' && *s == 'l') {
			x.qual = 'L';
			++s;
		}

		debugger_format_field(&x, &args, *s, ac);

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

void debugger_format_integer_digits(ConkerPft *px, u8 code);
void debugger_format_f64(ConkerPft *args, u8 type);

void debugger_format_field(ConkerPft *x, va_list *args, u8 type, u8 *buff)
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

		debugger_format_integer_digits(x, type);
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
		debugger_format_integer_digits(x, type);
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
		debugger_format_f64(x, type);
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
		debugger_format_integer_digits(x, 'x');
		break;
	case 's':
		x->s = va_arg(*args, u8 *);
		x->n1 = debugger_string_length(x->s);

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
typedef struct { s32 quot, rem; } ConkerLdiv;
ConkerLdiv func_10023060(s32 numerator, s32 denominator);
extern const f64 D_16004828[9];
extern const u8 D_16004870[4];
extern const u8 D_16004874[4];
extern const f64 D_16004950;
s16 debugger_unscale_f64(s16 *exponent, f64 *value);
void debugger_format_decimal_digits(ConkerPft *px, u8 code, u8 *digits, s16 count, s16 exponent);

void debugger_format_f64(ConkerPft *args, u8 type)
{
	u8 buff[0x20];
	u8 *p = buff;
	f64 ldval = args->v.ld;
	f64 zero64;
	f32 zero = 0.0f;
	f32 one32;
	/* Preserve the observed gap between the floating temporaries and shorts. */
	u32 unused_stack;
	s16 err;
	s16 nsig;
	s16 exp;

	zero64 = zero;

	if (args->prec < 0) {
		args->prec = 6;
	} else if (args->prec == 0 && (type == 'g' || type == 'G')) {
		args->prec = 1;
	}

	err = debugger_unscale_f64(&exp, &args->v.ld);

	if (err > 0) {
		debugger_copy_bytes(args->s, err == 2 ? D_16004870 : D_16004874, args->n1 = 3);
		return;
	}

	if (err == 0) {
		nsig = 0;
		exp = 0;
	} else {
		s32 i;
		s32 n;

		if (ldval < zero64) {
			ldval = -ldval;
		}

		exp = exp * 30103 / 0x000186a0 - 4;

		if (exp < 0) {
			n = (3 - exp) & ~3;
			exp = -n;

			for (i = 0; n > 0; n >>= 1, i++) {
				if ((n & 1) != 0) {
					ldval *= D_16004828[i];
				}
			}
		} else if (exp > 0) {
			f64 factor;
			one32 = 1.0f;
			factor = one32;
			exp &= ~3;

			for (n = exp, i = 0; n > 0; n >>= 1, i++) {
				if (n & 1) {
					factor *= D_16004828[i];
				}
			}

			ldval /= factor;
		}

		{
			s32 gen = ((type == 'f') ? exp + 10 : 6) + args->prec;

			if (gen > 0x13) {
				gen = 0x13;
			}

			*p++ = '0';

			for (; gen > 0 && zero64 < ldval; p += 8) {
				s32 j;
				s32 lo = ldval;

				if ((gen -= 8) > 0) {
					ldval = (ldval - lo) * D_16004950;
				}

				p += 8;

				for (j = 8; lo > 0 && --j >= 0;) {
					ConkerLdiv qr;

					qr = func_10023060(lo, 10);
					*--p = qr.rem + '0';
					lo = qr.quot;
				}

				while (--j >= 0) {
					p--;
					*p = '0';
				}

			}

			gen = p - &buff[1];

			for (p = &buff[1], exp += 7; *p == '0'; p++) {
				--gen;
				--exp;
			}

			nsig = ((type == 'f') ? exp + 1 : ((type == 'e' || type == 'E') ? 1 : 0)) + args->prec;

			if (gen < nsig) {
				nsig = gen;
			}

			if (nsig > 0) {
				u8 drop;
				s32 n;

				if (nsig < gen && p[nsig] > '4') {
					drop = '9';
				} else {
					drop = '0';
				}

				for (n = nsig; p[--n] == drop;) {
					nsig--;
				}

				if (drop == '9') {
					p[n]++;
				}

				if (n < 0) {
					--p, ++nsig, ++exp;
				}
			}
		}
	}

	debugger_format_decimal_digits(args, type, p, nsig, exp);
}




s16 debugger_unscale_f64(s16 *exponent, f64 *value) {
    u16 *words = (u16 *)value;
    s16 characteristic = (words[0] & 0x7FF0) >> 4;

    if (characteristic == 0x7FF) {
        *exponent = 0;
        return (words[0] & 0xF) || words[1] || words[2] || words[3] ? 2 : 1;
    } else if (characteristic > 0) {
        words[0] = (words[0] & 0x800F) | 0x3FF0;
        *exponent = characteristic - 0x3FE;
        return -1;
    } else if (characteristic < 0) {
        return 2;
    } else {
        *exponent = 0;
        return 0;
    }
}
extern const u8 D_16004878[2];

void debugger_format_decimal_digits(ConkerPft *px, u8 code, u8 *p, s16 nsig, s16 xexp)
{
	const u8 point = '.';

	if (nsig <= 0) {
		p = (u8 *)D_16004878;
		nsig = 1;
	}

	if (code == 'f' || ((code == 'g' || code == 'G') && xexp >= -4 && xexp < px->prec)) {
		/* 'f' format */
		xexp++; /* change to leading digit count */

		if (code != 'f') {
			/* fixup for 'g' */
			if (!(px->flags & 8) && nsig < px->prec) {
				px->prec = nsig;
			}

			px->prec -= xexp;

			if (px->prec < 0) {
				px->prec = 0;
			}
		}

		if (xexp <= 0) {
			/* digits only to right of point */
			px->s[px->n1++] = '0';

			if (px->prec > 0 || px->flags & 8) {
				px->s[px->n1++] = point;
			}

			if (px->prec < -xexp) {
				xexp = -px->prec;
			}

			px->nz1 = -xexp;
			px->prec += xexp;

			if (px->prec < nsig) {
				nsig = px->prec;
			}

			px->n2 = nsig;

			debugger_copy_bytes(&px->s[px->n1], p, nsig);

			px->nz2 = px->prec - nsig;
		} else if (nsig < xexp) {
			/* zeros before point */
			debugger_copy_bytes(&px->s[px->n1], p, nsig);

			px->n1 += nsig;
			px->nz1 = xexp - nsig;

			if (px->prec > 0 || px->flags & 8) {
				px->s[px->n1] = point;
				px->n2++;
			}

			px->nz2 = px->prec;
		} else {
			/* enough digits before point */
			debugger_copy_bytes(&px->s[px->n1], p, xexp);

			px->n1 += xexp;
			nsig -= xexp;

			if (px->prec > 0 || px->flags & 8) {
				px->s[px->n1++] = point;
			}

			if (px->prec < nsig) {
				nsig = px->prec;
			}

			debugger_copy_bytes(&px->s[px->n1], p + xexp, nsig);

			px->n1 += nsig;
			px->nz1 = px->prec - nsig;
		}
	} else {
		/* 'e' format */
		if (code == 'g' || code == 'G') {
			/* fixup for 'g' */
			if (nsig < px->prec) {
				px->prec = nsig;
			}

			px->prec--;

			if (px->prec < 0) {
				px->prec = 0;
			}

			code = code == 'g' ? 'e' : 'E';
		}

		px->s[px->n1] = *p;
		px->n1++;
		p++;

		if (px->prec > 0 || px->flags & 8) {
			px->s[px->n1] = point;
			px->n1++;
		}

		if (px->prec > 0) {
			/* put fraction digits */
			nsig--;

			if (px->prec < nsig) {
				nsig = px->prec;
			}

			debugger_copy_bytes(&px->s[px->n1], p, nsig);

			px->n1 += nsig;
			px->nz1 = px->prec - nsig;
		}

		p = (u8 *) &px->s[px->n1]; /* put exponent */
		*p = code;
		p++;

		if (xexp >= 0) {
			*p++ = '+';
		} else {
			/* negative exponent */
			*p++ = '-';
			xexp = -xexp;
		}

		if (xexp >= 100) {
			/* put oversize exponent */
			if (xexp >= 1000) {
				*p = xexp / 1000 + 0x30, xexp %= 1000;
				p++;
			}

			*p = xexp / 100 + 0x30, xexp %= 100;
			p++;
		}

		*p = xexp / 10 + 0x30, xexp %= 10;
		p++;
		*p = xexp + 0x30;
		p++;

		px->n2 = p - (u8 *) &px->s[px->n1];
	}

	if ((px->flags & (16 | 4)) == 16) {
		/* pad with leading zeros */
		int n = px->n0 + px->n1 + px->nz1 + px->n2 + px->nz2;

		if (n < px->width) {
			px->nz0 = px->width - n;
		}
	}
}

typedef struct { s64 quot, rem; } DebuggerLldiv;
DebuggerLldiv func_10022F60(s64 numerator, s64 denominator);
u64 func_1002682C(u64 numerator, u64 denominator);
u64 func_10026868(u64 numerator, u64 denominator);
extern u8 D_16003CB8[17];
extern u8 D_16003CCC[17];
#define FLAGS_MINUS 4
#define FLAGS_ZERO 16

void debugger_format_integer_digits(ConkerPft *px, u8 code) {
    u8 buff[24];
    const u8 *digs;
    int base;
    int i;
    unsigned long long ullval;

    digs = (code == 'X') ? D_16003CCC : D_16003CB8;

    base = (code == 'o') ? 8 : ((code != 'x' && code != 'X') ? 10 : 16);
    i = 24;
    ullval = px->v.ll;

    if ((code == 'd' || code == 'i') && px->v.ll < 0) {
        ullval = -ullval;
    }

    if (ullval != 0 || px->prec != 0) {
        buff[--i] = digs[func_1002682C(ullval, base)];
    }

    px->v.ll = func_10026868(ullval, base);

    while (px->v.ll > 0 && i > 0) {
        DebuggerLldiv qr = func_10022F60(px->v.ll, base);

        px->v.ll = qr.quot;
        buff[--i] = digs[qr.rem];
    }

    px->n1 = 24 - i;

    debugger_copy_bytes(px->s, buff + i, px->n1);

    if (px->n1 < px->prec) {
        px->nz0 = px->prec - px->n1;
    }


    if (px->prec < 0 && (px->flags & (FLAGS_ZERO | FLAGS_MINUS)) == FLAGS_ZERO) {
        if ((i = px->width - px->n0 - px->nz0 - px->n1) > 0) {
            px->nz0 += i;
        }
    }

}
