#include "struct.h"

void big_free();

static __thread void ** free_buffer;
static __thread long free_buffer_no,free_buffer_size;

void thread_init(){
  free_buffer      = (void **) malloc_wrap(64*sizeof(void*));
  free_buffer_no   = 0; 
  free_buffer_size = 0;
}
void thread_fini(){
  big_free();
  free_internal(free_buffer);
}

void free_wrap(void *x){
  free_buffer[free_buffer_no]= x;
  free_buffer_no++;
  // free_buffer_size+=alloc_size(x);

  // TODO Merge adjacent free requests.

  if(free_buffer_no>=64 || free_buffer_size >= 1<<20 )
    big_free();
}


void big_free(){ int i;
  // lock
  for(i=0;i<free_buffer_no;i++){
    free_internal(free_buffer[i]);
  }
  // unlock
}


void free_internal(void *ptr){
  header *h = (header*)(((size_t)ptr)&(~512));
  if (h->checksum==CHECKSUM) {
    if (!h->mask) {
      h->next=small_pool[h->size];
      small_pool[h->size]=h;
    }
    unsigned int shift=(((uint64_t)ptr)/16)%64; 
    uint64_t newmask = h->mask|(1<<(shift));
    /* TODO use atomic compare and swap */
    h->mask = newmask;
  } else {
    free(ptr);
  }
}


