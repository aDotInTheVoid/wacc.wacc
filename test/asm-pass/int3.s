.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 2064
    lea rax, [rbp-8]
    push rax # assign_addr_local
    mov eax, 0
    push rax # e_push_number
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    lea rax, [rbp-16]
    push rax # assign_addr_local
    mov eax, 1
    push rax # e_push_number
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    mov rax, [rbp-16] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    lea rax, [rbp-24]
    push rax # assign_addr_local
    mov eax, 2
    push rax # e_push_number
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    mov rax, [rbp-16] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    mov rax, [rbp-24] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    xor rax, rax
.ret_main:
    add rsp, 2064
    pop rbp
    ret
.section .rodata

