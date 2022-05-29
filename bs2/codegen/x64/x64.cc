#include <cassert>

#include <fmt/core.h>

#include "type.hh"
#include "x64.hh"

/*
 * We generate x64 assembly code for GNU GAS using intel syntax.
 *
 * - https://en.wikibooks.org/wiki/X86_Disassembly/The_Stack
 */

#define MAX_LOCS 10
#define LOC_SIZE 8

static int32_t addr_of(int32_t locno) { return LOC_SIZE * (locno + 1); }
static const char *print_fn_name(PrintKind pk) {
  return "i32"; // TODO
}

X64Codegen::X64Codegen() {
  add_dir(".intel_syntax noprefix");
  add_dir(".global main");
}

void X64Codegen::start_main() { start_function("main", type_int()); }
void X64Codegen::end_main() {
  add_instr("xor rax, rax");
  end_function();
}
std::string X64Codegen::finish() { return buff_; }
// Function
void X64Codegen::start_function(std::string_view name, const Type &ret) {
  add_dir(fmt::format("{}:", name));
  add_instr("push rbp");
  add_instr("mov rbp, rsp");
  add_instr(fmt::format("sub rsp, {}", MAX_LOCS * LOC_SIZE));
  // TODO: Reserve stack space?
}
void X64Codegen::add_arg(std::string_view name, const Type &ty) { assert(0); }
void X64Codegen::start_function_body() { assert(0); }
void X64Codegen::end_function() {
  add_instr(fmt::format("add rsp, {}", MAX_LOCS * LOC_SIZE));
  add_instr("pop rbp");
  add_instr("ret");
  // TODO: What needs to be done?
  // Probably reset vars
}
// Stmt

void X64Codegen::pop_print(PrintKind pk, bool multiline) {
  add_instr("pop rdi # load print");
  add_instr(fmt::format("call waccrt_print{}_{}", multiline ? "ln" : "",
                        print_fn_name(pk))); // TODO: Use correct type
}

void X64Codegen::pop_free(FreeKind) { assert(0); }
void X64Codegen::pop_return() { assert(0); }
void X64Codegen::pop_exit() { assert(0); }
void X64Codegen::if_cond() { assert(0); }
void X64Codegen::if_when() { assert(0); }
void X64Codegen::if_else() { assert(0); }
void X64Codegen::if_end() { assert(0); }
void X64Codegen::while_cond() { assert(0); }
void X64Codegen::while_body() { assert(0); }
void X64Codegen::while_end() { assert(0); }
void X64Codegen::start_block() { assert(0); }
void X64Codegen::end_block() { assert(0); }
// Expr
void X64Codegen::e_push_number(int32_t n) {
  add_instr(fmt::format("mov eax, {}", n));
  add_instr("push rax # e_push_number");
}
void X64Codegen::e_push_local(std::string_view name) {
  int32_t locno = locs_[name];
  add_instr(fmt::format("mov rax, [rbp-{}] # e_push_local", addr_of(locno)));
  add_instr("push rax # e_push_local");
}

// Assignment
void X64Codegen::add_var(std::string_view name, const Type &ty) {
  int32_t locno = n_locs_++;
  if (n_locs_ > MAX_LOCS) {
    throw std::runtime_error("Too many locals");
  }
  locs_[name] = locno;
}
// Push the addr of a local to the stack
void X64Codegen::assign_addr_local(std::string_view name) {
  int32_t locno = locs_[name];
  add_instr(fmt::format("lea rax, [rbp-{}]", addr_of(locno)));
  add_instr("push rax # assign_addr_local");
} // Push address of local
void X64Codegen::assign_do() {
  add_instr("pop rdi # assign_do val");  // Value
  add_instr("pop rax # assign_do addr"); // Address
  add_instr("mov [rax], rdi");
} // Pop value and address.
void X64Codegen::assign_addr_fst() { assert(0); }
void X64Codegen::assign_addr_snd() { assert(0); }

void X64Codegen::add_dir(std::string_view s) {
  buff_ += s;
  buff_ += "\n";
}
void X64Codegen::add_instr(std::string_view s) {
  buff_ += "    ";
  buff_ += s;
  buff_ += "\n";
}