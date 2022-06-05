.intel_syntax noprefix
.global main
ppair:
    push rbp
    mov rbp, rsp
    sub rsp, 2064
    mov [rbp-8], rdi
    lea rax, [rbp-16]
    push rax # assign_addr_local
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-24]
    push rax # assign_addr_local
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax+8]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    mov rax, [rbp-16] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    mov rax, [rbp-24] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    mov eax, 0
    push rax # e_push_number
    pop rax
    jmp .ret_ppair
.ret_ppair:
    add rsp, 2064
    pop rbp
    ret
main:
    push rbp
    mov rbp, rsp
    sub rsp, 2064
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
    lea rax, [rbp-16]
    push rax # assign_addr_local
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi
    sub rsp, 8
    call ppair
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
    mov eax, 10
    push rax # e_push_number
    pop rax
    neg eax
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-8]
    push rax # assign_addr_local
    pop rax
    mov rbx, [rax]
    add rbx, 8
    push rbx
    mov eax, 20
    push rax # e_push_number
    pop rax
    neg eax
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-16]
    push rax # assign_addr_local
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi
    sub rsp, 8
    call ppair
    add rsp, 8
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    xor rax, rax
.ret_main:
    add rsp, 2064
    pop rbp
    ret
.section .rodata

