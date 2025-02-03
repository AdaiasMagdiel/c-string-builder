#include <assert.h>

#define MGDL_SB_IMPLEMENTATION
#include "string_builder.h"

void ok(const char *test) { printf("\x1b[32m[PASS]\x1b[0m %s\n", test); }

void test_init() {
  StringBuilder sb;

  assert(sb_init(&sb) == 0);
  assert(sb.capacity == SB_DEFAULT_CAPACITY);
  assert(sb.length == 0);

  sb_free(&sb);
  ok("test_init");
}

void test_free() {
  StringBuilder sb;
  assert(sb_init(&sb) == 0);

  sb_append(&sb, "Some content");

  sb_free(&sb);

  assert(sb.data == NULL);
  assert(sb.capacity == SB_DEFAULT_CAPACITY);
  assert(sb.length == 0);

  sb_free(&sb);
  ok("test_free");
}

void test_replace() {
  StringBuilder sb;
  sb_init(&sb);

  sb_append(&sb, "Hello, World!");
  sb_replace(&sb, "World", "C");

  assert(strcmp(sb.data, "Hello, C!") == 0);

  sb_free(&sb);
  ok("test_replace");
}

void test_append() {
  StringBuilder sb;
  assert(sb_init(&sb) == 0);

  sb_append(&sb, "Hello");
  assert(strcmp("Hello", sb.data) == 0);

  sb_append(&sb, ", ");
  sb_append(&sb, "World");
  sb_append(&sb, "!");
  assert(strcmp("Hello, World!", sb.data) == 0);

  sb_free(&sb);
  ok("test_append");
}

int main() {
  test_init();
  test_free();
  test_append();

  return 0;
}
