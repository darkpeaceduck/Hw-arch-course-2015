CC_FLAGS =  -m32  -nostdlib -nostdinc -ffreestanding
all:mbr multiboot

mbr:mbr.o
	ld -T mbr_linker mbr.o -o mbr
	rm -f mbr.o
mbr.o:mbr.S
	gcc -c mbr.S $(CC_FLAGS)
multiboot:multiboot.o multiboot_init.o
	ld -m elf_i386 -T multiboot_linker multiboot.o multiboot_init.o -o multiboot
	rm -f multiboot.o multiboot_init.o
multiboot.o:multiboot.c
	gcc -c multiboot.c $(CC_FLAGS)
multiboot_init.o:multiboot.S
	gcc -c multiboot.S $(CC_FLAGS) -o multiboot_init.o
clean:
	rm -f mbr multiboot mbr.o multiboot.o multiboot_init.o
.PHONY: clean

