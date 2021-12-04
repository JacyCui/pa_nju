#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
// 	printf("\nPlease implement page_translate()\n");
// 	fflush(stdout);
// 	assert(0);
	LADDR_STATUS laddr_status;
	laddr_status.val = laddr;
	// printf("cpu.cr3.padr = %x \n", (cpu.cr3.pdbr << 12));
	PDE* pde = (PDE*)(hw_mem + (cpu.cr3.pdbr << 12)) + laddr_status.dir;
	if (!pde->present) {
	    printf("\nPage Table Not Present\n");
	    fflush(stdout);
	    assert(0);
	}
	PTE* pte = (PTE*)(hw_mem + (pde->page_frame << 12)) + laddr_status.page;
	// printf("%x \n", (pde->page_frame << 12));
	if (!pte->present) {
	    printf("\nPage Not Present\n");
	    fflush(stdout);
	    assert(0);
	}
	return (pte->page_frame << 12) + laddr_status.offset;
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
#endif
}
