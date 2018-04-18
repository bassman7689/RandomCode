#include "paging.h"
#include "kheap.h"

page_directory_t *kernel_directory=0;
page_directory_t *current_directory=0;

unsigned int *frames;
unsigned int nframes;

extern heap_t *kheap;

extern unsigned int placement_address;

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

static void set_frame(unsigned int frame_addr)
{
	unsigned int frame = frame_addr/0x1000;
	unsigned int idx = INDEX_FROM_BIT(frame);
	unsigned int off = OFFSET_FROM_BIT(frame);
	frames[idx] |= (0x1 << off);
}

static void clear_frame(unsigned int frame_addr)
{
	unsigned int frame = frame_addr/0x1000;
	unsigned int idx = INDEX_FROM_BIT(frame);
	unsigned int off = OFFSET_FROM_BIT(frame);
	frames[idx] &= ~(0x1 << off);
}

static unsigned int first_frame()
{
	unsigned int i, j;
	for (i = 0; i < INDEX_FROM_BIT(nframes); i++)
	{
		if (frames[i] != 0xFFFFFFFF)
		{
			for (j = 0; j < 32; j++)
			{
				unsigned int toTest = 0x1 << j;
				if (!(frames[i]&toTest))
				{
					return i*4*8+j;
				}
			}
		}
	}
	return (unsigned int)-1;
}

void alloc_frame(page_t *page, int is_kernel, int is_writeable)
{
	if(page->frame != 0)
	{
		return;
	}
	else
	{
		unsigned int idx = first_frame();
		if (idx == (unsigned int)-1)
		{
			PANIC("No free frames!");
		}
		set_frame(idx*0x1000);
		page->present = 1;
		page->rw = (is_writeable)?1:0;
		page->user = (is_kernel)?0:1;
		page->frame = idx;
	}
}

void free_frame(page_t *page)
{
	unsigned int frame;
	if(!(frame=page->frame))
	{
		return;
	}
	else
	{
		clear_frame(frame);
		page->frame = 0x0;
	}
}

void page_fault(registers_t regs)
{
	unsigned int faulting_address;
	asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

	int present = !(regs.err_code & 0x1);
	int rw = (regs.err_code & 0x2);
	int us = (regs.err_code & 0x4);
	int reserved = (regs.err_code & 0x8);
	int id = (regs.err_code & 0x10);

	monitor_write("Page fault! ( ");
	if (present)  { monitor_write("present "); }
	if (rw)       { monitor_write(" read-only "); }
	if (us)       { monitor_write(" user-mode "); }
	if (reserved) { monitor_write(" reserved "); }
	if (id)       { monitor_write(" instruction_fetch "); }
	monitor_write(") at ");
	monitor_write_hex(faulting_address);
	monitor_write("\n");
	PANIC("Page Fault");
}

void initialize_paging()
{
	unsigned int mem_end_page = 0x1000000;

	nframes = mem_end_page / 0x1000;
	frames = (unsigned int *)kmalloc(INDEX_FROM_BIT(nframes));
	memset((unsigned char *)frames, 0, INDEX_FROM_BIT(nframes));

	kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
	memset((unsigned char *)kernel_directory, 0, sizeof(page_directory_t));
	current_directory = kernel_directory;

	unsigned int i = 0;
	for (i = KHEAP_START; i < KHEAP_START + KHEAP_INITIAL_SIZE; i += 0x1000)
	{
		get_page(i, 1, kernel_directory);
	}

	i = 0;
	while (i < placement_address+0x1000)
	{
		alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
		i += 0x1000;
	}

	for (i = KHEAP_START; i < KHEAP_START + KHEAP_INITIAL_SIZE; i += 0x1000)
	{
		alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
	}

	register_interrupt_handler(14, page_fault);

	switch_page_directory(kernel_directory);

	kheap = create_heap(KHEAP_START, KHEAP_START + KHEAP_INITIAL_SIZE, 0xCFFFF000, 0, 0);
}

void switch_page_directory(page_directory_t *dir)
{
	current_directory = dir;
	asm volatile("mov %0, %%cr3":: "r"(&dir->tablesPhysical));
	unsigned int cr0;
	asm volatile("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page_t *get_page(unsigned int address, int make, page_directory_t *dir)
{
	address /= 0x1000;
	unsigned int table_idx = address / 1024;
	if (dir->tables[table_idx])
	{
		return &dir->tables[table_idx]->pages[address%1024];
	}
	else if (make)
	{
		unsigned int tmp;
		dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
		memset((unsigned char *)dir->tables[table_idx], 0, 0x1000);
		dir->tablesPhysical[table_idx] = tmp | 0x7;
		return &dir->tables[table_idx]->pages[address%1024];
	}
	else
	{
		return 0;
	}
}
