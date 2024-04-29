#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
// Function to swap the byte order of a 16-bit integer
uint16_t swap_uint16(uint16_t val);
uint32_t swap_uint32(uint32_t val);

void fread_uint16_t(uint16_t* val_ptr, FILE* fp);
void fread_uint32_t(uint32_t* val_ptr, FILE* fp);
void fread_uint64_t(uint64_t* val_ptr, FILE* fp);

void print_help();
#endif