#include "memory/mmu/cache.h"
#include "memory/memory.h"
#include <stdlib.h>

#ifdef CACHE_ENABLED

CacheLine cache[CATCHE_LINES]; // define cache

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
    // write through
    memcpy(hw_mem + paddr, &data, len);
#ifndef HAS_DEVICE_IDE
    // update cache
	PADDR_STATUS addr_state;
    addr_state.val = paddr;
    int cur_gp = addr_state.group * 8, next_gp = cur_gp + 8;
    // if found in cache
	for (int i = cur_gp; i < next_gp; i++) {
	    if (cache[i].valid_bit && cache[i].tag == addr_state.tag) {
	        if (addr_state.block + len > CATCHE_WIDTH) {
                size_t cur = CATCHE_WIDTH - addr_state.block;
                memcpy(cache[i].block + addr_state.block, &data, cur);
                size_t left = len - cur;
                for (int j = next_gp; j < next_gp + 8; j++) {
                    if (cache[j].valid_bit && cache[j].tag == addr_state.tag) {
                        memcpy(cache[j].block, (uint8_t*)&data + cur, left);
                    }
                }
	        }
	        else {
	            memcpy(cache[i].block + addr_state.block, &data, len);
	        }
	    }
	}
#endif
}

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len)
{
#ifdef HAS_DEVICE_IDE
    uint32_t ret = 0;
    memcpy(&ret, hw_mem + paddr, len);
    return ret;
#else
    PADDR_STATUS addr_state;
    addr_state.val = paddr;
    int cur_gp = addr_state.group * 8, next_gp = cur_gp + 8;
    // if found in cache
	for (int i = cur_gp; i < next_gp; i++) {
	    if (cache[i].valid_bit && cache[i].tag == addr_state.tag) {
	        if (addr_state.block + len > CATCHE_WIDTH) {
                size_t cur = CATCHE_WIDTH - addr_state.block;
                memcpy(&ret, cache[i].block + addr_state.block, cur);
                size_t left = len - cur;
                for (int j = next_gp; j < next_gp + 8; j++) {
                    if (cache[j].valid_bit && cache[j].tag == addr_state.tag) {
                        memcpy((uint8_t*)&ret + cur, cache[j].block, left);
                        return ret;
                    }
                }
                break;
	        }
	        else {
	            memcpy(&ret, cache[i].block + addr_state.block, len);
	            return ret;
	        }
	    }
	}
	// if not found in chache and has empty lines
	for (int i = cur_gp; i < next_gp; i++) {
	    if (!cache[i].valid_bit) {
	        cache[i].valid_bit = 1;
	        cache[i].tag = addr_state.tag;
	        
	        PADDR_STATUS tmp;
	        tmp.tag = addr_state.tag;
	        tmp.group = addr_state.group;
	        tmp.block = 0;
	        
	        memcpy(cache[i].block, hw_mem + tmp.val, CATCHE_WIDTH);
	        
	        memcpy(&ret, hw_mem + paddr, len);
	        return ret;
	    }
	}
	// if not found in chache and no empty lines
	srand(time(0));
    int i = cur_gp + rand() % 8;
    cache[i].valid_bit = 1;
    cache[i].tag = addr_state.tag;
    
    PADDR_STATUS tmp;
    tmp.tag = addr_state.tag;
    tmp.group = addr_state.group;
    tmp.block = 0;
    
    memcpy(cache[i].block, hw_mem + tmp.val, CATCHE_WIDTH);
    
    memcpy(&ret, hw_mem + paddr, len);
    return ret;
#endif
}

#endif
