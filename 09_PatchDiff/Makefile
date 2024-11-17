
all: run

run: prog0 prog1 prog2 prog3
	./prog0
	./prog1 17
	./prog2 ' &' 15
	./prog3 1 ' &' 11

prog0: prog.c
	gcc prog.c -o $@

prog1: prog.c 1.patch
	cp prog.c prog_temp1.c
	patch prog_temp1.c < 1.patch
	gcc prog_temp1.c -o $@

prog2: prog.c 1.patch 2.patch
	cp prog.c prog_temp2.c
	patch prog_temp2.c < 1.patch
	patch prog_temp2.c < 2.patch
	gcc prog_temp2.c -o $@

prog3: prog.c
	cp prog.c prog_temp3.c
	patch prog_temp3.c < 1.patch
	patch prog_temp3.c < 2.patch
	patch prog_temp3.c < 3.patch
	gcc prog_temp3.c -o $@

clean:
	rm -f prog0 prog1 prog2 prog3 prog_temp1.c prog_temp2.c prog_temp3.c
