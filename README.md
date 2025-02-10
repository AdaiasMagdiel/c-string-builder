# C String Builder

**C String Builder** is a simple and efficient string builder implementation in pure C, designed to make dynamic string manipulation easier. With this library, you can concatenate, split, reverse, replace, and more, in a powerful and hassle-free way, without worrying about manual memory management.

This library is ideal for projects that require frequent string manipulation, such as text processing, file parsing, or building complex strings.

---

## License

This project is licensed under the **GNU General Public License v3.0 (GPLv3)**. This means you are free to use, modify, and distribute this code, as long as you keep the license and the source code open. See the [LICENSE](LICENSE) file for more details.

---

## Features

Here’s what **C String Builder** can do:

- **Efficient string concatenation**: Append strings dynamically without manual memory management.
- **String replacement**: Replace all occurrences of a substring with another.
- **File reading**: Load the contents of a file directly into the StringBuilder.
- **String splitting**: Split a string into substrings based on a delimiter.
- **String reversal**: Reverse a string quickly and easily.
- **Whitespace trimming**: Remove unnecessary leading and trailing whitespace.
- **Leading/trailing character trimming**: Remove specific characters from the start (`sb_ltrim`) or end (`sb_rtrim`) of the string.
- **Memory management**: Automatically handles memory allocation and reallocation.
- **Lightweight**: Written in pure C with no external dependencies.
- **Easy to integrate**: Single-header library with a simple API.

---

## How to Use

### Download

You can download the `string_builder.h` file directly from the repository using the following command:

```bash
curl -O https://raw.githubusercontent.com/AdaiasMagdiel/c-string-builder/main/string_builder.h
```

### Integration

To use the library, simply include the `string_builder.h` file in your project. To enable the implementation of the functions, define the `MGDL_SB_IMPLEMENTATION` macro in one file of your project.

```c
#define MGDL_SB_IMPLEMENTATION
#include "string_builder.h"
```

---

## Usage Examples

### Initialization and Concatenation

```c
#include <stdio.h>
#include "string_builder.h"

int main() {
    // Initialize the StringBuilder with an initial value
    StringBuilder sb = sb_new("Hello");

    // Or initialize with empty value
    // StringBuilder sb = sb_new("");

    // Append strings
    sb_append(&sb, ", ");
    sb_append(&sb, "World!");

    // Display the result
    printf("String: %s\n", sb.data); // Output: "Hello, World!"

    // Free allocated memory
    sb_free(&sb);
    return 0;
}
```

### Resetting the StringBuilder

```c
// Reset the StringBuilder, effectively clearing its content
if (sb_reset(&sb) == -1) {
    fprintf(stderr, "Error: Failed to reset the StringBuilder.\n");
    return 1;
}
printf("StringBuilder after reset: %s\n", sb.data); // Output: ""
```

### String Replacement

```c
// Replace all occurrences of "World" with "C"
sb_replace(&sb, "World", "C");
printf("After replacement: %s\n", sb.data); // Output: "Hello, C!"
```

### Reading Files

```c
// Read the contents of a file into the StringBuilder
if (sb_read_file(&sb, "file.txt") == -1) {
    fprintf(stderr, "Error: Failed to read the file.\n");
    return 1;
}
printf("File contents: %s\n", sb.data);
```

### Splitting Strings

```c
// Split the string into substrings based on a delimiter
size_t count;
char **substrings = sb_split(&sb, " ", &count);

if (substrings) {
    for (size_t i = 0; i < count; i++) {
        printf("Substring %zu: %s\n", i, substrings[i]);
        free(substrings[i]); // Free each substring
    }
    free(substrings); // Free the array of substrings
}
```

### Splitting Strings into StringBuilders

```c
// Split the string into substrings based on a delimiter and store them in separate StringBuilders
size_t count;
StringBuilder *builders = sb_split_into_builders(&sb, " ", &count);

if (builders) {
    for (size_t i = 0; i < count; i++) {
        printf("Substring %zu: %s (length %zu)\n", i, builders[i].data, builders[i].length);
    }

    sb_free_array(builders, count); // Free the array of StringBuilders
}
```

### Reversing Strings

```c
// Reverse the string
sb_reverse(&sb);
printf("Reversed string: %s\n", sb.data);
```

### Trimming Whitespace

```c
// Trim leading and trailing whitespace
sb_trim(&sb, NULL);
printf("String after trimming: %s\n", sb.data);
```

### Trimming Leading Characters
```c
sb_ltrim(&sb, NULL); // Trims whitespace by default
printf("String after left-trimming: %s\n", sb.data);
```

### Trimming Trailing Characters
```c
sb_rtrim(&sb, NULL); // Trims whitespace by default
printf("String after right-trimming: %s\n", sb.data);
```

---

## Requirements

- A C99-compatible compiler.
- The C standard library (`stdlib.h`, `string.h`, `stdio.h`).

---

## Testing

To test the **C String Builder** library, you can compile and run the provided test file (`test.c`). Here’s how:

### Compile and Run Tests

1. Download the `string_builder.h` file and the `test.c` file:
   ```bash
   curl -O https://raw.githubusercontent.com/AdaiasMagdiel/c-string-builder/main/string_builder.h
   curl -O https://raw.githubusercontent.com/AdaiasMagdiel/c-string-builder/main/test.c
   ```

2. Compile the test file:
   ```bash
   gcc test.c -o test -Wall -Wextra -Werror
   ```

3. Run the tests:
   ```bash
   ./test
   ```

---

## API Reference

### Types

#### `StringBuilder`
Represents the string builder object.

```c
typedef struct StringBuilder {
    char *data;      // Pointer to the string data.
    size_t length;   // Current length of the string (excluding null terminator).
    size_t capacity; // Total allocated memory for the string.
} StringBuilder;
```

---

### Functions

#### `StringBuilder sb_new(const char *value)`
Initializes a new `StringBuilder` with an optional initial value.
- **Parameters**:
  - `value`: The initial string value (can be `NULL` or an empty string).
- **Returns**:
  - A `StringBuilder` object initialized with the given value.
  - If memory allocation fails, the `length` and `capacity` will be `0`.

---

#### `int sb_reset(StringBuilder *sb)`
Resets the `StringBuilder`, effectively clearing its content without freeing the allocated memory. This allows the `StringBuilder` to be reused for new strings.

- **Parameters**:
  - `sb`: Pointer to the `StringBuilder` object.
- **Returns**:
  - `0` on success.
  - `-1` on failure (e.g., if `sb` or `sb->data` is `NULL`).

---

#### `int sb_append(StringBuilder *sb, const char *string)`
Appends a string to the `StringBuilder`.

- **Parameters**:
  - `sb`: Pointer to the `StringBuilder` object.
  - `string`: The string to append.
- **Returns**:
  - Length of the appended string on success.
  - `-1` on failure.

---

#### `int sb_replace(StringBuilder *sb, const char *str1, const char *str2)`
Replaces all occurrences of `str1` with `str2` in the `StringBuilder`.

- **Parameters**:
  - `sb`: Pointer to the `StringBuilder` object.
  - `str1`: The substring to replace.
  - `str2`: The replacement string.
- **Returns**:
  - `0` on success.
  - `-1` on failure.

---

#### `int sb_trim(StringBuilder *sb, const char *chars_to_trim)`
Trims leading and trailing characters from the `StringBuilder`. If `chars_to_trim` is `NULL`, trims whitespace characters (`" \t\n\r"`).

- **Parameters**:
  - `sb`: Pointer to the `StringBuilder` object.
  - `chars_to_trim`: Characters to trim (or `NULL` for whitespace).
- **Returns**:
  - `0` on success.
  - `-1` on failure.

---

#### `int sb_ltrim(StringBuilder *sb, const char *chars_to_trim)`
Trims leading characters from the `StringBuilder`. If `chars_to_trim` is `NULL`, trims whitespace characters (`" \t\n\r"`).
- **Parameters**:
  - `sb`: Pointer to the `StringBuilder` object.
  - `chars_to_trim`: Characters to trim (or `NULL` for whitespace).
- **Returns**:
  - `0` on success.
  - `-1` on failure.

---

#### `int sb_rtrim(StringBuilder *sb, const char *chars_to_trim)`
Trims trailing characters from the `StringBuilder`. If `chars_to_trim` is `NULL`, trims whitespace characters (`" \t\n\r"`).
- **Parameters**:
  - `sb`: Pointer to the `StringBuilder` object.
  - `chars_to_trim`: Characters to trim (or `NULL` for whitespace).
- **Returns**:
  - `0` on success.
  - `-1` on failure.

---

#### `void sb_reverse(StringBuilder *sb)`
Reverses the string in the `StringBuilder`.

- **Parameters**:
  - `sb`: Pointer to the `StringBuilder` object.

---

#### `char **sb_split(const StringBuilder *sb, const char *delimiter, size_t *count)`
Splits the `StringBuilder` into substrings based on a delimiter.

- **Parameters**:
  - `sb`: Pointer to the `StringBuilder` object.
  - `delimiter`: The delimiter string.
  - `count`: Pointer to store the number of substrings.
- **Returns**:
  - Array of substrings (must be freed by the caller).
  - `NULL` on failure.

---

#### `StringBuilder **sb_split_to_builders(const StringBuilder *sb, const char *delimiter, size_t *count)`
Splits the `StringBuilder` into an array of `StringBuilder` objects, each holding a substring. This is useful when you want to perform further manipulations on each substring as a `StringBuilder`.

- **Parameters**:
  - `sb`: Pointer to the `StringBuilder` object.
  - `delimiter`: The delimiter string.
  - `count`: Pointer to store the number of `StringBuilder` objects.
- **Returns**:
  - Array of `StringBuilder` objects (must be freed by the caller using `sb_free_array`).
  - `NULL` on failure.

---

#### `int sb_read_file(StringBuilder *sb, const char *filename)`
Reads the content of a file and appends it to the `StringBuilder`.

- **Parameters**:
  - `sb`: Pointer to the `StringBuilder` object.
  - `filename`: Path to the file.
- **Returns**:
  - `0` on success.
  - `-1` on failure.

---

#### `void sb_free_array(StringBuilder *sbs, size_t count)`
Frees the memory allocated for an array of `StringBuilder`.

- **Parameters**:
  - `array`: Pointer to the array of substrings.
  - `count`: The number of substrings in the array.

---

#### `void sb_free(StringBuilder *sb)`
Frees the memory allocated for the `StringBuilder`.

- **Parameters**:
  - `sb`: Pointer to the `StringBuilder` object.

---

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, feel free to open an **issue** or submit a **pull request**.
