#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "codegen.hh"
#include "codegen/x64/x64.hh"
#include "codegen/xml/xml.hh"
#include "lex.hh"
#include "parser.hh"

static void san_check() {
  int *a = (int *)NULL + 0;
  int b[3] = {1, 2, 3};
  int c = b[4];
  int d;
  int e = d;
}

int main(int argc, char **argv) {

  san_check();

  if (!(argc == 2 || argc == 3)) {
    char *name = argv[0];
    fprintf(stderr, "Usage: %s (parse|lex|asm) file?\n", name);
    return EXIT_FAILURE;
  }

  std::string source{};
  const char *filename;
  std::FILE *input;

  // Read the file into a string.
  if (argc == 2 || std::strcmp(argv[2], "-") == 0) {
    input = stdin;
    filename = "<stdin>";
  } else {
    input = std::fopen(argv[2], "r");
    filename = argv[2];
    if (!input) {
      fprintf(stderr, "Could not open file: %s\n", argv[2]);
      return EXIT_FAILURE;
    }
  }
  char c;
  while ((c = std::fgetc(input)) != EOF) {
    source.push_back(c);
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
  } else if (std::strcmp(argv[1], "asm") == 0) {
    Lexer lexer(source);
    X64Codegen codegen;
    Parser parser{lexer, &codegen, filename};
    parser.unit();
    std::cout << codegen.finish() << std::endl; // TODO: Dedup with parse
  } else {
    std::cerr << "Usage: " << argv[0] << " (lex|parse|asm) filename?"
              << std::endl;
    return EXIT_FAILURE;
  }
}
