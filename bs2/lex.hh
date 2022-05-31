#ifndef BS2_LEX_HH
#define BS2_LEX_HH

#include <cstddef>
#include <ostream>
#include <string>

enum class TokenType {
  And,
  Assign,
  Begin,
  Bool,
  Call,
  Char,
  Chr,
  Comma,
  Div,
  Do,
  Done,
  Else,
  End,
  Eof,
  Eq,
  Exit,
  Extern,
  False,
  Fi,
  Free,
  Fst,
  Ge,
  Gt,
  Identifier,
  If,
  Int,
  Is,
  Le,
  Len,
  Lparen,
  Lsquare,
  Lt,
  Minus,
  Mod,
  Ne,
  Newpair,
  Not,
  Null,
  Number,
  Or,
  Ord,
  Pair,
  Plus,
  Print,
  Println,
  Read,
  Return,
  Rparen,
  Rsquare,
  Semi,
  Skip,
  Snd,
  String,
  Then,
  Times,
  True,
  While,
};

struct Token {
  TokenType type_;
  std::string_view value_;

  size_t line_;
  size_t column_;

  void debug(std::ostream &);
};

struct Lexer {
  std::string input_;
  std::size_t start_;
  std::size_t current_;
  std::size_t line_;
  std::size_t column_;

  Lexer(std::string input) {
    input_ = input;
    start_ = current_ = line_ = column_ = 0;
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
  Token char_lit();
  Token string_lit();
  void escape_sequence();
};

const char *token_type_str(TokenType);

#endif