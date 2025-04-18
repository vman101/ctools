section .text
    global split
    extern malloc
    extern putstr
    extern putnumber
    extern strcpy
    extern memchr
    extern substr
    extern strlen

count_splits:       ; RAX: int count_splits(RDI: char *, RSI: int c)
    push rbx
    xor rcx, rcx
    xor rbx, rbx
.loop:
    cmp byte [rdi + rcx], 0
    jz  .done
    cmp byte [rdi + rcx], sil
    jne .skip
.while_is_c:
    inc rcx
    cmp byte [rdi + rcx], 0
    jz  .done
    cmp byte [rdi + rcx], sil
    jz .while_is_c
    inc rbx
.skip:
    inc rcx
    jmp .loop
.done:
    mov rax, rbx
    pop rbx
    inc rax
    ret

split:              ; RAX: char ** split(RDI: char *, RSI: int)
    push rbp
    mov rbp, rsp    ; save base pointer
    push rbx
    push r12
    push r13

    ; int count = [ rbp - 4 ]
    ; char **split = [ rbp - 8 ]

    sub rsp, 16      ; allocate local vars
    mov [rbp - 8], rdi
    call count_splits
    mov rcx, 8
    mov rbx, rax
    inc rax
    mul rcx
    push rdi
    push rsi
    mov rdi, rax
    call malloc
    pop rsi
    pop rdi
    cmp rax, 0
    je .fail



    mov qword [rax + rbx * 8], 0

    mov [rbp - 16], rax
    mov rcx, rax

    cmp rbx, 1
    je .no_match

    call strlen
    mov r13, rax
.loop:
    cmp rbx, 0
    je .done

    mov rdx, r13
    push rcx
    call memchr
    pop rcx
    xor r9, r9
    jmp .skip_matches
.after_skip:

    lea rdx, [rax]
    sub rdx, rdi
    sub r13, rdx

    mov r12, rax
    add r12, r9

    push rsi
    mov rsi, 0
    push rcx
    call substr
    pop rcx
    pop rsi
    mov rdi, r12
    lea r8, [rax]
    mov [rcx], r8
    add rcx, 8
    dec rbx
    jmp .loop

.fail:
    xor rax, rax
    jmp .cleanup
.no_match:
    push rcx
    call strcpy
    pop rcx
    mov [rcx], rax
.done:
    mov rax, [rbp - 16]
.cleanup:
    add rsp, 16
    pop r13
    pop r12
    pop rbx
    mov rsp, rbp
    pop rbp
    ret

.skip_matches:
    cmp byte [rax + r9], 0
    jz .after_skip
    cmp byte [rax + r9], sil
    jnz .after_skip
    inc r9
    dec r13
    jmp .skip_matches


