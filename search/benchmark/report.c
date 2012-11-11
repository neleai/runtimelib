#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/file.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "hook.c"


int main(){ int i,j;
  char *fname = HOOK_NAME;
  FILE *fi = fopen(fname,"r+");
	void *sm= mmap(NULL,sizeof(disk_layout),PROT_READ|PROT_WRITE,MAP_SHARED,fileno(fi),0);
  if (sm){
		disk_layout *lay=sm;
#define GNUPLOT_SET "echo ' reset\n set terminal png\n set xlabel \"blocks\"\n set ylabel \"number of calls\""
		
		#define REPORT(fn) \
		printf("\necho '<h1>" #fn "</h1>'\n");\
		prof_str *smp = &(lay->fn);\
		printf("echo '<br>number of calls<br>'\n");\
    for(i=0;i<variants_no;i++){\
		printf("echo '");\
		for(j=1;j<32;j++) printf("%i %11d\n",j,smp->cnt[i][0][j]);\
		printf("'> " #fn "%i_1\n " ,i);}\
    printf(GNUPLOT_SET "\n plot");\
    for(i=0;i<variants_no;i++){\
      printf( "\"" #fn "%i_1\" with lines lc rgb \"%s\" title \"%s\",",i,variant_color[i],variant_names[i]);\
    }\
    printf("0 '| gnuplot > " #fn "_1.png\n");\
		printf("echo '<img src=" #fn "_1.png></img>'\n ");\
		printf("echo '<br>average time<br>'\n");\
	    for(i=0;i<variants_no;i++){\
		printf("echo '");\
	for(j=1;j<32;j++) printf("%i %11d\n",j,smp->time[i][0][j]/(smp->cnt[i][0][j]+1));\
		printf("'> " #fn "%i_1\n " ,i);}\
   printf(GNUPLOT_SET "\n plot");\
    for(i=0;i<variants_no;i++){\
      printf( "\"" #fn "%i_1\" with lines lc rgb \"%s\" title \"%s\",",i,variant_color[i],variant_names[i]);\
    }\
    printf("0 '| gnuplot > " #fn "_1t.png\n");\
		printf("echo '<img src=" #fn "_1t.png></img>'\n");\
  if (b_##fn & B_SHOW_ALIGN){\
	printf("\necho \"");\
		for(i=0;i<64;i++) {\
	 		printf("%i %11d\n",i,smp->aligns[i]);\
		}\
		printf("\">" #fn "_alignment\n");\
		printf("" GNUPLOT_SET "\n set xtics 8\n set xlabel \"alignment\"\n plot \"" #fn "_alignment\" with lines'| gnuplot > " #fn "_alignment.png\n");\
		printf("echo '<br>alignment <br> <img src=" #fn "_alignment.png></img><br>'\n");\
    printf("echo '<br> Calls aligned to 16 bytes: %f%% <br>'",100*(smp->aligns[0]+smp->aligns[16]+smp->aligns[32]+smp->aligns[48]+0.0)/(smp->success+smp->fail));\
    }\
		printf("\necho \"");\
		for(i=0;i<32;i++) {\
	 		printf("%i %11d\n",i,smp->delay[i]);\
		}\
		printf("\">" #fn "_delay\n");\
		printf("echo '<br>delays between calls<br> <img src=" #fn "_delay.png></img><br>'\n");\
		printf("" GNUPLOT_SET "\n set xlabel \"log(cycles)\" \n  plot \"" #fn "_delay\" with lines'| gnuplot > " #fn "_delay.png\n");\
			printf("echo '<br> success: %11d\n fail:     %11d\n <br>'",smp->success,smp->fail);


		{			REPORT(bsearch);		}
		

  printf("echo '<pre>'\n cat /proc/cpuinfo \n echo '</pre>'");

		munmap(sm,sizeof(disk_layout));
  }
}

