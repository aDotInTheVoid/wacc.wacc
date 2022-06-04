#include <cassert>
#include <cstdlib>

#include "op.hh"

const char *op_name(Op op) {
  switch (op) {
  case Op::Mul:
    return "mul";
  case Op::Div:
    return "div";
  case Op::Mod:
    return "mod";
  case Op::Add:
    return "add";
  case Op::Sub:
    return "sub";
  case Op::Lt:
    return "lt";
  case Op::Gt:
    return "gt";
  case Op::Le:
    return "le";
  case Op::Ge:
    return "ge";
  case Op::Eq:
    return "eq";
  case Op::Ne:
    return "ne";
  case Op::And:
    return "and";
  case Op::Or:
    return "or";
  }
  assert(0);
}

Op token_to_op(TokenType tt) {
  switch (tt) {
  case TokenType::Times:
    return Op::Mul;
  case TokenType::Div:
    return Op::Div;
  case TokenType::Mod:
    return Op::Mod;
  case TokenType::Plus:
    return Op::Add;
  case TokenType::Minus:
    return Op::Sub;
  case TokenType::Lt:
    return Op::Lt;
  case TokenType::Gt:
    return Op::Gt;
  case TokenType::Le:
    return Op::Le;
  case TokenType::Ge:
    return Op::Ge;
  case TokenType::Eq:
    return Op::Eq;
  case TokenType::Ne:
    return Op::Ne;
  case TokenType::And:
    return Op::And;
  case TokenType::Or:
    return Op::Or;
  default:
    fprintf(stderr, "token_to_op: Invalid_token %s", token_type_str(tt));
    std::exit(-1);
  }
}

bool is_op_eq(Op op) {
  switch (op) {
  case Op::Eq:
  case Op::Ne:
    return true;
  default:
    return false;
  }
}