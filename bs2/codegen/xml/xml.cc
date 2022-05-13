#include <cassert>
#include <fmt/core.h>

#include "xml.hh"

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