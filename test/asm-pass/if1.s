.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 2064
    mov rax, 1
    push rax
    pop rax
    test rax, rax
    je .CF0
    lea rax, .str0[rip]
    push rax
    pop rdi # load print
    call waccrt_println_str
    jmp .CF1
.CF0:
.CF1:
    xor rax, rax
.ret_main:
    add rsp, 2064
    pop rbp
    ret
.section .rodata
.str0:
    .string "t"

