#include "kheap.h"
#include "paging.h"

extern unsigned int end;
unsigned int placement_address = (unsigned int)&end;
extern page_directory_t *kernel_directory;
heap_t *kheap = 0;

static unsigned int kmalloc_int(unsigned int sz, int align, unsigned int *phys)
{
	if (kheap != 0)
	{
		void *addr = alloc(sz, (unsigned char) align, kheap);
		if (phys != 0)
		{
			page_t *page = get_page((unsigned int) addr, 0, kernel_directory);
			*phys = (page->frame*0x1000) + ((unsigned int)addr&0xFFF);
		}
		return (unsigned int) addr;
	}
	else
	{
		if (align == 1 && (placement_address & 0xFFFFF000))
		{
			placement_address &= 0xFFFFF000;
			placement_address += 0x1000;
		}

		if(phys)
		{
			*phys = placement_address;
		}

		unsigned int tmp = placement_address;
		placement_address += sz;
		return tmp;
	}
}

void kfree(void *p)
{
	free(p, kheap);
}


unsigned int kmalloc_a(unsigned int sz)
{
	return kmalloc_int(sz, 1, 0);
}

unsigned int kmalloc_p(unsigned int sz, unsigned *phys)
{
	return kmalloc_int(sz, 0, phys);
}

unsigned int kmalloc_ap(unsigned int sz, unsigned int *phys)
{
	return kmalloc_int(sz, 1, phys);
}

unsigned int kmalloc(unsigned int sz)
{
	return kmalloc_int(sz, 0, 0);
}

static signed int find_smallest_hole(unsigned int size, unsigned char page_align, heap_t *heap)
{
	unsigned int iterator = 0;
	while (iterator < heap->index.size)
	{
		header_t *header = (header_t*)lookup_ordered_array(iterator, &heap->index);
		if (page_align > 0)
		{
			unsigned int location = (unsigned int)header;
			signed int offset = 0;
			if (((location+sizeof(header_t)) & 0xFFFF00) != 0)
			{
				offset = 0x1000 - (location+sizeof(header_t))%0x1000;
			}

			signed hole_size = (signed int)header->size - offset;
			if (hole_size >= (signed int)size)
			{
				break;
			}
		}
	       	else if (header->size >= size)
	       	{
			break;
		}
		iterator++;
	}
	if (iterator == heap->index.size)
	{
		return -1;
	}
       	else
	{
		return iterator;
	}
}

static signed char header_t_less_than(void *a, void *b)
{
	return (((header_t*)a)->size < ((header_t*)b)->size)?1:0;
}

heap_t *create_heap(unsigned int start_addr, unsigned int end_addr, unsigned int max, unsigned char supervisor, unsigned char readonly)
{
	heap_t *heap = (heap_t*)kmalloc(sizeof(heap_t));

	ASSERT(start_addr%0x1000 == 0);
	ASSERT(end_addr%0x1000 == 0);

	heap->index = place_ordered_array((void*)start_addr, HEAP_INDEX_SIZE, &header_t_less_than);

	start_addr += sizeof(type_t)*HEAP_INDEX_SIZE;

	if ((start_addr & 0xFFFFF000) != 0)
	{
		start_addr &= 0xFFFFF000;
		start_addr += 0x1000;
	}

	heap->start_address = start_addr;
	heap->end_address = end_addr;
	heap->max_address = max;
	heap->supervisor = supervisor;
	heap->readonly = readonly;

	header_t *hole = (header_t*)start_addr;
	hole->size = end_addr-start_addr;
	hole->magic = HEAP_MAGIC;
	hole->is_hole = 1;
	insert_ordered_array((void*)hole, &heap->index);

	return heap;
}

static void expand(unsigned int new_size, heap_t *heap)
{
	ASSERT(new_size > heap->end_address - heap->start_address);
	if ((new_size & 0xFFFFF000) != 0)
	{
		new_size &= 0xFFFFF000;
		new_size += 0x1000;
	}
	ASSERT(heap->start_address+new_size <= heap->max_address);

	unsigned int old_size = heap->end_address - heap->start_address;
	unsigned int i = old_size;

	while (i < new_size)
	{
		alloc_frame(get_page(heap->start_address + i, 1, kernel_directory), (heap->supervisor) ? 1 : 0, (heap->readonly) ? 0 : 1);
		i += 0x1000;
	}
	heap->end_address = heap->start_address + new_size;
}

static unsigned int contract(unsigned int new_size, heap_t *heap)
{
	ASSERT(new_size < heap->end_address - heap->start_address);
	if (new_size & 0x1000)
	{
		new_size &= 0x1000;
		new_size += 0x1000;
	}

	if (new_size < HEAP_MIN_SIZE)
	{
		new_size = HEAP_MIN_SIZE;
	}

	unsigned int old_size = heap->end_address - heap->start_address;
	unsigned int i = old_size - 0x1000;
	while (new_size < i)
	{
		free_frame(get_page(heap->start_address + i, 0, kernel_directory));
		i -= 0x1000;
	}
	heap->end_address = heap->start_address + new_size;
	return new_size;
}

void *alloc(unsigned int size, unsigned char page_align, heap_t *heap)
{
	unsigned int new_size = size + sizeof(header_t) + sizeof(footer_t);

	signed int iterator = find_smallest_hole(new_size, page_align, heap);

	if (iterator == -1)
	{
		unsigned int old_length = heap->end_address - heap->start_address;
		unsigned int old_end_address = heap->end_address;

		expand(old_length+new_size, heap);
		unsigned int new_length = heap->end_address - heap->start_address;

		iterator = 0;
		unsigned int idx = 0xFFFFFFFF;
		unsigned int value = 0x0;
		while ((unsigned int) iterator < heap->index.size)
		{
			unsigned int tmp = (unsigned int)lookup_ordered_array(iterator, &heap->index);
			if (tmp > value)
			{
				value = tmp;
				idx = iterator;
			}
			iterator++;
		}

		if (idx == 0xFFFFFFFF)
		{
			header_t *header = (header_t *)old_end_address;
			header->magic = HEAP_MAGIC;
			header->size = new_length - old_length;
			header->is_hole = 1;
			footer_t *footer = (footer_t *) (old_end_address + header->size - sizeof(footer_t));
			footer->magic = HEAP_MAGIC;
			footer->header = header;
			insert_ordered_array((void *)header, &heap->index);
		}
		else
		{
			header_t *header = lookup_ordered_array(idx, &heap->index);
			header->size += new_length - old_length;
			footer_t *footer = (footer_t *) ((unsigned int)header + header->size - sizeof(footer_t));
			footer->header = header;
			footer->magic = HEAP_MAGIC;
		}

		return alloc(size, page_align, heap);
	}

	header_t *orig_hole_header = (header_t *)lookup_ordered_array(iterator, &heap->index);
	unsigned int orig_hole_pos = (unsigned int)orig_hole_header;
	unsigned int orig_hole_size = orig_hole_header->size;
	if (orig_hole_size - new_size < sizeof(header_t)+sizeof(footer_t))
	{
		size += orig_hole_size - new_size;
		new_size = orig_hole_size;
	}

	if (page_align && orig_hole_pos & 0xFFFFF000)
	{
		unsigned int new_location = orig_hole_pos + 0x1000 - (orig_hole_pos & 0xFFF) - sizeof(header_t);
		header_t *hole_header     = (header_t *)orig_hole_pos;
		hole_header->size         = 0x1000 - (orig_hole_pos & 0xFFF) - sizeof(header_t);
		hole_header->magic        = HEAP_MAGIC;
		hole_header->is_hole      = 1;
		footer_t *hole_footer     = (footer_t *) ((unsigned int)new_location - sizeof(footer_t));
		hole_footer->magic        = HEAP_MAGIC;
		hole_footer->header       = hole_header;
		orig_hole_pos             = new_location;
		orig_hole_size            = orig_hole_size - hole_header->size;
	}

	else
	{
		remove_ordered_array(iterator, &heap->index);
	}

	header_t *block_header = (header_t *)orig_hole_pos;
	block_header->magic    = HEAP_MAGIC;
	block_header->is_hole  = 0;
	block_header->size     = new_size;

	footer_t *block_footer = (footer_t *) (orig_hole_pos + sizeof(header_t) + size);
	block_footer->magic    = HEAP_MAGIC;
	block_footer->header   = block_header;

	if (orig_hole_size - new_size > 0)
	{
		header_t *hole_header = (header_t *) (orig_hole_pos + sizeof(header_t) + size + sizeof(footer_t));
		hole_header->magic    = HEAP_MAGIC;
		hole_header->is_hole  = 1;
		hole_header->size     = orig_hole_size - new_size;
		footer_t *hole_footer = (footer_t *) ((unsigned int)hole_header + orig_hole_size - new_size - sizeof(footer_t));
		if ((unsigned int)hole_footer < heap->end_address)
		{
			hole_footer->magic = HEAP_MAGIC;
			hole_footer->header = hole_header;
		}

		insert_ordered_array((void *)hole_header, &heap->index);
	}

	return (void *) ((unsigned int)block_header+sizeof(header_t));
}

void free(void *p, heap_t *heap)
{
	if (p == 0)
	{
		return;
	}

	header_t *header = (header_t*) ((unsigned int) p - sizeof(header_t));
	footer_t *footer = (footer_t*) ((unsigned int) header + header->size - sizeof(footer_t));

	ASSERT(header->magic == HEAP_MAGIC);
	ASSERT(footer->magic == HEAP_MAGIC);

	header->is_hole = 1;

	char do_add = 1;

	footer_t *test_footer = (footer_t *) ((unsigned int) header - sizeof(footer_t));
	if (test_footer->magic == HEAP_MAGIC &&
			test_footer->header->is_hole == 1)
	{
		unsigned int cache_size = header->size;
		header = test_footer->header;
		footer->header = header;
		header->size += cache_size;
		do_add = 0;
	}

	header_t *test_header = (header_t*) ((unsigned int) footer + sizeof(footer_t));
	if (test_header->magic == HEAP_MAGIC &&
			test_header->is_hole == 1)
	{
		header->size += test_header->size;
		test_footer = (footer_t *) ((unsigned int) test_header + test_header->size - sizeof(footer_t));
		footer = test_footer;

		unsigned int iterator = 0;
		while ((iterator < heap->index.size) &&
				(lookup_ordered_array(iterator, &heap->index) != (void *) test_header))
		{
			iterator++;
		}

		ASSERT(iterator < heap->index.size);
		remove_ordered_array(iterator, &heap->index);
	}

	if ((unsigned int) footer + sizeof(footer_t) == heap->end_address)
	{
		unsigned int old_length = heap->end_address - heap->start_address;
		unsigned int new_length = contract((unsigned int)header - heap->start_address, heap);

		if (header->size - (old_length - new_length) > 0)
		{
			header->size -= old_length - new_length;
			footer = (footer_t *) ((unsigned int) header + header->size - sizeof(footer_t));
			footer->magic = HEAP_MAGIC;
			footer->header = header;
		}
		else
		{
			unsigned int iterator = 0;
			while ((iterator < heap->index.size) &&
						(lookup_ordered_array(iterator, &heap->index) != (void *) test_header))
			{
				iterator++;
			}

			if (iterator < heap->index.size)
			{
				remove_ordered_array(iterator, &heap->index);
			}
		}
	}

	if (do_add == 1)
	{
		insert_ordered_array((void *) header, &heap->index);
	}
}