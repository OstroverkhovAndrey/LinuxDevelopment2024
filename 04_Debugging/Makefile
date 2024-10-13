
range: range.c
	cc $< -O0 -g -Wall -o $@

test: range
	@gdb --batch --quiet --command=gdb_script_1 --args ./range | grep @@@ > gdb_res_1
	@if cmp gdb_cor_1 gdb_res_1 >/dev/null 2>&1;\
		then echo "TEST 1 PASS";\
		else echo "TEST 1 FAILD";\
	fi
	@gdb --batch --quiet --command=gdb_script_2 --args ./range | grep @@@ > gdb_res_2
	@if cmp gdb_cor_2 gdb_res_2 >/dev/null 2>&1;\
		then echo "TEST 2 PASS";\
		else echo "TEST 2 FAILD";\
	fi

clean:
	rm -f range gdb_res_1 gdb_res_2
