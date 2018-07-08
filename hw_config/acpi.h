typedef unsigned int uint32_t ;
typedef char uint8_t;	
typedef unsigned short uint16_t;
typedef unsigned long long uint64_t;

typedef struct  {
  char Signature[4];
  uint32_t Length;
  uint8_t Revision;
  uint8_t Checksum;
  char OEMID[6];
  char OEMTableID[8];
  uint32_t OEMRevision;
  uint32_t CreatorID;
  uint32_t CreatorRevision;
}__attribute__ ((packed))  acpi_header;

typedef struct  {
  acpi_header h;
  uint32_t PointerToOtherSDT[1];
}__attribute__ ((packed))  rsdt;

typedef struct  {
 char Signature[8];
 uint8_t Checksum;
 char OEMID[6];
 uint8_t Revision;
 uint32_t RsdtAddress;
} __attribute__ ((packed)) rsdp_descriptor;

typedef struct {
	uint8_t type;
	uint8_t Length;
}__attribute__ ((packed))  madt_entry;

typedef struct {
	acpi_header h;
	uint32_t local_controller_adress;
	uint32_t flags;
	madt_entry entries[1];
}__attribute__ ((packed))  madt;

typedef struct {
	uint8_t proc_id;
	uint8_t apic_id;
	uint32_t flags;
}__attribute__ ((packed)) processor_local_apic;

typedef struct{
	uint8_t io_id;
	uint8_t Reserved;
	uint32_t adress;
	uint32_t gsi_bast;
}__attribute__ ((packed)) io_apic;

typedef struct{
	uint8_t type;
	uint8_t length;
	uint16_t reserved;
	uint64_t local_apic_adress;
}__attribute__ ((packed)) local_apic_override_struct;

typedef struct {
	uint16_t reserved;
	uint32_t apic_id;
	uint32_t flags;
	uint32_t proc_id;
}__attribute__ ((packed)) processor_local_x2_apic;




