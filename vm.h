extern stk *sk, *rsk;
void addbltn(char *nam, void (*fun)(void));
void addwd(char *nam, cmd *cmds);
void initvm(void);
void callwd(const char *wdnam);
