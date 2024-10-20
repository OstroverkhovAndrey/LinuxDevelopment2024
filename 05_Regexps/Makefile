
all: esub

esub: esub.c
	cc $< -Wall -o $@

test: esub
	@./esub '([12]+)(3)' 'q\2q\1q' '3121231123' > esud_test_1_res
	@echo '3121231123' | sed -E 's/([12]+)(3)/q\2q\1q/' > sed_test_1_res
	@if cmp esud_test_1_res sed_test_1_res >/dev/null 2>&1;\
		then echo "TEST 1 PASS";\
		else echo "TEST 1 FAILD";\
	fi
	@./esub '([12]+)(3)' 'q\2\*q\1q' '3121231123' > esud_test_2_res
	@echo '3121231123' | sed -E 's/([12]+)(3)/q\2\*q\1q/' > sed_test_2_res
	@if cmp esud_test_2_res sed_test_2_res >/dev/null 2>&1;\
		then echo "TEST 2 PASS";\
		else echo "TEST 2 FAILD";\
	fi
	@./esub '([12]+)(3)' 'q\2\\q\1q' '3121231123' > esud_test_3_res
	@echo '3121231123' | sed -E 's/([12]+)(3)/q\2\\q\1q/' > sed_test_3_res
	@if cmp esud_test_3_res sed_test_3_res >/dev/null 2>&1;\
		then echo "TEST 3 PASS";\
		else echo "TEST 3 FAILD";\
	fi

clean:
	rm -f esub *_res
