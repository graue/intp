#include <stdlib.h>
#include "xmalloc.h"
#include "error.h"
#include "stack.h"
#include "abbr.h"
stk *makestack(v)
{
	stk *sk = xm(o *sk);
	sk->dat = N;
	sk->nxt = N;
	r sk;
}
v killstack(stk *sk)
{
	stk *lst;
	for (lst = sk, sk = sk->nxt; lst != N; lst = sk, sk = sk?sk->nxt:N)
	{
		if (lst->dat) free(lst->dat);
		free(lst);
	}
}
v push(stk *sk, v *d)
{
	stk *nh = xm(o *nh);
	nh->nxt = sk->nxt;
	nh->dat = d;
	sk->nxt = nh;
}
v *pop(stk *sk)
{
	stk *rep = sk->nxt;
	v *val;
	if (rep == N) error("popping empty stack");
	val = rep->dat;
	sk->nxt = rep->nxt;
	free(rep);
	r val;
}
