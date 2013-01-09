typedef struct _stacknode
{
	struct _stacknode *nxt;
	void *dat;
} stacknode;
typedef stacknode stk;
stk *makestack(void);
void killstack(stk *sk);
void push(stk *sk, void *d);
void *pop(stk *sk);
