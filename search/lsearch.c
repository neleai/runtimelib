#include <emmintrin.h>
#include <stdlib.h>
typedef __m128i tp_vector;
typedef int tp_scalar;
typedef long tp_mask;
#define LOAD(x) _mm_load_si128((tp_vector *) (x))
#define EQ _mm_cmpeq_epi32
#define OR _mm_or_si128
#define shift_down(x,y) (x)>>(y)
#define shift_up(x,y)   (x)<<(y)

#define PARA sizeof(tp_vector)/sizeof(tp_scalar)
#define BROADCAST(x) _mm_set1_epi32(x)
#define get_mask(x) ((long)_mm_movemask_epi8(x))
static inline tp_mask first_bit(tp_mask x)
{
  return __builtin_ctzl(x)/sizeof(tp_scalar);
}
#define unroll 4
tp_scalar * lsearch_int_sse(tp_scalar *e,tp_scalar *start, size_t no,size_t size,void* compar){size_t i,r;
  tp_mask mask;
  if (!no) return NULL;
  tp_scalar *end  = start+no;
  tp_scalar *s2   = ((size_t)start)&(~(unroll*sizeof(tp_vector)-1));
  tp_scalar *s2end= ((size_t)end-1)&(~(unroll*sizeof(tp_vector)-1));
  tp_vector pe= BROADCAST(*e);
  tp_vector v0,v1,v2,v3;
  v0=EQ(pe,LOAD(s2));
  v1=EQ(pe,LOAD(s2+PARA));
  v2=EQ(pe,LOAD(s2+2*PARA));
  v3=EQ(pe,LOAD(s2+3*PARA));

  mask=get_mask(v0)|(get_mask(v1)<<16)|(get_mask(v2)<<32)|(get_mask(v3)<<48);
  mask= mask & shift_up((long)-1,((long)start));
  if(mask) {
      if(s2!=s2end || mask & shift_down((unsigned long)-1,-((long)end)))
        return s2+first_bit(mask);
  }
  while(s2!=s2end){
    s2+=unroll*PARA;
    v0=EQ(pe,LOAD(s2));
    v1=EQ(pe,LOAD(s2+PARA));
    v2=EQ(pe,LOAD(s2+2*PARA));
    v3=EQ(pe,LOAD(s2+3*PARA));
    if(get_mask(OR(v0,OR(v1,OR(v2,v3))))){
      mask=get_mask(v0)|(get_mask(v1)<<16)|(get_mask(v2)<<32)|(get_mask(v3)<<48);

      if(s2!=s2end || mask & shift_down((unsigned long)-1,-(long)end))
        return s2+first_bit(mask);
    }
  }
  return NULL;
}
