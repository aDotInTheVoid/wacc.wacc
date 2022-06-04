#ifndef BS2_OP_HH
#define BS2_OP_HH

#include "lex.hh"

enum class Op {
  Mul,
  Div,
  Mod,
  Add,
  Sub,
  Lt,
  Gt,
  Le,
  Ge,
  Eq,
  Ne,
  And,
  Or,
};

const char *op_name(Op);
Op token_to_op(TokenType);
bool is_op_eq(Op);

#endif