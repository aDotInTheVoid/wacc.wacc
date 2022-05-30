#include <cctype>
#include <cstdlib>
#include <string>

#include "lex.hh"
#include "util.hh"

static bool is_alpha(char c) { return std::isalpha(c) || c == '_'; }

Token Lexer::next_token() {
  skip_whitespace();
  start_ = current_;
  if (is_at_end())
    return make_token(TokenType::Eof);

  char c = advance();
  if (is_alpha(c))
    return identifier();

  if (std::isdigit(c))
    return number();

  switch (c) {
  case '\'':
    return char_lit();
  case '"':
    return string_lit();
  case '(':
    return make_token(TokenType::Lparen);
  case ')':
    return make_token(TokenType::Rparen);
  case '=':
    return make_token(match('=') ? TokenType::Eq : TokenType::Assign);
  case ';':
    return make_token(TokenType::Semi);
  case ',':
    return make_token(TokenType::Comma);
  case '+':
    return make_token(TokenType::Plus);
  case '[':
    return make_token(TokenType::Lsquare);
  case ']':
    return make_token(TokenType::Rsquare);
  case '!':
    return make_token(match('=') ? TokenType::Ne : TokenType::Not);
  case '-':
    return make_token(TokenType::Minus);
  case '*':
    return make_token(TokenType::Times);
  case '/':
    return make_token(TokenType::Div);
  case '%':
    return make_token(TokenType::Mod);
  case '<':
    return make_token(match('=') ? TokenType::Le : TokenType::Lt);
  case '>':
    return make_token(match('=') ? TokenType::Ge : TokenType::Gt);
  case '&':
    if (match('&'))
      return make_token(TokenType::And);
    else
      break;
  case '|':
    if (match('|'))
      return make_token(TokenType::Or);
    else
      break;
  }
  fprintf(stderr, "Unexpected character: %c\n", c);
  std::exit(EXIT_FAILURE);
}

Token Lexer::make_token(TokenType tt) {
  std::string_view value =
      std::string_view(input_).substr(start_, current_ - start_);
  return Token{tt, value, line_, column_};
}

bool Lexer::match(char expected) {
  if (is_at_end())
    return false;
  if (peak() != expected)
    return false;
  advance();
  return true;
}

void Lexer::skip_whitespace() {
  while (!is_at_end()) {
    char c = peak();
    switch (c) {
    case ' ':
    case '\n':
    case '\t':
    case '\r':
      advance();
      break;
    case '#':
      skip_comment();
      break;
    default:
      return;
    }
  }
}

Token Lexer::identifier() {
  while (is_alpha(peak()))
    advance();
  auto t = make_token(TokenType::Identifier);
  auto new_type = TokenType::Identifier;

  // Not that efficent, but it works
  if (t.value_ == "begin")
    new_type = TokenType::Begin;
  else if (t.value_ == "bool")
    new_type = TokenType::Bool;
  else if (t.value_ == "call")
    new_type = TokenType::Call;
  else if (t.value_ == "char")
    new_type = TokenType::Char;
  else if (t.value_ == "chr")
    new_type = TokenType::Chr;
  else if (t.value_ == "do")
    new_type = TokenType::Do;
  else if (t.value_ == "done")
    new_type = TokenType::Done;
  else if (t.value_ == "else")
    new_type = TokenType::Else;
  else if (t.value_ == "end")
    new_type = TokenType::End;
  else if (t.value_ == "exit")
    new_type = TokenType::Exit;
  else if (t.value_ == "false")
    new_type = TokenType::False;
  else if (t.value_ == "fi")
    new_type = TokenType::Fi;
  else if (t.value_ == "free")
    new_type = TokenType::Free;
  else if (t.value_ == "fst")
    new_type = TokenType::Fst;
  else if (t.value_ == "if")
    new_type = TokenType::If;
  else if (t.value_ == "int")
    new_type = TokenType::Int;
  else if (t.value_ == "is")
    new_type = TokenType::Is;
  else if (t.value_ == "len")
    new_type = TokenType::Len;
  else if (t.value_ == "newpair")
    new_type = TokenType::Newpair;
  else if (t.value_ == "null")
    new_type = TokenType::Null;
  else if (t.value_ == "ord")
    new_type = TokenType::Ord;
  else if (t.value_ == "pair")
    new_type = TokenType::Pair;
  else if (t.value_ == "print")
    new_type = TokenType::Print;
  else if (t.value_ == "println")
    new_type = TokenType::Println;
  else if (t.value_ == "read")
    new_type = TokenType::Read;
  else if (t.value_ == "return")
    new_type = TokenType::Return;
  else if (t.value_ == "skip")
    new_type = TokenType::Skip;
  else if (t.value_ == "snd")
    new_type = TokenType::Snd;
  else if (t.value_ == "string")
    new_type = TokenType::String;
  else if (t.value_ == "then")
    new_type = TokenType::Then;
  else if (t.value_ == "true")
    new_type = TokenType::True;
  else if (t.value_ == "while")
    new_type = TokenType::While;

  t.type_ = new_type;
  return t;
}

Token Lexer::char_lit() {
  if (is_at_end()) {
    fprintf(stderr, "Unexpected end of input in char lit\n");
    std::exit(EXIT_FAILURE);
  }
  char c = advance();
  switch (c) {
  case '\'': // invalid
  case '"':
    fprintf(stderr, "Unexpected character in char lit: %c\n", c);
    std::exit(EXIT_FAILURE);
  case '\\':
    escape_sequence();
  }
  c = advance();
  if (c != '\'') {
    fprintf(stderr, "Expected ' after char lit\n");
    std::exit(EXIT_FAILURE);
  }
  return make_token(TokenType::Char);
}

Token Lexer::string_lit() {
  while (!is_at_end()) {
    char c = advance();
    switch (c) {
    case '"':
      return make_token(TokenType::String);
    case '\'': {
      fprintf(stderr, "Error: Must escape ' in string literal\n");
      std::exit(EXIT_FAILURE);
    }
    case '\\': {
      escape_sequence();
    }
    }
  }
  fprintf(stderr, "Unexpected end of file: Unclosed string literal\n");
  std::exit(EXIT_FAILURE);
}

void Lexer::escape_sequence() {
  char c = advance();
  // todo: check is_at_end
  switch (c) {
  case '0':
  case 'b':
  case 't':
  case 'n':
  case 'f':
  case 'r':
  case '"':
  case '\'':
  case '\\':
    break;
  default:
    fprintf(stderr, "Error: Unknown escape sequence: \\%c\n", c);
  }
}

Token Lexer::number() {
  while (std::isdigit(peak()))
    advance();
  return make_token(TokenType::Number);
}

void Lexer::skip_comment() {
  while (!is_at_end() && advance() != '\n')
    ;
}

void Token::debug(std::ostream &o) {
  o << value_.size() << " " << token_type_str(type_) << " " << value_
    << std::endl;
}

bool Lexer::is_at_end() {
  int a = current_;
  a = input_.size();
  return current_ >= input_.size();
}
char Lexer::advance() {
  // TODO: Update line_ and col_
  char c = input_[current_];
  current_++;
  if (c == '\n') {
    line_++;
    column_ = 0;
  } else {
    column_++;
  }
  return c;
}
char Lexer::peak() { return input_[current_]; }

const char *token_type_str(TokenType tt) {
  switch (tt) {
  case TokenType::Identifier:
    return "identifier";
  case TokenType::Number:
    return "number";
  case TokenType::Eof:
    return "eof";
  case TokenType::Begin:
    return "begin";
  case TokenType::Bool:
    return "bool";
  case TokenType::Call:
    return "call";
  case TokenType::Char:
    return "char";
  case TokenType::Chr:
    return "chr";
  case TokenType::Do:
    return "do";
  case TokenType::Done:
    return "done";
  case TokenType::Else:
    return "else";
  case TokenType::End:
    return "end";
  case TokenType::Exit:
    return "exit";
  case TokenType::False:
    return "false";
  case TokenType::Fi:
    return "fi";
  case TokenType::Free:
    return "free";
  case TokenType::Fst:
    return "fst";
  case TokenType::If:
    return "if";
  case TokenType::Int:
    return "int";
  case TokenType::Is:
    return "is";
  case TokenType::Len:
    return "len";
  case TokenType::Newpair:
    return "newpair";
  case TokenType::Null:
    return "null";
  case TokenType::Ord:
    return "ord";
  case TokenType::Pair:
    return "pair";
  case TokenType::Print:
    return "print";
  case TokenType::Println:
    return "println";
  case TokenType::Read:
    return "read";
  case TokenType::Return:
    return "return";
  case TokenType::Skip:
    return "skip";
  case TokenType::Snd:
    return "snd";
  case TokenType::String:
    return "string";
  case TokenType::Then:
    return "then";
  case TokenType::True:
    return "true";
  case TokenType::While:
    return "while";
  case TokenType::Lparen:
    return "lparen";
  case TokenType::Rparen:
    return "rparen";
  case TokenType::Assign:
    return "assign";
  case TokenType::Semi:
    return "semi";
  case TokenType::Comma:
    return "comma";
  case TokenType::Lsquare:
    return "lsquare";
  case TokenType::Rsquare:
    return "rsquare";
  case TokenType::Not:
    return "not";
  case TokenType::Minus:
    return "minus";
  case TokenType::Times:
    return "times";
  case TokenType::Div:
    return "div";
  case TokenType::Mod:
    return "mod";
  case TokenType::Plus:
    return "plus";
  case TokenType::Gt:
    return "gt";
  case TokenType::Ge:
    return "ge";
  case TokenType::Lt:
    return "lt";
  case TokenType::Le:
    return "le";
  case TokenType::Eq:
    return "eq";
  case TokenType::Ne:
    return "ne";
  case TokenType::And:
    return "and";
  case TokenType::Or:
    return "or";
  }
  TODO(); // Unreachable
}