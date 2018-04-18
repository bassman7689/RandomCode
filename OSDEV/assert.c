#include "assert.h"

extern void panic(const char *message, const char *file, unsigned int line)
{
	asm volatile("cli");

	monitor_write("\nPANIC(");
	monitor_write((char *)message);
	monitor_write(") at ");
	monitor_write((char *)file);
	monitor_write(":");
	monitor_write_dec(line);
	monitor_write("\n");
	for(;;);
}

extern void panic_assert(const char *file, unsigned int line, const char *desc)
{
	asm volatile("cli");

	monitor_write("\nASSERTION-FAILED(");
	monitor_write((char *)desc);
	monitor_write(") at ");
	monitor_write((char *)file);
	monitor_write(":");
	monitor_write_dec(line);
	monitor_write("\n");
	for(;;);
}
