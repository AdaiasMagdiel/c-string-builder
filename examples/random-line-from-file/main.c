#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MGDL_SB_IMPLEMENTATION
#include "../../string_builder.h"

int main() {
  // Seed the random number generator
  srand(time(NULL));

  // Initialize the StringBuilder
  StringBuilder sb;
  if (sb_init(&sb) == -1) {
    fprintf(stderr, "Error: Failed to initialize the StringBuilder.\n");
    return 1;
  }

  // Read the contents of a file into the StringBuilder
  if (sb_read_file(&sb, "file.txt") == -1) {
    fprintf(stderr, "Error: Failed to read the file 'file.txt'.\n");
    sb_free(&sb); // Clean up the StringBuilder before exiting
    return 1;
  }

  // Split the file content into lines
  size_t count;
  char **lines = sb_split(&sb, "\n", &count);
  if (!lines) {
    fprintf(stderr, "Error: Failed to split the file content into lines.\n");
    sb_free(&sb); // Clean up the StringBuilder before exiting
    return 1;
  }

  // Check if the file is empty
  if (count == 0) {
    fprintf(stderr, "Error: The file is empty or contains no lines.\n");
    sb_free(&sb); // Clean up the StringBuilder before exiting
    return 1;
  }

  // Pick a random line from the file
  int rand_idx = rand() % count;
  char *line = lines[rand_idx];

  // Display the selected line
  printf("Random Line: %s\n", line);

  // Free the memory allocated for the lines
  for (size_t i = 0; i < count; i++) {
    free(lines[i]);
  }
  free(lines);

  // Free the StringBuilder
  sb_free(&sb);

  return 0;
}
