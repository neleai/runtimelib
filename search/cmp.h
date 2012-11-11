#ifndef TPCMP
#include <stdint.h>
#define TPCMP(name,tp) \
static inline int name##cmp(tp *a,tp *b){ \
  if(*a>*b) return 1; \
  if(*a<*b) return -1; \
  return 0; \
}
#endif

TPCMP(int,int)
TPCMP(long,long)
TPCMP(uint16,uint16_t)
TPCMP(uint32,uint32_t)
TPCMP(uint64,uint64_t)


TPCMP(uint,unsigned int)
TPCMP(ulong,unsigned long)


TPCMP(float,float)
TPCMP(double,double)

#undef TPCMP
