#include <PR/ultratypes.h>

/* Conker US Rare floating-point formatter, 0x1550:0x2070.
 * Independent lineage: Perfect Dark 169ed48bdcbfb3b568b028bd5bebb27680073514.
 * MIT notice: src/rsp/LICENSE. Complete source and constants are preserved
 * when promoting the reviewed source unit into the library archive.
 */

/* Formatting descriptor layout follows the pinned SDK xstdio.h. */
typedef struct {
    union { s64 ll; f64 ld; } v;
    u8 *s;
    s32 n0, nz0, n1, nz1, n2, nz2;
    s32 prec, width;
    u32 nchar, flags;
    u8 qual;
} ConkerPft;

typedef struct { s32 quot, rem; } ConkerLdiv;
extern void *func_80022EC0(void *dst, const void *src, u32 length);
extern ConkerLdiv func_80023060(s32 numerator, s32 denominator);
const f64 D_8002BF20[9] = {1e1, 1e2, 1e4, 1e8, 1e16, 1e32, 1e64, 1e128, 1e256};
const u8 D_8002BF68[] = "NaN";
const u8 D_8002BF6C[] = "Inf";
const u8 D_8002BF70[] = "0";
s16 func_800019F0(s16 *exponent, f64 *value);
void func_80001AA8(ConkerPft *px, u8 code, u8 *digits, s16 count, s16 exponent);

/* Retain the reviewed regional entry-point names. */
#define _Ldtob func_80001550
void _Ldtob(ConkerPft *args, u8 type)
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

	err = func_800019F0(&exp, &args->v.ld);

	if (err > 0) {
		func_80022EC0(args->s, err == 2 ? D_8002BF68 : D_8002BF6C, args->n1 = 3);
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
					ldval *= D_8002BF20[i];
				}
			}
		} else if (exp > 0) {
			f64 factor;
			one32 = 1.0f;
			factor = one32;
			exp &= ~3;

			for (n = exp, i = 0; n > 0; n >>= 1, i++) {
				if (n & 1) {
					factor *= D_8002BF20[i];
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
					ldval = (ldval - lo) * 1.0e8;
				}

				p += 8;

				for (j = 8; lo > 0 && --j >= 0;) {
					ConkerLdiv qr;

					qr = func_80023060(lo, 10);
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

	func_80001AA8(args, type, p, nsig, exp);
}



s16 func_800019F0(s16 *exponent, f64 *value) {
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
void func_80001AA8(ConkerPft *px, u8 code, u8 *p, s16 nsig, s16 xexp)
{
	const u8 point = '.';

	if (nsig <= 0) {
		p = D_8002BF70;
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

			func_80022EC0(&px->s[px->n1], p, nsig);

			px->nz2 = px->prec - nsig;
		} else if (nsig < xexp) {
			/* zeros before point */
			func_80022EC0(&px->s[px->n1], p, nsig);

			px->n1 += nsig;
			px->nz1 = xexp - nsig;

			if (px->prec > 0 || px->flags & 8) {
				px->s[px->n1] = point;
				px->n2++;
			}

			px->nz2 = px->prec;
		} else {
			/* enough digits before point */
			func_80022EC0(&px->s[px->n1], p, xexp);

			px->n1 += xexp;
			nsig -= xexp;

			if (px->prec > 0 || px->flags & 8) {
				px->s[px->n1++] = point;
			}

			if (px->prec < nsig) {
				nsig = px->prec;
			}

			func_80022EC0(&px->s[px->n1], p + xexp, nsig);

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

			func_80022EC0(&px->s[px->n1], p, nsig);

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
