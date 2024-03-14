BITS 64

extern __errno_location

section .text
  global ft_read

ft_read:
	mov rax, 0
  syscall
  cmp rax, 0
  jl error
  ret

error:
  neg rax 
  push rax
  call __errno_location WRT ..plt
  pop rdi
  mov [rax], edi
  mov rax, -1
  ret
