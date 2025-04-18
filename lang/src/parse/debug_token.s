section .data
    token: db 0xa, "---------", 0xa, "Token ", 0
    type: db "type = ", 0
    value: db "value = ", 0

section .text
    global print_tokens
    extern putstr
    extern putendl
    extern putchar
    extern putnumberendl

print_tokens:       ; (rdi: tok*, rsi: int n)
    xor rcx, rcx
    push rbx
    mov rbx, rdi
    mov r13, rsi
.loop:
    mov rsi, r13
    cmp rcx, rsi
    je .done
    mov r12, rcx
    mov rdi, token
    call putstr
    mov rdi, r12
    call putnumberendl

    mov rdi, type
    call putstr
    mov rax, 16
    mul r12
    mov rdi, [rbx + rax]
    push rax
    call putnumberendl

    mov rdi, value
    call putstr
    pop rax

    mov rdi, [rbx + rax + 8]
    call putendl
    mov rcx, r12
    inc rcx
    jmp .loop

.done:
    pop rbx
    ret
