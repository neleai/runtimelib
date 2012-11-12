HOOK_NAME = bsearch.prof
all:
	gcc -O3 -g -I. ../bsearch.s  bsearch_libc.c hook.c -DHOOK_NAME=\"${HOOK_NAME}\" -shared -o libhook.so -fPIC -lm
	gcc -O3 -g -I. test.c -DHOOK_NAME=\"${HOOK_NAME}\"  -L. -lhook -o test
	dd if=/dev/zero of=${HOOK_NAME} count=200 2> /dev/null
	chmod a+rw ${HOOK_NAME}
	LD_LIBRARY_PATH=. ./test
	gcc -O3 -g -I. report.c  ../bsearch.s  bsearch_libc.c  -DHOOK_NAME=\"${HOOK_NAME}\" -lm -o report
	./report > html/x
	cd html; sh x > result.html
lsearch:
	gcc -O3 -g -I. ../bsearch.s ../lsearch.s bsearch_libc.c lsearch_hook.c -DHOOK_NAME=\"${HOOK_NAME}\" -shared -o liblsearch_hook.so -fPIC -lm
	gcc -O3 -g -I. lsearch_test.c -DHOOK_NAME=\"${HOOK_NAME}\"  -L. -llsearch_hook -o lsearch_test
	dd if=/dev/zero of=${HOOK_NAME} count=200 2> /dev/null
	chmod a+rw ${HOOK_NAME}
	LD_LIBRARY_PATH=. ./lsearch_test
	gcc -O3 -g -I. ../bsearch.s ../lsearch.s bsearch_libc.c lsearch_report.c -DHOOK_NAME=\"${HOOK_NAME}\" -o lsearch_report -fPIC -lm
	./lsearch_report > html/x
	cd html; sh x > result.html
