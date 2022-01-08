#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
	LADDR_STATUS laddr_status;
	laddr_status.val = laddr;

	PDE* pde = (PDE*)(hw_mem + (cpu.cr3.pdbr << 12)) + laddr_status.dir;
	if (!pde->present) {
	    printf("\nPage Table Not Present\n");
	    fflush(stdout);
	    assert(0);
	}
	PTE* pte = (PTE*)(hw_mem + (pde->page_frame << 12)) + laddr_status.page;

	if (!pte->present) {
	    printf("\npte->page_frame = 0x%x, laddr = 0x%x, Page Not Present\n", pte->page_frame, laddr);
	    fflush(stdout);
	    assert(0);
	}
	return (pte->page_frame << 12) + laddr_status.offset;
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
#endif
}
