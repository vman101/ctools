
section .text
    global  open_file
    global  close_file
    global  read_file_bytes

open_file:
    mov rax, 2          ; sys_open

    syscall
    ret

close_file:
    mov rax, 3         ; sys_close

    syscall
    ret

read_file_bytes:    ; read(RDI: int fd, RSI: char *buffer, RDX: size_t size)
    mov rax, 0      ; sys_read
    syscall         ;
    ret

