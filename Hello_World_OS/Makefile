OBJECTS = loader.o kmain.o
CC = gcc
CFLAGS =-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -I/usr/lib/gcc/x86_64-linux-gnu/5/include 
LDFLAGS =-T link.ld -melf_i386
AS = nasm
ASFLAGS =-f elf32

all: HelloWorldOS.iso

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

HelloWorldOS.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
		    -b boot/grub/stage2_eltorito    \
		    -no-emul-boot                   \
		    -boot-load-size 4               \
		    -A HelloWorldOS                 \
		    -input-charset utf8             \
		    -quiet                          \
		    -boot-info-table                \
		    -o HelloWorldOS.iso             \
		    iso

run: HelloWorldOS.iso
	bochs -f bochsrc.txt -q

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf iso/boot/kernel.elf HelloWorldOS.iso bochslog.txt
