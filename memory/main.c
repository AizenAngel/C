#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "error_codes.h"
#include "constatnts.h"
#include "memory_blocks.h"

/*
?TODO: Choose/Create more appropriate data structure for saving memory blocks, for tasks:
?       1) allocating new memory block
?       2) "freeing" unused  memory block
?       3) connect free memory blocks after fragmentation
?       4) if more than 10 memory blocks are taken, find a way to allocate more memory
*/

bool used_array[10] = {false, false, false, false, false, 
                       false, false, false, false, false};

#define UNUSED(x) (void)(x)

void print_memory(const char* memory){
    int num_blocks = strlen(memory) / BLOCK_LEN;

    for(int i = 0; i < num_blocks; i++)
        printf("\t%.*s\n", BLOCK_LEN, memory + i * BLOCK_LEN);
}

void error(int code){
    switch(code){
        case MEMORY_ERROR: fprintf(stderr, "Memory error!");
                            exit(1);
    }
}

void set_memory(char** memory, int index, int len){
    int set_index = -1;

    for(int i = 0; i < 10; i++){
        if(!used_array[i]){
            set_index = i;
            break;
        }
    }

    if(set_index == -1){
        return;
    }
        

    used_array[set_index] = true;

    memset(*(memory) + index, set_index + '0', len);

    return;
}

/*
Initialize memory block and set it's inital value to indicate that it's empty.
*/

void initialize_memory_block(char** memory, block** mem_blocks, int* NUM_MEM_BLOCKS, int num_blocks){
    
    *memory = (char*) malloc(num_blocks * BLOCK_LEN * sizeof(char));
    *mem_blocks = (block*) malloc(BLOCK_LEN * sizeof(block));

    memset(*memory, '*', num_blocks * BLOCK_LEN);

    mem_blocks[0]->start_index = 0;
    mem_blocks[0]->block_size = num_blocks * BLOCK_LEN;
    mem_blocks[0]->used = false;

    *NUM_MEM_BLOCKS = 1;

    if(!memory)
        error(MEMORY_ERROR);
}

bool allocate_memory_block(char** memory, block** mem_blocks, int block_size){
    if(*mem_blocks == NULL)
        return false;

    if(!(*mem_blocks)->used && (*mem_blocks)->block_size >= block_size){
 
        int unused_size_block = (*mem_blocks)->block_size - block_size;

        if(unused_size_block == 0){
            (*mem_blocks)->used = true;
            
            return true;
        }

        int unused_block_start_index = (*mem_blocks)->start_index + block_size;
        int unused_block_size = (*mem_blocks)->block_size - block_size;

        block* new_block = create_new_memory_block(unused_block_start_index, unused_block_size);
        
        (*mem_blocks)->used = true;
        (*mem_blocks)->block_size = block_size;

        block* old_next = (*mem_blocks)->next;
        (*mem_blocks)->next = new_block;
        new_block->next = old_next;

        set_memory(memory, (*mem_blocks)->start_index, (*mem_blocks)->block_size);

        return true;
    }

    if(allocate_memory_block(memory, &((*mem_blocks)->next), block_size))
        return true;
        
    return false;
}

int main(int argc, char** argv){

    UNUSED(argc);
    UNUSED(argv);

    int NUM_BLOCKS;
    int action_code;
    char* memory;

    block* mem_blocks;
    int NUM_MEM_BLOCKS;

    printf("Enter number of blocks: ");
    scanf("%d", &NUM_BLOCKS);
    
    initialize_memory_block(&memory, &mem_blocks, &NUM_MEM_BLOCKS, NUM_BLOCKS);


    while(true){  
        
        printf("Action: ");
        scanf("%d", &action_code);

        switch(action_code){
            case 0: 
                print_memory(memory);
                break;
            case 1:
                print_memory_blocks(mem_blocks);
                break;
            case 2:{
                int block_size;
                printf("\tEnter block's size:\n\t");
                scanf("%d", &block_size);
                allocate_memory_block(&memory, &mem_blocks, block_size);
            }
        }        

    }

    return 0;
}