
#define TODO() wacc_cpp_todo_fail(__FILE__, __LINE__, __func__)

[[noreturn]] void wacc_cpp_todo_fail(const char *file, int line,
                                     const char *func);
