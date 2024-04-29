#include "../include/helper_functions.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Function to swap the byte order of a 16-bit integer
uint16_t swap_uint16(uint16_t val) {
    return (val << 8) | (val >> 8);
}

// Function to swap the byte order of a 32-bit unsigned integer
uint32_t swap_uint32(uint32_t val) {
    return ((val >> 24) & 0x000000FF) |       
           ((val << 8) & 0x00FF0000) |       
           ((val >> 8) & 0x0000FF00) | 
           ((val << 24) & 0xFF000000);
}

void fread_uint16_t(uint16_t* val_ptr, FILE* fp)
{
    if (fread(val_ptr, sizeof(uint16_t), 1, fp) != 1)
    {
        fprintf(stderr, "error reading file\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
}

void fread_uint32_t(uint32_t* val_ptr, FILE* fp)
{
    if (fread(val_ptr, sizeof(uint32_t), 1, fp) != 1)
    {
        fprintf(stderr, "error reading file\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
}

void fread_uint64_t(uint64_t* val_ptr, FILE* fp)
{
    if (fread(val_ptr, sizeof(uint64_t), 1, fp) != 1)
    {
        fprintf(stderr, "error reading file\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
}

void print_help()
{
    fprintf(stdout, "Usage: ./disp-header [options] <elf-file>\n");
    fprintf(stdout, "Options:\n");
    fprintf(stdout, " -h: print file header \n");
    fprintf(stdout, " -help: print help message\n");
}