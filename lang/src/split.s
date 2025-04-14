global  split   ; export split

section .text

count_splits:   ; RAX: int count_splits(RDI: char *, RSI: int c)
    push rbx
    xor rcx, rcx
    xor rbx, rbx
.loop:
    cmp byte [rdi + rcx], 0
    jz  .done
    cmp byte [rdi + rcx], sil
    jne .skip
    inc rbx
.skip:
    inc rcx
    jmp .loop
.done:
    mov rax, rbx
    pop rbx
    ret

split:          ; RAX: char ** split(RDI: char *str, RSI: int c)
    push rbp
    mov rbp, rsp    ; save base pointer

    ; int count = [ rbp - 4 ]

    sub rsp, 4      ; allocate local vars

    call count_splits

    mov rsp, rbp
    pop rbp

    ret

    ; count = count_splits()
    mov [rbp - 4], rax

    pop rbp

    ret
