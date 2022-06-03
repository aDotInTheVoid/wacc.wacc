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
  bool opened_main = false;

  for (;;) {
    if ((t = ty())) {
      Token name = expect(TokenType::Identifier);
      // TODO: Handle case where int foo = 1; and start of main,
      // not int foo() is ...
      if (match(TokenType::Lparen))
        function(name.value_, t.value());
      else {
        codegen_->start_main();
        opened_main = true;
        s_decl_2(std::move(t.value()), name.value_);
        if (match(TokenType::Semi))
          break;
        else
          goto end;
      }
    } else if (match(TokenType::Extern)) {
      extern_fn();
    } else {
      break;
    }
  }
  if (!opened_main)
    codegen_->start_main();

  main();
end:
  codegen_->end_main();
  expect(TokenType::End);
  expect(TokenType::Eof);
}

void Parser::main() { stmts(); }

void Parser::function(std::string_view name, const Type &ret) {
  codegen_->start_function(name, ret);

  // expect(TokenType::Lparen);
  std::optional<Type> oty;
  if ((oty = ty())) {
    Token name = expect(TokenType::Identifier);
    Type aty = std::move(oty.value());
    codegen_->add_arg(name.value_, aty);
    loc_tys_[name.value_] = std::move(aty);

    while (match(TokenType::Comma)) {
      aty = ty().value();
      Token name = expect(TokenType::Identifier);
      codegen_->add_arg(name.value_, aty);
      loc_tys_[name.value_] = std::move(aty);
    }
  }

  expect(TokenType::Rparen);
  expect(TokenType::Is);

  codegen_->start_function_body();
  stmts();

  expect(TokenType::End);

  codegen_->end_function();
}

void Parser::extern_fn() {
  ty().value();
  expect(TokenType::Identifier);
  expect(TokenType::Lparen); // TODO: Parse with args in extern.
  expect(TokenType::Rparen);
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
  } else if (match(TokenType::Pair)) {
    t = type_eraised_pair();
    if (match(TokenType::Lparen)) {
      auto lt = ty().value();
      expect(TokenType::Comma);
      auto rt = ty().value();
      expect(TokenType::Rparen);
      t = type_pair(std::move(lt), std::move(rt));
    }
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
  s_decl_2(std::move(ty), ident.value_);
}
void Parser::s_decl_2(Type ty, std::string_view name) {
  expect(TokenType::Assign);
  codegen_->add_var(name, ty);
  loc_tys_[name] = std::move(ty);
  codegen_->assign_addr_local(name);
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
  // http://craftinginterpreters.com/image/jumping-back-and-forth/while.png

  int32_t j_cond = codegen_->while_cond();
  expr();
  expect(TokenType::Do);
  int32_t j_body = codegen_->while_body();
  stmts();
  expect(TokenType::Done);
  codegen_->while_end(j_cond, j_body);
}
void Parser::s_block() {
  // fatal("Who uses blocks?"); // TODO
  codegen_->start_block();
  stmts();
  expect(TokenType::End);
  codegen_->end_block();
}
void Parser::s_assign_local(std::string_view name) {
  // TODO: Arrays
  codegen_->assign_addr_local(name);
  while (match(TokenType::Lsquare)) {
    expr();
    codegen_->assign_addr_array();
    expect(TokenType::Rsquare);
  }

  expect(TokenType::Assign);
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
    expr_and();
    // TODO Typecheck
    codegen_->e_pop_op(Op::Or);
    tp = type_bool();
  }
  return tp;
}
Type Parser::expr_and() {
  Type tp = expr_eq();
  while ((match(TokenType::And))) {
    expr_eq();
    // TODO Typecheck
    codegen_->e_pop_op(Op::And);
    tp = type_bool();
  }
  return tp;
}
Type Parser::expr_eq() {
  Type tp = expr_cmp();
  std::optional<Token> otk;
  while ((otk = match2(TokenType::Eq, TokenType::Ne))) {
    expr_cmp();
    codegen_->e_pop_op(token_to_op(otk.value().type_));
    tp = type_bool();
  }
  return tp;
}
Type Parser::expr_cmp() {
  Type tp = expr_add();
  std::optional<Token> otk;
  while ((otk = match4(TokenType::Lt, TokenType::Le, TokenType::Gt,
                       TokenType::Ge))) {
    expr_add();
    codegen_->e_pop_op(token_to_op(otk.value().type_));
    tp = type_bool();
  }
  return tp;
}
Type Parser::expr_add() {
  Type tp = expr_mul();
  std::optional<Token> otk;
  while ((otk = match2(TokenType::Plus, TokenType::Minus))) {
    expr_mul();
    codegen_->e_pop_op(token_to_op(otk.value().type_));
    tp = type_int();
  }
  return tp;
}
Type Parser::expr_mul() {
  Type tp = expr_unary();
  std::optional<Token> otk;
  while ((otk = match3(TokenType::Times, TokenType::Div, TokenType::Mod))) {
    expr_unary();
    codegen_->e_pop_op(token_to_op(otk.value().type_));
    tp = type_int();
  }
  return tp;
}
Type Parser::expr_unary() {
  // TODO:
  if (match(TokenType::Len)) {
    Type t = expr_unary();
    if (t.kind_ != TypeKind::Array)
      fatal(fmt::format("len on non-array type {}",
                        print_kind_name(t.print_kind())));
    codegen_->e_len();
    return type_int();
  } else if (match(TokenType::Ord)) {
    expr_unary(); // Due to how we handle types, no need to do anything
    return type_int();
  } else if (match(TokenType::Chr)) {
    expr_unary(); // Ditto
    return type_char();
  } else if (match(TokenType::Not)) {
    expr_unary();
    codegen_->e_not();
    return type_bool();
  } else if (match(TokenType::Minus)) {
    expr_unary();
    codegen_->e_neg();
    return type_int();
  } else if (match(TokenType::Plus)) {
    expr_unary();
    return type_int();
  } else
    return expr_base();
}
Type Parser::expr_base() {
  /*

    CharLiter,
    StrLiter,
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
    return expr_array_elem(ty->second.clone());
  } else if (match(TokenType::Lparen)) {
    auto ty = expr();
    expect(TokenType::Rparen);
    return ty;
  } else if (match(TokenType::Null)) {
    codegen_->e_push_null();
    return type_eraised_pair();
  } else {
    // TODO: Flesh out
    Parser::fatal(fmt::format("Expected expr got {}({})",
                              token_type_str(current_.type_), current_.value_));
  }
}
Type Parser::expr_array_elem(Type ty) {
  while (match(TokenType::Lsquare)) {
    expr();
    codegen_->e_array_elem();
    expect(TokenType::Rsquare);
    ty = type_array_inner(std::move(ty));
  }
  return ty;
}

/* #endregion */

/* #region assign-rhs */
void Parser::assign_rhs() {
  // TODO: FLesh out
  // Expr,
  // ArrayLiter,
  // "newpair" "(" Expr "," Expr ")",
  // PairElem,
  // "call" Ident "(" ArgList ? ")",
  if (match(TokenType::Call))
    rhs_call();
  else if (match(TokenType::Newpair))
    rhs_newpair();
  else if (match(TokenType::Fst))
    rhs_fst();
  else if (match(TokenType::Snd))
    rhs_snd();
  else if (match(TokenType::Lsquare))
    return rhs_array_lit();
  else
    expr();
}

void Parser::rhs_call() {
  Token ident = expect(TokenType::Identifier);
  expect(TokenType::Lparen);
  int32_t nargs = 0;
  if (!match(TokenType::Rparen)) {
    do {
      expr();
      nargs++;
    } while (match(TokenType::Comma));
    expect(TokenType::Rparen);
  }
  codegen_->call_func(ident.value_, nargs);
}
void Parser::rhs_newpair() {
  expect(TokenType::Lparen);
  expr();
  expect(TokenType::Comma);
  expr();
  expect(TokenType::Rparen);
  codegen_->e_push_newpair();
}
void Parser::rhs_fst() {
  expr();
  codegen_->e_fst();
}
void Parser::rhs_snd() {
  expr();
  codegen_->e_snd();
}
void Parser::rhs_array_lit() {
  int32_t nels = 0;
  if (!match(TokenType::Rsquare)) {
    do {
      expr();
      nels++;
    } while (match(TokenType::Comma));
    expect(TokenType::Rsquare);
  }
  codegen_->e_push_array_lit(nels);
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