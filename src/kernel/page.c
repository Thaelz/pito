#include <common/stdtypes.h>
#include <common/stdlib.h>
#include <kernel/page.h>
#include <kernel/atag.h>
#include <kernel/list.h>

extern uint8_t __end; /* Comes from linker script */

static uint32_t num_pages;

DEFINE_LIST(page);
IMPLEMENT_LIST(page);

static page_t * all_pages_array;
page_list_t *free_pages;
uint32_t LIMIT_ADRESS_SPACES;

void *alloc_page(void) 
{
  page_t *page;
  void *page_mem;

  page = pop_page_list(free_pages);
  page->flags.allocated = 1;
  page->flags.kernel_page = 1;

  page_mem = (void *)((page - all_pages_array) * PAGE_SIZE);

  bzero(page_mem, PAGE_SIZE);

  return page;
}

void free_page(void *ptr)
{
  page_t *page;

  page = all_pages_array + ((uint32_t)ptr / PAGE_SIZE);

  page->flags.allocated = 0;
  append_page_list(free_pages, page);
}

void mem_init(atag_t * atags) 
{
    uint32_t mem_size,  page_array_len, kernel_pages, i;

    // Get the total number of pages
    mem_size = get_mem_size(atags);
    num_pages = mem_size / PAGE_SIZE;

    // Allocate space for all those pages' metadata.  Start this block just after the kernel image is finished
    page_array_len = sizeof(page_t) * num_pages; /* in bytes */
    all_pages_array = (page_t *)&__end;
    bzero(all_pages_array, page_array_len);
    INITIALIZE_LIST(free_pages);

    // Iterate over all pages and mark them with the appropriate flags
    // Start with kernel pages
    kernel_pages = ((uint32_t)&__end) / PAGE_SIZE;
    for (i = 0; i < kernel_pages; i++) {
        all_pages_array[i].vaddr_mapped = i * PAGE_SIZE;    // Identity map the kernel pages
        all_pages_array[i].flags.allocated = 1;
        all_pages_array[i].flags.kernel_page = 1;
    }
    // Map the rest of the pages as unallocated, and add them to the free list
    for(; i < num_pages; i++){
        all_pages_array[i].flags.allocated = 0;
        append_page_list(free_pages, &all_pages_array[i]);
    }

}
