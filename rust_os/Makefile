arch ?= x86_64
kernel := build/kernel-$(arch).bin
iso := build/os-$(arch).iso

linker_script := src/arch/$(arch)/linker.ld
grub_cfg := src/arch/$(arch)/grub.cfg
assembly_source_files := $(wildcard src/arch/$(arch)/*.s)
assembly_object_files := $(patsubst src/arch/$(arch)/%.s, \
    build/arch/$(arch)/%.o, $(assembly_source_files))

target ?= $(arch)-rust_os
rust_os := target/$(target)/debug/librust_os.a

HOST=$(shell uname)

.PHONY: all clean run iso kernel

all: $(kernel)

clean:
	@rm -r build target

ifeq ($(HOST), Darwin)
run:
	@qemu-system-x86_64 -cdrom $(iso) -m 500M
else
run: $(iso)
	@qemu-system-x86_64 -cdrom $(iso) -m 500M
endif

run_other: $(iso)

iso: $(iso)

$(iso): $(kernel) $(grub_cfg)
	@mkdir -p build/isofiles/boot/grub
	@cp $(kernel) build/isofiles/boot/kernel.bin
	@cp $(grub_cfg) build/isofiles/boot/grub
	@grub-mkrescue -o $(iso) build/isofiles 2> /dev/null
	@rm -r build/isofiles

$(kernel): kernel $(assembly_object_files)
	@ld -n --gc-sections -T $(linker_script) -o $(kernel) $(assembly_object_files) $(rust_os)

# compile assembly files
build/arch/$(arch)/%.o: src/arch/$(arch)/%.s
	@mkdir -p $(shell dirname $@)
	@nasm -felf64 $< -o $@

kernel:
	@RUST_TARGET_PATH=$(shell pwd) xargo build --target $(target)
