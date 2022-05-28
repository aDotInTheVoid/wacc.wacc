#ifndef BS2_CODEGEN_XML_XML_HH
#define BS2_CODEGEN_XML_XML_HH

#include "codegen.hh"
#include <fmt/core.h>

const size_t indent_width = 2;

struct XmlCodegen : Codegen {
  size_t indent = 0;
  XmlCodegen() { open("unit"); }
  std::string finish();

  // Parser hooks
  void start_main();
  void end_main();

  void start_function(std::string_view name, Type &ret);
  virtual void add_arg(std::string_view name, Type &ty);
  virtual void start_function_body();
  void end_function();

  void type(Type &t);

  // Internal
  void line(std::string_view l);
  void open(const char *name);
  void close(const char *name);
};

#endif