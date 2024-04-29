#include "../include/elf_header.h"

#include <stdint.h>
#include <stdio.h>

void print_common_32_64
(
    uint8_t* e_ident,       //indenfitication first 16 bytes
    enum EI_CLASS class,         //32bit or 64bit
    enum EI_DATA ei_data,   //little or big endian
    enum EI_VERSION ei_version, 
    enum EI_OSABI os_abi, 
    uint16_t e_type,
    uint16_t e_machine,
    uint32_t version
)
{
    fprintf(stdout, "ELF Header:\n");

    /*--------print magic number------*/
    fprintf(stdout, " Magic:\t");
    for (uint8_t i=0; i<EI_NIDENT; i++)
    {
        fprintf(stdout, "%02X ", e_ident[i]);
    }
    fprintf(stdout, "\n");

    /*---------print architecture --------*/
    fprintf(stdout, "%-36s", " Class:");
    if (class == ELFCLASS32)
        fprintf(stdout, "ELF32\n");
    else if (class == ELFCLASS64)
        fprintf(stdout, "ELF64\n");
    
    /*--------print endianness----------*/
    fprintf(stdout, "%-36s", " Data:");
    if (ei_data == ELFDATA2LSB)
        fprintf(stdout, "2's complement, little endian\n");
    else if (ei_data == ELFDATA2MSB)
        fprintf(stdout, "2's complement, big endian\n");
    
    /*--------print version------------*/
    fprintf(stdout, "%-36s", " Version:");
    if (ei_version == EV_NONE)
        fprintf(stdout, "0 (none)\n");
    else if (ei_version == EV_CURRENT)
        fprintf(stdout, "%s", "1 (current)\n");

    /*--------print OS/ABI--------------*/
    fprintf(stdout, "%-36s", " OS/ABI:");
    if (os_abi == ELFOSABI_SYSV)
        fprintf(stdout, "%s\n", "UNIX - System V");
    else if (os_abi == ELFOSABI_HPUX)
        fprintf(stdout, "%s\n", "HP-UX");
    else if (os_abi == ELFOSABI_STANDALONE)
        fprintf(stdout, "%s", "Embedded");
    
    fprintf(stdout, "%-36s%d\n", " ABI Version:", e_ident[EI_ABIVERSION]);

    /*---------print type----------------*/
    fprintf(stdout, "%-36s", " Type:");
    if (e_type == ET_NONE)
        fprintf(stdout, "%s\n", "NONE (No File Type)");
    else if (e_type == ET_REL)
        fprintf(stdout, "%s\n", "REL (Relocatable Object File)");
    else if (e_type == ET_EXEC)
        fprintf(stdout, "%s\n", "EXEC (Executable File)");
    else if (e_type == ET_DYN)
        fprintf(stdout, "%s\n", "DYN (Shared Object File)");
    else if (e_type == ET_CORE)
        fprintf(stdout, "%s\n", "CORE (Core File)");
    else if (e_type == ET_LOOS)
        fprintf(stdout, "%s\n", "LOOS (Environment-specific Use)");
    else if (e_type == ET_HIOS)
        fprintf(stdout, "%s\n", "HIOS");
    else if (e_type == ET_LOPROC)
        fprintf(stdout, "%s\n", "LOPROC");
    else if (e_type == ET_HIPROC)
        fprintf(stdout, "%s\n", "HIPROC");

    /*---------print Machine----------*/
    fprintf(stdout, "%-36s", " Machine:");
    if (e_machine == EM_X86_64)
        fprintf(stdout, "%s\n", "X86_64");
    else if (e_machine == EM_AARCH64)
        fprintf(stdout, "%s\n", "AARCH64");
    else if (e_machine == EM_RISCV)
        fprintf(stdout, "%s\n", "RISCV");
    //TODO implement other machine types

    
    /*---------print version----------*/
    fprintf(stdout, "%-36s%d\n", " Version:", version);
    /*---------print Entry Point Address*/
}

void print_header_information_32
(
    Elf32_Ehdr* elf32_header,
    enum EI_CLASS class,         //32bit or 64bit
    enum EI_DATA ei_data,   //little or big endian
    enum EI_VERSION ei_version, 
    enum EI_OSABI os_abi
)
{
    print_common_32_64(
        &(elf32_header->e_ident[0]), class, ei_data, 
        ei_version, os_abi, elf32_header->e_type, 
        elf32_header->e_machine,
        elf32_header->e_version);

    fprintf(stdout,"%-36s0x%x\n", " Entry point:",
    elf32_header->e_entry);
    fprintf(stdout, "%-36s%d\n", " Start of program headers:",
    elf32_header->e_phoff);
    fprintf(stdout, "%-36s%d\n", " Start of section headers",
    elf32_header->e_shoff);

    fprintf(stdout, "%-36s0x%x\n", " Flags:", elf32_header->e_flags);

    fprintf(stdout, "%-36s%d\n", " Size of this header:", 
    elf32_header->e_ehsize);

    fprintf(stdout, "%-36s%d\n", " Size of program headers:", 
    elf32_header->e_phentsize);

    fprintf(stdout, "%-36s%d\n", "Number of program headers:", 
    elf32_header->e_phnum);

    fprintf(stdout, "%-36s%d\n", " Size of section headers:", 
    elf32_header->e_shentsize);

    fprintf(stdout, "%-36s%d\n", " Number of section headers",
    elf32_header->e_shnum);

    fprintf(stdout, "%-36s%d\n", " Section header string table index:",
    elf32_header->e_shstrndx);
}

void print_header_information_64
(
    Elf64_Ehdr* elf64_header,  
    enum EI_CLASS class,         //32bit or 64bit
    enum EI_DATA ei_data,   //little or big endian
    enum EI_VERSION ei_version, 
    enum EI_OSABI os_abi
)
{
    print_common_32_64(
        (&elf64_header->e_ident[0]), class, ei_data, 
        ei_version, os_abi, elf64_header->e_type, 
        elf64_header->e_machine, elf64_header->e_version);

    fprintf(stdout, "%-36s0x%llx\n", " Entry point:", 
    (unsigned long long)elf64_header->e_entry);
    fprintf(stdout, "%-36s%ld\n", " Start of program headers:",
    elf64_header->e_phoff);
    fprintf(stdout, "%-36s%ld\n", " Start of section headers:",
    elf64_header->e_shoff);

    fprintf(stdout, "%-36s0x%x\n", " Flags:", elf64_header->e_flags);

    fprintf(stdout, "%-36s%d\n", " Size of this header:", 
    elf64_header->e_ehsize);

    fprintf(stdout, "%-36s%d\n", " Size of program headers:", 
    elf64_header->e_phentsize);

    fprintf(stdout, "%-36s%d\n", "Number of program headers:", 
    elf64_header->e_phnum);

    fprintf(stdout, "%-36s%d\n", " Size of section headers:", 
    elf64_header->e_shentsize);

    fprintf(stdout, "%-36s%d\n", " Number of section headers",
    elf64_header->e_shnum);

    fprintf(stdout, "%-36s%d\n", " Section header string table index:",
    elf64_header->e_shstrndx);
}
