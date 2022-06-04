.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 400
    lea rax, .str0[rip]
    push rax
    pop rdi # load print
    call waccrt_println_str
    mov eax, 1
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rsi
    pop rdi
    xor eax, eax
    cmp rdi, rsi
    sete al
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 1
    push rax # e_push_number
    mov eax, 2
    push rax # e_push_number
    pop rsi
    pop rdi
    xor eax, eax
    cmp rdi, rsi
    sete al
    push rax
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
    pop rsi
    pop rdi
    xor eax, eax
    cmp rdi, rsi
    setne al
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 7
    push rax # e_push_number
    mov eax, 7
    push rax # e_push_number
    pop rsi
    pop rdi
    xor eax, eax
    cmp rdi, rsi
    setne al
    push rax
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
    pop rsi
    pop rdi
    xor eax, eax
    cmp edi, esi
    setl al
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 1
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rsi
    pop rdi
    xor eax, eax
    cmp edi, esi
    setl al
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 2
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rsi
    pop rdi
    xor eax, eax
    cmp edi, esi
    setl al
    push rax
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
    pop rsi
    pop rdi
    xor eax, eax
    cmp edi, esi
    setle al
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 1
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rsi
    pop rdi
    xor eax, eax
    cmp edi, esi
    setle al
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 2
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rsi
    pop rdi
    xor eax, eax
    cmp edi, esi
    setle al
    push rax
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
    pop rsi
    pop rdi
    xor eax, eax
    cmp edi, esi
    setg al
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 1
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rsi
    pop rdi
    xor eax, eax
    cmp edi, esi
    setg al
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 1
    push rax # e_push_number
    mov eax, 2
    push rax # e_push_number
    pop rsi
    pop rdi
    xor eax, eax
    cmp edi, esi
    setg al
    push rax
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
    pop rsi
    pop rdi
    xor eax, eax
    cmp edi, esi
    setge al
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 1
    push rax # e_push_number
    mov eax, 1
    push rax # e_push_number
    pop rsi
    pop rdi
    xor eax, eax
    cmp edi, esi
    setge al
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov eax, 1
    push rax # e_push_number
    mov eax, 2
    push rax # e_push_number
    pop rsi
    pop rdi
    xor eax, eax
    cmp edi, esi
    setge al
    push rax
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
    pop rsi
    pop rdi
    and esi, edi
    movzx eax, sil
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov rax, 1
    push rax
    mov rax, 0
    push rax
    pop rsi
    pop rdi
    and esi, edi
    movzx eax, sil
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov rax, 0
    push rax
    mov rax, 0
    push rax
    pop rsi
    pop rdi
    and esi, edi
    movzx eax, sil
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov rax, 0
    push rax
    mov rax, 1
    push rax
    pop rsi
    pop rdi
    and esi, edi
    movzx eax, sil
    push rax
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
    pop rsi
    pop rdi
    or esi, edi
    movzx eax, sil
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov rax, 1
    push rax
    mov rax, 0
    push rax
    pop rsi
    pop rdi
    or esi, edi
    movzx eax, sil
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov rax, 0
    push rax
    mov rax, 0
    push rax
    pop rsi
    pop rdi
    or esi, edi
    movzx eax, sil
    push rax
    pop rdi # load print
    call waccrt_println_bool
    mov rax, 0
    push rax
    mov rax, 1
    push rax
    pop rsi
    pop rdi
    or esi, edi
    movzx eax, sil
    push rax
    pop rdi # load print
    call waccrt_println_bool
    xor rax, rax
.ret_main:
    add rsp, 400
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

