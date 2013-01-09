typedef struct
{
	enum
	{
		CMDCALL,
		CMDSTR,
		CMDNUM,
		CMDEND
	} ctyp;
	union
	{
		char *str;
		int num;
	} arg;
} cmd;
typedef struct
{
	char *nam;
	int bltn; /* builtin */
	union
	{
		cmd *cmds; /* ""-call-terminated */
		void (*fun)(void);
	} meat;
} word;
