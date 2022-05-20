#include <fmt/core.h>
#include <iostream>

#include "parser.hh"

void Parser::unit() {
  expect(TokenType::Begin);

  // TODO: Keep parsing functions, until we reach stmts in main.

  main();

  expect(TokenType::End);
  expect(TokenType::Eof);
}

void Parser::main() {
  codegen_->startmain();
  stmts();
  codegen_->endmain();
}

void Parser::stmts() {
  do {
    stmt();
  } while (peak(TokenType::Semi));
}

void Parser::stmt() {
  // TODO: Flesh out
  expect(TokenType::Skip);
}

// === Internal functions ===
void Parser::expect(TokenType kind) {
  auto t = current_;
  if (t.type_ != kind) {
    fatal(fmt::format("Expected {} but got {}({})", token_type_str(kind),
                      token_type_str(t.type_), t.value_));
  }
  current_ = lexer_.next_token();
}

bool Parser::peak(TokenType type) { return current_.type_ == type; }

[[noreturn]] void Parser::fatal(std::string msg) {
  std::cerr << fmt::format("{}:{}:{} {}", filename_, current_.line_,
                           current_.column_, msg)
            << std::endl;
  std::exit(EXIT_FAILURE);
}