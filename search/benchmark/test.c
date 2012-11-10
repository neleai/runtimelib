#include "../cmp.h"
static int r_seed;
int ary[1000001];

int main(){int i,j,k,no;
  for(i=0;i<1000000;i++)
    ary[i]=i;
  for(i=0;i<1000000;i++){
    no=rand_r(&r_seed)%1000000; 
    k=no ? rand_r(&r_seed)%no : 0;
    bsearch(&k,ary,no,sizeof(int),intcmp);
  }
  return 0;
}
