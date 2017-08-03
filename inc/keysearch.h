#ifndef __KEYSEARCH__H__
#define __KEYSEARCH__H__

#include <stdint.h>

// Key is stored in the first 8M of the memory dump
int get_key_error(uint8_t *data, uint64_t startpoint);

#endif
