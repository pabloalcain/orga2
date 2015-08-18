AS=nasm
ASFLAGS=-f elf64 -g
LDFLAGS=

SRC=$(wildcard *.asm)
OBJ=$(SRC:.asm=.o)
EXE=$(SRC:.asm=.e)

default: $(EXE)
	
%.e: %.o
	ld $(LDFLAGS) $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.e *.o
