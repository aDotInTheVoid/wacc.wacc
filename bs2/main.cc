#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "lex.hh"

int main(int argc, char **argv) {
  if (argc != 1 && argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return EXIT_FAILURE;
  }

  std::string source;
  std::stringstream ss;

  // Read the file into a string.
  if (argc == 1 || std::strcmp(argv[1], "-") != 0) {
    char c;
    while ((c = std::getchar()) != EOF) {
      source.push_back(c);
    }
  } else {
    std::ifstream file(argv[1]);
    ss << file.rdbuf();
    source = ss.str();
  }

  Lexer lexer(source);
  Token t;
  while ((t = lexer.next_token()).type_ != TokenType::Eof) {
    t.debug(std::cout, lexer);
  }
}