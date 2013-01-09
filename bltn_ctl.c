#include "error.h"
#include "stack.h"
#include "code.h"
#include "vm.h"
#include "parse.h"
#include "vobj.h"
#include "builtin.h"
#include "abbr.h"
/* control flow & misc. */
s v IFTE(v) /* num "wordtrue" "wordfalse" -- (calls one) */
{
	vobj *vjf = pop(sk);
	vobj *vjt = pop(sk);
	vobj *vjb = pop(sk);
	VERIFY(vjf, VSTR);
	VERIFY(vjt, VSTR);
	VERIFY(vjb, VNUM);
	if (vjb->vl.num) callwd(vjt->vl.str);
	l		 callwd(vjf->vl.str);
	killvj(vjf);
	killvj(vjt);
	killvj(vjb);
}
s v INCL(v)
{
	vobj *vjc = pop(sk);
	VERIFY(vjc, VSTR);
	readfil(vjc->vl.str);
	killvj(vjc);
}
v regctl(v) { BLTN(IFTE); BLTN(INCL); }
