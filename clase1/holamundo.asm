section .data
  msg: DB 'Hola Mundo', 10
  largo EQU $ - msg
	
section .text
global _start

_start:
  mov rax, 4
  mov rbx, 1
  mov rcx, msg
  mov rdx, largo
  int 128
  mov rax, 1
  mov rbx, 0
  int 128
