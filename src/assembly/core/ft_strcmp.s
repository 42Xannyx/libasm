BITS 64

section .text
  global ft_strcmp

ft_strcmp:
  xor rdx, rdx

l1:
  mov al, BYTE [rdi + rdx]
  mov bl, BYTE [rsi + rdx]

  ; Jump if one of them is '\0'
  cmp al, 0
  je end
  cmp bl, 0
  je end


  cmp al, bl
  jne end

  inc rdx
  jmp l1

end:
  sub al, bl
  movsx rax, al
  ret
