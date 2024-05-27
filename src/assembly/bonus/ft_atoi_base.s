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

	; Logic
	; 1. Check if rsi (base) is correct
	; 2. Skip whitespaces, minus & plus
	; 3. Go through rdi (str) and make string and number

ft_atoi_base:
	;   Initialize registers
	xor rax, rax; Result
	xor rcx, rcx; Index
	xor r8, r8; Base length
	mov r9, 1; Sign (1 for positive, -1 for negative)

	;   Validate base
	mov r10, rsi; Pointer to base

validate_base:
	movzx rdx, BYTE [r10 + r8]
	test  rdx, rdx
	jz    base_validated

	;   Check for invalid characters in base
	cmp rdx, ' '
	je  error
	cmp rdx, '+'
	je  error
	cmp rdx, '-'
	je  error

	;   Check for duplicate characters in base
	mov r11, r10

check_duplicate:
	inc   r11
	movzx rbx, BYTE [r11]
	test  rbx, rbx
	jz    next_base_char
	cmp   rbx, rdx
	je    error
	jmp   check_duplicate

next_base_char:
	inc r8
	jmp validate_base

base_validated:
	;   Base must have at least 2 characters
	cmp r8, 2
	jb  error

	;   Skip leading whitespaces
	mov rdi, rdi; Ensure rdi points to the string

skip_whitespaces:
	movzx rdx, BYTE [rdi + rcx]
	cmp   rdx, ' '
	je    increment_index
	cmp   rdx, '\t'
	je    increment_index
	cmp   rdx, '\n'
	je    increment_index
	cmp   rdx, '\v'
	je    increment_index
	cmp   rdx, '\f'
	je    increment_index
	cmp   rdx, '\r'
	je    increment_index
	jmp   check_sign

increment_index:
	inc rcx
	jmp skip_whitespaces

check_sign:
	movzx rdx, BYTE [rdi + rcx]
	cmp   rdx, '-'
	je    set_negative
	cmp   rdx, '+'
	je    increment_index
	jmp   convert_loop

set_negative:
	mov r9, -1
	inc rcx
	jmp convert_loop

convert_loop:
	movzx rdx, BYTE [rdi + rcx]
	test  rdx, rdx
	jz    end_conversion

	;   Find the character in the base
	xor r11, r11

find_char_in_base:
	movzx rbx, BYTE [rsi + r11]
	test  rbx, rbx
	jz    end_conversion
	cmp   rdx, rbx
	je    valid_char_found
	inc   r11
	jmp   find_char_in_base

valid_char_found:
	;    Update the result
	imul rax, r8
	add  rax, r11
	inc  rcx
	jmp  convert_loop

end_conversion:
	;    Apply the sign
	imul rax, r9
	ret

error:
	xor rax, rax
	ret
