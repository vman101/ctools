%define DEF_BUFFER_LEN 4096
%define INPUT_LENGTH 64

; rax -- syscall

; type widths

section .data
    message:        db      "Hello World!", 0xA, 0 ; hello
    message_length: equ     $-message

section .bss
    arr:            resb DEF_BUFFER_LEN

section .text
    global  _start

print_string:
    push rbp
    push rdx
    mov rbp, rsp    ; set up stack frame

    mov rax, 1      ; sys_write

    pop rdx
    pop rbp

exit:
    mov     rax, 60
    syscall

strlen:
    push rcx
    xor rcx, rcx
.loop:
    cmp byte [rdi + rcx], 0
    jz  .done
    inc rcx
    jmp .loop
.done:
    mov rax, rcx
    pop rcx
    ret

_start:
    mov rdi, message    ; prepare first arg -> string addr to rdi
    call strlen
    mov rdi, rax
    call exit
