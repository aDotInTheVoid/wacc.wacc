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
  virtual void start_function(std::string_view name, Type &ret) = 0;
  virtual void end_function() = 0;
};

#endif