#include <kernel/atag.h>

#ifndef __PAGE_H
#define __PAGE_H

#define PAGE_SIZE 4096

typedef struct {
    uint8_t allocated: 1;           // This page is allocated to something
    uint8_t kernel_page: 1;         // This page is a part of the kernel
    uint32_t reserved: 30;
} page_flags_t;

typedef struct page {
    uint32_t vaddr_mapped;  // The virtual address that maps to this page   
    page_flags_t flags;
    struct page *next;
} page_t;

void mem_init(atag_t * atags);

#endif
