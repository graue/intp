#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "xmalloc.h"
#include "abbr.h"
i asprf(c **ret, t c *fmt, ...)
{
	i ln;
	va_list ap;
	c *str;
	va_start(ap, fmt);
	ln = vsnprintf(N, 0, fmt, ap) + 1;
	va_end(ap);
	va_start(ap, fmt);
	str = xm(ln);
	vsnprintf(str, ln, fmt, ap);
	va_end(ap);
	*ret = str;
	r ln - 1;
}
