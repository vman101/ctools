%define DEF_BUFFER_LEN 4096
%define INPUT_LENGTH 64

extern split

section .data
    message:        db      "Hello World!", 0xA, 0
    message_length: equ     $-message
    filepath:       db      "./test.c"

section .bss
    file_content_buffer:    resb DEF_BUFFER_LEN

section .text
    global  _start

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

print_string:       ; print_string(RDI: char *string)
    call strlen

    mov rdx, rax    ; string length

    mov rsi, rdi
    mov rdi, 1      ; stdout
    mov rax, 1      ; sys_write
    syscall

    ret

exit:
    mov     rax, 60
    syscall

strlen:                 ; strlen(RDI: char *str)
    push rcx            ; save counter
    xor rcx, rcx
.loop:                  ; loop until '\0' character
    cmp byte [rdi + rcx], 0
    jz  .done
    inc rcx
    jmp .loop
.done:
    mov rax, rcx        ; mov return value to rax
    pop rcx             ; restore counter
    ret

_start:
    mov rdi, message    ; prepare first arg -> string addr to rdi
    call print_string

    mov rdi, rax
    push rax            ; save rax
    push rdi            ; save rdi since arg comes into it

    mov rdi, filepath   ; filepath for open call
    mov rsi, 0          ; O_RDONLY flag
    call open_file

    mov rbx, rax        ; mov new fd to rbx

    mov rdi, rbx        ; first arg: mov fd to rdi for read call
    mov rsi, file_content_buffer    ; 2nd arg: buffer
    mov rdx, 15         ; 3rd arg: read len

    call read_file_bytes
    mov byte [file_content_buffer + 15], 0xA   ; newline
    mov byte [file_content_buffer + 16], 0x0   ; 0 terminate string

    push rdi            ; save fd
    mov rdi, rsi          ; stdout fd

    call print_string
    pop rdi             ; restore fd

    call close_file

    mov rdi, rsi
    mov rsi, 0x20       ; ' ' space character
    call split

.exit_early:
    mov rdi, rax

    call exit
