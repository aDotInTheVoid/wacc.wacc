.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 80
    lea rax, [rbp-8]
    push rax # assign_addr_local
    mov rax, 49
    push rax
    mov rax, 50
    push rax
    mov rax, 51
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
    lea rax, [rbp-16]
    push rax # assign_addr_local
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
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
    mov rax, [rbp-16] # e_push_local
    push rax # e_push_local
    mov eax, 0
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    mov eax, 0
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # load print
    call waccrt_println_char
    mov rax, [rbp-16] # e_push_local
    push rax # e_push_local
    mov eax, 0
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # load print
    call waccrt_println_char_array
    mov rax, [rbp-16] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_ptr
    mov rax, [rbp-16] # e_push_local
    push rax # e_push_local
    mov eax, 0
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi
    call waccrt_array_delete
    mov rax, [rbp-16] # e_push_local
    push rax # e_push_local
    pop rdi
    call waccrt_array_delete
    xor rax, rax
.ret_main:
    add rsp, 80
    pop rbp
    ret
.section .rodata

