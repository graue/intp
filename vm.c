#include <stdio.h>
#include <string.h>
#include "xmalloc.h"
#include "error.h"
#include "stack.h"
#include "code.h"
#include "builtin.h"
#include "vm.h"
#include "vobj.h"
#include "abbr.h"
stk *sk, *rsk;
s word *wds;
s i nwds, swds;
/* adding words */
v addbltn(c *nam, v (*fun)(v))
{
	XPND(wds, nwds, swds);
	wds[nwds].nam = nam;
	wds[nwds].bltn = 1;
	wds[nwds].meat.fun = fun;
	nwds++;
}
v addwd(c *nam, cmd *cmds)
{
	XPND(wds, nwds, swds);
	wds[nwds].nam = nam;
	wds[nwds].bltn = 0;
	wds[nwds].meat.cmds = cmds;
	nwds++;
}
/* setup */
v initvm(v)
{
	sk = makestack();
	rsk = makestack();
	regstk();
	regstr();
	regctl();
	regnum();
}
/* running words */
s t c *todo;
s v execcmd(t cmd *cd, i cp) /* cp -> can postpone */
{
	if (cd->ctyp == CMDCALL)
	{
		if (cp) todo = cd->arg.str;
		l callwd(cd->arg.str);
	}
	l if (cd->ctyp == CMDNUM)
		push(sk, vjfromnum(cd->arg.num));
	l /* CMDSTR */
		push(sk, vjfromstr(xsd(cd->arg.str)));
}
s v execwd(t word *wd)
{
	if (wd->bltn)
		wd->meat.fun();
	l
	{
		cmd *cd;
		for (cd = wd->meat.cmds; cd->ctyp != CMDEND; cd++)
			execcmd(cd, cd[1].ctyp == CMDEND);
	}
}
v callwd(t c *wdnam)
{
	i ix;
start:
	todo = N;
	for (ix = 0; ix < nwds; ix++)
		if (strcmp(wdnam, wds[ix].nam) == 0)
		{
			execwd(&wds[ix]);
			if (todo != N)
			{
				wdnam = todo;
				goto start;
			}
			r;
		}
	error("missing word %s", wdnam);
}
