#include <stdint.h>

#define TPCMP(name,tp) \
static inline int name##cmp(tp *a,tp *b){ \
  if(*a>*b) return 1; \
  if(*a<*b) return -1; \
  return 0; \
}

#include "cmp.h"

#define TPCMP(name,type) void* bsearch_##name(const void *key, const void *start, size_t size){\
  return bsearch_generic(key,start,size,sizeof(type),name##cmp);
}
#include "cmp.h"

inline void * bsearch(const void *key, const void *start, size_t size, size_t psize,
   int (*compar) (const void *, const void *)){

  if ( __builtin_constant_p(compar)){
    #define TPCMP(name,type) if ( psize==sizeof(type) && compar==name##cmp) return bsearch_##name(key,start,size);
    #include "cmp.h"
  }
  return bsearch_generic(key,start,size,psize,compar);
}

