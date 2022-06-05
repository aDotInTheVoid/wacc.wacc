.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 2064
    mov eax, 1
    push rax # e_push_number
    mov eax, 2
    push rax # e_push_number
    mov eax, 3
    push rax # e_push_number
    pop rsi
    pop rdi
    mov eax, edi
    imul eax, esi
    push rax
    pop rsi
    pop rdi
    lea eax, [rdi+rsi]
    push rax
    pop rdi # load print
    call waccrt_println_i32
    mov eax, 2
    push rax # e_push_number
    mov eax, 3
    push rax # e_push_number
    pop rsi
    pop rdi
    mov eax, edi
    imul eax, esi
    push rax
    mov eax, 1
    push rax # e_push_number
    pop rsi
    pop rdi
    lea eax, [rdi+rsi]
    push rax
    pop rdi # load print
    call waccrt_println_i32
    mov eax, 1
    push rax # e_push_number
    mov eax, 2
    push rax # e_push_number
    mov eax, 3
    push rax # e_push_number
    pop rsi
    pop rdi
    mov eax, edi
    imul eax, esi
    push rax
    pop rsi
    pop rdi
    lea eax, [rdi+rsi]
    push rax
    mov eax, 4
    push rax # e_push_number
    pop rsi
    pop rdi
    lea eax, [rdi+rsi]
    push rax
    pop rdi # load print
    call waccrt_println_i32
    xor rax, rax
.ret_main:
    add rsp, 2064
    pop rbp
    ret
.section .rodata

