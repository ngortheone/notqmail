#ifndef ALLOC_H
#define ALLOC_H

#include <stdlib.h>

#define alloc(x) malloc(x)
#define alloc_free(x) free(x)

/*
 * This functions should not be used in any new code. It is provided so that
 * external patches that rely on it's presence still work correctly.
 */
#ifndef DONT_PROVIDE_OBSOLETE
static inline int alloc_re(void **x, unsigned int m, unsigned int n)
{
  void *y = realloc(*x, n);
  (void)m;
  if (y != NULL)
    *x = y;
  return !!y;
}
#endif

#endif
