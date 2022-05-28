#include <cassert>
#include <fmt/core.h>

#include "xml.hh"

void XmlCodegen::start_function(std::string_view name, Type &ret) {
  open("fn");
  open("name");
  line(name);
  close("name");
  open("ret");
  type(ret);
  close("ret");
  open("args");
}

void XmlCodegen::add_arg(std::string_view name, Type &ty) {
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

void XmlCodegen::type(Type &t) {
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

void XmlCodegen::start_main() { open("main"); }
void XmlCodegen::end_main() { close("main"); }