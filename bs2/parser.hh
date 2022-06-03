#ifndef BS2_PARSER_HH
#define BS2_PARSER_HH
#include "codegen.hh"
#include "lex.hh"
#include "type.hh"

#include <map>
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
  std::map<std::string_view, Type> loc_tys_; // TODO: Reset on new func

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
  void extern_fn();
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
  void s_decl(Type);
  void s_decl_2(Type ty, std::string_view name);
  void s_assign_fst();
  void s_assign_snd();
  void s_assign_local(std::string_view);

  // Expr
  Type expr();
  Type expr_or();
  Type expr_and();
  Type expr_eq();
  Type expr_cmp();
  Type expr_add();
  Type expr_mul();
  Type expr_unary();
  Type expr_base();
  Type expr_array_elem(Type);
  // Assignment
  void assign_rhs();
  void rhs_call();
  void rhs_newpair();
  void rhs_array_lit();
  void rhs_fst();
  void rhs_snd();

  // Lexer functions
  Token expect(TokenType kind);
  std::optional<Token> match(TokenType kind);
  std::optional<Token> match2(TokenType a, TokenType b);
  std::optional<Token> match3(TokenType a, TokenType b, TokenType c);
  std::optional<Token> match4(TokenType a, TokenType b, TokenType c,
                              TokenType d);
  bool peak(TokenType kind);

  [[noreturn]] void fatal(std::string);
};

#endif