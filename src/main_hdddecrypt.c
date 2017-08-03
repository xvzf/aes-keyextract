/*
      ======  AES HDD Encrypt for Hacking Proseminar Saarland University =====
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "iops.h"


int main(int argc, char *argv[]) {

  if(argc != 3) printf("Usage: ./hddencrypt key memory.bin\n");

  uint64_t size = 0;
  uint8_t* hdd_image = load_memory_dump_posix(argv[1], &size);

  uint64_t keysize = 0;
  uint8_t* key = load_memory_dump_posix(argv[2], &keysize);

  FILE* f = fopen("decrypted.hdd", "w");
  if(f == 0) return 1;

  uint16_t keycount = 0;
  for(uint64_t i  = 0; i < size; i++) {
    fprintf(f, "%c", hdd_image[i] ^ key[keycount]);
    keycount ++;
    if(keycount == 512) keycount = 0;
  }

  fclose(f);

  free(key);
  free(hdd_image);
  return 0;
}
