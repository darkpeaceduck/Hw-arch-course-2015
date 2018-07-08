#define PIXEL_MODE 15
#define SCREEN_SIZE 25*80*2
#define SCREEN_MEMORY_PREFIX 0xb800

.code16 .text
.global start

start:
	ljmp $0, $real_start
	
real_start:
	mov $0, %bx
	mov %bx, %ds
	mov $SCREEN_MEMORY_PREFIX, %ax 
	mov %ax, %es
	mov $0, %ax

clean_loop:
	cmp $SCREEN_SIZE, %bx
	je pre_init
	mov %ax, %es:0(%bx)
	mov %ax, %es:1(%bx)
	add $2, %bx
	jmp clean_loop 

pre_init:
	mov $0, %bx

print_loop:
	mov msg(%bx), %ax
	cmp $0, %ax
	je infinite_loop

	mov $PIXEL_MODE, %cx
	mov %ax, %es:0(%bx)
	mov %cx, %es:1(%bx)
	add $2, %bx
	jmp print_loop

infinite_loop:
	jmp infinite_loop
	

.code16 .data
msg:
	.string "H e l l o ,   w o r l d !"

.code16 .section ".mbr_magic", "a"
	.long 0xAA55 

	


