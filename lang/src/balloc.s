global balloc

brk_find_break:     ; RAX: long brk(0)
    mov rdi, 0x0
    mov rax, 0xC    ; sys_brk
    syscall
    ret

balloc:                 ; RAX: long basic_malloc(RDI: size_t n, RSI void **heap_begin_ptr)
    cmp dword [rsi], 0        ; check if heap_begin_ptr exist
    jne .allocate       ; allocate normally if exists

    push rdi

    call brk_find_break

    mov qword [rsi], rax        ; get heap beginning
    pop rdi

.allocate:
    mov rax, qword [rsi]
    add rdi, rax
    mov rax, 0xC        ; sys_brk

    syscall
    ret
