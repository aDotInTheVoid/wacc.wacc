.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 400
    lea rax, [rbp-8]
    push rax # assign_addr_local
    mov rax, 'a'
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-16]
    push rax # assign_addr_local
    mov eax, 1
    push rax # e_push_number
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-24]
    push rax # assign_addr_local
    mov rax, 1
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-32]
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
    lea rax, [rbp-40]
    push rax # assign_addr_local
    lea rax, .str0[rip]
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-48]
    push rax # assign_addr_local
    mov rax, 'a'
    push rax
    mov rax, 'b'
    push rax
    mov rax, 'f'
    push rax
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
    lea rax, [rbp-56]
    push rax # assign_addr_local
    xor eax, eax
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_char
    mov rax, [rbp-16] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    mov rax, [rbp-24] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_bool
    mov rax, [rbp-32] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_ptr
    mov rax, [rbp-40] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_str
    mov rax, [rbp-48] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_char_array
    mov rax, [rbp-56] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_ptr
    xor rax, rax
.ret_main:
    add rsp, 400
    pop rbp
    ret
.section .rodata
.str0:
    .string "str e"

