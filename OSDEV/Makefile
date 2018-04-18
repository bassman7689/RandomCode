OBJECTS = loader.o assert.o io.o strings.o interrupt.o isr.o gdt.o descriptor_tables.o monitor.o timer.o ordered_array.o kheap.o paging.o kmain.o
CC = gcc
CFLAGS =-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS =-T link.ld -melf_i386
AS = nasm
ASFLAGS =-f elf32

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

MohawkOS.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
	            -b boot/grub/stage2_eltorito    \
                    -no-emul-boot                   \
                    -boot-load-size 4               \
                    -A MohawkOS                     \
                    -input-charset utf8             \
                    -quiet                          \
                    -boot-info-table                \
                    -o MohawkOS.iso                 \
		    iso

run: MohawkOS.iso
	bochs -f bochsrc.txt -q

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf MohawkOS.iso
