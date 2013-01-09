#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "abbr.h"
#define MKERROR(nam, term)			\
v nam(t c *msg, ...)				\
{						\
	va_list rpt;				\
	c str[1600] = "";			\
	va_start(rpt, msg);			\
	vsnprintf(str, o str, msg, rpt);	\
	fprintf(stderr, "%s\n", str);		\
	va_end(rpt);				\
	term;					\
}
MKERROR(error, abort())
MKERROR(usrerr, exit(1))
