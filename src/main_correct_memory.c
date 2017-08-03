/*
      ======  Error correct memory dump for Hacking Proseminar Saarland University =====
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "iops.h"


int main(int argc, char *argv[]) {

  if(argc != 4) printf("Usage: ./hddencrypt key memory.bin\n");

  uint64_t size = 0;
  uint8_t* memory_image = load_memory_dump_posix(argv[1], &size);

  uint64_t validkeysize = 0;
  uint8_t* validkey = load_memory_dump_posix(argv[2], &validkeysize);

  uint64_t corruptedkeysize = 0;
  uint8_t* corruptedkey = load_memory_dump_posix(argv[3], &corruptedkeysize);

  uint8_t bitflips[512] = {0};

  for(int i = 0; i < 512; i++) {
    bitflips[i] = validkey[i] ^ corruptedkey[i];
  }

  FILE* f = fopen("corrected_memory.bin", "w");
  if(f == 0) return 1;

  uint16_t keycount = 0;
  for(uint64_t i  = 8388608; i < size; i++) {
    fprintf(f, "%c", memory_image[i] ^ bitflips[keycount]);
    keycount ++;
    if(keycount == 512) keycount = 0;
  }

  fclose(f);

  free(validkey);
  free(corruptedkey);
  free(memory_image);
  return 0;
}
