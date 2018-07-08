CC_FLAGS =  -m32  -nostdlib -nostdinc -ffreestanding
all:multiboot

multiboot:kernel.o kernel_init.o video.o
	ld -m elf_i386 -T kernel_linker kernel.o kernel_init.o video.o -o multiboot
kernel.o:kernel.c
	gcc -c kernel.c $(CC_FLAGS)
video.o:video.c
	gcc -c video.c $(CC_FLAGS)
kernel_init.o:kernel.S
	gcc -c kernel.S $(CC_FLAGS) -o kernel_init.o
clean:
	rm -f multiboot mbr.o kernel.o kernel_init.o video.o
.PHONY: clean

