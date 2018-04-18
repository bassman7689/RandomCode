#include "monitor.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "kheap.h"
#include "paging.h"

int kmain()
{
	init_descriptor_tables();

	monitor_clear();
	unsigned int a = kmalloc(8);
	initialize_paging();
	unsigned int b = kmalloc(8);
	unsigned int c = kmalloc(8);
	monitor_write("a: ");
	monitor_write_hex(a);
	monitor_write(", b: ");
	monitor_write_hex(b);
	monitor_write("\nc: ");
	monitor_write_hex(c);

	kfree((void *)b);
	kfree((void *)c);
	unsigned int d = kmalloc(12);
	monitor_write(", d: ");
	monitor_write_hex(d);

	return 0;
}
