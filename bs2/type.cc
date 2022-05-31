#include "type.hh"

#include <cassert>
#include <cstdlib>
#include <utility>

bool Type::is_valid() {
  switch (kind_) {
  case TypeKind::Int:
  case TypeKind::Char:
  case TypeKind::String:
  case TypeKind::Bool:
  case TypeKind::EraisedPair:
    return !p1_ && !p2_;
  case TypeKind::Pair:
    return p1_ && p2_ && p1_->is_valid() && p2_->is_valid() &&
           p1_->kind_ != TypeKind::Pair && p2_->kind_ != TypeKind::Pair;
  case TypeKind::Array:
    return p1_ && !p2_ && p1_->is_valid();
  }
  assert(0);
}

FreeKind Type::free_kind() {
  switch (kind_) {
  case TypeKind::Pair:
  case TypeKind::EraisedPair:
    return FreeKind::Pair;
  case TypeKind::Array:
    return FreeKind::Array;
  }
  assert(0 && "invalid free kind");
}

PrintKind Type::print_kind() {
  switch (kind_) {
  case TypeKind::Int:
    return PrintKind::Int;
  case TypeKind::Char:
    return PrintKind::Char;
  case TypeKind::String:
    return PrintKind::String;
  case TypeKind::Bool:
    return PrintKind::Bool;
  case TypeKind::Array:
    if (p1_->kind_ == TypeKind::Char)
      return PrintKind::CharArray;
    // Fallthrough
  case TypeKind::Pair:
  case TypeKind::EraisedPair:
    return PrintKind::Ptr;
  }
  assert(0);
}

Type Type::clone() const {
  auto p1 = p1_ ? std::make_unique<Type>(p1_->clone()) : nullptr;
  auto p2 = p2_ ? std::make_unique<Type>(p2_->clone()) : nullptr;
  return Type{kind_, std::move(p1), std::move(p2)};
}

Type type_array(Type t) {
  return Type{TypeKind::Array, std::make_unique<Type>(std::move(t)), nullptr};
}

Type type_int() { return Type{TypeKind::Int, nullptr, nullptr}; }
Type type_char() { return Type{TypeKind::Char, nullptr, nullptr}; }
Type type_bool() { return Type{TypeKind::Bool, nullptr, nullptr}; }
Type type_string() { return Type{TypeKind::String, nullptr, nullptr}; }
Type type_eraised_pair() {
  return Type{TypeKind::EraisedPair, nullptr, nullptr};
}
Type type_pair(Type t1, Type t2) {
  return Type{TypeKind::Pair, std::make_unique<Type>(std::move(t1)),
              std::make_unique<Type>(std::move(t2))};
}

Type type_array_inner(Type t) {
  assert(t.kind_ == TypeKind::Array);
  return std::move(*t.p1_);
}

const char *print_kind_name(PrintKind pk) {
  switch (pk) {
  case PrintKind::Int:
    return "i32";
  case PrintKind::Char:
    return "char";
  case PrintKind::String:
    return "str";
  case PrintKind::Bool:
    return "bool";
  case PrintKind::Ptr:
    return "ptr";
  case PrintKind::CharArray:
    return "char_array";
  }
  assert(0);
}

const char *free_kind_name(FreeKind fk) {
  switch (fk) {
  case FreeKind::Pair:
    return "pair";
  case FreeKind::Array:
    return "array";
  }
  assert(0);
}