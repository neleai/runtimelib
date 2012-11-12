 typedef struct {
 uint64_t cnt[4][3][64];
 uint64_t time[4][3][64];
 uint64_t needle[4][34];
	uint64_t delay[64];
 uint64_t aligns[64];
 uint64_t success,fail;
 uint64_t start,last;
} prof_str;


typedef struct {
	prof_str bsearch,lsearch;

} disk_layout;

#define B_NEEDLE 1
#define B_REL_ALIGN 2
#define B_SHOW_ALIGN 4
#define B_BYTEWISE_SIZE 8

uint64_t b_bsearch=0;
