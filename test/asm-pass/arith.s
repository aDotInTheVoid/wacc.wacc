.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 400
    mov eax, 1
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rsi
    pop rdi
    lea eax, [rdi+rsi]
    push rax
    pop rdi # load print
    call waccrt_println_i32
    mov eax, 100
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rsi
    pop rdi
    mov eax, edi
    sub eax, esi
    push rax
    pop rdi # load print
    call waccrt_println_i32
    mov eax, 1
    push rax # e_push_number
    mov eax, 100
    push rax # e_push_number
    pop rsi
    pop rdi
    mov eax, edi
    sub eax, esi
    push rax
    pop rdi # load print
    call waccrt_println_i32
    mov eax, 2147483647
    push rax # e_push_number
    mov eax, 3
    push rax # e_push_number
    pop rsi
    pop rdi
    lea eax, [rdi+rsi]
    push rax
    pop rdi # load print
    call waccrt_println_i32
    xor rax, rax
.ret_main:
    add rsp, 400
    pop rbp
    ret
.section .rodata

