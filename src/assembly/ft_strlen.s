BITS 64

extern ___error
global ft_strlen

ft_strlen:
	mov rax, 0

l1:
	cmp byte ptr [rdi + rax], 0
	je  end
	inc rax
	jmp l1

end:
	ret
