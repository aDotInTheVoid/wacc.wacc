.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    lea rax, [rbp-0]
    push rax # assign_addr_local
    mov eax, 0
    push rax # e_push_number
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    mov rax, [rbp-0] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call wacctr_println_i32
    pop rbp
    ret

