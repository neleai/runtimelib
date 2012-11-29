#include <stdlib.h>
#include <stdint.h>

#define CHECKSUM 0x816ca75

typedef struct header{
  uint64_t checksum;
  size_t sizes;
  uint64_t mask;
  struct header *next;
} header;

header *pool16;

void *malloc_wrap(size_t size){
  size=(size+15)&(~15); /*Align request to 16 bytes*/
  if(size==16){
    if(!pool16) {
      posix_memalign((void**)&pool16,1024,1024);
      pool16->checksum=CHECKSUM;
      pool16->sizes=16;
      pool16->mask=(-1)<<(sizeof(header)/16);
      pool16->next=NULL;
    }
    uint64_t mask=pool16->mask;
    int shift=__builtin_ctz(mask);
    uint64_t newmask=mask-(1<<shift);
    
    /* TODO use atomic compare and swap */
    pool16->mask = newmask;
    void *p=((void*) pool16)+shift*16;
    if(!pool16->mask) pool16=pool16->next;
    return p;
  } else return malloc(size);
}

void free_wrap(void *ptr){
  header *h = (header*)(((size_t)ptr)&(~1023));
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
