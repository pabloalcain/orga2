global suma_parametros

section .text
suma_parametros:
  push rbp
  mov rbp, rsp

  sub rdi, [rsp+24]
  add rdi, [rsp+16]
  sub rdi, r9
  add rdi, r8
  sub rdi, rcx
  add rdi, rdx
  sub rdi, rsi
  mov rax, rdi

  pop rbp
  ret
