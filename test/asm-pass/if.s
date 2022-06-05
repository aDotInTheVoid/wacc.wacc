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
    call waccrt_print_str
    jmp .CF1
.CF0:
    lea rax, .str1[rip]
    push rax
    pop rdi # load print
    call waccrt_print_str
.CF1:
    mov rax, 0
    push rax
    pop rax
    test rax, rax
    je .CF2
    lea rax, .str2[rip]
    push rax
    pop rdi # load print
    call waccrt_print_str
    jmp .CF3
.CF2:
    lea rax, .str3[rip]
    push rax
    pop rdi # load print
    call waccrt_print_str
.CF3:
    mov rax, 1
    push rax
    pop rax
    test rax, rax
    je .CF4
    mov rax, 1
    push rax
    pop rax
    test rax, rax
    je .CF5
    mov rax, 0
    push rax
    pop rax
    test rax, rax
    je .CF6
    jmp .CF7
.CF6:
    lea rax, .str4[rip]
    push rax
    pop rdi # load print
    call waccrt_print_str
.CF7:
    jmp .CF8
.CF5:
.CF8:
    jmp .CF9
.CF4:
.CF9:
    mov rax, 0
    push rax
    pop rax
    test rax, rax
    je .CF10
    jmp .CF11
.CF10:
    mov rax, 1
    push rax
    pop rax
    test rax, rax
    je .CF12
    mov rax, 0
    push rax
    pop rax
    test rax, rax
    je .CF13
    jmp .CF14
.CF13:
    lea rax, .str5[rip]
    push rax
    pop rdi # load print
    call waccrt_print_str
.CF14:
    jmp .CF15
.CF12:
.CF15:
.CF11:
    xor rax, rax
.ret_main:
    add rsp, 2064
    pop rbp
    ret
.section .rodata
.str0:
    .string "t"
.str1:
    .string "f"
.str2:
    .string "f"
.str3:
    .string "t"
.str4:
    .string "t"
.str5:
    .string "t"

