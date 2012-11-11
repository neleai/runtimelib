#include "../../hooks.h"


void *bsearch_libc();
void *bsearch_generic();

char* y;
const int variants_no=2;
static void const * const variants[]={ bsearch_libc , bsearch_generic };
static char* variant_names[]=        {"bsearch_libc","bsearch_generic"};
static char* variant_color[]=        {"red"         ,"blue"           };          
void *
bsearch (const void *key, const void *base, size_t nmemb, size_t size,
   int (*compar) (const void *, const void *)){
  char * x=base;
  int r = nmemb ? log(nmemb)/log(2) : 0;
  int fno = rand()%2;
  START_MEASURE(bsearch)
  void * f=((void * (*)())variants[fno])(key,base,nmemb,size,compar) ;
  END_MEASURE(bsearch)
  return f;
}

