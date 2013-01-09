#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xmalloc.h"
#include "error.h"
#include "read.h"
#include "asprf.h"
#include "stack.h"
#include "code.h"
#include "vm.h"
#include "vobj.h"
#include "builtin.h"
#include "abbr.h"
/* strings */
s v CONCAT(v) /* "one" "two" -- "onetwo" */
{
	vobj *s1 = pop(sk);
	vobj *s2 = pop(sk);
	c *dst;
	VERIFY(s1, VSTR);
	VERIFY(s2, VSTR);
	dst = xm(strlen(s1->vl.str) + strlen(s2->vl.str) + 1);
	strcpy(dst, s2->vl.str);
	strcat(dst, s1->vl.str);
	killvj(s1);
	killvj(s2);
	push(sk, vjfromstr(dst));
}
s v CHRAT(v) /* "word" 3 -- 'r' (114) */
{
	vobj *vji = pop(sk);
	vobj *vjc = pop(sk);
	c *str = vjc->vl.str;
	VERIFY(vji, VNUM);
	VERIFY(vjc, VSTR);
	if (vji->vl.num < 1 || (z) vji->vl.num > strlen(str))
		error("out of bounds value in CHRAT");
	vji->vl.num = str[vji->vl.num-1];
	push(sk, vji);
	killvj(vjc);
}
s v STR(v)
{
	vobj *vji = pop(sk);
	c *str = xm(2);
	VERIFY(vji, VNUM);
	str[0] = vji->vl.num;
	str[1] = '\0';
	push(sk, vjfromstr(str));
	killvj(vji);
}
s v LEN(v)
{
	vobj *vjc = pop(sk);
	VERIFY(vjc, VSTR);
	push(sk, vjfromnum(strlen(vjc->vl.str)));
	killvj(vjc);
}
s v INPUT(v) { push(sk, vjfromstr(readln())); }
s v PRINT(v) /* "str" -- */
{
	vobj *vjc = pop(sk);
	VERIFY(vjc, VSTR);
	printf("%s", vjc->vl.str);
	killvj(vjc);
}
s v ATOI(v)
{
	vobj *vj = pop(sk);
	VERIFY(vj, VSTR);
	vj->vl.num = atoi(vj->vl.str);
	vj->vtyp = VNUM;
	push(sk, vj);
}
s v ITOA(v)
{
	vobj *vj = pop(sk);
	VERIFY(vj, VNUM);
	asprf(&vj->vl.str, "%d", vj->vl.num);
	vj->vtyp = VSTR;
	push(sk, vj);
}
v regstr(v)
{
	BLTN(CONCAT);	BLTN(CHRAT);	BLTN(ATOI);	BLTN(ITOA);
	BLTN(STR);	BLTN(LEN);	BLTN(INPUT);	BLTN(PRINT);
}
