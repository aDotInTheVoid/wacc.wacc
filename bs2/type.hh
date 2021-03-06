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

enum class PrintKind {
  Int,
  Char,
  String,
  CharArray,
  Bool,
  Ptr,
};
const char *print_kind_name(PrintKind);

enum class FreeKind {
  Pair,
  Array,
};
const char *free_kind_name(FreeKind);

struct Type {
  TypeKind kind_;
  std::unique_ptr<Type> p1_;
  std::unique_ptr<Type> p2_;

  bool is_valid();
  FreeKind free_kind();
  PrintKind print_kind();
  Type clone() const;
};

Type type_int();
Type type_char();
Type type_bool();
Type type_string();
Type type_eraised_pair();
Type type_pair(Type, Type);
Type type_array(Type);
Type type_array_inner(Type);
const Type &type_pair_fst(const Type &);
const Type &type_pair_snd(const Type &);

#endif