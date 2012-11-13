#include "../../hooks.h"

void *intcmp();
void *lsearch_int();
void *lsearch_int_sse();

void *bsearch_int();

void *lsearch_generic();
void *bsearch_libc();
void *bsearch_generic();

char* y;
const int variants_no=2;
static void const * const variants[]={  bsearch_int , lsearch_int_sse};
static char* variant_names[]=        { "bsearch_int","lsearch_int_sse"};
static char* variant_color[]=        { "blue"       ,"red"};          
void *
lsearch (const void *key, const void *base, size_t nmemb, size_t size,
   int (*compar) (const void *, const void *)){
  if(compar!=intcmp) return lsearch_generic(key,base,nmemb,size,compar) ;
  char * x=base;
  int r = nmemb/30;
  if (r>63) r=63;
  int fno = rand()%variants_no;
  START_MEASURE(bsearch)
  void * f=((void * (*)())variants[fno])(key,base,nmemb,size,compar) ;
  END_MEASURE(bsearch)
  return f;
}

