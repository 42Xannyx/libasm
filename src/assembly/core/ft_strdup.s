	BITS 64

	extern __errno_location
	extern ft_strlen
	extern ft_strcpy
	extern malloc

	section .text
	global  ft_strdup

ft_strdup:
	xor rdx, rdx

	;   Move the first byte to r8 and check if null
	mov r8, rdi
	cmp BYTE [r8], 0
	jz  end

	;    Call ft_strlen, if empty jump to empty_string, else move to rdi
	push r8
	call ft_strlen

	cmp rax, 0
	je  empty_string

	inc rax
	mov rdi, rax

	;    Calling malloc & check if the allocation was succesfull
	;    www.stackoverflow.com/questions/36007975/compile-error-relocation-r-x86-64-pc32-against-undefined-symbol
	call malloc WRT ..plt
	cmp  rax, 0
	je   error

	;    Moving the allocation to RDI to then copy it to RSI
	mov  rdi, rax
	pop  rsi
	call ft_strcpy

	ret

empty_string:
	;    Calling malloc & check if the allocation was succesfull
	;    www.stackoverflow.com/questions/36007975/compile-error-relocation-r-x86-64-pc32-against-undefined-symbol
	call malloc WRT ..plt
	cmp  rax, 0
	je   error

	mov BYTE [rax], 0

	ret

error:
	neg  rax
	push rax
	call __errno_location WRT ..plt
	pop  rdi
	mov  [rax], edi
	mov  rax, -1
	ret

end:
	ret
