#include <cassert>
#include <iostream>
#include <utility>

#include <fmt/core.h>

#include "type.hh"
#include "x64.hh"

/*
 * We generate x64 assembly code for GNU GAS using intel syntax.
 *
 * - https://en.wikibooks.org/wiki/X86_Disassembly/The_Stack
 *
 * Needing to keep a 16-byte stack frame is quite annoying.
 */

static const char *rnames[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};

#define MAX_LOCS 50
#define LOC_SIZE 8

static int32_t addr_of(int32_t locno) {
  assert(locno < MAX_LOCS);
  return LOC_SIZE * (locno + 1);
}

X64Codegen::X64Codegen() {
  add_dir(".intel_syntax noprefix");
  add_dir(".global main");
}

void X64Codegen::start_main() { start_function("main"); }
void X64Codegen::end_main() {
  add_instr("xor rax, rax");
  end_function();
  add_dir(".section .rodata");
  for (size_t i = 0; i < strs_.size(); i++) {
    add_dir(fmt::format(".str{}:", i));
    add_instr(fmt::format(".string {}", strs_[i]));
  }
}
std::string X64Codegen::finish() { return buff_; }
// Function
void X64Codegen::start_function(std::string_view name) {
  nargs_ = 0;
  cur_func_ = name;
  n_locs_ = 0;
  // locs_.clear();
  assert(npush_ == 0);

  add_dir(fmt::format("{}:", name));

  add_instr("push rbp"); // This doesn't get counted in npush_
  add_instr("mov rbp, rsp");
  add_instr(fmt::format("sub rsp, {}", MAX_LOCS * LOC_SIZE));
}

void X64Codegen::add_arg(int32_t argno) {
  add_instr(fmt::format("mov [rbp-{}], {}", addr_of(argno), rnames[argno]));
}
void X64Codegen::call_func(std::string_view name, int32_t nargs) {
  for (int32_t i = nargs - 1; i >= 0; i--)
    add_pop(rnames[i]);
  // TODO: Is the stack aligned here
  add_call(name);
  add_push("rax");
}

void X64Codegen::start_function_body() {}
void X64Codegen::end_function() {
  add_dir(fmt::format(".ret_{}:", cur_func_));
  add_instr(fmt::format("add rsp, {}", MAX_LOCS * LOC_SIZE));
  assert(npush_ == 0);
  add_instr("pop rbp"); // Doens't get counted in npush_
  add_instr("ret");
}
// Stmt

void X64Codegen::pop_print(PrintKind pk, bool multiline) {
  add_pop("rdi # load print");
  // TODO: Is the stack aligned here
  add_call(fmt::format("waccrt_print{}_{}", multiline ? "ln" : "",
                       print_kind_name(pk)));
}
void X64Codegen::do_read(const Type &ty) { assert(0); }

void X64Codegen::pop_free(FreeKind fk) {
  add_pop("rdi");
  add_call(fmt::format("waccrt_{}_delete", free_kind_name(fk)));
}
void X64Codegen::pop_return() {
  add_pop("rax");
  add_instr(fmt::format("jmp .ret_{}", cur_func_));
}
void X64Codegen::pop_exit() {
  add_pop(rnames[0]);
  add_call("waccrt_exit");
}
void X64Codegen::if_cond() {} // nop
int32_t X64Codegen::if_when() {
  int32_t j = jno();
  add_pop("rax");
  add_instr("test rax, rax");
  add_instr(fmt::format("je .CF{}", j));
  return j;
}
int32_t X64Codegen::if_else(int32_t rno) {
  int32_t j = jno();
  add_instr(fmt::format("jmp .CF{}", j));
  add_dir(fmt::format(".CF{}:", rno));
  return j;
}
void X64Codegen::if_end(int32_t jno) { add_dir(fmt::format(".CF{}:", jno)); }
int32_t X64Codegen::while_cond() {
  int32_t j_cond = jno();
  add_dir(fmt::format(".CF{}:", j_cond));
  return j_cond;
}
int32_t X64Codegen::while_body() {
  int32_t j_cond = jno();
  add_pop("rax");
  add_instr("test rax, rax");
  add_instr(fmt::format("je .CF{}", j_cond));
  return j_cond;
}
void X64Codegen::while_end(int32_t j_cond, int32_t j_body) {
  add_instr(fmt::format("jmp .CF{}", j_cond));
  add_dir(fmt::format(".CF{}:", j_body));
}
void X64Codegen::start_block() { assert(0); }
void X64Codegen::end_block() { assert(0); }
// Expr
void X64Codegen::e_push_number(int32_t n) {
  add_instr(fmt::format("mov eax, {}", n));
  add_push("rax # e_push_number");
}
void X64Codegen::e_push_local(int32_t locno) {
  add_instr(fmt::format("mov rax, [rbp-{}] # e_push_local", addr_of(locno)));
  add_push("rax # e_push_local");
}
void X64Codegen::e_push_char(std::string_view c) {
  // assert(c.size() == 3); // TODO: Escape
  // // https://sourceware.org/binutils/docs-2.38/as/Strings.html
  // // GAS syntax is probably a superset of wacc syntax
  // int cno = c[1];
  add_instr(fmt::format("mov rax, {}", c));
  add_push("rax"); // TODO: x64 Imm version??
}
void X64Codegen::e_push_bool(bool b) {
  add_instr(fmt::format("mov rax, {}", b ? 1 : 0));
  add_push("rax");
}
void X64Codegen::e_push_null() {
  add_instr("xor eax, eax");
  add_push("rax");
}
void X64Codegen::e_push_newpair() {
  add_pop("rsi"); // rsi = snd
  add_pop("rdi"); // rdi = fst
  add_call("waccrt_pair_new");
  add_push("rax");
}
void X64Codegen::e_fst() {
  add_pop("rax");
  add_instr("mov rdi, [rax]");
  add_push("rdi");
}
void X64Codegen::e_snd() {
  add_pop("rax");
  add_instr("mov rdi, [rax+8]");
  add_push("rdi");
}
void X64Codegen::e_len() {
  add_pop("rax");
  add_instr("mov rdi, [rax-8]");
  add_push("rdi");
}
void X64Codegen::e_not() {
  add_pop("rax");
  add_instr("xor rax, 1");
  add_push("rax");
}
void X64Codegen::e_neg() {
  add_pop("rax");
  add_instr("neg eax");
  add_push("rax");
}
void X64Codegen::e_array_elem() {
  add_pop("rbx"); // rbx = index
  add_pop("rax"); // rax = array
  add_instr("mov rdi, [rax+rbx*8]");
  add_push("rdi");
}
void X64Codegen::e_push_array_lit(int32_t nels) {
  add_instr(fmt::format("mov rdi, {}", nels));                 // arg1 = nels
  add_instr(fmt::format("lea rsi, [rsp+{}]", (nels - 1) * 8)); // arg2 = array
  add_call("waccrt_array_new");
  // rax = array
  for (int i = 0; i < nels; i++)
    add_pop("rdx");
  add_push("rax");
}

void X64Codegen::e_push_string(std::string_view s) {
  strs_.push_back(s);
  add_instr(fmt::format("lea rax, .str{}[rip]", strs_.size() - 1));
  // add_instr("call waccrt_str_new");
  add_push("rax");
}

static const char *test_name(Op op) {
  switch (op) {
  case Op::Eq:
    return "e";
  case Op::Ne:
    return "ne";
  case Op::Lt:
    return "l";
  case Op::Le:
    return "le";
  case Op::Gt:
    return "g";
  case Op::Ge:
    return "ge";
  default:
    fprintf(stderr, "Unknown test op %s\n", op_name(op));
    assert(0);
  }
}

void X64Codegen::e_pop_op(Op op) {
  add_pop("rax"); // rax = rhs
  add_pop("rbx"); // rbx = lhs
  switch (op) {
  case Op::Add:
    add_instr("add ebx, eax");
    break;
  case Op::Sub:
    add_instr("sub ebx, eax");
    break;
  case Op::Mul:
    add_instr("imul ebx, eax");
    break;
  case Op::And:
    add_instr("and ebx, eax"); // TODO: Merge and,sub,mul,and
    break;
  case Op::Or:
    add_instr("or ebx, eax"); // TODO: is bitwize OK here?
    break;
  case Op::Lt:
  case Op::Le:
  case Op::Gt:
  case Op::Ge:
  case Op::Eq:
  case Op::Ne:
    // rbx := rbx < rax
    add_instr("mov rcx, rbx");
    add_instr("xor ebx, ebx");
    add_instr("cmp rcx, rax");
    add_instr(fmt::format("set{} bl", test_name(op)));
    break;
  default:
    fprintf(stderr, "Unhandled op: %s\n", op_name(op));
    assert(0);
  }
  add_push("rbx");
}

// Assignment
// void X64Codegen::add_var(std::string_view name, const Type &_) {
//   int32_t locno = n_locs_++;
//   if (n_locs_ > MAX_LOCS) {
//     std::cerr << fmt::format(
//         "Too many locals in {}, now have {}, the latest being {}\n",
//         cur_func_, n_locs_, name);
//     exit(1);
//   }
//   locs_[name] = locno;
// }
// Push the addr of a local to the stack
void X64Codegen::assign_addr_local(int32_t locno) {
  add_instr(fmt::format("lea rax, [rbp-{}]", addr_of(locno)));
  add_push("rax # assign_addr_local");
} // Push address of local
void X64Codegen::assign_do() {
  add_pop("rdi # assign_do val");  // Value
  add_pop("rax # assign_do addr"); // Address
  add_instr("mov [rax], rdi");
} // Pop value and address.
void X64Codegen::assign_addr_fst() {
  add_pop("rax");
  add_instr("mov rbx, [rax]");
  // add_instr("lea rbx, [rax]");
  add_push("rbx");
}
void X64Codegen::assign_addr_snd() {
  add_pop("rax");
  add_instr("mov rbx, [rax]"); // Fo
  add_instr("add rbx, 8");
  // add_instr("lea rbx, [rax+8]");
  add_push("rbx");
}
void X64Codegen::assign_addr_array() {
  add_pop("rbx # array index"); // rbx = index
  add_pop("rax # array base");  // rax = array
  add_instr("mov rax, [rax]");
  add_instr("lea rcx, [rax+rbx*8]");
  add_push("rcx");
}

void X64Codegen::add_dir(std::string_view s) {
  buff_ += s;
  buff_ += "\n";
}
void X64Codegen::add_instr(std::string_view s) {
  buff_ += "    ";
  buff_ += s;
  buff_ += "\n";
}
void X64Codegen::add_push(const char *reg) {
  add_instr(fmt::format("push {}", reg));
  npush_++;
}
void X64Codegen::add_pop(const char *reg) {
  add_instr(fmt::format("pop {}", reg));
  npush_--;
}

void X64Codegen::add_call(std::string_view name) {
  if (npush_ % 2 != 0)
    add_instr("sub rsp, 8"); // Allign stack
  add_instr(fmt::format("call {}", name));
  if (npush_ % 2 != 0)
    add_instr("add rsp, 8"); // Deallign stack
  // TODO: Make these methods
}

int32_t X64Codegen::jno() { return jno_++; }