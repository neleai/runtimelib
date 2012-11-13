#include <stdlib.h>
#include "sse.h"
#include "hash.h"

#define IN_BLOCK 64/sizeof(int)
/*while there is place in block we can delete elements normally by setting key to VACANT.
  when block becomes full we cannot delete and use PLACEHOLDER.*/
#define VACANT      0xdeadbeef
#define PLACEHOLDER 0x600Dbeef

hash_s* hash_init(){int i;
  hash_s *h=malloc(sizeof(hash_s));
  h->capa=1024;
  h->size=0;
  h->k=malloc(h->capa*sizeof(int));
  h->v=malloc(h->capa*sizeof(void **));
  for(i=0;i<h->capa;i++){ h->k[i]=VACANT; h->v[i]=NULL;}
}
/**/


/*find index of occurence of k or first empty place*/
int _hash_find(hash_s*h, int k){ int i;
  int hash= k&(h->capa-1)&(~(IN_BLOCK-1));
  while(1){
    int m=find64(hash,h->k+hash);
    if (m) return h->v+hash+first_bit(m);
    if (h->k[hash+IN_BLOCK-1]==VACANT){
      return h->v+hash+first_bit(find64(VACANT,h->k+hash));
    }
    hash+=IN_BLOCK;
  }
}
void ** hash_add (hash_s* h,int k){
  int no=_hash_find(h,k);
  h->k[no]=k;
  return h->v+no;
}

void ** hash_find(hash_s* h,int k){
  int no=_hash_find(h,k);
  if(h->k[no]==k) return  h->v+no;
  return NULL;
}

void   hash_rm  (hash_s* h ,int k){
  int hash= k&(h->capa-1)&(~(IN_BLOCK-1));
  while(1){
    int m=find64(hash,h->k+hash);
    if (m){ 
      h->k[hash+first_bit(m)]=h->k[hash+IN_BLOCK-1];
      h->v[hash+first_bit(m)]=h->v[hash+IN_BLOCK-1];
      if (h->k[hash+IN_BLOCK-1]!=VACANT)
        h->k[hash+IN_BLOCK-1]=PLACEHOLDER;
      return;
    }
    if (h->k[hash+IN_BLOCK-1]==VACANT)
      return;
    hash+=IN_BLOCK;
  }

}



