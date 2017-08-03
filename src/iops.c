#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "iops.h"
#include "colored.h"

uint8_t* load_memory_dump_posix(char* filename, uint64_t* size) {

  // Open memory dump
  int fd = open(filename, O_RDONLY);

  // Get size of memory dump
  *size = lseek(fd, 0, SEEK_END);

  // Map the file - needed for datasets larger than 4GB
  uint8_t* buffer = mmap(0, *size, PROT_READ, MAP_PRIVATE, fd, 0);

  // Check if everything worked out
  if(buffer == MAP_FAILED) {
    fprintf(stderr, "[-] load_memory_dump -> Something went wrong!\n");
    exit(1);
  }

  printf("["COLOR_GREEN"+"COLOR_RESET"] load_memory_dump -> Loaded %lu bytes\n", *size);
  printf("["COLOR_GREEN"+"COLOR_RESET"] load_memory_dump -> Creating work copy\n");

  // Create a working copy so we cannot accidently change the binary file
  uint8_t* work_buffer = (uint8_t*)malloc(*size * sizeof(buffer));

  // Again, check if everything is alright
  if(work_buffer == NULL) {
    fprintf(stderr, "[-] load_memory_dump -> Something went wrong!\n");
    exit(1);
  }

  printf("["COLOR_GREEN"+"COLOR_RESET"] load_memory_dump -> Copying to work copy\n");
  // copy data to working buffer!
  for(uint64_t i = 0; i < *size; i++) work_buffer[i] = buffer[i];

  // Close memory dump
  close(fd);

  printf("["COLOR_GREEN"+"COLOR_RESET"] load_memory_dump -> Done\n");
  return work_buffer;
}
