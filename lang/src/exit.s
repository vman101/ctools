
section .text

global exit

exit:
    mov     rax, 60
    syscall
