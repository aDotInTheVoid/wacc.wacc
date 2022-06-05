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

void waccrt_println_ptr(void *x) { printf("%p\n", x); }
void waccrt_print_ptr(void *x) { printf("%p", x); }

void waccrt_print_char_array(uint64_t *arr) {
  uint64_t len = arr[-1];
  for (uint64_t i = 0; i < len; i++)
    putchar(arr[i]);
}

void waccrt_println_char_array(uint64_t *arr) {
  waccrt_print_char_array(arr);
  putchar('\n');
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

uint64_t *waccrt_array_new(uint64_t len, uint64_t *start) {
  uint64_t *array = malloc((len + 1) * 8);
  array[0] = len;
  for (uint64_t i = 0; i < len; i++) {
    array[i + 1] = start[-i]; // Because stacks grow down
  }
  return &array[1];
}

void waccrt_array_delete(void *array) {
  uint64_t *a = array;
  free(a - 1);
}

uint64_t waccrt_array_get(uint64_t *array, uint32_t index) {
  uint64_t len = array[-1];
  if (0 <= index && index < len) {
    return array[index];
  } else {
    printf("Index out of bounds: %d, len is %d\n", index, len);
    exit(-1);
  }
}
// void *waccrt_string_new(char *str) {
//   size_t l = strlen(str);

//   size_t bufsz = (l + 1) * 8;
//   uint64_t *buf = malloc(bufsz);
//   buf[0] = l;
//   for (size_t i = 0; i < l; i++) {
//     buf[i + 1] = str[i];
//   }
//   return &buf[1];
// }

void waccrt_exit(int32_t x) { exit(x); }

// TODO: Is space before % needed?
void waccrt_read_int(int32_t *x) { scanf(" %d", x); }
void waccrt_read_char(char *x) { scanf(" %c", x); }
