#ifndef BS2_PARSER_HH
#define BS2_PARSER_HH
#include "codegen.hh"
#include "lex.hh"
#include "type.hh"

#include <optional>

// The parser takes a stream of tokens, and converts it into instructions
// for the code generator.
//
// These are designed to be amenable to a signle-pass stack based code
// generation. Note that we don't do any type checking.

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
  void function(std::string_view name, const Type &ret);
  std::optional<Type> ty();

  // Stmts
  void s_read();
  void s_free();
  void s_return();
  void s_exit();
  void s_print();
  void s_println();
  void s_if();
  void s_while();
  void s_block();
  void s_decl(Type &);
  void s_assign_fst();
  void s_assign_snd();
  void s_assign_local(std::string_view);

  // Expr
  void expr();
  // Assignment
  void assign_rhs();

  // Lexer functions
  Token expect(TokenType kind);
  std::optional<Token> match(TokenType kind);
  bool peak(TokenType kind);

  [[noreturn]] void fatal(std::string);
};

#endif