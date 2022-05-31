.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 80
    lea rax, .str0[rip]
    push rax
    pop rdi # load print
    call waccrt_println_str
    mov eax, 1
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    sete bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 1
    push rax # e_push_number
    mov eax, 2
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    sete bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    lea rax, .str1[rip]
    push rax
    pop rdi # load print
    call waccrt_println_str
    mov eax, 1
    push rax # e_push_number
    mov eax, 2
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    setne bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 7
    push rax # e_push_number
    mov eax, 7
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    setne bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    lea rax, .str2[rip]
    push rax
    pop rdi # load print
    call waccrt_println_str
    mov eax, 0
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    setl bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 1
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    setl bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 2
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    setl bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    lea rax, .str3[rip]
    push rax
    pop rdi # load print
    call waccrt_println_str
    mov eax, 0
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    setle bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 1
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    setle bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 2
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    setle bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    lea rax, .str4[rip]
    push rax
    pop rdi # load print
    call waccrt_println_str
    mov eax, 1
    push rax # e_push_number
    mov eax, 0
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    setg bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 1
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    setg bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 1
    push rax # e_push_number
    mov eax, 2
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    setg bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    lea rax, .str5[rip]
    push rax
    pop rdi # load print
    call waccrt_println_str
    mov eax, 1
    push rax # e_push_number
    mov eax, 0
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    setge bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 1
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    setge bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 1
    push rax # e_push_number
    mov eax, 2
    push rax # e_push_number
    pop rax
    pop rbx
    mov rcx, rbx
    xor ebx, ebx
    cmp rcx, rax
    setge bl
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    lea rax, .str6[rip]
    push rax
    pop rdi # load print
    call waccrt_println_str
    mov rax, 1
    push rax
    mov rax, 1
    push rax
    pop rax
    pop rbx
    and ebx, eax
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov rax, 1
    push rax
    mov rax, 0
    push rax
    pop rax
    pop rbx
    and ebx, eax
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov rax, 0
    push rax
    mov rax, 0
    push rax
    pop rax
    pop rbx
    and ebx, eax
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov rax, 0
    push rax
    mov rax, 1
    push rax
    pop rax
    pop rbx
    and ebx, eax
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    lea rax, .str7[rip]
    push rax
    pop rdi # load print
    call waccrt_println_str
    mov rax, 1
    push rax
    mov rax, 1
    push rax
    pop rax
    pop rbx
    or ebx, eax
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov rax, 1
    push rax
    mov rax, 0
    push rax
    pop rax
    pop rbx
    or ebx, eax
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov rax, 0
    push rax
    mov rax, 0
    push rax
    pop rax
    pop rbx
    or ebx, eax
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    mov rax, 0
    push rax
    mov rax, 1
    push rax
    pop rax
    pop rbx
    or ebx, eax
    push rbx
    pop rdi # load print
    call waccrt_println_bool
    xor rax, rax
.ret_main:
    add rsp, 80
    pop rbp
    ret
.section .rodata
.str0:
    .string "=="
.str1:
    .string "!="
.str2:
    .string "<"
.str3:
    .string "<="
.str4:
    .string ">"
.str5:
    .string ">="
.str6:
    .string "&&"
.str7:
    .string "||"

