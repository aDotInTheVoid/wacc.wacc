.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 400
    lea rax, [rbp-8]
    push rax # assign_addr_local
    mov eax, -2147483648
    push rax # e_push_number
    pop rax
    neg eax
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    xor rax, rax
.ret_main:
    add rsp, 400
    pop rbp
    ret
.section .rodata

