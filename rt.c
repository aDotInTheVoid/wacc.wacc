#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void waccrt_println_char(char x) { printf("%c\n", x); }
void waccrt_print_char(char x) { printf("%c", x); }

void waccrt_println_i32(int32_t x) { printf("%d\n", x); }
void waccrt_print_i32(int32_t x) { printf("%d", x); }

void waccrt_println_str(char *x) { printf("%s\n", x); }
void waccrt_print_str(char *x) { printf("%s", x); }

void waccrt_println_bool(bool x) {
  if (x)
    printf("true\n");
  else
    printf("false\n");
}
void waccrt_print_bool(bool x) {
  if (x)
    printf("true");
  else
    printf("false");
}

void waccrt_println_ptr(void *x) {
  if (x)
    printf("%p\n", x);
  else
    printf("(nil)\n");
}
void waccrt_print_ptr(void *x) {
  if (x)
    printf("%p", x);
  else
    printf("(nil)");
}

struct Pair {
  uint64_t a;
  uint64_t b;
};

struct Pair *waccrt_pair_new(uint64_t a, uint64_t b) {
  struct Pair *p = malloc(sizeof(struct Pair));
  p->a = a;
  p->b = b;
  return p;
}

void waccrt_pair_delete(struct Pair *p) { free(p); }

void waccrt_array_delete(void *array) {
  uint64_t *a = array;
  free(a - 1);
}

void *waccrt_string_new(char *str) {
  size_t l = strlen(str);

  size_t bufsz = (l + 1) * 8;
  uint64_t *buf = malloc(bufsz);
  buf[0] = l;
  for (size_t i = 0; i < l; i++) {
    buf[i + 1] = str[i];
  }
  return &buf[1];
}

// TODO: waccrt_array_new