#include "stack.h"
#include "code.h"
#include "vm.h"
#include "vobj.h"
#include "builtin.h"
#include "abbr.h"
/* stack manipulation */
s v DROP(v) { killvj(pop(sk)); }
s v SWAP(v)
{
	v *v1 = pop(sk);
	v *v2 = pop(sk);
	push(sk, v1);
	push(sk, v2);
}
s v DUP(v)
{
	v *val = pop(sk);
	push(sk, val);
	push(sk, vjdup(val));
}
s v SWSTK(v)
{
	stk *tmp = sk;
	sk = rsk;
	rsk = tmp;
}
s v SHOVE(v) { push(rsk, pop(sk)); }
v regstk(v)
{
	BLTN(DROP);	BLTN(SWAP);	BLTN(DUP);
	BLTN(SWSTK);	BLTN(SHOVE);
}
