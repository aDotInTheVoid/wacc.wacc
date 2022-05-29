#include "x64.hh"

#include <cassert>

void X64Codegen::start_main() { assert(0); }
void X64Codegen::end_main() { assert(0); }
std::string X64Codegen::finish() { assert(0); }
// Function
void X64Codegen::start_function(std::string_view name, Type &ret) { assert(0); }
void X64Codegen::add_arg(std::string_view name, Type &ty) { assert(0); }
void X64Codegen::start_function_body() { assert(0); }
void X64Codegen::end_function() { assert(0); }
// Stmt
void X64Codegen::start_free() { assert(0); }
void X64Codegen::end_free() { assert(0); }
void X64Codegen::start_return() { assert(0); }
void X64Codegen::end_return() { assert(0); }
void X64Codegen::start_exit() { assert(0); }
void X64Codegen::end_exit() { assert(0); }
void X64Codegen::start_print() { assert(0); }
void X64Codegen::end_print() { assert(0); }
void X64Codegen::start_println() { assert(0); }
void X64Codegen::end_println() { assert(0); }
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
void X64Codegen::e_push_number(int32_t) { assert(0); }
void X64Codegen::e_push_local(std::string_view) { assert(0); }

// Assignment
void X64Codegen::add_var(std::string_view name, Type &ty) { assert(0); }
void X64Codegen::assign_addr_local(std::string_view) {
  assert(0);
} // Push address of local
void X64Codegen::assign_do() { assert(0); } // Pop value and address.
void X64Codegen::assign_addr_fst() { assert(0); }
void X64Codegen::assign_addr_snd() { assert(0); }