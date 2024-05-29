	BITS 64

	section .text
	global  ft_list_remove_if

	; rdi == 'begin_list **'
	; rsi == 'void *data_ref'
	; rdx == 'int32_t (*cmp)()'

ft_list_remove_if:
	xor rax, rax; Reset count

	;    Dereference double pointer to r8
	mov  r8, [rdi]
	push rdi

l1:
	cmp r8, 0
	je  end

	mov  rdi, [r8]
	call rdx

	cmp rax, rdi
	jhi remove_node

	mov r8, [r8 + 8]; t_list->next

	jmp l1

remove_node:
	mov r8, [r8 + 8]; t_list->next
	jmp l1

end:
	pop rdi
	ret
