.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 400
    lea rax, [rbp-8]
    push rax # assign_addr_local
    xor eax, eax
    push rax
    xor eax, eax
    push rax
    xor eax, eax
    push rax
    xor eax, eax
    push rax
    mov rdi, 4
    lea rsi, [rsp+24]
    sub rsp, 8
    call waccrt_array_new
    add rsp, 8
    pop rdx
    pop rdx
    pop rdx
    pop rdx
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax-8]
    push rdi
    pop rdi # load print
    call waccrt_println_i32
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax-8]
    push rdi
    pop rax
    neg eax
    push rax
    pop rdi # load print
    call waccrt_println_i32
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax-8]
    push rdi
    pop rax
    neg eax
    push rax
    pop rax
    neg eax
    push rax
    pop rdi # load print
    call waccrt_println_i32
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax-8]
    push rdi
    mov eax, 3
    push rax # e_push_number
    pop rsi
    pop rdi
    xor eax, eax
    cmp rdi, rsi
    sete al
    push rax
    pop rax
    xor rax, 1
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax-8]
    push rdi
    mov eax, 4
    push rax # e_push_number
    pop rsi
    pop rdi
    xor eax, eax
    cmp rdi, rsi
    setne al
    push rax
    pop rax
    xor rax, 1
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 39
    push rax # e_push_number
    pop rdi # load print
    call waccrt_println_char
    mov rax, 'a'
    push rax
    pop rdi # load print
    call waccrt_println_i32
    mov eax, 40
    push rax # e_push_number
    pop rdi # load print
    call waccrt_println_char
    xor rax, rax
.ret_main:
    add rsp, 400
    pop rbp
    ret
.section .rodata

