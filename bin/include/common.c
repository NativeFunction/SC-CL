#include "types.h"
#include "constants.h"
#include "natives.h"
#include "intrinsics.h"
#include "varargs.h"


#define GlobalCharBufferD "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"

char* GlobalCharBuffer = GlobalCharBufferD;//256

void print(const char* str, int ms)
{
	#if TARGET == TARGET_GTAV
	begin_text_command_print("STRING");
	add_text_component_substring_player_name(str);
	end_text_command_print(ms, 1);
	#elif TARGET == TARGET_RDR
	_clear_prints();
	_print_subtitle(str, ms != 0 ? (float)ms / 1000.0f : 0, true, 2, 1, 0, 0, 0);
	#elif TARGET == TARGET_GTAIV
	CLEAR_PRINTS();
	PRINT_STRING_WITH_LITERAL_STRING_NOW("STRING", str, ms, true);
	#endif
}

const char* IntToHex(int val, bool isLowercase)
{
	char* hex_str;
	if(isLowercase)
		hex_str = "0123456789ABCDEF";
	else
		hex_str = "0123456789abcdef";

	byte* bin = (byte*)&val;

	char* str = "         ";

	for (int i = 0; i < 4; i++)
	{
		str[i * 2] = hex_str[(bin[i] >> 4) & 0x0F];
		str[i * 2 + 1] = hex_str[(bin[i]) & 0x0F];
	}
	str[8] = 0;
	return str;
}
int HexToInt(const char *hex)
{
	uint result = 0;

	while (*hex)
	{
		if (*hex > 47 && *hex < 58)
			result += (*hex - 48);
		else if (*hex > 64 && *hex < 71)
			result += (*hex - 55);
		else if (*hex > 96 && *hex < 103)
			result += (*hex - 87);

		if (*++hex)
			result <<= 4;
	}

	return result;
}
int IntToBase(int n, int b)
{
	int rslt = 0, digitPos = 1;
	while (n)
	{
		rslt += (n%b)*digitPos;
		n /= b;
		digitPos *= 10;
	}
	return rslt;
}


#define MAX_FCONVERSION	255	/* largest possible real conversion 	*/
#define MAX_EXPT	8	/* largest possible exponent field */
#define MAX_FRACT	23	/* largest possible fraction field */

#define TESTFLAG(x)	0


#define	to_char(n)	((n) + '0')
#define	to_digit(c)	((c) - '0')
#define _isNan(arg)	((arg) != (arg))

#if TARGET == TARGET_RDR
#define strlen(str) string_length(str)
#else
#define strlen(str) get_length_of_literal_string(str)
#endif

static int cvt(float arg, int prec, char *signp, int fmtch,
			   char *startp, char *endp);
static char *_round(float fract, int *exp, char *start, char *end,
				   char ch, char *signp);
static char *exponent(char *p, int exp, int fmtch);
static double ModF(float f, float * iptr)
{
	*iptr = (float)(int)f;
	return f - (float)(int)f;
}

#define	to_char(n)	((n) + '0')
#define	to_digit(c)	((c) - '0')
#define _isNan(arg)	((arg) != (arg))
/*
typedef union IEEEf2bits
{
	float	f;
	struct
	{
		#if ENDIAN == ENDIAN_LITTLE
		unsigned int	man : 23;
		unsigned int	exp : 8;
		unsigned int	sign : 1;
		#else //ENDIAN_BIG
		unsigned int	sign : 1;
		unsigned int	exp : 8;
		unsigned int	man : 23;
		#endif
	} bits;
} IEEEf2bits;

static int __finite(rtype f)
{
	IEEEf2bits ip;
	ip.f = f;
	return (ip.bits.exp != 0xFF);
}
*/

static int __finite(float d)
{
	
	#if ENDIAN == ENDIAN_LITTLE
	struct IEEEdp
	{
		unsigned manl : 32;
		unsigned manh : 20;
		unsigned exp : 11;
		unsigned sign : 1;
	} *ip;
	#else
	struct IEEEdp
	{
		unsigned int sign : 1;
		unsigned int exp : 11;
		unsigned int manh : 20;
		unsigned int manl : 32;
	} *ip;
	#endif


	ip = (struct IEEEdp *)&d;
	return (ip->exp != 0xff);
}

static void dtoa(char *dbuf, float arg, int fmtch, int width, int prec)
{
	char	buf[MAX_FCONVERSION + 1], *cp;
	char	sign;
	int	size;

	if (!__finite(arg))
	{
		if (_isNan(arg))
			strcpy(dbuf, "NaN", 255);
		else if (arg < 0)
			strcpy(dbuf, "-Infinity", 255);
		else
			strcpy(dbuf, "Infinity",255);
		return;
	}

	if (prec == 0)
		prec = 6;
	else if (prec > MAX_FRACT)
		prec = MAX_FRACT;

	/* leave room for sign at start of buffer */
	cp = buf + 1;

	/*
	* cvt may have to round up before the "start" of
	* its buffer, i.e. ``intf("%.2f", (double)9.999);'';
	* if the first character is still NUL, it did.
	* softsign avoids negative 0 if _double < 0 but
	* no significant digits will be shown.
	*/
	*cp = '\0';
	size = cvt(arg, prec, &sign, fmtch, cp, buf + sizeof(buf));
	if (*cp == '\0')
		cp++;

	if (sign)
		*--cp = sign, size++;

	cp[size] = 0;
	memcpy(dbuf, cp, size + 1);
}

static int cvt(float number, int prec, char *signp, int fmtch, char *startp, char *endp)
{
	register char *p, *t;
	register float fract;
	float integer, tmp;
	int dotrim, expcnt, gformat;

	dotrim = expcnt = gformat = 0;
	if (number < 0)
	{
		number = -number;
		*signp = '-';
	}
	else
		*signp = 0;

	fract = ModF(number, &integer);

	/* get an extra slot for rounding. */
	t = ++startp;

	/*
	* get integer portion of number; put into the end of the buffer; the
	* .01 is added for modf(356.0 / 10, &integer) returning .59999999...
	*/
	for (p = endp - 1; integer; ++expcnt)
	{
		tmp = ModF(integer / 10, &integer);
		*p-- = to_char((int)((tmp + .01) * 10));
	}
	switch (fmtch)
	{
		case 'f':
			/* reverse integer into beginning of buffer */
			if (expcnt)
				for (; ++p < endp; *t++ = *p);
			else
				*t++ = '0';
			/*
			* if precision required or alternate flag set, add in a
			* decimal point.
			*/
			if (prec || TESTFLAG(ALTERNATE_FORM))
				*t++ = '.';
			/* if requires more precision and some fraction left */
			if (fract)
			{
				if (prec)
					do
					{
						fract = ModF(fract * 10, &tmp);
						*t++ = to_char((int)tmp);
					} while (--prec && fract);
					if (fract)
						startp = _round(fract, (int *)NULL, startp,
									   t - 1, (char)0, signp);
			}
			for (; prec--; *t++ = '0');
			break;
		case 'e':
		case 'E':
		eformat:	if (expcnt)
		{
			*t++ = *++p;
			if (prec || TESTFLAG(ALTERNATE_FORM))
				*t++ = '.';
			/* if requires more precision and some integer left */
			for (; prec && ++p < endp; --prec)
				*t++ = *p;
			/*
			* if done precision and more of the integer component,
			* round using it; adjust fract so we don't re-round
			* later.
			*/
			if (!prec && ++p < endp)
			{
				fract = 0;
				startp = _round(0, &expcnt, startp,
							   t - 1, *p, signp);
			}
			/* adjust expcnt for digit in front of decimal */
			--expcnt;
		}
					/* until first fractional digit, decrement exponent */
					else if (fract)
					{
						/* adjust expcnt for digit in front of decimal */
						for (expcnt = -1;; --expcnt)
						{
							fract = ModF(fract * 10, &tmp);
							if (tmp)
								break;
						}
						*t++ = to_char((int)tmp);
						if (prec || TESTFLAG(ALTERNATE_FORM))
							*t++ = '.';
					}
					else
					{
						*t++ = '0';
						if (prec || TESTFLAG(ALTERNATE_FORM))
							*t++ = '.';
					}
					/* if requires more precision and some fraction left */
					if (fract)
					{
						if (prec)
							do
							{
								fract = ModF(fract * 10, &tmp);
								*t++ = to_char((int)tmp);
							} while (--prec && fract);
							if (fract)
								startp = _round(fract, &expcnt, startp,
											   t - 1, (char)0, signp);
					}
					/* if requires more precision */
					for (; prec--; *t++ = '0');

					/* unless alternate flag, trim any g/G format trailing 0's */
					if (gformat && !TESTFLAG(ALTERNATE_FORM))
					{
						while (t > startp && *--t == '0');
						if (*t == '.')
							--t;
						++t;
					}
					t = exponent(t, expcnt, fmtch);
					break;
		case 'g':
		case 'G':
			/* a precision of 0 is treated as a precision of 1. */
			if (!prec)
				++prec;
			/*
			* ``The style used depends on the value converted; style e
			* will be used only if the exponent resulting from the
			* conversion is less than -4 or greater than the precision.''
			*	-- ANSI X3J11
			*/
			if (expcnt > prec || (!expcnt && fract && fract < .0001))
			{
				/*
				* g/G format counts "significant digits, not digits of
				* precision; for the e/E format, this just causes an
				* off-by-one problem, i.e. g/G considers the digit
				* before the decimal point significant and e/E doesn't
				* count it as precision.
				*/
				--prec;
				fmtch -= 2;		/* G->E, g->e */
				gformat = 1;
				goto eformat;
			}
			/*
			* reverse integer into beginning of buffer,
			* note, decrement precision
			*/
			if (expcnt)
				for (; ++p < endp; *t++ = *p, --prec);
			else
				*t++ = '0';
			/*
			* if precision required or alternate flag set, add in a
			* decimal point.  If no digits yet, add in leading 0.
			*/
			if (prec || TESTFLAG(ALTERNATE_FORM))
			{
				dotrim = 1;
				*t++ = '.';
			}
			else
				dotrim = 0;
			/* if requires more precision and some fraction left */
			if (fract)
			{
				if (prec)
				{
					do
					{
						fract = ModF(fract * 10, &tmp);
						*t++ = to_char((int)tmp);
					} while (!tmp && !expcnt);
					while (--prec && fract)
					{
						fract = ModF(fract * 10, &tmp);
						*t++ = to_char((int)tmp);
					}
				}
				if (fract)
					startp = _round(fract, (int *)NULL, startp,
								   t - 1, (char)0, signp);
			}
			/* alternate format, adds 0's for precision, else trim 0's */
			if (TESTFLAG(ALTERNATE_FORM))
				for (; prec--; *t++ = '0');
			else if (dotrim)
			{
				while (t > startp && *--t == '0');
				if (*t != '.')
					++t;
			}
	}
	return (t - startp);
}

static char* _round(float fract, int *exp, char *start, char *end, char ch, char *signp)
{
	float tmp;

	if (fract)
		(void)ModF(fract * 10, &tmp);
	else
		tmp = to_digit(ch);
	if (tmp > 4)
		for (;; --end)
		{
			if (*end == '.')
				--end;
			if (++*end <= '9')
				break;
			*end = '0';
			if (end == start)
			{
				if (exp)
				{	/* e/E; increment exponent */
					*end = '1';
					++*exp;
				}
				else
				{		/* f; add extra digit */
					*--end = '1';
					--start;
				}
				break;
			}
		}
	/* ``"%.3f", (double)-0.0004'' gives you a negative 0. */
	else if (*signp == '-')
		for (;; --end)
		{
			if (*end == '.')
				--end;
			if (*end != '0')
				break;
			if (end == start)
				*signp = 0;
		}
	return (start);
}

static char* exponent(char *p, int exp, int fmtch)
{
	char *t;
	char expbuf[MAX_FCONVERSION];

	*p++ = fmtch;
	if (exp < 0)
	{
		exp = -exp;
		*p++ = '-';
	}
	else
		*p++ = '+';
	t = expbuf + MAX_FCONVERSION;
	if (exp > 9)
	{
		do
		{
			*--t = to_char(exp % 10);
		} while ((exp /= 10) > 9);
		*--t = to_char(exp);
		for (; t < expbuf + MAX_FCONVERSION; *p++ = *t++);
	}
	else
	{
		*p++ = '0';
		*p++ = to_char(exp);
	}
	return (p);
}



void vsprintf(char* buffer, const char* format, va_list va)
{

	int FormatLen = strlen(format);
	char TempBuffer[4] = { 0 , 0, 0, 0 };

	strcpy(buffer, "", 255);

	enum
	{
		PF_Positive,
		PF_Prefix,
	};

	int PF_Options = 0;

	for (int i = 0; i < FormatLen; i++)
	{
		#define AdvanceFormat() if (++i >= FormatLen) goto end_sprintf;

		if (format[i] == '%')
		{
			AdvanceFormat();

			//parse flags
		PF_Parse_Flags:
			switch (format[i])
			{
				case '+':
				bit_set(&PF_Options, PF_Positive);
				AdvanceFormat();
				goto PF_Parse_Flags;
				case '#':
				bit_set(&PF_Options, PF_Prefix);
				AdvanceFormat();
				goto PF_Parse_Flags;
			}


			//parse specifier
			switch (format[i])
			{
				case 'd':
				case 'i':
				{
					int Value = va_arg(va, int);
					if (bit_test(PF_Options, PF_Positive) && Value >= 0)
						stradd(buffer, "+", 255);
					straddi(buffer, Value, 255);

				}
				break;
				case 'o':
				if (bit_test(PF_Options, PF_Prefix))
					stradd(buffer, "0", 255);
				straddi(buffer, IntToBase(va_arg(va, int), 8), 255);
				break;
				case 'p':
				case 'x':
				if (bit_test(PF_Options, PF_Prefix))
					stradd(buffer, "0x", 255);
				stradd(buffer, IntToHex(va_arg(va, int), true), 255);
				break;
				case 'X':
				if (bit_test(PF_Options, PF_Prefix))
					stradd(buffer, "0X", 255);
				stradd(buffer, IntToHex(va_arg(va, int), false), 255);
				break;
				case 'f':
				case 'F':
				{
					char b[255];
					dtoa(b, va_arg(va, float), 'f', 0, 0);
					stradd(buffer, b, 255);
				}
				break;
				case 'c':
				TempBuffer[0] = va_arg(va, char);
				stradd(buffer, TempBuffer, 255);
				break;
				case 's':
				stradd(buffer, va_arg(va, char*), 255);
				break;
				case 'n':
				*va_arg(va, int*) = strlen(buffer);
				break;

				case '%':
				TempBuffer[0] = format[i];
				stradd(buffer, TempBuffer, 255);
				break;
			}
		}
		else
		{
			TempBuffer[0] = format[i];
			stradd(buffer, TempBuffer, 255);
		}
	}
end_sprintf:;
}



void sprintf(char* buffer, const char* format, ...)
{
	struct IEEEdd
	{
		int a;
		int b;
		int c;
	} *bp;
	bp->a = 0;
	bp->b = 0;
	bp->c = 0;
	va_list va;
	va_start(va, format);
	vsprintf(buffer, format, va);
}
void printf(const char* format, ...)
{
	char b[255];
	float n = 3.6;
	dtoa(b, n, 'f', 0, 0);

	va_list va;
	va_start(va, format);
	vsprintf(GlobalCharBuffer, format, va);
	print(GlobalCharBuffer, 5000);
}

const char* strcatGlobal(const char* str1, const char* str2)
{
	//this takes advantage of strings being global
	//this returns a static pointer so if you want to use the function again without losing the return you have to strcpy it


	strcpy((char*)GlobalCharBuffer, str1, 255);
	stradd((char*)GlobalCharBuffer, str2, 255);
	return (char*)GlobalCharBuffer;
}
const char* straddiGlobal(const char* str1, int i)
{
	//this takes advantage of strings being global
	//this returns a static pointer so if you want to use the function again without losing the return you have to strcpy it

	strcpy((char*)GlobalCharBuffer, str1, 255);
	straddi((char*)GlobalCharBuffer, i, 255);
	return (char*)GlobalCharBuffer;
}
const char* itosGlobal(int i)
{
	//this takes advantage of strings being global
	//this returns a static pointer so if you want to use the function again without losing the return you have to strcpy it

	itos((char*)GlobalCharBuffer, i, 64);
	return (char*)GlobalCharBuffer;
}
void Throw(const char* str)
{
	char Buffer[256];
	strcpy(Buffer, "~r~Exception~s~: ", 255);

	stradd(Buffer, str, 255);
	print(Buffer, 10000);
	wait(10000);

	#if TARGET == TARGET_GTAV
	terminate_this_thread();
	#else
	terminate_this_script();
	#endif
}
void Warn(const char* str)
{
	char Buffer[256];
	#if TARGET == TARGET_RDR
	strcpy(Buffer, "<yellow>Warning</yellow>: ", 255);
	#else
	strcpy(Buffer, "~y~Warning~s~: ", 255);
	#endif

	stradd(Buffer, str, 255);
	print(Buffer, 5000);
}
void Error(const char* str)
{
	char Buffer[256];
	#if TARGET == TARGET_RDR
	strcpy(Buffer, "<red>Error</red>: ", 255);
	#else
	strcpy(Buffer, "~r~Error~s~: ", 255);
	#endif

	stradd(Buffer, str, 255);
	print(Buffer, 5000);
}

int SwapEndian32(int value)
{
	return ((((value) & 0xff000000) >> 24) | (((value) & 0x00ff0000) >> 8) | (((value) & 0x0000ff00) << 8) | (((value) & 0x000000ff) << 24));
}
short SwapEndian16(short value)
{
	return (((value) & 0xff000000) >> 24) | (((value) & 0x00ff0000) >> 8);
}
int CeilDivInt(uint a, uint b)
{
	return a == 0 || b == 0 ? 0 : 1 + ((a - 1) / b);
}

int DivInt(int a, int b)
{
	return a == 0 || b == 0 ? 0 : a / b;
}
float DivFloat(float a, float b)
{
	return a == 0.0f || b == 0.0f ? 0.0f : a / b;
}
void SetBitAtIndex(int* value, uint index, bool bit)
{
	*value = *value ^ ((-bit ^ *value) & (1 << (index % 32)));
}
int ModNegitive(int value1, int value2)
{
	int ret = value1 % value2;
	return ret < 0 ? ret + value2 : ret;
}
quaternion EulerToQuaternion(vector3 euler)
{
	float cosYawOver2 = cos(euler.x * 0.5),
		sinYawOver2 = sin(euler.x * 0.5),

		cosPitchOver2 = cos(euler.y * 0.5),
		sinPitchOver2 = sin(euler.y * 0.5),

		cosRollOver2 = cos(euler.z * 0.5),
		sinRollOver2 = sin(euler.z * 0.5);

	quaternion out =
	{
		(cosYawOver2 * cosPitchOver2 * cosRollOver2) + (sinYawOver2 * sinPitchOver2 * sinRollOver2),
		(cosYawOver2 * cosPitchOver2 * sinRollOver2) - (sinYawOver2 * sinPitchOver2 * cosRollOver2),
		(cosYawOver2 * sinPitchOver2 * cosRollOver2) + (sinYawOver2 * cosPitchOver2 * sinRollOver2),
		(sinYawOver2 * cosPitchOver2 * cosRollOver2) - (cosYawOver2 * sinPitchOver2 * sinRollOver2)
	};
	return out;
}
vector3 RotationLookAtPoint(vector3 pos, vector3 endpos)
{
	vector3 out =
	{
		atan2(pos.y, pos.z),
		atan2(pos.x * cos(endpos.x), pos.z),
		atan2(cos(endpos.x), sin(endpos.x) * sin(pos.y))
	};
	return out;
}

#if TARGET == TARGET_RDR
#ifdef _MSC_VER
#define acos(number) acosMSC(number)
float acosMSC(float number)
#else
float acos(float number)
#endif
{
	//this works fine for floats as negitive ints and floats both have msb set
	if (reinterpretFloatToInt(number) < 0)
	{
		number = -number;
		return
			-(((((((
			-0.0187293f * number)
			+ 0.0742610f)
			* number)
			- 0.2121144f)
			* number)
			+ 1.5707288f)
			* sqrt(1.0 - number))
			+ PI;
	}

	return
		((((((
		-0.0187293f * number)
		+ 0.0742610f)
		* number)
		- 0.2121144f)
		* number)
		+ 1.5707288f)
		* sqrt(1.0 - number);

}
#ifdef _MSC_VER
#define asin(number) asinMSC(number)
float asinMSC(float number)
#else
float asin(float number)
#endif
{
	//this works fine for floats as negitive ints and floats both have msb set
	if (reinterpretFloatToInt(number) < 0)
	{
		number = -number;
		return
			(((((((
			-0.0187293f * number)
			+ 0.0742610f)
			* number)
			- 0.2121144f)
			* number)
			+ 1.5707288f)
			* sqrt(1.0 - number))
			- 1.57079632;
	}
	return
		-(((((((
		-0.0187293f * number)
		+ 0.0742610f)
		* number)
		- 0.2121144f)
		* number)
		+ 1.5707288f)
		* sqrt(1.0 - number))
		+ 1.57079632;
}

#endif

float StringToFloat(const char* str)
{
	float rez = 0, fact = 1;
	bool point_seen = false;
	str -= 3;
	int d = 0, read_char = *str & 0xFF;

	if (read_char == '-')
	{
		fact = -1;
		read_char = *++str & 0xFF;
	}

	while (read_char)
	{
		if (read_char == '.')
		{
			point_seen = true;
			read_char = *++str & 0xFF;
			continue;
		}

		d = read_char - '0';

		if (d >= 0 && d <= 9)
		{
			if (point_seen)
				fact /= 10;
			rez = rez * 10.0f + (float)d;
		}
		read_char = *++str & 0xFF;
	}
	return rez * fact;
}

bool CmpLtU(int a, int b)
{
	if (a >= 0 && b >= 0)
		return a < b;
	else
	{
		if (a == b)
			return false;

		int ltb = ~a & b;

		ltb |= ltb >> 1;
		ltb |= ltb >> 2;
		ltb |= ltb >> 4;
		ltb |= ltb >> 8;
		ltb |= ltb >> 16;
		return ((a & ~b) & ~ltb) == 0;
	}
}
bool CmpGtU(int a, int b)
{
	if (a >= 0 && b >= 0)
		return a > b;
	else
	{
		int ltb = ~a & b;

		ltb |= ltb >> 1;
		ltb |= ltb >> 2;
		ltb |= ltb >> 4;
		ltb |= ltb >> 8;
		ltb |= ltb >> 16;

		return ((a & ~b) & ~ltb) != 0;
	}
}
//TODO: add these as intrinsics
int Diff64P(int* x, int* y)
{
	int out[2];
	out[0] = (int)x - (int)y;
	#if PTRWIDTH == 64
	*(int*)((char*)out + 4) = *(int*)((char*)&x + 4) - *(int*)((char*)&y + 4);
	if (CmpGtU(out[0], (int)x))
		out[1]--;
	#endif
	return out[0];

}
int* Sub64P(int* x, int yLeft, int yRight)
{
	int out[2];
	out[0] = (int)x - yLeft;
	#if PTRWIDTH == 64
	*(int*)((char*)out + 4) = *(int*)((char*)&x + 4) - yRight;
	if (CmpGtU(out[0], (int)x))
		out[1]--;
	#endif
	return (int*)out[0];
}
int* Add64P(int* x, int yLeft, int yRight)
{
	int out[2];
	out[0] = (int)x + yLeft;
	#if PTRWIDTH == 64
	*(int*)((char*)out + 4) = *(int*)((char*)&x + 4) + yRight;
	//if (CmpLtU(out[0], (int)x))
		//out[1]++;
	#endif
	return (int*)out[0];
}
int* Push64P(int LeftMost, int RightMost)
{
	#if PTRWIDTH == 64
	int out[2];
	out[0] = LeftMost;
	*(int*)((char*)out + 4) = RightMost;
	return (int*)out[0];
	#else
	return (int*)LeftMost;
	#endif
}

