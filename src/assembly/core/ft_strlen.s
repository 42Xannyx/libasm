BITS 64

global ft_strlen

ft_strlen:
	mov rax, 0

l1:
	cmp BYTE [rdi + rax], 0
	je  end
	inc rax
	jmp l1

end:
	ret
