
GENERATES = prog prog-a prog-so README liboutput_static.a liboutput.so
TRASH = *.o *.out
CFLAGS = -Wall -fPIC
Green=\033[0;32m
NC=\033[0m

all: liboutput_static.a liboutput.so prog prog-a prog-so test README

prog: prog.o const.o fun.o

prog-a: prog.o liboutput_static.a
	$(CC) $(CFLAGS) -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	$(CC) $(CFLAGS) -L. $< -loutput -o $@

test: test0 test1 test3

test0: prog prog-a prog-so
	@echo "${Green}----------Start test<without parameters>----------${NC}"
	./prog > $@_prog.out 2>&1
	./prog-a > $@_prog-a.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > $@_prog-so.out 2>&1
	cmp $@_prog.out $@_prog-a.out
	cmp $@_prog.out $@_prog-so.out
	@echo "${Green}----------Test<without parameters> pass----------${NC}"

test1: prog prog-a prog-so
	@echo "${Green}----------Start test<with 1 parameters>----------${NC}"
	./prog 1 > $@_prog.out 2>&1
	./prog-a 1 > $@_prog-a.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so 1 > $@_prog-so.out 2>&1
	cmp $@_prog.out $@_prog-a.out
	cmp $@_prog.out $@_prog-so.out
	@echo "${Green}----------Test<with 1 parameters> pass----------${NC}"

test3: prog prog-a prog-so
	@echo "${Green}----------Start test<with 3 parameters>----------${NC}"
	./prog 1 2 3 > $@_prog.out 2>&1
	./prog-a 1 2 3 > $@_prog-a.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so 1 2 3 > $@_prog-so.out 2>&1
	cmp $@_prog.out $@_prog-a.out
	cmp $@_prog.out $@_prog-so.out
	@echo "${Green}----------Test<with 3 parameters> pass----------${NC}"


README: prog
	./$< 2> $@

fun.o:  outlib.h
prog.o:  outlib.h

.SECONDARY:	fun.o const.o
.INTERMEDIATE:	liboutput_static.a(fun.o const.o)

liboutput_static.a: liboutput_static.a(fun.o const.o)

liboutput.so: fun.o const.o
	$(CC) -shared $^ -o $@

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
