#ifndef BS2_CODEGEN_XML_XML_HH
#define BS2_CODEGEN_XML_XML_HH

#include "codegen.hh"

const size_t indent_width = 2;

struct XmlCodegen : Codegen {
  size_t indent = 0;
  XmlCodegen() { open("unit"); }
  std::string finish();

  // Parser hooks
  void start_main() override;
  void end_main() override;
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

  // Internal
  void type(const Type &t);
  void line(std::string_view l);
  void open(const char *name);
  void close(const char *name);
  void open_close(const char *name);
};

#endif