/*
* varargs.h
*
* Provides facilities for stepping through a list of function arguments of
* an unknown number and type.
*
* Note that the type used in va_arg is supposed to match the actual type
* *after default promotions*. Thus, va_arg (..., short) is not valid.
*
*/

#ifndef _VARARGS_H_
#define _VARARGS_H_


/*
* I was told that Win NT likes this.
*/
#ifndef _VA_LIST_DEFINED
#define _VA_LIST_DEFINED
#endif

#ifndef	_VA_LIST
#define _VA_LIST
typedef int* va_list;
#endif

/*
* Amount of space required in an argument list (ie. the stack) for an
* argument of type t.
*/
#define __va_argsiz(t)	\
	(((sizeof(t) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))


/*
* Start variable argument list processing by setting AP to point to the
* argument after pN.
*/
#define va_start(ap, pN)	\
	((ap) = (va_list)*(va_list)((char*)(&pN) + __va_argsiz(pN)))

/*
* Increment ap to the next argument in the list while returing a
* pointer to what ap pointed to first, which is of type t.
*
* We cast to void* and then to t* because this avoids a warning about
* increasing the alignment requirement.
*/

#define va_arg(ap, t)					\
	 (((ap) = (va_list)((char*)(ap) + __va_argsiz(t))),		\
	  *((t*) (void*) ((char*)(ap) - __va_argsiz(t))))

/*
* Gets the variable argument param count from the last argument pN
*/
#define va_count(pN)	\
	(*(int*)((char*)(&pN) + __va_argsiz(pN) + sizeof(va_list)))

/*
* Gets the variable argument stack count from the last argument pN
*/
#define va_scount(pN)	\
	(*(int*)((char*)(&pN) + __va_argsiz(pN) + sizeof(va_list) + sizeof(int)))


#endif /* not _VARARGS_H_ */