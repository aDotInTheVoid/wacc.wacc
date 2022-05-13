#ifndef BS2_LEXBUF_HH
#define BS2_LEXBUF_HH

#include "lex.hh"
#include <array>

const int size = 10;

struct LexBuff {
  Lexer lexer_;
  std::array<Token, size> buf_;
  size_t n_buf_; // number of tokens in buf_
  LexBuff(Lexer l) : n_buf_(0), lexer_(l) {}

  Token next() {
    if (n_buf_ == 0)
      return lexer_.next_token();
    else
      return buf_[--n_buf_];
  }

  void unget(Token t) {
    if (n_buf_ == size)

      buf_[n_buf_++] = t;
  }
};

#endif