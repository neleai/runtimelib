#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/file.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "layout.h"

static __inline__ uint64_t rdtsc(void)
{
  uint32_t lo, hi;
/*  __asm__ __volatile__ (
    "        xorl %%eax,%%eax \n"
    "        cpuid"      // serialize
    ::: "%rax", "%rbx", "%rcx", "%rdx");*/
  /* We cannot use "=A", since this would use %rax on x86_64 and return only the lower 32bits of the TSC */
  __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
  return (uint64_t)hi << 32 | lo;
}

disk_layout prof;
__attribute__((destructor)) static void save_cnt(){ int i,j;
  char *fname = HOOK_NAME;
  FILE *fi = fopen(fname,"r+");
	void *sm= mmap(NULL,sizeof(disk_layout),PROT_READ|PROT_WRITE,MAP_SHARED,fileno(fi),0);
  if (sm){
		disk_layout *lay=sm;
		int i;
		uint64_t *  ptr= (uint64_t*)lay;
		uint64_t * mptr= (uint64_t*)&prof;

		for(i=0;i<sizeof(disk_layout)/sizeof(uint64_t);i++)	
			ptr[i]+=mptr[i];
		munmap(sm,sizeof(disk_layout));
  }
}
#define START_MEASURE(fn) prof.fn.start=rdtsc();
#define END_MEASURE(fn)\
	uint64_t ts=rdtsc();\
	if (ts-prof.fn.last<2000000000 && ts-prof.fn.start<2000000){\
	prof.fn.delay[ 63-__builtin_clzl(prof.fn.start-prof.fn.last) ]++;\
  size_t r2= (b_##fn & B_BYTEWISE_SIZE) ? r\
    :((size_t)x+r)/16-((size_t)x)/16+1;\
  prof.fn.cnt[fno][0][r]++;\
	prof.fn.time[fno][0][r]+=ts-prof.fn.start;\
  prof.fn.aligns[(b_## fn & B_REL_ALIGN) ? (x-y)%64 : ((uint64_t) x)%64]++;\
	prof.fn.success++;\
	}\
	prof.fn.last=ts;\
  if (b_##fn & B_NEEDLE){\
  size_t r2=strlen(y);\
  if(r2>=1000) r2=999;\
  prof.fn.needle[2][r2/30]++;\
  if(r2>=100) r2=99;\
  prof.fn.needle[1][r2/3]++;\
  if(r2>=10) r2=9;\
  prof.fn.needle[0][r2]++;\
  }

