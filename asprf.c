#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "xmalloc.h"
#include "abbr.h"
s i vasprf(c **ret, t c *fmt, va_list ap)
{
	i ln = vsnprintf(N, 0, fmt, ap) + 1;
	c *str = xm(ln);
	*ret = str;
#ifdef __OpenBSD__
	r vsnprintf(str, ln, fmt, ap);
#else
	r vsprintf(str, fmt, ap);
#endif
}
i asprf(c **ret, t c *fmt, ...)
{
	i res;
	va_list rpt;
	va_start(rpt, fmt);
	res = vasprf(ret, fmt, rpt);
	va_end(rpt);
	r res;
}
