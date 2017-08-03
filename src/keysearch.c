
#include <stdio.h>
#include <stdlib.h>

#include "colored.h"
#include "keysearch.h"
#include "keyerror.h"

int get_key_error(uint8_t *data, uint64_t startpoint) {
  // first row and first column are arbitrary
  // Value is calculated using the value above and left

  // 64 cols, 8 rows
  uint64_t offset = startpoint;

  int errorcounter = 0; // Max bit errors are 5

  for(int row = 1; row < 8; row++) {
    for(int col = 1; col < 64; col++) {
      if(data[offset + row*64 + col] != (data[offset + (row-1)*64 + col] ^ data[offset + row*64 + col -1]) ) errorcounter++;
    }
  }

  return errorcounter;
}
