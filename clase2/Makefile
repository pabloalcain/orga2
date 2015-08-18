AS=nasm
ASFLAGS=-f elf64 -g -Wall
LDFLAGS=

CC=gcc
CFLAGS=-O0 -g -Wall

default: add_integers.e add_doubles.e imprimir.e sumar.e

sumar.e: sumar_c.o suma_parametros_a.o
	gcc $(LDFLAGS) $^ -o $@
	
imprimir.e: imprimir_c.o imprime_parametros_a.o
	gcc $(LDFLAGS) $^ -o $@
	
add_doubles.e: add_doubles_c.o dadd_a.o
	gcc $(LDFLAGS) $^ -o $@

add_integers.e: add_integers_c.o iadd_a.o
	gcc $(LDFLAGS) $^ -o $@

%_c.o: %.c
	gcc $(CFLAGS) $< -c -o $@

%_a.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.e *.o
