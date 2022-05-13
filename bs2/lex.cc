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
  case '(':
    return make_token(TokenType::Lparen);
  case ')':
    return make_token(TokenType::Rparen);
  case '=':
    return make_token(match('=') ? TokenType::Eq : TokenType::Assign);
  case ';':
    return make_token(TokenType::Semi);
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
  return Token{tt, value, start_};
}

bool Lexer::match(char expected) {
  if (is_at_end())
    return false;
  if (peak() != expected)
    return false;
  current_++;
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
  // TODO: Correct type
  return make_token(TokenType::Identifier);
}

Token Lexer::number() {
  while (std::isdigit(advance()))
    ;
  return make_token(TokenType::Number);
}

void Lexer::skip_comment() {
  while (!is_at_end() && advance() != '\n')
    ;
}

void Token::debug(std::ostream &o, Lexer const &l) {
  o << start_ << " " << value_.size() << " " << token_type_str(type_) << " "
    << value_ << std::endl;
}

bool Lexer::is_at_end() { return current_ >= input_.size(); }
char Lexer::advance() { return input_[current_++]; }
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