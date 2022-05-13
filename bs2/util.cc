#include "util.hh"

#include <cstdlib>
#include <iostream>

[[noreturn]] void wacc_cpp_todo_fail(const char *file, int line,
                                     const char *func) {
  std::cerr << "TODO: " << file << ":" << line << ": " << func << std::endl;
  std::exit(EXIT_FAILURE);
}
