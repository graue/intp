#include "error.h"
#include "stack.h"
#include "code.h"
#include "vm.h"
#include "vobj.h"
#include "builtin.h"
#include "abbr.h"
/* arithmetic */
#define INFIX(sym, nam)				\
s v nam(v)					\
{						\
	vobj *i1 = pop(sk);			\
	vobj *i2 = pop(sk);			\
	VERIFY(i1, VNUM);			\
	VERIFY(i2, VNUM);			\
	i2->vl.num = i2->vl.num sym i1->vl.num;	\
	killvj(i1);				\
	push(sk, i2);				\
}
#define ONEARG(sym, nam)		\
s v nam(v)				\
{					\
	vobj *ij = pop(sk);		\
	VERIFY(ij, VNUM);		\
	ij->vl.num = sym ij->vl.num;	\
	push(sk, ij);			\
}
INFIX(+, ADD)	INFIX(-, SUB)	INFIX(*, MUL)	INFIX(/, DIV)
INFIX(%, MOD)	INFIX(&&, AND)	INFIX(||, OR)	INFIX(^, XOR)
INFIX(&, BAND)	INFIX(|, BOR)	INFIX(<, LT)	INFIX(>, GT)
INFIX(<=, LE)	INFIX(>=, GE)	INFIX(!=, NE)	INFIX(==, EQ)
ONEARG(!, NOT)	ONEARG(-, NEG)	ONEARG(~, COMPL)
struct bn { c *nam; v (*fun)(v); } rthbltns[] =
{
	{"+",	ADD},	{"-",	SUB},	{"*",	MUL},	{"/",	DIV},
	{"MOD",	MOD},	{"&&",	AND},	{"||",	OR},	{"^",	XOR},
	{"&",	BAND},	{"|",	BOR},	{"<",	LT},	{">",	GT},
	{"<=",	LE},	{">=",	GE},	{"!=",	NE},	{"==",	EQ},
	{"!",	NOT},	{"~",	COMPL},	{"NEG",	NEG},
	{N, N}
};
v regnum(v)
{
	struct bn *it = rthbltns;
	for (; it->nam != N; it++)
		addbltn(it->nam, it->fun);
}
