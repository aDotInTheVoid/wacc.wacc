#include <cassert>
#include <charconv>
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

void Parser::function(std::string_view name, const Type &ret) {
  codegen_->start_function(name, ret);

  expect(TokenType::Lparen);
  std::optional<Type> oty;
  if ((oty = ty())) {
    Token name = expect(TokenType::Identifier);
    codegen_->add_arg(name.value_, oty.value());
    if (match(TokenType::Comma)) {
      Type aty = ty().value();
      Token name = expect(TokenType::Identifier);
      codegen_->add_arg(name.value_, aty);
    }
  }

  expect(TokenType::Rparen);
  expect(TokenType::Is);

  codegen_->start_function_body();
  stmts();

  expect(TokenType::End);

  codegen_->end_function();
}

void Parser::stmts() {
  do {
    stmt();
  } while (match(TokenType::Semi));
}

void Parser::stmt() {
  std::optional<Type> oty;
  std::optional<Token> oname;
  if ((oty = ty()))
    s_decl(oty.value());
  else if (match(TokenType::Skip))
    return;
  // TODO: assign-lhs = assign-rhs
  else if (match(TokenType::Read))
    s_read();
  else if (match(TokenType::Free))
    s_free();
  else if (match(TokenType::Return))
    s_return();
  else if (match(TokenType::Exit))
    s_exit();
  else if (match(TokenType::Print))
    s_print();
  else if (match(TokenType::Println))
    s_println();
  else if (match(TokenType::If))
    s_if();
  else if (match(TokenType::While))
    s_while();
  else if (match(TokenType::Begin))
    s_block();
  else if (match(TokenType::Fst))
    s_assign_fst();
  else if (match(TokenType::Snd))
    s_assign_snd();
  else if ((oname = match(TokenType::Identifier)))
    s_assign_local(oname.value().value_);
  else {
    Token t = current_;
    fatal(fmt::format("Expected stmt got {}({})", token_type_str(t.type_),
                      t.value_));
  }
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

/* #region stmt */
void Parser::s_read() {
  // TODO
  exit(-1);
}
void Parser::s_decl(Type &ty) {
  //  type, ident, "=", assign-rhs
  Token ident = expect(TokenType::Identifier);
  expect(TokenType::Assign);
  codegen_->add_var(ident.value_, ty);
  codegen_->assign_addr_local(ident.value_);
  assign_rhs();
  codegen_->assign_do();
}

void Parser::s_free() {
  codegen_->start_free();
  expr();
  codegen_->end_free();
}
void Parser::s_return() {
  codegen_->start_return();
  expr();
  codegen_->end_return();
}
void Parser::s_exit() {
  codegen_->start_exit();
  expr();
  codegen_->end_exit();
}
void Parser::s_print() {
  codegen_->start_print();
  expr();
  codegen_->end_print();
}
void Parser::s_println() {
  codegen_->start_println();
  expr();
  codegen_->end_println();
}
void Parser::s_if() {
  codegen_->if_cond();
  expr();
  expect(TokenType::Then);
  codegen_->if_when();
  stmts();
  expect(TokenType::Else);
  codegen_->if_else();
  stmts();
  expect(TokenType::Fi);
  codegen_->if_end();
}
void Parser::s_while() {
  codegen_->while_cond();
  expr();
  expect(TokenType::Do);
  codegen_->while_body();
  stmts();
  expect(TokenType::Done);
  codegen_->while_end();
}
void Parser::s_block() {
  codegen_->start_block();
  stmts();
  expect(TokenType::End);
  codegen_->end_block();
}
void Parser::s_assign_local(std::string_view name) {
  // TODO: Arrays
  expect(TokenType::Assign);
  codegen_->assign_addr_local(name);
  assign_rhs();
  codegen_->assign_do();
}
void Parser::s_assign_fst() {
  Token ident = expect(TokenType::Identifier);
  expect(TokenType::Assign);
  codegen_->assign_addr_local(ident.value_);
  codegen_->assign_addr_fst();
  assign_rhs();
  codegen_->assign_do();
}
void Parser::s_assign_snd() {
  Token ident = expect(TokenType::Identifier);
  expect(TokenType::Assign);
  codegen_->assign_addr_local(ident.value_);
  codegen_->assign_addr_snd();
  assign_rhs();
  codegen_->assign_do();
}

/* #endregion */

/* #region expr */
void Parser::expr() {
  std::optional<Token> ot;
  if ((ot = match(TokenType::Number))) {
    int32_t n;
    Token t = ot.value();
    std::from_chars(t.value_.data(), t.value_.end(), n);
    codegen_->e_push_number(n);
  } else if ((ot = match(TokenType::Identifier))) {
    codegen_->e_push_local(ot.value().value_);
  } else {
    // TODO: Flesh out
    Parser::fatal(fmt::format("Expected expr got {}({})",
                              token_type_str(current_.type_), current_.value_));
  }
}
/* #endregion */

/* #region assign-rhs */
void Parser::assign_rhs() {
  // TODO: FLesh out
  expr();
}

/* #endregion */

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
  std::cerr << fmt::format("{}:{}:{} {}", filename_, current_.line_ + 1,
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