section .data
    header: db 0xa, "---------", 0xa, "Expr ", 0
    type:   db 0xa, "type: ", 0
section .text
    extern print_tokens

print_expressions:  ; (rdi: expr*)
    push r12
    push rbp
    mov rbp, rsp
    sub rsp, 16

    mov [rbp - 8], rdi
    mov 
    xor rcx, rcx

.print_loop:
    cmp rcx, 
