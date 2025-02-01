#include <assert.h>

#define MGDL_SB_IMPLEMENTATION
#include "string_builder.h"

StringBuilder sb;

void ok(const char *test) { printf("\x1b[32m[PASS]\x1b[0m %s\n", test); }

void test_init() {
  assert(sb_init(&sb) == 0);
  assert(sb.capacity == SB_DEFAULT_CAPACITY);
  assert(sb.length == 0);

  ok("test_init");
}

void test_free() {
  sb_free(&sb);
  assert(sb.data == NULL);
  assert(sb.capacity == SB_DEFAULT_CAPACITY);
  assert(sb.length == 0);

  ok("test_free");
}

void test_append() {
  sb_free(&sb);
  assert(sb_init(&sb) == 0);

  sb_append(&sb, "Hello");
  assert(strcmp("Hello", sb.data) == 0);

  sb_append(&sb, ", ");
  sb_append(&sb, "World");
  sb_append(&sb, "!");
  assert(strcmp("Hello, World!", sb.data) == 0);

  ok("test_append");
}

int main() {
  test_init();
  test_free();
  test_append();

  return 0;
}
