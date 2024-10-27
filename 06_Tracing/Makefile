
move: move.c
	gcc $< -Wall -o $@

remove.so: remove.c
	gcc -shared -o remove.so remove.c

test: move remove.so
	@echo "1234567890" > in_test
	@./move in_test out_test > /dev/null 2>&1 || true
	@if ! test -f in_test && test -f out_test;\
		then echo "TEST 1 PASS";\
		else echo "TEST 1 FAILD";\
	fi
	@echo "1234567890" > in_test
	@strace -foo -e fault=openat:error=EACCES:when=1 ./move in_test out_test > /dev/null 2>&1 || true
	@if (cat o | grep 'exited with 0' > /dev/null 2>&1);\
		then echo "TEST 2 PASS";\
		else echo "TEST 2 FAILD";\
	fi
	@echo "1234567890" > in_test
	@strace -foo -e fault=openat:error=EACCES:when=2 ./move in_test out_test > /dev/null 2>&1 || true
	@if (cat o | grep 'exited with 0' > /dev/null 2>&1);\
		then echo "TEST 3 PASS";\
		else echo "TEST 3 FAILD";\
	fi
	@echo "1234567890" > in_test
	@strace -foo -e fault=openat:error=EACCES:when=3 ./move in_test out_test > /dev/null 2>&1 || true
	@if (cat o | grep 'exited with 13' > /dev/null 2>&1);\
		then echo "TEST 4 PASS";\
		else echo "TEST 4 FAILD";\
	fi
	@echo "1234567890" > in_test
	@strace -foo -e fault=openat:error=EACCES:when=4 ./move in_test out_test > /dev/null 2>&1 || true
	@if (cat o | grep 'exited with 13' > /dev/null 2>&1);\
		then echo "TEST 5 PASS";\
		else echo "TEST 5 FAILD";\
	fi
	@echo "1234567890" > in_test
	@strace -foo -e fault=openat:error=EACCES:when=5 ./move in_test out_test > /dev/null 2>&1 || true
	@if (cat o | grep 'exited with 0' > /dev/null 2>&1);\
		then echo "TEST 6 PASS";\
		else echo "TEST 6 FAILD";\
	fi
	@echo "1234567890" > PROTECT
	@LD_PRELOAD=`pwd`/remove.so ./move PROTECT out_test > /dev/null 2>&1
	@if test -f PROTECT && test -f out_test;\
		then echo "TEST 7 PASS";\
		else echo "TEST 7 FAILD";\
	fi

clean:
	rm -f move o in_test out_test PROTECT remove.so
