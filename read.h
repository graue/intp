#include <stdio.h>
char *readstr(FILE *fp, const char *trms, int sq);
#define readtows(fp) readstr(fp, " \n\t\r\v\f", 1)
#define readln() readstr(stdin, "\n", 0)
