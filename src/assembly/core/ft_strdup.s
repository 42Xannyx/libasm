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
	cmp BYTE [rdi], 0
	je  empty_string

	;    Call ft_strlen, if empty jump to empty_string, else move to rdi
	push rdi
	call ft_strlen

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
	mov rdi, 1

	;    Calling malloc & check if the allocation was succesfull
	;    www.stackoverflow.com/questions/36007975/compile-error-relocation-r-x86-64-pc32-against-undefined-symbol
	call malloc WRT ..plt
	cmp  rax, 0
	je   error

	mov BYTE [rax], 0

	ret

error:
	push rax
	call __errno_location WRT ..plt

	mov QWORD [rax], 12

	pop rax
	pop rsi
	ret

end:
	ret
