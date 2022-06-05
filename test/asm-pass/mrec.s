.intel_syntax noprefix
.global main
r1:
    push rbp
    mov rbp, rsp
    sub rsp, 2064
    mov [rbp-8], rdi
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    mov eax, 0
    push rax # e_push_number
    pop rsi
    pop rdi
    xor eax, eax
    cmp rdi, rsi
    sete al
    push rax
    pop rax
    test rax, rax
    je .CF0
    jmp .CF1
.CF0:
    lea rax, .str0[rip]
    push rax
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    lea rax, [rbp-16]
    push rax # assign_addr_local
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi
    sub rsp, 8
    call r2
    add rsp, 8
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
.CF1:
    mov eax, 42
    push rax # e_push_number
    pop rax
    jmp .ret_r1
.ret_r1:
    add rsp, 2064
    pop rbp
    ret
r2:
    push rbp
    mov rbp, rsp
    sub rsp, 2064
    mov [rbp-8], rdi
    lea rax, .str1[rip]
    push rax
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    lea rax, [rbp-16]
    push rax # assign_addr_local
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    mov eax, 1
    push rax # e_push_number
    pop rsi
    pop rdi
    mov eax, edi
    sub eax, esi
    push rax
    pop rdi
    sub rsp, 8
    call r1
    add rsp, 8
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    mov eax, 44
    push rax # e_push_number
    pop rax
    jmp .ret_r2
.ret_r2:
    add rsp, 2064
    pop rbp
    ret
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
    lea rax, [rbp-8]
    push rax # assign_addr_local
    mov eax, 8
    push rax # e_push_number
    pop rdi
    sub rsp, 8
    call r1
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
.str0:
    .string "r1: sending "
.str1:
    .string "r2: received "

