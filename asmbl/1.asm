section .data
	message db "Hello, world!", 10
	message_length equ $ - message

section .text
	global _start

_start:
	mov eax, 1
	mov edi, 1
	mov rsi, message
	mov edx, message_length
	syscall

	mov eax, 60
	xor edi, edi
	syscall
