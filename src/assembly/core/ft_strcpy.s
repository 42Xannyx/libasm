BITS 64

section .text
  global ft_strcpy

; rdi == dest*
; rsi == src*

ft_strcpy:
  mov rcx, 0

l1:
  mov al, [rsi + rcx]
  mov [rdi + rcx], al
  cmp al, 0
  je end
  inc rcx
  jmp l1

end:
  mov rax, rdi
  ret
  
