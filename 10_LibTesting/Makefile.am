
SUBDIRS = src tests

demo:	all
	./src/vector

checklog:	check
	cat tests/*.log

gcov:	check
	$(MAKE) $(MAKEFLAGS) -C src gcov
