/*
 * Copyright (C) 2025 Adaías Magdiel
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MGDL_STRING_BUILDER_H
#define MGDL_STRING_BUILDER_H

#include <stdio.h>  // For FILE, fopen, fread, etc.
#include <stdlib.h> // For malloc, realloc, free
#include <string.h> // For memcpy, memmove, strlen, etc.

#ifdef MGDL_SB_IMPLEMENTATION
#define SB_DEFAULT_CAPACITY 256

// ================================================================
// Public API
// ================================================================

// StringBuilder structure
typedef struct StringBuilder {
  char *data;      // Pointer to the string data.
  size_t length;   // Current length of the string (excluding null terminator).
  size_t capacity; // Total allocated memory for the string.
} StringBuilder;

int sb_init(StringBuilder *sb);
void sb_free(StringBuilder *sb);

// ================================================================
// Implementation
// ================================================================

// Initialize the StringBuilder
int sb_init(StringBuilder *sb) {
  if (!sb)
    return -1;

  sb->length = 0;
  sb->capacity = SB_DEFAULT_CAPACITY;

  sb->data = malloc(sb->capacity * sizeof(char));
  if (!sb->data)
    return -1;

  // Start with an empty string
  sb->data[0] = '\0';
  return 0;
}

// Free the StringBuilder
void sb_free(StringBuilder *sb) {
  if (sb && sb->data) {
    free(sb->data);
    sb->data = NULL;
    sb->length = 0;
    sb->capacity = SB_DEFAULT_CAPACITY;
  }
}

#endif
#endif
