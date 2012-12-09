
#include "struct.h"

header *alloc_block(int size){
  header *h;
  posix_memalign(((void **) &h),512,512*size);
  h->checksum=CHECKSUM;
  h->size=size;
  h->mask=(-1)<<((sizeof(header)+size-1)/size);
  h->next=NULL;
  return h;
}

void *malloc_wrap(size_t size){
  size=(size+7)/8;
  if (size<=8){
    if(!small_pool[size])
      small_pool[size]=alloc_block(size);
    header *h=small_pool[size];
    uint64_t mask=h->mask;
    int shift=__builtin_ctz(mask);
    uint64_t newmask=mask-(1<<shift);
    h->mask=newmask;
    if(1){//TODO atomic operation
      if(!h->mask)
        small_pool[size]=h->next;
      void *p= ((void *)h)+8*size*shift;
      return p;
    }
  }else{
  }
}

int main(){
  void *a;
  void *b;
  a=malloc_wrap(16);
  b=malloc_wrap(16);
  free_wrap(b);
  free_wrap(a);
}
