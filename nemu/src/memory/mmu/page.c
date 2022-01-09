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
	    printf("\npde->page_frame = 0x%x, laddr = 0x%x = {dir=0x%x, page=0x%x, offset=0x%x}, Page Table Not Present\n", \
pde->page_frame, laddr, laddr_status.dir, laddr_status.page, laddr_status.offset);
	    fflush(stdout);
	    assert(0);
	}
	PTE* pte = (PTE*)(hw_mem + (pde->page_frame << 12)) + laddr_status.page;

	if (!pte->present) {
	    printf("\npte->page_frame = 0x%x, laddr = 0x%x = {dir=0x%x, page=0x%x, offset=0x%x}, Page Not Present\n", \
pte->page_frame, laddr, laddr_status.dir, laddr_status.page, laddr_status.offset);
	    fflush(stdout);
	    assert(0);
	}
	return (pte->page_frame << 12) + laddr_status.offset;
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
#endif
}
