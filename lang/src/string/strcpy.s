global strcpy

section .text
    extern malloc
    extern strlen

strcpy:         ; rax: char *(rdi: char *)
    push rbx
    call strlen
    mov r9, rdi     ; r9 contains arg
    mov r8, rax
    mov rdi, rax
    inc rdi
    call malloc
    push rcx
    xor rcx, rcx
.loop:
    cmp byte [r9 + rcx], 0
    je .done
    mov bl, [r9 + rcx]
    mov [rax + rcx], bl
    inc rcx
    jmp .loop
.done:
    mov byte [rax + rcx], 0
    pop rcx
    pop rbx
    ret
