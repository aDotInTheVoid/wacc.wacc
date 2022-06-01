.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 400
    mov eax, 1
    push rax # e_push_number
    mov eax, 2
    push rax # e_push_number
    mov eax, 3
    push rax # e_push_number
    pop rax
    pop rbx
    imul ebx, eax
    push rbx
    pop rax
    pop rbx
    add ebx, eax
    push rbx
    pop rdi # load print
    call waccrt_println_i32
    mov eax, 2
    push rax # e_push_number
    mov eax, 3
    push rax # e_push_number
    pop rax
    pop rbx
    imul ebx, eax
    push rbx
    mov eax, 1
    push rax # e_push_number
    pop rax
    pop rbx
    add ebx, eax
    push rbx
    pop rdi # load print
    call waccrt_println_i32
    mov eax, 1
    push rax # e_push_number
    mov eax, 2
    push rax # e_push_number
    mov eax, 3
    push rax # e_push_number
    pop rax
    pop rbx
    imul ebx, eax
    push rbx
    pop rax
    pop rbx
    add ebx, eax
    push rbx
    mov eax, 4
    push rax # e_push_number
    pop rax
    pop rbx
    add ebx, eax
    push rbx
    pop rdi # load print
    call waccrt_println_i32
    xor rax, rax
.ret_main:
    add rsp, 400
    pop rbp
    ret
.section .rodata

