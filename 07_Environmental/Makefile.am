
CFLAGS = -Wall -O0 -g -I. 

bin_PROGRAMS=rhasher

rhasher_SOURCES=src/rhasher.c

TESTS=test.sh

test.sh:
	echo 'test "`./rhasher < /dev/null 2>&1`" = ">>>"' > $@
	chmod +x $@

gitclean:
	git clean -df
