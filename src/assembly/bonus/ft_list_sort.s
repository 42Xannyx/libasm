	BITS 64

	section .text
	global  ft_list_sort

	; rdi == 't_list *'
	; rsi == 'int (*cmp)()'

ft_list_sort:
	;   Reset rax
	xor rax, rax

l1:

end:
	ret
