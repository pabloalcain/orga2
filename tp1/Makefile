CC=c99
CFLAGS=-Wall -Wextra -pedantic -O0 -ggdb -lm
OBJS=lista_c.o lista_asm.o
TESTOBJS=tester.o
NASM=nasm
NASMFLAGS=-f elf64 -g -F DWARF

default: main

main: $(OBJS)

tester: $(TESTOBJS) $(OBJS)

%.o: %.asm
	$(NASM) $(NASMFLAGS) $< -o $@

all: tester main

clean:
	rm -f *.o
	rm -f main tester
	rm -f salida.caso?.txt
