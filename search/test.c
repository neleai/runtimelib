#include <emmintrin.h>
int ary[1000000];
int* least_upper(int x,int *start,int size){
  int steps=31-__builtin_clz(size);
  while(steps--){
    int size2=size/2;
/* do not add something like this - too slow
   if(start[size2]==x) return start;
*/
    if(start[size2]>x){
      size=size2;
    } else {
      start+=size2;
      size-=size2;
    }
  }
  return start;
}

int main(int argc,int **argv){int i,j;
  void fns[1]= { least_upper };
  test(
}

void test(int fno, void *fns){
}
