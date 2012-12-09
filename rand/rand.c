#include <malloc.h>

void aesrand(int *);

int *rand_state; int rand_state_no;
void *initstate(long seed){int i;
  int *r;
  posix_memalign(&r,16,16*8);
  for(i=0;i<32;i++) r[i]=684026525*i*i+985956522*i*seed+713451925;
  rand_state = r;
}


long random(){int i;
  if (rand_state_no>=4*4){
    aesrand(rand_state);
    rand_state_no=0;
  }
  return rand_state[rand_state_no++];
}
