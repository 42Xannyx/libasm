BITS 64

extern ___error
global _ft_read

_ft_read:
	mov rax, 0
  syscall
  ret
