global iadd

section .text
iadd:
  push rbp
  mov rbp, rsp
  add rdi, rsi
  mov rax, rdi

  pop rbp
  ret
