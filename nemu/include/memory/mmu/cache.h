#ifndef __CACHE_H__
#define __CACHE_H__

#include "nemu.h"

#ifdef CACHE_ENABLED

#define CATCHE_LINES 1024
#define CATCHE_WIDTH 64

typedef union {
	struct
	{
		uint32_t block : 6;
        uint32_t group : 7;
		uint32_t tag : 19;
	};
	uint32_t val;
} PADDR_STATUS;

typedef struct {
    union {
        struct {
            uint32_t valid_bit : 1;
            uint32_t tag : 19;
        };
    };
    uint8_t block[CATCHE_WIDTH];
} CacheLine;

// init the cache
void init_cache();

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data);

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len);

#endif

#endif
