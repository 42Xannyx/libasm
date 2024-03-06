BITS 64

extern ___error
global _ft_write

_ft_write:
	mov rax, 1
  syscall
  ret
