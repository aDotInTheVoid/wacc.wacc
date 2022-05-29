#ifndef BS2_CODEGEN_X64_X64_HH
#define BS2_CODEGEN_X64_X64_HH

#include <map>
#include <string>

#include "codegen.hh"

struct X64Codegen : Codegen {
  std::string buff_;
  int32_t n_locs_ = 0;
  std::map<std::string_view, int32_t> locs_;

  X64Codegen();
  ~X64Codegen() override = default;

  // Parser hooks
  void start_main() override;
  void end_main() override;
  std::string finish();
  // Function
  void start_function(std::string_view name, const Type &ret) override;
  void add_arg(std::string_view name, const Type &ty) override;
  void start_function_body() override;
  void end_function() override;
  // Stmt
  void pop_free(FreeKind) override;
  void pop_return() override;
  void pop_exit() override;
  void pop_print(PrintKind, bool) override;
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
  void add_var(std::string_view name, const Type &ty) override;
  void assign_addr_local(std::string_view) override; // Push address of local
  void assign_do() override;                         // Pop value and address.
  void assign_addr_fst() override;
  void assign_addr_snd() override;

  void add_dir(std::string_view);
  void add_instr(std::string_view);
};

#endif