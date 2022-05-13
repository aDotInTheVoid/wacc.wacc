#include <iostream>

#include "parser.hh"

void Parser::expect(TokenType kind) {
  auto t = lexer.next_token();
  if (t.type_ != kind) {
    std::cerr << "Expected " << token_type_str(kind) << " but got "
              << token_type_str(t.type_) << "(" << t.value_ << ")" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

void Parser::unit() {
  expect(TokenType::Begin);

  // Keep parsing functions, until we reach stmts in main.

  main();

  expect(TokenType::Else);
  expect(TokenType::Eof);
}

void Parser::main() {
  codegen->startmain();
  stmts();
  codegen->endmain();
}

void Parser::stmts() {
  do {
    stmt();
  } while (peak(TokenType::Semi));
}

void Parser::stmt() {
  // TODO: Implement
}