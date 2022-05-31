.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 80
    mov eax, 1
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rax
    pop rbx
    add ebx, eax
    push rbx
    pop rdi # load print
    call waccrt_println_i32
    mov eax, 100
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rax
    pop rbx
    sub ebx, eax
    push rbx
    pop rdi # load print
    call waccrt_println_i32
    mov eax, 1
    push rax # e_push_number
    mov eax, 100
    push rax # e_push_number
    pop rax
    pop rbx
    sub ebx, eax
    push rbx
    pop rdi # load print
    call waccrt_println_i32
    mov eax, 2147483647
    push rax # e_push_number
    mov eax, 3
    push rax # e_push_number
    pop rax
    pop rbx
    add ebx, eax
    push rbx
    pop rdi # load print
    call waccrt_println_i32
    xor rax, rax
.ret_main:
    add rsp, 80
    pop rbp
    ret
.section .rodata

