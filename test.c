#include <assert.h>

#define MGDL_SB_IMPLEMENTATION
#include "string_builder.h"

void ok(const char *test) { printf("\x1b[32m[PASS]\x1b[0m %s\n", test); }

void test_new() {
  StringBuilder sb = sb_new("value");

  assert(sb.capacity == SB_DEFAULT_CAPACITY);
  assert(sb.length == strlen("value"));
  assert(strcmp(sb.data, "value") == 0);
  sb_free(&sb);

  StringBuilder sb1 = sb_new("");

  assert(sb1.capacity == SB_DEFAULT_CAPACITY);
  assert(sb1.length == 0);
  assert(strcmp(sb1.data, "") == 0);
  sb_free(&sb1);

  StringBuilder sb2 = sb_new(NULL);

  assert(sb2.capacity == SB_DEFAULT_CAPACITY);
  assert(sb2.length == 0);
  assert(strcmp(sb2.data, "") == 0);
  sb_free(&sb2);

  ok("test_new");
}

void test_free() {
  StringBuilder sb = sb_new("");

  sb_append(&sb, "Some content");

  sb_free(&sb);

  assert(sb.data == NULL);
  assert(sb.capacity == SB_DEFAULT_CAPACITY);
  assert(sb.length == 0);

  sb_free(&sb);
  ok("test_free");
}

void test_append() {
  StringBuilder sb = sb_new("");

  sb_append(&sb, "Hello");
  assert(strcmp("Hello", sb.data) == 0);

  sb_append(&sb, ", ");
  sb_append(&sb, "World");
  sb_append(&sb, "!");
  assert(strcmp("Hello, World!", sb.data) == 0);

  sb_free(&sb);
  ok("test_append");
}

void test_appendf() {

  StringBuilder sb = sb_new("");
  assert(sb_appendf(&sb, "Hello, %s!", "World") == 0);
  assert(strcmp(sb.data, "Hello, World!") == 0);

  assert(sb_appendf(&sb, " The number is %d and the float is %.2f.", 42,
                    3.14159) == 0);
  assert(strcmp(sb.data,
                "Hello, World! The number is 42 and the float is 3.14.") == 0);

  StringBuilder sb_empty = sb_new("");
  assert(sb_appendf(&sb_empty, "%s", NULL) == 0);
  assert(strcmp(sb_empty.data, "(null)") == 0);

  StringBuilder sb_long = sb_new("");
  char long_str[1000];
  memset(long_str, 'a', sizeof(long_str) - 1);
  long_str[sizeof(long_str) - 1] = '\0';
  assert(sb_appendf(&sb_long, "Long string: %s", long_str) == 0);
  char expected_long[1015];
  snprintf(expected_long, sizeof(expected_long), "Long string: %s", long_str);
  assert(strcmp(sb_long.data, expected_long) == 0);

  sb_free(&sb);
  sb_free(&sb_empty);
  sb_free(&sb_long);

  ok("test_appendf");
}

void test_replace() {
  StringBuilder sb = sb_new("");

  sb_append(&sb, "Hello, World!");
  sb_replace(&sb, "World", "C");

  assert(strcmp(sb.data, "Hello, C!") == 0);

  sb_free(&sb);
  ok("test_replace");
}

void test_trim() {
  StringBuilder sb = sb_new("");

  sb_append(&sb, "     \r\n              Hello, World! \n\n\t");
  sb_trim(&sb, NULL);
  assert(strcmp(sb.data, "Hello, World!") == 0);

  sb_reset(&sb);

  sb_append(&sb, "...........Hello, World!.............");
  sb_trim(&sb, ".");
  assert(strcmp(sb.data, "Hello, World!") == 0);

  sb_free(&sb);
  ok("test_trim");
}

void test_ltrim() {
  StringBuilder sb = sb_new("");

  sb_append(&sb, "     \r\n              Hello, World! \n\n\t");
  sb_ltrim(&sb, NULL);
  assert(strcmp(sb.data, "Hello, World! \n\n\t") == 0);

  sb_reset(&sb);

  sb_append(&sb, "...........Hello, World!.............");
  sb_ltrim(&sb, ".");
  assert(strcmp(sb.data, "Hello, World!.............") == 0);

  sb_free(&sb);
  ok("test_ltrim");
}

void test_rtrim() {
  StringBuilder sb = sb_new("");

  sb_append(&sb, "     \r\n   Hello, World! \n\n\t           ");
  sb_rtrim(&sb, NULL);
  assert(strcmp(sb.data, "     \r\n   Hello, World!") == 0);

  sb_reset(&sb);

  sb_append(&sb, "...........Hello, World!.............");
  sb_rtrim(&sb, ".");
  assert(strcmp(sb.data, "...........Hello, World!") == 0);

  sb_free(&sb);
  ok("test_rtrim");
}

void test_reset() {
  StringBuilder sb = sb_new("");

  sb_append(&sb, "Hello, World!");
  assert(strcmp(sb.data, "Hello, World!") == 0);

  sb_reset(&sb);

  sb_append(&sb, "A new string");
  assert(strcmp(sb.data, "A new string") == 0);

  sb_free(&sb);
  ok("test_reset");
}

void test_reverse() {
  StringBuilder sb = sb_new("");

  sb_append(&sb, "Hello, World!");
  sb_reverse(&sb);
  assert(strcmp(sb.data, "!dlroW ,olleH") == 0);

  sb_free(&sb);
  ok("test_reverse");
}

void test_read_file() {
  StringBuilder sb = sb_new("");

  sb_read_file(&sb, ".gitignore");
  sb_trim(&sb, NULL); // to remove newlines
  assert(strcmp(sb.data, "*.exe") == 0);

  sb_free(&sb);
  ok("test_read_file");
}

void test_split_to_builders() {
  StringBuilder sb = sb_new("");

  sb_append(&sb, "one,two,three,four");

  size_t count = 0;
  StringBuilder *substrings = sb_split_to_builders(&sb, ",", &count);

  assert(count == 4);
  assert(strcmp(substrings[0].data, "one") == 0);
  assert(strcmp(substrings[1].data, "two") == 0);
  assert(strcmp(substrings[2].data, "three") == 0);
  assert(strcmp(substrings[3].data, "four") == 0);

  sb_free_array(substrings, count);
  sb_free(&sb);
  ok("test_split_to_builders");
}

void test_split_to_builders_no_delimiter() {
  StringBuilder sb = sb_new("");

  sb_append(&sb, "singleword");

  size_t count = 0;
  StringBuilder *substrings = sb_split_to_builders(&sb, ",", &count);

  assert(count == 1);
  assert(strcmp(substrings[0].data, "singleword") == 0);

  sb_free_array(substrings, count);
  sb_free(&sb);
  ok("test_split_to_builders_no_delimiter");
}

void test_split_to_builders_empty_string() {
  StringBuilder sb = sb_new("");

  size_t count = 0;
  StringBuilder *substrings = sb_split_to_builders(&sb, ",", &count);

  assert(count == 0);
  assert(substrings == NULL);

  sb_free(&sb);
  ok("test_split_to_builders_empty_string");
}

int main() {
  test_new();
  test_free();
  test_append();
  test_appendf();
  test_replace();
  test_trim();
  test_ltrim();
  test_rtrim();
  test_reset();
  test_reverse();
  test_read_file();
  test_split_to_builders();
  test_split_to_builders_no_delimiter();
  test_split_to_builders_empty_string();

  return 0;
}
