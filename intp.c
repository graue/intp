#include "stack.h"
#include "code.h"
#include "vm.h"
#include "error.h"
#include "parse.h"
#include "abbr.h"
i main(i rc, c *rv[])
{
	rc--, rv++;
	if (rc < 1) usrerr("no input files");
	initvm();
	for (; rc > 0; rc--, rv++)
		readfil(*rv);
	callwd("main");
	r 0;
}
