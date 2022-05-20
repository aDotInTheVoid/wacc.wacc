#ifndef BS2_TYPE_HH
#define BS2_TYPE_HH

#include <memory>

enum class TypeKind {
  Int,
  Char,
  String,
  Bool,
  Pair,
  Array,
  EraisedPair,
};

struct Type {
  TypeKind kind_;
  std::unique_ptr<Type> p1_;
  std::unique_ptr<Type> p2_;

  bool is_valid();
};

Type type_int();
Type type_char();
Type type_bool();
Type type_string();
Type type_eraised_pair();
Type type_array(Type);

#endif