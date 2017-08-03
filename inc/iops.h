#ifndef __IOPS_H
#define __IOPS_H

#include <stdint.h>

/* Loads memory dump to a buffer*/
uint8_t* load_memory_dump_posix(char* filename, uint64_t* size);

#endif
