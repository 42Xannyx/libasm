.global ft_strlen
.intel_syntax noprefix

ft_strlen:
	mov rax, 0

l1:
	cmp byte ptr [rdi + rax], 0
	je  end
	inc rax
	jmp l1

end:
	ret
