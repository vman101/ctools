%define EXPR_SIZE 32

section .text
    global create_expressions
    extern split
    extern get_split_count
    extern malloc
    extern err_malloc
    extern parse
    extern expr_type
    extern expr_tok
    extern expr_tok_cnt
    extern expr_size
    extern print_tokens
    extern print_expression


create_expressions:         ; rax: exp* (rdi: char *filecontent)
    push rbp
    mov rbp, rsp
    sub rsp, 32             ; allocate stack

    mov rsi, 0x0a
    call split

    mov rdi, rax
    push rdi
    call get_split_count
    mov [rbp - 24], rax     ; store split count
    inc rax
    mov rcx, 8
    mul rcx
    mov rdi, rax
    call malloc
    cmp rax, 0
    mov r14, rax
    je err_malloc

    mov [rbp - 8], rax      ; char *** tok

    xor rcx, rcx
    pop rdi
    mov r13, rdi
    mov r12, [rbp - 24]

.split_splits:
    mov rsi, 0x20
    cmp rcx, r12
    je .splitting_done
    mov rbx, rcx
    mov rdi, [r13 + rcx * 8]
    call split
    mov rcx, rbx
    mov rbx, [rbp - 8]
    mov [rbx + rcx * 8], rax
    inc rcx
    jmp .split_splits

.splitting_done:

    ; allocate expressions
    mov rax, [expr_size]
    mul rcx                 ; rcx contains the amount of splits aka expr count
    mov rdi, rax
    call malloc
    cmp rax, 0
    je err_malloc

    mov [rbp - 16], rax     ; store expr* on stack

    xor rcx, rcx
.loop_expressions:

    ; create the actual expressions
    mov rbx, [rbp - 24]
    cmp rcx, rbx
    je .expressions_done
    mov rbx, [rbp - 8]
    mov rdi, [rbx + rcx * 8]
    push rcx
    call parse
    pop rcx
    push rax
    mov rbx, [rbp - 16]     ; mov expr* into rax
    mov rax, [expr_size]
    mul rcx
    lea rax, [rbx + rax]
    pop rbx
    mov rdx, [expr_tok]
    mov [rax + rdx], rbx
    inc rcx
    jmp .loop_expressions

.expressions_done:
    ; print expressions debug
    xor rcx, rcx

.expr_loop_print:
    mov rbx, [rbp - 24]
    cmp rcx, rbx
    je .done
    mov rbx, [rbp - 16]
    mov rax, [expr_size]
    mul rcx
    lea rdi, [rbx + rax]
    push rcx
    call print_expression
    pop rcx
    inc rcx
    jmp .expr_loop_print

.done:
    mov rax, [rbp - 16]
    add rsp, 32
    mov rsp, rbp
    pop rbp
    ret
