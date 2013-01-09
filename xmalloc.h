#include <stddef.h>
void *xm(size_t sz);
void *xr(void *p, size_t sz);
char *xsnd(const char *sr, int n);
#define xsd(sr) xsnd(sr, strlen(sr))
void *xpnd(void *p, int nit, int *sit, size_t sz);
#define XPND(p, num, spc) (p = xpnd(p, num, &spc, sizeof *p))
