#define MULTIBOOT_MAGIC_NUMBER 0x1BADB002
#define MULTIBOOT_FLAGS 0x02
#define MULTIBOOT_CHECKSUM -(MULTIBOOT_MAGIC_NUMBER + MULTIBOOT_FLAGS )
#define STACK_SIZE 8192

.code32 .text
.global start
start:
_start:
	jmp entry
header:
	.align 4			
	.long MULTIBOOT_MAGIC_NUMBER            
	.long MULTIBOOT_FLAGS                 
	.long MULTIBOOT_CHECKSUM
entry:
  	movl    $(_sys_stack + STACK_SIZE), %esp
    pushl   %ebx
    call main
infinite_loop: 
	hlt
	jmp infinite_loop
.bss
    .lcomm _sys_stack, STACK_SIZE
