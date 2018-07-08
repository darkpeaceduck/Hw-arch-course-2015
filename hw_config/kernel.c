#define FLAG_MEM 6
#define FLAG_CM 2
#include "kernel.h"
#include "acpi.h"

extern void cls(void);
extern void printf(const char *format, ...);
extern int strcomp(const char *f, const char *s, int len);



void print_cmd(multiboot_info_t *mbi) {
	if(!(mbi->flags & (1<<FLAG_CM))){
		return;
	}
	printf("cmdline: %s\n", (char *) mbi->cmdline);
}

void print_mem(multiboot_info_t *mbi) {
	if (!(mbi->flags & (1 << FLAG_MEM)) || mbi->mmap_length == 0) {
		printf("cant provide memmap\n");
		return;
	}
	multiboot_memory_map_t *mmap;
	for (mmap = (multiboot_memory_map_t *) mbi->mmap_addr;
			(unsigned) mmap < mbi->mmap_addr + mbi->mmap_length;
			mmap = (multiboot_memory_map_t *) ((unsigned) mmap + mmap->size
					+ sizeof(mmap->size))) {
		printf("memory range: 0x%o-0x%o, type %d\n",
				(mmap->addr),
				(mmap->addr + mmap->len - 1),
				(mmap->type));
	}
}

unsigned get_EBDA_adress() {
	const unsigned adress = 0x40E;
	return ((short *)adress)[0] * 16;
}



int find_RSD_adress() {
	const char * str = "RSD PTR ";
	const int len = 8;
	int i;
	for (i = 0xE0000; i <= 0xFFFFF; i++) {
		if (strcomp((char *) i, str, len)) {
			return i;
		}
	}
	unsigned ebda = get_EBDA_adress();
	const int KB = 1 << 10;
	for (i = ebda; ebda + KB; i++) {
		if (strcomp((char *) i, str, len)) {
			return i;
		}
	}
	return -1;
}

void print_apic_info(acpi_header * header) {
	madt * madt_s = (madt *) header;
	if (madt_s->flags & 1) {
		printf("PC/AT dual PIC supported\n");
	}
	char * ptr = (char *) &madt_s->entries[0];
	int local_adress_override = madt_s->local_controller_adress;
	int i;
	for (i = 0; ptr < ((char *) header + header->Length); i++) {
		madt_entry * start = (madt_entry *) ptr;
		int tt = start->type;
		if (tt == 0) {
			processor_local_apic * pc = (processor_local_apic *) (ptr
					+ sizeof(*start));
			int aid = pc->apic_id;
			printf("Processor Local APIC %d\n", aid);
		}
		if (tt == 1) {
			io_apic * pc = (io_apic *) (ptr + sizeof(*start));
			int id = pc->io_id;
			printf("IOAPIC %d at 0x%x IRQs from %d\n", id,
					pc->adress, pc->gsi_bast);
		}
		if (tt == 5) {
			local_apic_override_struct * pc = (local_apic_override_struct *)(ptr + sizeof(*start));
			local_adress_override = pc->local_apic_adress & 0xffffffff;
		}
		if (tt == 9) {
			processor_local_x2_apic * pc = (processor_local_x2_apic *) (ptr
								+ sizeof(*start));
			printf("Processor Local x2 APIC %d\n", pc->apic_id);
		}
		ptr = ptr + start->Length;
	}
	printf("Local APIC's acceptible at 0x%x\n", local_adress_override);
}

void print_acpi_info(unsigned long adress) {
	rsdp_descriptor * rsdp = (rsdp_descriptor *)(adress);
	rsdt * rsdt_s = (rsdt *) rsdp->RsdtAddress;
	int i;
	int entries = (rsdt_s->h.Length - sizeof(rsdt_s->h)) / 4;
	for (i = 0; i < entries; i++) {
		acpi_header *h = (acpi_header *) rsdt_s->PointerToOtherSDT[i];
		if (strcomp(h->Signature, "APIC", 4)) {
			print_apic_info(h);
		}
	}
}

void main(unsigned adress) {
	multiboot_info_t *mbi = (multiboot_info_t *) adress;
	cls();
	print_cmd(mbi);
	print_mem(mbi);
	int rsd_adress = find_RSD_adress();
	if(rsd_adress == -1){
		printf("Cannot find RSDP\n");
		return;
	}
	print_acpi_info(rsd_adress);
	return;
}


