#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "abbr.h"
v *xm(z sz)
{
	v *p;
	p = malloc(sz);
	if (p == N) error("out of memory");
	r p;
}
v *xr(v *p, z sz)
{
	p = realloc(p, sz);
	if (p == N) error("out of memory");
	r p;
}
c *xsnd(t c *sr, i n)
{
	c *ds = xm(n+1);
	memcpy(ds, sr, n);
	ds[n] = '\0';
	r ds;
}
/* expand array */
v *xpnd(v *p, i nit, i *sit, z sz)
{
	if (nit < *sit) r p;
	l if (*sit > 0) r xr(p, sz * (*sit *= 2));
	l r xm(sz * (*sit = 10));
}
