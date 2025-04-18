section .data

    usage:  db "Usage: ./debug <file>.lang", 0xa, 0
section .text
    global _start
    extern exit
    extern split
    extern print_split
    extern putchar
    extern putstr
    extern putnumber
    extern open
    extern close
    extern read
    extern get_file_size
    extern malloc
    extern lseek
    extern read_file
    extern err_args
    extern putendl
    extern parse
    extern print_tokens

print_usage:
    mov rdi, usage
    call putstr

get_file_content:       ; rax: char *(rdi: char*)
    mov rsi, 0
    call open
    mov rdi, rax
    push rax
    call read_file
    mov rsi, rax
    pop rdi
    call close
    mov rax, rsi
    ret

_start:
    pop rdi
    cmp rdi, 2
    jne err_args
    mov rdi, [rsp + 8]      ; argv[1]

    push rbp
    mov rbp, rsp
    sub rsp, 32             ; allocate stack

    call get_file_content

    mov rdi, rax
    mov rsi, 0x0a
    call split

    mov rdi, rax
    push rdi
    call print_split
    mov rsi, rax
    pop rdi
    push rsi
    mov rdx, rsi
    call parse
    pop rsi

    mov rdi, rax
    call print_tokens

    xor rdi, rdi
    add rsp, 32
    mov rsp, rbp
    pop rbp
    call exit
