	BITS 64

	section .text
	global  ft_strcpy

	; rdi == dest*
	; rsi == src*

ft_strcpy:
	xor rcx, rcx

l1:
	;   mov src + count to `al`, `al` being a BYTE and then move it to dest
	mov al, [rsi + rcx]
	mov [rdi + rcx], al
	cmp al, 0
	je  end

	inc rcx
	jmp l1

end:
	mov rax, rdi
	ret
