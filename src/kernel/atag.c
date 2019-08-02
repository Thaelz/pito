#include <kernel/atag.h>

uint32_t get_mem_size(atag_t * tag) {
#ifndef QEMU
   while (tag->tag != NONE) {
       if (tag->tag == MEM) {
           return tag->mem.size;
       }
       tag += tag->tag_size; 
   }
   return 0;
#else
   return 1024 * 1024 * 128;
#endif
}
