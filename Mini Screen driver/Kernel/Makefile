

OBJECTS = loader.o kernel_main.o 

os.iso :  kernel-22.elf
	cp kernel-22.elf iso/boot/
	grub-mkrescue -o os.iso iso

kernel-22.elf : $(OBJECTS)
	ld -T link.ld -melf_i386 $(OBJECTS) -o kernel-22.elf

loader.o : loader.s
	nasm -f elf32 $<

kernel_main.o : kernel_main.c
	gcc -c -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs  kernel_main.c -o kernel_main.o
#-Wall -Wextra -Werror

io_low_level.o : io_low_level.c
		gcc -c -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs  io_low_level.c -o io_low_level.o

run : bochsrc.txt os.iso
	bochs -f bochsrc.txt -q 

.PHONY : clean
clean :
	-rm *.o *.elf *.iso bochslog.txt

