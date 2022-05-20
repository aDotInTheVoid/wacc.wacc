#include "type.hh"

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
  std::exit(-1); // Unreachable
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