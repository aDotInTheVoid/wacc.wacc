.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 400
    lea rax, [rbp-8]
    push rax # assign_addr_local
    mov eax, 1
    push rax # e_push_number
    mov eax, 2
    push rax # e_push_number
    pop rsi
    pop rdi
    sub rsp, 8
    call waccrt_pair_new
    add rsp, 8
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-8]
    push rax # assign_addr_local
    pop rax
    mov rbx, [rax]
    push rbx
    mov eax, 3
    push rax # e_push_number
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi
    call waccrt_pair_delete
    xor rax, rax
.ret_main:
    add rsp, 400
    pop rbp
    ret
.section .rodata

