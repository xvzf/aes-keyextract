#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "keyextract.h"
#include "colored.h"

void print_key_readable_to_file(uint8_t *data, uint64_t startpoint, char* filename) {

  uint64_t offset = startpoint;

  printf("["COLOR_GREEN"+"COLOR_RESET"] Storing key '%s'\n", filename);

  FILE* f = fopen(filename, "w");
  if(f == NULL) {
    printf("["COLOR_RED"-"COLOR_RESET"] print_key_readable_to_file -> Something went wrong...\n");
    exit(EXIT_FAILURE);
  }

  for(int row = 0; row < 8; row++) {
    for(int col = 0; col < 64; col++) {
        if(row > 0 && col > 0) {
          if(data[offset + row*64 + col] != (data[offset + (row-1)*64 + col] ^ data[offset + row*64 + col -1]) ) {
            fprintf(f, "{%.2x} ", data[offset + row*64 + col]);
          } else {
            fprintf(f, "%.2x   ", data[offset + row*64 + col]);
          }
        } else {
            fprintf(f, "%.2x   ", data[offset + row*64 + col]);
        }

      }
      fprintf(f, "\n");
   }

   fclose(f);
}

void print_key_binary_to_file(uint8_t* data, uint64_t startpoint, char* filename) {

  printf("["COLOR_GREEN"+"COLOR_RESET"] Storing key '%s'\n", filename);
  FILE* f = fopen(filename, "w");
  if(f == NULL) {
    printf("["COLOR_RED"-"COLOR_RESET"] print_key_binary_to_file -> Something went wrong...\n");
    exit(EXIT_FAILURE);
  }

  for(int i = startpoint; i < startpoint + 512; i++) {
    fprintf(f, "%c", data[i]);
  }
  fclose(f);
}

int find_key(uint8_t* data, uint64_t key_search_area) {

  uint16_t *errors = malloc(key_search_area*sizeof(uint16_t));

  for(uint64_t i = 0; i < key_search_area; i++) {
    errors[i] = get_key_error(data, i);
    if(i % 100000 == 0)
      printf("["COLOR_GREEN"+"COLOR_RESET"] Searching key at offset %lu -> %.1lf %c\r", i, 100.0*((double)i)/((double)key_search_area), '%');
  }
  printf("\n");

  uint64_t index = 0;
  for(uint64_t i = 0; i < key_search_area; i++) {
    if( errors[i] < errors[index] ) index = i;
  }


  printf("["COLOR_GREEN"+"COLOR_RESET"] Key at %lu, total errors: %u\n", index, errors[index]);
  free(errors);

  print_key_readable_to_file(data, index, "corrupted_key.txt");
  print_key_binary_to_file(data, index, "corrupted_key.bin");
  correct_key_error(data, index);
  if(get_key_error(data, index) == 0) {
    print_key_readable_to_file(data, index, "restored_key.txt");
    print_key_binary_to_file(data, index, "restored_key.bin");
    return 0;
  } else {
    print_key_readable_to_file(data, index, "partially_restored_key.txt");
    print_key_binary_to_file(data, index, "partially_restored_key.bin");
    return 1;
  }
}
