extern printf
global imprime_parametros

section .text
imprime_parametros:
  push rbp
  mov rbp, rsp

  mov rax, 1
  mov rdx, rsi
  mov rsi, rdi
  mov rdi, format
  call printf

  pop rbp
  ret

section .data
  format: DB "%i %f %s", 10, 0
