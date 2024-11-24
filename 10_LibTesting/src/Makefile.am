
CFLAGS = -ansi -pedantic -Wall -Wextra
if COND_GCOV
CFLAGS  += -std=c99 -O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS  += -std=c99 -O3 -g3
endif

lib_LTLIBRARIES = libvector.la
bin_PROGRAMS=vector

vector_LDADD = libvector.la

gcov:
	gcov -o .libs libvector -t -k -b | egrep -v '[[:digit:]]:[ /][*]'
