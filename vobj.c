#include <stdlib.h>
#include <string.h>
#include "xmalloc.h"
#include "stack.h"
#include "code.h"
#include "vm.h"
#include "vobj.h"
#include "abbr.h"
vobj *vjfromstr(c *str)
{
	vobj *ds = xm(o *ds);
	ds->vtyp = VSTR;
	ds->vl.str = str;
	r ds;
}
vobj *vjfromnum(i n)
{
	vobj *ds = xm(o *ds);
	ds->vtyp = VNUM;
	ds->vl.num = n;
	r ds;
}
v killvj(vobj *vj)
{
	if (vj->vtyp == VSTR) free(vj->vl.str);
	free(vj);
}
vobj *vjdup(vobj *vj)
{
	vobj *ds = xm(o *ds);
	ds->vtyp = vj->vtyp;
	if (ds->vtyp == VSTR)
		ds->vl.str = xsd(vj->vl.str);
	l
		ds->vl.num = vj->vl.num;
	r ds;
}
