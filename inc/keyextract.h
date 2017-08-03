#ifndef __KEYEXTRACT_H__
#define __KEYEXTRACT_H__

#include "keysearch.h"
#include "keyerror.h"

int find_key(uint8_t* data, uint64_t key_search_area);

#endif
