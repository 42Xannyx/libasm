	BITS 64

	section .text
	global  ft_list_size

	; rdi == 't_list *'

ft_list_size:
	;   Reset rax
	xor rax, rax

l1:
	;   Check if null, if not continue
	cmp rdi, 0
	je  end

	;   *next is 8 bytes. So we go to the next 8 bytes to find the next pointer
	mov rdi, [rdi + 8]
	inc rax

	jmp l1

end:
	ret
