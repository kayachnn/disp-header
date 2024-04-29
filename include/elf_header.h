#ifndef ELF_HEADER_H
#define ELF_HEADER_H

#include <stdint.h>

#pragma pack(push, 1)

enum EI_DATA_INDEX
{
    EI_MAG0         = 0,
    EI_MAG1         = 1,
    EI_MAG2         = 2,
    EI_MAG3         = 3,
    EI_CLASS        = 4,
    EI_DATA         = 5,
    EI_VERSION      = 6,
    EI_OSABI        = 7,
    EI_ABIVERSION   = 8,
    EI_PAD          = 9,
    EI_NIDENT       = 16,
};

typedef struct
{
    uint8_t      e_ident[EI_NIDENT];
    uint16_t     e_type;
    uint16_t     e_machine;
    uint32_t     e_version;
    uint32_t     e_entry;
    uint32_t     e_phoff;
    uint32_t     e_shoff;
    uint32_t     e_flags;
    uint16_t     e_ehsize;
    uint16_t     e_phentsize;
    uint16_t     e_phnum;
    uint16_t     e_shentsize;
    uint16_t     e_shnum;
    uint16_t     e_shstrndx; 
} Elf32_Ehdr;

typedef struct
{
    uint8_t     e_ident[EI_NIDENT];
    uint16_t    e_type;
    uint16_t    e_machine;
    uint32_t    e_version;
    uint64_t    e_entry;
    uint64_t    e_phoff;
    uint64_t    e_shoff;
    uint32_t    e_flags;
    uint16_t    e_ehsize;
    uint16_t    e_phentsize;
    uint16_t    e_phnum;
    uint16_t    e_shentsize;
    uint16_t    e_shnum;
    uint16_t    e_shstrndx;
} Elf64_Ehdr;

enum EI_CLASS
{
    ELFCLASSNONE = 0,
    ELFCLASS32,
    ELFCLASS64,
};

enum EI_DATA
{
    ELFDATANONE = 0,
    ELFDATA2LSB = 1,
    ELFDATA2MSB = 2,
};

enum EI_VERSION
{
    EV_NONE     = 0,
    EV_CURRENT  = 1,
};

enum EI_OSABI
{
    ELFOSABI_SYSV       = 0,
    ELFOSABI_HPUX       = 1,
    ELFOSABI_STANDALONE = 255,
};

enum E_TYPE
{
    ET_NONE     = 0,
    ET_REL      = 1,
    ET_EXEC     = 2,
    ET_DYN      = 3,
    ET_CORE     = 4,
    ET_LOOS     = 0xFE00,
    ET_HIOS     = 0xFEFF,
    ET_LOPROC   = 0xFF00,
    ET_HIPROC   = 0xFFFF,
};

typedef enum {
    EM_NONE         = 0,
    EM_M32          = 1,
    EM_SPARC        = 2,
    EM_386          = 3,
    EM_68K          = 4,
    EM_88K          = 5,
    EM_860          = 7,
    EM_MIPS         = 8,
    EM_PARISC       = 15,
    EM_SPARC32PLUS  = 18,
    EM_PPC          = 20,
    EM_PPC64        = 21,
    EM_ARM          = 40,
    EM_SPARCV9      = 43,
    EM_IA_64        = 50,
    EM_X86_64       = 62,
    EM_AARCH64      = 183,
    EM_RISCV        = 243
    // Add more as needed
} EM_MACHINE;


void print_common_32_64
(
    uint8_t* e_ident,
    enum EI_CLASS ei_class,
    enum EI_DATA ei_data,
    enum EI_VERSION ei_version,
    enum EI_OSABI os_abi,
    uint16_t e_type,
    uint16_t e_machine,
    uint32_t version
);


void print_header_information_32
(
    Elf32_Ehdr* elf32_header,
    enum EI_CLASS ei_class,
    enum EI_DATA ei_data,
    enum EI_VERSION ei_version,
    enum EI_OSABI os_abi
);

void print_header_information_64
(
    Elf64_Ehdr* elf64_header,
    enum EI_CLASS ei_class,
    enum EI_DATA ei_data,
    enum EI_VERSION ei_version,
    enum EI_OSABI os_abi
);

#pragma pack(pop)
#endif