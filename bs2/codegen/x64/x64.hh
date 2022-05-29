#ifndef BS2_CODEGEN_X64_X64_HH
#define BS2_CODEGEN_X64_X64_HH

#include <string>

#include "codegen.hh"

struct X64Codegen : Codegen {
  std::string buff;
  X64Codegen(){};
  ~X64Codegen() override = default;

  // Parser hooks
  void start_main() override;
  void end_main() override;
  std::string finish();
  // Function
  void start_function(std::string_view name, Type &ret) override;
  void add_arg(std::string_view name, Type &ty) override;
  void start_function_body() override;
  void end_function() override;
  // Stmt
  void start_free() override;
  void end_free() override;
  void start_return() override;
  void end_return() override;
  void start_exit() override;
  void end_exit() override;
  void start_print() override;
  void end_print() override;
  void start_println() override;
  void end_println() override;
  void if_cond() override;
  void if_when() override;
  void if_else() override;
  void if_end() override;
  void while_cond() override;
  void while_body() override;
  void while_end() override;
  void start_block() override;
  void end_block() override;
  // Expr
  void e_push_number(int32_t) override;
  void e_push_local(std::string_view) override;

  // Assignment
  void add_var(std::string_view name, Type &ty) override;
  void assign_addr_local(std::string_view) override; // Push address of local
  void assign_do() override;                         // Pop value and address.
  void assign_addr_fst() override;
  void assign_addr_snd() override;
};

#endif