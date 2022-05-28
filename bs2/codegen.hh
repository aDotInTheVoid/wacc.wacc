#ifndef BS2_CODEGEN_HH
#define BS2_CODEGEN_HH

#include <string>

#include "type.hh"

struct Codegen {
  std::string buff;
  virtual std::string finish() = 0;
  virtual ~Codegen() = default;

  // Parser hooks
  virtual void start_main() = 0;
  virtual void end_main() = 0;
  // Function
  virtual void start_function(std::string_view name, Type &ret) = 0;
  virtual void add_arg(std::string_view name, Type &ty) = 0;
  virtual void start_function_body() = 0;
  virtual void end_function() = 0;
  // Stmt
  virtual void start_free() = 0;
  virtual void end_free() = 0;
  virtual void start_return() = 0;
  virtual void end_return() = 0;
  virtual void start_exit() = 0;
  virtual void end_exit() = 0;
  virtual void start_print() = 0;
  virtual void end_print() = 0;
  virtual void start_println() = 0;
  virtual void end_println() = 0;
  virtual void if_cond() = 0;
  virtual void if_when() = 0;
  virtual void if_else() = 0;
  virtual void if_end() = 0;
  virtual void while_cond() = 0;
  virtual void while_body() = 0;
  virtual void while_end() = 0;
  virtual void start_block() = 0;
  virtual void end_block() = 0;
  // Expr
  virtual void e_push_number(int32_t) = 0;
  // Assignment
  virtual void add_var(std::string_view name, Type &ty) = 0;
  virtual void assign_addr_local(std::string_view) = 0; // Push address of local
  virtual void assign_do() = 0; // Pop value and address.
};

#endif