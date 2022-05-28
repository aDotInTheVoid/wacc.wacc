#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "codegen.hh"
#include "codegen/xml/xml.hh"
#include "lex.hh"
#include "parser.hh"

int main(int argc, char **argv) {
  if (!(argc == 2 || argc == 3)) {
    char *name = argv[0];
    fprintf(stderr, "Usage: %s (parse|lex) file?\n", name);
    return EXIT_FAILURE;
  }

  std::string source;
  std::stringstream ss;
  const char *filename;

  // Read the file into a string.
  if (argc == 2 || std::strcmp(argv[2], "-") == 0) {
    char c;
    while ((c = std::getchar()) != EOF) {
      source.push_back(c);
    }
    filename = "<stdin>";
  } else {
    std::ifstream file(argv[2]);
    ss << file.rdbuf();
    source = ss.str();
    filename = argv[2];
  }

  if (std::strcmp(argv[1], "lex") == 0) {
    Lexer lexer(source);
    Token t;
    do {
      t = lexer.next_token();
      t.debug(std::cout);
    } while (t.type_ != TokenType::Eof);
  } else if (std::strcmp(argv[1], "parse") == 0) {
    Lexer lexer(source);
    XmlCodegen codegen;
    Parser parser{lexer, &codegen, filename};
    parser.unit();
    std::cout << codegen.finish() << std::endl;
  } else {
    std::cerr << "Usage: " << argv[0] << " (lex|parse) filename?" << std::endl;
    return EXIT_FAILURE;
  }
}
