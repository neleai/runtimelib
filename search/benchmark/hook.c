#include "../../hooks.h"



void *
bsearch2 (const void *key, const void *base, size_t nmemb, size_t size,
   int (*compar) (const void *, const void *))
{
  size_t l, u, idx;
  const void *p;
  int comparison;

  l = 0;
  u = nmemb;
  while (l < u)
    {
      idx = (l + u) / 2;
      p = (void *) (((const char *) base) + (idx * size));
      comparison = (*compar) (key, p);
      if (comparison < 0)
  u = idx;
      else if (comparison > 0)
  l = idx + 1;
      else
  return (void *) p;
    }

  return NULL;
}


char* y;
const int variants_no=1;
static void const * const variants[]={bsearch2};
void *
bsearch (const void *key, const void *base, size_t nmemb, size_t size,
   int (*compar) (const void *, const void *)){
  char * x=base;
  int r = nmemb;
  START_MEASURE(bsearch)
  void * f=bsearch2(key,base,nmemb,size,compar);
  END_MEASURE(bsearch)
  return f;
}

