BITS 64

extern ___error
global ft_read

ft_read:
	mov rax, 0
  syscall
  ret
