# Hello World OS 
# ( 100 lines of code for a "Hello World" )
By Sean Rodman


# The bootloader

- We will be using grub for our boot loader.
- The good thing about this is we don't have to write our own bootloader.
- The bad thing is it requires more setup.


# Grub Setup: Directory Structure

First, we will need to make some directories for our grub setup:

```sh
   mkdir -p iso/boot/grub
```


# Grub Setup: Creating the Grub Menu File

edit the file iso/boot/grub/menu.lst with your favorite text editor and add the below file contents:

```grub
default=0
timeout=0

title HelloWorldOS
kernel /boot/kernel.elf
```



# Assembly Code? Oh NO's 

Next, we need to write an assembly code layer that sets up some data required
by grub or other multiboot complient bootloaders so that they can recognize our
kernel as a multiboot complient kernel.

This assembly code also setups a stack so that we can write the rest of our kernel in C.

We will be using the NetWide Assembler (Nasm) Because I like intel syntax.


# Lets actually Write the Kernel now!

Things to Remember when writing your own OS:
- You write your own standard C library
- You write your own drivers
- You write your own everything

features we need for a simple hello world kernel:
- a way to print to the screen
- a way to move the cursor
- a way to clear the screen
- parsing for newline characters in our print function

I will show all of these features in the c code


# Building Your Bootable ISO

I have a Makefile that will build my kernel with the grub bootloader
and the grub config that we talked about before.


# Configuring Bochs to boot our ISO

edit bochsrc.txt and add the below information:

```asm
megs:            32
romimage:        file=/full/path/to/bochs/BIOS-bochs-latest
vgaromimage:     file=/full/path/to/bochs/VGABIOS-lgpl-latest
ata0-master:     type=cdrom, path="/full/path/to/iso", status=inserted
boot:            cdrom
log:             bochslog.txt
clock:           sync=realtime, time0=local
cpu:             count=1, ips=1000000
```
