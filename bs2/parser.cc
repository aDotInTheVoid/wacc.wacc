#include <fmt/core.h>
#include <iostream>
#include <optional>

#include "parser.hh"

void Parser::unit() {
  expect(TokenType::Begin);

  // TODO: Keep parsing functions, until we reach stmts in main.
  std::optional<Type> t;
  while ((t = ty())) {
    Token name = expect(TokenType::Identifier);
    // TODO: Handle case where int foo = 1; and start of main,
    // not int foo() is ...
    function(name.value_, t.value());
  }

  main();

  expect(TokenType::End);
  expect(TokenType::Eof);
}

void Parser::main() {
  codegen_->start_main();
  stmts();
  codegen_->end_main();
}

void Parser::function(std::string_view name, Type &ret) {
  codegen_->start_function(name, ret);

  expect(TokenType::Lparen);
  // TODO: Args
  expect(TokenType::Rparen);
  expect(TokenType::Is);

  stmts();

  expect(TokenType::End);

  codegen_->end_function();
}

void Parser::stmts() {
  do {
    stmt();
  } while (peak(TokenType::Semi));
}

void Parser::stmt() {
  // TODO: Flesh out
  if (match(TokenType::Skip)) {
    return;
  }

  // TODO
  exit(-1);
}

std::optional<Type> Parser::ty() {
  Type t;
  if (match(TokenType::Int)) {
    t = type_int();
  } else if (match(TokenType::Char)) {
    t = type_char();
  } else if (match(TokenType::Bool)) {
    t = type_bool();
  } else if (match(TokenType::String)) {
    t = type_string();
  } else {
    // TODO: Handle pairs
    return {};
  }
  while (match(TokenType::Lsquare)) {
    expect(TokenType::Rsquare);
    t = type_array(std::move(t));
  }
  return t;
}

// === Internal functions ===
Token Parser::expect(TokenType kind) {
  auto t = current_;
  if (t.type_ != kind) {
    fatal(fmt::format("Expected {} but got {}({})", token_type_str(kind),
                      token_type_str(t.type_), t.value_));
  }
  current_ = lexer_.next_token();
  return t;
}

bool Parser::peak(TokenType type) { return current_.type_ == type; }

[[noreturn]] void Parser::fatal(std::string msg) {
  std::cerr << fmt::format("{}:{}:{} {}", filename_, current_.line_,
                           current_.column_, msg)
            << std::endl;
  std::exit(EXIT_FAILURE);
}

std::optional<Token> Parser::match(TokenType type) {
  if (peak(type)) {
    auto t = current_;
    current_ = lexer_.next_token();
    return t;
  }
  return {};
}