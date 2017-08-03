/*
      ======  AES Key extractor for Hacking Proseminar Saarland University =====
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "iops.h"
#include "keyextract.h"


int main(int argc, char *argv[]) {

  if(argc != 2) printf("Usage: ./keyextract memory.bin\n");

  uint64_t size = 0;

  uint8_t* buffer = load_memory_dump_posix(argv[1], &size);

  find_key(buffer, 8388608);

  free(buffer);
  return 0;
}
