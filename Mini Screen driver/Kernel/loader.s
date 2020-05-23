global loader 					; the entry symbol for ELF
extern main	
extern frame_buffer_write_shell	
extern fb_print_rectangule

MAGIC_NUMBER equ 0x1BADB002 	; define the magic number constant
FLAGS equ 0x0 					; multiboot flags
CHECKSUM equ -MAGIC_NUMBER 		; calculate the checksum
								; (magic number + checksum + flags should equal 0)


KERNEL_STACK_SIZE equ 4096
FRAME_BUFFER equ 0x000B8000			

section .text 					; start of the text (code) section
	
	;multiboot spec
	align 4 						; the code must be 4 byte aligned
		dd MAGIC_NUMBER 				; write the magic number to the machine code,
		dd FLAGS 						; the flags,
		dd CHECKSUM 					; and the checksum

	loader: 						; the loader label (defined as entry point in linker script)
		
		mov esp, kernel_stack+KERNEL_STACK_SIZE ; setup 		
		call main
		
	.loop:
		jmp .loop 						; loop forever

section .bss 

	align 4
	kernel_stack:
		resb KERNEL_STACK_SIZE



;nasm -f elf32 loader.s