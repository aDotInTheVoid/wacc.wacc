.intel_syntax noprefix
.global main
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
    add rsp, 80
    pop rbp
    ret
.section .rodata

