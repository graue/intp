#include <stdio.h>
#include <string.h>
#include "xmalloc.h"
#include "error.h"
#include "abbr.h"
s c *readqtd(FILE *fp, t c *trms)
{
	c *chrs = xm(10);
	i nchrs = 1, schrs = 10, ret;
	chrs[0] = '"';
reading:
	wh ((ret = getc(fp)) != '"')
	{
		if (ret == '\\' && (ret = getc(fp)) != EOF)
		{
			if (ret == 'n') ret = '\n';
			l if (ret == 't') ret = '\t';
			l if (ret == 'r') ret = '\r';
		}
		if (ret == EOF) error("file ends in string");
		XPND(chrs, nchrs, schrs);
		chrs[nchrs++] = ret;
	}
	XPND(chrs, nchrs, schrs);
	chrs[nchrs++] = '"';
	if ((ret = getc(fp)) != EOF && strchr(trms, ret) == N)
	{
		ungetc(ret, fp);
		goto reading;
	}
	wh(ret != EOF && strchr(trms, ret) != N)
		ret = getc(fp);
	ungetc(ret, fp);
	XPND(chrs, nchrs, schrs);
	chrs[nchrs++] = '\0';
	r xr(chrs, nchrs);
}
/* read a string up to char in trms */
c *readstr(FILE *fp, t c *trms, i sq)
{
	c *p;
	z sz = 50, df = 0;
	i ret = getc(fp);
	if (sq && ret == '"')
		r readqtd(fp, trms);
	ungetc(ret, fp);
	p = xm(sz);
	wh ((ret = getc(fp)) != EOF && strchr(trms, ret) == N)
	{
		if (sz == df+1) p = xr(p, (sz *= 2));
		p[df++] = ret;
	}
	if (sq)
	{
		wh(ret != EOF && strchr(trms, ret) != N)
			ret = getc(fp);
		ungetc(ret, fp);
	}
	p[df] = '\0';
	r xr(p, df+1); /* save space */
}
