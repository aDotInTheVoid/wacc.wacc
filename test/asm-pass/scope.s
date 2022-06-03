.intel_syntax noprefix
.global main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 400
    lea rax, [rbp-8]
    push rax # assign_addr_local
    lea rax, .str0[rip]
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-16]
    push rax # assign_addr_local
    mov eax, 5
    push rax # e_push_number
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-24]
    push rax # assign_addr_local
    mov rax, 'x'
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-32]
    push rax # assign_addr_local
    mov rax, 1
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-40]
    push rax # assign_addr_local
    lea rax, .str1[rip]
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-48]
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
    lea rax, [rbp-56]
    push rax # assign_addr_local
    mov rax, 'x'
    push rax
    mov rax, 'y'
    push rax
    mov rax, 'z'
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
    lea rax, [rbp-64]
    push rax # assign_addr_local
    mov rax, 1
    push rax
    mov rax, 0
    push rax
    mov rax, 1
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
    lea rax, [rbp-72]
    push rax # assign_addr_local
    lea rax, .str2[rip]
    push rax
    lea rax, .str3[rip]
    push rax
    lea rax, .str4[rip]
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
    lea rax, [rbp-80]
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
    lea rax, [rbp-88]
    push rax # assign_addr_local
    mov rax, 'a'
    push rax
    mov rax, 1
    push rax
    pop rsi
    pop rdi
    sub rsp, 8
    call waccrt_pair_new
    add rsp, 8
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-96]
    push rax # assign_addr_local
    mov rax, 'b'
    push rax
    mov rax, 0
    push rax
    pop rsi
    pop rdi
    sub rsp, 8
    call waccrt_pair_new
    add rsp, 8
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-104]
    push rax # assign_addr_local
    mov rax, [rbp-88] # e_push_local
    push rax # e_push_local
    mov rax, [rbp-96] # e_push_local
    push rax # e_push_local
    mov rdi, 2
    lea rsi, [rsp+8]
    sub rsp, 8
    call waccrt_array_new
    add rsp, 8
    pop rdx
    pop rdx
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-112]
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
    lea rax, [rbp-120]
    push rax # assign_addr_local
    mov rax, 'a'
    push rax
    mov rax, 'b'
    push rax
    mov rax, 'c'
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
    lea rax, [rbp-128]
    push rax # assign_addr_local
    mov rax, [rbp-112] # e_push_local
    push rax # e_push_local
    mov rax, [rbp-120] # e_push_local
    push rax # e_push_local
    pop rsi
    pop rdi
    sub rsp, 8
    call waccrt_pair_new
    add rsp, 8
    push rax
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-136]
    push rax # assign_addr_local
    mov rax, [rbp-128] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-144]
    push rax # assign_addr_local
    mov rax, [rbp-128] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax+8]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, .str5[rip]
    push rax
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-136] # e_push_local
    push rax # e_push_local
    mov eax, 0
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # load print
    call waccrt_print_i32
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-136] # e_push_local
    push rax # e_push_local
    mov eax, 1
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # load print
    call waccrt_print_i32
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-136] # e_push_local
    push rax # e_push_local
    mov eax, 2
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # load print
    call waccrt_print_i32
    lea rax, .str6[rip]
    push rax
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-144] # e_push_local
    push rax # e_push_local
    mov eax, 0
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # load print
    call waccrt_print_char
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-144] # e_push_local
    push rax # e_push_local
    mov eax, 1
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # load print
    call waccrt_print_char
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-144] # e_push_local
    push rax # e_push_local
    mov eax, 2
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # load print
    call waccrt_print_char
    lea rax, .str7[rip]
    push rax
    pop rdi # load print
    call waccrt_println_str
    lea rax, [rbp-112]
    push rax # assign_addr_local
    mov rax, [rbp-104] # e_push_local
    push rax # e_push_local
    mov eax, 0
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-120]
    push rax # assign_addr_local
    mov rax, [rbp-112] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-128]
    push rax # assign_addr_local
    mov rax, [rbp-112] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax+8]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-136]
    push rax # assign_addr_local
    mov rax, [rbp-104] # e_push_local
    push rax # e_push_local
    mov eax, 1
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-144]
    push rax # assign_addr_local
    mov rax, [rbp-136] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-152]
    push rax # assign_addr_local
    mov rax, [rbp-136] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax+8]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, .str8[rip]
    push rax
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-112] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_ptr
    lea rax, .str9[rip]
    push rax
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-120] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_char
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-128] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_bool
    lea rax, .str10[rip]
    push rax
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-136] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_ptr
    lea rax, .str11[rip]
    push rax
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-144] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_char
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-152] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_bool
    lea rax, .str12[rip]
    push rax
    pop rdi # load print
    call waccrt_println_str
    lea rax, [rbp-88]
    push rax # assign_addr_local
    mov rax, [rbp-80] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-96]
    push rax # assign_addr_local
    mov rax, [rbp-80] # e_push_local
    push rax # e_push_local
    pop rax
    mov rdi, [rax+8]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    mov rax, [rbp-88] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_i32
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-96] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    lea rax, [rbp-80]
    push rax # assign_addr_local
    mov rax, [rbp-72] # e_push_local
    push rax # e_push_local
    mov eax, 0
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-88]
    push rax # assign_addr_local
    mov rax, [rbp-72] # e_push_local
    push rax # e_push_local
    mov eax, 1
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-96]
    push rax # assign_addr_local
    mov rax, [rbp-72] # e_push_local
    push rax # e_push_local
    mov eax, 2
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    mov rax, [rbp-80] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-88] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-96] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_str
    mov rax, [rbp-64] # e_push_local
    push rax # e_push_local
    mov eax, 0
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # load print
    call waccrt_print_bool
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-64] # e_push_local
    push rax # e_push_local
    mov eax, 1
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # load print
    call waccrt_print_bool
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-64] # e_push_local
    push rax # e_push_local
    mov eax, 2
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # load print
    call waccrt_println_bool
    mov rax, [rbp-56] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_char_array
    lea rax, [rbp-56]
    push rax # assign_addr_local
    mov rax, [rbp-48] # e_push_local
    push rax # e_push_local
    mov eax, 0
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-64]
    push rax # assign_addr_local
    mov rax, [rbp-48] # e_push_local
    push rax # e_push_local
    mov eax, 1
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    lea rax, [rbp-72]
    push rax # assign_addr_local
    mov rax, [rbp-48] # e_push_local
    push rax # e_push_local
    mov eax, 2
    push rax # e_push_number
    pop rbx
    pop rax
    mov rdi, [rax+rbx*8]
    push rdi
    pop rdi # assign_do val
    pop rax # assign_do addr
    mov [rax], rdi
    mov rax, [rbp-56] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_i32
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-64] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_i32
    mov rax, [rbp-8] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_print_str
    mov rax, [rbp-72] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    mov rax, [rbp-40] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_str
    mov rax, [rbp-32] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_bool
    mov rax, [rbp-24] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_char
    mov rax, [rbp-16] # e_push_local
    push rax # e_push_local
    pop rdi # load print
    call waccrt_println_i32
    xor rax, rax
.ret_main:
    add rsp, 400
    pop rbp
    ret
.section .rodata
.str0:
    .string ", "
.str1:
    .string "this is a string"
.str2:
    .string "array"
.str3:
    .string "of"
.str4:
    .string "strings"
.str5:
    .string "( ["
.str6:
    .string "] , ["
.str7:
    .string "] )"
.str8:
    .string "[ "
.str9:
    .string " = ("
.str10:
    .string "), "
.str11:
    .string " = ("
.str12:
    .string ") ]"

