#include "../../hooks.h"

void *intcmp();
void *bsearch_libc();
void *bsearch_generic();
void *bsearch_int();


char* y;
const int variants_no=3;
static void const * const variants[]={ bsearch_libc , bsearch_generic , bsearch_int};
static char* variant_names[]=        {"bsearch_libc","bsearch_generic","bsearch_int"};
static char* variant_color[]=        {"red"         ,"blue"           ,"green"};          
void *
bsearch (const void *key, const void *base, size_t nmemb, size_t size,
   int (*compar) (const void *, const void *)){
  if(compar!=intcmp) return bsearch_generic(key,base,nmemb,size,compar) ;
  char * x=base;
  int r = nmemb ? log(nmemb)/log(2) : 0;
  if (r>63) r = 63;
  int fno = rand()%variants_no;
  START_MEASURE(bsearch)
  void * f=((void * (*)())variants[fno])(key,base,nmemb,size,compar) ;
  END_MEASURE(bsearch)
  return f;
}

