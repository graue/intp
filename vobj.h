typedef struct
{
	enum { VSTR, VNUM } vtyp;
	union { char *str; int num; } vl;
} vobj;
vobj *vjfromstr(char *str);
vobj *vjfromnum(int n);
void killvj(vobj *vj);
vobj *vjdup(vobj *vj);
