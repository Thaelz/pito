#include <common/stdtypes.h>

#ifndef __ATAG_H
#define __ATAG_H

typedef enum {
    NONE        = 0x00000000,
    CORE        = 0x54410001,
    MEM         = 0x54410002,
    VIDEOTEXT   = 0x54410003,
    RAMDISK     = 0x54410004,
    INITRD2     = 0x54410005,
    SERIAL      = 0x54410006,
    REVISION    = 0x54410007,
    VIDEOLFB    = 0x54410008,
    CMDLINE     = 0x54410009,
} atag_tag_t;

typedef struct {
    uint32_t size;
    uint32_t start;
} mem_t;

typedef struct atag {
    uint32_t tag_size;
    atag_tag_t tag;
    union {
        mem_t mem;
    };
} atag_t;

uint32_t get_mem_size(atag_t * tag);

#endif
