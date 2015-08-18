section .data
  msg: DB 'en 10 me voy ... 9', 10
  largo EQU $ - msg
  endl: DB 10
  digit: DQ 34

section .text
global _start

_start:
  mov esi, 10
  loop:
    mov rax, 4
    mov rbx, 1
    mov rcx, msg
    mov rdx, largo
    int 128

    dec byte [msg+largo-2]
    dec esi
    cmp esi, 0
  jnz loop
  mov rax, 1
  mov rbx, 0
  int 128
