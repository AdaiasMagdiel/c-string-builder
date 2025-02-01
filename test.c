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

int main() {
  test_init();
  test_free();

  return 0;
}
