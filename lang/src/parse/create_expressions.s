%define EXPR_SIZE 32

section .text
    global create_expressions
    extern split
    extern get_split_count
    extern malloc
    extern err_malloc
    extern parse


create_expressions:         ; rax: exp* (rdi: char *filecontent)
    push rbp
    mov rbp, rsp
    sub rsp, 32             ; allocate stack

    mov rsi, 0x0a
    call split

    mov rdi, rax
    push rdi
    call get_split_count
    mov r12, rax
    inc rax
    mov rcx, 8
    mul rcx
    mov rdi, rax
    call malloc
    cmp rax, 0
    mov r14, rax
    je err_malloc
    mov [rbp - 8], rax      ; char *** tok

    mov [rbp - 24], r12     ; store split count
    mov rdi, r12
    mov rax, EXPR_SIZE
    mul rdi
    mov rdi, rax
    call malloc
    cmp rax, 0
    je err_malloc
    mov [rbp - 16], rax     ; *expression

    xor rcx, rcx
    pop rdi
    mov r13, rdi

.split_splits:
    mov rsi, 0x20
    cmp rcx, r12
    je .done
    mov rbx, rcx
    mov rdi, [r13 + rcx * 8]
    call split
    mov rcx, rbx
    mov rbx, [rbp - 8]
    mov [rbx + rcx * 8], rax
    push rcx
    mov rdi, rax
    call get_split_count
    pop rcx
    push rax
    mov rsi, rax
    mov rbx, [rbp - 8]
    mov rdi, [rbx + rcx * 8]
    push rcx
    call parse
    pop rcx
    push rax
    mov rbx, [rbp - 16]
    mov rdx, rcx
    mov rax, EXPR_SIZE
    mul rdx
    mov rdx, rax
    pop rax
    mov [rbx + rdx + 16], rax
    pop rax
    mov [rbx + rdx + 8], rax
    inc rcx
    jmp .split_splits

.done:
    add rsp, 32
    mov rsp, rbp
    pop rbp
    mov rax, [rbp - 16]
    ret
