#ifndef WACC_CPP_LEX_HH
#define WACC_CPP_LEX_HH

#include <cstddef>
#include <ostream>
#include <string>

struct Lexer;

enum class TokenType {
  Identifier,
  Number,
  Eof,
  Begin,
  Bool,
  Call,
  Char,
  Chr,
  Do,
  Done,
  Else,
  End,
  Exit,
  False,
  Fi,
  Free,
  Fst,
  If,
  Int,
  Is,
  Len,
  Newpair,
  Null,
  Ord,
  Pair,
  Print,
  Println,
  Read,
  Return,
  Skip,
  Snd,
  String,
  Then,
  True,
  While,
  Lparen,
  Rparen,
  Assign,
  Semi,
  Comma,
  Lsquare,
  Rsquare,
  Not,
  Minus,
  Times,
  Div,
  Mod,
  Plus,
  Gt,
  Ge,
  Lt,
  Le,
  Eq,
  Ne,
  And,
  Or
};

struct Token {
  TokenType type_;
  std::string_view value_;
  size_t start_; // Byte offset
  // TODO: Line number

  void debug(std::ostream &, Lexer const &);
};

struct Lexer {
  std::string input_;
  std::size_t start_;
  std::size_t current_;

  Lexer(std::string input) {
    input_ = input;
    start_ = current_ = 0;
  }

  Token next_token();
  void skip_whitespace();
  void skip_comment();
  bool is_at_end();
  Token make_token(TokenType);
  char advance();
  Token identifier();
  Token number();
  bool match(char);
  char peak();
};

const char *token_type_str(TokenType);

#endif