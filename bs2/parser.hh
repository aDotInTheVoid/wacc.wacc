#ifndef BS2_PARSER_HH
#define BS2_PARSER_HH
#include "codegen.hh"
#include "lex.hh"

#include <optional>

struct Parser {
  Lexer lexer_;
  Codegen *codegen_;
  const char *filename_;

  Token current_;

  Parser(Lexer lexer, Codegen *codegen, const char *filename) : lexer_(lexer) {
    codegen_ = codegen;
    filename_ = filename;
    current_ = lexer_.next_token();
  }

  // Parser functions
  void unit();
  void main();
  void stmts();
  void stmt();

  // Lexer functions
  void expect(TokenType kind);
  std::optional<Token> match(TokenType kind);
  bool peak(TokenType kind);

  [[noreturn]] void fatal(std::string);
};

#endif