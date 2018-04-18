global _main

section .text

_main:
	mov rax, WRITE_SYSCALL
	mov rdi, STDOUT
	mov rsi, message
	mov rdx, message.len
	syscall

	mov rax, EXIT_SYSCALL
	xor rdi, rdi
	syscall

message:
	db	"Hello, World!", 10

	.len: equ $ - message

WRITE_SYSCALL equ 0x2000004
EXIT_SYSCALL equ 0x2000001
STDOUT equ 1
