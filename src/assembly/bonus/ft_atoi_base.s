	BITS 64

	section .text
	global  ft_atoi_base

	; From the Piscine Subject:

	; • Write a function that converts the initial portion
	; of the string pointed to by str to an integer representation.

	; • The str input string is interpreted in a specific base given
	; as a second parameter.

	; • Except for the base rule, the function should work exactly
	; like the standard ft_atoi function.

	; • If there’s an invalid argument, the function should return 0.

	; Examples of invalid arguments:

	; • The base is empty or has a size of 1.

	; • The base contains the same character twice.

	; • The base contains '+' or '-' or whitespaces.

	; rdi == char *str
	; rsi == char *base

ft_atoi_base:
	;   Give the correct values for each variable
	xor rcx, rcx
	xor rax, rax
	mov r8, 1

	jmp skip_whitespace

skip_whitespace:
	movzx rdx, BYTE [rdi + rcx]

	cmp rdx, 33
	jle increment_whitespace

	jmp is_minus

increment_whitespace:
	inc rcx
	jmp skip_whitespace

is_minus:
	cmp BYTE [rdi], '-'
	jne is_plus

	inc rcx
	mov r8, -1

	jmp is_plus

is_plus:
	cmp byte [rdi], '+'
	jne l1

	inc rcx
	jmp reset_to_l2

l1:
	;     l1 loops through rdi
	movzx rdx, BYTE [rdi + rcx]

	;   Check if end of string
	cmp rdx, 0
	je  end

	;   Check if string is a non-digit
	cmp rdx, '0'
	jl  end; str[i] < '0'
	cmp rdx, '9'
	jg  end; str[i] > '9'

	;    Add to current result
	;    rax = rax * 10 + (rdx - '0')
	sub  rdx, '0'
	imul rax, 10
	add  rax, rdx

	inc rcx
	jmp l1

l2:
	;     l2 loops through rsi to find out if `base` is valid
	movzx rdx, BYTE [rsi + rcx]

	;   Compare to ' '
	cmp rdx, ' '
	je  error_base

	;   Compare to '-'
	cmp rdx, '-'
	je  error_base

	;   Compare to '+'
	cmp rdx, '+'
	je  error_base

	cmp rdx, 0
	je  reset_to_l1

	inc rcx
	jmp l2

reset_to_l1:
	mov rcx, 0
	jmp l1

reset_to_l2:
	mov rcx, 0
	jmp l2

error_base:
	mov rax, -1
	ret

end:
	imul rax, r8
	ret
