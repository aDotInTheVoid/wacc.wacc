.intel_syntax noprefix
.global main
hello:
    push rbp
    mov rbp, rsp
    sub rsp, 2064
    lea rax, .str0[rip]
    push rax
    pop rdi # load print
    call waccrt_println_str
    mov eax, 0
    push rax # e_push_number
    pop rax
    jmp .ret_hello
.ret_hello:
    add rsp, 2064
    pop rbp
    ret
main:
    push rbp
    mov rbp, rsp
    sub rsp, 2064
    lea rax, [rbp-8]
    push rax # assign_addr_local
    sub rsp, 8
    call hello
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
    .string "Hello World"

