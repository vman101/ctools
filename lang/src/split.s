section .text
    global split
    global print_split
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

print_split:        ; print_split(rdi: char **)
    cmp qword [rdi], 0
    je  .done
    push rdi
    mov r8, [rdi]
    mov rdi, r8
    call putstr
    pop rdi
    add rdi, 8
    jmp print_split
.done:
    ret

split:              ; RAX: char ** split(RDI: char *, RSI: int)
    push rbp
    mov rbp, rsp    ; save base pointer
    push rbx
    push rcx
    push r12
    push r13

    ; int count = [ rbp - 4 ]
    ; char **split = [ rbp - 8 ]

    sub rsp, 16      ; allocate local vars

    call count_splits

    mov [rbp], rdi

    mov rcx, 8
    mov rbx, rax
    inc rax
    mul rcx

    push rdi
    push rsi
    mov rdi, rax
    call malloc
    cmp rax, 0
    je .fail

    pop rsi
    pop rdi


    mov qword [rax + rbx * 8], 0

    mov [rbp - 8], rax
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

    mov rdx, rax
    sub rdx, rdi
    sub r13, rdx

    mov r12, rax
    inc r12

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
    mov rax, [rbp - 8]
.cleanup:
    add rsp, 16
    pop r13
    pop r12
    pop rbx
    pop rcx
    mov rsp, rbp
    pop rbp
    ret

