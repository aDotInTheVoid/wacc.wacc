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
    mov eax, 3
    push rax # e_push_number
    mov rdi, 3
    lea rsi, [rsp+16]
    call waccrt_array_new
    pop rdx
    pop rdx
    pop rdx
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-16]
    push rax # assign_addr_local
    mov eax, 0
    push rax # e_push_number
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
.CF0:
    mov rax, [rbp-16] # e_push_local
    push rax # e_push_local
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax-8]
    push rdi
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
    lea rax, [rbp-8]
    push rax # assign_addr_local
    mov rax, [rbp-16] # e_push_local
    push rax # e_push_local
    pop rbx # array index
    pop rax # array base
    mov rax, [rax]
    lea rcx, [rax+rbx*8]
    push rcx
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    mov rax, [rbp-16] # e_push_local
    push rax # e_push_local
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rax
    neg eax
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-16]
    push rax # assign_addr_local
    mov rax, [rbp-16] # e_push_local
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
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    mov eax, 0
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # load print
    call waccrt_println_i32
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    mov eax, 1
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # load print
    call waccrt_println_i32
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    mov eax, 2
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # load print
    call waccrt_println_i32
    xor rax, rax
.ret_main:
    add rsp, 400
    pop rbp
    ret
.section .rodata

