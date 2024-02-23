.global ft_write
.intel_syntax noprefix

ft_write:
	mov rax, 1
	mov rcx, 0

l1:
	mov rdi, rdi
	cmp byte ptr [rsi + rcx], 0
	cmp rcx, rdx
	jge end
	inc rcx

	jmp l1

end:
	syscall
	ret
