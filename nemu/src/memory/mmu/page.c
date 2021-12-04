#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
// 	printf("\nPlease implement page_translate()\n");
// 	fflush(stdout);
// 	assert(0);
    printf("debug: here \n");
	LADDR_STATUS laddr_status;
	laddr_status.val = laddr;
	PDE* pde = (PDE*)(hw_mem + (cpu.cr3.pdbr << 12));
	if (!pde[laddr_status.dir].present) {
	    printf("\nPage Table Not Present\n");
	    fflush(stdout);
	    assert(0);
	}
	PTE* pte = (PTE*)(hw_mem + (pde[laddr_status.dir].page_frame << 12));
	printf("%x \n", pte - hw_mem);
	if (!pte[laddr_status.page].present) {
	    printf("\nPage Not Present\n");
	    fflush(stdout);
	    assert(0);
	}
	return (pte[laddr_status.page].page_frame << 12) + laddr_status.offset;
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
#endif
}
