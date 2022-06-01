#ifndef BS2_CODEGEN_X64_X64_HH
#define BS2_CODEGEN_X64_X64_HH

#include <map>
#include <string>
#include <vector>

#include "codegen.hh"

struct X64Codegen : Codegen {
  std::string buff_;
  int32_t n_locs_ = 0;
  int32_t jno_ = 0;
  int32_t nargs_ = 0;
  int32_t npush_ = 0;
  std::vector<std::string_view> strs_;
  std::map<std::string_view, int32_t> locs_;
  std::string_view cur_func_;
  // std::map<std::string_view, Type> locs_ty_;

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
  int32_t if_when() override;
  int32_t if_else(int32_t) override;
  void if_end(int32_t) override;
  int32_t while_cond() override;
  int32_t while_body() override;
  void while_end(int32_t, int32_t) override;
  void start_block() override;
  void end_block() override;
  // Expr
  void e_push_number(int32_t) override;
  void e_push_bool(bool) override;
  void e_push_string(std::string_view) override;
  void e_push_char(std::string_view) override;
  void e_push_local(std::string_view) override;
  void e_push_null() override;
  void e_push_newpair() override;
  void e_fst() override;
  void e_snd() override;
  void e_len() override;
  void e_not() override;
  void e_neg() override;
  void e_array_elem() override;
  void e_push_array_lit(int32_t) override;
  void e_pop_op(Op) override;

  // Assignment
  void add_var(std::string_view name, const Type &ty) override;
  void assign_addr_local(std::string_view) override; // Push address of local
  void assign_do() override;                         // Pop value and address.
  void assign_addr_fst() override;
  void assign_addr_snd() override;
  void assign_addr_array() override;
  void call_func(std::string_view, int32_t nargs) override;

  void add_dir(std::string_view);
  void add_instr(std::string_view);
  void add_push(const char *);
  void add_pop(const char *);
  void add_call(std::string_view name);

  int32_t jno();
};

#endif