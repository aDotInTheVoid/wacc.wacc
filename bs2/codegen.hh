#ifndef BS2_CODEGEN_HH
#define BS2_CODEGEN_HH

#include <string>

struct Codegen {
  std::string buff;
  virtual std::string finish() = 0;
  virtual ~Codegen() = default;
};

#endif