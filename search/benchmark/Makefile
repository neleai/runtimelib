HOOK_NAME = bsearch.prof
all:
	gcc -O3 -g -I. ../bsearch.s  bsearch_libc.c hook.c -DHOOK_NAME=\"${HOOK_NAME}\" -shared -o hook.so -fPIC -lm
	gcc -O3 -g -I. test.c -DHOOK_NAME=\"${HOOK_NAME}\" -o test
	dd if=/dev/zero of=${HOOK_NAME} count=100 2> /dev/null
	chmod a+rw ${HOOK_NAME}
	LD_PRELOAD=./hook.so ./test
	gcc -g -I. report.c  ../bsearch.s  bsearch_libc.c  -DHOOK_NAME=\"${HOOK_NAME}\" -lm -o report
	./report > html/x
	cd html; sh x > result.html
