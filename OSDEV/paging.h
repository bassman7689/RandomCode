#ifndef PAGING_H
#define PAGING_H

#include "isr.h"
#include "strings.h"
#include "monitor.h"
#include "assert.h"

typedef struct page
{
	unsigned int present	: 1;
	unsigned int rw		: 1;
	unsigned int user	: 1;
	unsigned int accessed	: 1;
	unsigned int dirty	: 1;
	unsigned int unused	: 7;
	unsigned int frame	: 20;
} page_t;

typedef struct page_table
{
	page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
	page_table_t *tables[1024];
	unsigned int tablesPhysical[1024];
	unsigned int physicalAddr;
} page_directory_t;

void initialize_paging();

void switch_page_directory(page_directory_t *new);

page_t *get_page(unsigned int address, int make, page_directory_t *dir);
void alloc_frame(page_t *page, int is_kernel, int is_writeable);
void free_frame(page_t *page);

void page_fault(registers_t regs);

#endif
