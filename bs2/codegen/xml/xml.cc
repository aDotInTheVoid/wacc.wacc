#include <cassert>
#include <fmt/core.h>
#include <string>

#include "xml.hh"

/* #region main */
void XmlCodegen::start_main() { open("main"); }
void XmlCodegen::end_main() { close("main"); }
/* #endregion main */

/* #region function */
void XmlCodegen::start_function(std::string_view name) {
  open("fn");
  open("name");
  line(name);
  close("name");
  open("args");
}

void XmlCodegen::add_arg(int32_t offset) {
  open("arg");
  line(fmt::format("{}", offset));
  close("arg");
}

void XmlCodegen::start_function_body() {
  close("args");
  open("body");
}

void XmlCodegen::end_function() {
  close("body");
  close("fn");
}
/* #endregion */

/* #region stmt */
void XmlCodegen::pop_free(FreeKind) { open_close("free"); }
void XmlCodegen::pop_return() { open_close("return"); }
void XmlCodegen::pop_exit() { open_close("exit"); }
void XmlCodegen::pop_print(PrintKind pk, bool nl) {
  open("print");
  open("kind");
  line(print_kind_name(pk));
  close("kind");
  open("newline");
  line(nl ? "true" : "false");
  close("newline");
  close("print");
}
void XmlCodegen::do_read(const Type &ty) {
  open("read");
  open("ty");
  type(ty);
  close("ty");
  close("read");
}

void XmlCodegen::if_cond() {
  open("if");
  open("cond");
}
int32_t XmlCodegen::if_when() {
  close("cond");
  open("when");
  return -1;
}
int32_t XmlCodegen::if_else(int32_t) {
  close("when");
  open("else");
  return -1;
}
void XmlCodegen::if_end(int32_t) {
  close("else");
  close("if");
}
int32_t XmlCodegen::while_cond() {
  open("while");
  open("cond");
  return -1;
}
int32_t XmlCodegen::while_body() {
  close("cond");
  open("body");
  return -1;
}
void XmlCodegen::while_end(int32_t, int32_t) {
  close("body");
  close("while");
}
void XmlCodegen::start_block() { open("block"); }
void XmlCodegen::end_block() { close("block"); }
/* #endregion stmt */

/* #region expr */
void XmlCodegen::e_push_number(int32_t n_neg) {
  int64_t n = n_neg;
  int64_t n2 = -n;
  std::string s = fmt::format("{}", n2);
  open("num");
  line(s);
  close("num");
}
void XmlCodegen::e_push_bool(bool b) {
  if (b) {
    open_close("true");
  } else {
    open_close("false");
  }
}
void XmlCodegen::e_push_null() { open_close("null"); }
void XmlCodegen::e_push_newpair() { open_close("newpair"); }
void XmlCodegen::e_fst() { open_close("fst"); }
void XmlCodegen::e_snd() { open_close("snd"); }
void XmlCodegen::e_len() { open_close("len"); }
void XmlCodegen::e_not() { open_close("not"); }
void XmlCodegen::e_neg() { open_close("neg"); }
void XmlCodegen::e_array_elem() { open_close("array_elem"); }

void XmlCodegen::e_push_array_lit(int32_t nels) {
  open("array_lit");
  line(fmt::format("{}", nels));
  close("array_lit");
}

void XmlCodegen::e_push_string(std::string_view s) {
  open("str");
  line(s);
  close("str");
}
void XmlCodegen::e_push_char(std::string_view c) {
  open("char");
  line(c);
  close("char");
}
void XmlCodegen::e_push_local(int32_t locno) {
  open("local");
  line(fmt::format("{}", locno));
  close("local");
}
void XmlCodegen::e_pop_op(Op op) {
  open("op");
  line(op_name(op));
  close("op");
}

/* endregion */

/* #region assign */
// void XmlCodegen::add_var(std::string_view name, const Type &ty) {
//   open("var");
//   open("name");
//   line(name);
//   close("name");
//   open("ty");
//   type(ty);
//   close("ty");
//   close("var");
// }

void XmlCodegen::assign_addr_local(int32_t name) {
  open("addr_local");
  line(fmt::format("{}", name));
  close("addr_local");
}
void XmlCodegen::assign_addr_fst() { open_close("addr_fst"); }
void XmlCodegen::assign_addr_snd() { open_close("addr_snd"); }
void XmlCodegen::assign_addr_array() { open_close("addr_array"); }
void XmlCodegen::assign_do() { open_close("assign_do"); }
/* #endregion */

/* #region internal */
void XmlCodegen::type(const Type &t) {
  switch (t.kind_) {
  case TypeKind::Int:
    return line("int");
  case TypeKind::Char:
    return line("char");
  case TypeKind::String:
    return line("string");
  case TypeKind::Bool:
    return line("bool");
  case TypeKind::EraisedPair:
    return line("eraised_pair");
  case TypeKind::Pair:
    open("pair");
    open("left");
    type(*t.p1_);
    close("left");
    open("right");
    type(*t.p2_);
    close("right");
    close("pair");
    return;
  case TypeKind::Array:
    open("array");
    type(*t.p1_);
    close("array");
    return;
  }
}
void XmlCodegen::call_func(std::string_view name, int32_t nargs) {
  open("call_func");
  open("name");
  line(name);
  close("name");
  open("nargs");
  line(fmt::format("{}", nargs));
  close("nargs");
  close("call_func");
}

std::string XmlCodegen::finish() {
  close("unit");
  // assert(indent == 0);
  return buff;
}

void XmlCodegen::line(std::string_view l) {
  for (size_t i = 0; i < indent; i++) {
    buff += " ";
  }
  buff += l;
  buff += "\n";
}

void XmlCodegen::close(const char *name) {
  indent -= indent_width;
  line(fmt::format("</{}>", name));
}

void XmlCodegen::open(const char *name) {
  line(fmt::format("<{}>", name));
  indent += indent_width;
}
void XmlCodegen::open_close(const char *name) {
  open(name);
  close(name);
}

/* #endregion */
