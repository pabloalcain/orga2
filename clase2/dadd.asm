global dadd
dadd:
  push rbp
  mov rbp, rsp
  addsd XMM0, XMM1

  pop rbp
  ret
