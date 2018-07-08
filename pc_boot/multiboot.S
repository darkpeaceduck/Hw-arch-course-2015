#define MULTIBOOT_MAGIC_NUMBER 0x1BADB002
#define MULTIBOOT_FLAGS 0x00
#define MULTIBOOT_CHECKSUM -(MULTIBOOT_MAGIC_NUMBER + MULTIBOOT_FLAGS )
#define STACK_SIZE 8192

.code32 .text
  .align 4
  .long MULTIBOOT_MAGIC_NUMBER            
  .long MULTIBOOT_FLAGS                 
  .long MULTIBOOT_CHECKSUM

.global start
start:
    call main
    hlt
.bss
    .lcomm _sys_stack, STACK_SIZE

