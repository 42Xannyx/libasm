BITS 64

extern __errno_location
extern ft_strlen
extern ft_strcpy
extern malloc
;
section .text
  global ft_strdup
;
ft_strdup:
  xor rdx, rdx

  mov r8, rdi
  cmp BYTE [r8], 0
  je end

  push r8
  call ft_strlen
  inc rax
  mov rdi, rax

  call malloc WRT ..plt ; https://stackoverflow.com/questions/36007975/compile-error-relocation-r-x86-64-pc32-against-undefined-symbol
  cmp rax, 0
  je error 

  mov rdi, rax
  pop rsi
  call ft_strcpy

  ret

error:
  neg rax 
  push rax
  call __errno_location WRT ..plt
  pop rdi
  mov [rax], edi
  mov rax, -1
  ret

end:
  ret
