/*Fast hash implementation that uses sse.*/
/* keys are integers. Values should contain pointer to actual data. */
#include <stdint.h>
typedef struct {
  int *k;
  void **v;
  long size,capa;
} hash_s;

hash_s* hash_init();
void ** hash_add (hash_s* h,int k);
void ** hash_find(hash_s* h,int k);
void   hash_rm  (hash_s* h ,int k);

