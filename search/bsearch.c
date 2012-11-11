#include <stdlib.h>
#include <stdint.h>
inline void * 
bsearch_generic (const void *key, const void *start, size_t size, size_t psize,
   int (*cmp) (const void *, const void *)){
  int steps=31-__builtin_clz(size);
  while(steps--){
    int size2=size/2;
/* do not add something like this - too slow
   if(start[size2]==x) return start;
*/
    if(cmp(key,start+psize*size2)>0){
      size=size2;
    } else {
      start+=psize*size2;
      size-=size2;
    }
  }
  if (cmp(key,start)) return NULL;
  return start;

}
inline void * 
lsearch_generic (const void *key, const void *s, size_t size, size_t psize,
   int (*cmp) (const void *, const void *)){
  void *end; 
  for(end = s+size*psize; s!=end; s+=psize){
    if (!cmp(key,s)) return s;
  }
  return NULL;
}



#define TPCMP(name,tp) \
static inline int name##cmp(tp *a,tp *b){ \
  if(*a>*b) return 1; \
  if(*a<*b) return -1; \
  return 0; \
}

#include "cmp.h"

#define TPCMP(name,type) void* bsearch_##name(const void *key, const void *start, size_t size){\
  return bsearch_generic(key,start,size,sizeof(type),(int (*)(const void *, const void *)) name##cmp);\
} \
void* lsearch_##name(const void *key, const void *start, size_t size){\
  return lsearch_generic(key,start,size,sizeof(type),(int (*)(const void *, const void *)) name##cmp);\
}

#include "cmp.h"


