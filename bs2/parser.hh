#ifndef BS2_PARSER_HH
#define BS2_PARSER_HH
#include "codegen.hh"
#include "lex.hh"

#include <optional>

struct Parser {
  Lexer lexer;
  Codegen *codegen;

  Token current;

  // Parser functions
  void unit();
  void main();
  void stmts();
  void stmt();

  // Lexer functions
  void expect(TokenType kind);
  std::optional<Token> match(TokenType kind);
  bool peak(TokenType kind);
};

#endif