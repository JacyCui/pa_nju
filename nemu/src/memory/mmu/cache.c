#include "memory/mmu/cache.h"

#ifdef CACHE_ENABLED

CacheLine cache[CATCHE_LINES];

// init the cache
void init_cache()
{
	for (int i = 0; i < CATCHE_LINES; i++) {
	    cache[i].valid_bit = 0;
	}
}

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data)
{
	// implement me in PA 3-1
}

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len)
{
    PADDR
	for (int i = 0; i < CATCHE_LINES; i++) {
	    if (cache[i].valid_bit && cache[i].tag == )
	}
	return 0;
}

#endif
