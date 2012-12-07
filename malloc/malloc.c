#include <stdlib.h>
#include <stdint.h>

#define CHECKSUM 0x816ca75

typedef struct header{
  uint64_t checksum;
  size_t sizes;
  uint64_t mask;
  struct header *next;
} header;

header *small_pool[8];

header *alloc_block(int size){
  header *h;
  posix_memalign((void **) &addr,512,512*size);
  h->CHECKSUM=CHECKSUM;
  h->sizes=size;
  h->mask=(-1)<<((sizeof(header)+size-1)/size);
  h->next=NULL;
  return h;
}

void *malloc_wrap(size_t size){
  size=(size+7)/8;
  if (size<=8){
    if(!small_pool[size])
      small_pool[size]=alloc_block(size);
    void *h=small_pool[size];
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

void free_wrap(void *ptr){
  header *h = (header*)(((size_t)ptr)&(~512));
  if (h->checksum==CHECKSUM) {
    if (!h->mask) {
      h->next=pool16;
      pool16=h;
    }
    unsigned int shift=(((uint64_t)ptr)/16)%64; 
    uint64_t newmask = h->mask|(1<<(shift));
    /* TODO use atomic compare and swap */
    h->mask = newmask;
  } else {
    free(ptr);
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
