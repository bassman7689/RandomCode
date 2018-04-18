#include "timer.h"
#include "isr.h"
#include "monitor.h"

unsigned int tick = 0;

static void timer_callback(registers_t regs)
{
	tick++;
	monitor_write("Interrupt Number: ");
	monitor_write_dec(regs.int_no);
	monitor_write(", Tick: ");
	monitor_write_dec(tick);
	monitor_write("\n");
}

void init_timer(unsigned int frequency)
{
	register_interrupt_handler(IRQ0, &timer_callback);

	unsigned int divisor = 1193180 / frequency;

	outb(0x43, 0x36);

	unsigned char l = (unsigned char)(divisor & 0xFF);
	unsigned char h = (unsigned char)((divisor >> 8) & 0xFF);

	outb(0x40, l);
	outb(0x40, h);
	monitor_write("Timer initialized with frequency ");
	monitor_write_dec(frequency);
	monitor_write("\n");
}
