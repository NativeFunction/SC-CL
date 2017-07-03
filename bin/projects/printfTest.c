//largest possible real conversion
#define MAX_FCONVERSION 255
//largest possible exponent field
#define MAX_EXPT 8
//largest possible fraction field
#define MAX_FRACT 23

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
static float ModF(float f, float * iptr)
{
	*iptr = (float)(int)f;
	return f - (float)(int)f;
}

#define	to_char(n)	((n) + '0')
#define	to_digit(c)	((c) - '0')
#define _isNan(arg)	((arg) != (arg))

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
	char *p, *t;
	float fract;
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
		case 'f':{
			/* reverse integer into beginning of buffer */
			if (expcnt)
				for (; ++p < endp; *t++ = *p);
			else
				*t++ = '0';
			/*
			* if precision required or alternate flag set, add in a
			* decimal point.
			*/
			if (prec)// || TESTFLAG(ALTERNATE_FORM))
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
		}
			break;
		case 'e'://Scientific notation
		case 'E':{
		eformat:
			if (expcnt)
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
			else if (fract)/* until first fractional digit, decrement exponent */
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
		}
			break;
		case 'g'://shortest representation
		case 'G':{
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
			break;
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
	va_list va;
	va_start(va, format);
	vsprintf(buffer, format, va);
}
void printf(const char* format, ...)
{
	va_list va;
	va_start(va, format);
	vsprintf(GlobalCharBuffer, format, va);
	print(GlobalCharBuffer, 5000);
}
