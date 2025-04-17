global putstr
global putchar

section .text
    extern strlen

write:              ; RAX: int write(RDI: int fd, RSI: char *buf, RDX: size_t n)
    mov rax, 1      ; sys_write
    syscall
    ret

putchar:
    sub rsp, 16     ; create stack var
    mov [rsp], dil  ; move lower byte of tdi into stack
    mov rsi, rsp
    mov rdx, 1
    mov rdi, 1
    call write
    add rsp, 16
    ret

putstr:       ; print_string(RDI: char *string)
    call strlen

    mov rdx, rax    ; string length
    mov rsi, rdi    ; mov buffer
    mov rdi, 1      ; stdout

    call write

    ret
