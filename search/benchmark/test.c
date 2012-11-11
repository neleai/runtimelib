#include "../cmp.h"
static int r_seed;
#define SIZE (1<<25)
int ary[SIZE];

int main(){int i,j,k,no,pow;
  for(i=0;i<SIZE;i++)
    ary[i]=i;
  for(i=0;i<100000;i++){
    pow=rand_r(&r_seed)%25; 
    no = rand_r(&r_seed)%(1<<pow);
    k=no ? rand_r(&r_seed)%no : 0;
    bsearch(&k,ary,no,sizeof(int),intcmp);
  }
  return 0;
}
