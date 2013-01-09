#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "xmalloc.h"
#include "read.h"
#include "code.h"
#include "stack.h"
#include "vm.h"
#include "error.h"
#include "abbr.h"
s v swlcmnt(FILE *fp)
{
	free(readstr(fp, "\n", 0));
	ungetc('\n', fp);
	free(readtows(fp));
}
s i readwd(FILE *fp)
{
	c *cit, *nam;
	cmd *cmds = N;
	i ncmds = 0, scmds = 0;
	for (;;)
	{
		if (*(nam = readtows(fp)) == '\0')
		{
			free(nam);
			r 0;
		}
		if (strcmp(nam, ";") != 0)
			break;
		free(nam);
		swlcmnt(fp);
	}
	wh (*(cit = readtows(fp)) != '\0' && strcmp(cit, "%") != 0)
	{
		if (strcmp(cit, ";") == 0)
		{
			free(cit);
			swlcmnt(fp);
			continue;
		}
		XPND(cmds, ncmds, scmds);
		if (isdigit(*cit) || (*cit == '-' && isdigit(cit[1])))
		{
			cmds[ncmds].ctyp = CMDNUM;
			cmds[ncmds].arg.num = atoi(cit);
			free(cit);
		}
		l if (*cit == '"' && cit[strlen(cit)-1] == '"'
			&& strlen(cit) > 1)
		{
			cmds[ncmds].ctyp = CMDSTR;
			cmds[ncmds].arg.str = xsnd(cit+1, strlen(cit)-2);
			free(cit);
		}
		l
		{
			cmds[ncmds].ctyp = CMDCALL;
			cmds[ncmds].arg.str = cit;
		}
		ncmds++;
	}
	free(cit);
	XPND(cmds, ncmds, scmds); /* space for CMDEND */
	cmds[ncmds].ctyp = CMDEND;
	r (addwd(nam, cmds), 1);
}
v readfil(t c *fn)
{
	FILE *fp;
	fp = fopen(fn, "r");
	if (fp == N) usrerr("cannot open %s", fn);
	wh (readwd(fp)) ;
	fclose(fp);
}
