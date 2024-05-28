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
	xor rcx, rcx; Index for str
	xor r8, r8; Base length
	mov r9, 1; Sign (1 for positive, -1 for negative)

	;   Validate base
	mov r10, rsi; Pointer to base

	; -----------------------
	; Logic of validate_base
	; 1. RDX is a char of rsi, and checks if it has any whitespace, minus or plus has
	; 2. Iterate through each character to find a duplicate.

validate_base:
	movzx rdx, BYTE [rsi + r8]
	cmp   rdx, 0
	je    base_validated

	;   Check for invalid characters in base
	cmp rdx, ' '
	je  error
	cmp rdx, '+'
	je  error
	cmp rdx, '-'
	je  error

	mov r11, r8

check_duplicate:
	inc r11

	;     If we finish going through the the string of base, we go to the next char of RDX
	movzx rbx, BYTE [rsi + r11]
	cmp   rbx, 0
	je    next_base_char

	cmp rbx, rdx
	je  error

	jmp check_duplicate

next_base_char:
	inc r8
	jmp validate_base

	; -------------------------

base_validated:
	;   Base must have at least 2 characters
	cmp r8, 2
	jb  error

skip_whitespaces:
	;     Skip leading whitespaces
	movzx rdx, BYTE [rdi + rcx]

	cmp rdx, ' '
	je  increment_index_whitespace
	cmp rdx, 9
	je  increment_index_whitespace
	cmp rdx, 10
	je  increment_index_whitespace
	cmp rdx, 11
	je  increment_index_whitespace
	cmp rdx, 12
	je  increment_index_whitespace
	cmp rdx, 13
	je  increment_index_whitespace

	jmp check_sign

increment_index_whitespace:
	inc rcx
	jmp skip_whitespaces

	; -------------------------

check_sign:
	movzx rdx, BYTE [rdi + rcx]

	cmp rdx, '-'
	je  set_negative

	cmp rdx, '+'
	je  increment_index_sign

	jmp convert_loop

set_negative:
	;   If there is a minus, make it negative
	mov r9, -1
	inc rcx

	jmp convert_loop

increment_index_sign:
	;   If there is a plus, skip it and go to convert_loop
	inc rcx
	jmp convert_loop

	; -------------------------

convert_loop:
	movzx rdx, BYTE [rdi + rcx]
	cmp   rdx, 0
	je    end_conversion

	;   Find the character in the base
	xor r11, r11

find_char_in_base:
	movzx rbx, BYTE [rsi + r11]
	cmp   rbx, 0
	je    end_conversion

	cmp rdx, rbx
	je  valid_char_found

	inc r11
	jmp find_char_in_base

valid_char_found:
	; Update the result
	; The formula is: result = result * base_length + digit_value
	; rax = result
	; r8  = base_length (length of the base string)
	; r11 = digit_value (numeric value of the current character in the base string)

	imul rax, r8
	add  rax, r11
	inc  rcx

	jmp convert_loop

end_conversion:
	;    Apply the sign
	imul rax, r9
	ret

error:
	mov rax, 0
	ret
