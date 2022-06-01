.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 400
    lea rax, [rbp-8]
    push rax # assign_addr_local
    mov eax, 0
    push rax # e_push_number
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
.CF0:
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    mov eax, 10
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    setl bl
    push rbx
    pop rax
    test rax, rax
    je .CF1
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    lea rax, [rbp-8]
    push rax # assign_addr_local
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    mov eax, 1
    push rax # e_push_number
    pop rax
    pop rbx
    add ebx, eax
    push rbx
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    jmp .CF0
.CF1:
    xor rax, rax
.ret_main:
    add rsp, 400
    pop rbp
    ret
.section .rodata

