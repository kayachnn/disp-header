#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "../include/elf_header.h"
#include "../include/helper_functions.h"

void print_elf_header(char* filename);

// 0x7f E L F
const uint8_t elf_header_magic_nr[4] = {0x7f, 'E', 'L', 'F'};

int main(int argc, char* argv[])
{
    int opt;
    char* filename = NULL;
    int print_header = 0;
    while ((opt = getopt(argc, argv, "h")) != -1)
    {
        switch(opt)
        {
            case 'h':
            {
                print_header = 1;
                break;
            }
            default:
                print_help();
                return 1;
        }
    }

    if (print_header)
    {
        if (optind < argc)
        {
            filename = argv[optind];
            print_elf_header(filename);
        }
        else 
        {
            print_help();
            return 1;
        }
    }

    return 0;
}

void print_elf_header(char *filename)
{
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "Error while opening file\n");
        exit(EXIT_FAILURE);
    }

    uint8_t e_ident[EI_NIDENT] = {0};
    size_t bytes_read = fread(e_ident, sizeof(uint8_t), EI_NIDENT, fp);
    if (bytes_read != EI_NIDENT)
    {
        fprintf(stderr, "Wrong file format\n");
        exit(EXIT_FAILURE);
    }

    //check for the magic firs 4 bytes
    if (memcmp(e_ident, elf_header_magic_nr, 
    sizeof(elf_header_magic_nr)) != 0)
    {
        fprintf(stderr, "Wrong file format\n");
        exit(EXIT_FAILURE);
    }

    enum EI_CLASS class;
    switch (e_ident[EI_CLASS])
    {
        case 0x01:
        {
            class = ELFCLASS32;
            break;
        }
        case 0x02:
        {
            class = ELFCLASS64;
            break;
        }
        default:
        {
            class = ELFCLASSNONE;
            break;
        }
    }

    enum EI_DATA ei_data;
    switch(e_ident[EI_DATA])
    {
        case ELFDATA2LSB:
        {
            ei_data = ELFDATA2LSB;
            break;
        }
        case ELFDATA2MSB:
        {
            ei_data = ELFDATA2MSB;
            break;
        }
        default:
        {
            ei_data = ELFDATANONE;
            break;
        }
    }

    enum EI_VERSION ei_version;
    switch(e_ident[EI_VERSION])
    {
        case EV_CURRENT:
        {
            ei_version = EV_CURRENT;
            break;
        }
        default:
        {
            ei_version = EV_NONE;
            break;
        }
    }

    enum EI_OSABI os_abi;
    switch(e_ident[EI_OSABI])
    {
        case ELFOSABI_SYSV:
        {
            os_abi = ELFOSABI_SYSV;
            break;
        }
        case ELFOSABI_HPUX:
        {
            os_abi = ELFOSABI_HPUX;
            break;
        }
        case ELFOSABI_STANDALONE:
        {
            os_abi = ELFOSABI_STANDALONE;
            break;
        }
    }

    if (e_ident[EI_CLASS] == ELFCLASS32)
    {
        Elf32_Ehdr elf32_header;
        memcpy(&(elf32_header.e_ident), e_ident, EI_NIDENT);

        fread_uint16_t(&(elf32_header.e_type), fp);
        fread_uint16_t(&(elf32_header.e_machine), fp);
        fread_uint32_t(&(elf32_header.e_version), fp);


        fread_uint32_t(&(elf32_header.e_entry), fp);
        fread_uint32_t(&(elf32_header.e_shoff), fp);
        fread_uint32_t(&(elf32_header.e_shoff), fp);

        fread_uint32_t(&(elf32_header.e_flags), fp);
        fread_uint16_t(&(elf32_header.e_ehsize), fp);
        fread_uint16_t(&(elf32_header.e_phentsize), fp);
        fread_uint16_t(&(elf32_header.e_phnum), fp);
        fread_uint16_t(&(elf32_header.e_shentsize), fp);
        fread_uint16_t(&(elf32_header.e_shnum), fp);
        fread_uint16_t(&(elf32_header.e_shstrndx), fp);

        print_header_information_32(
        &elf32_header, class, ei_data, 
        ei_version, os_abi);
    }
    else if (e_ident[EI_CLASS] == ELFCLASS64)
    {
        Elf64_Ehdr elf64_header;
        memcpy(&(elf64_header.e_ident), e_ident, EI_NIDENT);

        fread_uint16_t(&(elf64_header.e_type), fp);
        fread_uint16_t(&(elf64_header.e_machine), fp);
        fread_uint32_t(&(elf64_header.e_version), fp);

        fread_uint64_t(&(elf64_header.e_entry), fp);
        fread_uint64_t(&(elf64_header.e_phoff), fp);
        fread_uint64_t(&(elf64_header.e_shoff), fp);

        fread_uint32_t(&(elf64_header.e_flags), fp);
        fread_uint16_t(&(elf64_header.e_ehsize), fp);
        fread_uint16_t(&(elf64_header.e_phentsize), fp);
        fread_uint16_t(&(elf64_header.e_phnum), fp);
        fread_uint16_t(&(elf64_header.e_shentsize), fp);
        fread_uint16_t(&(elf64_header.e_shnum), fp);
        fread_uint16_t(&(elf64_header.e_shstrndx), fp);

        print_header_information_64(
        &elf64_header, class, ei_data, 
        ei_version, os_abi);
    }
    
    fclose(fp);
}