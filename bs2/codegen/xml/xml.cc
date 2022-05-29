#include <cassert>
#include <fmt/core.h>
#include <string>

#include "xml.hh"

/* #region main */
void XmlCodegen::start_main() { open("main"); }
void XmlCodegen::end_main() { close("main"); }
/* #endregion main */

/* #region function */
void XmlCodegen::start_function(std::string_view name, const Type &ret) {
  open("fn");
  open("name");
  line(name);
  close("name");
  open("ret");
  type(ret);
  close("ret");
  open("args");
}

void XmlCodegen::add_arg(std::string_view name, const Type &ty) {
  open("arg");
  open("name");
  line(name);
  close("name");
  open("ty");
  type(ty);
  close("ty");
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
void XmlCodegen::start_free() { open("free"); }
void XmlCodegen::end_free() { close("free"); }
void XmlCodegen::start_return() { open("return"); }
void XmlCodegen::end_return() { close("return"); }
void XmlCodegen::start_exit() { open("exit"); }
void XmlCodegen::end_exit() { close("exit"); }
void XmlCodegen::start_print() { open("print"); }
void XmlCodegen::end_print() { close("print"); }
void XmlCodegen::start_println() { open("println"); }
void XmlCodegen::end_println() { close("println"); }
void XmlCodegen::if_cond() {
  open("if");
  open("cond");
}
void XmlCodegen::if_when() {
  close("cond");
  open("when");
}
void XmlCodegen::if_else() {
  close("when");
  open("else");
}
void XmlCodegen::if_end() {
  close("else");
  close("if");
}
void XmlCodegen::while_cond() {
  open("while");
  open("cond");
}
void XmlCodegen::while_body() {
  close("cond");
  open("body");
}
void XmlCodegen::while_end() {
  close("body");
  close("while");
}
void XmlCodegen::start_block() { open("block"); }
void XmlCodegen::end_block() { close("block"); }
/* #endregion stmt */

/* #region expr */
void XmlCodegen::e_push_number(int32_t n) {
  std::string s = fmt::format("{}", n);
  open("num");
  line(s);
  close("num");
}
void XmlCodegen::e_push_local(std::string_view name) {
  open("local");
  line(name);
  close("local");
}
/* endregion */

/* #region assign */
void XmlCodegen::add_var(std::string_view name, const Type &ty) {
  open("var");
  open("name");
  line(name);
  close("name");
  open("ty");
  type(ty);
  close("ty");
  close("var");
}

void XmlCodegen::assign_addr_local(std::string_view name) {
  open("addr_local");
  line(name);
  close("addr_local");
}
void XmlCodegen::assign_addr_fst() {
  open("addr_fst");
  close("addr_fst");
}
void XmlCodegen::assign_addr_snd() {
  open("addr_snd");
  close("addr_snd");
}
void XmlCodegen::assign_do() {
  open("assign_do");
  close("assign_do");
}
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

std::string XmlCodegen::finish() {
  close("unit");
  assert(indent == 0);
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

/* #endregion */
