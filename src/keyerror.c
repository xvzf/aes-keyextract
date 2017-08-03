#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "keyerror.h"
#include "colored.h"

int correct_key_error(uint8_t *data, uint64_t startpoint) {

  uint64_t offset = startpoint;
  uint16_t corrected = 0;
  bool errormatrix[8][64] = {false};

  for(int row = 1; row < 8; row++) {
    for(int col = 1; col < 64; col++) {
      if(data[offset + row*64 + col] != (data[offset + (row-1)*64 + col] ^ data[offset + row*64 + col -1])) errormatrix[row][col] = true;
    }
  }

  for(int row = 1; row < 8; row++) {
    for(int col = 1; col < 64; col++) {
      if(errormatrix[row][col]) {
        if( (col < 63) && (row < 7) && errormatrix[row][col+1] && errormatrix[row+1][col]) {
          data[offset + row*64 + col] = data[offset + (row-1)*64 + col] ^ data[offset + row*64 + col -1];
          corrected += 3;
        } else if( (col == 1) && !errormatrix[row][col+1]) {
          data[offset + row*64 + 0] = data[offset + row*64 + 1] ^ data[offset + (row - 1)*64 + 1];
          corrected += 1;
        } else if( (col < 63) && (row==7) && errormatrix[row][col+1]) {
          data[offset + row*64 + col] = data[offset + row*64 + col - 1] ^ data[offset + (row - 1)*64 + col];
          corrected += 2;
        }
      }
    }
  }

  printf("["COLOR_GREEN"+"COLOR_RESET"] Corrected %u errors!\n", corrected);

  return 0;
}
