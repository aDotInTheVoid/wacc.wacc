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

  if (match(TokenType::Skip))
    return;
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
  else if ((oty = ty()))
    s_decl(std::move(oty.value()));
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
void Parser::s_decl(Type ty) {
  //  type, ident, "=", assign-rhs
  Token ident = expect(TokenType::Identifier);
  expect(TokenType::Assign);
  codegen_->add_var(ident.value_, ty);
  loc_tys_[ident.value_] = std::move(ty);
  codegen_->assign_addr_local(ident.value_);
  assign_rhs();
  codegen_->assign_do();
}

void Parser::s_free() {
  auto ty = expr();
  codegen_->pop_free(ty.free_kind());
}
void Parser::s_return() {
  expr();
  codegen_->pop_return();
}
void Parser::s_exit() {
  expr();
  codegen_->pop_exit();
}
void Parser::s_print() {
  auto t = expr();
  codegen_->pop_print(t.print_kind(), false);
}
void Parser::s_println() {
  auto t = expr();
  codegen_->pop_print(t.print_kind(), true);
}
void Parser::s_if() {
  // http://craftinginterpreters.com/image/jumping-back-and-forth/if-else.png
  codegen_->if_cond();
  expr();
  expect(TokenType::Then);
  int32_t jno = codegen_->if_when();
  stmts(); //
  expect(TokenType::Else);
  jno = codegen_->if_else(jno);
  stmts();
  expect(TokenType::Fi);
  codegen_->if_end(jno);
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

// https://github.com/aDotInTheVoid/pisswaccrs/blob/89c8688f4d18a389241f5ccd323c846987689edf/src/parser.lalrpop#L126-L164

Type Parser::expr() { return expr_or(); }
Type Parser::expr_or() {
  Type tp = expr_and();
  while ((match(TokenType::Or))) {
    tp = expr_and();
    // TODO Typecheck
    codegen_->e_pop_op(Op::Or);
  }
  return tp;
}
Type Parser::expr_and() {
  Type tp = expr_eq();
  while ((match(TokenType::And))) {
    tp = expr_eq();
    // TODO Typecheck
    codegen_->e_pop_op(Op::And);
  }
  return tp;
}
Type Parser::expr_eq() {
  Type tp = expr_cmp();
  std::optional<Token> otk;
  while ((otk = match2(TokenType::Eq, TokenType::Ne))) {
    tp = expr_cmp();
    codegen_->e_pop_op(token_to_op(otk.value().type_));
  }
  return tp;
}
Type Parser::expr_cmp() {
  Type tp = expr_add();
  std::optional<Token> otk;
  while ((otk = match4(TokenType::Lt, TokenType::Le, TokenType::Gt,
                       TokenType::Ge))) {
    tp = expr_add();
    codegen_->e_pop_op(token_to_op(otk.value().type_));
  }
  return tp;
}
Type Parser::expr_add() {
  Type tp = expr_mul();
  std::optional<Token> otk;
  while ((otk = match2(TokenType::Plus, TokenType::Minus))) {
    tp = expr_mul();
    codegen_->e_pop_op(token_to_op(otk.value().type_));
  }
  return tp;
}
Type Parser::expr_mul() {
  Type tp = expr_unary();
  std::optional<Token> otk;
  while ((otk = match3(TokenType::Times, TokenType::Div, TokenType::Mod))) {
    tp = expr_unary();
    codegen_->e_pop_op(token_to_op(otk.value().type_));
  }
  return tp;
}
Type Parser::expr_unary() {
  // TODO:
  return expr_base();
}
Type Parser::expr_base() {
  /*

    CharLiter,
    StrLiter,
    PairLiter,
    Ident,
    ArrayElem,
    "(" Expr ")",
    */

  std::optional<Token> ot;
  if ((ot = match(TokenType::Number))) {
    int32_t n;
    Token t = ot.value();
    std::from_chars(t.value_.data(), t.value_.end(), n);
    codegen_->e_push_number(n);
    return type_int();
  } else if ((ot = match(TokenType::True))) {
    codegen_->e_push_bool(true);
    return type_bool();
  } else if ((ot = match(TokenType::False))) {
    codegen_->e_push_bool(false);
    return type_bool();
  } else if ((ot = match(TokenType::Char))) {
    codegen_->e_push_char(ot.value().value_);
    return type_char();
  } else if ((ot = match(TokenType::String))) {
    codegen_->e_push_string(ot.value().value_);
    return type_string();
  } else if ((ot = match(TokenType::Identifier))) {
    codegen_->e_push_local(ot.value().value_);
    auto ty = loc_tys_.find(ot.value().value_);
    assert(ty != loc_tys_.end());
    return ty->second.clone();
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

std::optional<Token> Parser::match2(TokenType a, TokenType b) {
  if (peak(a) || peak(b)) {
    auto t = current_;
    current_ = lexer_.next_token();
    return t;
  }
  return {};
}

std::optional<Token> Parser::match3(TokenType a, TokenType b, TokenType c) {
  if (peak(a) || peak(b) || peak(c)) {
    auto t = current_;
    current_ = lexer_.next_token();
    return t;
  }
  return {};
}

std::optional<Token> Parser::match4(TokenType a, TokenType b, TokenType c,
                                    TokenType d) {
  if (peak(a) || peak(b) || peak(c) || peak(d)) {
    auto t = current_;
    current_ = lexer_.next_token();
    return t;
  }
  return {};
}