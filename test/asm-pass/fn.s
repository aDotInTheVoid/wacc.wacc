.intel_syntax noprefix
.global main
add:
    push rbp
    mov rbp, rsp
    sub rsp, 80
    mov [rbp-8], rdi
    mov [rbp-16], rsi
    lea rax, .str0[rip]
    push rax
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_i32
    lea rax, .str1[rip]
    push rax
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-16] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    mov rax, [rbp-16] # e_push_local
    push rax # e_push_local
    pop rax
    pop rbx
    add ebx, eax
    push rbx
    pop rax
    jmp .ret_add
.ret_add:
    add rsp, 80
    pop rbp
    ret
main:
    push rbp
    mov rbp, rsp
    sub rsp, 80
    lea rax, [rbp-8]
    push rax # assign_addr_local
    mov eax, 1
    push rax # e_push_number
    mov eax, 2
    push rax # e_push_number
    pop rsi
    pop rdi
    sub rsp, 8
    call add
    add rsp, 8
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
    add rsp, 80
    pop rbp
    ret
.section .rodata
.str0:
    .string "a = "
.str1:
    .string ", b = "

