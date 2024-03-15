BITS 64

section .text
  global ft_atoi_base

; rdi == int8_t *str
; rsi == int32_t base

ft_atoi_base:
  mov rcx, 0
  mov rax, 0
  mov r8, 1

  jmp skip_whitespace

skip_whitespace:
  movzx rdx, byte [rdi + rcx]

  cmp rdx, 33                
  jle skip_non_whitespace     

  jmp is_minus                      

skip_non_whitespace:
  inc rcx                     
  jmp skip_whitespace        

is_minus:
  cmp byte [rdi], '-'
  jne is_plus

  inc rcx
  mov r8, -1

  jmp is_plus

is_plus:
  cmp byte [rdi], '+'
  jne l1 
  inc rcx

  jmp l1

l1:
  movzx rdx, byte [rdi + rcx]
  cmp rdx, 0
  je end

  cmp rdx, '0'
  jl end ; str[i] < '0'
  cmp rdx, '9'
  jg end ; str[i] > '9'
  
  sub rdx, '0'
  imul rax, rsi
  add rax, rdx 

  inc rcx
  jmp l1

end:
  imul rax, r8
  ret
