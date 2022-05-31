#ifndef BS2_CODEGEN_HH
#define BS2_CODEGEN_HH

#include <string>

#include "op.hh"
#include "type.hh"

struct Codegen {
  std::string buff;
  virtual std::string finish() = 0;
  virtual ~Codegen() = default;

  // Parser hooks
  virtual void start_main() = 0;
  virtual void end_main() = 0;
  // Function
  virtual void start_function(std::string_view name, const Type &ret) = 0;
  virtual void add_arg(std::string_view name, const Type &ty) = 0;
  virtual void start_function_body() = 0;
  virtual void end_function() = 0;
  // Stmt
  virtual void pop_free(FreeKind) = 0;
  virtual void pop_return() = 0;
  virtual void pop_exit() = 0;
  virtual void pop_print(PrintKind, bool) = 0;
  virtual void if_cond() = 0;
  virtual int32_t if_when() = 0;
  virtual int32_t if_else(int32_t) = 0;
  virtual void if_end(int32_t) = 0;
  virtual int32_t while_cond() = 0;
  virtual int32_t while_body() = 0;
  virtual void while_end(int32_t j_cond, int32_t j_body) = 0;
  virtual void start_block() = 0;
  virtual void end_block() = 0;
  // Expr
  virtual void e_push_number(int32_t) = 0;
  virtual void e_push_bool(bool) = 0;
  virtual void e_push_string(std::string_view) = 0;
  virtual void e_push_char(std::string_view) = 0;
  virtual void e_push_local(std::string_view) = 0;
  virtual void e_push_null() = 0;
  virtual void e_push_newpair() = 0;
  virtual void e_fst() = 0;
  virtual void e_snd() = 0;
  virtual void e_array_elem() = 0;
  virtual void e_push_array_lit(int32_t) = 0;

  virtual void e_pop_op(Op) = 0;
  // Assignment
  virtual void add_var(std::string_view name, const Type &ty) = 0;
  virtual void assign_addr_local(std::string_view) = 0; // Push address of local
  virtual void assign_addr_fst() = 0;
  virtual void assign_addr_snd() = 0;
  virtual void assign_do() = 0; // Pop value and address.

  virtual void call_func(std::string_view, int32_t nargs) = 0;
};

#endif