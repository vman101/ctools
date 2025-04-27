section .data
    header: db 0xa, "---------", 0xa, "Expr ", 0
    type:   db 0xa, "type: ", 0
section .text
    extern print_tokens
    extern expr_type
    extern expr_tok
    extern expr_tok_cnt

global print_expression
print_expression:  ; (rdi: expr*)
    push r12

    add rdi, [expr_tok]     ; tok**
    mov r12, [rdi]          ; r12 = tok*
    mov rdi, r12
    call print_tokens

    pop r12
    ret
