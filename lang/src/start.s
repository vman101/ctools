section .data
    message: db "Hello,   World", 0xa, 0
    EARGCNT: db "[ERROR] Invalid arg count: expected 2", 0xa, 0
    usage:  db "Usage: ./debug <string> <delim>", 0xa, 0

section .text
    global _start
    extern exit
    extern split
    extern print_split
    extern putstr

print_usage:
    mov rdi, usage
    call putstr

err_args:
    mov rdi, EARGCNT
    call putstr
    jmp exit_err

exit_err:
    mov rdi, 1
    call exit

_start:
    pop rdi
    cmp rdi, 3
    jne err_args
    mov rdi, [rsp + 8]
    mov rsi, [rsp + 16]
    mov r8b, byte [rsi]
    mov rsi, r8
    call split
    mov rdi, rax
    call print_split
    xor rdi, rdi
    call exit
