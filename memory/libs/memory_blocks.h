#ifndef _MEM_BLOCKS_
#define _MEM_BLOCKS_

#include <stdbool.h>

typedef struct{
    int start_index;
    int block_size;
    bool used;
    struct block* next;
}block;

#define swap_values(x, y, T) do { T tmp = x; x = y; y = tmp; } while (0)

void swap_blocks(block* block1, block* block2);
void add_new_block(block** head, int start_index, int block_size, bool used);
void print_memory_blocks(block* head);
int __combine_free_memory_blocks_size_and_release_them(block** head);
void combine_free_memory_blocks_size_and_release_them(block** head);
void arrange_memory_blocks(block** head);
void sort_memory_blocks(block** head);

#endif